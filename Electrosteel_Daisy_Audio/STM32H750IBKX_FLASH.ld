/* Generated by LinkerScriptGenerator [http://visualgdb.com/tools/LinkerScriptGenerator]
 * Target: STM32H750IB
 * The file is provided under the BSD license.
 */

ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(DTCMRAM) + LENGTH(DTCMRAM);    /* end of RAM */
/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x4000;      /* required amount of heap  */
_Min_Stack_Size = 0x8000; /* required amount of stack */

MEMORY
{
	FLASH (RX)    : ORIGIN =      0x08000000, LENGTH = 128K
	DTCMRAM (RWX) : ORIGIN =      0x20000000, LENGTH = 128K
	SRAM (RWX)    : ORIGIN =      0x24000000, LENGTH = 256K
	RAM_D1 (RWX)    : ORIGIN =    0x24040000, LENGTH = 256K
	RAM_D2_DMA (RWX) : ORIGIN =   0x30000000, LENGTH = 8K
	RAM_D2 (RWX)  : ORIGIN =      0x30002000, LENGTH = 280K
	RAM_D3 (RWX)  : ORIGIN =      0x38000000, LENGTH = 64K
	BACKUP_SRAM (RWX)  : ORIGIN = 0x38800000, LENGTH = 4K
	ITCMRAM (RWX) : ORIGIN =      0x00000000, LENGTH = 1K
	ITCMRAMFUNC (RWX) : ORIGIN =  0x00000400, LENGTH = 63K
	SDRAM (RWX)   : ORIGIN =      0xc0000000, LENGTH = 64M
  	QSPIFLASH (RX): ORIGIN =      0x90040000, LENGTH = 7936K

}


SECTIONS
{
	.isr_vector :
	{
		. = ALIGN(4);
		KEEP(*(.isr_vector))
		. = ALIGN(4);
	} > SRAM

	.text :
	{
		. = ALIGN(4);
		_stext = .;

		*(.text)
		*(.text*)
		*(.rodata)
		*(.rodata*)
		*(.glue_7)
		*(.glue_7t)
		KEEP(*(.init))
		KEEP(*(.fini))
		. = ALIGN(4);
		_etext = .;

	} > SRAM

	.ARM.extab :
	{
		. = ALIGN(4);
		*(.ARM.extab)
		*(.gnu.linkonce.armextab.*)
		. = ALIGN(4);
	} > SRAM

	.exidx :
	{
		. = ALIGN(4);
		PROVIDE(__exidx_start = .);
		*(.ARM.exidx*)
		. = ALIGN(4);
		PROVIDE(__exidx_end = .);
	} > SRAM

	.ARM.attributes :
	{
		*(.ARM.attributes)
	} > SRAM

	.preinit_array :
	{
		PROVIDE(__preinit_array_start = .);
		KEEP(*(.preinit_array*))
		PROVIDE(__preinit_array_end = .);
	} > SRAM

	.init_array :
	{
		PROVIDE(__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array*))
		PROVIDE(__init_array_end = .);
	} > SRAM

	.fini_array :
	{
		PROVIDE(__fini_array_start = .);
		KEEP(*(.fini_array*))
		KEEP(*(SORT(.fini_array.*)))
		PROVIDE(__fini_array_end = .);
	} > SRAM

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
	
	.data :
	{
		. = ALIGN(4);
		_sdata = .;

		PROVIDE(__data_start__ = _sdata);
		*(.data)
		*(.data*)
		. = ALIGN(4);
		_edata = .;

		PROVIDE(__data_end__ = _edata);
	} > DTCMRAM AT > SRAM

	_sidata = LOADADDR(.data);

	.bss (NOLOAD) :
	{
		. = ALIGN(4);
		_sbss = .;

		PROVIDE(__bss_start__ = _sbss);
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;

		PROVIDE(__bss_end__ = _ebss);
	} > DTCMRAM 


	/* add a section that we can put functions into ITCMRAM for faster execution 
	(quicker bus speed than executing from AXI-SRAM but only 64k of space) 
	*/
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
	  } >ITCMRAMFUNC AT> SRAM
	  
	  _siitcmram = LOADADDR(.itcmram);
	  	
	/*
	.sdram_text :
	{
		. = ALIGN(4);
		_ssdram_text = .;

		PROVIDE(__sdram_text_start = _ssdram_text);
		*(.sdram_text)
		*(.sdram_text*)
		. = ALIGN(4);
		_esdram_text = .;

		PROVIDE(__sdram_text_end = _esdram_text);
	} > SDRAM AT >FLASH
	_sisdram_text = LOADADDR(.sdram_text);
	*/

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


    .qspiflash_text :
	{
		. = ALIGN(4);
		_sqspiflash_text = .;

		PROVIDE(__qspiflash_text_start = _sqspiflash_text);
		*(.qspiflash_text)
		*(.qspiflash_text*)
		. = ALIGN(4);
		_eqspiflash_text = .;

		PROVIDE(__qspiflash_text_end = _eqspiflash_text);
	} > QSPIFLASH

	.qspiflash_data :
	{
		. = ALIGN(4);
		_sqspiflash_data = .;

		PROVIDE(__qspiflash_data_start = _sqspiflash_data);
		*(.qspiflash_data)
		*(.qspiflash_data*)
		. = ALIGN(4);
		_eqspiflash_data = .;

		PROVIDE(__qspiflash_data_end = _eqspiflash_data);
	} > QSPIFLASH

	.qspiflash_bss (NOLOAD) :
	{
		. = ALIGN(4);
		_sqspiflash_bss = .;

		PROVIDE(__qspiflash_bss_start = _sqspiflash_bss);
		*(.qspiflash_bss)
		*(.qspiflash_bss*)
		. = ALIGN(4);
		_eqspiflash_bss = .;

		PROVIDE(__qspiflash_bss_end = _eqspiflash_bss);
	} > QSPIFLASH

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