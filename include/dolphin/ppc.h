#ifndef DOLPHIN_PPC_H
#define DOLPHIN_PPC_H

// Special purpose register numbers for the Gekko.
//
// These are written by number rather than by name in every asm block in the
// project, because the inline assembler is not relied on to know a mnemonic for
// any of them. Collected here so the same register cannot end up with two
// spellings in two files, which is what happened with the quantization
// registers before this header existed.

// Machine state and exception handling.
#define SPR_SRR0 26
#define SPR_SRR1 27
#define SPR_DSISR 18
#define SPR_DAR 19
#define SPR_DEC 22
#define SPR_SDR1 25
#define SPR_EAR 282

// Scratch registers the SDK uses for its own bookkeeping.
#define SPR_SPRG0 272
#define SPR_SPRG1 273
#define SPR_SPRG2 274
#define SPR_SPRG3 275

// Hardware implementation dependent registers.
#define SPR_HID0 1008
#define SPR_HID1 1009
#define SPR_HID2 920
#define SPR_PVR 287

// Write gather pipe and the locked cache.
#define SPR_WPAR 921
#define SPR_DMA_U 922
#define SPR_DMA_L 923
#define SPR_L2CR 1017

// Breakpoint address registers.
#define SPR_IABR 1010
#define SPR_DABR 1013

// Performance monitor.
#define SPR_MMCR0 952
#define SPR_MMCR1 956
#define SPR_PMC1 953
#define SPR_PMC2 954
#define SPR_PMC3 957
#define SPR_PMC4 958
#define SPR_SIA 955
#define SPR_SDA 959

// Thermal management.
#define SPR_THRM1 1020
#define SPR_THRM2 1021
#define SPR_THRM3 1022
#define SPR_ICTC 1019

// Paired single graphics quantization registers.
#define SPR_GQR0 912
#define SPR_GQR1 913
#define SPR_GQR2 914
#define SPR_GQR3 915
#define SPR_GQR4 916
#define SPR_GQR5 917
#define SPR_GQR6 918
#define SPR_GQR7 919

// Block address translation pairs, instruction side then data side.
#define SPR_IBAT0U 528
#define SPR_IBAT0L 529
#define SPR_IBAT1U 530
#define SPR_IBAT1L 531
#define SPR_IBAT2U 532
#define SPR_IBAT2L 533
#define SPR_IBAT3U 534
#define SPR_IBAT3L 535
#define SPR_DBAT0U 536
#define SPR_DBAT0L 537
#define SPR_DBAT1U 538
#define SPR_DBAT1L 539
#define SPR_DBAT2U 540
#define SPR_DBAT2L 541
#define SPR_DBAT3U 542
#define SPR_DBAT3L 543

// The external interrupt enable bit of the machine state register.
#define MSR_EE 0x8000

#endif
