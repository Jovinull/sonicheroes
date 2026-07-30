#include "types.h"

// TObjScrollRing's collect hook: it walks whatever the ring currently overlaps,
// keeps the last player it found, then credits that player and retires the ring.
//
// The claim is .text 0x8E28 to 0x8F98, which is the rest of the gap
// rel/scroll_ring_step.cpp opened; rel/scroll_ring_disp.cpp starts at 0x8F98.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out.

struct Overlap {
	u8 unk0[0x4];
	struct Contact* contact; // 0x04
};

struct Contact {
	u8 unk0[0x78];
	void* body; // 0x78
};

struct Player {
	u8 unk0[0x38];
	s8 slot;         // 0x38
	u8 unk39[0x225]; // 0x39
	s8 voice;        // 0x25E
};

struct Record {
	u8 unk0[0x29];
	s8 state; // 0x29
};

struct RecordData {
	u8 unk0[0x18];
};

// The bitmap the eleventh slot hands back is reached through a real virtual
// call: an index into a function pointer array parks the table in an argument
// register first, while a virtual call puts it straight into r12.
struct RecordOwner : public RecordData {
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual u32* collected();
};

struct ScrollRing {
	u8 unk0[0x90];
	u8 transform[0x18]; // 0x90
	u8 animation[0x18]; // 0xA8
	u8 emitter[0x8];    // 0xC0
	u8 award[0x1];      // 0xC8
	s8 award1;          // 0xC9
	u8 unkCA[0xA];      // 0xCA
	Record* record;     // 0xD4
};

extern "C" void* lbl_8042C1A4;
extern "C" void* lbl_8042C388;
extern "C" Player* lbl_802AD0D0[];

extern "C" void fn_80021824(void* query);
extern "C" Overlap* fn_800211A8(ScrollRing* object);
extern "C" s32 fn_80041B64(void* body);
extern "C" Player* fn_800924E4(s32 player);
extern "C" void fn_80066B74(void* emitter, s32 slot, s32 mode);
extern "C" void fn_800668D0(void* award, s32 player, s32 count);
extern "C" void objEmitBurst(void* transform, void* animation, f32 amount);
extern "C" void fn_800B4984(void* handle, s32 sound);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" const f32 scrollRingBurstA;
extern "C" const f32 scrollRingBurstB;

// The overlap list hands back an entry, and the body is reached through it only
// when there is one. Written as a helper because the original tests the entry
// and the body separately, in that order, before the loop body runs.
static inline Contact* nextContact(ScrollRing* object)
{
	Overlap* overlap = fn_800211A8(object);
	return overlap != NULL ? overlap->contact : NULL;
}

extern "C" void scrollRingTouch(ScrollRing* object)
{
	s32 player = -1;
	Contact* contact;

	fn_80021824(&lbl_8042C1A4);

	while ((contact = nextContact(object)) != NULL) {
		player = fn_80041B64(contact->body);
	}

	if (player == -1) {
		return;
	}

	Player* winner = fn_800924E4(player);
	fn_80066B74(object->emitter, winner->slot, 1);

	if (object->record != NULL && object->record->state != 4) {
		fn_800668D0(object->award, player, 10);
	}

	u32* collected = ((RecordOwner*)object->record)->collected();
	if (collected != NULL) {
		s8 index = object->award1;

		// The word is picked out of the index's own bits rather than by
		// shifting it: the original masks with 0x60 first and shifts after,
		// which bounds the bitmap at four words without a separate range test.
		collected[(index & 0x60) >> 5] |= 1 << (index & 31);
	}

	object->award[0] = 5;

	objEmitBurst(object->transform, object->animation, scrollRingBurstA);
	objEmitBurst(object->transform, object->animation, scrollRingBurstB);

	fn_800B4984(lbl_8042C388, lbl_802AD0D0[player]->voice);
}
