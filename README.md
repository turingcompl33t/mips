## Instruction-Level MIPS Simulator 

Kyle Dotterrer

January, 2019

### Overview

An instruction-level simulator of a single-cycle processor implementing the MIPS ISA. 

### Semantics

Several of the semantic characteristics of this simulator may differ from what is expected.

**Implemented Instructions**

While a large subset of the instructions specified in the MIPS ISA are implemented, there remain a number of more "special purpose" instructions that are not.

**Branch Delay Slot**

The simulator is implemented _without_ obeying the semantics the the branch delay slot as it is specified in the MIPS ISA. That is, branch instructions may update the program counter directly without stalling for an additional cycle, and jump-and-link instructions update the program counter to PC + 4 rather than PC + 8, as is specified in the ISA.  

**Overflow Exceptions**

The simulator does not handle exceptions raised by overflows from arithmetic operations. 

**System Calls**

Only very limited system call behavior is implemented: if the register $v0 (register 2) has value 0x0A (decimal 10) when SYSCALL is executed, then simulator drops out of the simulation loop and returns to the shell prompt. If $v0 has any other value, the instruction has no effect.

### Acknowledgements

Project based on [specifications](http://www.archive.ece.cmu.edu/~ece447/s15/doku.php?id=start) originally published by Professor Onur Mutlu for his 2015 offering of _Introduction to Computer Architecture_ at Carnegie Mellon University. 
