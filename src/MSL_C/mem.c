#include "types.h"

// Order follows the original binary, which for this compiler is source order.

void __copy_longs_rev_unaligned(void* dst, const void* src, u32 n);
void __copy_longs_unaligned(void* dst, const void* src, u32 n);
void __copy_longs_rev_aligned(void* dst, const void* src, u32 n);
void __copy_longs_aligned(void* dst, const void* src, u32 n);

// How the Metrowerks source spells the walking pointers. The code generation
// depends on the parameters themselves being advanced rather than copied into
// named locals, so these are macros over the parameters rather than variables.
#define cps               ((u8*)src)
#define cpd               ((u8*)dst)
#define lps               ((u32*)src)
#define lpd               ((u32*)dst)
#define deref_auto_inc(p) *++(p)

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
// The unaligned copy walking backwards.
void __copy_longs_rev_unaligned(void* dst, const void* src, u32 n)
{
	u32 i, v1, v2;
	uint src_offset, left_shift, right_shift;

	cps = ((u8*)src) + n;
	cpd = ((u8*)dst) + n;

	i = ((u32)cpd) & 3;

	if (i) {
		n -= i;

		do
			*--cpd = *--cps;
		while (--i);
	}

	src_offset = ((uint)cps) & 3;

	left_shift  = src_offset << 3;
	right_shift = 32 - left_shift;

	cps += 4 - src_offset;

	i = n >> 3;

	v1 = *--lps;

	do {
		v2     = *--lps;
		*--lpd = (v2 << left_shift) | (v1 >> right_shift);
		v1     = *--lps;
		*--lpd = (v1 << left_shift) | (v2 >> right_shift);
	} while (--i);

	if (n & 4) {
		v2     = *--lps;
		*--lpd = (v2 << left_shift) | (v1 >> right_shift);
	}

	n &= 3;

	if (n) {
		cps += src_offset;
		do
			*--cpd = *--cps;
		while (--n);
	}
}
// Source and destination disagree about word alignment, so every output word is
// stitched from two input words with a shift each way. The loop is unrolled by
// two because the halves alternate which temporary carries the remainder.
void __copy_longs_unaligned(void* dst, const void* src, u32 n)
{
	u32 i, v1, v2;
	uint src_offset, left_shift, right_shift;

	i = (-(u32)dst) & 3;

	cps = ((u8*)src) - 1;
	cpd = ((u8*)dst) - 1;

	if (i) {
		n -= i;

		do
			deref_auto_inc(cpd) = deref_auto_inc(cps);
		while (--i);
	}

	src_offset = ((uint)(cps + 1)) & 3;

	left_shift  = src_offset << 3;
	right_shift = 32 - left_shift;

	cps -= src_offset;

	lps = ((u32*)(cps + 1)) - 1;
	lpd = ((u32*)(cpd + 1)) - 1;

	i = n >> 3;

	v1 = deref_auto_inc(lps);

	do {
		v2                  = deref_auto_inc(lps);
		deref_auto_inc(lpd) = (v1 << left_shift) | (v2 >> right_shift);
		v1                  = deref_auto_inc(lps);
		deref_auto_inc(lpd) = (v2 << left_shift) | (v1 >> right_shift);
	} while (--i);

	if (n & 4) {
		v2                  = deref_auto_inc(lps);
		deref_auto_inc(lpd) = (v1 << left_shift) | (v2 >> right_shift);
	}

	cps = ((u8*)(lps + 1)) - 1;
	cpd = ((u8*)(lpd + 1)) - 1;

	n &= 3;

	if (n) {
		cps -= 4 - src_offset;
		do
			deref_auto_inc(cpd) = deref_auto_inc(cps);
		while (--n);
	}
}
// The same copy walking backwards, for an overlap where the destination sits
// above the source.
void __copy_longs_rev_aligned(void* dst, const void* src, u32 n)
{
	u32 i;

	cps = ((u8*)src) + n;
	cpd = ((u8*)dst) + n;

	i = ((u32)cpd) & 3;

	if (i) {
		n -= i;

		do
			*--cpd = *--cps;
		while (--i);
	}

	i = n >> 5;

	if (i)
		do {
			*--lpd = *--lps;
			*--lpd = *--lps;
			*--lpd = *--lps;
			*--lpd = *--lps;
			*--lpd = *--lps;
			*--lpd = *--lps;
			*--lpd = *--lps;
			*--lpd = *--lps;
		} while (--i);

	i = (n & 31) >> 2;

	if (i)
		do
			*--lpd = *--lps;
		while (--i);

	n &= 3;

	if (n)
		do
			*--cpd = *--cps;
		while (--n);
}
// Both ends word aligned. A byte run to reach alignment, an unrolled run of
// eight words, the remaining words, then a byte tail.
void __copy_longs_aligned(void* dst, const void* src, u32 n)
{
	u32 i;

	i = (-(u32)dst) & 3;

	cps = ((u8*)src) - 1;
	cpd = ((u8*)dst) - 1;

	if (i) {
		n -= i;

		do
			deref_auto_inc(cpd) = deref_auto_inc(cps);
		while (--i);
	}

	lps = ((u32*)(cps + 1)) - 1;
	lpd = ((u32*)(cpd + 1)) - 1;

	i = n >> 5;

	if (i)
		do {
			deref_auto_inc(lpd) = deref_auto_inc(lps);
			deref_auto_inc(lpd) = deref_auto_inc(lps);
			deref_auto_inc(lpd) = deref_auto_inc(lps);
			deref_auto_inc(lpd) = deref_auto_inc(lps);
			deref_auto_inc(lpd) = deref_auto_inc(lps);
			deref_auto_inc(lpd) = deref_auto_inc(lps);
			deref_auto_inc(lpd) = deref_auto_inc(lps);
			deref_auto_inc(lpd) = deref_auto_inc(lps);
		} while (--i);

	i = (n & 31) >> 2;

	if (i)
		do
			deref_auto_inc(lpd) = deref_auto_inc(lps);
		while (--i);

	cps = ((u8*)(lps + 1)) - 1;
	cpd = ((u8*)(lpd + 1)) - 1;

	n &= 3;

	if (n)
		do
			deref_auto_inc(cpd) = deref_auto_inc(cps);
		while (--n);
}
