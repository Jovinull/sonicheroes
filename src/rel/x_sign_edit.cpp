#include "types.h"

// TObjXSign::EditOnChange (the PS2 build's name; xSignEditOnChange
// here): an edited size of zero becomes 1, and the size is kept at 0.1 at
// least.

typedef struct XSignParams {
	f32 size; // 0x00
} XSignParams;

typedef struct XSignEdit {
	u8 unk00[0x2C];
	XSignParams* params; // 0x2C
} XSignEdit;

extern "C" const f32 xSignEditUnset[1];
extern "C" const f32 xSignEditDefault[1];
extern "C" const f32 xSignEditMin[1];

extern "C" void xSignEditOnChange(void* object, XSignEdit* edit)
{
	XSignParams* params = edit->params;

	if (xSignEditUnset[0] == params->size) {
		params->size = xSignEditDefault[0];
	}
	const f32* min;
	if (params->size < *(min = xSignEditMin)) {
		params->size = *min;
	}
}
