#include "types.h"

// The bind hook TObjCannonSmoke's translation unit (TObjCannon's) keeps beside cannonSmokeFieldCallback, the same
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

extern "C" Handle* cannonSmokeBoundHandle;

extern "C" void cannonSmokeFieldCallback(void);

extern "C" void fn_801527A4(Handle* handle, void* callback, void* arg);

extern "C" BindObject* cannonSmokeBind(BindObject* object, void* arg)
{
	cannonSmokeBoundHandle = object->handle;
	cannonSmokeBoundHandle->flags |= 0x40;

	fn_801527A4(cannonSmokeBoundHandle, (void*)cannonSmokeFieldCallback, arg);

	return object;
}
