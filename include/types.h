#ifndef TYPES_H
#define TYPES_H

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

typedef unsigned int uint;

#ifdef __MWERKS__
#define ASM asm
#define DECL_SECT(sect) __declspec(section sect)
#else
#define ASM
#define DECL_SECT(sect)
#endif

#endif
