NOT1: bu dosyadaki komutlar test edilmemiştir.

NOT2: libmin.h'yi libmin'i kullanacak olan dosyalarda `#include`lamalı ve bu header'da tanımlanan makro ve türleri ve prototiplenen fonksiyonları içeren diğer header'ların `#include`lanmasını kaldırmalısınız. 

Bunun için benchmark kodlarında standard header'ları içeren kod dosyalarında şu şekilde koşullu derleme yapabilirsiniz:
```c
#ifndef TARGET_SPIKE
#include <stdio.h>
#else
#include "libmin.h"
#endif
```
`TARGET_SPIKE` makrosu aşağıda verilecek olan Makefile örneğinde derleme kurallarında tanımlanmaktadır.

NOT3: Derleme sırasında "multiple definition of macro ..." veya "multiple declaration of function ..." veya "confilicting types for ..." veya "multiple definition of type ..." veya "... is undeclared in this scope" gibi hataların NOT2'de bahsedilen durumdan kaynaklanıyor olma ihtimali büyük.

libmin'i farklı bir benchmark'ı baremetal olarak çalıştırmak için aşağıdaki düzende
```
|---build
|   |---Makefile
```
Makefile dosyasının içerisine:
```Makefile
###################################
#    AYARLANABILIR PARAMETRELER   #
###################################
# 8000_0000 program ( .vector .text .data .bss) - stack - heap
PROGRAM_START          :=0x80000000
PROGRAM_LENGTH         :=0xbd0000
STACK_LENGTH           :=0x8000
HEAP_LENGTH            :=0xf000000

# UART_BASE tanimliysa 
# uart_putchar'in karakterleri bastigi degisken olan uart_base'in adresi
# link asamasinda yeniden tanimlanir: ld --defsym=uart_base=$(UART_BASE)
# aksi takdirde kodun icinde weak olarak tanimlanan degisken
# linker tarafindan otomatik olarak uygun bir yere yerlestirilir. 
UART_BASE              :=0x10000000
HARD_FLOAT             :=0
GDB_DEBUG              :=0
COMPILE_DEBUG          :=1
SPIKE_INTERAC          :=0
USE_EXTERNAL_QSORT     :=0
PREPROCESS_TARGET      :=
PRINT_MAX_HEAP_ON_EXIT :=1
SPIKE_OUT_FILE         :=

# benchmark proje dizini
ROOT                   :=..

# benchmark kaynak dosyalari
SRC                    :=$(ROOT)/src

# eger USE_EXTERNAL_QSORT=0 ise bu asagidaki degisken onemsizdir
# NOT: EXT_QSORT_LOCATION'daki dosyalarin derleme kurallari 
# LIBMIN bolumunde mevcuttur.
EXT_QSORT_LOCATION     :=$(SRC)/qsort


########################################################
#        BENCHMARK OBJECT DOSYALARI DERLENMESI         #
########################################################
# bu kisim kullanici tarafindan degistirilebilir

$(BENCHMARK_INC)       :=-I$(SRC)
ifeq ($(USE_EXTERNAL_QSORT),1)
$(BENCHMARK_INC)       += -I$(SRC)/qsort
endif

BENCH_FILES_CPP               := $(wildcard $(SRC)/*.cpp)
BENCH_FILES_S                 := $(wildcard $(SRC)/*.S)

BENCH_OBJS  := $(patsubst %.cpp, $(BUILD)/%.o, $(notdir $(BENCH_FILES_CPP)))
BENCH_OBJS  += $(patsubst %.S, $(BUILD)/%.o, $(notdir $(BENCH_FILES_S)))
BENCH_DEPS  := $(patsubst %.o, $(BUILD)/%.d, $(notdir $(BENCH_OBJS)))

-include $(BENCH_DEPS)

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: $(SRC)/%.S
	$(CC) $(CFLAGS) -c $< -o $@


####################################
# RENKLER
VSY:=\033[0m
YSL:=\033[32m
SAR:=\033[33m
MAV:=\033[34m
TRK:=\033[36m


help:
	@echo "$(YSL)make komutuyla verilebilecek bazi argumanlar:$(VSY)"
	@echo "    $(TRK)HARD_FLOAT$(VSY)=1       hardware float kullanacak sekilde derle."
	@echo "                       etkiledigi kurallar: derleme kurallari, disassembled.s"
	@echo "                       varsayilan: HARD_FLOAT=$(HARD_FLOAT)"
	@echo "   "
	@echo "    $(TRK)GDB_DEBUG$(VSY)=1        gdb ile debug'lanabilecek sekilde derle ve simulasyon yap"
	@echo "                       etkiledigi kurallar: derleme kurallari, disassembled.s, run"
	@echo "                       varsayilan: GDB_DEBUG=$(GDB_DEBUG)"
	@echo "   "
	@echo "    $(TRK)COMPILE_DEBUG$(VSY)=1        derlenen dosyalarda debug info bulundur"
	@echo "                       etkiledigi kurallar: derleme kurallari, disassembled.s"
	@echo "                       varsayilan: COMPILE_DEBUG=$(COMPILE_DEBUG)"
	@echo "   "
	@echo "    $(TRK)SPIKE_INTERAC$(VSY)=1    spike interactive mod'da calistirilsin."
	@echo "                       etkiledigi kurallar: run"
	@echo "                       varsayilan: SPIKE_INTERAC=$(SPIKE_INTERAC)"
	@echo "   "
	@echo "    $(TRK)USE_EXTERNAL_QSORT$(VSY)=0   qsort fonksiyonu icin libmin'dekini kullan"
	@echo "                       etkiledigi kurallar: derleme kurallari"
	@echo "                       varsayilan: USE_EXTERNAL_QSORT=$(USE_EXTERNAL_QSORT)"
	@echo "   "
	@echo "    $(TRK)EXT_QSORT_LOCATION$(VSY)=dir   libmin kutuphanesindeki haricinde kullanmak istediginiz qsort kodlarinin/kodunun konumu. USE_EXTERNAL_QSORT=0 ise gormezden gelinir."
	@echo "                       etkiledigi kurallar: derleme kurallari"
	@echo "                       varsayilan: EXT_QSORT_LOCATION=$(EXT_QSORT_LOCATION)"
	@echo "   "
	@echo "    $(TRK)PREPROCESS_TARGET$(VSY)=file.c"
	@echo "                       file.c, c preprocessor'u kullanilarak ve derleyiciye gonderilen include path'leri kullanilarak preprocess edilsin"
	@echo "                       etkiledigi kurallar: preprocess"
	@echo "                       varsayilan: PREPROCESS_TARGET=$(PREPROCESS_TARGET)"
	@echo "   "
	@echo "    $(TRK)PRINT_MAX_HEAP_ON_EXIT$(VSY)=0"
	@echo "                       programi bitirirken heap_ptr en fazla kac deger almis bastir."
	@echo "                       etkiledigi kurallar: derleme kurallari"
	@echo "                       varsayilan: PRINT_MAX_HEAP_ON_EXIT=$(PRINT_MAX_HEAP_ON_EXIT)"
	@echo "   "
	@echo "    $(TRK)SPIKE_OUT_FILE$(VSY)=out_file"
	@echo "                       (eski) spike'in standard out'unu verilen dosyaya yonlendir. (--log=file flag'i degil sadece spike elf_file > out_file)"
	@echo "                       etkiledigi kurallar: run"
	@echo "                       varsayilan: SPIKE_OUT_FILE=$(SPIKE_OUT_FILE)"
	@echo "   "

	@echo "$(YSL)bazi kurallar:$(VSY)"
	@echo "    $(SAR)preprocess$(VSY):        c preprocessor'u ile verilen dosyayi preprocess et."
	@echo "   "
	@echo "    $(SAR)disassembled.s$(VSY):    elf dosyasini olustur ve .text section'unu disassemble'layip disassembled.s dosyasina yaz."
	@echo "   "
	@echo "    $(SAR)run$(VSY):               spike ile simulasyonu calistir."
	@echo "    $(SAR)openocd$(VSY):           (eski) openocd calistir, konfigurasyonlar ROOT/openocd_conf.cfg'den okunmaktadir. bu komutu run'dan ayri bir terminal'de calistirmalisiniz. run'dan sonra calistirmalisiniz."
	@echo "    $(SAR)gdb$(VSY):               (eski) gdb'yi calistir. bu komutu openocd'yi calistirdiktan sonra calistirmalisiniz. yine ayri bir terminal'de calistirmalisiniz."


###########################
#         DIZINLER        #
###########################
# NOT: su an bu Makefile dosyasi, build dizininin icinde bulunmasi gerekiyor.

BUILD   :=.
RUN_DIR :=$(ROOT)/run_spike

$(RUN_DIR):
	mkdir -p $(RUN_DIR)

#bringup-bench
BRINGUP_BENCH_DIR :=

ifeq ($(BRINGUP_BENCH_DIR), )
$(error BRINGUP_BENCH_DIR degiskenini bringup-bench\
 dizinini gosterecek sekilde ayarlamalisiniz)
endif

# bringup-bench/common
LIBMIN_D       := $(BRINGUP_BENCH_DIR)/common

# bringup-bench/target
TARGET_D       := $(BRINGUP_BENCH_DIR)/target


############################
#   DERLEYICI VE FLAGLER   #
############################

CC := riscv64-unknown-elf-gcc
CXX := riscv64-unknown-elf-g++
PP := riscv64-unknown-elf-cpp
AR := riscv64-unknown-elf-ar

ifeq ($(or $(COMPILE_DEBUG), $(GDB_DEBUG)), 1)
DBG_OPT_FLAGS := -g -Og
else
DBG_OPT_FLAGS := -O3
endif

ifeq ($(GDB_DEBUG), 1)
GDB_DBG_MAC   := -DGDB_DEBUG=1
else
GDB_DBG_MAC := -DGDB_DEBUG=0
endif

ifeq ($(HARD_FLOAT), 1)
MARCH_MABI := -march=rv64imfdc_zicsr -mabi=lp64d
HARDF_MAC  := -DHARD_FLOAT
else
MARCH_MABI := -march=rv64imc_zicsr -mabi=lp64
HARDF_MAC  :=
endif

INC := -I$(LIBMIN_D) -I$(TARGET_D) $(BENCHMARK_INC)

# -static -ffreestanding -nostartfiles
# -ffreestanding __int64_t_defined macro'sunun tanimlanmamasina sebep oluyor.
# o flag'i kaldirdim. gerekli olduguna dair bir delil bulamadim.
PREPFLAGS          := $(HARDF_MAC) -DTARGET_SPIKE -DALIAS_RM_LIBMIN \
  -DPRINT_CYCLES_ON_EXIT \
  -DUSE_EXTERNAL_QSORT=$(USE_EXTERNAL_QSORT) -DHEAP_LENGTH=$(HEAP_LENGTH)\
  -DPRINT_MAX_HEAP_ON_EXIT=$(PRINT_MAX_HEAP_ON_EXIT)\
  $(GDB_DBG_MAC) $(INC) -MMD -MP
COMPILE_LINK_FLAGS := -Wall $(DBG_OPT_FLAGS) $(MARCH_MABI)\
  -static -nostartfiles -nostdlib -fno-builtin -fPIC
CFLAGS             := $(PREPFLAGS) $(COMPILE_LINK_FLAGS)
# NOT: aslinda bu flag'lerde daha ayrintili bir ayrim da yapilabilir 
# her kural grubu sadece gerekli flag'leri alir. 
# linkleme, libmin derleme, benchmark derleme
# ama vakit kaybi. ve ilerde hataya sebep olmayacagini garanti edemem.


###########################
#          LIBMIN         #
###########################

LIBMIN_SRCS  := $(wildcard $(LIBMIN_D)/*.c)
LIBTARG_SRCS := $(wildcard $(TARGET_D)/*.c)
ifeq ($(USE_EXTERNAL_QSORT),1)
EXTERNAL_QSORT_SRCS := $(wildcard $(EXT_QSORT_LOCATION)/*.c)
endif

LIBMIN_OBJS := $(patsubst %.c, $(BUILD)/%.o, $(notdir $(LIBMIN_SRCS)))
LIBMIN_OBJS += $(patsubst %.c, $(BUILD)/%.o, $(notdir $(EXTERNAL_QSORT_SRCS)))
LIBMIN_OBJS += $(patsubst %.c, $(BUILD)/%.o, $(notdir $(LIBTARG_SRCS)))

LIBMIN_DEPS := $(patsubst %.o, %.d, $(LIBMIN_OBJS))

LIBMIN      := $(BUILD)/libmin.a

-include $(LIBMIN_DEPS)

AR         := riscv64-unknown-elf-ar

# derleme kurallari
$(BUILD)/%.o: $(LIBMIN_D)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: $(EXT_QSORT_LOCATION)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: $(TARGET_D)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBMIN): $(LIBMIN_OBJS)
	$(AR) rcs $@ $^

#######################
# C RUNTIME DOSYASI   #
#######################

CRUNTIME_FILE := $(TARGET_D)/spike-crt0.S

CRUNTIME_OBJ  := $(patsubst %.S, $(BUILD)/%.o, $(notdir $(CRUNTIME_FILE)))
CRUNTIME_DEP  := $(patsubst %.o, %.d, $(CRUNTIME_OBJ))

# kendime NOT: yukarida CRUNTIME_FILE'da wildcard kullanip kullanmamam onemli degil
# derleme kuralinda % isaretini kullanmazsam (sagda varsa solda da olacak)
# sacmaliyor. ya da % isaretini hic kullanmayacagim
$(BUILD)/%.o: $(TARGET_D)/%.S
	$(CC) $(CFLAGS) -c $< -o $@

-include $(CRUNTIME_DEP)

######################################
#         EXECUTABLE OLUSTURMA       #
######################################

EXEC   :=$(BUILD)/prog.elf

# Default target
all: $(EXEC)

STACK_START    := $(shell printf "0x%X\n" $$(($(PROGRAM_START) + $(PROGRAM_LENGTH))))
HEAP_START     := $(shell printf "0x%X\n" $$(($(STACK_START) + $(STACK_LENGTH))))
MEM_START      := $(PROGRAM_START)
MEM_LENGTH     := $(shell printf "0x%X\n" $$(($(PROGRAM_LENGTH) + $(HEAP_LENGTH) + $(STACK_LENGTH))))


LD_PREP_MACS = -DPROGRAM_START=$(PROGRAM_START) -DPROGRAM_LENGTH=$(PROGRAM_LENGTH)\
  -DHEAP_START=$(HEAP_START) -DHEAP_LENGTH=$(HEAP_LENGTH)\
  -DSTACK_START=$(STACK_START) -DSTACK_LENGTH=$(STACK_LENGTH)\

$(BUILD)/spike-map-prep.ld: $(TARGET_D)/spike-map.ld
	$(PP) $(LD_PREP_MACS) -P $< > $@

# TRACE_LIST := _ZNSt11char_traitsIcE4findEPKcmRS1_ find abort memchr getenv _impure_ptr __unorddf2
TRACE_LIST :=
COMMA := ,
TRACE_ARG  := $(patsubst %, -Wl$(COMMA)--trace-symbol=%, $(TRACE_LIST))

ifneq ($(UART_BASE),)
UART_BASE_OWR := -Wl,--defsym=uart_base=$(UART_BASE)
else
UART_BASE_OWR :=
endif
# Rule to link the object files to create the executable
$(EXEC): $(BENCH_OBJS) $(CRUNTIME_OBJ) $(LIBMIN) $(BUILD)/spike-map-prep.ld
	$(CXX) $(CFLAGS) $(TRACE_ARG) $(BENCH_OBJS) $(CRUNTIME_OBJ)\
   $(UART_BASE_OWR)\
   -T $(BUILD)/spike-map-prep.ld -o $@ -lm -lstdc++ $(LIBMIN) -lgcc


######################################
#              SIMULASYON            #
######################################

ifeq ($(SPIKE_INTERAC),1)
DEBUG_FLAG:=-d
else
DEBUG_FLAG:=
endif

ifeq ($(GDB_DEBUG), 1)
RBB_PORT:= --rbb-port=9824
else
RBB_PORT:=
endif

ifeq ($(SPIKE_OUT_FILE),)
SPIKE_REDIRECT :=
else
SPIKE_REDIRECT := 1> $(SPIKE_OUT_FILE)
endif

RUN_COMMAND := $(SPIKE_ORIG)/build/spike $(DEBUG_FLAG) $(RBB_PORT)\
 -m$(MEM_START):$(MEM_LENGTH) $(EXEC)

run: $(EXEC) $(RUN_DIR)
	$(RUN_COMMAND) $(SPIKE_REDIRECT)


######################################
#                 EK                 #
######################################

# Phony targets
.PHONY: all clean  preprocess

disassembled.s: $(EXEC)
	riscv64-unknown-elf-objdump --visualize-jumps=extended-color -D -j .text $< > $@; code $@


preprocess:
ifeq ($(PREPROCESS_TARGET),)
	@echo usage:
	@echo make preprocess PREPROCESS_TARGET=file.c
else
	$(PP) -DTARGET_SPIKE $(INC) $(PREPROCESS_TARGET) > $(notdir $(PREPROCESS_TARGET)).prep.c
endif


OPENOCD_COMMAND := openocd -f $(ROOT)/openocd.cfg

openocd: $(RUN_DIR)
	$(OPENOCD_COMMAND)


GDB :=riscv64-unknown-elf-gdb
GDB_FLAGS:=\
  -tui\
  -ex "file $(EXEC)"\
  -ex "target extended-remote :3333"\
  -ex "print wait=0"\
  -ex "b default_exc_handler"\
  -ex "b reset_handler"\
  -ex "focus cmd" \
  -ex "c"\

GDB_COMMAND:=$(GDB) $(GDB_FLAGS)

gdb:
	$(GDB_COMMAND)


KILL_COMMAND:= pkill spike; pkill openocd
kill_bg_spike_openocd:
	$(KILL_COMMAND)
# Clean up generated files
clean:
	rm -f $(shell find $(BUILD) -not -name 'Makefile' -not -name '.' -not -name '..') $(EXEC) $(LIBMIN)


##########################
# MAKEFILE HATA AYIKLAMA #
##########################

define list-group
$(foreach dir,$(sort $(dir $(1))),\
    $(SAR)$(dir $(dir))$(VSY): \
    $(notdir $(filter $(dir)%,$(1))) \
)
endef


print_variables:
	@echo "$(YSL)BENCH_OBJS$(VSY)=$(call list-group, $(BENCH_OBJS))"
	@echo "$(YSL)BENCH_DEPS$(VSY)=$(call list-group, $(BENCH_DEPS))"

```