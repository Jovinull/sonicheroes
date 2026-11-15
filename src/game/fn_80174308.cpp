// Reads an object of the unit around 0x8017306C from a stream (HYPOTHESIS): allocates one
// (fn_8017306C), initialises it (fn_801730A4 with 1), reads its header (fn_801731D4, returning null
// on failure) and its body (fn_80173DF0). When the body cannot be read the object is destroyed
// again: its list at 0xB4 and, if every 0x100-byte entry of the list at 0xAC (count at 0xB0) could
// be released (fn_80172F94), that list too, then the object goes back to the free list at 0x1DC of
// lbl_803EC968. Returns the result of fn_80173DF0. Field names are inferred.
// NonMatching: the retail entry loop clears the flag before each test and keeps it in r29 without
// a bool mask; ours masks the && result (71 vs 70 instructions).
#include "game/rw_engine.h"

struct Object80174308 {
	u8 pad0[0xAC];
	RwSList* entries; // 0xAC: 0x100-byte entries
	s32 count;        // 0xB0
	RwSList* list;    // 0xB4
};

struct Block80174308 {
	u8 pad0[0x1DC];
	RwFreeList* freeList; // 0x1DC
};

extern "C" {
extern Block80174308 lbl_803EC968;

Object80174308* fn_8017306C(void);
Object80174308* fn_801730A4(Object80174308* object, void* owner);
void* fn_801731D4(Object80174308* object, void* stream);
void* fn_80173DF0(Object80174308* object, void* stream, s32 flags);
s32 fn_80172F94(void* entry);
s32 fn_80194628(RwSList* list);
void* fn_8019460C(RwSList* list);
}

static inline void ObjectDestroy(Object80174308* object)
{
	if (object) {
		s32 ok = 1;
		u8* end;
		u8* entry;

		if (object->list) {
			ok = fn_80194628(object->list);
		}
		end = (u8*)fn_8019460C(object->entries) + (object->count << 8);
		for (entry = (u8*)fn_8019460C(object->entries); entry != end; entry += 0x100) {
			ok = ok && fn_80172F94(entry);
		}
		if (ok) {
			fn_80194628(object->entries);
		}
		lbl_8042C9A4->freeListFree(lbl_803EC968.freeList, object);
	}
}

extern "C" {
void* fn_80174308(void* stream)
{
	Object80174308* object = fn_8017306C();
	void* result;

	fn_801730A4(object, (void*)1);
	if (!fn_801731D4(object, stream)) {
		return 0;
	}
	result = fn_80173DF0(object, stream, 0);
	if (!result) {
		ObjectDestroy(object);
	}
	return result;
}
}
