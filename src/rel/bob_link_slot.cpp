#include "types.h"

// The slot helpers of the special stages' sled link objects (the class has
// no PS2 name), in stage01D and stage07D. bobLinkUnlinkKill lets go of an
// object as bobLinkDetachCurrent does, bobLinkUnlink only takes a linked
// object's slot out of the world's list, and bobLinkLink puts the object's
// other slot in and tells the sound side.

typedef struct BobLink {
	u8 unk00[0x4];
	u16 signal; // 0x04
	u8 unk06[0x22];
	s32 linked;  // 0x28
	s32 slotIn;  // 0x2C
	s32 slotOut; // 0x30
} BobLink;

extern "C" BobLink* bobLinkCurrent;
extern "C" void* lbl_8042C1F8;
extern "C" void fn_80130F78(s32 kind, void* object);
extern "C" void fn_80131088(s32 kind, void* object);
extern "C" void fn_8004D99C(void* world);
extern "C" void fn_8004D9B8(void* world);
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

extern "C" void bobLinkUnlinkKill(BobLink* object)
{
	bobLinkSlotOut(object);
	if (object == bobLinkCurrent) {
		bobLinkCurrent = NULL;
	}
	object->signal |= 1;
}

extern "C" void bobLinkUnlink(BobLink* object)
{
	bobLinkSlotOut(object);
}

extern "C" void bobLinkLink(BobLink* object)
{
	fn_80131088(0xE, object);
	fn_8004D9B8(lbl_8042C1F8);
	fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), object->slotIn);
	object->linked = 1;
}
