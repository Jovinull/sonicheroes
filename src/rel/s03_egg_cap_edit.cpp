#include "types.h"

// The egg capsule's EditOnChange (s03EggCapEditOnChange here): its kind is
// kept between 1 and 2 in one game mode and between 0 and 1 in the others,
// and the editor's three fields are named for it.

typedef struct S03EggCapParams {
	s8 kind; // 0x00
} S03EggCapParams;

typedef struct S03EggCapEdit {
	u8 unk00[0x2C];
	S03EggCapParams* params; // 0x2C
} S03EggCapEdit;

// the game state: only the mode is read here
typedef struct EggCapGameState {
	u8 unk00[0x2C];
	s32 mode; // 0x2C
} EggCapGameState;

extern "C" EggCapGameState lbl_8029C310;

extern "C" const char* s03EggCapFieldNames[];
extern "C" const char* s03EggCapFields0[];
extern "C" const char* s03EggCapFields1[];
extern "C" const char* s03EggCapFields2[];

extern "C" void s03EggCapEditOnChange(void* object, S03EggCapEdit* edit)
{
	S03EggCapParams* params = edit->params;

	if (lbl_8029C310.mode == 4) {
		if (params->kind < 1) {
			params->kind = 1;
		}
		if (params->kind >= 3) {
			params->kind = 2;
		}
	} else {
		if (params->kind < 0) {
			params->kind = 0;
		}
		if (params->kind > 1) {
			params->kind = 1;
		}
	}
	s03EggCapFieldNames[0] = s03EggCapFields0[params->kind];
	s03EggCapFieldNames[1] = s03EggCapFields1[params->kind];
	s03EggCapFieldNames[2] = s03EggCapFields2[params->kind];
}
