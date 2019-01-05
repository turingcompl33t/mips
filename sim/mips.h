/*
 * mips.h
 * MIPS ISA-specific constant values. 
 *
 * Kyle Dotterrer
 * January, 2019 
 */

#ifndef __MIPS_H
#define __MIPS_H

/* ----------------------------------------------------------------------------
	Register Designations
*/

#define REG_LINK 31

/* ----------------------------------------------------------------------------
	Instruction Opcodes 
*/

#define OPCODE_J   2
#define OPCODE_JAL 3
#define OPCODE_BEQ 4
#define OPCODE_BNE 5
#define OPCODE_BLEZ 6 
#define OPCODE_BGTZ 7

#define OPCODE_LW 35
#define OPCODE_ADDIU 9 


/* ----------------------------------------------------------------------------
	Instruction - Bit Masking Constants
*/

#define MASK_PC_HIGH 0xF0000000
 
#define MASK_OPCODE 0xFC000000 

#define MASK_I_RS         0x03E00000
#define MASK_I_RT         0x001F0000
#define MASK_I_IMMEDIATE  0x0000FFFF

#define MASK_J_TARGET 0x03FFFFFF

/* ----------------------------------------------------------------------------
	Instruction - Bit Shift Constants
*/

#define SHIFT_OPCODE 26

#define SHIFT_I_RS        21
#define SHIFT_I_RT        16
#define SHIFT_I_IMMEDIATE 0

#define SHIFT_J_TARGET 0 

#endif // __MIPS_H
