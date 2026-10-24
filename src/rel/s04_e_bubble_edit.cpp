#include "types.h"

// The s04EBubble object's EditOnChange (s04EBubbleEditOnChange here): it keeps
// each edited parameter within its bounds.
// The fields are named by their offsets (written with notes/tools/clampgen.py;
// the limits are the module's constants, which other code shares).

typedef struct S04EBubbleParams {
	u8 pad00[0x8];
	f32 f08; // 0x08
} S04EBubbleParams;

typedef struct S04EBubbleEdit {
	u8 unk00[0x2C];
	S04EBubbleParams* params; // 0x2C
} S04EBubbleEdit;

extern "C" const f32 s04EBubbleEditLimit[1];

extern "C" void s04EBubbleEditOnChange(void* object, S04EBubbleEdit* edit)
{
	S04EBubbleParams* params = edit->params;
	const f32* limit;

	if (params->f08 > *(limit = s04EBubbleEditLimit)) {
		params->f08 = *limit;
	}
}
