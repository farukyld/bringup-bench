ALIAS_RM_LIBMIN = 1
PRINT_CYCLES_ON_EXIT = 0
SPIKE_INTERAC = 0
HARD_FLOAT = 0
GDB_DEBUG = 0
HEAP_LENGTH        = 0x5000
PROGRAM_START      = 0x80000000
PROGRAM_LENGTH     = 0x600000
STACK_LENGTH       = 0x8000


define HELP_TEXT
Please choose one of the following targets:
  run-tests      - clean, build, and test all benchmarks for the specified TARGET mode (host,standalone,simple)
  all-clean      - clean all benchmark directories for all TARGET modes

Within individual directories, the following Makefile targets are also available:
  clean          - delete all generated files
  build          - build the binary
  test           - run the standard test on the binary
  run-sim        - run the binary in the Spike simulator, output to stdout
Options available:
	ALIAS_RM_LIBMIN=0 - disable aliasing of libmin functions
	HARD_FLOAT=1 - enable hard float ABI
	PRINT_CYCLES_ON_EXIT=1 - print cycle count on exit


Example benchmark builds:
  make  HARD_FLOAT=1 ALIAS_RM_LIBMIN=0 run-tests
  make  run-tests # soft float is used, aliasing is enabled. run simulations and diff check
  make  run-sims # run all benchmarks in Spike simulator. output to stdout.
endef

export HELP_TEXT

error:
	@echo "$$HELP_TEXT"


OPT_CFLAGS = -O3 -g

STACK_START        = $(shell printf "0x%X\n" $$(($(PROGRAM_START) + $(PROGRAM_LENGTH))))
HEAP_START         = $(shell printf "0x%X\n" $$(($(STACK_START) + $(STACK_LENGTH))))
MEM_START          = $(PROGRAM_START)
MEM_LENGTH         = $(shell printf "0x%X\n" $$(($(PROGRAM_LENGTH) + $(STACK_LENGTH) + $(HEAP_LENGTH) )))


TARGET_CC = riscv64-unknown-elf-gcc
TARGET_AR = riscv64-unknown-elf-ar

ifeq ($(GDB_DEBUG), 1)
CC_GDB_OPT_FLAGS = -g -Og -DGDB_DEBUG=1
else
CC_GDB_OPT_FLAGS = -Os -DGDB_DEBUG=0
endif

COMMON_CFLAGS = -DALIAS_RM_LIBMIN=$(ALIAS_RM_LIBMIN)\
  -DPRINT_CYCLES_ON_EXIT=$(PRINT_CYCLES_ON_EXIT)\
  -DHEAP_LENGTH=$(HEAP_LENGTH) $(CC_GDB_OPT_FLAGS)\
	-static -mcmodel=medlow -Wall \
	-fvisibility=hidden -nostdlib -nostartfiles -ffreestanding -fPIC # -MMD -mcmodel=medany

ifeq ($(HARD_FLOAT), 1)
HARD_FLOAT_MARCH_MABI = -DHARD_FLOAT -march=rv64imfdc_zicsr -mabi=lp64d
else
HARD_FLOAT_MARCH_MABI = -march=rv64imc_zicsr -mabi=lp64
endif
TARGET_CFLAGS = $(HARD_FLOAT_MARCH_MABI) $(COMMON_CFLAGS)

TARGET_LIBS = -lgcc

ifeq ($(SPIKE_INTERAC), 1)
SPK_DBG=-d
else
SPK_DBG=
endif

ifeq ($(GDB_DEBUG), 1)
RBB_PORT= --rbb-port=9824
else
RBB_PORT=
endif
#  -ffreestanding  -fvisibility=hidden -nostdlib olmadan da calisiyor gibi gorunuyor.
TARGET_SIM = $(SPIKE_ORIG)/build/spike $(SPK_DBG) $(RBB_PORT) --isa=RV64IMAFDC -m$(MEM_START):$(MEM_LENGTH)

ifeq ($(PRINT_CYCLES_ON_EXIT), 1)
TARGET_DIFF =sed -i 's/mcycle.*//' FOO;  truncate -s -2 FOO; diff
else
TARGET_DIFF =diff
endif

TARGET_EXE = $(PROG).elf
TARGET_EXTRA_DEPS = ../target/spike-map-prep.ld ../target/spike-crt0.S
# bu alt satirdaki ne?
TARGET_CLEAN = *.d ibex_simple_system_pcount.csv
TARGET_BMARKS = banner blake2b boyer-moore-search bubble-sort dhrystone distinctness fft-int flood-fill\
  frac-calc fuzzy-match fy-shuffle gcd-list grad-descent hanoi heapsort indirect-test kadane kepler \
	knapsack life mandelbrot max-subseq mersenne minspan murmur-hash natlog nr-solver parrondo pascal \
	primal-test qsort-demo regex-parser shortest-path sieve simple-grep skeleton strange topo-sort \
	totient weekday health_check



CFLAGS = -Wall -Wno-strict-aliasing $(TARGET_CFLAGS) $(LOCAL_CFLAGS) -I../common/ -I../target/
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


run-sim: $(TARGET_EXE)
	@echo "\033[0;34m"
	$(TARGET_SIM) ./$(TARGET_EXE)
	@echo "\033[0m"

%.o: %.c
	$(TARGET_CC) $(CFLAGS) -I../common/ -I../target/ -o $@ -c $<

../common/libmin.a: $(LIBMIN_OBJS)
	$(TARGET_AR) rcs ../common/libmin.a $(LIBMIN_OBJS)



LINKER_MACROS = -DPROGRAM_START=$(PROGRAM_START) -DPROGRAM_LENGTH=$(PROGRAM_LENGTH)\
  -DHEAP_START=$(HEAP_START) -DHEAP_LENGTH=$(HEAP_LENGTH)\
	-DSTACK_START=$(STACK_START) -DSTACK_LENGTH=$(STACK_LENGTH)\

../target/spike-map-prep.ld: ../target/spike-map.ld
	riscv64-unknown-elf-cpp $(LINKER_MACROS) -P $< > $@


$(TARGET_EXE): $(OBJS) $(LIBS) $(TARGET_EXTRA_DEPS)
	$(TARGET_CC) $(CFLAGS) -T ../target/spike-map-prep.ld $(OBJS) ../target/spike-crt0.S -o $@ $(LIBS) $(TARGET_LIBS)


clean:
	rm -f $(PROG).host $(PROG).sa $(PROG).elf *.o ../common/*.o ../target/*.o ../target/spike-map-prep.ld\
	 ../common/libmin.a *.d ../common/*.d core mem.out *.log FOO $(LOCAL_CLEAN) $(TARGET_CLEAN)


#
# top-level Makefile interfaces
#

run-tests:
	@for _BMARK in $(TARGET_BMARKS) ; do \
	  cd $$_BMARK ; \
	  echo "--------------------------------" ; \
	  echo "Running "$$_BMARK"              " ; \
	  echo "--------------------------------" ; \
	  $(MAKE) clean build test || exit 1; \
	  cd .. ; \
	done

build-all:
	@for _BMARK in $(TARGET_BMARKS) ; do \
		cd $$_BMARK ; \
		echo "--------------------------------" ; \
		echo "Building "$$_BMARK"             " ; \
		echo "--------------------------------" ; \
		$(MAKE) build ; \
		cd .. ; \
	done

run-sims:
	@for _BMARK in $(TARGET_BMARKS) ; do \
		cd $$_BMARK ; \
		echo "--------------------------------" ; \
		echo "Running "$$_BMARK"              " ; \
		echo "--------------------------------" ; \
		$(MAKE) clean build run-sim; \
		cd .. ; \
	done


clean-all all-clean:
	@for _BMARK in $(TARGET_BMARKS) ; do \
		cd $$_BMARK ; \
		echo "--------------------------------" ; \
		echo "Cleaning "$$_BMARK"             " ; \
		echo "--------------------------------" ; \
		$(MAKE) TARGET=$$_TARGET clean ; \
		cd .. ; \
	done


openocd:
	openocd -f $(CURDIR)/openocd.cfg
