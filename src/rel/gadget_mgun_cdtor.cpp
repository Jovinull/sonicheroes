#include "types.h"

// TEnemyGadgetMGun's destructor (the PS2 build's name): the gadget closes its
// machine gun (the TEnemyGadget destructor inline, as the retail has it). The
// constructor stays in assembly: it keeps its owner argument in r31 across the
// TEnemyGadget constructor without using it (as TEnemyGadgetShot's does), which
// neither a C body nor a C++ constructor reproduces.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

class TMachineGun
{
public:
	void Stop();
};

typedef struct Searcher {
	u8 unk000[0x140];
	RwV3d pos;  // 0x140
	sAngle ang; // 0x14C
} Searcher;

typedef struct GadgetMGun {
	char* name; // 0x00
	u8 unk04[0x14];
	void** vtable; // 0x18
	u8 unk1C[0x2];
	u16 size; // 0x1E
	u8 unk20[0x10];
	s32 gmode; // 0x30
	u8 unk34[0x4];
	Searcher* enemy;   // 0x38
	TMachineGun* mgun; // 0x3C
	s32 field40;       // 0x40
	u8 unk44[0xC];
} GadgetMGun;

extern "C" void* lbl_8042C148;
extern "C" void* __vt__16TEnemyGadgetMGun[];
extern "C" void* __vt__12TEnemyGadget[];

extern "C" void __dt__7TObjectFv(GadgetMGun* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, GadgetMGun* object);
extern "C" void pawnReleaseBuffer(TMachineGun* mgun);

extern "C" GadgetMGun* __dt__16TEnemyGadgetMGunFv(GadgetMGun* gadget, s16 flags)
{
	if (gadget != NULL) {
		gadget->vtable = __vt__16TEnemyGadgetMGun;
		if (gadget->mgun != NULL) {
			pawnReleaseBuffer(gadget->mgun);
			gadget->mgun = NULL;
		}
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
