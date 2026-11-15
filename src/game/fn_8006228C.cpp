#include "types.h"

// PARTICLE_TASK::Exec() (CORROBORATED by PS2 metadata): the only GameCube caller of fn_800601A4, as the only
// PS2 caller of PARTICLE_TASK::CreateParticle is PARTICLE_TASK::Exec; also the mode-switch check and the kill flag.
// Names are from PS2; the symbol keeps its address-based name.

extern "C" {
void fn_800601A4(void*);
extern void* lbl_8042C180;
}

typedef struct Sub8006228C Sub8006228C;
struct Sub8006228C {
	u8 pad[0x10];
	s16 f10;
};

typedef struct Obj8006228C Obj8006228C;
struct Obj8006228C {
	u8 pad0[4];
	u16 f4;
	u8 pad6[0x2C - 0x06];
	s32 f2C;
	u8 pad30[0x74 - 0x30];
	void* f74;
	u8 pad78[0xA4 - 0x78];
	u16 fA4;
	s8 fA6;
	s16 fA8;
	u8 padAA[0xB0 - 0xAA];
	Sub8006228C* fB0;
};

extern "C" void fn_8006228C(Obj8006228C* o)
{
	s16 t;

	if (o->fB0 == 0) {
		return;
	}
	if (*(s8*)((u8*)lbl_8042C180 + 0x1F) != 0 && (o->f2C & 0x10000000) == 0) {
		return;
	}
	t = o->fA8;
	if (t == 0) {
		if (o->fA6 == 0) {
			if (o->f74 == 0 && (o->fA4 & 8) == 0) {
				o->f4 = o->f4 | 1;
			}
		} else {
			if ((o->fA4 & 1) == 0 && (o->fA4 & 4) == 0) {
				fn_800601A4(o);
				if (o->fA6 > 0) {
					o->fA6--;
				}
				o->fA8 = o->fB0->f10;
			}
		}
	} else {
		o->fA8--;
	}
}
