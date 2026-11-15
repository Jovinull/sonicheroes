// Places a menu model and plays it at a rate (HYPOTHESIS: the timed twin of fn_8012CEF0; names
// inferred): sets up the frame of the object at 0xC as fn_8012CEF0 does, then runs fn_8012C9D4 over
// its parts with mode 1 and the value when the rate is lbl_8042EDD0, otherwise with mode 0 and the
// time step lbl_8042EDCC * value * rate, followed by fn_802041EC and fn_802033F4.
// NonMatching: the second multiply of the time step has its operands swapped (1 word); every
// grouping and operand order of the product, a compound assignment and a const constant give the
// same or more.
#include "types.h"

struct Model8012CE00 {
	u8 pad0[0xC];
	void* object; // 0xC
	u8 pad10[0x1C - 0x10];
	f32 angleA; // 0x1C
	f32 angleB; // 0x20
	u8 pad24[0x28 - 0x24];
	u8 matrix[0x40]; // 0x28
};

struct Param8012CE00 {
	s32 enabled; // 0x0
	f32 value;   // 0x4
};

extern "C" {
extern f32 lbl_8042EDCC;
extern f32 lbl_8042EDD0;
void* fn_802043AC(void* object);
void fn_801733FC(void* frame, void* matrix);
void fn_801734F4(void* frame, f32 a, f32 b);
void fn_8017442C(void* frame);
void* fn_8012C9D4(void* part, void* cursor, void* arg, Param8012CE00* param);
void fn_80204144(void* object,
    void* (*callback)(void* part, void* cursor, void* arg, Param8012CE00* param),
    Param8012CE00* data);
void fn_802041EC(void* object);
void fn_802033F4(void* object);

void fn_8012CE00(Model8012CE00* model, f32 value, f32 rate)
{
	Param8012CE00 param;

	if (model->object != 0) {
		void* frame = fn_802043AC(model->object);
		fn_801733FC(frame, model->matrix);
		fn_801734F4(frame, model->angleA, -model->angleB);
		fn_8017442C(frame);
	}
	if (lbl_8042EDD0 != rate) {
		param.enabled = 0;
		param.value   = lbl_8042EDCC * value * rate;
	} else {
		param.enabled = 1;
		param.value   = value;
	}
	if (model->object != 0) {
		fn_80204144(model->object, fn_8012C9D4, &param);
		fn_802041EC(model->object);
		fn_802033F4(model->object);
	}
}
}
