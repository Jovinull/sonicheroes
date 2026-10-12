#include "types.h"

// The bind hook the hint ring's translation unit keeps beside hintringFieldCallback, the same
// code as rel/checkpoint_bind.cpp: it publishes the object's handle at +0x18
// into the module's slot, raises bit 6 of that handle's flags and hooks the
// field callback onto it.

typedef struct Handle {
	u8 unk0[0x08]; // 0x00
	u32 flags;     // 0x08
} Handle;

typedef struct BindObject {
	u8 unk0[0x18];  // 0x00
	Handle* handle; // 0x18
} BindObject;

extern "C" Handle* hintringBoundHandle;

extern "C" void hintringFieldCallback(void);

extern "C" void fn_801527A4(Handle* handle, void* callback, void* arg);

extern "C" BindObject* hintringBind(BindObject* object, void* arg)
{
	hintringBoundHandle = object->handle;
	hintringBoundHandle->flags |= 0x40;

	fn_801527A4(hintringBoundHandle, (void*)hintringFieldCallback, arg);

	return object;
}
