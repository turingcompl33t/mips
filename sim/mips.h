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

#define OPCODE_SPECIAL 0
#define OPCODE_REGIMM 1
#define OPCODE_J   2
#define OPCODE_JAL 3
#define OPCODE_BEQ 4
#define OPCODE_BNE 5
#define OPCODE_BLEZ 6 
#define OPCODE_BGTZ 7
#define OPCODE_ADDI 8
#define OPCODE_ADDIU 9 
#define OPCODE_SLTI 10
#define OPCODE_SLTIU 11
#define OPCODE_ANDI 12
#define OPCODE_ORI 13
#define OPCODE_XORI 14
#define OPCODE_LUI 15
#define OPCODE_LB 32
#define OPCODE_LH 33
#define OPCODE_LW 35
#define OPCODE_LBU 36
#define OPCODE_LHU 37

#define OPCODE_SB 40
#define OPCODE_SH 41
#define OPCODE_SW 43

/* ----------------------------------------------------------------------------
	Instruction Function Codes  
*/

#define FUNC_SLL 0 
#define FUNC_SRL 2
#define FUNC_SRA 3
#define FUNC_SLLV 4
#define FUNC_SRLV 6
#define FUNC_SRAV 7
#define FUNC_JR 8
#define FUNC_JALR 9
#define FUNC_ADD 32
#define FUNC_ADDU 33

/* ----------------------------------------------------------------------------
	Instruction Target Codes
*/

#define TARGET_BLTZ 0
#define TARGET_BGEZ 1
#define TARGET_BLTZAL 16
#define TARGET_BGEZAL 17

/* ----------------------------------------------------------------------------
	Instruction - Bit Masking Constants
*/

#define MASK_PC_HIGH 0xF0000000
 
#define MASK_OPCODE 0xFC000000 

#define MASK_I_RS         0x03E00000
#define MASK_I_RT         0x001F0000
#define MASK_I_IMMEDIATE  0x0000FFFF

#define MASK_J_TARGET 0x03FFFFFF
#define MASK_J_FUNCT  0x0000003F

#define MASK_R_RS    0x03E00000
#define MASK_R_RT    0x001F0000
#define MASK_R_RD    0x0000F800
#define MASK_R_SHAMT 0x000007C0
#define MASK_R_FUNCT 0x0000003F

/* ----------------------------------------------------------------------------
	Instruction - Bit Shift Constants
*/

#define SHIFT_OPCODE 26

#define SHIFT_I_RS        21
#define SHIFT_I_RT        16
#define SHIFT_I_IMMEDIATE  0

#define SHIFT_J_TARGET 0 
#define SHIFT_J_FUNCT  0

#define SHIFT_R_RS    21
#define SHIFT_R_RT    16
#define SHIFT_R_RD    11
#define SHIFT_R_SHAMT  6
#define SHIFT_R_FUNCT  0

#endif // __MIPS_H
