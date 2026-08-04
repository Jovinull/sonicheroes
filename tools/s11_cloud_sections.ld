SECTIONS
{
    .text 0 : { *(.text) }
    .ctors 0 : { *(.ctors) }
    .rodata 0 : { *(.rodata) *(.cloudbias) *(.cloudtail) }
    .data 0 : { *(.data) }
    .bss 0 : { *(.bss) }
    .comment 0 : { *(.comment) }
}
