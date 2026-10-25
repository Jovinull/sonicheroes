#include "game/effect/eff_bomb.h"

// The wall neon's Unload and Load hooks (s14dWallNeonUnload and
// s14dWallNeonLoad here): the object it keeps is deleted, its four textures
// forgotten and its model info released; when the module's texture dictionary
// is there, it is made current, the module's model archive is read and the
// model info loaded, the material of its model's first atomic being kept, and
// each texture is looked up by its name in the dictionary.

// one of the stage's model infos (s13ModelInfoRelease and s13ModelInfoLoad
// handle them)
struct RpClump;

typedef struct S13ModelInfo {
	u8 unk00[0x10];
	RpClump* model; // 0x10
	u8 unk14[0x4];
} S13ModelInfo; // 0x18

// one of the family's textures: the texture once found and its name
typedef struct WallNeonTexture {
	void* texture; // 0x00
	char* name;    // 0x04
} WallNeonTexture; // 0x08

// the parts of an RpAtomic and its RpGeometry read here
typedef struct RpGeometry {
	u8 unk00[0x20];
	void** materials; // 0x20: the material list's materials
} RpGeometry;

typedef struct RpAtomic {
	u8 unk00[0x18];
	RpGeometry* geometry; // 0x18
} RpAtomic;

extern "C" S13ModelInfo s14dWallNeonModels[1];
extern "C" WallNeonTexture s14dWallNeonTextures[4];
extern "C" TObject* s14dWallNeonObject;
extern "C" void* s14dWallNeonMaterial;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" char lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* dictionary);
extern "C" void* fn_801A4BBC(void* dictionary, char* name);
extern "C" void LoadOneFile__7ONEFILEFPc(void* file, char* name);
extern "C" void s13ModelInfoRelease(S13ModelInfo* info);
extern "C" void s13ModelInfoLoad(S13ModelInfo* info, const char* name);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* after);

extern "C" void s14dWallNeonUnload(void)
{
	S13ModelInfo* file = (S13ModelInfo*)s14dWallNeonModels;

	if (s14dWallNeonObject != NULL) {
		delete s14dWallNeonObject;
	}
	WallNeonTexture* texture = s14dWallNeonTextures;
	for (int j = 0; j < 4; j++) {
		texture->texture = NULL;
		texture++;
	}
	for (u8 i = 0; i < 1; i++) {
		s13ModelInfoRelease(file);
		file++;
	}
}

extern "C" void s14dWallNeonLoad(void)
{
	void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (dictionary != NULL) {
		fn_801A4C84(dictionary);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S13ModelInfo* file = s14dWallNeonModels;

	for (s8 i = 0; i < 1; i++) {
		s13ModelInfoLoad(file, NULL);
		if (s14dWallNeonModels[i].model != NULL) {
			RpAtomic* atomic = objRpClumpGetAtomic(s14dWallNeonModels[i].model, NULL);
			if (atomic != NULL) {
				s14dWallNeonMaterial = atomic->geometry->materials[0];
			}
		}
		file++;
	}
	WallNeonTexture* texture = (WallNeonTexture*)s14dWallNeonTextures;
	for (u8 i = 0; i < 4; i++) {
		texture->texture = fn_801A4BBC(*(void**)(lbl_8042C1D0 + 0x8C18), texture->name);
		texture++;
	}
}
