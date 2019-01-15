import sys
import subprocess
import psutil
import os

#assert(len(sys.argv) == 3)

old_exe_path = sys.argv[1]
#new_exe_path = sys.argv[2]
#our_exe_path = sys.argv[3]

process = subprocess.Popen(old_exe_path, shell=True)

pid = process.pid

max_mem = 0
while process.poll() is None:
    pinfo = psutil.Process(pid)
    max_mem = max(pinfo.memory_full_info().uss, max_mem)

print(max_mem)