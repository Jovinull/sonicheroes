#include "cri/lsc.h"
#include "cri/stm.h"
#include "MSL_C/string.h"

// LSC initialization and shutdown; two surviving functions.
// Independent banner/count/pool ownership supports this inferred boundary.

const char lbl_8023FF00[]                      = "\nLSC/GC Ver.2.11 Build:May  9 2003 17:09:53\n";
static const char* const volatile lbl_8023FF30 = lbl_8023FF00;
static s32 lsc_InitCount                       = 0;
LscObj lsc_ObjTbl[LSC_OBJ_MAX];

void fn_802201E0(void)
{
	s8 crs[8];
	s32 i;

	fn_8021F524(crs);
	if (--lsc_InitCount == 0) {
		for (i = 0; i < LSC_OBJ_MAX; i++) {
			if (lsc_ObjTbl[i].used == 1) {
				fn_8021FF7C(&lsc_ObjTbl[i]);
			}
		}
		memset(lsc_ObjTbl, 0, sizeof(lsc_ObjTbl));
		fn_8021F4D0(0, 0);
	}
	fn_8021F504(crs);
}

void fn_80220284(void)
{
	s8 crs[8];

	lbl_8023FF30;
	fn_8021F524(crs);
	if (lsc_InitCount == 0) {
		memset(lsc_ObjTbl, 0, sizeof(lsc_ObjTbl));
		fn_8021F4D0(0, 0);
	}
	lsc_InitCount++;
	fn_8021F504(crs);
}
