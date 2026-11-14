// Drops one reference to an object (count at +0x4). The last reference releases every 12-byte
// entry of its growable array (+0x0, read through fn_8019469C/fn_8019460C) that has a first object
// (fn_80170FDC on +0x4, fn_80169EF4 on +0x8), destroys the array through fn_80194628
// (_rwSListDestroy) and its geometry (+0x8) through fn_80152EEC (RpGeometryDestroy) and frees the
// object with the engine memory function. Names are UNKNOWN. Returns 1 when the object was
// released, otherwise 0.
#include "game/rw_engine.h"

struct Entry80174A34 {
	void* f0;
	void* first;  // 0x4
	void* second; // 0x8
};

struct Object80174A34 {
	RwSList* entries; // 0x0
	s32 refCount;     // 0x4
	void* geometry;   // 0x8
};

extern "C" {
Entry80174A34* fn_8019460C(RwSList* sList);
s32 fn_8019469C(RwSList* sList);
s32 fn_80194628(RwSList* sList);
void fn_80170FDC(void* object);
s32 fn_80169EF4(void* entry);
s32 fn_80152EEC(void* geometry);

s32 fn_80174A34(Object80174A34* object)
{
	if (--object->refCount == 0) {
		s32 count;
		s32 i;
		Entry80174A34* entry;
		count = fn_8019469C(object->entries);
		entry = fn_8019460C(object->entries);
		for (i = 0; i < count; i++) {
			if (entry->first != 0) {
				fn_80170FDC(entry->first);
				fn_80169EF4(entry->second);
			}
			entry++;
		}
		fn_80194628(object->entries);
		if (object->geometry != 0) {
			fn_80152EEC(object->geometry);
			object->geometry = 0;
		}
		lbl_8042C9A4->rwfree(object);
		return 1;
	}
	return 0;
}
}
