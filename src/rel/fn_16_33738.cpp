#include "types.h"

extern "C" {
void* __nw__10TObjSampleFUl(u32 size);
void* fn_16_33400(void* obj, void* owner);
extern void* lbl_8042C110;

void fn_16_33738(void)
{
	void* p = __nw__10TObjSampleFUl(0xD4);
	if (p) {
		p = fn_16_33400(p, lbl_8042C110);
	}
}
}
