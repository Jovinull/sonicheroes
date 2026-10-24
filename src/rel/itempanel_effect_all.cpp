#include "types.h"

// ExecuteAndDisplayItempanelEffectForAll (the PS2 build's name): for a team
// (0 to 3) and an item (0 to 12), the team's item panel control is made the
// first time (TObjItempanelControl's constructor inlined) and a new panel of
// the item joins it. (stage11D has its own copy, in rel/goal_ring_stage11.cpp.)

// the item kinds (0 to 12)
enum EnumTypeItem { ITEM_COUNT = 13 };

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

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" void* lbl_8042C2A0;
extern "C" ItempanelControl* itempanelObjects[];
extern "C" const char* CL_TObjItempanelControl;
extern "C" void* __vt__20TObjItempanelControl[];
extern "C" const f32 itempanelScale[1];

extern "C" void* Malloc__9THeapCtrlFUi(void*, u32);
extern "C" void* __nw__FUl(u32);
extern "C" void __ct__7TObjectFP7TObject(void*, void*);
extern "C" void __ct__17ItempanelInstanceFP20TObjItempanelControli12EnumTypeItemi(
    void* instance, int flags, ItempanelControl* control, int type, int item, int data);

void ExecuteAndDisplayItempanelEffectForAll(int group, int type, EnumTypeItem item, int data)
{
	if (group < 0 || group >= 4) {
		return;
	}
	if (item < 0 || item >= 13) {
		return;
	}
	{
		if (itempanelObjects[group] == NULL) {
			void* parent = lbl_8042C2A0;

			if (parent == NULL) {
				parent = lbl_8042C110;
			}
			ItempanelControl* object = (ItempanelControl*)Malloc__9THeapCtrlFUi(lbl_8042C148, 0x40);
			if (object != NULL) {
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
			}
		}
		if (itempanelObjects[group] != NULL) {
			void* instance = __nw__FUl(0x3C);
			if (instance != NULL) {
				__ct__17ItempanelInstanceFP20TObjItempanelControli12EnumTypeItemi(
				    instance, 1, itempanelObjects[group], type, item, data);
			}
		}
	}
}
