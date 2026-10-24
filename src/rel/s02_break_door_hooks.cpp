#include "types.h"

// The breakable door's Unload and Load hooks (s02BreakdoorUnload and
// s02BreakdoorLoad here): each of its five models is released, and the data
// its callback gets cleared; when the module's texture dictionary is there, it
// is made current, then the module's model archive is read and each model not
// loaded yet is loaded by its name. The second model's atomics go through the
// family's callback, with the first byte of lbl_3_bss_18CC cleared first.

// what the family's callback gets
typedef struct S02BreakdoorCallbackData {
	u32 unk00;
	u32 unk04;
} S02BreakdoorCallbackData;

extern "C" char* s02BreakdoorModelNames[5];
extern "C" void* s02BreakdoorModels[5];
extern "C" S02BreakdoorCallbackData s02BreakdoorCallbackData;
extern "C" u8 lbl_3_bss_18CC[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_3_93AE0(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s02BreakdoorUnload(void)
{
	for (u8 i = 0; i < 5; i++) {
		if (s02BreakdoorModels[i] != NULL) {
			fn_80150958(s02BreakdoorModels[i]);
			s02BreakdoorModels[i] = NULL;
		}
	}
	s02BreakdoorCallbackData.unk00 = 0;
	s02BreakdoorCallbackData.unk04 = 0;
}

extern "C" void s02BreakdoorLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	for (u8 i = 0; i < 5; i++) {
		if (s02BreakdoorModels[i] == NULL) {
			s02BreakdoorModels[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(
			        *(void**)(lbl_8042C298 + 0xA50), s02BreakdoorModelNames[i]),
			    lbl_802FF5A0);
		}
	}
	if (s02BreakdoorModels[1] != NULL) {
		lbl_3_bss_18CC[0] = 0;
		fn_8014FFBC(s02BreakdoorModels[1], fn_3_93AE0, &s02BreakdoorCallbackData);
	}
}
