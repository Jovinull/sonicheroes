#include "types.h"

// The bobsleigh's setup helpers (the PS2 build's names):
// - SetBobsleigh_SpecialModel and SetBobsleigh: create a TObjBobsleigh with
//   the given ID and parameters (and, for the first, its own two models) in the
//   first free slot of the sled table (4 when none is free).
// - BobsleighParam::BobsleighParam: the course's paths and their count, and the
//   module's default tuning.

typedef struct RpClump RpClump;
typedef struct PATHTAG PATHTAG;

class BobsleighParam
{
public:
	BobsleighParam(PATHTAG* (*paths)[2], int count);

	PATHTAG* (*paths)[2]; // 0x00
	s32 count;            // 0x04
	f32 unk08;            // 0x08
	f32 unk0C;            // 0x0C
	f32 unk10;            // 0x10
	f32 unk14;            // 0x14
	f32 unk18;            // 0x18
	f32 baseSpeed;        // 0x1C
	s32 unk20;            // 0x20
	f32 unk24;            // 0x24
	f32 unk28;            // 0x28
	s32 unk2C;            // 0x2C
	f32 unk30;            // 0x30
	u8 unk34[0x4];
	s32 unk38; // 0x38
	s32 unk3C; // 0x3C
	s32 unk40; // 0x40
	s32 unk44; // 0x44
	s32 unk48; // 0x48
};

extern "C" void* lbl_8042C148;
extern "C" void* lbl_8042C104;
extern "C" void* lbl_80288E0C[];
extern "C" f32 bobsleighParamDefault08;
extern "C" f32 bobsleighParamDefault0C;
extern "C" f32 bobsleighParamDefault10;
extern "C" f32 bobsleighParamDefault14;
extern "C" f32 bobsleighParamDefault18;
extern "C" f32 bobsleighParamDefault24;
extern "C" f32 bobsleighParamDefault28;
extern "C" const f32 bobsleighBaseSpeed[1];
extern "C" const f32 bobsleighZero[1];

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void*
__ct__13TObjBobsleighFP7TObject17ENUM_BOBSLEIGH_IDP14BobsleighParamP7RpClumpP7RpClumpi(void* object,
    int complete, void* parent, int id, BobsleighParam* param, RpClump* clump, RpClump* launcher,
    int slot);

extern "C" void SetBobsleigh_SpecialModel__F17ENUM_BOBSLEIGH_IDP14BobsleighParamP7RpClumpP7RpClump(
    int id, BobsleighParam* param, RpClump* clump, RpClump* launcher)
{
	int slot;
	void* memory;

	for (slot = 0; slot < 4; slot++) {
		if (lbl_80288E0C[slot] == NULL) {
			break;
		}
	}
	memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x394);
	if (memory != NULL) {
		__ct__13TObjBobsleighFP7TObject17ENUM_BOBSLEIGH_IDP14BobsleighParamP7RpClumpP7RpClumpi(
		    memory, 1, lbl_8042C104, id, param, clump, launcher, slot);
	}
}

extern "C" void SetBobsleigh__F17ENUM_BOBSLEIGH_IDP14BobsleighParam(int id, BobsleighParam* param)
{
	int slot;
	void* memory;

	for (slot = 0; slot < 4; slot++) {
		if (lbl_80288E0C[slot] == NULL) {
			break;
		}
	}
	memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x394);
	if (memory != NULL) {
		__ct__13TObjBobsleighFP7TObject17ENUM_BOBSLEIGH_IDP14BobsleighParamP7RpClumpP7RpClumpi(
		    memory, 1, lbl_8042C104, id, param, NULL, NULL, slot);
	}
}

BobsleighParam::BobsleighParam(PATHTAG* (*paths)[2], int count)
{
	this->paths = paths;
	this->count = count;
	unk08       = bobsleighParamDefault08;
	unk0C       = bobsleighParamDefault0C;
	unk10       = bobsleighParamDefault10;
	unk14       = bobsleighParamDefault14;
	unk18       = bobsleighParamDefault18;
	baseSpeed   = bobsleighBaseSpeed[0];
	unk20       = 3;
	unk24       = bobsleighParamDefault24;
	unk28       = bobsleighParamDefault28;
	unk2C       = 30;
	unk30       = bobsleighZero[0];
	unk38       = 0;
	unk3C       = 3;
	unk40       = 1;
	unk44       = 1;
	unk48       = 1;
}
