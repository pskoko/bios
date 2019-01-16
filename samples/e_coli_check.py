import sys
import subprocess
import psutil
import os
import timeit

#assert(len(sys.argv) == 3)

out_name = "mid_res.txt"
in_name = "e_coli_stripped.txt"

exe = sys.argv[1]
result = subprocess.getoutput(['./cgmemtime -t ' + exe +" " + in_name+ " " + out_name])
print("time: {}".format(result.split(';')[2])) 
print("mem: {}".format(result.split(';')[3]))

