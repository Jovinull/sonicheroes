// Applies a descriptor to an fn_802038AC object (HYPOTHESIS): picks the target (the object's
// part at 0x24 when both descriptor ids at 0x34/0x38 are -1, otherwise the entry fn_80173A4C
// finds for id 0x38 in what fn_8020472C returns for id 0x34, with flag 4 cleared by
// fn_801733C0), runs fn_80202DB4 with that target on the object entry of every id listed by the
// descriptor's groups (fn_8020530C on the table at 0x30, ids from each group's list at 0x8), then
// resets the key-frame cursor at 0x4 against the block at 0x20 and steps it once. Returns the
// object. Field names are inferred from this function only.
#include "game/keyframe_cursor.h"
#include "game/object_802038AC.h"

struct Group80203A6C {
	u8 pad0[0x8];
	RwSList* ids; // 0x8: list of s32
};

struct Descriptor80203A6C {
	u8 pad0[0x4];
	KeyFrameCursor cursor; // 0x4
	u8 block[0x10];        // 0x20
	void* groups;          // 0x30
	s32 id34;              // 0x34
	s32 id38;              // 0x38
};

extern "C" {
void* fn_8020472C(Object802038AC* object, s32 id);
void* fn_80173A4C(void* table, s32 id);
void fn_801733C0(void* target, s32 enable);
s32 fn_8020128C(KeyFrameCursor* cursor);
Group80203A6C* fn_8020530C(void* groups, s32 index);
s32 fn_8019469C(RwSList* list);
void* fn_8019460C(RwSList* list);
void* fn_80202C60(Object802038AC* object, s32 id);
void* fn_80202DB4(void* entry, void* target);
KeyFrameCursor* fn_80200AC4(KeyFrameCursor* cursor, void* arg);
KeyFrameCursor* fn_80200BAC(KeyFrameCursor* cursor, void* arg, s32 steps);

Object802038AC* fn_80203A6C(Object802038AC* object, Descriptor80203A6C* descriptor)
{
	void* target;
	s32 count;
	s32 i;

	if (descriptor->id34 == -1 && descriptor->id38 == -1) {
		target = object->part24;
	} else {
		target = fn_80173A4C(fn_8020472C(object, descriptor->id34), descriptor->id38);
		fn_801733C0(target, 0);
	}

	count = fn_8020128C(&descriptor->cursor);
	for (i = 0; i < count; i++) {
		Group80203A6C* group = fn_8020530C(descriptor->groups, i);
		if (group) {
			s32 idCount;
			s32 j;
			s32* ids;
			idCount = fn_8019469C(group->ids);
			ids     = (s32*)fn_8019460C(group->ids);
			for (j = 0; j < idCount; j++) {
				fn_80202DB4(fn_80202C60(object, *ids), target);
				ids++;
			}
		}
	}

	fn_80200AC4(&descriptor->cursor, descriptor->block);
	fn_80200BAC(&descriptor->cursor, descriptor->block, 1);
	return object;
}
}
