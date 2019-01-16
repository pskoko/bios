
import sys

print(sys.argv)

inputf = sys.argv[1]
outputf = sys.argv[2]

with open(inputf, 'r') as f:
    #source=[int(x) for x in f.read().split()]
    source = f.read()

"""
A naive, slow suffix-array construction algorithm.
"""

# Construct a list of suffixes of the source string.
suffixes = []
for offset in range(len(source) + 1):
    suffixes.append(source[offset:])

# Sort the suffixes
suffixes.sort()

def callcp(a, b):
    lcp = 0
    while lcp < len(a) and lcp < len(b) and a[lcp] == b[lcp]:
        lcp +=1
    return lcp

lcps =[-1];
for (i, s) in enumerate(suffixes):
    if i== 0: 
        continue
    lcps.append(callcp(suffixes[i-1], suffixes[i]))

# Calculate the start offset of each suffix, storing them in
# sorted order into the suffix array.
suffixArray = []
for suffix in suffixes:
    offset = len(source) - len(suffix)
    suffixArray.append(offset)

with open(outputf, 'w') as f:
    for s in lcps:
        f.write(str(s) + " ")




