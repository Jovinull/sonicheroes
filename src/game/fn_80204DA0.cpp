// Applies an event to an fn_802038AC object (HYPOTHESIS): finds the descriptor of the event's id
// (fn_8020407C), takes the group of its current key frame (fn_8020530C with fn_802012C4 of the
// descriptor's cursor) and searches the group for the entry whose key (fn_80205578) equals the
// event key. For that entry's object part (fn_80202C60), when its flag bits (+0x8, upper bits
// shifted by 4 select the slots) contain the event mask, the slot of the highest mask bit selects
// a value at +0x10; a non-negative value is run through fn_80203144 with the object's index
// temporarily set to the event id. Returns the event, or null for a negative key. Names are
// inferred from this function only.
#include "game/keyframe_cursor.h"
#include "game/object_802038AC.h"

struct Event80204DA0 {
	u8 pad0[0x4];
	s32 id;   // 0x4
	s32 key;  // 0x8
	u32 mask; // 0xC
};

struct Descriptor80204DA0 {
	u8 pad0[0x4];
	KeyFrameCursor cursor; // 0x4
	u8 pad[0x30 - 0x4 - sizeof(KeyFrameCursor)];
	void* groups; // 0x30
};

struct Group80204DA0 {
	u8 pad0[0x8];
	RwSList* entries; // 0x8
};

struct Part80204DA0 {
	u8 pad0[0x8];
	u32 flags; // 0x8
	u8 padC[0x4];
	s32 values[1]; // 0x10 (extent UNKNOWN)
};

extern "C" {
Descriptor80204DA0* fn_8020407C(Object802038AC* object, s32 id);
s32 fn_802012C4(KeyFrameCursor* cursor);
Group80204DA0* fn_8020530C(void* groups, s32 index);
s32 fn_8019469C(RwSList* list);
void* fn_8019472C(RwSList* list, s32 index);
void fn_80205578(Object802038AC* object, void* groups, s32 frame, s32 index, s32* key);
Part80204DA0* fn_80202C60(Object802038AC* object, s32 id);
void fn_80203144(Object802038AC* object, s32 value);

Event80204DA0* fn_80204DA0(Object802038AC* object, Event80204DA0* event)
{
	Descriptor80204DA0* descriptor;
	s32 key;
	s32 found;
	Group80204DA0* group;
	s32 count;
	s32 i;
	s32 frame;

	descriptor = fn_8020407C(object, event->id);
	key        = event->key;
	if (key < 0) {
		return 0;
	}

	frame = fn_802012C4(&descriptor->cursor);
	group = fn_8020530C(descriptor->groups, frame);
	found = -1;
	count = fn_8019469C(group->entries);
	for (i = 0; i < count; i++) {
		s32 entryKey;
		fn_80205578(object, descriptor->groups, frame, i, &entryKey);
		if (entryKey == key) {
			found = i;
			break;
		}
	}

	if (found >= 0) {
		s32* entry         = (s32*)fn_8019472C(group->entries, found);
		u32 mask           = event->mask;
		Part80204DA0* part = fn_80202C60(object, *entry);
		if (part->flags & mask) {
			s32 slot = -1;
			u32 bits = part->flags >> 4;
			while (mask != 0) {
				if (bits & 1) {
					slot++;
				}
				mask >>= 1;
				bits >>= 1;
			}
			if (part->values[slot] >= 0) {
				s32 savedIndex = object->index;
				object->index  = event->id;
				fn_80203144(object, part->values[slot]);
				object->index = savedIndex;
			}
		}
	}
	return event;
}
}
