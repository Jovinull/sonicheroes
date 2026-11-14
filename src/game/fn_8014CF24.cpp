// Opens the module around 0x8014A3A0 for one engine instance (HYPOTHESIS: the "Open" counterpart
// of fn_8014CE74): the first instance runs fn_8014A9F0 and builds the heap blocks for entries 4 to
// 10 of the table lbl_803EC568 (fn_8014AC68, freeing the ones already built when one fails); a
// failure records error 3 of plugin 0x102 and returns null. Counts the instance and returns it.
#include "game/rw_engine.h"

extern "C" {
extern RwModuleInfo lbl_8042C8A8;
extern void* lbl_803EC568[12];

s32 fn_8014A9F0(void);
void* fn_8014AC68(s32 index);
}

static inline s32 BuildTables(void)
{
	s32 i;
	for (i = 4; i <= 10; i++) {
		void* block     = fn_8014AC68(i);
		lbl_803EC568[i] = block;
		if (!block) {
			for (i--; i >= 4; i--) {
				lbl_8042C9A4->rwfree(lbl_803EC568[i]);
				lbl_803EC568[i] = 0;
			}
			return 0;
		}
	}
	return 1;
}

static inline void RecordOpenError(void)
{
	RwError error;
	error.pluginID  = 0x102;
	error.errorCode = fn_8019408C(3);
	fn_80193FE8(&error);
}

extern "C" {
void* fn_8014CF24(void* instance)
{
	if (lbl_8042C8A8.numInstances == 0) {
		if (!fn_8014A9F0()) {
			RecordOpenError();
			return 0;
		}
		if (!BuildTables()) {
			RecordOpenError();
			return 0;
		}
	}
	lbl_8042C8A8.numInstances++;
	return instance;
}
}
