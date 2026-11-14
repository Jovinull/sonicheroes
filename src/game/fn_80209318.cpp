// For a running audio pool slot (see game/audio_system.h): walks the slot's objects (0xA0,
// fn_802068E4) and, for each, the entries of the object's list at 0x10 (fn_8020733C), updating
// every entry with fn_8020709C, fn_80207648 and fn_802073A0 (word 0x2C of the object's channel
// and ramp B's value). The object layout is inferred.
#include "game/audio_system.h"

struct Object80209318 {
	unsigned char pad0[0x2];
	unsigned char channel; // 0x02
	unsigned char pad3[0x10 - 0x3];
	PoolListNode* entries; // 0x10
};

extern "C" {
PoolListNode* fn_802068E4(PoolListNode** list, PoolListNode* prev);
PoolListNode* fn_8020733C(PoolListNode** list, PoolListNode* prev);
void fn_8020709C(void* p);
void fn_80207648(void* p, PoolSlot* s);
void fn_802073A0(void* p, int value, float level);

void fn_80209318(PoolSlot* s)
{
	PoolListNode* a;
	PoolListNode* b;
	if (!(s->active & 0x80000000)) {
		return;
	}
	a = 0;
	while ((a = fn_802068E4(&s->objects, a)) != 0) {
		int ch = ((Object80209318*)a->data)->channel;
		b      = 0;
		while ((b = fn_8020733C(&((Object80209318*)a->data)->entries, b)) != 0) {
			fn_8020709C(b->data);
			fn_80207648(b->data, s);
			fn_802073A0(b->data, s->channels[ch].f2C, s->rampBValue);
		}
	}
}
}
