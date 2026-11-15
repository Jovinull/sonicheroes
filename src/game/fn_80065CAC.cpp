#include "types.h"

// TObjPtclCore::TDisp() (HYPOTHESIS, medium confidence from PS2 metadata): same references, order and size
// pattern as the PS2 PDisp, TDisp and Disp trio (the middle one is 12 bytes larger on both).
// Names are from PS2; the symbol keeps its address-based name.

class PARTICLE_MATERIAL;
class ParticleHeader
{
public:
	u8 pad0[4];
	s32 f4;
	u8 pad8[0x40];
	PARTICLE_MATERIAL* f48;
	u8 pad4C[8];
};
class PARTICLE_MATERIAL : public ParticleHeader
{
public:
	virtual void MoveManager();
	virtual void DispManager();
	virtual s32 Move(void*);
	virtual void Disp(void*);
	virtual void* AllocInstance();
	virtual void* CreateInstance();
};
struct Obj80065CAC {
	u8 pad[0x28];
	PARTICLE_MATERIAL* f28;
};
struct Mode80065CAC {
	u8 pad[0x20];
	s8 f20;
};

extern "C" {
extern u32 lbl_8042C2E0;
extern Mode80065CAC* lbl_8042C180;
void fn_80194234(s32, s32);

void fn_80065CAC(Obj80065CAC* o)
{
	PARTICLE_MATERIAL* p;
	PARTICLE_MATERIAL* n;
	s32 flags;

	if (lbl_8042C2E0 == 0) {
		return;
	}
	p = o->f28;
	if (p == 0) {
		return;
	}
	n = p;
	fn_80194234(0xe, 0);
	while (n != 0) {
		flags = n->f4;
		if (lbl_8042C180->f20 != 0 && (flags & 0x10000000) == 0) {
			n = n->f48;
		} else {
			if ((flags & 2) == 0 && (flags & 0x1C) != 0) {
				n->DispManager();
			}
			n = n->f48;
		}
	}
	fn_80194234(0xe, 1);
}
}
