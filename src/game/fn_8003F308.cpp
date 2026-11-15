// Releases a player's share of the 775 shared resource slots of lbl_802AD280 (16 bytes each):
// clears the player's bit (1 << character, +0x761) from each slot's user mask (+0x4) and, when no
// user is left, releases the slot's handle (+0xC, fn_800D075C), its object's buffer (+0x10 of
// the object at +0x8, fn_800126C8) and the object itself (fn_8020C2D8), clearing the pointers.
// HYPOTHESIS: per-character model/texture sharing; the roles are UNKNOWN.
// NonMatching (20 words, register allocation): the retail code sets up the counter and the slot
// pointer (r31/r30) before computing the bit and mask (r28/r29). Tried: every declaration order,
// an explicit slot pointer, the bit computed in the loop.
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

void fn_8003F308(Player8003F308* p)
{
	int i;
	s32 mask;
	s32 bit;

	bit  = 1 << p->character;
	mask = ~bit;
	for (i = 0; i < 0x307; i++) {
		if (bit & lbl_802AD280[i].users) {
			lbl_802AD280[i].users &= mask;
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
}
