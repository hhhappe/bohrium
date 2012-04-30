/*
 * Copyright 2011 Simon A. F. Lund <safl@safl.dk>
 *
 * This file is part of cphVB.
 *
 * cphVB is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cphVB is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cphVB. If not, see <http://www.gnu.org/licenses/>.
 */
#include <cphvb.h>
#include <cphvb_compute.h>
#include "functors.hpp"
#include "traverser.hpp"

cphvb_error cphvb_compute_apply( cphvb_instruction *instr ) {

    computeloop comp = cphvb_compute_get( instr );
    return comp( instr );

}

computeloop cphvb_compute_get( cphvb_instruction *instr ) {

    // Poly contains a unique value, pairing an opcode with its function signature.
    // All in one nicely switchable value.
    long int poly;
 
    if (cphvb_operands(instr->opcode) == 3) {   // Three operands

        if (cphvb_is_constant(instr->operand[1])) {             // First operand is constant
            poly = instr->opcode \
                +(instr->operand[0]->type << 8) \
                +(instr->constant.type << 12) \
                +(instr->operand[2]->type << 16) \
                +(1 << 17);

        } else if (cphvb_is_constant(instr->operand[2])) {      // Second operand is constant
            poly = instr->opcode \
                +(instr->operand[0]->type << 8) \
                +(instr->operand[1]->type << 12) \
                +(instr->constant.type << 16) \
                +(1 << 18);

        } else {                                                // No constant operand
            poly = instr->opcode \
                +(instr->operand[0]->type << 8) \
                +(instr->operand[1]->type << 12) \
                +(instr->operand[2]->type << 16);
        }

    } else {                                    // Two operands

        if (cphvb_is_constant(instr->operand[1])) {
            poly = instr->opcode \
                +(instr->operand[0]->type << 8) \
                +(instr->constant.type << 12) \
                +(1 << 17);
        } else {
            poly = instr->opcode \
                +(instr->operand[0]->type << 8) \
                +(instr->operand[1]->type << 12);
        }
    }

    switch(poly) {

        case CPHVB_IDENTITY + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12):
            return &traverse_aa<cphvb_int8,cphvb_int8, identity_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int8,cphvb_int8, identity_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12):
            return &traverse_aa<cphvb_uint8,cphvb_uint8, identity_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint8,cphvb_uint8, identity_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12):
            return &traverse_aa<cphvb_int16,cphvb_int16, identity_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int16,cphvb_int16, identity_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12):
            return &traverse_aa<cphvb_uint16,cphvb_uint16, identity_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint16,cphvb_uint16, identity_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12):
            return &traverse_aa<cphvb_int32,cphvb_int32, identity_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int32,cphvb_int32, identity_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12):
            return &traverse_aa<cphvb_uint32,cphvb_uint32, identity_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint32,cphvb_uint32, identity_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12):
            return &traverse_aa<cphvb_int64,cphvb_int64, identity_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int64,cphvb_int64, identity_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12):
            return &traverse_aa<cphvb_uint64,cphvb_uint64, identity_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint64,cphvb_uint64, identity_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, identity_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, identity_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, identity_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_IDENTITY + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, identity_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_RAD2DEG + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, rad2deg_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_RAD2DEG + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, rad2deg_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_RAD2DEG + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, rad2deg_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_RAD2DEG + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, rad2deg_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_EXP + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, exp_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_EXP + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, exp_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_EXP + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, exp_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_EXP + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, exp_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_SQUARE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12):
            return &traverse_aa<cphvb_int8,cphvb_int8, square_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_SQUARE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int8,cphvb_int8, square_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_SQUARE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12):
            return &traverse_aa<cphvb_uint8,cphvb_uint8, square_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_SQUARE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint8,cphvb_uint8, square_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_SQUARE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12):
            return &traverse_aa<cphvb_int16,cphvb_int16, square_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_SQUARE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int16,cphvb_int16, square_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_SQUARE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12):
            return &traverse_aa<cphvb_uint16,cphvb_uint16, square_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_SQUARE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint16,cphvb_uint16, square_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_SQUARE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12):
            return &traverse_aa<cphvb_int32,cphvb_int32, square_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_SQUARE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int32,cphvb_int32, square_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_SQUARE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12):
            return &traverse_aa<cphvb_uint32,cphvb_uint32, square_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_SQUARE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint32,cphvb_uint32, square_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_SQUARE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12):
            return &traverse_aa<cphvb_int64,cphvb_int64, square_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_SQUARE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int64,cphvb_int64, square_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_SQUARE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12):
            return &traverse_aa<cphvb_uint64,cphvb_uint64, square_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_SQUARE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint64,cphvb_uint64, square_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_SQUARE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, square_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_SQUARE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, square_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_SQUARE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, square_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_SQUARE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, square_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, divide_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, divide_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, divide_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, divide_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, divide_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, divide_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, divide_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, divide_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, divide_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, divide_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, divide_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, divide_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, divide_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, divide_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, divide_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, divide_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, divide_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, divide_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, divide_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, divide_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, divide_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, divide_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, divide_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, divide_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, divide_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, divide_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, divide_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, divide_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, divide_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, divide_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, less_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, less_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, less_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int8,cphvb_int8, less_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int8,cphvb_int8, less_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int8,cphvb_int8, less_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint8,cphvb_uint8, less_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint8,cphvb_uint8, less_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint8,cphvb_uint8, less_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int16,cphvb_int16, less_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int16,cphvb_int16, less_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int16,cphvb_int16, less_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint16,cphvb_uint16, less_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint16,cphvb_uint16, less_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint16,cphvb_uint16, less_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int32,cphvb_int32, less_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int32,cphvb_int32, less_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int32,cphvb_int32, less_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint32,cphvb_uint32, less_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint32,cphvb_uint32, less_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint32,cphvb_uint32, less_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int64,cphvb_int64, less_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int64,cphvb_int64, less_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int64,cphvb_int64, less_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint64,cphvb_uint64, less_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint64,cphvb_uint64, less_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint64,cphvb_uint64, less_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float32,cphvb_float32, less_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float32,cphvb_float32, less_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float32,cphvb_float32, less_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float64,cphvb_float64, less_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float64,cphvb_float64, less_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LESS + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float64,cphvb_float64, less_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_RINT + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, rint_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_RINT + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, rint_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_RINT + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, rint_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_RINT + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, rint_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ARCTAN2 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, arctan2_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCTAN2 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, arctan2_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCTAN2 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, arctan2_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCTAN2 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, arctan2_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ARCTAN2 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, arctan2_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ARCTAN2 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, arctan2_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_SIGN + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12):
            return &traverse_aa<cphvb_int8,cphvb_int8, sign_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_SIGN + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int8,cphvb_int8, sign_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_SIGN + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12):
            return &traverse_aa<cphvb_uint8,cphvb_uint8, sign_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_SIGN + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint8,cphvb_uint8, sign_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_SIGN + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12):
            return &traverse_aa<cphvb_int16,cphvb_int16, sign_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_SIGN + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int16,cphvb_int16, sign_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_SIGN + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12):
            return &traverse_aa<cphvb_uint16,cphvb_uint16, sign_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_SIGN + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint16,cphvb_uint16, sign_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_SIGN + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12):
            return &traverse_aa<cphvb_int32,cphvb_int32, sign_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_SIGN + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int32,cphvb_int32, sign_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_SIGN + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12):
            return &traverse_aa<cphvb_uint32,cphvb_uint32, sign_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_SIGN + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint32,cphvb_uint32, sign_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_SIGN + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12):
            return &traverse_aa<cphvb_int64,cphvb_int64, sign_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_SIGN + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int64,cphvb_int64, sign_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_SIGN + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12):
            return &traverse_aa<cphvb_uint64,cphvb_uint64, sign_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_SIGN + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint64,cphvb_uint64, sign_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_SIGN + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, sign_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_SIGN + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, sign_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_SIGN + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, sign_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_SIGN + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, sign_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, logical_or_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, logical_or_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, logical_or_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int8,cphvb_int8, logical_or_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int8,cphvb_int8, logical_or_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int8,cphvb_int8, logical_or_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint8,cphvb_uint8, logical_or_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint8,cphvb_uint8, logical_or_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint8,cphvb_uint8, logical_or_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int16,cphvb_int16, logical_or_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int16,cphvb_int16, logical_or_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int16,cphvb_int16, logical_or_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint16,cphvb_uint16, logical_or_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint16,cphvb_uint16, logical_or_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint16,cphvb_uint16, logical_or_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int32,cphvb_int32, logical_or_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int32,cphvb_int32, logical_or_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int32,cphvb_int32, logical_or_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint32,cphvb_uint32, logical_or_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint32,cphvb_uint32, logical_or_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint32,cphvb_uint32, logical_or_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int64,cphvb_int64, logical_or_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int64,cphvb_int64, logical_or_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int64,cphvb_int64, logical_or_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint64,cphvb_uint64, logical_or_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint64,cphvb_uint64, logical_or_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint64,cphvb_uint64, logical_or_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float32,cphvb_float32, logical_or_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float32,cphvb_float32, logical_or_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float32,cphvb_float32, logical_or_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float64,cphvb_float64, logical_or_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float64,cphvb_float64, logical_or_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGICAL_OR + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float64,cphvb_float64, logical_or_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, minimum_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, minimum_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, minimum_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, minimum_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, minimum_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, minimum_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, minimum_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, minimum_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, minimum_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, minimum_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, minimum_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, minimum_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, minimum_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, minimum_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, minimum_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, minimum_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, minimum_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, minimum_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, minimum_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, minimum_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, minimum_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, minimum_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, minimum_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, minimum_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, minimum_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, minimum_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, minimum_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, minimum_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, minimum_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, minimum_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, minimum_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, minimum_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_MINIMUM + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, minimum_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, logical_and_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, logical_and_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, logical_and_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int8,cphvb_int8, logical_and_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int8,cphvb_int8, logical_and_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int8,cphvb_int8, logical_and_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint8,cphvb_uint8, logical_and_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint8,cphvb_uint8, logical_and_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint8,cphvb_uint8, logical_and_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int16,cphvb_int16, logical_and_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int16,cphvb_int16, logical_and_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int16,cphvb_int16, logical_and_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint16,cphvb_uint16, logical_and_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint16,cphvb_uint16, logical_and_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint16,cphvb_uint16, logical_and_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int32,cphvb_int32, logical_and_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int32,cphvb_int32, logical_and_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int32,cphvb_int32, logical_and_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint32,cphvb_uint32, logical_and_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint32,cphvb_uint32, logical_and_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint32,cphvb_uint32, logical_and_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int64,cphvb_int64, logical_and_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int64,cphvb_int64, logical_and_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int64,cphvb_int64, logical_and_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint64,cphvb_uint64, logical_and_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint64,cphvb_uint64, logical_and_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint64,cphvb_uint64, logical_and_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float32,cphvb_float32, logical_and_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float32,cphvb_float32, logical_and_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float32,cphvb_float32, logical_and_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float64,cphvb_float64, logical_and_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float64,cphvb_float64, logical_and_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGICAL_AND + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float64,cphvb_float64, logical_and_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOG2 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, log2_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOG2 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, log2_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOG2 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, log2_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOG2 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, log2_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_TAN + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, tan_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_TAN + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, tan_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_TAN + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, tan_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_TAN + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, tan_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12):
            return &traverse_aa<cphvb_bool,cphvb_bool, absolute_functor<cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_bool, absolute_functor<cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12):
            return &traverse_aa<cphvb_int8,cphvb_int8, absolute_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int8,cphvb_int8, absolute_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12):
            return &traverse_aa<cphvb_uint8,cphvb_uint8, absolute_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint8,cphvb_uint8, absolute_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12):
            return &traverse_aa<cphvb_int16,cphvb_int16, absolute_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int16,cphvb_int16, absolute_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12):
            return &traverse_aa<cphvb_uint16,cphvb_uint16, absolute_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint16,cphvb_uint16, absolute_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12):
            return &traverse_aa<cphvb_int32,cphvb_int32, absolute_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int32,cphvb_int32, absolute_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12):
            return &traverse_aa<cphvb_uint32,cphvb_uint32, absolute_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint32,cphvb_uint32, absolute_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12):
            return &traverse_aa<cphvb_int64,cphvb_int64, absolute_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int64,cphvb_int64, absolute_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12):
            return &traverse_aa<cphvb_uint64,cphvb_uint64, absolute_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint64,cphvb_uint64, absolute_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, absolute_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, absolute_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, absolute_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ABSOLUTE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, absolute_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, logical_xor_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, logical_xor_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, logical_xor_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int8,cphvb_int8, logical_xor_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int8,cphvb_int8, logical_xor_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int8,cphvb_int8, logical_xor_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint8,cphvb_uint8, logical_xor_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint8,cphvb_uint8, logical_xor_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint8,cphvb_uint8, logical_xor_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int16,cphvb_int16, logical_xor_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int16,cphvb_int16, logical_xor_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int16,cphvb_int16, logical_xor_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint16,cphvb_uint16, logical_xor_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint16,cphvb_uint16, logical_xor_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint16,cphvb_uint16, logical_xor_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int32,cphvb_int32, logical_xor_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int32,cphvb_int32, logical_xor_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int32,cphvb_int32, logical_xor_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint32,cphvb_uint32, logical_xor_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint32,cphvb_uint32, logical_xor_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint32,cphvb_uint32, logical_xor_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int64,cphvb_int64, logical_xor_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int64,cphvb_int64, logical_xor_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int64,cphvb_int64, logical_xor_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint64,cphvb_uint64, logical_xor_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint64,cphvb_uint64, logical_xor_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint64,cphvb_uint64, logical_xor_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float32,cphvb_float32, logical_xor_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float32,cphvb_float32, logical_xor_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float32,cphvb_float32, logical_xor_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float64,cphvb_float64, logical_xor_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float64,cphvb_float64, logical_xor_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGICAL_XOR + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float64,cphvb_float64, logical_xor_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, remainder_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, remainder_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, remainder_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, remainder_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, remainder_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, remainder_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, remainder_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, remainder_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, remainder_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, remainder_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, remainder_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, remainder_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, remainder_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, remainder_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, remainder_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, remainder_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, remainder_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, remainder_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, remainder_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, remainder_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, remainder_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, remainder_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, remainder_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, remainder_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, remainder_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, remainder_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, remainder_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, remainder_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, remainder_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_REMAINDER + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, remainder_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOG + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, log_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOG + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, log_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOG + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, log_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOG + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, log_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_FLOOR + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, floor_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_FLOOR + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, floor_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_FLOOR + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, floor_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_FLOOR + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, floor_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_EXP2 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, exp2_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_EXP2 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, exp2_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_EXP2 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, exp2_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_EXP2 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, exp2_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_INVERT + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12):
            return &traverse_aa<cphvb_bool,cphvb_bool, invert_functor<cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_INVERT + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_bool, invert_functor<cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_INVERT + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12):
            return &traverse_aa<cphvb_int8,cphvb_int8, invert_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_INVERT + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int8,cphvb_int8, invert_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_INVERT + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12):
            return &traverse_aa<cphvb_uint8,cphvb_uint8, invert_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_INVERT + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint8,cphvb_uint8, invert_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_INVERT + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12):
            return &traverse_aa<cphvb_int16,cphvb_int16, invert_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_INVERT + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int16,cphvb_int16, invert_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_INVERT + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12):
            return &traverse_aa<cphvb_uint16,cphvb_uint16, invert_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_INVERT + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint16,cphvb_uint16, invert_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_INVERT + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12):
            return &traverse_aa<cphvb_int32,cphvb_int32, invert_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_INVERT + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int32,cphvb_int32, invert_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_INVERT + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12):
            return &traverse_aa<cphvb_uint32,cphvb_uint32, invert_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_INVERT + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint32,cphvb_uint32, invert_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_INVERT + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12):
            return &traverse_aa<cphvb_int64,cphvb_int64, invert_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_INVERT + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int64,cphvb_int64, invert_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_INVERT + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12):
            return &traverse_aa<cphvb_uint64,cphvb_uint64, invert_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_INVERT + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint64,cphvb_uint64, invert_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_SIGNBIT + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_bool,cphvb_float32, signbit_functor<cphvb_bool,cphvb_float32> >;
            break;
        case CPHVB_SIGNBIT + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_float32, signbit_functor<cphvb_bool,cphvb_float32> >;
            break;
        case CPHVB_SIGNBIT + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_bool,cphvb_float64, signbit_functor<cphvb_bool,cphvb_float64> >;
            break;
        case CPHVB_SIGNBIT + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_float64, signbit_functor<cphvb_bool,cphvb_float64> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12):
            return &traverse_aa<cphvb_bool,cphvb_bool, negative_functor<cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_bool, negative_functor<cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12):
            return &traverse_aa<cphvb_int8,cphvb_int8, negative_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int8,cphvb_int8, negative_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12):
            return &traverse_aa<cphvb_uint8,cphvb_uint8, negative_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint8,cphvb_uint8, negative_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12):
            return &traverse_aa<cphvb_int16,cphvb_int16, negative_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int16,cphvb_int16, negative_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12):
            return &traverse_aa<cphvb_uint16,cphvb_uint16, negative_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint16,cphvb_uint16, negative_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12):
            return &traverse_aa<cphvb_int32,cphvb_int32, negative_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int32,cphvb_int32, negative_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12):
            return &traverse_aa<cphvb_uint32,cphvb_uint32, negative_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint32,cphvb_uint32, negative_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12):
            return &traverse_aa<cphvb_int64,cphvb_int64, negative_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int64,cphvb_int64, negative_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12):
            return &traverse_aa<cphvb_uint64,cphvb_uint64, negative_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint64,cphvb_uint64, negative_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, negative_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, negative_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, negative_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_NEGATIVE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, negative_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_SQRT + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, sqrt_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_SQRT + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, sqrt_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_SQRT + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, sqrt_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_SQRT + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, sqrt_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ARCTAN + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, arctan_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCTAN + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, arctan_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCTAN + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, arctan_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ARCTAN + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, arctan_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ADD + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, add_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_ADD + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, add_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_ADD + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, add_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_ADD + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, add_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_ADD + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, add_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_ADD + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, add_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_ADD + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, add_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_ADD + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, add_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_ADD + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, add_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_ADD + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, add_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_ADD + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, add_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_ADD + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, add_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_ADD + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, add_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_ADD + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, add_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_ADD + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, add_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_ADD + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, add_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_ADD + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, add_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_ADD + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, add_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_ADD + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, add_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_ADD + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, add_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_ADD + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, add_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_ADD + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, add_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_ADD + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, add_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_ADD + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, add_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_ADD + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, add_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_ADD + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, add_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_ADD + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, add_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_ADD + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, add_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ADD + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, add_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ADD + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, add_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ADD + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, add_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ADD + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, add_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ADD + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, add_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, right_shift_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, right_shift_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, right_shift_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, right_shift_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, right_shift_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, right_shift_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, right_shift_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, right_shift_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, right_shift_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, right_shift_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, right_shift_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, right_shift_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, right_shift_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, right_shift_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, right_shift_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, right_shift_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, right_shift_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, right_shift_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, right_shift_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, right_shift_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, right_shift_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, right_shift_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, right_shift_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_RIGHT_SHIFT + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, right_shift_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_ARCTANH + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, arctanh_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCTANH + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, arctanh_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCTANH + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, arctanh_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ARCTANH + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, arctanh_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, floor_divide_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, floor_divide_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, floor_divide_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, floor_divide_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, floor_divide_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, floor_divide_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, floor_divide_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, floor_divide_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, floor_divide_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, floor_divide_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, floor_divide_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, floor_divide_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, floor_divide_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, floor_divide_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, floor_divide_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, floor_divide_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, floor_divide_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, floor_divide_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, floor_divide_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, floor_divide_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, floor_divide_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, floor_divide_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, floor_divide_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, floor_divide_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, floor_divide_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, floor_divide_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, floor_divide_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, floor_divide_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, floor_divide_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_FLOOR_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, floor_divide_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOG10 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, log10_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOG10 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, log10_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOG10 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, log10_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOG10 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, log10_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_SIN + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, sin_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_SIN + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, sin_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_SIN + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, sin_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_SIN + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, sin_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, maximum_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, maximum_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, maximum_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, maximum_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, maximum_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, maximum_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, maximum_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, maximum_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, maximum_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, maximum_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, maximum_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, maximum_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, maximum_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, maximum_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, maximum_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, maximum_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, maximum_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, maximum_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, maximum_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, maximum_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, maximum_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, maximum_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, maximum_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, maximum_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, maximum_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, maximum_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, maximum_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, maximum_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, maximum_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, maximum_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, maximum_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, maximum_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_MAXIMUM + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, maximum_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, bitwise_xor_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, bitwise_xor_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, bitwise_xor_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, bitwise_xor_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, bitwise_xor_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, bitwise_xor_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, bitwise_xor_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, bitwise_xor_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, bitwise_xor_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, bitwise_xor_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, bitwise_xor_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, bitwise_xor_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, bitwise_xor_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, bitwise_xor_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, bitwise_xor_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, bitwise_xor_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, bitwise_xor_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, bitwise_xor_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, bitwise_xor_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, bitwise_xor_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, bitwise_xor_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, bitwise_xor_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, bitwise_xor_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, bitwise_xor_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, bitwise_xor_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, bitwise_xor_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_BITWISE_XOR + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, bitwise_xor_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_TANH + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, tanh_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_TANH + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, tanh_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_TANH + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, tanh_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_TANH + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, tanh_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGADDEXP2 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, logaddexp2_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGADDEXP2 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, logaddexp2_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGADDEXP2 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, logaddexp2_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGADDEXP2 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, logaddexp2_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGADDEXP2 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, logaddexp2_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGADDEXP2 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, logaddexp2_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, greater_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, greater_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, greater_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int8,cphvb_int8, greater_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int8,cphvb_int8, greater_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int8,cphvb_int8, greater_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint8,cphvb_uint8, greater_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint8,cphvb_uint8, greater_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint8,cphvb_uint8, greater_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int16,cphvb_int16, greater_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int16,cphvb_int16, greater_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int16,cphvb_int16, greater_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint16,cphvb_uint16, greater_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint16,cphvb_uint16, greater_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint16,cphvb_uint16, greater_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int32,cphvb_int32, greater_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int32,cphvb_int32, greater_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int32,cphvb_int32, greater_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint32,cphvb_uint32, greater_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint32,cphvb_uint32, greater_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint32,cphvb_uint32, greater_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int64,cphvb_int64, greater_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int64,cphvb_int64, greater_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int64,cphvb_int64, greater_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint64,cphvb_uint64, greater_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint64,cphvb_uint64, greater_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint64,cphvb_uint64, greater_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float32,cphvb_float32, greater_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float32,cphvb_float32, greater_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float32,cphvb_float32, greater_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float64,cphvb_float64, greater_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float64,cphvb_float64, greater_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_GREATER + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float64,cphvb_float64, greater_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_POWER + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, power_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_POWER + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, power_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_POWER + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, power_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_POWER + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, power_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_POWER + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, power_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_POWER + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, power_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_POWER + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, power_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_POWER + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, power_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_POWER + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, power_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_POWER + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, power_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_POWER + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, power_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_POWER + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, power_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_POWER + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, power_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_POWER + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, power_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_POWER + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, power_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_POWER + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, power_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_POWER + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, power_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_POWER + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, power_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_POWER + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, power_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_POWER + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, power_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_POWER + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, power_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_POWER + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, power_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_POWER + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, power_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_POWER + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, power_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_POWER + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, power_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_POWER + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, power_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_POWER + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, power_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_POWER + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, power_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_POWER + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, power_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_POWER + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, power_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_EXPM1 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, expm1_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_EXPM1 + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, expm1_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_EXPM1 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, expm1_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_EXPM1 + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, expm1_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_DEG2RAD + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, deg2rad_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_DEG2RAD + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, deg2rad_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_DEG2RAD + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, deg2rad_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_DEG2RAD + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, deg2rad_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ARCSINH + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, arcsinh_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCSINH + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, arcsinh_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCSINH + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, arcsinh_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ARCSINH + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, arcsinh_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_SINH + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, sinh_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_SINH + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, sinh_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_SINH + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, sinh_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_SINH + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, sinh_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, multiply_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, multiply_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, multiply_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, multiply_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, multiply_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, multiply_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, multiply_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, multiply_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, multiply_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, multiply_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, multiply_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, multiply_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, multiply_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, multiply_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, multiply_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, multiply_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, multiply_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, multiply_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, multiply_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, multiply_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, multiply_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, multiply_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, multiply_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, multiply_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, multiply_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, multiply_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, multiply_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, multiply_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, multiply_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, multiply_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, multiply_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, multiply_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_MULTIPLY + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, multiply_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_COSH + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, cosh_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_COSH + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, cosh_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_COSH + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, cosh_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_COSH + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, cosh_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, subtract_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, subtract_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, subtract_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, subtract_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, subtract_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, subtract_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, subtract_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, subtract_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, subtract_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, subtract_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, subtract_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, subtract_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, subtract_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, subtract_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, subtract_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, subtract_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, subtract_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, subtract_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, subtract_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, subtract_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, subtract_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, subtract_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, subtract_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, subtract_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, subtract_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, subtract_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, subtract_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, subtract_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, subtract_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, subtract_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, subtract_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, subtract_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_SUBTRACT + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, subtract_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGADDEXP + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, logaddexp_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGADDEXP + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, logaddexp_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGADDEXP + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, logaddexp_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOGADDEXP + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, logaddexp_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGADDEXP + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, logaddexp_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGADDEXP + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, logaddexp_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_TRUNC + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, trunc_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_TRUNC + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, trunc_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_TRUNC + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, trunc_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_TRUNC + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, trunc_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ARCSIN + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, arcsin_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCSIN + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, arcsin_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCSIN + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, arcsin_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ARCSIN + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, arcsin_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_COS + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, cos_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_COS + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, cos_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_COS + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, cos_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_COS + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, cos_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, not_equal_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, not_equal_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, not_equal_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int8,cphvb_int8, not_equal_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int8,cphvb_int8, not_equal_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int8,cphvb_int8, not_equal_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint8,cphvb_uint8, not_equal_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint8,cphvb_uint8, not_equal_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint8,cphvb_uint8, not_equal_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int16,cphvb_int16, not_equal_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int16,cphvb_int16, not_equal_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int16,cphvb_int16, not_equal_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint16,cphvb_uint16, not_equal_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint16,cphvb_uint16, not_equal_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint16,cphvb_uint16, not_equal_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int32,cphvb_int32, not_equal_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int32,cphvb_int32, not_equal_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int32,cphvb_int32, not_equal_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint32,cphvb_uint32, not_equal_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint32,cphvb_uint32, not_equal_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint32,cphvb_uint32, not_equal_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int64,cphvb_int64, not_equal_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int64,cphvb_int64, not_equal_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int64,cphvb_int64, not_equal_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint64,cphvb_uint64, not_equal_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint64,cphvb_uint64, not_equal_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint64,cphvb_uint64, not_equal_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float32,cphvb_float32, not_equal_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float32,cphvb_float32, not_equal_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float32,cphvb_float32, not_equal_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float64,cphvb_float64, not_equal_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float64,cphvb_float64, not_equal_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_NOT_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float64,cphvb_float64, not_equal_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12):
            return &traverse_aa<cphvb_bool,cphvb_bool, logical_not_functor<cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_bool, logical_not_functor<cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12):
            return &traverse_aa<cphvb_bool,cphvb_int8, logical_not_functor<cphvb_bool,cphvb_int8> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_int8, logical_not_functor<cphvb_bool,cphvb_int8> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12):
            return &traverse_aa<cphvb_bool,cphvb_uint8, logical_not_functor<cphvb_bool,cphvb_uint8> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_uint8, logical_not_functor<cphvb_bool,cphvb_uint8> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12):
            return &traverse_aa<cphvb_bool,cphvb_int16, logical_not_functor<cphvb_bool,cphvb_int16> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_int16, logical_not_functor<cphvb_bool,cphvb_int16> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12):
            return &traverse_aa<cphvb_bool,cphvb_uint16, logical_not_functor<cphvb_bool,cphvb_uint16> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_uint16, logical_not_functor<cphvb_bool,cphvb_uint16> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12):
            return &traverse_aa<cphvb_bool,cphvb_int32, logical_not_functor<cphvb_bool,cphvb_int32> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_int32, logical_not_functor<cphvb_bool,cphvb_int32> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12):
            return &traverse_aa<cphvb_bool,cphvb_uint32, logical_not_functor<cphvb_bool,cphvb_uint32> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_uint32, logical_not_functor<cphvb_bool,cphvb_uint32> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12):
            return &traverse_aa<cphvb_bool,cphvb_int64, logical_not_functor<cphvb_bool,cphvb_int64> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_int64, logical_not_functor<cphvb_bool,cphvb_int64> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12):
            return &traverse_aa<cphvb_bool,cphvb_uint64, logical_not_functor<cphvb_bool,cphvb_uint64> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_uint64, logical_not_functor<cphvb_bool,cphvb_uint64> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_bool,cphvb_float32, logical_not_functor<cphvb_bool,cphvb_float32> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_float32, logical_not_functor<cphvb_bool,cphvb_float32> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_bool,cphvb_float64, logical_not_functor<cphvb_bool,cphvb_float64> >;
            break;
        case CPHVB_LOGICAL_NOT + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_float64, logical_not_functor<cphvb_bool,cphvb_float64> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, greater_equal_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, greater_equal_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, greater_equal_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int8,cphvb_int8, greater_equal_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int8,cphvb_int8, greater_equal_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int8,cphvb_int8, greater_equal_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint8,cphvb_uint8, greater_equal_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint8,cphvb_uint8, greater_equal_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint8,cphvb_uint8, greater_equal_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int16,cphvb_int16, greater_equal_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int16,cphvb_int16, greater_equal_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int16,cphvb_int16, greater_equal_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint16,cphvb_uint16, greater_equal_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint16,cphvb_uint16, greater_equal_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint16,cphvb_uint16, greater_equal_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int32,cphvb_int32, greater_equal_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int32,cphvb_int32, greater_equal_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int32,cphvb_int32, greater_equal_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint32,cphvb_uint32, greater_equal_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint32,cphvb_uint32, greater_equal_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint32,cphvb_uint32, greater_equal_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int64,cphvb_int64, greater_equal_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int64,cphvb_int64, greater_equal_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int64,cphvb_int64, greater_equal_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint64,cphvb_uint64, greater_equal_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint64,cphvb_uint64, greater_equal_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint64,cphvb_uint64, greater_equal_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float32,cphvb_float32, greater_equal_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float32,cphvb_float32, greater_equal_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float32,cphvb_float32, greater_equal_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float64,cphvb_float64, greater_equal_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float64,cphvb_float64, greater_equal_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_GREATER_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float64,cphvb_float64, greater_equal_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12):
            return &traverse_aa<cphvb_int8,cphvb_int8, reciprocal_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int8,cphvb_int8, reciprocal_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12):
            return &traverse_aa<cphvb_uint8,cphvb_uint8, reciprocal_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint8,cphvb_uint8, reciprocal_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12):
            return &traverse_aa<cphvb_int16,cphvb_int16, reciprocal_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int16,cphvb_int16, reciprocal_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12):
            return &traverse_aa<cphvb_uint16,cphvb_uint16, reciprocal_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint16,cphvb_uint16, reciprocal_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12):
            return &traverse_aa<cphvb_int32,cphvb_int32, reciprocal_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int32,cphvb_int32, reciprocal_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12):
            return &traverse_aa<cphvb_uint32,cphvb_uint32, reciprocal_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint32,cphvb_uint32, reciprocal_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12):
            return &traverse_aa<cphvb_int64,cphvb_int64, reciprocal_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int64,cphvb_int64, reciprocal_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12):
            return &traverse_aa<cphvb_uint64,cphvb_uint64, reciprocal_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint64,cphvb_uint64, reciprocal_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, reciprocal_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, reciprocal_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, reciprocal_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_RECIPROCAL + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, reciprocal_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, bitwise_or_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, bitwise_or_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, bitwise_or_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, bitwise_or_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, bitwise_or_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, bitwise_or_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, bitwise_or_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, bitwise_or_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, bitwise_or_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, bitwise_or_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, bitwise_or_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, bitwise_or_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, bitwise_or_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, bitwise_or_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, bitwise_or_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, bitwise_or_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, bitwise_or_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, bitwise_or_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, bitwise_or_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, bitwise_or_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, bitwise_or_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, bitwise_or_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, bitwise_or_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, bitwise_or_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, bitwise_or_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, bitwise_or_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_BITWISE_OR + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, bitwise_or_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LOG1P + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, log1p_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOG1P + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, log1p_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LOG1P + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, log1p_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LOG1P + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, log1p_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_CEIL + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, ceil_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_CEIL + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, ceil_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_CEIL + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, ceil_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_CEIL + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, ceil_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_int8,cphvb_int8, true_divide_functor<cphvb_float64,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_int8,cphvb_int8, true_divide_functor<cphvb_float64,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_int8,cphvb_int8, true_divide_functor<cphvb_float64,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_uint8,cphvb_uint8, true_divide_functor<cphvb_float64,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_uint8,cphvb_uint8, true_divide_functor<cphvb_float64,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_uint8,cphvb_uint8, true_divide_functor<cphvb_float64,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_int16,cphvb_int16, true_divide_functor<cphvb_float64,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_int16,cphvb_int16, true_divide_functor<cphvb_float64,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_int16,cphvb_int16, true_divide_functor<cphvb_float64,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_uint16,cphvb_uint16, true_divide_functor<cphvb_float64,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_uint16,cphvb_uint16, true_divide_functor<cphvb_float64,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_uint16,cphvb_uint16, true_divide_functor<cphvb_float64,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_int32,cphvb_int32, true_divide_functor<cphvb_float64,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_int32,cphvb_int32, true_divide_functor<cphvb_float64,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_int32,cphvb_int32, true_divide_functor<cphvb_float64,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_uint32,cphvb_uint32, true_divide_functor<cphvb_float64,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_uint32,cphvb_uint32, true_divide_functor<cphvb_float64,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_uint32,cphvb_uint32, true_divide_functor<cphvb_float64,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_int64,cphvb_int64, true_divide_functor<cphvb_float64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_int64,cphvb_int64, true_divide_functor<cphvb_float64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_int64,cphvb_int64, true_divide_functor<cphvb_float64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_uint64,cphvb_uint64, true_divide_functor<cphvb_float64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_uint64,cphvb_uint64, true_divide_functor<cphvb_float64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_uint64,cphvb_uint64, true_divide_functor<cphvb_float64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, true_divide_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, true_divide_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, true_divide_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, true_divide_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, true_divide_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_TRUE_DIVIDE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, true_divide_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, left_shift_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, left_shift_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, left_shift_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, left_shift_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, left_shift_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, left_shift_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, left_shift_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, left_shift_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, left_shift_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, left_shift_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, left_shift_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, left_shift_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, left_shift_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, left_shift_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, left_shift_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, left_shift_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, left_shift_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, left_shift_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, left_shift_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, left_shift_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, left_shift_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, left_shift_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, left_shift_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LEFT_SHIFT + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, left_shift_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, equal_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, equal_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, equal_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int8,cphvb_int8, equal_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int8,cphvb_int8, equal_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int8,cphvb_int8, equal_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint8,cphvb_uint8, equal_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint8,cphvb_uint8, equal_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint8,cphvb_uint8, equal_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int16,cphvb_int16, equal_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int16,cphvb_int16, equal_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int16,cphvb_int16, equal_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint16,cphvb_uint16, equal_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint16,cphvb_uint16, equal_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint16,cphvb_uint16, equal_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int32,cphvb_int32, equal_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int32,cphvb_int32, equal_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int32,cphvb_int32, equal_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint32,cphvb_uint32, equal_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint32,cphvb_uint32, equal_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint32,cphvb_uint32, equal_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int64,cphvb_int64, equal_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int64,cphvb_int64, equal_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int64,cphvb_int64, equal_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint64,cphvb_uint64, equal_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint64,cphvb_uint64, equal_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint64,cphvb_uint64, equal_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float32,cphvb_float32, equal_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float32,cphvb_float32, equal_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float32,cphvb_float32, equal_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float64,cphvb_float64, equal_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float64,cphvb_float64, equal_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float64,cphvb_float64, equal_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_HYPOT + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, hypot_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_HYPOT + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, hypot_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_HYPOT + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, hypot_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_HYPOT + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, hypot_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_HYPOT + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, hypot_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_HYPOT + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, hypot_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_FMOD + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, fmod_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_FMOD + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, fmod_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_FMOD + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, fmod_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_FMOD + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, fmod_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_FMOD + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, fmod_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_FMOD + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, fmod_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_FMOD + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, fmod_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_FMOD + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, fmod_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_FMOD + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, fmod_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_FMOD + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, fmod_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_FMOD + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, fmod_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_FMOD + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, fmod_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_FMOD + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, fmod_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_FMOD + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, fmod_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_FMOD + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, fmod_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_FMOD + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, fmod_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_FMOD + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, fmod_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_FMOD + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, fmod_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_FMOD + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, fmod_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_FMOD + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, fmod_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_FMOD + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, fmod_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_FMOD + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, fmod_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_FMOD + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, fmod_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_FMOD + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, fmod_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_FMOD + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_float32,cphvb_float32,cphvb_float32, fmod_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_FMOD + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float32,cphvb_float32,cphvb_float32, fmod_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_FMOD + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float32,cphvb_float32,cphvb_float32, fmod_functor<cphvb_float32,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_FMOD + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_float64,cphvb_float64,cphvb_float64, fmod_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_FMOD + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_float64,cphvb_float64,cphvb_float64, fmod_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_FMOD + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_float64,cphvb_float64,cphvb_float64, fmod_functor<cphvb_float64,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ARCCOS + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, arccos_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCCOS + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, arccos_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCCOS + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, arccos_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ARCCOS + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, arccos_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, less_equal_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, less_equal_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, less_equal_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int8,cphvb_int8, less_equal_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int8,cphvb_int8, less_equal_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int8,cphvb_int8, less_equal_functor<cphvb_bool,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint8,cphvb_uint8, less_equal_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint8,cphvb_uint8, less_equal_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint8,cphvb_uint8, less_equal_functor<cphvb_bool,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int16,cphvb_int16, less_equal_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int16,cphvb_int16, less_equal_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int16,cphvb_int16, less_equal_functor<cphvb_bool,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint16,cphvb_uint16, less_equal_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint16,cphvb_uint16, less_equal_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint16,cphvb_uint16, less_equal_functor<cphvb_bool,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int32,cphvb_int32, less_equal_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int32,cphvb_int32, less_equal_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int32,cphvb_int32, less_equal_functor<cphvb_bool,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint32,cphvb_uint32, less_equal_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint32,cphvb_uint32, less_equal_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint32,cphvb_uint32, less_equal_functor<cphvb_bool,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_int64,cphvb_int64, less_equal_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_int64,cphvb_int64, less_equal_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_int64,cphvb_int64, less_equal_functor<cphvb_bool,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_uint64,cphvb_uint64, less_equal_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_uint64,cphvb_uint64, less_equal_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_uint64,cphvb_uint64, less_equal_functor<cphvb_bool,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float32,cphvb_float32, less_equal_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float32,cphvb_float32, less_equal_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT32 <<12) + (CPHVB_FLOAT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float32,cphvb_float32, less_equal_functor<cphvb_bool,cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16):
            return &traverse_aaa<cphvb_bool,cphvb_float64,cphvb_float64, less_equal_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_float64,cphvb_float64, less_equal_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_LESS_EQUAL + (CPHVB_BOOL << 8) +(CPHVB_FLOAT64 <<12) + (CPHVB_FLOAT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_float64,cphvb_float64, less_equal_functor<cphvb_bool,cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16):
            return &traverse_aaa<cphvb_bool,cphvb_bool,cphvb_bool, bitwise_and_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 18):
            return &traverse_aac<cphvb_bool,cphvb_bool,cphvb_bool, bitwise_and_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (CPHVB_BOOL <<16) + (1 << 17):
            return &traverse_aca<cphvb_bool,cphvb_bool,cphvb_bool, bitwise_and_functor<cphvb_bool,cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16):
            return &traverse_aaa<cphvb_int8,cphvb_int8,cphvb_int8, bitwise_and_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int8,cphvb_int8,cphvb_int8, bitwise_and_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (CPHVB_INT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int8,cphvb_int8,cphvb_int8, bitwise_and_functor<cphvb_int8,cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16):
            return &traverse_aaa<cphvb_uint8,cphvb_uint8,cphvb_uint8, bitwise_and_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint8,cphvb_uint8,cphvb_uint8, bitwise_and_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (CPHVB_UINT8 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint8,cphvb_uint8,cphvb_uint8, bitwise_and_functor<cphvb_uint8,cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16):
            return &traverse_aaa<cphvb_int16,cphvb_int16,cphvb_int16, bitwise_and_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int16,cphvb_int16,cphvb_int16, bitwise_and_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (CPHVB_INT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int16,cphvb_int16,cphvb_int16, bitwise_and_functor<cphvb_int16,cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16):
            return &traverse_aaa<cphvb_uint16,cphvb_uint16,cphvb_uint16, bitwise_and_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint16,cphvb_uint16,cphvb_uint16, bitwise_and_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (CPHVB_UINT16 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint16,cphvb_uint16,cphvb_uint16, bitwise_and_functor<cphvb_uint16,cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16):
            return &traverse_aaa<cphvb_int32,cphvb_int32,cphvb_int32, bitwise_and_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int32,cphvb_int32,cphvb_int32, bitwise_and_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (CPHVB_INT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int32,cphvb_int32,cphvb_int32, bitwise_and_functor<cphvb_int32,cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16):
            return &traverse_aaa<cphvb_uint32,cphvb_uint32,cphvb_uint32, bitwise_and_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint32,cphvb_uint32,cphvb_uint32, bitwise_and_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (CPHVB_UINT32 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint32,cphvb_uint32,cphvb_uint32, bitwise_and_functor<cphvb_uint32,cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16):
            return &traverse_aaa<cphvb_int64,cphvb_int64,cphvb_int64, bitwise_and_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_int64,cphvb_int64,cphvb_int64, bitwise_and_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (CPHVB_INT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_int64,cphvb_int64,cphvb_int64, bitwise_and_functor<cphvb_int64,cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16):
            return &traverse_aaa<cphvb_uint64,cphvb_uint64,cphvb_uint64, bitwise_and_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 18):
            return &traverse_aac<cphvb_uint64,cphvb_uint64,cphvb_uint64, bitwise_and_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_BITWISE_AND + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (CPHVB_UINT64 <<16) + (1 << 17):
            return &traverse_aca<cphvb_uint64,cphvb_uint64,cphvb_uint64, bitwise_and_functor<cphvb_uint64,cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_ARCCOSH + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, arccosh_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCCOSH + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, arccosh_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ARCCOSH + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, arccosh_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ARCCOSH + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, arccosh_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12):
            return &traverse_aa<cphvb_bool,cphvb_bool, ones_like_functor<cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_BOOL << 8) +(CPHVB_BOOL <<12) + (1 << 17):
            return &traverse_ac<cphvb_bool,cphvb_bool, ones_like_functor<cphvb_bool,cphvb_bool> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12):
            return &traverse_aa<cphvb_int8,cphvb_int8, ones_like_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_INT8 << 8) +(CPHVB_INT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int8,cphvb_int8, ones_like_functor<cphvb_int8,cphvb_int8> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12):
            return &traverse_aa<cphvb_uint8,cphvb_uint8, ones_like_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_UINT8 << 8) +(CPHVB_UINT8 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint8,cphvb_uint8, ones_like_functor<cphvb_uint8,cphvb_uint8> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12):
            return &traverse_aa<cphvb_int16,cphvb_int16, ones_like_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_INT16 << 8) +(CPHVB_INT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int16,cphvb_int16, ones_like_functor<cphvb_int16,cphvb_int16> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12):
            return &traverse_aa<cphvb_uint16,cphvb_uint16, ones_like_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_UINT16 << 8) +(CPHVB_UINT16 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint16,cphvb_uint16, ones_like_functor<cphvb_uint16,cphvb_uint16> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12):
            return &traverse_aa<cphvb_int32,cphvb_int32, ones_like_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_INT32 << 8) +(CPHVB_INT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int32,cphvb_int32, ones_like_functor<cphvb_int32,cphvb_int32> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12):
            return &traverse_aa<cphvb_uint32,cphvb_uint32, ones_like_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_UINT32 << 8) +(CPHVB_UINT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint32,cphvb_uint32, ones_like_functor<cphvb_uint32,cphvb_uint32> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12):
            return &traverse_aa<cphvb_int64,cphvb_int64, ones_like_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_INT64 << 8) +(CPHVB_INT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_int64,cphvb_int64, ones_like_functor<cphvb_int64,cphvb_int64> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12):
            return &traverse_aa<cphvb_uint64,cphvb_uint64, ones_like_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_UINT64 << 8) +(CPHVB_UINT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_uint64,cphvb_uint64, ones_like_functor<cphvb_uint64,cphvb_uint64> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12):
            return &traverse_aa<cphvb_float32,cphvb_float32, ones_like_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_FLOAT32 << 8) +(CPHVB_FLOAT32 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float32,cphvb_float32, ones_like_functor<cphvb_float32,cphvb_float32> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12):
            return &traverse_aa<cphvb_float64,cphvb_float64, ones_like_functor<cphvb_float64,cphvb_float64> >;
            break;
        case CPHVB_ONES_LIKE + (CPHVB_FLOAT64 << 8) +(CPHVB_FLOAT64 <<12) + (1 << 17):
            return &traverse_ac<cphvb_float64,cphvb_float64, ones_like_functor<cphvb_float64,cphvb_float64> >;
            break;

        default:
            return NULL;

    }

}
