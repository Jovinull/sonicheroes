// TObjSetGen::RebuildCommunicateIdList (symbol name from the retail map): rebuilds the doubly
// linked list of the active set objects (bit 0 of word 0x18) that use the given communicate id
// (byte 0x2A), walking the 0x800 entries of the set object table lbl_802D63A0 in order; the list
// head and tail for each id are kept at 0x30 and 0x430 of the generator. Field names are
// inferred from this function only.
#include "types.h"

// Set object entry (0x40 bytes).
struct SetObject80059434 {
	u8 pad0[0x18];
	u32 flags; // 0x18: bit 0 set while the entry is in use
	u8 pad1C[0xE];
	u8 communicateId; // 0x2A
	u8 pad2B[0x9];
	SetObject80059434* prev; // 0x34
	SetObject80059434* next; // 0x38
	u8 pad3C[0x4];
};

struct SetGen80059434 {
	u8 pad0[0x30];
	SetObject80059434* heads[0x100]; // 0x30
	SetObject80059434* tails[0x100]; // 0x430
};

extern "C" {
extern SetObject80059434 lbl_802D63A0[0x800];

void RebuildCommunicateIdList__10TObjSetGenFUc(SetGen80059434* gen, u8 id)
{
	s32 i;

	gen->heads[id] = 0;
	gen->tails[id] = 0;
	for (i = 0; i < 0x800; i++) {
		SetObject80059434* object = &lbl_802D63A0[i];
		if ((object->flags & 1) != 0 && id == object->communicateId) {
			SetObject80059434* tail = gen->tails[id];
			if (!tail) {
				gen->tails[id] = object;
				gen->heads[id] = object;
				object->prev   = 0;
				object->next   = 0;
			} else {
				object->prev         = tail;
				object->next         = 0;
				gen->tails[id]->next = object;
				gen->tails[id]       = object;
			}
		}
	}
}
}
