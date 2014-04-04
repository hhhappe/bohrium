//
// Elementwise operation on two-dimensional arrays using strided indexing
{
    {{#OPERAND}}{{#ARRAY}}
    int64_t a{{NR}}_shape_ld    = a{{NR}}_shape[1];
    int64_t a{{NR}}_shape_sld   = a{{NR}}_shape[0];

    int64_t a{{NR}}_stride_ld   = a{{NR}}_stride[1];
    int64_t a{{NR}}_stride_sld  = a{{NR}}_stride[0];

    int64_t a{{NR}}_rewind_ld   = a{{NR}}_shape_ld * a{{NR}}_stride_ld;
    {{/ARRAY}}{{/OPERAND}}

    int mthreads = omp_get_max_threads();
    int64_t nworkers = a{{NR_OUTPUT}}_shape_sld > mthreads ? mthreads : 1;

    #pragma omp parallel num_threads(nworkers)
    {
        int tid      = omp_get_thread_num();    // Work partitioning
        int nthreads = omp_get_num_threads();

        int64_t work = a{{NR_OUTPUT}}_shape_sld / nthreads;
        int64_t work_offset = work * tid;
        if (tid==nthreads-1) {
            work += a{{NR_OUTPUT}}_shape_sld % nthreads;
        }
        int64_t work_end = work_offset+work;
                                                // Pointer fixes
        {{#OPERAND}}{{#ARRAY}}
        {{TYPE}} *a{{NR}}_current = a{{NR}}_first + (work_offset * a{{NR}}_stride_sld);
        {{/ARRAY}}{{/OPERAND}}

        for(int64_t j=work_offset; j<work_end; ++j) {
            for (int64_t i = 0; i < a{{NR_OUTPUT}}_shape_ld; ++i) {
                {{#OPERATORS}}
                {{OPERATOR}};
                {{/OPERATORS}}
               
                {{#OPERAND}}{{#ARRAY}}
                a{{NR}}_current += a{{NR}}_stride_ld;
                {{/ARRAY}}{{/OPERAND}}
            }
            {{#OPERAND}}{{#ARRAY}}
            a{{NR}}_current -= a{{NR}}_rewind_ld;
            a{{NR}}_current += a{{NR}}_stride_sld;
            {{/ARRAY}}{{/OPERAND}}
        }
    }
    
    {{#OPERAND}}{{#SCALAR}}
    // Write scalar-operand to main-memory;
    // Note this is only necessary for non-temporary scalar-operands.
    // So this code should only be generated for non-temps.
    if ({{NR_OUTPUT}} == {{NR}}) {
        *a{{NR}}_first = a{{NR}}_current;
    }
    {{/SCALAR}}{{/OPERAND}}
}

