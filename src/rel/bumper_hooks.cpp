#include "types.h"

// The bumper family's Reset, Unload and Load hooks (bumperReset, bumperUnload
// and bumperLoad here): nothing to reset; the model files' models are released;
// the module's texture dictionary is made current, the family's material
// animation is set up and the module's model archive is read and each model
// file's model loaded, its atomics going through the family's callback when it
// loads and it is handed to the module's texture setup with each of the
// family's texture name prefixes.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" ModelFile bumperModelFiles[4];

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct MatAnim {
	u8 unk00[0x18];
} MatAnim;

extern "C" MatAnim bumperMatAnim;
extern "C" char bumperTexturePrefix1[];
extern "C" char bumperTexturePrefix2[];
extern "C" u8 lbl_5_bss_2668[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_80150958(void* clump);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_8015C728(MatAnim* anim);
extern "C" void fn_8015C6F8(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(MatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(MatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_5_8B3B0(void* atomic);
extern "C" void fn_5_A0238(void* setup, void* clump, char* prefix, s32 a, s32 b, s32 c);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void bumperReset(void) { }

extern "C" void bumperUnload(void)
{
	ModelFile* files = bumperModelFiles;

	for (int i = 0; i < 4; i++) {
		if (files[i].model != NULL) {
			fn_80150958(files[i].model);
			files[i].model = NULL;
		}
	}
}

extern "C" void bumperLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_8015C728(&bumperMatAnim);
	fn_8015C6F8(&bumperMatAnim, 3, 4);
	fn_8015C704(&bumperMatAnim, 1, 0);
	fn_8015C710(&bumperMatAnim, 1, 3, 8);
	fn_8015C720(&bumperMatAnim, 0);
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelFile* files = bumperModelFiles;

	for (int i = 0; i < 4; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
		if (files[i].model != NULL) {
			fn_8014FFBC(files[i].model, fn_5_8B3B0, NULL);
		}
		fn_5_A0238(lbl_5_bss_2668, files[i].model, bumperTexturePrefix1, 1, 2, 20);
		fn_5_A0238(lbl_5_bss_2668, files[i].model, bumperTexturePrefix2, 1, 2, 30);
	}
}
