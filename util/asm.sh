#!/bin/bash
#
# asm.sh
# Pipeline to simplify assembly process. 
# 
# Kyle Dotterrer
# January, 2019

if [ $# != 1 ]; then
	echo "invalid arguments"
	echo "usage: asm.sh <MIPS assembly file>"
	exit 1
fi 

# just pipeline our other tools together 
python3 masm.py $1 | python3 strip.py 

exit 0
