#include "types.h"
struct Obj80178220 {
	int f0;
	int f4;
	int f8;
	int fC;
	int f10;
	int f14;
	int f18;
};

struct RwError80178220 {
	int pluginID;
	int errorCode;
};

extern "C" {
s32 fn_8019408C(s32 code, ...);
void* fn_80193FE8(void* error);

void* fn_80178220(void* obj, Obj80178220* o)
{
	if ((obj != 0) && (o != 0)) {
		int r;
		int v;
		int q;
		int f8;
		int fC;
		o->f0 = 8;
		v     = 0x10;
		o->f4 = 0xE;
		o->f8 = *(volatile int*)&o->f0 + 1;
		o->fC = *(volatile int*)&o->f4 + 1;
		f8    = o->f8;
		fC    = o->fC;
		do {
			v += v;
			q = v / f8;
			r = (q + 0x5A) / q;
		} while (v < r * fC);
		o->f10 = 0x5B;
		o->f14 = q;
		o->f18 = r;
		return obj;
	}
	RwError80178220 error;
	error.pluginID  = 0x180;
	error.errorCode = fn_8019408C(0x80000016);
	fn_80193FE8(&error);
	return 0;
}
}
