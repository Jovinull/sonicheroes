#include "types.h"

typedef struct AutosaveState {
	u32 unk_0x0;
	u32 resource_1;
	u32 resource_2;
	u32 resource_3;
	s32 mode;
	u8 unk_0x14[0x18];
	u32 value;
	u32 unk_0x30;
	u32 option;
	u8 unk_0x38[0xC];
} AutosaveState;

typedef struct Selector {
	u8 data[0x8C];
} Selector;

typedef struct AutosaveWindow {
	u8 base[0x18];
	void* methods;
	u8 unk_0x1C[2];
	u16 size;
	u8 unk_0x20[8];
	AutosaveState state;
	u32 unk_0x6C;
	u32 unk_0x70;
	Selector selector;
	u32 selection_state;
	f32 resource_value_1;
	f32 resource_value_2;
	f32 resource_value_3;
	u8 widgets[0x728];
} AutosaveWindow;

extern void* lbl_2_data_43C[];
extern void* lbl_2_data_438;
extern u8 lbl_803E8150[];

extern "C" const f32 lbl_2_rodata_348;

extern "C" void fn_80018818(AutosaveWindow* window, void* parent);
extern "C" void fn_2_4004(AutosaveState* state);
extern "C" void fn_2_47DC(Selector* selector);
extern "C" void fn_2_3D64(AutosaveState* destination, const AutosaveState* source);
extern "C" void fn_8012EBD4(void* widget, u32 resource);
extern "C" void fn_2_477C(Selector* selector, s32 value);
extern "C" u32 fn_8012EF3C(void* manager, u32 resource);
extern "C" u32 fn_8012ECA8(s32 group, s32 id);
extern "C" void fn_2_4074(Selector* selector, s32 index);

static inline f32 resource_to_float(u32 value)
{
	return (f32)value;
}

extern "C" AutosaveWindow* fn_2_3AE8(AutosaveWindow* window, void* parent, AutosaveState* state)
{
	fn_80018818(window, parent);
	window->methods = lbl_2_data_43C;
	fn_2_4004(&window->state);
	fn_2_47DC(&window->selector);
	*(void**)&window->base[0] = lbl_2_data_438;
	window->size              = 0x838;
	fn_2_3D64(&window->state, state);
	window->unk_0x6C        = 0;
	window->selection_state = 1;

	fn_8012EBD4(&window->widgets[0x0], state->unk_0x0);
	fn_8012EBD4(&window->widgets[0x400], state->resource_1);
	if (state->resource_1 != 0) {
		fn_2_477C(&window->selector, 1);
		window->resource_value_1 = resource_to_float(fn_8012EF3C(lbl_803E8150, state->resource_1));
	} else {
		window->resource_value_1 = lbl_2_rodata_348;
	}

	fn_8012EBD4(&window->widgets[0x500], state->resource_2);
	if (state->resource_2 != 0) {
		fn_2_477C(&window->selector, 2);
		window->resource_value_2 = resource_to_float(fn_8012EF3C(lbl_803E8150, state->resource_2));
	} else {
		window->resource_value_2 = lbl_2_rodata_348;
	}

	fn_8012EBD4(&window->widgets[0x600], state->resource_3);
	if (state->resource_3 != 0) {
		fn_2_477C(&window->selector, 3);
		window->resource_value_3 = resource_to_float(fn_8012EF3C(lbl_803E8150, state->resource_3));
	} else {
		window->resource_value_3 = lbl_2_rodata_348;
	}

	switch (state->mode) {
		case 0:
		case 2:
			window->unk_0x70 = 0;
			break;
		case 1:
			window->unk_0x70 = 0;
			break;
	}

	if (window->state.resource_1 == fn_8012ECA8(0, 0x54)
	    || window->state.resource_1 == fn_8012ECA8(0, 0x56)) {
		if (window->state.resource_3 != 0) {
			window->selection_state = 3;
			fn_2_4074(&window->selector, 2);
		} else {
			window->selection_state = 2;
			fn_2_4074(&window->selector, 1);
		}
	}

	return window;
}
