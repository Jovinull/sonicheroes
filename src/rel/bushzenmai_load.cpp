#include "types.h"

// The wind-up bush's Load hook (bushzenmaiLoad here): the module's texture dictionary is
// made current, the family's material animation is set up, the model file's
// model is loaded and, once there, its atomics get the family's callback.

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct BushzenmaiMatAnim {
	u8 unk00[0x18];
} BushzenmaiMatAnim;

extern "C" ModelFile bushZenmaiModelFile[1];
extern "C" BushzenmaiMatAnim bushzenmaiMatAnim;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;

extern "C" void fn_801A4C84(void* dictionary);
extern "C" void fn_8015C728(BushzenmaiMatAnim* anim);
extern "C" void fn_8015C6F8(BushzenmaiMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(BushzenmaiMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(BushzenmaiMatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(BushzenmaiMatAnim* anim, s32 a);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_7_94A0C(void* atomic);

extern "C" void bushzenmaiLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_8015C728(&bushzenmaiMatAnim);
	fn_8015C6F8(&bushzenmaiMatAnim, 3, 4);
	fn_8015C704(&bushzenmaiMatAnim, 1, 0);
	fn_8015C710(&bushzenmaiMatAnim, 1, 3, 8);
	fn_8015C720(&bushzenmaiMatAnim, 3);
	ModelFile* files = bushZenmaiModelFile;

	for (int i = 0; i < 1; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
	}
	if (files->model != NULL) {
		fn_8014FFBC(files->model, fn_7_94A0C, NULL);
	}
}
