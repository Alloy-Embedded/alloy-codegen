/* Generated linker script for atsame70n21b. */
/* REGION_TEXT=IFLASH; REGION_DATA=IRAM */

MEMORY
{
  ITCM (rwx) : ORIGIN = 0x00000000, LENGTH = 0x20000
  IFLASH (rwx) : ORIGIN = 0x00400000, LENGTH = 0x200000
  IROM (x) : ORIGIN = 0x00800000, LENGTH = 0x4000
  DTCM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x20000
  IRAM (rwx) : ORIGIN = 0x20400000, LENGTH = 0x60000
  QSPIMEM (rwx) : ORIGIN = 0x80000000, LENGTH = 0x20000000
  AXIMX (rw) : ORIGIN = 0xA0000000, LENGTH = 0x100000
}

REGION_ALIAS("REGION_TEXT", IFLASH);
REGION_ALIAS("REGION_DATA", IRAM);
REGION_ALIAS("REGION_BSS", IRAM);
REGION_ALIAS("REGION_STACK", IRAM);

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
