#include "types.h"

// The GameCube side of the debugger nub: bringing the target up, saving and
// restoring the register file across a break, and the nub's entry point.
// Every function in this file is written and every one matches.
//
// The two 440 byte register save blocks were transcribed from the listing by a
// script rather than typed, and every special purpose register is written by
// number rather than by name, so nothing depends on the assembler recognising a
// mnemonic for it. Both matched on the first build.
//
// Built with GC/1.3.2 like the rest of TRK, not with the 1.2.5n the Dolphin SDK
// uses. See the TRK entry in configure.py.
//
// The translation unit runs from 0x801CF550 to 0x801CFAF4, where dolphin_trk.c
// starts. The ten functions in that range add up to exactly 0x5A4 bytes, which
// is the whole span, so nothing else belongs here and nothing is missing.
//
// This object is built with -sdata 0 -sdata2 0. Without them TRK_mainError is
// small enough for the small data area and its address comes out through r13,
// while the original builds it with an lis and addi pair. That alone was worth
// seventeen points on TRK_main. The last point came from claiming the .bss
// range in splits.txt and defining lbl_803F0050 here instead of reaching it as
// an external: until the range is claimed, dtk keeps calling a file local
// symbol TRK_mainError_803F0058 and nothing written in C can match that name.
//
// Functions are in the order the original emits them.

// The instruction and data breakpoint address registers, cleared on entry so a
// breakpoint left over from the last stop cannot fire inside the nub.
#define SPR_IABR 1010
#define SPR_DABR 1013

// Linker defined, see ldscript.lcf. Declared as an unsized array so the
// compiler cannot decide it is small enough to reach through r13.
extern char _db_stack_addr[];

// Defined below InitMetroTRK, which calls it, so it needs a declaration here.
void TRKSaveExtended1Block(void);

extern int  InitMetroTRKCommTable(u32 which);
extern void TRK_main(void);
extern void TRKInterruptHandler(void);

// State the nub keeps about the target, 0xA4 bytes in .bss. Only the fields the
// written functions touch are named.
typedef struct TRKState {
	u8  unk00[0x8C]; // 0x00
	u32 unk8C;       // 0x8C, whatever fn_801CDCB8 reports
	u8  unk90[0x8];  // 0x90
	u32 unk98;       // 0x98, set to one on initialize
	u8  unk9C[0x8];  // 0x9C
} TRKState;          // 0xA4

extern TRKState gTRKState;

// The saved register file, 0x430 bytes. The word at 0x238 carries the flags
// fn_801CF650 tests.
extern u32 gTRKCPUState[];

// Nine bytes in .data. The first two say which optional blocks the last save
// wrote, and the restore clears them as it consumes them.
extern u8 gTRKRestoreFlags[];

// Base of the region the nub maps for itself, and the word after it. Owned by
// this file, so it is defined here rather than reached as an external.
static u32 lbl_803F0050[2];

extern u32  fn_801CDCB8(void);
extern void fn_801CFD74(void);

extern int  TRKInitializeNub(void);
extern void TRKNubWelcome(void);
extern int  TRKNubMainLoop(void);
extern int  TRKTerminateNub(void);

// Last result from TRK_main, kept so the host can read it back.
static int TRK_mainError;

// Four stubs that trap if anything reaches them. They are the unimplemented
// entries of the target interface: the nub declares them so the tables link,
// and traps rather than returning something wrong. Each one is a single
// unconditional twi followed by blr, which has no C form.

ASM void fn_801CF550(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	twi     31, r0, 0
	blr
#endif // clang-format on
}

ASM void fn_801CF558(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	twi     31, r0, 0
	blr
#endif // clang-format on
}

ASM void fn_801CF560(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	twi     31, r0, 0
	blr
#endif // clang-format on
}

ASM void fn_801CF568(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	twi     31, r0, 0
	blr
#endif // clang-format on
}

// Entered from whatever the game does to hand control to the debugger. It has
// to save the register file before touching anything, so it is assembly in the
// original source as well: there is no C for stmw, for moving the machine state
// register, or for writing the breakpoint address registers.
//
// The order matters. r3 is parked on the stack so it can be saved along with
// everything else, then the whole file goes out with one stmw. External
// interrupts are turned off in the copy of the MSR that is installed, while the
// original value is stashed in SRR1 for the return path.
ASM void InitMetroTRK(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	subi    r1, r1, 4
	stw     r3, 0(r1)
	lis     r3, gTRKCPUState@h
	ori     r3, r3, gTRKCPUState@l
	stmw    r0, 0(r3)
	lwz     r4, 0(r1)
	addi    r1, r1, 4
	stw     r1, 4(r3)
	stw     r4, 0xc(r3)
	mflr    r4
	stw     r4, 0x84(r3)
	stw     r4, 0x80(r3)
	mfcr    r4
	stw     r4, 0x88(r3)
	mfmsr   r4
	ori     r3, r4, 0x8000
	xori    r3, r3, 0x8000
	mtmsr   r3
	mtsrr1  r4
	bl      TRKSaveExtended1Block
	lis     r3, gTRKCPUState@h
	ori     r3, r3, gTRKCPUState@l
	lmw     r0, 0(r3)
	li      r0, 0
	mtspr   SPR_IABR, r0
	mtspr   SPR_DABR, r0
	lis     r1, _db_stack_addr@h
	ori     r1, r1, _db_stack_addr@l
	mr      r3, r5
	bl      InitMetroTRKCommTable
	cmpwi   r3, 1
	bne     _run
	lwz     r4, 0x84(r3)
	mtlr    r4
	lmw     r0, 0(r3)
	blr
_run:
	b       TRK_main
#endif // clang-format on
}

int TRKInitializeTarget(void)
{
	gTRKState.unk98 = 1;
	gTRKState.unk8C = fn_801CDCB8();

	lbl_803F0050[0] = 0xE0000000;

	return 0;
}

// Turns an address into the one the nub should actually touch. An address
// inside the nub's own region is left alone while the flags say it is live,
// because rewriting it would point the debugger at the wrong mapping. Anything
// else is forced through the cached mirror at 0x80000000.
static u32 fn_801CF650(u32 addr)
{
	if (addr >= lbl_803F0050[0] && addr < lbl_803F0050[0] + 0x4000
	    && (gTRKCPUState[0x238 / 4] & 3) != 0) {
		return addr;
	}

	return (addr & 0x3FFFFFFF) | 0x80000000;
}

void EnableMetroTRKInterrupts(void) { fn_801CFD74(); }

// Saves the parts of the machine the general purpose registers do not cover:
// the segment registers, the BAT pairs, the time base, the performance monitor
// and the paired single quantization registers. All of it is special purpose
// register traffic, so it is assembly in the original source too. Transcribed
// instruction for instruction rather than reconstructed, with every special
// purpose register written by number so nothing depends on the assembler
// knowing a name for it.
ASM void TRKSaveExtended1Block(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	lis     r2, gTRKCPUState@h
	ori     r2, r2, gTRKCPUState@l
	mfsr    r16, 0
	mfsr    r17, 1
	mfsr    r18, 2
	mfsr    r19, 3
	mfsr    r20, 4
	mfsr    r21, 5
	mfsr    r22, 6
	mfsr    r23, 7
	mfsr    r24, 8
	mfsr    r25, 9
	mfsr    r26, 10
	mfsr    r27, 11
	mfsr    r28, 12
	mfsr    r29, 13
	mfsr    r30, 14
	mfsr    r31, 15
	stmw    r16, 0x1A8(r2)
	mftb    r10, 268
	mftb    r11, 269
	mfspr   r12, 1008
	mfspr   r13, 1009
	mfspr   r14, 27
	mfspr   r15, 287
	mfspr   r16, 528
	mfspr   r17, 529
	mfspr   r18, 530
	mfspr   r19, 531
	mfspr   r20, 532
	mfspr   r21, 533
	mfspr   r22, 534
	mfspr   r23, 535
	mfspr   r24, 536
	mfspr   r25, 537
	mfspr   r26, 538
	mfspr   r27, 539
	mfspr   r28, 540
	mfspr   r29, 541
	mfspr   r30, 542
	mfspr   r31, 543
	stmw    r10, 0x1E8(r2)
	mfspr   r22, 25
	mfspr   r23, 19
	mfspr   r24, 18
	mfspr   r25, 272
	mfspr   r26, 273
	mfspr   r27, 274
	mfspr   r28, 275
	li      r29, 0
	mfspr   r30, 1010
	mfspr   r31, 282
	stmw    r22, 0x25C(r2)
	mfspr   r20, 912
	mfspr   r21, 913
	mfspr   r22, 914
	mfspr   r23, 915
	mfspr   r24, 916
	mfspr   r25, 917
	mfspr   r26, 918
	mfspr   r27, 919
	mfspr   r28, 920
	mfspr   r29, 921
	mfspr   r30, 922
	mfspr   r31, 923
	stmw    r20, 0x2FC(r2)
	b       _sav1
	mfspr   r16, 928
	mfspr   r17, 935
	mfspr   r18, 936
	mfspr   r19, 937
	mfspr   r20, 938
	mfspr   r21, 939
	mfspr   r22, 940
	mfspr   r23, 941
	mfspr   r24, 942
	mfspr   r25, 943
	mfspr   r26, 944
	mfspr   r27, 951
	mfspr   r28, 959
	mfspr   r29, 1014
	mfspr   r30, 1015
	mfspr   r31, 1023
	stmw    r16, 0x2B8(r2)
_sav1:
	mfspr   r19, 1013
	mfspr   r20, 953
	mfspr   r21, 954
	mfspr   r22, 957
	mfspr   r23, 958
	mfspr   r24, 955
	mfspr   r25, 952
	mfspr   r26, 956
	mfspr   r27, 1020
	mfspr   r28, 1021
	mfspr   r29, 1022
	mfspr   r30, 1019
	mfspr   r31, 1017
	stmw    r19, 0x284(r2)
	blr
	mfspr   r25, 976
	mfspr   r26, 977
	mfspr   r27, 978
	mfspr   r28, 979
	mfspr   r29, 980
	mfspr   r30, 981
	mfspr   r31, 982
	stmw    r25, 0x240(r2)
	mfspr   r31, 22
	stw     r31, 0x278(r2)
	blr
#endif // clang-format on
}

// The other direction. The two flag bytes at the front of gTRKRestoreFlags say
// which optional blocks were saved, and they are cleared as they are read so a
// second restore cannot put back stale state.
ASM void TRKRestoreExtended1Block(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	lis     r2, gTRKCPUState@h
	ori     r2, r2, gTRKCPUState@l
	lis     r5, gTRKRestoreFlags@h
	ori     r5, r5, gTRKRestoreFlags@l
	lbz     r3, 0x0(r5)
	lbz     r6, 0x1(r5)
	li      r0, 0
	stb     r0, 0x0(r5)
	stb     r0, 0x1(r5)
	cmpwi   r3, 0
	beq     _res1
	lwz     r24, 0x1E8(r2)
	lwz     r25, 0x1EC(r2)
	mtspr   284, r24
	mtspr   285, r25
_res1:
	lmw     r20, 0x2FC(r2)
	mtspr   912, r20
	mtspr   913, r21
	mtspr   914, r22
	mtspr   915, r23
	mtspr   916, r24
	mtspr   917, r25
	mtspr   918, r26
	mtspr   919, r27
	mtspr   920, r28
	mtspr   922, r30
	mtspr   923, r31
	b       _res2
	lmw     r26, 0x2E0(r2)
	mtspr   944, r26
	mtspr   951, r27
	mtspr   1014, r29
	mtspr   1015, r30
	mtspr   1023, r31
_res2:
	lmw     r19, 0x284(r2)
	mtspr   1013, r19
	mtspr   953, r20
	mtspr   954, r21
	mtspr   957, r22
	mtspr   958, r23
	mtspr   955, r24
	mtspr   952, r25
	mtspr   956, r26
	mtspr   1020, r27
	mtspr   1021, r28
	mtspr   1022, r29
	mtspr   1019, r30
	mtspr   1017, r31
	b       _res3
	cmpwi   r6, 0
	beq     _res4
	lwz     r26, 0x278(r2)
	mtspr   22, r26
_res4:
	lmw     r25, 0x240(r2)
	mtspr   976, r25
	mtspr   977, r26
	mtspr   978, r27
	mtspr   979, r28
	mtspr   980, r29
	mtspr   981, r30
	mtspr   982, r31
_res3:
	lmw     r16, 0x1A8(r2)
	mtsr    0, r16
	mtsr    1, r17
	mtsr    2, r18
	mtsr    3, r19
	mtsr    4, r20
	mtsr    5, r21
	mtsr    6, r22
	mtsr    7, r23
	mtsr    8, r24
	mtsr    9, r25
	mtsr    10, r26
	mtsr    11, r27
	mtsr    12, r28
	mtsr    13, r29
	mtsr    14, r30
	mtsr    15, r31
	lmw     r12, 0x1F0(r2)
	mtspr   1008, r12
	mtspr   1009, r13
	mtspr   27, r14
	mtspr   287, r15
	mtspr   528, r16
	mtspr   529, r17
	mtspr   530, r18
	mtspr   531, r19
	mtspr   532, r20
	mtspr   533, r21
	mtspr   534, r22
	mtspr   535, r23
	mtspr   536, r24
	mtspr   537, r25
	mtspr   538, r26
	mtspr   539, r27
	mtspr   540, r28
	mtspr   541, r29
	mtspr   542, r30
	mtspr   543, r31
	lmw     r22, 0x25C(r2)
	mtspr   25, r22
	mtspr   19, r23
	mtspr   18, r24
	mtspr   272, r25
	mtspr   273, r26
	mtspr   274, r27
	mtspr   275, r28
	mtspr   1010, r30
	mtspr   282, r31
	blr
#endif // clang-format on
}

static int fn_801CFA20(void) { return 0x54; }

// The nub's whole life. Bring it up, greet the host, run until it is told to
// stop, then tear it down. Both results are stored where the host can read
// them, and the teardown result wins because it happens last.
void TRK_main(void)
{
	TRK_mainError = TRKInitializeNub();

	if (TRK_mainError == 0) {
		TRKNubWelcome();
		TRKNubMainLoop();
	}

	TRK_mainError = TRKTerminateNub();
}

// Puts a saved context back and jumps straight into the interrupt handler
// rather than returning: the caller is not coming back. The half word at 0x1A2
// says whether the whole register file was saved or only the callee saved half,
// and the bit is cleared as it is consumed. Assembly in the original source
// too, since restoring the condition register, link register, count register
// and the SPRGs has no C form.
ASM void TRKLoadContext(void)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	lwz     r0, 0x0(r3)
	lwz     r1, 0x4(r3)
	lwz     r2, 0x8(r3)
	lhz     r5, 0x1A2(r3)
	rlwinm. r6, r5, 0, 30, 30
	beq     _ctx1
	rlwinm  r5, r5, 0, 31, 29
	sth     r5, 0x1A2(r3)
	lmw     r5, 0x14(r3)
	b       _ctx2
_ctx1:
	lmw     r13, 0x34(r3)
_ctx2:
	mr      r31, r3
	mr      r3, r4
	lwz     r4, 0x80(r31)
	mtcrf   255, r4
	lwz     r4, 0x84(r31)
	mtspr   8, r4
	lwz     r4, 0x88(r31)
	mtspr   9, r4
	lwz     r4, 0x8C(r31)
	mtspr   1, r4
	mfmsr   r4
	rlwinm  r4, r4, 0, 17, 15
	rlwinm  r4, r4, 0, 31, 29
	mtmsr   r4
	mtspr   273, r2
	lwz     r4, 0xC(r31)
	mtspr   274, r4
	lwz     r4, 0x10(r31)
	mtspr   275, r4
	lwz     r2, 0x198(r31)
	lwz     r4, 0x19C(r31)
	lwz     r31, 0x7C(r31)
	b       TRKInterruptHandler
#endif // clang-format on
}
