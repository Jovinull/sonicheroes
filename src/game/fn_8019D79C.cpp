// Closes the engine (HYPOTHESIS: RwEngineClose): sends the device close request, then copies the
// heap-allocated engine globals back into the static block lbl_803ED4E0, frees the heap copy,
// drops the engine instance count and marks the engine as initialised but closed. Returns the
// device status.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

extern "C" {
// Number of open engine instances. Volatile, like the instance reads below: the retail code keeps
// these accesses in source order and rereads the instance pointer after storing it.
extern volatile s32 lbl_8042C9A0;
// Static engine globals used before the engine is opened and after it is closed.
extern RwEngineGlobals lbl_803ED4E0;
}

static inline RwEngineGlobals* RwEngineInstanceReload(void)
{
	return *(RwEngineGlobals* volatile*)&lbl_8042C9A4;
}

extern "C" {
s32 fn_8019D79C(void)
{
	s32 ok = RwDeviceSystemRequest(RW_DEVICE_SYSTEM_CLOSE, 0, 0, 0);

	if (ok) {
		RwEngineGlobals* instance = lbl_8042C9A4;

		lbl_8042C9A4 = &lbl_803ED4E0;
		memcpy(RwEngineInstanceReload(), instance, sizeof(RwEngineGlobals));
		lbl_8042C9A4->rwfree(instance);
		lbl_8042C9A0--;
		RwEngineInstanceReload()->engineStatus = RW_ENGINE_STATUS_INITED;
	}
	return ok;
}
}
