#include "types.h"

// The pond's Load hook (pondLoad here): the module's texture dictionary is made
// current and each of its three entries loads its model and its second model
// from its archive, the second one going through fn_800BDF30. The dictionary
// also goes through fn_800BE274 before the models and fn_800BE1F4 after them.

typedef struct PondEntry {
	const char* name;  // 0x00
	const char* name2; // 0x04
	void* archive;     // 0x08
	u8 unk0C[0x8];
	void* model;  // 0x14
	void* model2; // 0x18
} PondEntry;      // 0x1C

extern "C" PondEntry pondTable[3];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_800BDF30(void* clump);
extern "C" void fn_800BE1F4(void* resource);
extern "C" void fn_800BE274(void* resource);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void pondLoad(void)
{
	fn_800BE274(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	PondEntry* table = pondTable;

	for (int i = 0; i < 3; i++) {
		table[i].model  = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), table[i].name),
		    table[i].archive);
		table[i].model2 = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), table[i].name2),
		    table[i].archive);
		fn_800BDF30(table[i].model2);
	}
	fn_800BE1F4(*(void**)(lbl_8042C1D0 + 0x8C18));
}
