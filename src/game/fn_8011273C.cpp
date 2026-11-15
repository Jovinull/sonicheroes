// Switches the shared archive to one of the built-in data blocks (HYPOTHESIS; names inferred):
// destroys the texture dictionary held in slot 0 of lbl_802636A0 (fn_801A46D0), creates the shared
// ONEFILE in slot 1 on first use and points it at entry `index` of the block table lbl_80288B28
// (buffer and size). Returns 1.
#include "game/one.h"

struct ArchiveSlots8011273C {
	RwTexDictionary* dictionary; // 0x0
	ONEFILE* file;               // 0x4
	u8 pad8[0x20 - 0x8];
};

struct DataBlock8011273C {
	void* buffer; // 0x0
	s32 size;     // 0x4
};

extern "C" {
extern ArchiveSlots8011273C lbl_802636A0;
extern DataBlock8011273C lbl_80288B28[];
// HYPOTHESIS: RwTexDictionaryDestroy.
void fn_801A46D0(RwTexDictionary* dictionary);

s32 fn_8011273C(s32 index)
{
	if (lbl_802636A0.dictionary != 0) {
		fn_801A46D0(lbl_802636A0.dictionary);
		lbl_802636A0.dictionary = 0;
	}
	if (lbl_802636A0.file == 0) {
		lbl_802636A0.file = new ONEFILE(0, 0);
	}
	lbl_802636A0.file->SetOneFile(lbl_80288B28[index].buffer, lbl_80288B28[index].size, 0);
	return 1;
}
}
