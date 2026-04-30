/* Generated linker script for esp32. */
/* REGION_TEXT=ROM; REGION_DATA=DRAM */

MEMORY
{
  DRAM (rwx) : ORIGIN = 0x3FFAA000, LENGTH = 0x50000
  ROM (rx) : ORIGIN = 0x40000000, LENGTH = 0x60000
  IRAM (rwx) : ORIGIN = 0x40080000, LENGTH = 0x20000
}

REGION_ALIAS("REGION_TEXT", ROM);
REGION_ALIAS("REGION_DATA", DRAM);
REGION_ALIAS("REGION_BSS", DRAM);
REGION_ALIAS("REGION_STACK", DRAM);

__stack_size = DEFINED(__stack_size) ? __stack_size : 0x1000;

SECTIONS
{
  .vectors :
  {
    KEEP(*(.vectors))
    KEEP(*(.isr_vector))
    KEEP(*(.interrupt_vectors))
  } > REGION_TEXT

  .text :
  {
    *(.text*)
    *(.rodata*)
    *(.glue_7*)
    *(.glue_7t*)
    KEEP(*(.init))
    KEEP(*(.fini))
  } > REGION_TEXT

  .init_array :
  {
    __init_array_start = .;
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array))
    __init_array_end = .;
  } > REGION_TEXT

  .fini_array :
  {
    __fini_array_start = .;
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array))
    __fini_array_end = .;
  } > REGION_TEXT

  .data :
  {
    . = ALIGN(4);
    __data_start__ = .;
    *(.data*)
    . = ALIGN(4);
    __data_end__ = .;
  } > REGION_DATA AT> REGION_TEXT
  __data_load_start__ = LOADADDR(.data);

  .bss (NOLOAD) :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } > REGION_BSS

  .stack ORIGIN(REGION_STACK) + LENGTH(REGION_STACK) - __stack_size (NOLOAD) :
  {
    . = ALIGN(8);
    __stack_limit = .;
    . += __stack_size;
    __stack_top = .;
  } > REGION_STACK
}

ASSERT(__stack_limit >= __bss_end__, "RAM overflow: .bss/.data overlap stack");
