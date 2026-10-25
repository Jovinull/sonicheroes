#include "types.h"

// The big cannon top's Unload and Load hooks (bigcannontopUnload and
// bigcannontopLoad here). The Unload releases each of its three animated model
// files' model and animation (resetting the matching aim record) and each of
// its four splines. The Load makes the module's texture dictionary current,
// reads the module's model archive and, for each animated model file, loads
// its model and, when it has one, its animation and the animation's key list,
// every file getting the family's frame step; then it loads each named spline.

struct DANIM_KEY;
struct RtAnimAnimation;

// one of the family's animated model files: the archive it is read from, the
// model's and the animation's names, the model and animation once loaded, the
// animation's key list and count, and its frame step
struct BigcannontopModelFile {
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

// one of the family's splines: its archive and name, and the spline once loaded
struct BigcannontopSpline {
	void* archive;    // 0x00
	const char* name; // 0x04
	u8 unk08[0x4];
	void* spline; // 0x0C
}; // 0x10

// the aim record reset with each model file
struct BigcannontopAim {
	s32 state;  // 0x00
	s32 target; // 0x04
	u8 unk08[0x8];
}; // 0x10

class HAnimClass
{
public:
	void GetHAnimKeyList(DANIM_KEY* keys, int count, RtAnimAnimation* animation);
};

extern "C" BigcannontopModelFile bigcannontopModelFiles[3];
extern "C" BigcannontopAim bigcannontopAims[3];
extern "C" BigcannontopSpline bigcannontopSplines[4];
extern "C" const f32 bigcannontopFrameStep;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];
extern HAnimClass HAnim;

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8020C2D8(void* animation);
extern "C" void fn_8014D8A4(void* spline);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadSplineEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void bigcannontopUnload(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (bigcannontopModelFiles[i].model != NULL) {
			fn_80150958(bigcannontopModelFiles[i].model);
		}
		if (bigcannontopModelFiles[i].animation != NULL) {
			fn_8020C2D8(bigcannontopModelFiles[i].animation);
		}
		bigcannontopAims[i].state  = 0;
		bigcannontopAims[i].target = -1;
	}
	for (i = 0; i < 4; i++) {
		if (bigcannontopSplines[i].spline != NULL) {
			fn_8014D8A4(bigcannontopSplines[i].spline);
		}
	}
}

extern "C" void bigcannontopLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	BigcannontopModelFile* files = bigcannontopModelFiles;
	for (int i = 0; i < 3; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
		if (files[i].anim != NULL) {
			files[i].animation
			    = (RtAnimAnimation*)LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].anim),
			        files[i].archive);
			HAnim.GetHAnimKeyList(files[i].keys, files[i].keyCount, files[i].animation);
		}
		files[i].step = bigcannontopFrameStep;
	}
	for (int i = 0; i < 4; i++) {
		if (bigcannontopSplines[i].name != NULL) {
			bigcannontopSplines[i].spline
			    = LoadSplineEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(
			            *(void**)(lbl_8042C298 + 0xA50), bigcannontopSplines[i].name),
			        bigcannontopSplines[i].archive);
		}
	}
}
