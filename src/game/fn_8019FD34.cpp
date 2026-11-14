// Sets the image search path (HYPOTHESIS: RwImageSetPath): grows the path buffer kept in the
// image module globals when the new path (with its terminator) does not fit, recording core
// error 0x80000013 (out of memory, with the size) and returning null if that fails, then copies
// the path in. Returns the path.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

extern "C" {
const char* fn_8019FD34(const char* path)
{
	s32 size = lbl_8042C9A4->rwstrlen(path) + 1;

	if (size > RW_IMAGE_PATH_SIZE) {
		char* buffer = (char*)lbl_8042C9A4->rwrealloc(RW_IMAGE_PATH, size);
		if (!buffer) {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
			fn_80193FE8(&error);
			return 0;
		}
		RW_IMAGE_PATH      = buffer;
		RW_IMAGE_PATH_SIZE = size;
	}
	memcpy(RW_IMAGE_PATH, path, size);
	return path;
}
}
