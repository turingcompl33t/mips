/*
 * decode.h
 * Instruction decode helpers.
 *
 * Kyle Dotterrer
 * January, 2019 
 */

#ifndef __DECODE_H
#define __DECODE_H

#include <stdint.h>

/* ----------------------------------------------------------------------------
	Opcode (All Instruction Types)
*/

/*
 * decode_op
 * Decode opcode from raw instruction. 
 */
int decode_opcode(uint32_t instr);

/* ----------------------------------------------------------------------------
	I-Type Instructions 
*/

/*
 * decode_i_rs 
 * Decode source register from I-type instruction. 
 */
int decode_i_rs(uint32_t instr);

/*
 * decode_i_rt
 * Decode target register from I-type instruction. 
 */
int decode_i_rt(uint32_t instr);

/*
 * decode_i_immediate
 * Decode immediate value from I-type instruction. 
 */
int16_t decode_i_immediate(uint32_t instr);

/* ----------------------------------------------------------------------------
	J-Type Instructions 
*/

/*
 * decode_j_target
 * Decode target address from J-type instruction. 
 */
uint32_t decode_j_target(uint32_t instr);

/* ----------------------------------------------------------------------------
	R-Type Instructions 
*/

/*
 * decode_r_rs
 * Decode source register from R-type instruction. 
 */
int decode_r_rs(uint32_t instr);

/*
 * decode_r_rt
 * Decode target register from R-type instruction. 
 */
int decode_r_rt(uint32_t instr);

/*
 * decode_r_rd
 * Decode destination register from R-type instruction. 
 */
int decode_r_rd(uint32_t instr);

/*
 * decode_r_shamt
 * Decode shift amount from R-type instruction. 
 */
int decode_r_shamt(uint32_t instr);

/*
 * decode_r_funct
 * Decode function code from R-type instruction. 
 */
int decode_r_funct(uint32_t instr);

#endif // __DECODE_H
