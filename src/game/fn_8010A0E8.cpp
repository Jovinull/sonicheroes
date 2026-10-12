#include "types.h"

// This unique main region contains one setter and seven empty functions.
struct TFn8010A0E8Data {
	u8 mPadding0[0x20];
	s32 mValue20;
};

extern "C" void fn_8010A0E8(TFn8010A0E8Data* arg0)
{
	arg0->mValue20 = 3;
}

extern "C" void fn_8010A0F4(void) { }
extern "C" void fn_8010A0F8(void) { }
extern "C" void fn_8010A0FC(void) { }
extern "C" void fn_8010A100(void) { }
extern "C" void fn_8010A104(void) { }
extern "C" void fn_8010A108(void) { }
extern "C" void fn_8010A10C(void) { }
