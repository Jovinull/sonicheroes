// Releases a player's share of the 775 shared resource slots of lbl_802AD280 (16 bytes each):
// clears the player's bit (1 << character, +0x761) from each slot's user mask (+0x4) and, when no
// user is left, releases the slot's handle (+0xC, fn_800D075C), its object's buffer (+0x10 of
// the object at +0x8, fn_800126C8) and the object itself (fn_8020C2D8), clearing the pointers.
// HYPOTHESIS: per-character model/texture sharing; the roles are UNKNOWN.
#include "types.h"

struct Object8003F308 {
	u8 pad0[0x10];
	void* buffer; // 0x10
};

struct Slot8003F308 {
	u8 pad0[4];
	s32 users;              // 0x4
	Object8003F308* object; // 0x8
	void* handle;           // 0xC
};

struct Player8003F308 {
	u8 pad0[0x761];
	s8 character; // 0x761
};

extern "C" {
extern Slot8003F308 lbl_802AD280[0x307];
void fn_800D075C(void* handle);
void fn_800126C8(void* buffer);
void fn_8020C2D8(Object8003F308* object);
}

// The bit is computed in the loop from the character passed by value: hoisted out of the loop,
// it lands after the loop setup, as in the retail code.
static inline void ReleaseShared(s32 character)
{
	int i;

	for (i = 0; i < 0x307; i++) {
		if ((1 << character) & lbl_802AD280[i].users) {
			lbl_802AD280[i].users &= ~(1 << character);
			if (lbl_802AD280[i].users == 0) {
				fn_800D075C(lbl_802AD280[i].handle);
				if (lbl_802AD280[i].object->buffer != NULL) {
					fn_800126C8(lbl_802AD280[i].object->buffer);
					lbl_802AD280[i].object->buffer = NULL;
				}
				lbl_802AD280[i].handle = NULL;
				fn_8020C2D8(lbl_802AD280[i].object);
				lbl_802AD280[i].object = NULL;
			}
		}
	}
}

extern "C" {
void fn_8003F308(Player8003F308* p)
{
	ReleaseShared(p->character);
}
}
