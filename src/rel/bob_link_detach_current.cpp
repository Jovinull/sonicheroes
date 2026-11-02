#include "types.h"

// Lets go of the special stages' current sled link (bobLinkDetachCurrent
// here; the class has no PS2 name), in stage01D and stage07D: a linked
// object takes its slot out of the world's list and tells the sound side,
// the current link is forgotten, and the object asks to be killed.

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
extern "C" void fn_8004D99C(void* world);
extern "C" void* fn_8004E608(void* world);
extern "C" void fn_8004DEC0(void* world, void* list, s32 slot);

extern "C" void bobLinkDetachCurrent(void)
{
	if (bobLinkCurrent != NULL) {
		BobLink* object = bobLinkCurrent;

		if (object->linked != 0) {
			fn_8004D99C(lbl_8042C1F8);
			fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), object->slotOut);
			fn_80130F78(0xE, object);
			object->linked = 0;
		}
		if (object == bobLinkCurrent) {
			bobLinkCurrent = NULL;
		}
		object->signal |= 1;
	}
}
