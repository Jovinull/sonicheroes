#include "types.h"

extern "C" {
f32 fn_802012B8(void* o);
extern f32 lbl_8042DE54;

void* fn_800C4758(void* arg0, void* arg1, void* arg2, f32* arg3)
{
	f32 temp_f1;
	f32 var_f31;

	var_f31 = *arg3;
	temp_f1 = fn_802012B8(arg1);
	while (temp_f1 < var_f31) {
		var_f31 -= temp_f1;
	}
	while (var_f31 < lbl_8042DE54) {
		var_f31 += temp_f1;
	}
	*arg3 = var_f31;
	return arg0;
}
}
