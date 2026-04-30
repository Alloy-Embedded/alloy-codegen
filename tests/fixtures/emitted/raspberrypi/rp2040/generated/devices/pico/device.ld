/* Generated linker script for pico. */
/* REGION_TEXT=XIP_FLASH; REGION_DATA=SRAM */

MEMORY
{
  XIP_FLASH (rx) : ORIGIN = 0x10000000, LENGTH = 0x200000
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x42000
}

REGION_ALIAS("REGION_TEXT", XIP_FLASH);
REGION_ALIAS("REGION_DATA", SRAM);
REGION_ALIAS("REGION_BSS", SRAM);
REGION_ALIAS("REGION_STACK", SRAM);

__stack_size = DEFINED(__stack_size) ? __stack_size : 0x1000;

SECTIONS
{
  /* RP2040 XIP boot stage-2 loader (256 bytes, device-specific). Replace with
     a real boot2 from pico-sdk for your flash chip before running on hardware. */
  .boot2 :
  {
    __boot2_start__ = .;
    KEEP(*(.boot2))
    . = ALIGN(256);
    __boot2_end__ = .;
  } > REGION_TEXT
  __boot2_size__ = __boot2_end__ - __boot2_start__;

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
