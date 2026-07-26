#include "types.h"

// Spawns a marker for one emitter, and the two teardown paths beside it.
//
// The translation unit runs from fn_1_63A8 at 0x63A8 to the end of fn_1_6458
// at 0x64E0. The only private data it names is at .data 0x1C40, which is left
// to the module and referenced here rather than emitted.

extern "C" u8 lbl_1_data_1C40[];

extern "C" void* fn_80041FF4(void* name);
extern "C" void* fn_80146EA8(void* handle);
extern "C" void fn_8014705C(void* object);
extern "C" void fn_801471C8(void* object);
extern "C" void* fn_801471DC(void);
extern "C" s32 fn_80192F38(void* handle, s32 kind, s32 arg2, s32 arg3);
extern "C" void fn_80197ED8(void* handle, s32 flag);
extern "C" void* fn_1_B1C(u32 size);
extern "C" void* fn_1_5FBC(void* object, void* marker, void* emitter);

extern "C" void* fn_1_63A8(void* marker, void* emitter)
{
	void* object;

	if (marker != NULL) {
		object = fn_1_B1C(0x19C);
		if (object != NULL) {
			object = fn_1_5FBC(object, marker, emitter);
		}
		return object;
	}
	return NULL;
}

extern "C" void fn_1_6414(void)
{
	void* object = fn_801471DC();

	if (object != NULL) {
		fn_801471C8(NULL);
		fn_8014705C(object);
	}
}

extern "C" void fn_1_6458(void)
{
	void* handle;
	void* object;

	object = NULL;
	handle = fn_80041FF4(lbl_1_data_1C40);
	if (handle != NULL) {
		if (fn_80192F38(handle, 0x21, 0, 0) != 0) {
			object = fn_80146EA8(handle);
		}
		fn_80197ED8(handle, 0);
	}
	if (object != NULL) {
		fn_801471C8(object);
	}
}
