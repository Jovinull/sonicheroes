#include "types.h"

// Order follows the original binary, which for this compiler is source order.
// The Metrowerks source walks a pointer decremented by one and pre-incremented
// in the loop, the same idiom as mem.c, so the length counter starts at -1.

// The walking destination pointer is u8* rather than char*. Keeping it the
// same type as the parameter lets the compiler propagate the copy away, and
// the byte stores then come out through the parameter register instead of the
// walking one.

// The word at a time copy is only taken when both pointers share the low two
// bits. The zero byte test is the usual (w - 0x01010101) & 0x80808080.
#define ONES  0x01010101
#define HIGHS 0x80808080

char* strcat(char* dst, const char* src)
{
	const char* s = src - 1;
	u8* p         = (u8*)dst - 1;

	while (*++p)
		;
	--p;
	while ((*++p = *++s) != 0)
		;
	return dst;
}

char* strncpy(char* dst, const char* src, u32 n)
{
	const char* s = src - 1;
	u8* p         = (u8*)dst - 1;

	n++;
	while (--n) {
		if ((*++p = *++s) == 0) {
			while (--n)
				*++p = 0;
			return dst;
		}
	}
	return dst;
}

char* strcpy(char* dst, const char* src)
{
	u8* p = (u8*)dst;
	u32 n;

	if (((u32)dst & 3) == ((u32)src & 3)) {
		u32 w;
		n = (u32)src & 3;
		if (n != 0) {
			if ((*p = *src) == 0)
				return dst;
			for (n = 3 - n; n != 0; n--)
				if ((*++p = *++src) == 0)
					return dst;
			++p;
			++src;
		}
		w = *(u32*)src;
		if (((w - ONES) & HIGHS) == 0) {
			p -= 4;
			do {
				*(u32*)(p += 4) = w;
				src += 4;
				w = *(u32*)src;
			} while (((w - ONES) & HIGHS) == 0);
			p += 4;
		}
	}

	if ((*p = *src) == 0)
		return dst;
	while ((*++p = *++src) != 0)
		;
	return dst;
}

u32 strlen(const char* str)
{
	const char* p = str - 1;
	u32 len       = -1;
	do {
		len++;
	} while (*++p);
	return len;
}
