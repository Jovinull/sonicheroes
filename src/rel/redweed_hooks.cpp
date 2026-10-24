#include "types.h"

// The redweed family's Reset and Unload hooks (redweedReset and redweedUnload
// here): nothing to reset; the model file's model is released. Its Load does
// more and is not here.

// the model file, its model at 0x18
typedef struct RedweedFile {
	u8 unk00[0x18];
	void* model; // 0x18
} RedweedFile;

extern "C" RedweedFile redweedModelFile;

extern "C" void fn_8013BD74(void* object);

extern "C" void redweedReset(void) { }

extern "C" void redweedUnload(void)
{
	fn_8013BD74(redweedModelFile.model);
}
