// Hooked render step: when fn_8014535C accepts target, makes sure the object's +0x18 sub-object has
// a shared state block in its plugin slot (lbl_8042C930, defaulting to lbl_8042C830 through
// fn_8015C878), runs the saved callback lbl_8042C844 with the mode reported by fn_8015C39C switched
// off around it when it is 1, and on success applies the state to target through fn_80145004 with
// the sub-object's +0x14 word. Otherwise it only runs the saved callback. Names are UNKNOWN. Returns
// the saved callback's result.
#include "types.h"

struct Sub801427C4 {
	unsigned char pad0[0x14];
	unsigned int f14; // 0x14
};

struct Object801427C4 {
	unsigned char pad0[0x18];
	Sub801427C4* sub; // 0x18
};

extern "C" {
extern void* (*lbl_8042C844)(Object801427C4* object, void* target);
extern s32 lbl_8042C930;
extern void* lbl_8042C830;
s32 fn_8014535C(void* target);
void fn_8015C878(void* object, void* shared);
s32 fn_8015C39C(void);
void fn_8015C394(s32 mode);
void fn_80145004(void* target, void* state, u32 value);

void* fn_801427C4(Object801427C4* object, void* target)
{
	if (fn_8014535C(target) != 0) {
		Sub801427C4* sub = object->sub;
		void* shared     = *(void**)((u8*)sub + lbl_8042C930);
		s32 mode;
		if (shared == 0) {
			fn_8015C878(sub, lbl_8042C830);
			shared = lbl_8042C830;
		}
		mode = fn_8015C39C();
		if (mode == 1) {
			fn_8015C394(0);
		}
		object = (Object801427C4*)lbl_8042C844(object, target);
		if (mode == 1) {
			fn_8015C394(1);
		}
		if (object != 0) {
			fn_80145004(target, shared, sub->f14);
		}
		return object;
	}
	return lbl_8042C844(object, target);
}
}
