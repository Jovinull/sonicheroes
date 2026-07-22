#include "types.h"

// Order follows the original binary, which for this compiler is source order.

void* __copy_longs_rev_unaligned(void* dst, const void* src, u32 n);
void* __copy_longs_unaligned(void* dst, const void* src, u32 n);
void* __copy_longs_rev_aligned(void* dst, const void* src, u32 n);
void* __copy_longs_aligned(void* dst, const void* src, u32 n);

int memcmp(const void* s1, const void* s2, u32 n)
{
	const unsigned char* p1;
	const unsigned char* p2;
	for (p1 = (const unsigned char*)(s1)-1, p2 = (const unsigned char*)(s2)-1, n++; --n;)
		if (*++p1 != *++p2)
			return *p1 < *p2 ? -1 : 1;
	return 0;
}

void* __memrchr(const void* ptr, int value, u32 num)
{
	const unsigned char* str;
	unsigned int v = value & 0xff;
	for (str = (const unsigned char*)(ptr) + num, num++; --num;)
		if (*--str == v)
			return (void*)str;
	return 0;
}

void* memchr(const void* ptr, int value, u32 num)
{
	const unsigned char* str;
	unsigned int v = value & 0xff;
	for (str = (const unsigned char*)ptr - 1, num++; --num;)
		if ((*++str & 0xff) == v)
			return (void*)str;
	return 0;
}
// clang-format off

asm void* memmove(void* dst, const void* src, u32 n) {
#ifdef __MWERKS__
	nofralloc
	stwu    r1,-16(r1)
	mflr    r0
	cmplwi  r5,32
	stw     r0,20(r1)
	stw     r31,12(r1)
	mr      r31,r3
	xor     r6,r31,r4
	cntlzw  r0,r6
	slw     r0,r31,r0
	srwi    r7,r0,31
	blt     small
	rlwinm. r0,r6,0,30,31
	beq     aligned
	cmpwi   r7,0
	bne     unaligned_rev
	bl      __copy_longs_unaligned
	b       done_helper
unaligned_rev:
	bl      __copy_longs_rev_unaligned
	b       done_helper
aligned:
	cmpwi   r7,0
	bne     aligned_rev
	bl      __copy_longs_aligned
	b       done_helper
aligned_rev:
	bl      __copy_longs_rev_aligned
done_helper:
	mr      r3,r31
	b       epilogue
small:
	cmpwi   r7,0
	bne     small_rev
	subi    r3,r4,1
	subi    r4,r31,1
	addi    r5,r5,1
	b       small_fwd_test
small_fwd:
	lbzu    r0,1(r3)
	stbu    r0,1(r4)
small_fwd_test:
	subic.  r5,r5,1
	bne     small_fwd
	b       small_done
small_rev:
	add     r3,r4,r5
	add     r4,r31,r5
	addi    r5,r5,1
	b       small_rev_test
small_rev_loop:
	lbzu    r0,-1(r3)
	stbu    r0,-1(r4)
small_rev_test:
	subic.  r5,r5,1
	bne     small_rev_loop
small_done:
	mr      r3,r31
epilogue:
	lwz     r0,20(r1)
	lwz     r31,12(r1)
	mtlr    r0
	addi    r1,r1,16
	blr
#endif
}
// clang-format on
// clang-format off

asm void* __copy_longs_rev_unaligned(void* dst, const void* src, u32 n) {
#ifdef __MWERKS__
	nofralloc
	add     r11,r3,r5
	add     r10,r4,r5
	rlwinm. r3,r11,0,30,31
	beq     head_done
	subf    r5,r3,r5
head_loop:
	lbzu    r0,-1(r10)
	subic.  r3,r3,1
	stbu    r0,-1(r11)
	bne     head_loop
head_done:
	rlwinm  r8,r10,3,27,28
	rlwinm  r7,r10,0,30,31
	subfic  r9,r8,32
	srwi    r6,r5,3
	subfic  r0,r7,4
	add     r10,r10,r0
	lwzu    r4,-4(r10)
main_loop:
	lwz     r0,-4(r10)
	srw     r3,r4,r9
	subic.  r6,r6,1
	slw     r4,r0,r8
	srw     r0,r0,r9
	or      r3,r4,r3
	stw     r3,-4(r11)
	lwzu    r4,-8(r10)
	slw     r3,r4,r8
	or      r0,r3,r0
	stwu    r0,-8(r11)
	bne     main_loop
	rlwinm. r0,r5,0,29,29
	beq     tail_check
	lwzu    r3,-4(r10)
	srw     r0,r4,r9
	slw     r3,r3,r8
	or      r0,r3,r0
	stwu    r0,-4(r11)
tail_check:
	li      r0,3
	and.    r5,r5,r0
	beqlr
	add     r10,r10,r7
tail_loop:
	lbzu    r0,-1(r10)
	subic.  r5,r5,1
	stbu    r0,-1(r11)
	bne     tail_loop
	blr
#endif
}
// clang-format on
// clang-format off

asm void* __copy_longs_unaligned(void* dst, const void* src, u32 n) {
#ifdef __MWERKS__
	nofralloc
	neg     r0,r3
	subi    r8,r4,1
	rlwinm. r6,r0,0,30,31
	subi    r3,r3,1
	beq     head_done
	subf    r5,r6,r5
head_loop:
	lbzu    r0,1(r8)
	subic.  r6,r6,1
	stbu    r0,1(r3)
	bne     head_loop
head_done:
	addi    r0,r8,1
	subi    r6,r3,3
	rlwinm  r9,r0,0,30,31
	srwi    r7,r5,3
	subf    r8,r9,r8
	rlwinm  r10,r0,3,27,28
	lwzu    r4,1(r8)
	subfic  r11,r10,32
main_loop:
	lwz     r3,4(r8)
	slw     r4,r4,r10
	subic.  r7,r7,1
	srw     r0,r3,r11
	slw     r3,r3,r10
	or      r0,r4,r0
	stw     r0,4(r6)
	lwzu    r4,8(r8)
	srw     r0,r4,r11
	or      r0,r3,r0
	stwu    r0,8(r6)
	bne     main_loop
	rlwinm. r0,r5,0,29,29
	beq     tail_check
	lwzu    r0,4(r8)
	slw     r3,r4,r10
	srw     r0,r0,r11
	or      r0,r3,r0
	stwu    r0,4(r6)
tail_check:
	li      r0,3
	addi    r4,r8,3
	and.    r5,r5,r0
	addi    r3,r6,3
	beqlr
	subfic  r0,r9,4
	subf    r4,r0,r4
tail_loop:
	lbzu    r0,1(r4)
	subic.  r5,r5,1
	stbu    r0,1(r3)
	bne     tail_loop
	blr
#endif
}
// clang-format on
// clang-format off

asm void* __copy_longs_rev_aligned(void* dst, const void* src, u32 n) {
#ifdef __MWERKS__
	nofralloc
	add     r6,r3,r5
	add     r4,r4,r5
	rlwinm. r3,r6,0,30,31
	beq     head_done
	subf    r5,r3,r5
head_loop:
	lbzu    r0,-1(r4)
	subic.  r3,r3,1
	stbu    r0,-1(r6)
	bne     head_loop
head_done:
	srwi.   r3,r5,5
	beq     words_check
block_loop:
	lwz     r0,-4(r4)
	subic.  r3,r3,1
	stw     r0,-4(r6)
	lwz     r0,-8(r4)
	stw     r0,-8(r6)
	lwz     r0,-12(r4)
	stw     r0,-12(r6)
	lwz     r0,-16(r4)
	stw     r0,-16(r6)
	lwz     r0,-20(r4)
	stw     r0,-20(r6)
	lwz     r0,-24(r4)
	stw     r0,-24(r6)
	lwz     r0,-28(r4)
	stw     r0,-28(r6)
	lwzu    r0,-32(r4)
	stwu    r0,-32(r6)
	bne     block_loop
words_check:
	rlwinm. r3,r5,30,29,31
	beq     bytes_check
word_loop:
	lwzu    r0,-4(r4)
	subic.  r3,r3,1
	stwu    r0,-4(r6)
	bne     word_loop
bytes_check:
	li      r0,3
	and.    r5,r5,r0
	beqlr
byte_loop:
	lbzu    r0,-1(r4)
	subic.  r5,r5,1
	stbu    r0,-1(r6)
	bne     byte_loop
	blr
#endif
}
// clang-format on
// clang-format off

asm void* __copy_longs_aligned(void* dst, const void* src, u32 n) {
#ifdef __MWERKS__
	nofralloc
	neg     r0,r3
	subi    r7,r4,1
	rlwinm. r6,r0,0,30,31
	subi    r3,r3,1
	beq     head_done
	subf    r5,r6,r5
head_loop:
	lbzu    r0,1(r7)
	subic.  r6,r6,1
	stbu    r0,1(r3)
	bne     head_loop
head_done:
	srwi.   r4,r5,5
	subi    r6,r7,3
	subi    r3,r3,3
	beq     words_check
block_loop:
	lwz     r0,4(r6)
	subic.  r4,r4,1
	stw     r0,4(r3)
	lwz     r0,8(r6)
	stw     r0,8(r3)
	lwz     r0,12(r6)
	stw     r0,12(r3)
	lwz     r0,16(r6)
	stw     r0,16(r3)
	lwz     r0,20(r6)
	stw     r0,20(r3)
	lwz     r0,24(r6)
	stw     r0,24(r3)
	lwz     r0,28(r6)
	stw     r0,28(r3)
	lwzu    r0,32(r6)
	stwu    r0,32(r3)
	bne     block_loop
words_check:
	rlwinm. r4,r5,30,29,31
	beq     bytes_check
word_loop:
	lwzu    r0,4(r6)
	subic.  r4,r4,1
	stwu    r0,4(r3)
	bne     word_loop
bytes_check:
	li      r0,3
	addi    r4,r6,3
	and.    r5,r5,r0
	addi    r3,r3,3
	beqlr
byte_loop:
	lbzu    r0,1(r4)
	subic.  r5,r5,1
	stbu    r0,1(r3)
	bne     byte_loop
	blr
#endif
}
// clang-format on
