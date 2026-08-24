#include "types.h"

// CRI AXRNA for GameCube.
//
// The unit runs from fn_80223500 at 0x80223500 to the end of fn_80224C3C at
// 0x80224D14, and owns .rodata 0x80240400 to 0x802405F8, .data 0x8029BAB0 to
// 0x8029BB30 and .bss 0x80428A78 to 0x8042A9D0. The disc ships no map, so the
// bounds are argued rather than read:
//
//   The .rodata opens with the module's own banner, "\nAXRNA Ver.1.02
//   Build:May  9 2003 17:10:58\n", followed by a pointer to it. It ends at
//   0x802405F8, where the "RNARES handle" and "ADX buffer" messages start;
//   those belong to fn_80224D14 and fn_80224E1C, which sit above this run.
//
//   Every .bss and .data block between 0x80428A78 and 0x8042A9D0, and between
//   0x8029BAB0 and 0x8029BB30, is touched only by functions of this run.
//   0x8042A9D0 is the first block that is not: fn_80224E1C and fn_80224F88
//   share it, and both sit above the cut.
//
//   The lower bound is the neighbour. game/cri/adapter.c ends at 0x80223500
//   and its .bss ends at 0x80428A78, exactly where this one starts.
//
// Nothing is named yet: the banner carries no function names and the two error
// strings in range belong to the unit above, so every function keeps its dtk
// name.

typedef struct AxObj AxObj;

typedef struct AxVtbl {
	/* 0x00 */ u8 pad00[0x24];
	/* 0x24 */ s32 (*get)(AxObj* obj, s32 arg);
} AxVtbl;

struct AxObj {
	/* 0x00 */ AxVtbl* vtbl;
};

typedef struct AxRna {
	/* 0x00 */ s8 stat;
	/* 0x01 */ s8 pad01[2];
	/* 0x03 */ s8 idx;
	/* 0x04 */ u8 pad04[0x30];
	/* 0x34 */ AxObj* slot[4];
	/* 0x44 */ u8 pad44[0xA4];
} AxRna;

#define AX_RNA_MAX 16

extern void fn_8022347C(void* func, void* obj);
extern void fn_80223820(AxRna* p);

static AxRna ax_Tbl[AX_RNA_MAX];

void fn_802237B4(void* p, s8 v)
{
	if (p == NULL) {
		return;
	}
	*((s8*)p + 3) = v;
}

void fn_802237C4(void)
{
	AxRna* p;
	u32 i;

	p = ax_Tbl;
	for (i = 0; i < AX_RNA_MAX; i++) {
		if (p->stat == 1) {
			fn_80223820(p);
		}
		p++;
	}
}

s32 fn_80223E78(AxRna* p)
{
	if (p == NULL) {
		return -1;
	}
	return (s32)((u32)p->slot[p->idx]->vtbl->get(p->slot[p->idx], 0) >> 1);
}

s32 fn_80223ED0(AxRna* p)
{
	if (p == NULL) {
		return -1;
	}
	return 4096 - (s32)((u32)p->slot[p->idx]->vtbl->get(p->slot[p->idx], 0) >> 1);
}

void fn_80224CB0(void* func, void* obj)
{
	fn_8022347C(func, obj);
}

s32 fn_80224CD0(void* p)
{
	if (p == NULL) {
		return 0;
	}
	return *(s32*)((s8*)p + 8);
}

s32 fn_80224CE8(void* p)
{
	if (p == NULL) {
		return 0;
	}
	return *(s32*)((s8*)p + 4);
}

void fn_80224D00(void* p)
{
	if (p == NULL) {
		return;
	}
	*(s32*)p = 0;
}
