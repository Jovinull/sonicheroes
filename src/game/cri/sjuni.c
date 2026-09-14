#include "cri/sjuni.h"
#include "MSL_C/string.h"

// Two surviving GC SJUNI functions, 0x80221574..0x80221610. The separate
// initialization count and 3072-byte workspace correlate with PS2 symbolic
// metadata. This inferred boundary does not reconstruct absent PS2 methods.

static s32 sjuni_init_cnt;
static u8 sjuni_obj[0xC00];

void fn_80221574(void)
{
	sjuni_init_cnt--;
	if (sjuni_init_cnt == 0) {
		memset(sjuni_obj, 0, sizeof(sjuni_obj));
	}
}

void fn_802215BC(void)
{
	if (sjuni_init_cnt == 0) {
		memset(sjuni_obj, 0, sizeof(sjuni_obj));
	}
	sjuni_init_cnt++;
}
