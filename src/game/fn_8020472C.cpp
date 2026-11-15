// Resolves the node of a descriptor id of an fn_802038AC object (HYPOTHESIS): id 0 (or below) is
// the object's root part (+0x24); any other id names a descriptor whose parent id (+0x34) is
// resolved first, then the descriptor's child id (+0x38) is looked up in that parent with
// fn_80173A4C. The compiler inlines the recursion several levels deep. Names are inferred from
// this function and fn_80203A6C.
#include "game/object_802038AC.h"

struct Descriptor8020472C {
	u8 pad0[0x34];
	s32 parentId; // 0x34
	s32 childId;  // 0x38
};

extern "C" {
void* fn_8019472C(void* sList, s32 index);
void* fn_80173A4C(void* table, s32 id);

void* fn_8020472C(Object802038AC* object, s32 id)
{
	if (id > 0) {
		Descriptor8020472C* descriptor = (Descriptor8020472C*)fn_8019472C(object->part8, id);
		return fn_80173A4C(fn_8020472C(object, descriptor->parentId), descriptor->childId);
	}
	return object->part24;
}
}
