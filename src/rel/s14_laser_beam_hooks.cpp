#include "types.h"

// The laser beam's Unload and Load hooks (s14LaserBeamUnload and
// s14LaserBeamLoad here): its fifteen model records are released, then
// fn_9_A4F38 runs; when the module's texture dictionary is there, it is made
// current, the module's model archive is read and, between fn_800BE274 and
// fn_800BE1F4 on the dictionary, each model record is loaded; then fn_9_A4F94
// runs.

// one of the stage's larger model records (fn_9_76448 releases them,
// fn_9_765CC loads them)
typedef struct S13ModelRecord {
	u8 unk00[0x2C];
} S13ModelRecord; // 0x2C

extern "C" S13ModelRecord s14LaserBeamModels[15];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" char lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* dictionary);
extern "C" void fn_800BE274(void* dictionary);
extern "C" void fn_800BE1F4(void* dictionary);
extern "C" void LoadOneFile__7ONEFILEFPc(void* file, char* name);
extern "C" void fn_9_76448(S13ModelRecord* record);
extern "C" void fn_9_765CC(S13ModelRecord* record, const char* name);
extern "C" void fn_9_A4F38(void);
extern "C" void fn_9_A4F94(void);

extern "C" void s14LaserBeamUnload(void)
{
	S13ModelRecord* record = (S13ModelRecord*)s14LaserBeamModels;

	for (u8 i = 0; i < 15; i++) {
		fn_9_76448(record);
		record++;
	}
	fn_9_A4F38();
}

extern "C" void s14LaserBeamLoad(void)
{
	void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (dictionary != NULL) {
		fn_801A4C84(dictionary);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	fn_800BE274(*(void**)(lbl_8042C1D0 + 0x8C18));
	S13ModelRecord* record = (S13ModelRecord*)s14LaserBeamModels;
	for (u8 i = 0; i < 15; i++) {
		fn_9_765CC(record, NULL);
		record++;
	}
	fn_800BE1F4(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_9_A4F94();
}
