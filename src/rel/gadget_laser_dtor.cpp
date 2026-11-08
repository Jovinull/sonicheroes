#include "types.h"

// TEnemyGadgetLaser's destructor (the PS2 build's name): the laser destroys its
// three beams and six parts (DestroyClump, inline here, as the retail has it;
// a helper taking the gadget as a parameter gives the inlined loops the retail's
// counter and pointer registers, where locals of the destructor swap them),
// releases its collision and runs the TEnemyGadget destructor inline.
typedef struct RpClump RpClump;

typedef struct GadgetLaserInfo {
	u8 unk00[0x4];
	u32 flags; // 0x04
} GadgetLaserInfo;

typedef struct GadgetLaserObj {
	char* name; // 0x00
	u8 unk04[0x14];
	void** vtable; // 0x18
	u8 unk1C[0x2];
	u16 size; // 0x1E
	u8 unk20[0x8];
	u8* owner; // 0x28
	u8 unk2C[0xC];
	u8 colli[0x10];        // 0x38
	GadgetLaserInfo* info; // 0x48
	u8 unk4C[0x4C];
	f32 pos[3]; // 0x98
	u8 unkA4[0x1C];
	void* enemy;   // 0xC0
	f32 scaleA[3]; // 0xC4
	f32 scaleB[3]; // 0xD0
	s32 zeroDC;
	s32 zeroE0;
	s32 zeroE4;
	s32 colour;        // 0xE8
	f32 scaleC;        // 0xEC
	s32 ready;         // 0xF0
	s32 readyF4;       // 0xF4
	RpClump* parts[6]; // 0xF8
	RpClump* beams[3]; // 0x110
	s32 zero11C;
	s32 zero120;
	s32 zero124;
	s32 zero128;
	s32 count; // 0x12C
	s32 zero130;
	u8 tail[0x140]; // 0x134
} GadgetLaserObj;

extern "C" void* lbl_8042C148;
extern "C" void* __vt__17TEnemyGadgetLaser[];
extern "C" void* __vt__12TEnemyGadget[];

extern "C" void __dt__7C_COLLIFv(void* colli, s32 flags);
extern "C" void __dt__7TObjectFv(GadgetLaserObj* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, GadgetLaserObj* object);
extern "C" void fn_80150958(RpClump* clump);

static inline void laserDestroyClump(GadgetLaserObj* self)
{
	int i;
	int j;

	for (i = 2; i >= 0; i--) {
		if (self->beams[i] != NULL) {
			fn_80150958(self->beams[i]);
			self->beams[i] = NULL;
		}
	}
	for (j = 5; j >= 0; j--) {
		if (self->parts[j] != NULL) {
			fn_80150958(self->parts[j]);
			self->parts[j] = NULL;
		}
	}
}

extern "C" GadgetLaserObj* __dt__17TEnemyGadgetLaserFv(GadgetLaserObj* gadget, s16 flags)
{
	if (gadget != NULL) {
		gadget->vtable = __vt__17TEnemyGadgetLaser;
		laserDestroyClump(gadget);
		__dt__7C_COLLIFv(gadget->colli, 0);
		if (gadget != NULL) {
			gadget->vtable = __vt__12TEnemyGadget;
			__dt__7TObjectFv(gadget, 0);
		}
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, gadget);
		}
	}
	return gadget;
}
