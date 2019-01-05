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

int handle_lw(uint32_t instr); 
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
	INSTR_DISPATCH[OPCODE_LW] = handle_lw; 
}




