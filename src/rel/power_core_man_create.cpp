#include "types.h"

// TEnemyPowerCoreMan::CreateInstance (the PS2 build's name), the same in the
// bonus stages (31D-33D): the instance is made once, with the constructor
// (rel/power_core_man.cpp) inlined.

typedef struct TObject {
	char* name; // 0x00
	u16 flags;  // 0x04
	u8 unk06[0x12];
	void** vtable; // 0x18
	u8 unk1C[0x2];
	u16 size; // 0x1E
	u8 unk20[0x8];
} TObject;

typedef struct PowerCoreMan {
	TObject base; // 0x00
	s32 count;    // 0x28
	u8 unk2C[0x4];
	f32 unk30; // 0x30
	f32 unk34; // 0x34
	f32 unk38; // 0x38
	f32 unk3C; // 0x3C
	f32 unk40; // 0x40
	u8 unk44[0x4];
	f32 unk48; // 0x48
	f32 unk4C; // 0x4C
	s32 unk50; // 0x50
} PowerCoreMan;

extern "C" char* powerCoreManClassName;
extern "C" void* searcherSoundLimitVtable[];
extern "C" PowerCoreMan* searcherSoundLimitInstance;
extern "C" const f32 powerCoreManZero;
extern "C" const f32 powerCoreManReach;
extern "C" TObject* lbl_8042C0FC;
extern "C" void* lbl_8042C148;

extern "C" void __ct__7TObjectFP7TObject(TObject* object, TObject* parent);
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);

static inline PowerCoreMan* powerCoreManInit(PowerCoreMan* object, TObject* parent)
{
	__ct__7TObjectFP7TObject(&object->base, parent);
	object->base.vtable = searcherSoundLimitVtable;
	object->unk30 = object->unk34 = object->unk38 = powerCoreManZero;
	object->unk38                                 = powerCoreManZero;
	object->unk3C                                 = powerCoreManZero;
	object->unk40                                 = powerCoreManReach;
	object->unk48                                 = powerCoreManZero;
	object->unk4C                                 = powerCoreManZero;
	object->unk50                                 = 0;
	object->base.name                             = powerCoreManClassName;
	object->base.size                             = 0x54;
	object->count                                 = 0;
	searcherSoundLimitInstance                    = object;
	return object;
}

extern "C" void CreateInstance__18TEnemyPowerCoreManFv(void)
{
	if (searcherSoundLimitInstance == NULL) {
		PowerCoreMan* object = (PowerCoreMan*)Malloc__9THeapCtrlFUi(lbl_8042C148, 0x54);

		if (object != NULL) {
			powerCoreManInit(object, lbl_8042C0FC);
		}
	}
}
