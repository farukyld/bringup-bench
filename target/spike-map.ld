/* Copyright lowRISC contributors.
   Licensed under the Apache License, Version 2.0, see LICENSE for details.
   SPDX-License-Identifier: Apache-2.0 */

OUTPUT_ARCH(riscv)

MEMORY
{

    program     : ORIGIN = PROGRAM_START, LENGTH = PROGRAM_LENGTH
    stack       : ORIGIN = STACK_START,   LENGTH = STACK_LENGTH
    heap        : ORIGIN = HEAP_START,    LENGTH = HEAP_LENGTH
}

/* Stack information variables */
_min_stack      = 0x2000;   /* 8K - minimum stack space to reserve */
_stack_len     = LENGTH(stack);
_stack_start   = ORIGIN(stack) + LENGTH(stack);
_heap_start    = ORIGIN(heap); /* stack goes top to bottom, heap goes bottom to top */

ENTRY(_entry_start)

SECTIONS
{
    .vectors :
    {   
        _entry_start = .;
        . = ALIGN(4);
        KEEP(*(.entry))
        _vectors_start = .;
        KEEP(*(.vectors))
        _vectors_end = .;
    } > program

    .text : {
        . = ALIGN(4);
        *(.text)
        *(.text.*)
    }  > program

    .rodata : {
        . = ALIGN(4);
        /* Small RO data before large RO data */
        *(.srodata)
        *(.srodata.*)
        *(.rodata);
        *(.rodata.*)
    } > program

    .data : {
        . = ALIGN(4);
        /* Small data before large data */
        *(.sdata)
        *(.sdata.*)
        *(.data);
        *(.data.*)
        _content_start = .;
        KEEP(*(.content))
        _content_end = .;
        _index_start = .;
        KEEP(*(.index))
        _index_end = .;
    } > program

    .bss :
    {
        . = ALIGN(4);
        _bss_start = .;
        /* Small BSS before large BSS */
        *(.sbss)
        *(.sbss.*)
        *(.bss)
        *(.bss.*)
        *(COMMON)
        _bss_end = .;
    } > program

    /* ensure there is enough room for stack */
    .stack (NOLOAD): {
        . = ALIGN(4);
        . = . + _min_stack ;
        . = ALIGN(4);
        stack = . ;
        _stack = . ;
    } > stack /*? stack burda STACK_LENGTH mi oluyor, min_stack mi oluyor?*/

    .heap (NOLOAD):
    {
        . = ALIGN(4);
        . = . + HEAP_LENGTH;
        . = ALIGN(4);
    } > heap
}
