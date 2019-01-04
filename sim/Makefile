# Makefile for instruction-level MIPS simulator. 
# 
# Kyle Dotterrer
# January, 2018 

sim: shell.c sim.c
	gcc -g -O2 $^ -o $@

clean:
	rm -rf *.o *~ sim

.PHONY: clean
