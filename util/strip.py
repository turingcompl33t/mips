# strip.py
# Strip assembled MIPS program of unnecessary information. 
# (enables easier parsing by simulator)
#
# Input:
# 	Reads assembled file from stdin
# Output:
# 	Writes stripped results to stdout
#
# Kyle Dotterrer
# January, 2019 

import sys 
import fileinput 

def main():
	# read assembled file from stdin 
	for line in fileinput.input():
		# assembled lines output by SPIM begin with address of instruction;
		# the instruction is encapsulated as "[address]" - use to parse 
		if line[0] != "[":
			continue

		# pretty disgusting parse job here 
		# appears the SPIM non-uniformly outputs data separated by tabs and spaces
		split  = (line.strip().split("\t")[1]).split(" ")

		# now isolate the leading '0x' from hextring, wont need in simulator 
		hexstr = (split[0].split("x"))[1]

		# write the cleaned-up line to stdout 
		sys.stdout.write(hexstr)
		sys.stdout.write("\n")

if __name__ == "__main__":
	main()
