import sys
import random

# 65 - 90
# 97 - 122

out_file_name = 'out.txt'

all_letters = []

for i in range(65, 91):
    all_letters.append(chr(i))


for i in range(97, 122):
    all_letters.append(chr(i))

string_length = int(sys.argv[1])

s = []

for i in range(string_length):
    idx = random.randint(0, len(all_letters)-1)
    s.append(all_letters[idx])

o_file = open(sys.argv[2], 'w')

o_file.write(''.join(s))

o_file.flush()
o_file.close()