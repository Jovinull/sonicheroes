#include "types.h"

// The large slot machine's Unload and Load hooks (slotlargeUnload and
// slotlargeLoad here). The Unload runs fn_5_A1090 and releases the model
// files' models. The Load makes the module's texture dictionary current, sets
// up the family's material animation and reads the module's model archive;
// each model file gets its model loaded, its atomics going through the
// family's callback, and handed to the module's texture setup with each of the
// family's two texture name prefixes; then fn_5_A10C8 runs and each of the
// eight strips gets its position, the running sum of the strips' lengths from
// the family's start.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

// one of the machine's strips: its length and its position
struct SlotlargeStrip {
	u8 unk00[0xC];  // 0x00
	f32 length;     // 0x0C
	f32 position;   // 0x10
	u8 unk14[0x14]; // 0x14
}; // 0x28

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct MatAnim {
	u8 unk00[0x18];
} MatAnim;

extern "C" ModelFile slotlargeModelFiles[19];
extern "C" SlotlargeStrip slotlargeStrips[8];
extern "C" const f32 slotlargeStripStart;
extern "C" MatAnim slotlargeMatAnim;
extern "C" char slotlargeTexturePrefix1[];
extern "C" char slotlargeTexturePrefix2[];
extern "C" u8 lbl_5_bss_2668[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_80150958(void* clump);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_5_A1090(void);
extern "C" s32 fn_5_A10C8(void);
extern "C" void fn_8015C728(MatAnim* anim);
extern "C" void fn_8015C6F8(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(MatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(MatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_5_972D4(void* atomic);
extern "C" void fn_5_A0238(void* setup, void* clump, char* prefix, s32 a, s32 b, s32 c);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void slotlargeUnload(void)
{
	fn_5_A1090();
	ModelFile* files = slotlargeModelFiles;

	for (int i = 0; i < 19; i++) {
		if (files[i].model != NULL) {
			fn_80150958(files[i].model);
			files[i].model = NULL;
		}
	}
}

extern "C" void slotlargeLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_8015C728(&slotlargeMatAnim);
	fn_8015C6F8(&slotlargeMatAnim, 3, 4);
	fn_8015C704(&slotlargeMatAnim, 1, 0);
	fn_8015C710(&slotlargeMatAnim, 1, 3, 8);
	fn_8015C720(&slotlargeMatAnim, 3);
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelFile* files = slotlargeModelFiles;

	for (int i = 0; i < 19; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
		if (files[i].model != NULL) {
			fn_8014FFBC(files[i].model, fn_5_972D4, NULL);
		}
		fn_5_A0238(lbl_5_bss_2668, files[i].model, slotlargeTexturePrefix1, 1, 4, 15);
		fn_5_A0238(lbl_5_bss_2668, files[i].model, slotlargeTexturePrefix2, 1, 2, 30);
	}
	fn_5_A10C8();
	f32 position          = slotlargeStripStart;
	SlotlargeStrip* strip = slotlargeStrips;
	for (int j = 0; j < 8; j++) {
		strip->position = position + strip->length;
		position        = strip->position;
		strip++;
	}
}
