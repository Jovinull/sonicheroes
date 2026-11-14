// Destroys an object created by fn_802038AC (HYPOTHESIS): runs the per-part destructors for the
// parts that are present (fn_80203E38: 0x8, fn_802023D0: 0xC, fn_80202C1C: 0x10, fn_80202EF0:
// 0x18, fn_80173944 on 0x24, fn_80203844: 0x20), destroys the list at 0x1C (fn_802022C0) and
// returns the object to free list 2 of lbl_8040EB50. Always returns 1.
#include "game/object_802038AC.h"

extern "C" {
void fn_80203E38(Object802038AC* object);
void fn_802023D0(Object802038AC* object);
void fn_80202C1C(Object802038AC* object);
void fn_80202EF0(Object802038AC* object);
void fn_80173944(void* part);
void* fn_80203844(Object802038AC* object);
void fn_802022C0(void* list);

s32 fn_80203998(Object802038AC* object)
{
	if (object->part8) {
		fn_80203E38(object);
	}
	if (object->partC) {
		fn_802023D0(object);
	}
	if (object->part10) {
		fn_80202C1C(object);
	}
	if (object->part18) {
		fn_80202EF0(object);
	}
	if (object->part24) {
		fn_80173944(object->part24);
	}
	if (object->part20) {
		fn_80203844(object);
	}
	if (object->list) {
		fn_802022C0(object->list);
		object->list = 0;
	}
	lbl_8042C9A4->freeListFree(lbl_8040EB50.lists[2], object);
	return 1;
}
}
