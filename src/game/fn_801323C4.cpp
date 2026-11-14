// Callback from a .rodata handler table (HYPOTHESIS): when the source has no position yet (word
// 0x8 clear), loads its position and word 0x20 from the default block lbl_8042C208; then clears
// the first four words of the output, copies the source position to 0x10, the position at 0x40
// of the current player's object lbl_80303DC8[lbl_8042C1FC] to 0x34 and the source word 0x20 to
// 0x24. Field names are inferred from this function only.
#include "types.h"

struct Vec801323C4 {
	f32 x;
	f32 y;
	f32 z;
};

struct Default801323C4 {
	Vec801323C4 position; // 0x0
	u8 padC[0x8];
	s32 value; // 0x14
};

struct Source801323C4 {
	u8 pad0[0x8];
	s32 hasPosition; // 0x8
	u8 padC[0x8];
	Vec801323C4 position; // 0x14
	s32 value;            // 0x20
};

struct Player801323C4 {
	u8 pad0[0x40];
	Vec801323C4 position; // 0x40
};

struct Output801323C4 {
	s32 word0;          // 0x0
	s32 word4;          // 0x4
	s32 word8;          // 0x8
	s32 wordC;          // 0xC
	Vec801323C4 source; // 0x10
	u8 pad1C[0x8];
	s32 value; // 0x24
	u8 pad28[0xC];
	Vec801323C4 player; // 0x34
};

static inline void CopyVec(Vec801323C4* dst, const Vec801323C4* src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

extern "C" {
extern s32 lbl_8042C1FC;
extern Default801323C4* lbl_8042C208;
extern Player801323C4* lbl_80303DC8[4];

void fn_801323C4(Output801323C4* out, Source801323C4* source)
{
	s32 player = lbl_8042C1FC;

	if (source->hasPosition == 0) {
		CopyVec(&source->position, &lbl_8042C208->position);
		source->value = lbl_8042C208->value;
	}
	out->word0 = 0;
	out->word4 = 0;
	out->word8 = 0;
	out->wordC = 0;
	CopyVec(&out->source, &source->position);
	CopyVec(&out->player, &lbl_80303DC8[player]->position);
	out->value = source->value;
}
}
