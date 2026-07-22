#ifndef TYPES_H
#define TYPES_H

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

typedef unsigned int uint;

// The SDK spells its boolean as a plain int. Kept here rather than repeated per
// file so two translation units cannot end up disagreeing about it silently.
typedef int BOOL;

#define FALSE 0
#define TRUE  1

#define NULL 0

#ifdef __MWERKS__
#define ASM asm
#define DECL_SECT(sect) __declspec(section sect)
#else
#define ASM
#define DECL_SECT(sect)
#endif

#endif
