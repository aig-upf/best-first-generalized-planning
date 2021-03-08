#!/usr/bin/env python
# coding: utf-8

import sys
import numpy as np
import random

def main():
	try:
		mode = sys.argv[1]
		from_size = int( sys.argv[2] )
		step = int( sys.argv[3] )
		to_size = int( sys.argv[4] )
		out_folder = sys.argv[5]
	except:
		print "Usage (from_size > 6 and step > 0): "
		print sys.argv[ 0 ] + " (synthesis|validation) <from_size> <step> <to_size> <out_folder>"
		print sys.argv[ 0 ] + " synthesis 10 5 100 tmp/"
		sys.exit(-1)
	
	if step < 1 or to_size < from_size :
		sys.exit( -2 )
	
	# DOMAIN
	str_domain = "SELECT\n\n"
	str_domain += "STATE DESCRIPTOR:\n"
	str_domain += "tail const-pointer\n"
	str_domain += "a pointer\n"
	str_domain += "b pointer\n"
	for i in range(to_size+1):
		str_domain += "v["+str(i)+"] register\n"
		
	f_domain=open( out_folder + "domain.txt", "w" )
	f_domain.write( str_domain )
	f_domain.close
			
	# INSTANCES
	np.random.seed(1007)
	i = from_size
	
	# synthesis by default
	max_val = 100
	if mode == "validation" :
		max_val = 1000000000

	while i <= to_size :
		# Computing
		v = np.random.randint(max_val, size=i)	
		sol = np.argmin( v, axis = 0 )
		
		# Problem name
		str_problem = "SELECT-" + str(i) + "\n"
		
		# Initial state
		str_problem += "\nINIT:\n"
		str_problem += "( a = 0 )\n"
		str_problem += "( b = 0 )\n"
		str_problem += "( tail = " + str(i-1) + " )\n"
		for j in range(i):
			str_problem += "( v["+str(j)+"] = " + str(v[j]) + " )\n"
		
		# Goal condition
		str_problem += "\nGOAL:\n"
		str_problem += "( a = " + str(i-1) + " )\n"
		str_problem += "( b = " + str(sol) + " )\n"		
		
		#print( str_problem )
		f_problem=open( out_folder + str( (i - from_size + step)//step ) + ".txt","w")
		f_problem.write( str_problem )
		f_problem.close()
		
		i += step
		
	sys.exit( 0 )
	
if __name__ == "__main__":
	main()
