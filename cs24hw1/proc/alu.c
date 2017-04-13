/*! \file
 *
 * This file contains definitions for an Arithmetic/Logic Unit of an
 * emulated processor.
 */


#include <stdio.h>
#include <stdlib.h>   /* malloc(), free() */
#include <string.h>   /* memset() */

#include "alu.h"
#include "instruction.h"


/*!
 * This function dynamically allocates and initializes the state for a new ALU
 * instance.  If allocation fails, the program is terminated.
 */
ALU * build_alu() {
    /* Try to allocate the ALU struct.  If this fails, report error then exit. */
    ALU *alu = malloc(sizeof(ALU));
    if (!alu) {
        fprintf(stderr, "Out of memory building an ALU!\n");
        exit(11);
    }

    /* Initialize all values in the ALU struct to 0. */
    memset(alu, 0, sizeof(ALU));
    return alu;
}


/*! This function frees the dynamically allocated ALU instance. */
void free_alu(ALU *alu) {
    free(alu);
}


/*!
 * This function implements the logic of the ALU.  It reads the inputs and
 * opcode, then sets the output accordingly.  Note that if the ALU does not
 * recognize the opcode, it should simply produce a zero result.
 */
void alu_eval(ALU *alu) {
    uint32_t A, B, aluop;
    uint32_t result;

    A = pin_read(alu->in1);
    B = pin_read(alu->in2);
    aluop = pin_read(alu->op);

    result = 0;

    /*
    *ALU Operations
    *Updates result variable.
    */
    switch(aluop){
        /* Simple addition of two values A + B*/
        case ALUOP_ADD:
            result = A+B;
            break;
        /* Inverts all bits of binary representation of A*/
        case ALUOP_INV:
            result = ~A;
            break;
        /* Simple subtraction of B from A */
        case ALUOP_SUB:
            result = A-B;
            break;
        /* Bitwise Exclusive OR of A and B.*/
        case ALUOP_XOR:
            result = A^B;
            break;
        /* Bitwise OR: A OR B*/
        case ALUOP_OR:
            result = A | B;
            break;
        /* Adds 1 to the value at A */
        case ALUOP_INCR:
            result = A+1;
            break;
        /* Bitwise AND of A and B. */
        case ALUOP_AND:
            result = A&B;
            break;
        /*Arithmetic shift right of A. Takes into account sign of A. */
        case ALUOP_SRA:
            result = (int32_t)A>>1;
            break;
        /*Logical shift right of A. Does not take sign of A into account. */
        case ALUOP_SRL:
            result = A>>1;
            break;
        /* Arithmetic shift left of A*/
        case ALUOP_SLA:
            result = (int32_t)A<<1;
            break;
        /* Logical shift left of A*/
        case ALUOP_SLL:
            result = A<<1;
            break;
        /* Return 0 if none of these opcodes are recognized. */
        default:
            result = 0;
            break;
    }

    pin_set(alu->out, result);
}

