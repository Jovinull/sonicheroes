#include "types.h"

// The destructor and constructor of the special stages' base sled link class
// (bobLinkDtor and bobLinkCtor here; the class has no PS2 name), in stage01D
// and stage07D. The destructor lets go of the object as bobLinkUnlinkKill
// does, but leaves its signal alone. The constructor lets go of the current
// link (as bobLinkDetachCurrent does) and becomes the current one, unlinked.

typedef struct TObject {
	const char* className; // 0x00
	u16 signal;            // 0x04
	u8 unk06[0x12];
	void** vtable; // 0x18
	u8 unk1C[0x2];
	u16 dispTime; // 0x1E
	u8 unk20[0x8];
} TObject;

typedef struct BobLink {
	TObject base; // 0x00
	s32 linked;   // 0x28
	s32 slotIn;   // 0x2C
	s32 slotOut;  // 0x30
} BobLink;

extern "C" BobLink* bobLinkCurrent;
extern "C" const char* bobLinkClassName;
extern "C" void* bobLinkVtable[];
extern "C" void* lbl_8042C1F8;
extern "C" void* lbl_8042C148;
extern "C" TObject* lbl_8042C110;

extern "C" void __ct__7TObjectFP7TObject(TObject* object, TObject* parent);
extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);
extern "C" void fn_80130F78(s32 kind, void* object);
extern "C" void fn_8004D99C(void* world);
extern "C" void* fn_8004E608(void* world);
extern "C" void fn_8004DEC0(void* world, void* list, s32 slot);

static inline void bobLinkSlotOut(BobLink* object)
{
	if (object->linked != 0) {
		fn_8004D99C(lbl_8042C1F8);
		fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), object->slotOut);
		fn_80130F78(0xE, object);
		object->linked = 0;
	}
}

extern "C" BobLink* bobLinkDtor(BobLink* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = bobLinkVtable;
		bobLinkSlotOut(object);
		if (object == bobLinkCurrent) {
			bobLinkCurrent = NULL;
		}

		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}

extern "C" BobLink* bobLinkCtor(BobLink* object)
{
	__ct__7TObjectFP7TObject(&object->base, lbl_8042C110);
	object->base.vtable    = bobLinkVtable;
	object->base.className = bobLinkClassName;
	object->base.dispTime  = 0x34;

	if (bobLinkCurrent != NULL) {
		BobLink* current = bobLinkCurrent;

		bobLinkSlotOut(current);
		if (current == bobLinkCurrent) {
			bobLinkCurrent = NULL;
		}
		current->base.signal |= 1;
	}

	object->linked  = 0;
	object->slotIn  = 0;
	object->slotOut = 0;
	bobLinkCurrent  = object;
	return object;
}
