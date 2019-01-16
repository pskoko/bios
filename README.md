# Inducing the LCP-Array

This is an implementation of the modified SA-IS algorithm [Inducing the LCP-Array](https://arxiv.org/abs/1101.3448) by Johannes Fischer.

The implementation is done for a course project in [Bioinformatics](https://www.fer.unizg.hr/predmet/bio) at the [Faculty of Electrical Engineering and Computing, University of Zagreb](https://www.fer.unizg.hr/en)

The implementation is done in C++ and licensed under the MIT license (see LICENSE).

## Instalation instructions

Clone the git repository with:
```
git clone https://github.com/pskoko/bios/
```
Go into repository directory:
```
cd bios
```
Make the directory for bulding the code and go into it:
```
mkdir build
cd build
```
Generate Makefiles with cmake:
```
cmake ..
```
And build the program:
```
make
```

Program is built under the name `LCP` and its run syntax is:
```
./LCP <path to input file> <path to output file>
```
First argument is path to file with text to calculate lcp values, and second argument is path to file where lcp values will be written.
