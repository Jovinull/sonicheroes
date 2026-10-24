#include "types.h"

// The mushanim family's Reset and Unload hooks (mushanimReset and
// mushanimUnload here): nothing to reset; the model file's model is released.
// Its Load does more and is not here.

// the model file, its model at 0xC
typedef struct MushanimFile {
	u8 unk00[0xC];
	void* model; // 0xC
} MushanimFile;

extern "C" MushanimFile mushanimModelFile;

extern "C" void fn_8013BD74(void* object);

extern "C" void mushanimReset(void) { }

extern "C" void mushanimUnload(void)
{
	fn_8013BD74(mushanimModelFile.model);
}
