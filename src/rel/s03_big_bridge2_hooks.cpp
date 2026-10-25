#include "types.h"

// The second big bridge's Unload and Load hooks (s03BigBridge2Unload and
// s03BigBridge2Load here): each of its 13 parts' animation and model are
// released (the first part's model through fn_800B8ADC first), the data the
// part callback gets being cleared; when the module's texture dictionary is
// there, it is made current, the module's model archive is read and each part
// loaded by its name with the model and animation extensions, the animation's
// length kept. The first part's model then goes through fn_800B8BEC, the
// others' atomics through the family's callback (with the first byte of
// lbl_4_bss_11FC cleared first).

// one of the bridge's parts: the model and its animation once loaded, what the
// callback gets, the animation's length and the part's file name
typedef struct S03BigBridge2Part {
	void* model;      // 0x00
	void* animation;  // 0x04
	u32 data;         // 0x08
	f32 duration;     // 0x0C
	const char* name; // 0x10
} S03BigBridge2Part;  // 0x14

extern "C" u8 s03BigBridge2Parts[];
extern "C" char s03BigBridge2NameFormat[];
extern "C" char s03BigBridge2AnimationFormat[];
extern "C" u8 lbl_4_bss_11FC[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_800B8ADC(void* clump);
extern "C" void fn_800B8BEC(void* clump, s32 flag);
extern "C" void fn_8020C2D8(void* animation);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_4_759CC(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s03BigBridge2Unload(void)
{
	S03BigBridge2Part* part = (S03BigBridge2Part*)s03BigBridge2Parts;

	for (u8 i = 0; i < 13; i++) {
		if (part->animation != NULL) {
			fn_8020C2D8(part->animation);
			part->animation = NULL;
		}
		part->data = 0;
		if (part->model != NULL) {
			if (i == 0) {
				fn_800B8ADC(part->model);
			}
			fn_80150958(part->model);
			part->model = NULL;
		}
		part++;
	}
}

extern "C" void s03BigBridge2Load(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S03BigBridge2Part* part = (S03BigBridge2Part*)s03BigBridge2Parts;

	for (u8 i = 0; i < 13; i++) {
		sprintf(name, s03BigBridge2NameFormat, part->name);
		part->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		sprintf(name, s03BigBridge2AnimationFormat, part->name);
		part->animation = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (part->animation != NULL) {
			part->duration = *(f32*)((u8*)part->animation + 0xC);
		}
		if (part->model != NULL) {
			if (i == 0) {
				fn_800B8BEC(part->model, 0);
			} else {
				lbl_4_bss_11FC[0] = 0;
				fn_8014FFBC(part->model, fn_4_759CC, &part->data);
			}
		}
		part++;
	}
}
