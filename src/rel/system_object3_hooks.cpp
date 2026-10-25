#include "types.h"

// The reset, unload and load hooks rel/system_object3_register.cpp puts in the
// systemObject3's editor record. Reset and unload have nothing to do; load
// hands the scene to the engine entry point fn_8005B268.

extern "C" void* lbl_8042C298;

extern "C" void fn_8005B268(void* scene);

extern "C" void systemObject3Reset(void) { }

extern "C" void systemObject3Unload(void) { }

extern "C" void systemObject3Load(void)
{
	fn_8005B268(lbl_8042C298);
}
