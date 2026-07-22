#include "types.h"
#include "dolphin/os.h"
#include "Runtime.PPCEABI.H/__ppc_eabi_linker.h"

// Order follows the original binary, which for this compiler is source order.

extern void* memcpy(void* dst, const void* src, u32 n);
extern void* memset(void* dst, int val, u32 n);

extern void OSResetSystem(int reset, u32 resetCode, int forceMenu);
extern void DBInit(void);
extern void OSInit(void);
extern void InitMetroTRK(void);
extern void InitMetroTRK_BBA(void);
extern void __init_user(void);
extern void exit(void);
extern int main(int argc, char** argv);

extern void __OSPSInit(void);
extern void __OSFPRInit(void);

DECL_SECT(".init") void __check_pad3(void);
DECL_SECT(".init") void __set_debug_bba(void);
DECL_SECT(".init") u8 __get_debug_bba(void);
DECL_SECT(".init") void __init_registers(void);
DECL_SECT(".init") void __init_data(void);
DECL_SECT(".init") void __init_hardware(void);
DECL_SECT(".init") void __flush_cache(void* dst, u32 n);

static u8 Debug_BBA;

DECL_SECT(".init") void __check_pad3(void)
{
	if ((*(u16*)0x800030E4 & 0xEEF) == 0xEEF) {
		OSResetSystem(0, 0, 0);
	}
}

DECL_SECT(".init") void __set_debug_bba(void) { Debug_BBA = 1; }

DECL_SECT(".init") u8 __get_debug_bba(void) { return Debug_BBA; }

DECL_SECT(".init") asm void __start(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	bl      __init_registers
	bl      __init_hardware
	li      r0,-1
	stwu    r1,-8(r1)
	stw     r0,4(r1)
	stw     r0,0(r1)
	bl      __init_data
	li      r0,0
	lis     r6,0x8000
	addi    r6,r6,0x44
	stw     r0,0(r6)
	lis     r6,0x8000
	addi    r6,r6,0xF4
	lwz     r6,0(r6)
	cmplwi  r6,0
	beq     no_apploader
	lwz     r7,12(r6)
	b       have_type
no_apploader:
	lis     r5,0x8000
	addi    r5,r5,0x34
	lwz     r5,0(r5)
	cmplwi  r5,0
	beq     no_trk
	lis     r7,0x8000
	addi    r7,r7,0x30E8
	lwz     r7,0(r7)
have_type:
	li      r5,0
	cmplwi  r7,2
	beq     init_trk
	cmplwi  r7,3
	li      r5,1
	beq     init_trk
	cmplwi  r7,4
	bne     no_trk
	li      r5,2
	bl      __set_debug_bba
	b       no_trk
init_trk:
	lis     r6,InitMetroTRK@ha
	addi    r6,r6,InitMetroTRK@l
	mtlr    r6
	blrl
no_trk:
	lis     r6,0x8000
	addi    r6,r6,0xF4
	lwz     r5,0(r6)
	cmplwi  r5,0
	beq+    no_args
	lwz     r6,8(r5)
	cmplwi  r6,0
	beq+    no_args
	add     r6,r5,r6
	lwz     r14,0(r6)
	cmplwi  r14,0
	beq     no_args
	addi    r15,r6,4
	mtctr   r14
reloc_loop:
	addi    r6,r6,4
	lwz     r7,0(r6)
	add     r7,r7,r5
	stw     r7,0(r6)
	bdnz    reloc_loop
	lis     r5,0x8000
	addi    r5,r5,0x34
	rlwinm  r7,r15,0,0,26
	stw     r7,0(r5)
	b       have_args
no_args:
	li      r14,0
	li      r15,0
have_args:
	bl      DBInit
	bl      OSInit
	lis     r4,0x8000
	addi    r4,r4,0x30E6
	lhz     r3,0(r4)
	andi.   r5,r3,0x8000
	beq     do_check
	andi.   r3,r3,0x7FFF
	cmplwi  r3,1
	bne     skip_check
do_check:
	bl      __check_pad3
skip_check:
	bl      __get_debug_bba
	cmplwi  r3,1
	bne     to_user
	bl      InitMetroTRK_BBA
to_user:
	bl      __init_user
	mr      r3,r14
	mr      r4,r15
	bl      main
	b       exit
#endif // clang-format on
}

DECL_SECT(".init") asm void __init_registers(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	li      r0,0
	li      r3,0
	li      r4,0
	li      r5,0
	li      r6,0
	li      r7,0
	li      r8,0
	li      r9,0
	li      r10,0
	li      r11,0
	li      r12,0
	li      r14,0
	li      r15,0
	li      r16,0
	li      r17,0
	li      r18,0
	li      r19,0
	li      r20,0
	li      r21,0
	li      r22,0
	li      r23,0
	li      r24,0
	li      r25,0
	li      r26,0
	li      r27,0
	li      r28,0
	li      r29,0
	li      r30,0
	li      r31,0
	lis     r1,_stack_addr@h
	ori     r1,r1,_stack_addr@l
	lis     r2,_SDA2_BASE_@h
	ori     r2,r2,_SDA2_BASE_@l
	lis     r13,_SDA_BASE_@h
	ori     r13,r13,_SDA_BASE_@l
	blr
#endif // clang-format on
}

// Written as asm rather than as the obvious loop over the BSS init table. Same
// reason as __init_cpp over in Runtime.PPCEABI.H/__ppc_eabi_init.c: the
// original carries chained branches through empty basic blocks between the loop
// setup and the condition test, and no plain C formulation reproduced them.
// Unlike most of the asm in this project, this one is a transcription rather
// than a function that is assembly in its own right. Worth another attempt, and
// solving it here would very likely solve __init_cpp too.
DECL_SECT(".init") asm void __init_data(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mflr    r0
	stw     r0,4(r1)
	stwu    r1,-24(r1)
	stw     r31,20(r1)
	stw     r30,16(r1)
	stw     r29,12(r1)
	lis     r3,_rom_copy_info@ha
	addi    r0,r3,_rom_copy_info@l
	mr      r29,r0
	b       rom_pre
rom_pre:
	b       rom_loop
rom_loop:
	lwz     r30,8(r29)
	cmplwi  r30,0
	beq     bss_setup
	lwz     r4,0(r29)
	lwz     r31,4(r29)
	beq     rom_next
	cmplw   r31,r4
	beq     rom_next
	mr      r3,r31
	mr      r5,r30
	bl      memcpy
	mr      r3,r31
	mr      r4,r30
	bl      __flush_cache
rom_next:
	addi    r29,r29,12
	b       rom_loop
bss_setup:
	lis     r3,_bss_init_info@ha
	addi    r0,r3,_bss_init_info@l
	mr      r29,r0
	b       bss_pre
bss_pre:
	b       bss_loop
bss_loop:
	lwz     r5,4(r29)
	cmplwi  r5,0
	beq     epilogue
	lwz     r3,0(r29)
	beq     bss_next
	li      r4,0
	bl      memset
bss_next:
	addi    r29,r29,8
	b       bss_loop
epilogue:
	lwz     r0,28(r1)
	lwz     r31,20(r1)
	lwz     r30,16(r1)
	lwz     r29,12(r1)
	addi    r1,r1,24
	mtlr    r0
	blr
#endif // clang-format on
}

DECL_SECT(".init") asm void __init_hardware(void) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	mfmsr   r0
	ori     r0,r0,0x2000
	mtmsr   r0
	mflr    r31
	bl      __OSPSInit
	bl      __OSFPRInit
	bl      __OSCacheInit
	mtlr    r31
	blr
#endif // clang-format on
}

DECL_SECT(".init") asm void __flush_cache(void* dst, u32 n) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
	lis     r5,0xFFFF
	ori     r5,r5,0xFFF1
	and     r5,r5,r3
	subf    r3,r5,r3
	add     r4,r4,r3
flush_loop:
	dcbst   r0,r5
	sync
	icbi    r0,r5
	addic   r5,r5,8
	subic.  r4,r4,8
	bge     flush_loop
	isync
	blr
#endif // clang-format on
}
