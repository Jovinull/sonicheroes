#include "types.h"

// The 456 dice's Load hook (obj456diceLoad here): the module's texture
// dictionary is made current, the family's material animation is set up, the
// module's model archive is read and the model file's model loaded; when it
// is there, its atomics go through the family's callback, and it then goes
// through fn_800B8BEC.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct MatAnim {
	u8 unk00[0x18];
} MatAnim;

extern "C" ModelFile obj456diceModelFile[1];
extern "C" MatAnim obj456diceMatAnim;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_800B8BEC(void* clump, s32 flag);
extern "C" void fn_8015C728(MatAnim* anim);
extern "C" void fn_8015C6F8(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(MatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(MatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_5_8E5C8(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void obj456diceLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_8015C728(&obj456diceMatAnim);
	fn_8015C6F8(&obj456diceMatAnim, 3, 4);
	fn_8015C704(&obj456diceMatAnim, 1, 0);
	fn_8015C710(&obj456diceMatAnim, 1, 3, 8);
	fn_8015C720(&obj456diceMatAnim, 0);
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelFile* files = obj456diceModelFile;

	for (int i = 0; i < 1; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
	}
	if (files->model != NULL) {
		fn_8014FFBC(files->model, fn_5_8E5C8, NULL);
	}
	fn_800B8BEC(files->model, 0);
}
