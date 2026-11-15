// Releases the resources of an object of the unit around 0x80174B0C (HYPOTHESIS): drops a
// reference to the shared data at 0xAC and, when it was the last, releases each 12-byte entry's
// two resources (fn_80170FDC, fn_80169EF4), the entry list, the geometry (fn_80152EEC, HYPOTHESIS:
// RpGeometryDestroy) and the data block; then detaches and destroys the atomic at 0xB4 (its
// geometry cleared with fn_80152220 and its frame destroyed with fn_8019E480 first, then
// fn_80150358) and frees the block at 0xB0. Always returns 1. Field names are inferred.
#include "game/rw_engine.h"

struct Entry801750B8 {
	u8 pad0[0x4];
	void* resource; // 0x4
	void* extra;    // 0x8
};

struct Shared801750B8 {
	RwSList* entries; // 0x0: Entry801750B8
	s32 refCount;     // 0x4
	void* geometry;   // 0x8
};

struct Atomic801750B8 {
	u8 pad0[0x4];
	void* frame; // 0x4
};

struct Object801750B8 {
	u8 pad0[0xAC];
	Shared801750B8* shared; // 0xAC
	void* block;            // 0xB0
	Atomic801750B8* atomic; // 0xB4
};

extern "C" {
s32 fn_8019469C(RwSList* list);
void* fn_8019460C(RwSList* list);
s32 fn_80194628(RwSList* list);
void fn_80170FDC(void* resource);
void fn_80169EF4(void* extra);
s32 fn_80152EEC(void* geometry);
Atomic801750B8* fn_80152220(Atomic801750B8* atomic, void* geometry);
void* fn_8019E480(void* frame);
s32 fn_80150358(Atomic801750B8* atomic);

s32 fn_801750B8(Object801750B8* object)
{
	s32 count;
	Entry801750B8* entry;
	s32 i;
	Shared801750B8* shared;

	shared = object->shared;
	if (--shared->refCount == 0) {
		count = fn_8019469C(shared->entries);
		entry = (Entry801750B8*)fn_8019460C(shared->entries);
		for (i = 0; i < count; i++) {
			if (entry->resource) {
				fn_80170FDC(entry->resource);
				fn_80169EF4(entry->extra);
			}
			entry++;
		}
		fn_80194628(shared->entries);
		if (shared->geometry) {
			fn_80152EEC(shared->geometry);
			shared->geometry = 0;
		}
		lbl_8042C9A4->rwfree(shared);
	}
	if (object->atomic) {
		void* frame = object->atomic->frame;
		if (frame) {
			fn_80152220(object->atomic, 0);
			fn_8019E480(frame);
		}
		fn_80150358(object->atomic);
	}
	if (object->block) {
		lbl_8042C9A4->rwfree(object->block);
		object->block = 0;
	}
	return 1;
}
}
