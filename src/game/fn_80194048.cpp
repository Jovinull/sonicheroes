// Copies the instance's last error into error and resets it to "none" (HYPOTHESIS: RwErrorGet).
// Returns error.
#include "game/rw_engine.h"

// The retail code copies the record as two plain words; a struct copy through the named fields
// orders the loads and stores differently.
struct RwErrorWords {
	u32 w[2];
};

extern "C" {
RwError* fn_80194048(RwError* error)
{
	*(RwErrorWords*)error   = *(RwErrorWords*)&RW_LAST_ERROR;
	RW_LAST_ERROR.pluginID  = 0;
	RW_LAST_ERROR.errorCode = RW_ERROR_NONE;
	return error;
}
}
