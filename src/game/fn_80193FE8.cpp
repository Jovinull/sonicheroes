// Records an error as the instance's last error unless one is already pending
// (HYPOTHESIS: RwErrorSet); codes with the top bit set are stored without a plugin ID. Returns
// error.
#include "game/rw_engine.h"

extern "C" {
RwError* fn_80193FE8(RwError* error)
{
	if (RW_LAST_ERROR.pluginID == 0 && RW_LAST_ERROR.errorCode == RW_ERROR_NONE) {
		if (error->errorCode & 0x80000000) {
			RW_LAST_ERROR.pluginID = 0;
		} else {
			RW_LAST_ERROR.pluginID = error->pluginID;
		}
		RW_LAST_ERROR.errorCode = error->errorCode;
	}
	return error;
}
}
