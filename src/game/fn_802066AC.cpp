// Walks a list of objects (see game/audio_system.h) and, for each, the entries of the object's
// list at 0x10 (fn_80206328 iterates both): an entry whose state at 0xD8 is 4 or more is set to
// state 5 with its two levels at 0xAC/0xB0 set to 0 and -96; others go to fn_80207034. Entry and
// object layouts are inferred from this code.
#include "game/audio_system.h"

struct Entry802066AC {
	unsigned char pad0[0xAC];
	float fAC;
	float fB0;
	unsigned char padB4[0xD8 - 0xB4];
	int state; // 0xD8
};

struct Object802066AC {
	unsigned char pad0[0x10];
	PoolListNode* entries; // 0x10
};

extern "C" {
extern const float lbl_8042FFCC; // 0.0f
extern const float lbl_8042FFD0; // -96.0f
PoolListNode* fn_80206328(PoolListNode** list, PoolListNode* prev);
void fn_80207034(Entry802066AC* e);

void fn_802066AC(PoolListNode** list)
{
	PoolListNode* a = 0;
	while ((a = fn_80206328(list, a)) != 0) {
		Object802066AC* o = (Object802066AC*)a->data;
		PoolListNode* b;
		if (o == 0) {
			continue;
		}
		b = 0;
		while ((b = fn_80206328(&o->entries, b)) != 0) {
			Entry802066AC* e = (Entry802066AC*)b->data;
			if (e == 0) {
				continue;
			}
			if (e->state >= 4) {
				e->fAC   = lbl_8042FFCC;
				e->fB0   = lbl_8042FFD0;
				e->state = 5;
			} else {
				fn_80207034(e);
			}
		}
	}
}
}
