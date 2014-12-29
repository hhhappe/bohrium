#include "engine.hpp"
#include "symbol_table.hpp"
#include "timevault.hpp"

#include <algorithm>
#include <set>
#include <iomanip>

using namespace std;
using namespace bohrium::core;

namespace bohrium{
namespace engine {
namespace cpu {

typedef std::vector<bh_instruction> instr_iter;
typedef std::vector<bh_ir_kernel>::iterator krnl_iter;

const char Engine::TAG[] = "Engine";

Engine::Engine(
    const string compiler_cmd,
    const string template_directory,
    const string kernel_directory,
    const string object_directory,
    const size_t vcache_size,
    const bool preload,
    const bool jit_enabled,
    const bool jit_fusion,
    const bool jit_dumpsrc,
    const bool dump_rep)
: compiler_cmd(compiler_cmd),
    template_directory(template_directory),
    kernel_directory(kernel_directory),
    object_directory(object_directory),
    vcache_size(vcache_size),
    preload(preload),
    jit_enabled(jit_enabled),
    jit_fusion(jit_fusion),
    jit_dumpsrc(jit_dumpsrc),
    storage(object_directory, kernel_directory),
    specializer(template_directory),
    compiler(compiler_cmd),
    exec_count(0),
    dump_rep(dump_rep)
{
    bh_vcache_init(vcache_size);    // Victim cache
    if (preload) {
        storage.preload();
    }
}

Engine::~Engine()
{   
    if (vcache_size>0) {    // De-allocate the malloc-cache
        bh_vcache_clear();
        bh_vcache_delete();
    }
}

string Engine::text()
{
    stringstream ss;
    ss << "ENVIRONMENT {" << endl;
    ss << "  BH_CORE_VCACHE_SIZE="      << this->vcache_size  << endl;
    ss << "  BH_VE_CPU_PRELOAD="        << this->preload      << endl;    
    ss << "  BH_VE_CPU_JIT_ENABLED="    << this->jit_enabled  << endl;    
    ss << "  BH_VE_CPU_JIT_FUSION="     << this->jit_fusion   << endl;
    ss << "  BH_VE_CPU_JIT_DUMPSRC="    << this->jit_dumpsrc  << endl;
    ss << "}" << endl;
    
    ss << "Attributes {" << endl;
    ss << "  " << specializer.text();    
    ss << "  " << compiler.text();
    ss << "}" << endl;

    return ss.str();    
}

bh_error Engine::sij_mode(SymbolTable& symbol_table, vector<tac_t>& program, Block& block)
{
    bh_error res = BH_SUCCESS;

    tac_t& tac = block.tac(0);
    switch(tac.op) {
        case NOOP:
            break;

        case SYSTEM:
            switch(tac.oper) {
                case DISCARD:
                case SYNC:
                    break;

                case FREE:
                    res = bh_vcache_free_base(symbol_table[tac.out].base);
                    if (BH_SUCCESS != res) {
                        fprintf(stderr, "Unhandled error returned by bh_vcache_free_base(...) "
                                        "called from Engine::sij_mode)\n");
                        return res;
                    }
                    break;

                default:
                    fprintf(stderr, "Yeah that does not fly...\n");
                    return BH_ERROR;
            }
            break;

        case EXTENSION:
            {
                map<bh_opcode,bh_extmethod_impl>::iterator ext;
                ext = extensions.find(static_cast<bh_instruction*>(tac.ext)->opcode);
                if (ext != extensions.end()) {
                    bh_extmethod_impl extmethod = ext->second;
                    res = extmethod(static_cast<bh_instruction*>(tac.ext), NULL);
                    if (BH_SUCCESS != res) {
                        fprintf(stderr, "Unhandled error returned by extmethod(...) \n");
                        return res;
                    }
                }
            }
            break;

        // Array operations (MAP | ZIP | REDUCE | SCAN)
        case MAP:
        case ZIP:
        case GENERATE:
        case REDUCE:
        case SCAN:

            //
            // We start by creating a symbol for the block
            block.symbolize();
            //
            // JIT-compile the block if enabled
            if (jit_enabled && \
                (!storage.symbol_ready(block.symbol()))) {   
                                                            // Specialize sourcecode
                string sourcecode = specializer.specialize(symbol_table, block, 0, 0);
                if (jit_dumpsrc==1) {                       // Dump sourcecode to file                
                    core::write_file(
                        storage.src_abspath(block.symbol()),
                        sourcecode.c_str(), 
                        sourcecode.size()
                    );
                }
                // Send to compiler
                bool compile_res = compiler.compile(
                    storage.obj_abspath(block.symbol()), 
                    sourcecode.c_str(), 
                    sourcecode.size()
                );
                if (!compile_res) {
                    fprintf(stderr, "Engine::sij_mode(...) == Compilation failed.\n");
                    return BH_ERROR;
                }
                                                            // Inform storage
                storage.add_symbol(block.symbol(), storage.obj_filename(block.symbol()));
            }

            //
            // Load the compiled code
            //
            if ((!storage.symbol_ready(block.symbol())) && \
                (!storage.load(block.symbol()))) {                // Need but cannot load

                fprintf(stderr, "Engine::sij_mode(...) == Failed loading object.\n");
                return BH_ERROR;
            }

            //
            // Allocate memory for operands
            res = bh_vcache_malloc_base(symbol_table[tac.out].base);
            if (BH_SUCCESS != res) {
                fprintf(stderr, "Unhandled error returned by bh_vcache_malloc_base() "
                                "called from Engine::sij_mode\n");
                return res;
            }

            //
            // Execute block handling array operations.
            // 
            storage.funcs[block.symbol()](block.operands());

            break;
    }
    return BH_SUCCESS;
}

/**
 *  Count temporaries in the 
 *
 */
void count_temp( set<size_t>& disqualified,  set<size_t>& freed,
                 vector<size_t>& reads,  vector<size_t>& writes,
                 set<size_t>& temps) {

    for(set<size_t>::iterator fi=freed.begin(); fi!=freed.end(); ++fi) {
        size_t operand_idx = *fi;
        if ((reads[operand_idx] == 1) && (writes[operand_idx] == 1)) {
            temps.insert(operand_idx);
        }
    }
}

void count_rw(  tac_t& tac, set<size_t>& freed,
                vector<size_t>& reads, vector<size_t>& writes,
                set<size_t>& temps)
{

    switch(tac.op) {    // Do read/write counting ...
        case MAP:
            reads[tac.in1]++;
            writes[tac.out]++;
            break;

        case EXTENSION:
        case ZIP:
            if (tac.in2!=tac.in1) {
                reads[tac.in2]++;
            }
            reads[tac.in1]++;
            writes[tac.out]++;
            break;
        case REDUCE:
        case SCAN:
            reads[tac.in2]++;
            reads[tac.in1]++;
            writes[tac.out]++;
            break;

        case GENERATE:
            switch(tac.oper) {
                case RANDOM:
                case FLOOD:
                    reads[tac.in1]++;
                default:
                    writes[tac.out]++;
            }
            break;

        case NOOP:
        case SYSTEM:    // ... or annotate operands with temp potential.
            if (FREE == tac.oper) {
                freed.insert(tac.out);
            }
            break;
    }
}

bh_error Engine::fuse_mode(SymbolTable& symbol_table, std::vector<tac_t>& program, Block& block)
{
    bh_error res = BH_SUCCESS;

    //
    // Determine temps and fusion_layout
    set<size_t> freed;
    vector<size_t> reads(symbol_table.size()+1);
    fill(reads.begin(), reads.end(), 0);
    vector<size_t> writes(symbol_table.size()+1);
    fill(writes.begin(), writes.end(), 0);
    set<size_t> temps;

    LAYOUT fusion_layout = SCALAR;
    for(size_t tac_idx=0; tac_idx<block.ntacs(); ++tac_idx) {
        tac_t& tac = block.tac(tac_idx);
        count_rw(tac, freed, reads, writes, temps);

        switch(tac_noperands(tac)) {
            case 3:
                if (symbol_table[tac.in2].layout > fusion_layout) {
                    fusion_layout = symbol_table[tac.in2].layout;
                }
            case 2:
                if (symbol_table[tac.in1].layout > fusion_layout) {
                    fusion_layout = symbol_table[tac.in1].layout;
                }
            case 1:
                if (symbol_table[tac.out].layout > fusion_layout) {
                    fusion_layout = symbol_table[tac.out].layout;
                }
            default:
                break;
        }
    }
    count_temp(symbol_table.disqualified(), freed, reads, writes, temps);
    //
    // Turn temps into scalars
    for(set<size_t>::iterator ti=temps.begin(); ti!=temps.end(); ++ti) {
        symbol_table.turn_scalar_temp(*ti);
    }

    //
    // The operands might have been modified at this point, so we need to create a new symbol.
    if (!block.symbolize()) {
        fprintf(stderr, "Engine::execute(...) == Failed creating symbol.\n");
        return BH_ERROR;
    }

    //
    // JIT-compile the block if enabled
    //
    if (jit_enabled && \
        (!storage.symbol_ready(block.symbol()))) {   
        // Specialize and dump sourcecode to file
        string sourcecode = specializer.specialize(symbol_table, block, fusion_layout);
        if (jit_dumpsrc==1) {
            core::write_file(
                storage.src_abspath(block.symbol()),
                sourcecode.c_str(), 
                sourcecode.size()
            );
        }
        // Send to compiler
        bool compile_res = compiler.compile(
            storage.obj_abspath(block.symbol()),
            sourcecode.c_str(), 
            sourcecode.size()
        );
        if (!compile_res) {
            fprintf(stderr, "Engine::execute(...) == Compilation failed.\n");

            return BH_ERROR;
        }
        // Inform storage
        storage.add_symbol(block.symbol(), storage.obj_filename(block.symbol()));
    }

    //
    // Load the compiled code
    //
    if ((block.narray_tacs() > 0) && \
        (!storage.symbol_ready(block.symbol())) && \
        (!storage.load(block.symbol()))) {// Need but cannot load

        fprintf(stderr, "Engine::execute(...) == Failed loading object.\n");
        return BH_ERROR;
    }

    //
    // Allocate memory for output
    //

    for(size_t i=0; i<block.ntacs(); ++i) {
        tac_t& tac = block.tac(i);
        operand_t& operand = symbol_table[tac.out];

        if (((tac.op & ARRAY_OPS)>0) && (operand.layout!= SCALAR_TEMP)) {
            res = bh_vcache_malloc_base(operand.base);
            if (BH_SUCCESS != res) {
                fprintf(stderr, "Unhandled error returned by bh_vcache_malloc() "
                                "called from bh_ve_cpu_execute()\n");
                return res;
            }
        }
    }

    //
    // Execute block handling array operations.
    // 
    DEBUG(TAG, "SYMBOL="<< block.symbol());
    for(size_t tac_idx=0; tac_idx<block.ntacs(); ++tac_idx) {
        tac_t& tac = block.tac(tac_idx);
        cout << tac_text(tac) << endl;
    }

    cout << "Executing: " << block.symbol() << endl;
    storage.funcs[block.symbol()](block.operands());

    //
    // De-Allocate operand memory

    for(size_t i=0; i<block.ntacs(); ++i) {
        tac_t& tac = block.tac(i);
        operand_t& operand = symbol_table[tac.out];

        if (tac.oper == FREE) {
            res = bh_vcache_free_base(operand.base);
            if (BH_SUCCESS != res) {
                fprintf(stderr, "Unhandled error returned by bh_vcache_free(...) "
                                "called from bh_ve_cpu_execute)\n");
                return res;
            }
        }
    }

    return BH_SUCCESS;
}

bh_error Engine::execute(bh_ir* bhir)
{
    exec_count++;
    DEBUG(TAG, "EXEC #" << exec_count);
    bh_error res = BH_SUCCESS;

    //
    //  Map kernels to blocks one at a time and execute them.
    for(krnl_iter krnl = bhir->kernel_list.begin();
        krnl != bhir->kernel_list.end();
        ++krnl) {

        bh_intp ninstrs = krnl->instrs.size();

        //
        // Instantiate the symbol-table and tac-program
        SymbolTable symbol_table(ninstrs*6+2);              // SymbolTable
        vector<tac_t> program(ninstrs);                     // Program
        
        // Map instructions to tac and symbol_table
        instrs_to_tacs(krnl->instrs, program, symbol_table);
        symbol_table.count_tmp();

        Block block(symbol_table, program);                 // Block
        block.clear();
        block.compose(krnl->instrs);

        // FUSE_MODE
        if (jit_fusion && \
            (block.narray_tacs() > 1)) {

            DEBUG(TAG, "FUSE START");
            res = fuse_mode(symbol_table, program, block);
            if (BH_SUCCESS != res) {
                return res;
            }
            DEBUG(TAG, "FUSE END");
        
        // SIJ_MODE
        } else {

            DEBUG(TAG, "SIJ START");
            for(size_t instr_i=0; instr_i<ninstrs; ++instr_i) {
                // Compose the block
                block.clear();
                block.compose(instr_i, instr_i);

                // Generate/Load code and execute it
                res = sij_mode(symbol_table, program, block);
                if (BH_SUCCESS != res) {
                    return res;
                }
            }
            DEBUG(TAG, "SIJ END");
        }
    }

    return res;
}

bh_error Engine::register_extension(bh_component& instance, const char* name, bh_opcode opcode)
{
    bh_extmethod_impl extmethod;
    bh_error err = bh_component_extmethod(&instance, name, &extmethod);
    if (err != BH_SUCCESS) {
        return err;
    }

    if (extensions.find(opcode) != extensions.end()) {
        fprintf(stderr, "[CPU-VE] Warning, multiple registrations of the same"
               "extension method '%s' (opcode: %d)\n", name, (int)opcode);
    }
    extensions[opcode] = extmethod;

    return BH_SUCCESS;
}

}}}
