define HELP_TEXT
Please choose one of the following targets:
  run-tests      - clean, build, and test all benchmarks for the specified TARGET mode (host,standalone,simple)
  all-clean      - clean all benchmark directories for all TARGET modes
  spike-build    - build RISC-V Spike simulator extensions for bringup-bench

Within individual directories, the following Makefile targets are also available:
  clean          - delete all generated files
  build          - build the binary
  test           - run the standard test on the binary

Note that benchmark builds must be parameterized with the build MODE, such as:
  TARGET=host       - build benchmarks to run on a Linux host
  TARGET=standalone - build benchmarks to run in standalone mode (a virtual bare-metal CPU)
  TARGET=simple     - build benchmarks to run on the RISC-V Simple_System simulation testing environment
	TARGET=spike_toddmaustin - build benchmarks to run on the RISC-V Spike simulator with Todd Austin's fork
	TARGET=spike      - build benchmarks to run on the RISC-V Spike simulator. with this target, you can choose to use hard float by setting HARD_FLOAT=1
Also there is the variable ALIAS_RM_LIBMIN (default: 1) available for TARGETs "spike", "spike_toddmaustin" and "simple" that enables aliasing of libmin functions without the libmin_ prefix.

Example benchmark builds:
  make TARGET=spike HARD_FLOAT=1 ALIAS_RM_LIBMIN=0 run-tests
  make TARGET=spike run-tests # soft float is used, aliasing is enabled.
  make TARGET=host clean build test
  make TARGET=standalone build
  make TARGET=simple clean
  make all-clean
  make TARGET=simple run-tests
endef

export HELP_TEXT

error:
	@echo "$$HELP_TEXT"

#
# END of user-modifiable variables
#
BMARKS = ackermann anagram banner blake2b boyer-moore-search bubble-sort c-interp checkers cipher dhrystone distinctness donut fft-int flood-fill frac-calc fuzzy-match fy-shuffle gcd-list grad-descent hanoi heapsort indirect-test kadane kepler knapsack life longdiv lz-compress mandelbrot max-subseq mersenne minspan murmur-hash natlog nr-solver parrondo pascal pi-calc primal-test qsort-demo quine rabinkarp-search regex-parser rho-factor shortest-path sieve simple-grep skeleton spelt2num strange topo-sort totient weekday

OPT_CFLAGS = -O3 -g

RAM_START          = 0x04000000
RAM_LENGTH         = 0x01def000
RAM_START_DEC      = $(shell printf "%d" $(RAM_START))
RAM_LENGTH_DEC     = $(shell printf "%d" $(RAM_LENGTH))
STACK_START_DEC    = $(shell expr $(RAM_START_DEC) + $(RAM_LENGTH_DEC))
STACK_START        = $(shell printf "0x%X" $(STACK_START_DEC))
STACK_LENGTH       = 0x8000
STACK_LENGTH_DEC   = $(shell printf "%d" $(STACK_LENGTH))
PROGRAM_LENGTH_DEC = $(shell expr $(RAM_LENGTH_DEC) + $(STACK_LENGTH_DEC))
PROGRAM_START      = $(RAM_START)
PROGRAM_LENGTH     = $(shell printf "0x%X" $(PROGRAM_LENGTH_DEC))


ifeq ($(TARGET), host)
TARGET_CC = gcc
#TARGET_CC = clang
TARGET_AR = ar
TARGET_CFLAGS = -DTARGET_HOST
TARGET_LIBS =
TARGET_SIM =
TARGET_DIFF = diff
TARGET_EXE = $(PROG).host
TARGET_EXTRA_DEPS = 
TARGET_CLEAN =
TARGET_BMARKS = $(BMARKS)
TARGET_CONFIGURED = 1
else ifeq ($(TARGET), standalone)
TARGET_CC = gcc
#TARGET_CC = clang
TARGET_AR = ar
TARGET_CFLAGS = -DTARGET_SA
TARGET_LIBS =
TARGET_SIM =
TARGET_DIFF = diff
TARGET_EXE = $(PROG).sa
TARGET_EXTRA_DEPS =
TARGET_CLEAN =
TARGET_BMARKS = $(BMARKS)
TARGET_CONFIGURED = 1
else ifeq ($(TARGET), simple)
TARGET_CC = riscv32-unknown-elf-gcc
#TARGET_CC = riscv32-unknown-elf-clang
TARGET_AR = riscv32-unknown-elf-ar
# TODO: HARD_FLOAT secenegini spike_toddmaustin ve simple icin de ekle
ALIAS_RM_LIBMIN = 1
TARGET_CFLAGS = -DTARGET_SIMPLE -DALIAS_RM_LIBMIN=$(ALIAS_RM_LIBMIN) -march=rv32imc -mabi=ilp32 -static -mcmodel=medlow -Wall -g -Os -fvisibility=hidden -nostdlib -nostartfiles -ffreestanding # -MMD -mcmodel=medany
TARGET_LIBS = -lgcc
TARGET_SIM = ../target/simple_sim.sh ../../../ibex/build/lowrisc_ibex_ibex_simple_system_0/sim-verilator/Vibex_simple_system
TARGET_DIFF = mv ibex_simple_system.log FOO; diff
TARGET_EXTRA_DEPS = ../target/simple-map.ld ../target/simple-crt0.S
TARGET_EXE = $(PROG).elf
TARGET_CLEAN = *.d ibex_simple_system_pcount.csv
TARGET_BMARKS = banner blake2b boyer-moore-search bubble-sort cipher dhrystone distinctness fft-int flood-fill frac-calc fuzzy-match fy-shuffle gcd-list grad-descent hanoi heapsort indirect-test kadane kepler knapsack life longdiv mandelbrot max-subseq mersenne minspan murmur-hash natlog nr-solver parrondo pascal primal-test qsort-demo rabinkarp-search regex-parser shortest-path sieve simple-grep skeleton strange topo-sort totient weekday
TARGET_CONFIGURED = 1
else ifeq ($(TARGET), spike_toddmaustin)
# TARGET_CC = riscv32-unknown-elf-gcc # toddmaustin'in orijinali
TARGET_CC = riscv64-unknown-elf-gcc
#TARGET_CC = riscv32-unknown-elf-clang
TARGET_AR = riscv64-unknown-elf-ar
# TODO: HARD_FLOAT secenegini spike_toddmaustin ve simple icin de ekle
ALIAS_RM_LIBMIN = 1
TARGET_CFLAGS = -DTARGET_SPIKE_TODDMAUSTIN -DALIAS_RM_LIBMIN=$(ALIAS_RM_LIBMIN) -march=rv64imc_zicsr -mabi=lp64 -static -mcmodel=medlow -Wall -g -Os -fvisibility=hidden -nostdlib -nostartfiles -ffreestanding # -MMD -mcmodel=medany
TARGET_LIBS = -lgcc
TARGET_SIM = $(SPIKE_TODDMAUSTIN)/build/spike --isa=RV64IMAFDC --extlib=../target/simple_mmio_plugin.so -m0x100000:0x40000 --device=simple_mmio_plugin,0x20000,x
TARGET_DIFF = diff
TARGET_EXE = $(PROG).elf
TARGET_EXTRA_DEPS = ../target/simple-map.ld ../target/simple-crt0.S
TARGET_CLEAN = *.d ibex_simple_system_pcount.csv
# TARGET_BMARKS = banner blake2b boyer-moore-search bubble-sort cipher dhrystone distinctness fft-int flood-fill frac-calc fuzzy-match fy-shuffle gcd-list grad-descent hanoi heapsort indirect-test kadane kepler knapsack life longdiv mandelbrot max-subseq mersenne minspan murmur-hash natlog nr-solver parrondo pascal primal-test qsort-demo rabinkarp-search regex-parser shortest-path sieve simple-grep skeleton strange topo-sort totient weekday
TARGET_BMARKS = banner blake2b boyer-moore-search bubble-sort dhrystone distinctness fft-int flood-fill frac-calc fuzzy-match fy-shuffle gcd-list grad-descent hanoi heapsort indirect-test kadane kepler knapsack life mandelbrot max-subseq mersenne minspan murmur-hash natlog nr-solver parrondo pascal primal-test qsort-demo regex-parser shortest-path sieve simple-grep skeleton strange topo-sort totient weekday
TARGET_CONFIGURED = 1
else ifeq ($(TARGET), spike)
# TARGET_CC = riscv32-unknown-elf-gcc # toddmaustin'in orijinali
TARGET_CC = riscv64-unknown-elf-gcc
#TARGET_CC = riscv32-unknown-elf-clang
TARGET_AR = riscv64-unknown-elf-ar
# libmin_function_name'ler icin function_name isimli bir alias olustur.
ALIAS_RM_LIBMIN = 1
PRINT_CYCLES_ON_EXIT = 0
	ifeq ($(HARD_FLOAT), 1)
TARGET_CFLAGS = -DTARGET_SPIKE -DHARD_FLOAT -DALIAS_RM_LIBMIN=$(ALIAS_RM_LIBMIN) -DPRINT_CYCLES_ON_EXIT=$(PRINT_CYCLES_ON_EXIT) -march=rv64imfdc_zicsr -mabi=lp64d -static -mcmodel=medlow -Wall -g -Os -fvisibility=hidden -nostdlib -nostartfiles -ffreestanding # -MMD -mcmodel=medany
	else
TARGET_CFLAGS = -DTARGET_SPIKE -DALIAS_RM_LIBMIN=$(ALIAS_RM_LIBMIN) -DPRINT_CYCLES_ON_EXIT=$(PRINT_CYCLES_ON_EXIT) -march=rv64imc_zicsr -mabi=lp64 -static -mcmodel=medlow -Wall -g -Os -fvisibility=hidden -nostdlib -nostartfiles -ffreestanding # -MMD -mcmodel=medany
	endif
#  -ffreestanding  -fvisibility=hidden -nostdlib olmadan da calisiyor gibi gorunuyor.
TARGET_LIBS = -lgcc
TARGET_SIM = $(SPIKE_ORIG)/build/spike --isa=RV64IMAFDC -m$(PROGRAM_START):$(PROGRAM_LENGTH)
	ifeq ($(PRINT_CYCLES_ON_EXIT), 1)
TARGET_DIFF =sed -i 's/mcycle.*//' FOO;  truncate -s -2 FOO; diff
	else
TARGET_DIFF =diff
	endif
TARGET_EXE = $(PROG).elf
TARGET_EXTRA_DEPS = ../target/spike-map-prep.ld ../target/spike-crt0.S
# bu alt satirdaki ne?
TARGET_CLEAN = *.d ibex_simple_system_pcount.csv
# TARGET_BMARKS = banner blake2b boyer-moore-search bubble-sort cipher dhrystone distinctness fft-int flood-fill frac-calc fuzzy-match fy-shuffle gcd-list grad-descent hanoi heapsort indirect-test kadane kepler knapsack life longdiv mandelbrot max-subseq mersenne minspan murmur-hash natlog nr-solver parrondo pascal primal-test qsort-demo rabinkarp-search regex-parser shortest-path sieve simple-grep skeleton strange topo-sort totient weekday
TARGET_BMARKS = banner blake2b boyer-moore-search bubble-sort dhrystone distinctness fft-int flood-fill frac-calc fuzzy-match fy-shuffle gcd-list grad-descent hanoi heapsort indirect-test kadane kepler knapsack life mandelbrot max-subseq mersenne minspan murmur-hash natlog nr-solver parrondo pascal primal-test qsort-demo regex-parser shortest-path sieve simple-grep skeleton strange topo-sort totient weekday
TARGET_CONFIGURED = 1


else
# default is an unconfigured
TARGET_CONFIGURED = 0
endif

CFLAGS = -Wall $(OPT_CFLAGS) -Wno-strict-aliasing $(TARGET_CFLAGS) $(LOCAL_CFLAGS)
OBJS = $(LOCAL_OBJS) ../target/libtarg.o
__LIBMIN_SRCS = libmin_abs.c libmin_atof.c libmin_atoi.c libmin_atol.c libmin_ctype.c libmin_exit.c \
  libmin_fabs.c libmin_fail.c libmin_floor.c libmin_getopt.c libmin_malloc.c libmin_mclose.c \
  libmin_memcmp.c libmin_memcpy.c libmin_memmove.c libmin_memset.c libmin_meof.c libmin_mgetc.c \
  libmin_mgets.c libmin_mopen.c libmin_mread.c libmin_msize.c libmin_pow.c libmin_printf.c \
  libmin_putc.c libmin_puts.c libmin_qsort.c libmin_rand.c libmin_rempio2.c libmin_scalbn.c \
  libmin_scanf.c libmin_sfile.c libmin_sincos.c libmin_sqrt.c libmin_strcat.c libmin_strchr.c \
  libmin_strcmp.c libmin_strcpy.c libmin_strcspn.c libmin_strdup.c libmin_strfits.c libmin_strlen.c \
	libmin_strncat.c libmin_strncmp.c libmin_strncontains.c \
  libmin_strncpy.c libmin_strpbrk.c libmin_strrchr.c libmin_strspn.c libmin_strstr.c libmin_strcasestr.c \
  libmin_strtok.c libmin_strtol.c libmin_success.c libmin_strncasecmp.c libmin_time.c
LIBMIN_SRCS = $(addprefix ../common/,$(basename $(__LIBMIN_SRCS)))
LIBMIN_OBJS = $(addprefix ../common/,$(addsuffix .o,$(basename $(__LIBMIN_SRCS))))

LIBS = ../common/libmin.a

build: $(TARGET_EXE)

%.o: %.c
	$(TARGET_CC) $(CFLAGS) -I../common/ -I../target/ -o $@ -c $<

../common/libmin.a: $(LIBMIN_OBJS)
	$(TARGET_AR) rcs ../common/libmin.a $(LIBMIN_OBJS)





LINKER_MACROS = -DRAM_START=$(RAM_START) -DRAM_LENGTH=$(RAM_LENGTH) -DSTACK_START=$(STACK_START) -DSTACK_LENGTH=$(STACK_LENGTH)

../target/spike-map-prep.ld: ../target/spike-map.ld
	riscv64-unknown-elf-cpp $(LINKER_MACROS) -P $< > $@


$(TARGET_EXE): $(OBJS) $(LIBS) $(TARGET_EXTRA_DEPS)
ifeq ($(TARGET), host)
	$(TARGET_CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) $(TARGET_LIBS)
else ifeq ($(TARGET), standalone)
	$(TARGET_CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) $(TARGET_LIBS)
else ifeq ($(TARGET), simple)
	$(TARGET_CC) $(CFLAGS) -T ../target/simple-map.ld $(OBJS) ../target/simple-crt0.S -o $@ $(LIBS) $(TARGET_LIBS)
else ifeq ($(TARGET), spike_toddmaustin)
	$(TARGET_CC) $(CFLAGS) -T ../target/simple-map.ld $(OBJS) ../target/simple-crt0.S -o $@ $(LIBS) $(TARGET_LIBS)
else ifeq ($(TARGET), spike)
	$(TARGET_CC) $(CFLAGS) -T ../target/spike-map-prep.ld $(OBJS) ../target/spike-crt0.S -o $@ $(LIBS) $(TARGET_LIBS)
else
	$(error MODE is not defined (add: TARGET={host|sa}).)
endif


clean:
	rm -f $(PROG).host $(PROG).sa $(PROG).elf *.o ../common/*.o ../target/*.o ../target/spike-map-prep.ld ../common/libmin.a *.d ../common/*.d core mem.out *.log FOO $(LOCAL_CLEAN) $(TARGET_CLEAN)


#
# top-level Makefile interfaces
#

run-tests:
ifeq ($(TARGET_CONFIGURED), 0)
	@echo "'run-tests' command requires a TARGET definition." ; \
	echo "" ; \
	echo "$$HELP_TEXT"
else
	@for _BMARK in $(TARGET_BMARKS) ; do \
	  cd $$_BMARK ; \
	  echo "--------------------------------" ; \
	  echo "Running "$$_BMARK" in TARGET="$$TARGET ; \
	  echo "--------------------------------" ; \
	  $(MAKE) TARGET=$$TARGET clean build test || exit 1; \
	  cd .. ; \
	done
endif

clean-all all-clean:
	@for _BMARK in $(BMARKS) ; do \
	  for _TARGET in host standalone simple spike ; do \
	    cd $$_BMARK ; \
	    echo "--------------------------------" ; \
	    echo "Cleaning "$$_BMARK" in TARGET="$$_TARGET ; \
	    echo "--------------------------------" ; \
	    $(MAKE) TARGET=$$_TARGET clean ; \
	    cd .. ; \
	  done \
	done

spike-build:
	$(MAKE) -C target clean build
