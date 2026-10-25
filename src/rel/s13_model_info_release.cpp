#include "types.h"

// s13ModelInfoRelease, which the stage 13 and 14 families' Unload hooks run
// over their model infos: when the info holds a model, its flags (the info's
// second set on stage 15 when the info asks for it) choose what is undone
// (fn_800B8ADC for each of the two set-ups, and, for the atomic walk, the
// shared material animation and the word next to it are deleted and
// forgotten), then the model is released and forgotten.

struct RpClump;

// the flags of a model info
typedef struct S13ModelFlags {
	u16 bits; // 0x00
} S13ModelFlags;

// one of the stage's model infos
typedef struct S13ModelInfo {
	S13ModelFlags flags; // 0x00
	u8 unk02[0x6];
	S13ModelFlags stage15Flags; // 0x08
	u8 unk0A[0x6];
	RpClump* model;   // 0x10
	const char* name; // 0x14
} S13ModelInfo;       // 0x18

// the shared material animation (s13ModelInfoLoad makes it)
typedef struct MatAnim {
	u8 unk00[0x18];
} MatAnim;

// the game state: only the stage is read here
typedef struct GameState {
	u8 unk00[0x2C];
	s32 stage; // 0x2C
} GameState;

extern "C" GameState lbl_8029C310;
extern "C" MatAnim* s13ModelInfoMatAnim;
extern "C" void* s13ModelInfoMatAnimData;

extern "C" void fn_800B8ADC(RpClump* clump);
extern "C" void fn_80150958(RpClump* clump);

extern "C" void s13ModelInfoRelease(S13ModelInfo* info)
{
	s32 stage            = lbl_8029C310.stage;
	S13ModelFlags* flags = &info->flags;

	if ((info->flags.bits & 0x200) && stage == 15) {
		flags = &info->stage15Flags;
	}
	if (info->model == NULL) {
		return;
	}
	if (flags->bits & 0x1) {
		fn_800B8ADC(info->model);
	}
	if (flags->bits & 0x4) {
		fn_800B8ADC(info->model);
	}
	if (flags->bits & 0x400) {
		if (s13ModelInfoMatAnim != NULL) {
			delete s13ModelInfoMatAnim;
			s13ModelInfoMatAnim = NULL;
		}
		if (s13ModelInfoMatAnimData != NULL) {
			delete (u8*)s13ModelInfoMatAnimData;
			s13ModelInfoMatAnimData = NULL;
		}
	}
	fn_80150958(info->model);
	info->model = NULL;
}
