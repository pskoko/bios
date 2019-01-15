import sys
import subprocess
import psutil
import os

#assert(len(sys.argv) == 3)

old_exe_path = sys.argv[1]
#new_exe_path = sys.argv[2]
#our_exe_path = sys.argv[3]

process = subprocess.Popen(old_exe_path, stdout=subprocess.PIPE, creationflags=0x08000000)
pid = process.pid

pinfo = psutil.Process(os.getpid())

max_mem = 0
while not process.poll() is None:
    max_mem = max(pinfo.memory_info().rss, max_mem)

print(max_mem)