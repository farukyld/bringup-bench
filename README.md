# Çalıştırmak için:

```shell
# Makefile dosyasinda simulasyon komutu olarak 
# $SPIKE_ORIG/build/spike seklinde kullanilmakta
export SPIKE_ORIG=$SPIKE_ORIG 
make run-tests
```

aşağıda benchmark'ları derlerken kullandığım derleyicinin versiyonu ve konfigürasyonu yer almaktadır: (konfigürasyonda gerekli multilib destekleri olmayınca derlemede hata veriyor. (konfigürasyonun küçültülmesi üzerine)[])
```shell
riscv64-unknown-elf-gcc -v
```
```shell
Using built-in specs.
COLLECT_GCC=riscv64-unknown-elf-gcc
COLLECT_LTO_WRAPPER=/opt/riscv/libexec/gcc/riscv64-unknown-elf/13.2.0/lto-wrapper
Target: riscv64-unknown-elf
Configured with: /home/usr1/riscv-gnu-toolchain/gcc/configure --target=riscv64-unknown-elf --prefix=/opt/riscv --disable-shared --disable-threads --enable-languages=c,c++ --with-pkgversion=gc891d8dc23e --with-system-zlib --enable-tls --with-newlib --with-sysroot=/opt/riscv/riscv64-unknown-elf --with-native-system-header-dir=/include --disable-libmudflap --disable-libssp --disable-libquadmath --disable-libgomp --disable-nls --disable-tm-clone-registry --src=.././gcc --enable-multilib --with-multilib-generator='rv32e-ilp32e--;rv32ea-ilp32e--;rv32em-ilp32e--;rv32eac-ilp32e--;rv32emac-ilp32e--;rv32i-ilp32--;rv32if-ilp32f--;rv32ifd-ilp32d--;rv32ia-ilp32--;rv32iaf-ilp32f--;rv32imaf-ilp32f--;rv32iafd-ilp32d--;rv32im-ilp32--;rv32imf-ilp32f--;rv32imfc-ilp32f--;rv32imfd-ilp32d--;rv32iac-ilp32--;rv32imac-ilp32--;rv32imafc-ilp32f--;rv32imafdc-ilp32d--;rv64i-lp64--;rv64if-lp64f--;rv64ifd-lp64d--;rv64ia-lp64--;rv64iaf-lp64f--;rv64imaf-lp64f--;rv64iafd-lp64d--;rv64im-lp64--;rv64imf-lp64f--;rv64imfc-lp64f--;rv64imfd-lp64d--;rv64iac-lp64--;rv64imac-lp64--;rv64imafc-lp64f--;rv64imafdc-lp64d--;rv64imafdc_zifencei-lp64d--;' --with-abi=lp64d --with-arch=rv64imafdc --with-tune=rocket --with-isa-spec=20191213 'CFLAGS_FOR_TARGET=-Os    -mcmodel=medany' 'CXXFLAGS_FOR_TARGET=-Os    -mcmodel=medany'
Thread model: single
Supported LTO compression algorithms: zlib
gcc version 13.2.0 (gc891d8dc23e)
```

**NOT:** Burada önemli olan konfigürasyon komutu:
```shell
/home/usr1/riscv-gnu-toolchain/gcc/configure --target=riscv64-unknown-elf --prefix=/opt/riscv --disable-shared --disable-threads --enable-languages=c,c++ --with-pkgversion=gc891d8dc23e --with-system-zlib --enable-tls --with-newlib --with-sysroot=/opt/riscv/riscv64-unknown-elf --with-native-system-header-dir=/include --disable-libmudflap --disable-libssp --disable-libquadmath --disable-libgomp --disable-nls --disable-tm-clone-registry --src=.././gcc --enable-multilib --with-multilib-generator='rv32e-ilp32e--;rv32ea-ilp32e--;rv32em-ilp32e--;rv32eac-ilp32e--;rv32emac-ilp32e--;rv32i-ilp32--;rv32if-ilp32f--;rv32ifd-ilp32d--;rv32ia-ilp32--;rv32iaf-ilp32f--;rv32imaf-ilp32f--;rv32iafd-ilp32d--;rv32im-ilp32--;rv32imf-ilp32f--;rv32imfc-ilp32f--;rv32imfd-ilp32d--;rv32iac-ilp32--;rv32imac-ilp32--;rv32imafc-ilp32f--;rv32imafdc-ilp32d--;rv64i-lp64--;rv64if-lp64f--;rv64ifd-lp64d--;rv64ia-lp64--;rv64iaf-lp64f--;rv64imaf-lp64f--;rv64iafd-lp64d--;rv64im-lp64--;rv64imf-lp64f--;rv64imfc-lp64f--;rv64imfd-lp64d--;rv64iac-lp64--;rv64imac-lp64--;rv64imafc-lp64f--;rv64imafdc-lp64d--;rv64imafdc_zifencei-lp64d--;' --with-abi=lp64d --with-arch=rv64imafdc --with-tune=rocket --with-isa-spec=20191213 'CFLAGS_FOR_TARGET=-Os    -mcmodel=medany' 'CXXFLAGS_FOR_TARGET=-Os    -mcmodel=medany'
```

spike versiyonu (en güncel versiyonda da çalışmalı)
```
11fbcb52f4d7ca247cb5f2503552ec653025bf40
```

# Libmini Farklı benchmark'larda kullanmak için:

[libmin kullanım talimatları](libmin_kullanim_talimatlari.md)



# Bringup-Bench Benchmark Suite

Bringup */bring-up/* **verb**
Refers to the process of bringing a newly designed and implemented CPU, accelerator, compiler, or operating system to life and verifying its functionality.

## Introduction

The Bringup-Bench Benchmark Suite is a collection of C code benchmarks that are purpose-built to be useful in "bringing up" newly designed CPUs, acclerators, compilers, and operating systems. Bringup-Bench facilitates the bringup process because i) its benchmarks have zero library dependencies since the "libmin" library included in the repo implements all the necessary library calls, ii) its benchmarks have near-zero system dependencies since only four simple system calls must be implement to support all the benchmarks, and iii) the benchmark build process supports code-based read-only file access, which allows benchmark file inputs to be packaged into the benchmark build.

I (Todd Austin) have used this benchmark suite to bring up new CPUs, new compiler infrastructure and even recently a Turing-complete encrypted computation accelerator. Most developers probably don't need bringup-bench, but if you do need it, you probably need it very badly!

## Bringing up Bringup-Bench
To build and test a benchmark, simply enter one of the benchmark directories and execute the following makefile command:
```
make clean build test
```
This command will first "clean" the benchmark directory and then "build" the application, and "test" that it is running correctly. 

Each benchmark support three standard Makefile targets: build, test, and clean

- **build** - Builds the benchmark

- **test** - Runs the benchmark and validates its output.

- **clean** - Deleted all derived files.

For example, to build, test and then clean the Bubble Sort benchmark in encrypted mode:
```
make build
make test
make clean
```

To assist in running experiments, the top-level Makefile includes a few useful targets:
```
make run-tests   # clean, build, and test all benchmarks
make all-clean   # clean all benchmark directories for all supported targets
```
You should be able to adapt these targets to your own project-specific tasks.

## Benchmarks

The Bringup-Bench benchmarks were selected for their minimal library and system dependencies, while still being interesting and non-trival codes.i Currently, the benchmark suite supports the following benchmarks. Note that the benchmarks tagged with (FP) require some form of floating point support, and the remaining benchmarks only require integer and string computation.

- **ackermann** - Calculates the Ackermann function for a variety of input values.

- **anagram** - Computes anagrams for the phrases in "input.txt" using the diction in the "words". This benchmark uses code-based read-only file access for multiple files.

- **banner** - Prints out a fancy vertical banner.

- **blake2b** - Reference implementation and test of BLAKE2b, a cryptographic hash function based on Daniel J. Bernstein's ChaCha stream cipher.

- **boyer-moore-search** - Performs a Boyer-Moore optimized search, given a test string and a large string to search.

- **bubble-sort** - Performs a bubble sort on a randomly generated internal list of integers.

- **checkers** - Checkers game based on minimax search.

- **c-interp** - A C language interpreter that interprets the test program "hello.c". This benchmark uses code-based read-only file access.

- **cipher** - A TEA cipher implementation the encrypts and decrypts some fixed test data.

- **dhrystone** - An old-school Dhrystone benchmark.

- **distinctness** - Computes if every element of an array is unique.

- **donut** - A donut in code and action that defies proper explanation!

- **fft-int** - Performs an integer fast-Fourier-transform on fixed integer input data.

- **flood-fill** - Performs a color-based flood fill of a fixed tw-dimensional text array.

- **frac-calc** - Computes calculations on proper and improper fractions.

- **fy-shuffle** - A Fisher-Yates perfect random vector shuffle implementation.

- **gcd-list** - Computes the greatest common divisor for a list of integers using the division algorithm.

- **hanoi** - Solves the Tower's of Hanoi problem for a variable number of towers.

- **heapsort** - Performs a heap sort on a randomly generated data set

- **kepler** - Calculates an orbital path for a planetary body based on the Kepler parameters.

- **life** - Conway's game of life simulation.

- **longdiv** - Computes a long division using the pencil-on-paper method.

- **lz-compress** - A compression/decompress tool based on the LZ compression algorithm.

- **mandelbrot** - Calculate and print using ASCII graphics a Mendelbrot fractal.

- **max-subseq** - Computes the longest subsequence common (LSC) to all sequences in a set of sequences using the dynamic programming method.

- **mersenne** - Generate a sequence of pseudo-random numbers using the Mersenne Twister algorithm.

- **minspan** - Finds the minimal spanning tree of a graph (via Kruscal's algorithm over the graph's adjacency matrix).

- **natlog** - Compute the value of natural log e, using an iterative method.

- **nr-solver** - Computes a square-root value using a Newton-Raphson solver.

- **parrondo** - A game theory based solver that simulates Parrondo's paradox.

- **pascal** - Compute Pascal's triangle, to a specified depth.

- **pi-calc** - An integer based high-precision PI calculator.

- **primal-test** - Performs the Miller-Rabin stochastic primarility test to extremely high certainty.

- **quine** - A C program that prints itself.

- **rabinkarp-search** - Implements the very efficient Rabin-Karp data-oblivious string search algorithm. This search algorithm is O(N) in the length of the string searched.

- **rho-factor** - A Pollard's Rho integer factorization algorithm.

- **shortest-path** - Solves the all-pairs shortest path problem using the Floyd-Warshall algorithm.

- **sieve** - Computes the prime values within a specified range, using the Sieve of Eratosthenes algorithmm

- **skeleton** - A minimal program, for use a starting point for new application ports and developments.

- **spelt2num** - A spelled-out number to binary number converter.

- **strange** - A strange C program that acts strangely in an expected manner.

- **topo-sort** - Tolologically sorts a graph and prints the result in breadth-first order.

- **totient** - Calculates the Euler totient function phi.

- **weekday** - Given a year, month, and day, deterime the day of the week for the specified date.

## Minimal library dependencies

Bringup-Bench has no library dependencies, to reduce the amount of system infrastructure needed to get your first application running. Instead of needing system libraries, Bringup-bench implements its own library in "libmin". "libmin" includes most of what simple applications need, including:

- printing values
- parsing numbers from text
- options parsing
- string processing
- memory copy and setting
- program exit interfaces
- pseudo-random number generation
- dynamic storage allocator
- code-based read-only file access functions
- sorting functions
- character class tests (from ctype.h)
- floating-point math functions

See the file "common/libmin.h" for more details.

## Minimal system dependencies

To minimize the system OS requirements, the Bringup-Bench only requires four system call interfaces to be implement. The interfaced required are as follows:
```
/* benchmark completed successfully */
void libtarg_success(void);

/* benchmark completed with error CODE */
void libtarg_fail(int code);

/* output a single character, to wherever the target wants to send it... */
void libtarg_putc(char c);

/* get some memory */
void *libtarg_sbrk(size_t inc);
```
Once these four interfaces are implemented, all of the Bringup-Bench benchmarks can be built and run. To facilitate testing, the "TARGET=host" target defines the four required system interfaces by passing them on to the Linux OS. In addition, the repo also provides a standalone target "TARGET=sa" which only requires that the target support provbable memory.

## Using the code-based read-only file system

 Using the code-based read-only file system, it is possible for a benchmark to access a read-only file that is incorporated into its code. To convert an input file to a read-only code-based file, create an assembly file, containing the below lines:
```assembly
#include "target/include_input_files.h"

REGISTER_FILE(file1.txt, file1_txt)
REGISTER_FILE(file2.txt, file2_txt)
```


file1.txt and file2.txt are file names, the paths are relative to where you lauch the assembler. file1_txt and file2_txt are just arbitrary names to be used in naming symbols in the assembly file.

compile and link that assembly file into your elf file. 

The following interfaces are available to access memory files:
```c
/* open an in-memory file */
MFILE * libmin_mopen(const char *fname, const char *mode);
```
here, fname is the string passed to `REGISTER_FILE` macro. (`file1.txt`)


```c
/* return in-memory file size */
size_t libmin_msize(MFILE *mfile);

/* at end of file */
int libmin_meof(MFILE *mfile);

/* close the in-memory file */
void libmin_mclose(MFILE *mfile);

/* read a buffer from the in-memory file */
size_t libmin_mread(void *ptr, size_t size, MFILE *mfile);

/* get a string from the in-memory file */
char *libmin_mgets(char *s, size_t size, MFILE *mfile);

/* read a character from the in-memory file */
int libmin_mgetc(MFILE *mfile);
```

## Porting the Bringup-Bench to other targets

To port the Bringup-bench to your new CPU, accelerator, compiler, or operating system, you need only concern yourself with the "libtarg.h" and "libmin.c" files. First define a new target specifier in "Makefile" and then add it to the "libtarg.h" and "libtarg.c" files. Inside the "libtarg.h" file you will need to define basic data type sizes plus define how the benchmarks access "vararg" parameter arguments. Inside the "libtarg.c" file, you will need to define the following four system call interfaces:
```
/* benchmark completed successfully */
void libtarg_success(void);

/* benchmark completed with error CODE */
void libtarg_fail(int code);

/* output a single character, to wherever the target wants to send it... */
void libtarg_putc(char c);

/* get some memory */
void *libtarg_sbrk(size_t inc);
```

## Licensing details

The portions of the benchmark suite that was built by the benchmark team are (C) 2021-2024 and available for use under
the [Apache License, version 2.0](https://www.apache.org/licenses/LICENSE-2.0) 

And, thanks to the respective authors of the benchmarks that were adapted for the Bringup-Bench Benchmark Suite from other efforts.

