#include "types.h"

enum Pt_FLAGS { Pt_NON_FLAG = 0, ALL_Pt_FLAGS = -1 };

struct SPRITE_INFO {
	u8 pad00[0xC];
	u32 texture;
	u8 pad10[0x1C];
	u32 field2C;
};

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct SAngle {
	s32 x;
	s32 y;
	s32 z;
};

class PARTICLE_MATERIAL;

static inline u32 getTex(SPRITE_INFO* p)
{
	return p->texture;
}

extern unsigned char lbl_80243BF8[];
extern PARTICLE_MATERIAL* lbl_8042C2E0;
extern const f32 lbl_8042D4A8;
extern const f32 lbl_8042D4DC;
extern const f32 lbl_8042D4E0;
extern const f32 lbl_8042D4E4;

class PARTICLE_MATERIAL
{
public:
	PARTICLE_MATERIAL(Pt_FLAGS flags, SPRITE_INFO* info);

	u16 f00;
	u16 pad02;
	s32 f04;
	s32 f08;
	u16 f0C;
	u16 f0E;
	f32 f10;
	f32 f14;
	f32 f18;
	f32 f1C;
	f32 f20;
	f32 f24;
	PARTICLE_MATERIAL* f28;
	SPRITE_INFO* f2C;
	u32 f30;
	void* f34;
	u32 f38;
	void* f3C;
	u32 f40;
	PARTICLE_MATERIAL* f44;
	PARTICLE_MATERIAL* f48;
	u32 f4C;
	u32 f50;
	unsigned char* f54;
	RwV3d pos;
	SAngle ang;
	RwV3d vec;
};

PARTICLE_MATERIAL::PARTICLE_MATERIAL(Pt_FLAGS flags, SPRITE_INFO* info)
{
	f54   = lbl_80243BF8;
	f08   = 0;
	f04   = flags | 0x10000;
	f0C   = 0;
	f0E   = 0;
	f10   = lbl_8042D4A8;
	f14   = lbl_8042D4A8;
	f18   = lbl_8042D4DC;
	f1C   = lbl_8042D4E0;
	f24   = lbl_8042D4E4;
	f44   = 0;
	f48   = 0;
	f4C   = 0;
	f50   = 0;
	f34   = 0;
	f00   = 0;
	f3C   = 0;
	f40   = 0;
	pos.x = pos.y = pos.z = lbl_8042D4A8;
	vec.x = vec.y = vec.z = lbl_8042D4A8;
	ang.x = ang.y = ang.z = 0;
	f30                   = 0;
	f38                   = 0;

	if (lbl_8042C2E0 == 0) {
		f08 = 0;
	} else if (f08 != 1) {
		PARTICLE_MATERIAL* p = lbl_8042C2E0->f28;
		if (p == 0) {
			lbl_8042C2E0->f28 = this;
			f48               = 0;
			f44               = 0;
		} else {
			while (p->f48 != 0) {
				p = p->f48;
			}
			p->f48 = this;
			f44    = p;
			f48    = 0;
		}
		f08 = 1;
	}

	f2C     = info;
	u32 tex = getTex(info);
	if (f2C == 0) {
		return;
	}
	if (f04 & 0x10000) {
		f2C->texture = tex;
		f38          = tex;
		return;
	}
	if (f04 & 0x20000) {
		f2C->field2C = tex;
		f38          = tex;
	}
}
