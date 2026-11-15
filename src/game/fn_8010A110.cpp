#include "types.h"

struct Obj8010A110 {
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	u8 pad[0x20 - 0x04];
	s32 f20; // 0x20
	u32 f24; // 0x24
};

extern "C" void fn_8010A110(Obj8010A110* self)
{
	self->f24 = self->f24 & 0xFFFFFFFD;
	self->v8();
	self->f20 = 1;
}
