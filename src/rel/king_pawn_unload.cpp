#include "types.h"

// The king pawn's unload hook (kingPawnUnload here): releases its path, its
// six UV animations, its fifteen models and its two buffers (each forgotten),
// resets its animated model files' frame steps while releasing their
// animations, and destroys its texture dictionary.

struct RtAnimAnimation;

// one of the fight's animated model files: its animation first, its frame step
// at 0x18
struct AnimFile {
	RtAnimAnimation* anim; // 0x00
	u8 unk04[0x14];
	f32 step; // 0x18
	u8 unk1C[0x8];
}; // 0x24

extern "C" void* lbl_10_bss_101C;
extern "C" void* lbl_10_bss_1000[6];
extern "C" void* lbl_10_bss_FC4[15];
extern "C" void* lbl_10_bss_FBC[2];
extern "C" void* lbl_10_bss_1018;
extern "C" AnimFile lbl_10_data_6508[2];
extern "C" AnimFile lbl_10_data_6290[17];
extern "C" const f32 lbl_10_rodata_1234;
extern "C" u8* lbl_8042C9A4;

extern "C" void fn_8014D8A4(void* path);
extern "C" void fn_8011B7CC(void* anim);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8020C2D8(RtAnimAnimation* anim);
extern "C" void fn_801A46D0(void* dictionary);

extern "C" void kingPawnUnload(void)
{
	int i;

	if (lbl_10_bss_101C != NULL) {
		fn_8014D8A4(lbl_10_bss_101C);
		lbl_10_bss_101C = NULL;
	}
	for (i = 0; i != 6; i++) {
		if (lbl_10_bss_1000[i] != NULL) {
			fn_8011B7CC(lbl_10_bss_1000[i]);
			lbl_10_bss_1000[i] = NULL;
		}
	}
	for (i = 0; i != 15; i++) {
		if (lbl_10_bss_FC4[i] != NULL) {
			fn_80150958(lbl_10_bss_FC4[i]);
			lbl_10_bss_FC4[i] = NULL;
		}
	}
	for (i = 0; i != 2; i++) {
		if (lbl_10_bss_FBC[i] != NULL) {
			(*(void (**)(void*))(lbl_8042C9A4 + 0x138))(lbl_10_bss_FBC[i]);
			lbl_10_bss_FBC[i] = NULL;
		}
	}
	for (i = 0; i < 1; i++) {
		lbl_10_data_6508[i].step = lbl_10_rodata_1234;
		if (lbl_10_data_6508[i].anim != NULL) {
			fn_8020C2D8(lbl_10_data_6508[i].anim);
			lbl_10_data_6508[i].anim = NULL;
		}
	}
	for (i = 0; i != 16; i++) {
		lbl_10_data_6290[i].step = lbl_10_rodata_1234;
		if (lbl_10_data_6290[i].anim != NULL) {
			fn_8020C2D8(lbl_10_data_6290[i].anim);
			lbl_10_data_6290[i].anim = NULL;
		}
	}
	if (lbl_10_bss_1018 != NULL) {
		fn_801A46D0(lbl_10_bss_1018);
		lbl_10_bss_1018 = NULL;
	}
}
