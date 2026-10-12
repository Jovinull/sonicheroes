#include "types.h"

struct TFn8011B81CData {
	u32 mPadding0;
	s32 mArgument;
};

extern "C" void fn_8020D02C(s32 arg0);

extern "C" s32 fn_8011B81C(TFn8011B81CData* arg0)
{
	fn_8020D02C(arg0->mArgument);
	return 1;
}
