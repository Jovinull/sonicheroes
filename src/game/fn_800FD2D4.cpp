// Returns the table file name for id `id` (the counterpart of fn_800FD3A0, with the second name
// of each entry): the name at +0xC of its entry in the 48-entry table lbl_8025A4E8 when it has
// one; otherwise (or when the id is not in the table) the name built in the buffer lbl_803E71D0
// from the format lbl_8025A7E8 ("se_s%02d") and the index fn_800194A8 returns for lbl_8029C310,
// followed by the suffix lbl_8025A7F4 ("_tbl.bin"), or null when that index is negative. HYPOTHESIS: the per-stage sound-effect table file names.
#include "types.h"

struct Entry800FD2D4 {
	s32 id; // 0x0
	u8 pad4[4];
	char* name;      // 0x8
	char* tableName; // 0xC
};

extern "C" {
extern Entry800FD2D4 lbl_8025A4E8[0x30];
extern u8 lbl_8029C310[];
extern char lbl_803E71D0[0x20];
extern const char lbl_8025A7E8[];
extern const char lbl_8025A7F4[];
s32 fn_800194A8(void* state);
int sprintf(char* s, const char* format, ...);
char* strcat(char* dst, const char* src);
}

// The name built from the stage index, or null when there is none.
static inline char* BuildName(void)
{
	s32 index = fn_800194A8(lbl_8029C310);

	if (index < 0) {
		return NULL;
	}
	sprintf(lbl_803E71D0, lbl_8025A7E8, index);
	return lbl_803E71D0;
}

extern "C" char* fn_800FD2D4(s32 id)
{
	Entry800FD2D4* entry = lbl_8025A4E8;
	u8 i;

	for (i = 0; i < 0x30; i++, entry++) {
		if (id == entry->id) {
			if (entry->tableName != NULL) {
				return entry->tableName;
			}
			break;
		}
	}
	if (BuildName() != NULL) {
		strcat(lbl_803E71D0, lbl_8025A7F4);
		return lbl_803E71D0;
	}
	return NULL;
}
