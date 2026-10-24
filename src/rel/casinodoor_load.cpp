#include "types.h"

// The casino door's Load hook (casinodoorLoad here): the module's texture
// dictionary is made current and its model archive read; each of its two
// animated model files gets its model loaded and, when it has one, its
// animation and, once that loaded, the animation's key list, every file
// getting the family's frame step; each model that loaded is then handed to
// the module's texture setup with each of the family's eight texture name
// prefixes.

struct DANIM_KEY;
struct RtAnimAnimation;

// one of the door's animated model files: the archive it is read from, the
// model's and the animation's names, the model and animation once loaded, the
// animation's key list and count, and its frame step
struct AnimModelFile {
	void* archive;              // 0x00
	const char* name;           // 0x04
	const char* anim;           // 0x08
	void* model;                // 0x0C
	RtAnimAnimation* animation; // 0x10
	DANIM_KEY* keys;            // 0x14
	s32 keyCount;               // 0x18
	f32 step;                   // 0x1C
	u8 unk20[0x4];              // 0x20
}; // 0x24

class HAnimClass
{
public:
	void GetHAnimKeyList(DANIM_KEY* keys, int count, RtAnimAnimation* animation);
};

extern "C" AnimModelFile casinodoorModelFiles[2];
extern "C" const f32 casinodoorFrameStep;
extern "C" char casinodoorTexturePrefix1[];
extern "C" char casinodoorTexturePrefix2[];
extern "C" char casinodoorTexturePrefix3[];
extern "C" char casinodoorTexturePrefix4[];
extern "C" char casinodoorTexturePrefix5[];
extern "C" char casinodoorTexturePrefix6[];
extern "C" char casinodoorTexturePrefix7[];
extern "C" char casinodoorTexturePrefix8[];
extern "C" u8 lbl_5_bss_2668[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];
extern HAnimClass HAnim;

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_5_A0238(void* setup, void* clump, char* prefix, s32 a, s32 b, s32 c);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void casinodoorLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	AnimModelFile* files = casinodoorModelFiles;
	for (int i = 0; i < 2; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
		if (files[i].anim != NULL) {
			files[i].animation
			    = (RtAnimAnimation*)LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].anim),
			        files[i].archive);
			if (files[i].animation != NULL) {
				HAnim.GetHAnimKeyList(files[i].keys, files[i].keyCount, files[i].animation);
			}
		}
		files[i].step = casinodoorFrameStep;
		if (files[i].model != NULL) {
			fn_5_A0238(lbl_5_bss_2668, files[i].model, casinodoorTexturePrefix1, 1, 3, 15);
			fn_5_A0238(lbl_5_bss_2668, files[i].model, casinodoorTexturePrefix2, 1, 4, 15);
			fn_5_A0238(lbl_5_bss_2668, files[i].model, casinodoorTexturePrefix3, 1, 4, 15);
			fn_5_A0238(lbl_5_bss_2668, files[i].model, casinodoorTexturePrefix4, 1, 4, 15);
			fn_5_A0238(lbl_5_bss_2668, files[i].model, casinodoorTexturePrefix5, 1, 4, 15);
			fn_5_A0238(lbl_5_bss_2668, files[i].model, casinodoorTexturePrefix6, 1, 4, 15);
			fn_5_A0238(lbl_5_bss_2668, files[i].model, casinodoorTexturePrefix7, 1, 3, 15);
			fn_5_A0238(lbl_5_bss_2668, files[i].model, casinodoorTexturePrefix8, 1, 4, 15);
		}
	}
}
