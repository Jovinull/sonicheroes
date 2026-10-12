#include "types.h"

// The objSecollision object's EditOnChange (objSecollisionEditOnChange here): it keeps
// each edited parameter within its bounds and names the editor's fields for the values that pick them.
// The fields are named by their offsets (written with notes/tools/clampgen.py).

typedef struct ObjSecollisionParams {
	u8 pad00[0x4];
	s8 f04; // 0x04
	u8 f05; // 0x05
	u8 pad06[0x1];
	s8 f07;  // 0x07
	s16 f08; // 0x08
} ObjSecollisionParams;

typedef struct ObjSecollisionEdit {
	u8 unk00[0x2C];
	ObjSecollisionParams* params; // 0x2C
} ObjSecollisionEdit;

extern "C" const char* objSecollisionFieldNames[];
extern "C" const char* objSecollisionFields0[];
extern "C" const char* objSecollisionFields1[];
extern "C" const char* objSecollisionFields2[];

extern "C" void objSecollisionEditOnChange(void* object, ObjSecollisionEdit* edit)
{
	ObjSecollisionParams* params = edit->params;

	if (params->f04 < 0) {
		params->f04 = 0;
	}
	if (params->f04 >= 6) {
		params->f04 = 5;
	}
	if (params->f05 > 1) {
		params->f05 = 1;
	}
	if (params->f08 < 0) {
		params->f08 = 0;
	}
	if (params->f07 < 0) {
		params->f07 = 0;
	}
	if (params->f07 >= 2) {
		params->f07 = 1;
	}
	objSecollisionFieldNames[1] = objSecollisionFields0[params->f04];
	objSecollisionFieldNames[2] = objSecollisionFields1[params->f05];
	objSecollisionFieldNames[4] = objSecollisionFields2[params->f07];
}
