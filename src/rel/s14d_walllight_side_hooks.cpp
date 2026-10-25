#include "game/effect/eff_bomb.h"

// The side wall light's Unload and Load hooks (s14dWalllightSideUnload and
// s14dWalllightSideLoad here). Unless it is already released, the Unload
// deletes the object it keeps, forgets its three textures, releases its two
// model infos and marks it released and not loaded. When the module's texture
// dictionary is there, the Load makes it current, reads the module's model
// archive and loads each model info, keeping the material of each model's
// first atomic, looks each texture up by its name in the dictionary and marks
// it loaded and not released, unless it is already loaded.

// one of the stage's model infos (s13ModelInfoRelease and s13ModelInfoLoad
// handle them)
struct RpClump;

typedef struct S13ModelInfo {
	u8 unk00[0x10];
	RpClump* model; // 0x10
	u8 unk14[0x4];
} S13ModelInfo; // 0x18

// one of the family's textures: the texture once found and its name
typedef struct WalllightSideTexture {
	void* texture;      // 0x00
	char* name;         // 0x04
} WalllightSideTexture; // 0x08

// the parts of an RpAtomic and its RpGeometry read here
typedef struct RpGeometry {
	u8 unk00[0x20];
	void** materials; // 0x20: the material list's materials
} RpGeometry;

typedef struct RpAtomic {
	u8 unk00[0x18];
	RpGeometry* geometry; // 0x18
} RpAtomic;

extern "C" S13ModelInfo s14dWalllightSideModels[2];
extern "C" WalllightSideTexture s14dWalllightSideTextures[3];
extern "C" TObject* s14dWalllightSideObject;
extern "C" void* s14dWalllightSideMaterials[2];
extern "C" s32 s14dWalllightSideLoaded;
extern "C" s32 s14dWalllightSideReleased;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" char lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* dictionary);
extern "C" void* fn_801A4BBC(void* dictionary, char* name);
extern "C" void LoadOneFile__7ONEFILEFPc(void* file, char* name);
extern "C" void s13ModelInfoRelease(S13ModelInfo* info);
extern "C" void s13ModelInfoLoad(S13ModelInfo* info, const char* name);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* after);

extern "C" void s14dWalllightSideUnload(void)
{
	S13ModelInfo* file = (S13ModelInfo*)s14dWalllightSideModels;

	if (s14dWalllightSideReleased == 1) {
		return;
	}
	if (s14dWalllightSideObject != NULL) {
		delete s14dWalllightSideObject;
	}
	WalllightSideTexture* texture = s14dWalllightSideTextures;
	for (int j = 0; j < 3; j++) {
		texture->texture = NULL;
		texture++;
	}
	for (u8 i = 0; i < 2; i++) {
		s13ModelInfoRelease(file);
		file++;
	}
	s14dWalllightSideReleased = 1;
	s14dWalllightSideLoaded   = 0;
}

extern "C" void s14dWalllightSideLoad(void)
{
	if (s14dWalllightSideLoaded == 1) {
		return;
	}
	void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (dictionary != NULL) {
		fn_801A4C84(dictionary);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S13ModelInfo* file = s14dWalllightSideModels;

	for (s8 i = 0; i < 2; i++) {
		s13ModelInfoLoad(file, NULL);
		if (s14dWalllightSideModels[i].model != NULL) {
			RpAtomic* atomic = objRpClumpGetAtomic(s14dWalllightSideModels[i].model, NULL);
			if (atomic != NULL) {
				s14dWalllightSideMaterials[i] = atomic->geometry->materials[0];
			}
		}
		file++;
	}
	WalllightSideTexture* texture = (WalllightSideTexture*)s14dWalllightSideTextures;
	for (u8 i = 0; i < 3; i++) {
		texture->texture = fn_801A4BBC(*(void**)(lbl_8042C1D0 + 0x8C18), texture->name);
		texture++;
	}
	s14dWalllightSideLoaded   = 1;
	s14dWalllightSideReleased = 0;
}
