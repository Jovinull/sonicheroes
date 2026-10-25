#include "game/one.h"

// The king pawn's load hook (kingPawnLoad here): with a 0xAF000-byte work
// buffer it opens the fight's archive and loads from it the texture dictionary
// (filtered and made current), the sixteen and the one animations of its
// animated model files, its two cameras, fifteen models and six UV animations;
// each of the six model and animation pairs whose two halves loaded gets the
// animation through its FX record; every model modulates its material colour,
// those marked so ignoring lights too; then the path is loaded, the archive
// closed and the buffer freed.

enum RwTextureFilterMode {
	rwFILTERLINEARMIPLINEAR = 6,
};

// the FX record handed to SetClumpCustomFXTexture: its UV animation first
struct UVFXInfo {
	RpUVAnimAnimation* anim; // 0x00
	u8 unk04[0x40];
}; // 0x44

// one of the fight's animated model files: its animation first
struct AnimFile {
	RtAnimAnimation* anim; // 0x00
	u8 unk04[0x20];
}; // 0x24

// a model and the UV animation it is given
struct FxPair {
	s32 model; // 0x00
	s32 anim;  // 0x04
};

void objChangeTextureFilterMode(RwTexDictionary* dict, RwTextureFilterMode mode);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);
void objRpClumpForAllGeometrysToModulateMaterialColor(RpClump* clump);
void SetClumpCustomFXTexture(RpClump* clump, UVFXInfo* info);
extern "C" void* fn_80012994(u32 size);
extern "C" void fn_800126C8(void* buffer);

extern "C" RpSpline* lbl_10_bss_101C;
extern "C" RpUVAnimAnimation* lbl_10_bss_1000[6];
extern "C" RpClump* lbl_10_bss_FC4[15];
extern "C" NJS_MOTION* lbl_10_bss_FBC[2];
extern "C" RwTexDictionary* lbl_10_bss_1018;
extern "C" UVFXInfo lbl_10_bss_1024[6];
extern "C" AnimFile lbl_10_data_6508[2];
extern "C" AnimFile lbl_10_data_6290[17];
extern "C" char lbl_10_data_6664[];
extern "C" const u32 lbl_10_rodata_106C[16];
extern "C" const u32 lbl_10_rodata_10AC[1];
extern "C" const u32 lbl_10_rodata_10B0[15];
extern "C" const s32 lbl_10_rodata_10EC[15];
extern "C" const u32 lbl_10_rodata_1128[6];
extern "C" const u32 lbl_10_rodata_1140[2];
extern "C" const FxPair lbl_10_rodata_1148[6];

extern "C" void fn_801A4C84(RwTexDictionary* dictionary);

extern "C" void kingPawnLoad(void)
{
	u32 j;
	int i;

	void* buffer = fn_80012994(0xAF000);
	if (buffer == NULL) {
		return;
	}
	ONEFILE* file = new ONEFILE(lbl_10_data_6664, 0);
	if (file != NULL) {
		lbl_10_bss_1018 = file->OneFileLoadTextureDictionay(2, buffer);
		if (lbl_10_bss_1018 != NULL) {
			objChangeTextureFilterMode(lbl_10_bss_1018, rwFILTERLINEARMIPLINEAR);
		}
		fn_801A4C84(lbl_10_bss_1018);
		for (i = 0; i != 16; i++) {
			lbl_10_data_6290[i].anim = file->OneFileLoadHAnimation(lbl_10_rodata_106C[i], buffer);
		}
		for (i = 0; i != 1; i++) {
			lbl_10_data_6508[i].anim = file->OneFileLoadHAnimation(lbl_10_rodata_10AC[i], buffer);
		}
		for (i = 0; i != 2; i++) {
			lbl_10_bss_FBC[i] = file->OneFileLoadCameraTmb(lbl_10_rodata_1140[i], buffer);
		}
		for (i = 0; i != 15; i++) {
			lbl_10_bss_FC4[i] = file->OneFileLoadClump(lbl_10_rodata_10B0[i], buffer);
		}
		for (i = 0; i != 6; i++) {
			lbl_10_bss_1000[i] = file->OneFileLoadUVAnim(lbl_10_rodata_1128[i], buffer);
		}
		for (j = 0; j != 6; j++) {
			const FxPair* pair = &lbl_10_rodata_1148[j];
			if (lbl_10_bss_FC4[pair->model] != NULL && lbl_10_bss_1000[pair->anim] != NULL) {
				lbl_10_bss_1024[pair->anim].anim = lbl_10_bss_1000[pair->anim];
				SetClumpCustomFXTexture(lbl_10_bss_FC4[pair->model], &lbl_10_bss_1024[pair->anim]);
			}
		}
		for (i = 0; i != 15; i++) {
			if (lbl_10_rodata_10EC[i] == 0) {
				objRpClumpForAllGeometrysToIgnoreLights(lbl_10_bss_FC4[i]);
			}
			objRpClumpForAllGeometrysToModulateMaterialColor(lbl_10_bss_FC4[i]);
		}
		lbl_10_bss_101C = file->OneFileLoadSpline(0x2A, buffer);
		delete file;
	}
	fn_800126C8(buffer);
}
