#include "types.h"

// TObjTreeleaf::EditOnChange (the PS2 build's name; treeleafEditOnChange
// here): an edited size of zero becomes 1, and the size is kept at 0.1 at
// least.

typedef struct TreeleafParams {
	f32 size; // 0x00
} TreeleafParams;

typedef struct TreeleafEdit {
	u8 unk00[0x2C];
	TreeleafParams* params; // 0x2C
} TreeleafEdit;

extern "C" const f32 treeleafEditUnset[1];
extern "C" const f32 treeleafEditDefault[1];
extern "C" const f32 treeleafEditMin[1];

extern "C" void treeleafEditOnChange(void* object, TreeleafEdit* edit)
{
	TreeleafParams* params = edit->params;

	if (treeleafEditUnset[0] == params->size) {
		params->size = treeleafEditDefault[0];
	}
	const f32* min;
	if (params->size < *(min = treeleafEditMin)) {
		params->size = *min;
	}
}
