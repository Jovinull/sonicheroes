#include "types.h"

// The leafaa object's EditOnChange (leafaaEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct LeafaaParams {
	f32 f00; // 0x00
} LeafaaParams;

typedef struct LeafaaEdit {
	u8 unk00[0x2C];
	LeafaaParams* params; // 0x2C
} LeafaaEdit;

extern "C" void leafaaEditOnChange(void* object, LeafaaEdit* edit)
{
	LeafaaParams* params = edit->params;

	if (params->f00 < 0.1f) {
		params->f00 = 0.1f;
	}
}
