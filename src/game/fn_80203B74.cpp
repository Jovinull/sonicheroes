// Reads an fn_802038AC object from a stream (HYPOTHESIS): creates it when none is given (the body
// of fn_802038AC inlined), then reads the version word, the four values at +0x48 and each part
// in turn (fn_80202464, fn_80204308, fn_802027F0, fn_80203068, fn_80203208, fn_80203E90), and
// finally applies fn_80203A6C to every descriptor (fn_802040A0). Returns the object, or null on
// failure. Names follow fn_802038AC.
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
// HYPOTHESIS: RwStreamReadInt32 and RwStreamReadReal.
void* fn_80193884(void* stream, void* ints, u32 numBytes);
void* fn_801937A0(void* stream, f32* reals, u32 numBytes);
void* fn_80202464(Object802038AC* object, void* stream);
void* fn_80204308(Object802038AC* object, void* stream);
void* fn_802027F0(Object802038AC* object, void* stream);
void* fn_80203068(Object802038AC* object, void* stream);
void* fn_80203208(Object802038AC* object, void* stream);
void* fn_80203E90(Object802038AC* object, void* stream);
void* fn_80203A6C(Object802038AC* object, void* descriptor);
void fn_802040A0(Object802038AC* object, void* (*callback)(Object802038AC*, void*), void* data);
}

// The body of fn_802038AC.
static inline Object802038AC* Create80203B74(void)
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

extern "C" {
Object802038AC* fn_80203B74(Object802038AC* object, void* stream)
{
	if (object == 0) {
		object = Create80203B74();
	}
	if (object != 0) {
		s32 version;
		if (fn_80193884(stream, &version, sizeof(version)) == 0) {
			return 0;
		}
		if (fn_801937A0(stream, &object->value48, 4 * sizeof(f32)) == 0) {
			return 0;
		}
		if (fn_80202464(object, stream) == 0) {
			return 0;
		}
		if (fn_80204308(object, stream) == 0) {
			return 0;
		}
		if (fn_802027F0(object, stream) == 0) {
			return 0;
		}
		if (fn_80203068(object, stream) == 0) {
			return 0;
		}
		if (fn_80203208(object, stream) == 0) {
			return 0;
		}
		if (fn_80203E90(object, stream) == 0) {
			return 0;
		}
		fn_802040A0(object, fn_80203A6C, 0);
	}
	return object;
}
}
