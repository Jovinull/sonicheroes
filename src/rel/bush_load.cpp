#include "types.h"

// The bush's Load hook (bushLoad here): the module's texture dictionary is
// made current, the family's material animation is set up, the model file's
// model is loaded and, once there, its atomics get the family's callback.

// the model file: its name, the archive it is read from and the model once
// loaded
typedef struct BushEntry {
	const char* name; // 0x00
	void* archive;    // 0x04
	void* model;      // 0x08
} BushEntry;

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct BushMatAnim {
	u8 unk00[0x18];
} BushMatAnim;

extern "C" BushEntry bushModelFile[1];
extern "C" BushMatAnim bushMatAnim;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;

extern "C" void fn_801A4C84(void* dictionary);
extern "C" void fn_8015C728(BushMatAnim* anim);
extern "C" void fn_8015C6F8(BushMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(BushMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(BushMatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(BushMatAnim* anim, s32 a);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_7_71668(void* atomic);

extern "C" void bushLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_8015C728(&bushMatAnim);
	fn_8015C6F8(&bushMatAnim, 3, 6);
	fn_8015C704(&bushMatAnim, 1, 0);
	fn_8015C710(&bushMatAnim, 1, 1, 6);
	fn_8015C720(&bushMatAnim, 3);
	BushEntry* files = bushModelFile;

	for (int i = 0; i < 1; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
	}
	if (files->model != NULL) {
		fn_8014FFBC(files->model, fn_7_71668, NULL);
	}
}
