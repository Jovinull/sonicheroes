#include "types.h"

// The truck rail's Unload and Load hooks (s01TruckRailUnload and
// s01TruckRailLoad here). The Unload releases each of the four rails'
// callback records (the first field through fn_800B8B48) and models, clears
// the shared record and releases the extra model, then marks the family as
// unloaded. The Load runs once until then: when the module's texture
// dictionary is there, it is kept and made current, the module's model archive
// is read and each rail's model loaded by its name, its atomics going through
// the rail callback with the rail's record (whose first field then goes
// through fn_800B8CC4); the extra model is loaded the same way with its own
// callback, and the family is marked as loaded.

// what the rail callback fills in for one rail
typedef struct S01TruckRailRecord {
	void* atomic; // 0x00
	void* unk04;
	void* unk08;
} S01TruckRailRecord; // 0xC

extern "C" void* s01TruckRailModels[4];
extern "C" S01TruckRailRecord s01TruckRailRecords[4];
extern "C" S01TruckRailRecord s01TruckRailExtraRecord;
extern "C" char* s01TruckRailModelNames[4];
extern "C" char s01TruckRailExtraName[];
extern "C" void* s01TruckRailDictionary;
extern "C" s32 s01TruckRailLoaded;
extern "C" void* s01TruckRailExtraModel;
extern "C" u8 lbl_3_bss_1808;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_800B8B48(void* atomic);
extern "C" void fn_800B8CC4(void* atomic, s32 flag);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_3_8FB40(void* atomic);
extern "C" void* fn_3_8FB14(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s01TruckRailUnload(void)
{
	for (s8 i = 0; i < 4; i++) {
		if (s01TruckRailRecords[i].atomic != NULL) {
			fn_800B8B48(s01TruckRailRecords[i].atomic);
			s01TruckRailRecords[i].atomic = NULL;
		}
		if (s01TruckRailRecords[i].unk04 != NULL) {
			s01TruckRailRecords[i].unk04 = NULL;
		}
		if (s01TruckRailRecords[i].unk08 != NULL) {
			s01TruckRailRecords[i].unk08 = NULL;
		}
		if (s01TruckRailModels[i] != NULL) {
			fn_80150958(s01TruckRailModels[i]);
			s01TruckRailModels[i] = NULL;
		}
	}
	s01TruckRailExtraRecord.atomic = NULL;
	s01TruckRailExtraRecord.unk04  = NULL;
	s01TruckRailExtraRecord.unk08  = NULL;
	if (s01TruckRailExtraModel != NULL) {
		fn_80150958(s01TruckRailExtraModel);
		s01TruckRailExtraModel = NULL;
	}
	s01TruckRailLoaded = 0;
}

extern "C" void s01TruckRailLoad(void)
{
	if (s01TruckRailLoaded != 0) {
		return;
	}
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		s01TruckRailDictionary = resource;
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	for (s32 i = 0; i < 4; i++) {
		s01TruckRailModels[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s01TruckRailModelNames[i]),
		    lbl_802FF5A0);
		if (s01TruckRailModels[i] != NULL) {
			lbl_3_bss_1808 = 0;
			fn_8014FFBC(s01TruckRailModels[i], fn_3_8FB40, &s01TruckRailRecords[i]);
			fn_800B8CC4(s01TruckRailRecords[i].atomic, 0);
		}
	}
	if ((s01TruckRailExtraModel = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	         CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s01TruckRailExtraName),
	         lbl_802FF5A0))
	    != NULL) {
		lbl_3_bss_1808 = 0;
		fn_8014FFBC(s01TruckRailExtraModel, fn_3_8FB14, NULL);
	}
	s01TruckRailLoaded = 1;
}
