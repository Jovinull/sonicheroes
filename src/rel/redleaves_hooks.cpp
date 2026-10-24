#include "types.h"

// The redleaves family's Reset and Unload hooks (redleavesReset and
// redleavesUnload here): nothing to reset; the model file's model is released.
// Its Load does more and is not here.

// the model file, its model at 0xC
typedef struct RedleavesFile {
	u8 unk00[0xC];
	void* model; // 0xC
} RedleavesFile;

extern "C" RedleavesFile redleavesModelFile;

extern "C" void fn_8013BD74(void* object);

extern "C" void redleavesReset(void) { }

extern "C" void redleavesUnload(void)
{
	fn_8013BD74(redleavesModelFile.model);
}
