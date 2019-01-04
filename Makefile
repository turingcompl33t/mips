# Top-level makefile for instruction-level MIPS simulator. 
#
# Kyle Dotterrer
# January, 2019 

MAKE = make 

clean:
	cd hex/; $(MAKE) clean
	cd sim/; $(MAKE) clean
	cd util/; $(MAKE) clean

.PHONY: clean
