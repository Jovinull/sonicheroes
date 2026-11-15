#include "types.h"

extern "C" {

typedef struct Unk800BEA18_30 {
	u8 pad[3];
	s8 unk3;
} Unk800BEA18_30;

typedef struct Unk800BEA18 {
	u8 pad[0x28];
	u8* unk28;
	u8* unk2C;
	Unk800BEA18_30* unk30;
	u8 pad2[0xC];
	u32 unk40;
	u32 unk44;
	s32 unk48;
	f32 unk4C;
} Unk800BEA18;

void memcpy(void*, const void*, u32);
void fn_800BF1C8(void*, u32, u32, s32, s32);

void fn_800BEA18(Unk800BEA18* p)
{
	memcpy(p->unk28, p->unk2C, 0x1000);
	s32 v    = (s32)p->unk4C;
	p->unk48 = p->unk48 + p->unk30->unk3;
	fn_800BF1C8(p->unk28, p->unk40, p->unk44, v, p->unk48);
}
}
