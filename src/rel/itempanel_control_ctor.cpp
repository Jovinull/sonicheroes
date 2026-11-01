#include "types.h"

// TObjItempanelControl's constructor (the PS2 build's name), the copy out of
// line; ExecuteAndDisplayItempanelEffectForAll (rel/itempanel_effect_all.cpp)
// inlines it. The control of a team (0 to 3) registers itself as the team's
// item panel control when the team has none yet. The same in the thirteen
// stage modules that share the engine core.

typedef struct ItempanelControl {
	const char* className; // 0x00
	u8 unk04[0x14];        // 0x04
	void* vtable;          // 0x18
	u8 unk1C[0x2];         // 0x1C
	u16 objectSize;        // 0x1E
	u8 unk20[0x8];         // 0x20
	s32 active;            // 0x28
	s32 count;             // 0x2C
	s32 group;             // 0x30
	f32 scale;             // 0x34
	s32 timer;             // 0x38
	void* first;           // 0x3C
} ItempanelControl;        // 0x40

extern "C" ItempanelControl* itempanelObjects[];
extern "C" const char* CL_TObjItempanelControl;
extern "C" void* __vt__20TObjItempanelControl[];
extern "C" const f32 itempanelScale[1];

extern "C" void __ct__7TObjectFP7TObject(void*, void*);

extern "C" ItempanelControl* __ct__20TObjItempanelControlFP7TObjecti(
    ItempanelControl* object, void* parent, s32 group)
{
	__ct__7TObjectFP7TObject(object, parent);
	object->vtable     = __vt__20TObjItempanelControl;
	object->className  = CL_TObjItempanelControl;
	object->objectSize = 0x40;
	object->count      = 0;
	object->scale      = itempanelScale[0];
	object->first      = NULL;
	object->group      = group;
	if (itempanelObjects[object->group] == NULL) {
		itempanelObjects[object->group] = object;
	}
	object->active = 1;
	object->timer  = 0;
	return object;
}
