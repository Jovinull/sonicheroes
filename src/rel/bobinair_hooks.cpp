#include "types.h"

// The bobinair family's Reset, Unload and Load hooks (bobinairReset,
// bobinairUnload and bobinairLoad here): nothing to reset; the model file's
// model is released; the module's texture dictionary is made current, the
// family's material animation is set up and the module's model archive is read
// and the model file's model loaded, its atomics going through the family's
// callback when it loads and it is handed to the module's texture setup with
// the family's texture name prefix.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

extern "C" ModelFile bobinAirModelFile[1];

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct MatAnim {
	u8 unk00[0x18];
} MatAnim;

extern "C" MatAnim bobinairMatAnim;
extern "C" char bobinairTexturePrefix[];
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
extern "C" void* fn_5_89C6C(void* atomic);
extern "C" void fn_5_A0238(void* setup, void* clump, char* prefix, s32 a, s32 b, s32 c);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void bobinairReset(void) { }

extern "C" void bobinairUnload(void)
{
	ModelFile* files = bobinAirModelFile;

	for (int i = 0; i < 1; i++) {
		if (files[i].model != NULL) {
			fn_80150958(files[i].model);
			files[i].model = NULL;
		}
	}
}

extern "C" void bobinairLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_8015C728(&bobinairMatAnim);
	fn_8015C6F8(&bobinairMatAnim, 3, 4);
	fn_8015C704(&bobinairMatAnim, 1, 0);
	fn_8015C710(&bobinairMatAnim, 1, 3, 8);
	fn_8015C720(&bobinairMatAnim, 0);
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelFile* files = bobinAirModelFile;

	for (int i = 0; i < 1; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
		if (files[i].model != NULL) {
			fn_8014FFBC(files[i].model, fn_5_89C6C, NULL);
		}
		fn_5_A0238(lbl_5_bss_2668, files[i].model, bobinairTexturePrefix, 1, 2, 15);
	}
}
