/*
 * sim.c
 *
 * Kyle Dotterrer
 * January, 2019 
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "sim.h"
#include "mips.h"
#include "shell.h"
#include "decode.h"

/* ----------------------------------------------------------------------------
	Instruction Handler Dipatch
*/

int (*INSTR_DISPATCH[128])(); 

/* ----------------------------------------------------------------------------
	Local Prototypes 
*/

int handle_j(uint32_t instr); 
int handle_jal(uint32_t instr); 
int handle_beq(uint32_t instr);
int handle_bne(uint32_t instr);
int handle_blez(uint32_t instr);
int handle_bgtz(uint32_t instr); 

int handle_lw(uint32_t instr); 
int handle_addiu(uint32_t instr);
int handle_unrecognized(uint32_t instr); 

/* ----------------------------------------------------------------------------
	Process Instruction
*/

void process_instruction(void) {
	// read the instr from memory text segment
	uint32_t raw_instr = mem_read_32(CURRENT_STATE.PC); 
	
	// decode the opcode 
	int op = decode_opcode(raw_instr);

	// dispatch the appropriate instruction handler
	(*INSTR_DISPATCH[op])(raw_instr); 
}

/* ----------------------------------------------------------------------------
	Instruction Handlers 
*/

/*
 * handle_j 
 * Jump 
 * Opcode: 2
 */
int handle_j(uint32_t instr) {
	// decode target address and shift left by 2 bits 
	uint32_t target = (decode_j_target(instr) << 2);

	// isolate high order bits of current address
	uint32_t current_addr = (CURRENT_STATE.PC & MASK_PC_HIGH); 

	// update the program counter unconditionally 
	NEXT_STATE.PC = current_addr + target; 

	return STATUS_OK; 
}

/*
 * handle_jal
 * Jump And Link
 * Opcode: 3
 */
int handle_jal(uint32_t instr) {
	// decode target address and shift left by 2 bits 
	uint32_t target = (decode_j_target(instr) << 2);

	// isolate high order bits of current address
	uint32_t current_addr = (CURRENT_STATE.PC & MASK_PC_HIGH);

	// update the program counter unconditionally 
	NEXT_STATE.PC = current_addr + target; 

	// place address of instruction after jump in link register 
	NEXT_STATE.REGS[REG_LINK] = CURRENT_STATE.PC + 4;

	return STATUS_OK;
}

/*
 * handle_beq
 * Branch On Equal
 * Opcode: 4
 */
int handle_beq(uint32_t instr) {
	// decode source and target registers 
	int rs = decode_i_rs(instr);
	int rt = decode_i_rt(instr);

	// decode offset, shift left 2 bits, and sign-extend 
	int32_t offset = (int32_t) (decode_i_immediate(instr) << 2); 

	if (CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt]) {
		// if contents of source and target registers are equal, branch is taken
		NEXT_STATE.PC = CURRENT_STATE.PC + offset; 
	} else {
		// otherwise, not taken
		NEXT_STATE.PC = CURRENT_STATE.PC + 4;
	}

	return STATUS_OK;
}

/*
 * handle_bne
 * Branch On Not Equal Zero
 * Opcode: 5
 */
int handle_bne(uint32_t instr) {
	// decode source and target registers 
	int rs = decode_i_rs(instr);
	int rt = decode_i_rt(instr);

	// decode offset, shift left 2 bits, and sign-extend 
	int32_t offset = (int32_t) (decode_i_immediate(instr) << 2);

	if (CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt]) {
		// if contents of source and taregt registers are not equal, branch is taken
		NEXT_STATE.PC = CURRENT_STATE.PC + offset;
	} else {
		// otherwise, not taken
		NEXT_STATE.PC = CURRENT_STATE.PC + 4;
	}

	return STATUS_OK; 
}

/*
 * handle_blez
 * Branch On Less Than Or Equal Zero
 * Opcode: 6
 */
int handle_blez(uint32_t instr) {
	// decode source register 
	int rs = decode_i_rs(instr);

	// decode offset, shift left 2 bits, and sign-extend 
	int32_t offset = (int32_t) (decode_i_immediate(instr) << 2); 

	if (CURRENT_STATE.REGS[rs] <= 0) {
		// if contents of source register less than or equal to zero, branch is taken
		NEXT_STATE.PC = CURRENT_STATE.PC + offset;
	} else {
		// otherwise, not taken
		NEXT_STATE.PC = CURRENT_STATE.PC + 4; 
	}

	return STATUS_OK; 
}

/*
 * handle_bgtz
 * Branch On Greater Than Zero
 * Opcode: 7
 */
int handle_bgtz(uint32_t instr) {
	// decode source register 
	int rs = decode_i_rs(instr);

	// decode offset, shift left 2 bits, and sign-extend 
	int32_t offset = (int32_t) (decode_i_immediate(instr) << 2);

	if (CURRENT_STATE.REGS[rs] > 0) {
		// if contents of source register greater than zero, branch is taken
		NEXT_STATE.PC = CURRENT_STATE.PC + offset;
	} else {
		// otherwise, not taken
		NEXT_STATE.PC = CURRENT_STATE.PC + 4;
	}

	return STATUS_OK;
}

/*
 * handle_lw
 * Load Word
 * Opcode: 35
 */
int handle_lw(uint32_t instr) {
	// decode base and target registers 
	int base = decode_i_rs(instr);
	int rt   = decode_i_rt(instr);

	// decode and sign-extend offset 
	int32_t offset = (int32_t) decode_i_immediate(instr);

	// add offet to contents of base register to form address
	uint32_t address = CURRENT_STATE.REGS[base] + offset; 
		
	// load memory contents at effective address into target register 
	NEXT_STATE.REGS[rt] = mem_read_32(address); 

	// update the program counter to point to next sequential instr
	NEXT_STATE.PC = CURRENT_STATE.PC + 4; 

	return STATUS_OK; 
}

/*
 * handle_addiu
 * Add Immediate Unsigned 
 * Opcode: 9
 */
int handle_addiu(uint32_t instr) {
	// decode source and target registers 
	int rs = decode_i_rs(instr);
	int rt = decode_i_rt(instr);

	// decode and sign-extend immediate value 
	int32_t immediate = (int32_t) decode_i_immediate(instr);

	// add contents of source register to immediate to form result
	int32_t result = CURRENT_STATE.REGS[rs] + immediate; 

	// store result in target register 
	NEXT_STATE.REGS[rt] = result;

	// update the program counter to point to next sequential instr
	NEXT_STATE.PC = CURRENT_STATE.PC + 4;

	return STATUS_OK; 
}

/*
 * handle_unrecognized 
 * Unrecognized Instruction
 * Opcode: any undefined opcode 
 */
int handle_unrecognized(uint32_t instr) {
	// for now, just fail silently 
	return STATUS_ERR;
}

/* ----------------------------------------------------------------------------
	Instruction Handler Dispatch Setup 
*/

void init_instr_dispatch(void) {
	memset(INSTR_DISPATCH, 0, sizeof(void *)*DISPATCH_SIZE);

	// setup handler for unrecognized instructions
	// prevents segmentation faults on bad opcode decodes 
	for (int i = 0; i < DISPATCH_SIZE; i++) {
		INSTR_DISPATCH[i] = handle_unrecognized;
	}

	// setup individual handlers for recognized instructions
	INSTR_DISPATCH[OPCODE_J] = handle_j; 
	INSTR_DISPATCH[OPCODE_JAL] = handle_jal; 
	INSTR_DISPATCH[OPCODE_BEQ] = handle_beq; 
	INSTR_DISPATCH[OPCODE_BNE] = handle_bne; 
	INSTR_DISPATCH[OPCODE_BLEZ] = handle_blez; 
	INSTR_DISPATCH[OPCODE_BGTZ] = handle_bgtz;

	INSTR_DISPATCH[OPCODE_LW] = handle_lw; 
	INSTR_DISPATCH[OPCODE_ADDIU] = handle_addiu; 
}




