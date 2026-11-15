// Copies the shared state record at +0x10 of lbl_802C218C into the current team record's block at
// +0x40 (lbl_802B908C[lbl_8042C1FC]): the vector at +0x30 of the block becomes source - block
// (SubVectorReturnToVector), then the first word, two floats, three words, six floats and one more
// float (into +0x3C) are copied. HYPOTHESIS: the camera/position snapshot of the team; the field
// roles are UNKNOWN.
#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct Block80051614 {
	f32 f0;      // 0x0
	f32 f4;      // 0x4
	f32 f8;      // 0x8
	s32 wC;      // 0xC
	s32 w10;     // 0x10
	s32 w14;     // 0x14
	f32 f18;     // 0x18
	f32 f1C;     // 0x1C
	f32 f20;     // 0x20
	f32 f24;     // 0x24
	f32 f28;     // 0x28
	f32 f2C;     // 0x2C
	RwV3d delta; // 0x30
	f32 f3C;     // 0x3C
};

struct Team80051614 {
	u8 pad0[0x40];
	Block80051614 block; // 0x40
	u8 pad80[0x2324 - 0x80];
};

struct Shared80051614 {
	u8 pad0[0x10];
	f32 f10; // 0x10
	f32 f14; // 0x14
	f32 f18; // 0x18
	s32 w1C; // 0x1C
	s32 w20; // 0x20
	s32 w24; // 0x24
	f32 f28; // 0x28
	f32 f2C; // 0x2C
	f32 f30; // 0x30
	f32 f34; // 0x34
	f32 f38; // 0x38
	f32 f3C; // 0x3C
	f32 f40; // 0x40
};

void SubVectorReturnToVector(const RwV3d* a, const RwV3d* b, RwV3d* out);

extern "C" {
extern Team80051614 lbl_802B908C[];
extern s32 lbl_8042C1FC;
extern Shared80051614 lbl_802C218C;

void fn_80051614(void)
{
	f32* source;
	Block80051614* block;

	block  = &lbl_802B908C[lbl_8042C1FC].block;
	source = &lbl_802C218C.f10;

	SubVectorReturnToVector((RwV3d*)source, (RwV3d*)block, &block->delta);
	block->f0  = *source;
	block->f4  = lbl_802C218C.f14;
	block->f8  = lbl_802C218C.f18;
	block->wC  = lbl_802C218C.w1C;
	block->w10 = lbl_802C218C.w20;
	block->w14 = lbl_802C218C.w24;
	block->f18 = lbl_802C218C.f28;
	block->f1C = lbl_802C218C.f2C;
	block->f20 = lbl_802C218C.f30;
	block->f24 = lbl_802C218C.f34;
	block->f28 = lbl_802C218C.f38;
	block->f2C = lbl_802C218C.f3C;
	block->f3C = lbl_802C218C.f40;
}
}
