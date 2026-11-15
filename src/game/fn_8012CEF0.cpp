// Places a menu model and updates it (HYPOTHESIS; names inferred): when the object at 0xC exists,
// sets its frame from the matrix at 0x28 (fn_801733FC), applies the two angles at 0x1C and 0x20
// (the second negated, fn_801734F4) and refreshes the frame (fn_8017442C); then runs fn_8012C9D4
// over its parts with the parameters {1, value} (fn_80204144), followed by fn_802041EC and
// fn_802033F4.
#include "types.h"

struct Model8012CEF0 {
	u8 pad0[0xC];
	void* object; // 0xC
	u8 pad10[0x1C - 0x10];
	f32 angleA; // 0x1C
	f32 angleB; // 0x20
	u8 pad24[0x28 - 0x24];
	u8 matrix[0x40]; // 0x28
};

struct Param8012CEF0 {
	s32 enabled; // 0x0
	f32 value;   // 0x4
};

extern "C" {
void* fn_802043AC(void* object);
void fn_801733FC(void* frame, void* matrix);
void fn_801734F4(void* frame, f32 a, f32 b);
void fn_8017442C(void* frame);
void* fn_8012C9D4(void* part, void* cursor, void* arg, Param8012CEF0* param);
void fn_80204144(void* object,
    void* (*callback)(void* part, void* cursor, void* arg, Param8012CEF0* param),
    Param8012CEF0* data);
void fn_802041EC(void* object);
void fn_802033F4(void* object);

void fn_8012CEF0(Model8012CEF0* model, f32 value)
{
	Param8012CEF0 param;

	if (model->object != 0) {
		void* frame = fn_802043AC(model->object);
		fn_801733FC(frame, model->matrix);
		fn_801734F4(frame, model->angleA, -model->angleB);
		fn_8017442C(frame);
	}
	param.enabled = 1;
	param.value   = value;
	if (model->object != 0) {
		fn_80204144(model->object, fn_8012C9D4, &param);
		fn_802041EC(model->object);
		fn_802033F4(model->object);
	}
}
}
