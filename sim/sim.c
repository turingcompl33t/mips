/*
 * sim.c
 *
 * Kyle Dotterrer
 * January, 2019 
 */

#include <stdio.h>
#include <stdint.h>

#include "mips.h"
#include "shell.h"
#include "decode.h"

#define STATUS_OK  0
#define STATUS_ERR 1

int handle_lw(uint32_t instr); 

int (*INSTR_DISPATCH[1])() = {
	handle_lw
}; 

void process_instruction(void) {
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */

	// read the instr from memory text segment
	uint32_t raw_instr = mem_read_32(CURRENT_STATE.PC); 
	
	// decode the opcode 
	int op = decode_opcode(raw_instr);

	// dispatch the appropriate instruction handler
	(*INSTR_DISPATCH[0])(raw_instr); 
}

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




