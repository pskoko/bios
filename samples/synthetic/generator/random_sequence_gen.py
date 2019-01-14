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

def generate(string_length):
	s = []

	for i in range(string_length):
	    idx = random.randint(0, len(all_letters)-1)
	    s.append(all_letters[idx])

	return ''.join(s)

ns = [64, 128, 256, 512, 1024, 2048, 16384, 262144, 524288, 1048576]

for n in ns:
	for i in range(1, 11):

		f_name = 'syn_{}_{}.txt'.format(n, i)
		print(f_name)
		o_file = open(f_name, 'w')

		o_file.write(generate(n))

		o_file.flush()
		o_file.close()