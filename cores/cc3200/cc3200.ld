/******************************************************************************
*
*   copyright (c) 2013 texas instruments incorporated
*
*   All rights reserved. Property of Texas Instruments Incorporated.
*   Restricted rights to use, duplicate or disclose this code are
*   granted through contract.
*
*   The program may not be used without the written permission of
*   Texas Instruments Incorporated or against the terms and conditions
*   stipulated in the agreement under which this program has been supplied,
*   and under no circumstances can it be used with non-TI connectivity device.
*
******************************************************************************/

STACK_SIZE = 0x2500;
HEAP_SIZE = 0x9000;/*0x3BF0; /*Original Size: 0x00010000*/
RAM_LOW_SIZE = 0x4000;

MEMORY
{
    SRAM_BIN (rwx)  : ORIGIN = 0x20004000, LENGTH = 0x30000 /*Limit to 196kB (debug-bootloader @0x20004000+0x30000) LENGTH = 0x3C000 */
    SRAM_FULL (rwx) : ORIGIN = 0x20004000, LENGTH = 0x3C000 
    SRAM_LOW (rw)   : ORIGIN = 0x20000000, LENGTH = 0x04000 
}

SECTIONS
{
    /*.bootloader 0x20000000: { KEEP(*(.blsec) }*/

    .text :
    {
        _text = .;
        KEEP(*(.intvecs))
        *(.text*)
        *(.rodata*)
        *(.ARM.extab* .gnu.linkonce.armextab.*)
        
        /* ---ENERGIA C++ Linking Specific-- */

        . = ALIGN(4);
        KEEP(*(.init))
        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(SORT(.preinit_array*)))
        KEEP (*(.preinit_array))
        __preinit_array_end = .;

        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;

        . = ALIGN(4);
        KEEP(*(.fini))

        . = ALIGN(4);
        __fini_array_start = .;
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        __fini_array_end = .;

        /* ---end ENERGIA C++ Linking Specific-- */

        . = ALIGN(8);
        _etext = .;
    } > SRAM_BIN AT > SRAM_FULL

    PROVIDE_HIDDEN (__exidx_start = .);
    .ARM : {
    __exidx_start = .;
      *(.ARM.exidx*)
      __exidx_end = .;
    } > SRAM_BIN AT > SRAM_FULL

    /*__init_data = .;*/

    .data : /*AT(__init_data)*/
    {
        _data = .;
        *(.data*)
	    . = ALIGN (8);
        _edata = .;
    } > SRAM_BIN AT > SRAM_FULL

    .stack : {
        _stack = .;
        . = . + STACK_SIZE;
        . = ALIGN(4);
        _estack = .;
    } > SRAM_FULL

    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM_FULL

    .heap :
    {
        _heap = .;
        . = . + HEAP_SIZE;
        . = ALIGN(8);
        _eheap = .;
    } > SRAM_FULL

    .memoryend :
    {
        . = .;
    } > SRAM_FULL

    .ringbuffer :
    {
        _ringbuffer = .;
	    . = . + RAM_LOW_SIZE;
        _eringbuffer = .;
    } > SRAM_LOW
}

/*PROVIDE(end = _end);*/

