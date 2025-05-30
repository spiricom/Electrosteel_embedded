/**
 ******************************************************************************
 * @file      LinkerScript.ld
 * @author    Auto-generated by STM32CubeIDE
 * @brief     Linker script for STM32H743ZITx Device from STM32H7 series
 *                      2048Kbytes FLASH
 *                      128Kbytes DTCMRAM
 *                      64Kbytes ITCMRAM
 *                      512Kbytes RAM_D1
 *                      288Kbytes RAM_D2
 *                      64Kbytes RAM_D3
 *
 *            Set heap size, stack size and stack location according
 *            to application requirements.
 *
 *            Set memory bank area and size if external memory is used
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = 0x20020000;    /* end of RAM */

_Min_Heap_Size = 0x3000;	/* required amount of heap  */
_Min_Stack_Size = 0x3000;	/* required amount of stack */

/* Memories definition */
MEMORY
{
  DTCMRAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 128K
	ITCMRAM (RWX) : ORIGIN = 0x00000000, LENGTH = 1K
	ITCMRAMFUNC (RWX) : ORIGIN = 0x00000400, LENGTH = 63K
	SRAM (RWX)    : ORIGIN =      0x24000000, LENGTH = 256K
	RAM_D1 (RWX)    : ORIGIN =    0x24040000, LENGTH = 256K
	RAM_D2_DMA (RWX) : ORIGIN =   0x30000000, LENGTH = 8K
	RAM_D2 (RWX)  : ORIGIN =      0x30002000, LENGTH = 280K
	RAM_D3 (RWX)  : ORIGIN =      0x38000000, LENGTH = 64K
	BACKUP_SRAM (RWX)  : ORIGIN = 0x38800000, LENGTH = 4K
  FLASH (rx)      : ORIGIN = 0x8000000, LENGTH = 1792K
  FIXED_DATA(rw)  : ORIGIN = 0x81E0000, LENGTH = 256K
  SDRAM (rx)      : ORIGIN = 0x60000000, LENGTH = 32M
}

/* Sections */
SECTIONS
{
  /* The startup code into "FLASH" Rom type memory */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* The program code and other data into "FLASH" Rom type memory */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data into "FLASH" Rom type memory */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  .ARM.extab   : { 
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } >FLASH
  
  .ARM : {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } >FLASH

  .preinit_array     :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } >FLASH
  
  .init_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } >FLASH
  
  .fini_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } >FLASH

  /* Used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections into "RAM_D1" Ram type memory */
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
    
  } >DTCMRAM AT> FLASH

  /* Uninitialized data section into "RAM_D1" Ram type memory */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >DTCMRAM

	.sram1_bss (NOLOAD) :
	{
		. = ALIGN(4);
		_ssram1_bss = .;

		PROVIDE(__sram1_bss_start__ = _sram1_bss);
		*(.sram1_bss)
		*(.sram1_bss*)
		. = ALIGN(4);
		_esram1_bss = .;

		PROVIDE(__sram1_bss_end__ = _esram1_bss);
	} > RAM_D1


	.sram2_dma_bss (NOLOAD) :
	{
		. = ALIGN(4);
		_ssram2_dma_bss = .;

		PROVIDE(__sram2_dma_bss_start__ = _sram2_dma_bss);
		*(.sram2_dma_bss)
		*(.sram2_dma_bss*)
		. = ALIGN(4);
		_esram2_dma_bss = .;

		PROVIDE(__sram2_dma_bss_end__ = _esram2_dma_bss);
	} > RAM_D2_DMA


	.sram2_bss (NOLOAD) :
	{
		. = ALIGN(4);
		_ssram2_bss = .;

		PROVIDE(__sram2_bss_start__ = _sram2_bss);
		*(.sram2_bss)
		*(.sram2_bss*)
		. = ALIGN(4);
		_esram2_bss = .;

		PROVIDE(__sram2_bss_end__ = _esram2_bss);
	} > RAM_D2
	
	.sram3_bss (NOLOAD) :
	{
		. = ALIGN(4);
		_ssram3_bss = .;

		PROVIDE(__sram3_bss_start__ = _sram3_bss);
		*(.sram3_bss)
		*(.sram3_bss*)
		. = ALIGN(4);
		_esram3_bss = .;

		PROVIDE(__sram3_bss_end__ = _esram3_bss);
	} > RAM_D3
	
	.userflash (NOLOAD) :
	{    
        . = ALIGN(4);
        KEEP(*(.userflash))
        . = ALIGN(4);
	} > BACKUP_SRAM


	 .itcmram :
	  {
	   

	    . = ALIGN(4);
		_sitcmram = .;
		 PROVIDE(__itcmram_start__ = _sitcmram);
	    *(.itcmram)         /* .section_name section */
	    *(.itcmram*)        /* .section_name* sub-sections if any */
	    . = ALIGN(4);
	    _eitcmram = .;
	    PROVIDE(__itcmram_end__ = _eitcmram);
	  } >ITCMRAMFUNC AT> FLASH
	  
	  _siitcmram = LOADADDR(.itcmram);

	.sdram_bss (NOLOAD) :
	{
		. = ALIGN(4);
		_ssdram_bss = .;

		PROVIDE(__sdram_bss_start = _ssdram_bss);
		*(.sdram_bss)
		*(.sdram_bss*)
		. = ALIGN(4);
		_esdram_bss = .;

		PROVIDE(__sdram_bss_end = _esdram_bss);
	} > SDRAM




	.heap (NOLOAD) :
	{
		. = ALIGN(4);
		PROVIDE(__heap_start__ = .);
		KEEP(*(.heap))
		. = ALIGN(4);
		PROVIDE(__heap_end__ = .);
	} > DTCMRAM


	.reserved_for_stack (NOLOAD) :
	{
		. = ALIGN(4);
		PROVIDE(__reserved_for_stack_start__ = .);
		KEEP(*(.reserved_for_stack))
		. = ALIGN(4);
		PROVIDE(__reserved_for_stack_end__ = .);
	} > DTCMRAM


	PROVIDE(end = .);
	
    DISCARD :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }

}
