/*
 * sim.h
 *
 * Kyle Dotterrer
 * January, 2018
 */

#ifndef __SIM_H
#define __SIM_H 

#define STATUS_OK  0
#define STATUS_ERR 1

// static size of instruction handler dispatch
// (opcode field is 6 bits, 2^6 = 128)
#define DISPATCH_SIZE 128

void init_instr_dispatch(void);

#endif // __SIM_H
