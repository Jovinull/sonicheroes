#include "types.h"

// s13ModelInfoLoad, which the stage 13 and 14 families' Load hooks run over
// their model infos: the model is loaded from the module's archive under the
// name given (or the info's own), and its flags (the info's second set on
// stage 15 when the info asks for it) choose what is done to it: two kinds of
// set-up (fn_800B8BEC), fn_800BDF30, fn_8003C640, ignoring lights, modulating
// the material colour, and an atomic walk (s13ModelInfoAtomicCallback) with the stage's shared
// material animation, made on first use.

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

// the shared material animation (fn_8015C6F8 and its neighbours set it up)
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
extern "C" char s13ModelInfoNameFormat[];
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" RpClump* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void fn_800B8BEC(RpClump* clump, s32 a);
extern "C" void fn_800BDF30(RpClump* clump);
extern "C" void fn_8003C640(RpClump* clump);
extern "C" void fn_8015C728(MatAnim* anim);
extern "C" void fn_8015C6F8(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(MatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(MatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(RpClump* clump, void* (*callback)(void*), void* data);
extern "C" void* s13ModelInfoAtomicCallback(void* atomic);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);
void objRpClumpForAllGeometrysToModulateMaterialColor(RpClump* clump);

// the stage's shared material animation, made and set up on first use
inline MatAnim* s13ModelInfoGetMatAnim(void)
{
	if (s13ModelInfoMatAnim != NULL) {
		return s13ModelInfoMatAnim;
	}
	s13ModelInfoMatAnim = (MatAnim*)operator new(sizeof(MatAnim));
	if (s13ModelInfoMatAnim != NULL) {
		fn_8015C728(s13ModelInfoMatAnim);
		fn_8015C6F8(s13ModelInfoMatAnim, 3, 4);
		fn_8015C704(s13ModelInfoMatAnim, 1, 0);
		fn_8015C710(s13ModelInfoMatAnim, 1, 3, 6);
		fn_8015C720(s13ModelInfoMatAnim, 3);
		return s13ModelInfoMatAnim;
	}
	return NULL;
}

extern "C" void s13ModelInfoLoad(S13ModelInfo* info, const char* name)
{
	char path[64];
	s32 stage            = lbl_8029C310.stage;
	S13ModelFlags* flags = &info->flags;

	if ((info->flags.bits & 0x200) && stage == 15) {
		flags = &info->stage15Flags;
	}
	sprintf(path, s13ModelInfoNameFormat, name != NULL ? name : info->name);
	info->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), path), lbl_802FF5A0);
	if (info->model == NULL) {
		return;
	}
	if (flags->bits & 0x1) {
		fn_800B8BEC(info->model, 0);
	}
	if (flags->bits & 0x4) {
		fn_800B8BEC(info->model, 0);
	}
	if (flags->bits & 0x10) {
		fn_800BDF30(info->model);
	}
	if (flags->bits & 0x20) {
		fn_8003C640(info->model);
	}
	if (flags->bits & 0x8) {
		objRpClumpForAllGeometrysToIgnoreLights(info->model);
	}
	if (flags->bits & 0x40) {
		objRpClumpForAllGeometrysToModulateMaterialColor(info->model);
	}
	if (flags->bits & 0x400) {
		RpClump* model = info->model;
		MatAnim* anim  = s13ModelInfoGetMatAnim();
		if (anim != NULL) {
			fn_8014FFBC(model, s13ModelInfoAtomicCallback, anim);
		}
	}
}
