# Makefile for instruction-level MIPS simulator. 
# 
# Kyle Dotterrer
# January, 2018 

sim: shell.c sim.c decode.c 
	gcc -g -O2 $^ -o $@

clean:
	rm -f *.o 
	rm -f *~ 
	rm -f sim
	rm -f dumpsim 
	rm -rf *.dSYM

.PHONY: clean
