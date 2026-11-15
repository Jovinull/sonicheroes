// Destructor of the class whose vtable is lbl_80254568 (derived from the class of dtor_800C497C;
// both names are UNKNOWN). It removes the object's ids from the 64-entry id table lbl_803042C8: the
// channel's main id (lbl_8042B3F0) and its three pairs of slot ids (lbl_80253DB8, lbl_80253DD0),
// clearing the matching bits of +0x74, then runs the base destructor (inlined: see
// dtor_800C497C) and frees the object when flags > 0. Returns the object. HYPOTHESIS: the ids are
// sound or effect handles of a per-channel object; the roles are UNKNOWN.
#include "types.h"

struct Obj800C3F0C {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	s8 channel; // 0x28
	u8 pad29[0x74 - 0x29];
	u32 registered; // 0x74 (bit 0: main id, bits 1-6: the six slot ids)
};

struct THeapCtrl;

extern "C" {
extern void* lbl_80254568[];
extern void* lbl_80254594[];
extern u32 lbl_8042B3F0[2];
extern u32 lbl_80253DB8[2][3];
extern u32 lbl_80253DD0[2][3];
extern u32 lbl_803042C8[0x40];
extern Obj800C3F0C* lbl_803043D8[];
extern Obj800C3F0C* lbl_803043C8[];
extern Obj800C3F0C* lbl_803043E8[];
extern Obj800C3F0C* lbl_803043F8[];
extern Obj800C3F0C* lbl_80304408[];
extern Obj800C3F0C* lbl_8042C40C;
extern Obj800C3F0C* lbl_8042C400;
extern Obj800C3F0C* lbl_8042C414;
extern Obj800C3F0C* lbl_8042C41C;
extern Obj800C3F0C* lbl_8042C424;
extern Obj800C3F0C* lbl_8042C42C;
extern THeapCtrl* lbl_8042C148;
void __dt__7TObjectFv(void* o, s32 flags);
void Free__9THeapCtrlFPv(THeapCtrl* heap, void* p);
}

// Clears `id` from the id table (the first matching entry).
static inline void Unregister(u32 id)
{
	int i;

	for (i = 0; i < 0x40; i++) {
		u32 entry = lbl_803042C8[i];

		if (entry == id) {
			lbl_803042C8[i] = 0;
			break;
		}
	}
}

// Body of dtor_800C497C without the free (flags 0).
static inline void DestroyBase(Obj800C3F0C* o)
{
	if (o != NULL) {
		s32 c;

		o->vtable = lbl_80254594;
		c         = o->channel;
		if (lbl_803043D8[c] == o) {
			lbl_803043D8[c] = NULL;
		}
		if (lbl_803043C8[c] == o) {
			lbl_803043C8[c] = NULL;
		}
		if (lbl_803043E8[c] == o) {
			lbl_803043E8[c] = NULL;
		}
		if (lbl_803043F8[c] == o) {
			lbl_803043F8[c] = NULL;
		}
		if (lbl_80304408[c] == o) {
			lbl_80304408[c] = NULL;
		}
		if (lbl_8042C40C == o) {
			lbl_8042C40C = NULL;
		}
		if (lbl_8042C400 == o) {
			lbl_8042C400 = NULL;
		}
		if (lbl_8042C414 == o) {
			lbl_8042C414 = NULL;
		}
		if (lbl_8042C41C == o) {
			lbl_8042C41C = NULL;
		}
		if (lbl_8042C424 == o) {
			lbl_8042C424 = NULL;
		}
		if (lbl_8042C42C == o) {
			lbl_8042C42C = NULL;
		}
		__dt__7TObjectFv(o, 0);
	}
}

extern "C" Obj800C3F0C* dtor_800C3F0C(Obj800C3F0C* o, s16 flags)
{
	if (o != NULL) {
		int i;

		o->vtable = lbl_80254568;
		Unregister(lbl_8042B3F0[o->channel]);
		o->registered &= ~1;
		for (i = 0; i < 3; i++) {
			Unregister(lbl_80253DB8[o->channel][i]);
			o->registered &= ~(2 << i);
			Unregister(lbl_80253DD0[o->channel][i]);
			o->registered &= ~(2 << (i + 3));
		}
		DestroyBase(o);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
