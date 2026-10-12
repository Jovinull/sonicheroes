#include "types.h"

struct TFn8009CFC0Data {
	u8 mPadding0[0x39];
	s8 mMemberCount;
	u8 mPadding3A[0x114 - 0x3A];
	void* mMember;
	u8 mPadding118[0x20D - 0x118];
	u8 mStatus[0x80];
};

extern "C" void fn_8003FC44(void* arg0);
extern "C" void fn_80092814(void* arg0, void* arg1);

extern "C" void fn_8009CFC0(TFn8009CFC0Data* arg0)
{
	u8* var_r30;
	s32 var_r29;
	register u32 var_r31 = 0;

	var_r29 = 0;
	var_r30 = (u8*)arg0;

	while (var_r29 < arg0->mMemberCount) {
		TFn8009CFC0Data* temp_r30 = (TFn8009CFC0Data*)var_r30;
		fn_8003FC44(temp_r30->mMember);
		fn_80092814(arg0, (u8*)temp_r30->mMember + 0x760);
		arg0->mStatus[var_r29] = var_r31;
		var_r30 += 4;
		var_r29 += 1;
	}
}
