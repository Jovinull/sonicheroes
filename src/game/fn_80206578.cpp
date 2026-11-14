// Removes finished objects from a list (see game/audio_system.h). An object is finished when none
// of the entries of its list at 0x10 is live; an entry with flags & 0x80000003 == 0x80000002 is
// not live once the halfword at 0x146 of its source (0x34) is 0, or once it is in state 5 with a
// level (0xAC) below 0.2. A finished object is looked up in its owner slot's list (fn_80206804
// through the system's searchKey) and removed with fn_80206890, and the walk restarts. Object and
// entry layouts are inferred from this code; as in retail, an empty list node makes the walk
// restart forever.
#include "game/audio_system.h"

struct Source80206578 {
	unsigned char pad0[0x146];
	unsigned short f146;
};

struct Entry80206578 {
	unsigned int flags; // 0x00
	unsigned char pad4[0x34 - 0x4];
	Source80206578* source; // 0x34
	unsigned char pad38[0xAC - 0x38];
	float level; // 0xAC
	unsigned char padB0[0xD8 - 0xB0];
	int state; // 0xD8
};

struct Object80206578 {
	unsigned char pad0[0xC];
	PoolSlot* slot;        // 0x0C
	PoolListNode* entries; // 0x10
};

extern "C" {
extern const float lbl_8042FFC8; // 0.2f
PoolListNode* fn_80206328(PoolListNode** list, PoolListNode* prev);
PoolListNode* fn_80206340(PoolListNode** list, int (*pred)(PoolListNode* node));
void fn_8020641C(PoolListNode* target, PoolListNode** list, void (*fn)(PoolListNode* node));
int fn_80206804(PoolListNode* node);
void fn_80206890(PoolListNode* node);

void fn_80206578(PoolListNode** list)
{
	int live;
	PoolListNode** objects;
	PoolListNode* a;
	Object80206578* o;
restart:
	a = 0;
	while ((a = fn_80206328(list, a)) != 0) {
		o    = (Object80206578*)a->data;
		live = 0;
		if (o != 0) {
			PoolListNode* b = 0;
			while ((b = fn_80206328(&o->entries, b)) != 0) {
				Entry80206578* e = (Entry80206578*)b->data;
				if (e == 0) {
					continue;
				}
				live++;
				if ((e->flags & 0x80000003) == 0x80000002) {
					if (e->source->f146 == 0 || (e->state == 5 && e->level < lbl_8042FFC8)) {
						live--;
					}
				}
			}
		}
		if (live == 0) {
			if (o != 0) {
				objects = (PoolListNode**)&o->slot->fA0;
				if (*objects != 0) {
					PoolListNode* found;
					lbl_8042CF6C->searchKey = o;
					found                   = fn_80206340(objects, fn_80206804);
					if (found != 0) {
						fn_8020641C(found, objects, fn_80206890);
					}
				}
			}
			goto restart;
		}
	}
}
}
