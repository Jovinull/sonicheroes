#include "types.h"

struct TFn8003C618 {
	u8 mPadding0[2];
	s16 mValue2;
	s16 mValue4;
	s16 mValue6;
	s16 mValue8;
	s16 mValueA;
	u8 mPaddingC[4];
	s32 mValue10;
	u8 mPadding14[0x64];
	s32 mValue78;
};

extern "C" void __ct__7C_COLLIFv(TFn8003C618* self)
{
	self->mValue10 = 0;
	self->mValue8  = 0;
	self->mValue2  = 0;
	self->mValueA  = 0;
	self->mValue4  = 1;
	self->mValue6  = 1;
	self->mValue78 = 0;
}
