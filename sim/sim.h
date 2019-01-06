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
// opcode and function field sizes are both 6 bits
#define DISPATCH_SIZE 128

void init_opcode_dispatch   (void);
void init_function_dispatch (void);
void init_target_dispatch   (void);

#endif // __SIM_H
