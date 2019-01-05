/*
 * mips.h
 * MIPS ISA-specific constant values. 
 *
 * Kyle Dotterrer
 * January, 2019 
 */

/* ----------------------------------------------------------------------------
	Instruction - Bit Masking Constants
*/
 
#define MASK_OPCODE 0xFC000000 

#define MASK_I_RS         0x03E00000
#define MASK_I_RT         0x001F0000
#define MASK_I_IMMEDIATE  0x0000FFFF

/* ----------------------------------------------------------------------------
	Instruction - Bit Shift Constants
*/

#define SHIFT_OPCODE 26

#define SHIFT_I_RS        21
#define SHIFT_I_RT        16
#define SHIFT_I_IMMEDIATE 0
