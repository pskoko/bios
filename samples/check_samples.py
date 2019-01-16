import sys
import subprocess
import psutil
import os
import timeit

#assert(len(sys.argv) == 3)

out_file_name = sys.argv[2]
f = open(out_file_name, 'w')

out_name = "mid_res.txt"

exe = sys.argv[1]

for dirName, subdirList, fileList in os.walk("synthetic"):
    if not len(subdirList) == 1:
        continue
    for in_name in fileList:
        #t0 = timeit.default_timer()
        result = subprocess.getoutput(['./cgmemtime -t ' + exe +" " + ("synthetic/" + in_name)+ " " + out_name])
        #t1 = timeit.default_timer()
        splt = in_name.split('.')[0].split('_')

        #f.write('{0},{1},{2},{3}\n'.format(splt[1], splt[2], t1-t0, max_mem.split(';')[3]))
        f.write('{0},{1},{2},{3}\n'.format(splt[1], splt[2], result.split(';')[2], result.split(';')[3]))


