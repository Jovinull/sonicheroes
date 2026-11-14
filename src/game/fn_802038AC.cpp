// Creates an object of the module around 0x80202000 (HYPOTHESIS): takes one from free list 2 of
// lbl_8040EB50, clears its list and buffer pointers, sets the index at 0x44 to -1, lets the
// per-part constructors allocate its parts (fn_80203DF0: 0x8, fn_80202384: 0xC, fn_80202BD0:
// 0x10, fn_80202E8C: 0x14/0x18, fn_802037C0: 0x20), creates the list at 0x1C (fn_8020229C),
// installs the callback fn_80204EF0 and the default .sdata2 values, then initialises the block
// at 0x58 (fn_80202C84). Their results are not checked. Returns the object, or null when the
// free list is exhausted.
#include "game/object_802038AC.h"

extern "C" {
extern f32 lbl_8042FF90;
extern f32 lbl_8042FF94;
extern u8 fn_80204EF0[];

void* fn_80203DF0(Object802038AC* object);
void* fn_80202384(Object802038AC* object);
void* fn_80202BD0(Object802038AC* object);
void* fn_80202E8C(Object802038AC* object);
void* fn_802037C0(Object802038AC* object);
void* fn_8020229C(void);
void fn_80202C84(void* block);

Object802038AC* fn_802038AC(void)
{
	Object802038AC* object = (Object802038AC*)lbl_8042C9A4->freeListAlloc(lbl_8040EB50.lists[2]);

	if (object) {
		object->part0  = 0;
		object->part4  = 0;
		object->part8  = 0;
		object->partC  = 0;
		object->list   = 0;
		object->part24 = 0;
		object->part10 = 0;
		object->index  = -1;
		fn_80203DF0(object);
		fn_80202384(object);
		fn_80202BD0(object);
		fn_80202E8C(object);
		fn_802037C0(object);
		object->list     = fn_8020229C();
		object->callback = fn_80204EF0;
		object->value2C  = lbl_8042FF90;
		object->value30  = lbl_8042FF90;
		object->part34   = 0;
		object->value48  = lbl_8042FF94;
		object->value4C  = lbl_8042FF94;
		object->value50  = lbl_8042FF94;
		object->value54  = lbl_8042FF94;
		fn_80202C84(object->block);
	}
	return object;
}
}
