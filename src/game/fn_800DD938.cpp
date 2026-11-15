// Stores a 12-byte record into slot `index` of the table lbl_803E7034. The record is copied word by
// word, so it is not declared with float members here (HYPOTHESIS: a position vector); the
// table's role and extent are UNKNOWN.
#include "types.h"

struct Record800DD938 {
	u32 words[3];
};

extern "C" {
extern Record800DD938 lbl_803E7034[];

void fn_800DD938(Record800DD938* record, s32 index)
{
	lbl_803E7034[index] = *record;
}
}
