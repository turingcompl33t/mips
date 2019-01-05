/*
 * decode.c
 *
 * Kyle Dotterrer
 * January, 2019 
 */

#include <stdint.h>
#include <stdlib.h>

#include "mips.h"

/* ----------------------------------------------------------------------------
	Opcode 
*/

int decode_opcode(uint32_t instr) {
	// opcode is always top 6 bits of instr 
	return (int) ((instr & MASK_OPCODE) >> SHIFT_OPCODE); 
}

/* ----------------------------------------------------------------------------
	I-Type Instructions 
*/

int decode_i_rs(uint32_t instr) {
	return (int) ((instr & MASK_I_RS) >> SHIFT_I_RS);
}


int decode_i_rt(uint32_t instr) {
	return (int) ((instr & MASK_I_RT) >> SHIFT_I_RT);
}

int16_t decode_i_immediate(uint32_t instr) {
	return (int16_t) ((instr & MASK_I_IMMEDIATE) >> SHIFT_I_IMMEDIATE); 
}
