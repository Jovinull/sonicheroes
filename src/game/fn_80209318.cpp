// For a running audio pool slot (see game/audio_system.h): walks the entries of the slot's list
// at 0xA0 (fn_802068E4) and, for each, the sub-entries of its object's list at 0x10
// (fn_8020733C), updating every sub-entry with fn_8020709C, fn_80207648 and fn_802073A0 (word
// 0x2C of the object's channel and ramp B's value). List and object types are inferred.
#include "game/audio_system.h"

struct ListNode80209318 {
	void* f0;
	void* data; // 0x04
};

struct Object80209318 {
	unsigned char pad0[0x2];
	unsigned char channel; // 0x02
	unsigned char pad3[0x10 - 0x3];
	unsigned char list[1]; // 0x10
};

extern "C" {
ListNode80209318* fn_802068E4(unsigned int* list, ListNode80209318* prev);
ListNode80209318* fn_8020733C(void* list, ListNode80209318* prev);
void fn_8020709C(void* p);
void fn_80207648(void* p, PoolSlot* s);
void fn_802073A0(void* p, int value, float level);

void fn_80209318(PoolSlot* s)
{
	ListNode80209318* a;
	ListNode80209318* b;
	if (!(s->active & 0x80000000)) {
		return;
	}
	a = 0;
	while ((a = fn_802068E4(&s->fA0, a)) != 0) {
		int ch = ((Object80209318*)a->data)->channel;
		b      = 0;
		while ((b = fn_8020733C(((Object80209318*)a->data)->list, b)) != 0) {
			fn_8020709C(b->data);
			fn_80207648(b->data, s);
			fn_802073A0(b->data, s->channels[ch].f2C, s->rampBValue);
		}
	}
}
}
