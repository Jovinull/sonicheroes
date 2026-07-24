#include "types.h"

struct Pair {
	u32 first;
	u32 second;
};

struct AutosaveState {
	u32 unk_0x0;
	u32 resource_1;
	u32 resource_2;
	u32 resource_3;
	s32 mode;
	Pair unk_0x14;
	u32 unk_0x1C;
	Pair unk_0x20;
	Pair unk_0x28;
	Pair unk_0x30;
	u32 unk_0x38;
	u32 unk_0x3C;
	u32 unk_0x40;
};

struct Selector {
	u8 data[0x8C];
};

struct AutosaveWindow {
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
};

struct Resource;
struct Archive;

extern void* lbl_2_data_43C[];
extern void* lbl_2_data_438;
extern char lbl_2_data_468[];
extern char* lbl_2_data_418[5];
extern u8 lbl_803E8150[];
extern Archive* lbl_2_bss_50;
extern u32 lbl_2_bss_54[5];

extern "C" const f32 lbl_2_rodata_348;

extern "C" void fn_2_4798(void* selector, s32 flags);
extern "C" void dtor_800186D0(void* window, s32 flags);
extern "C" void fn_2_13F4(void* allocation);
extern "C" void fn_80018818(AutosaveWindow* window, void* parent);
extern "C" void fn_2_4004(AutosaveState* state);
extern "C" void fn_2_47DC(Selector* selector);
extern "C" void fn_8012EBD4(void* widget, u32 resource);
extern "C" void fn_2_477C(Selector* selector, s32 value);
extern "C" u32 fn_8012EF3C(void* manager, u32 resource);
extern "C" u32 fn_8012ECA8(s32 group, s32 id);
extern "C" void fn_2_4074(Selector* selector, s32 index);
extern "C" AutosaveWindow* fn_2_1424(u32 size);
extern "C" void fn_2_3D64(AutosaveState* destination, const AutosaveState* source);
extern "C" Resource* fn_80057644(u32 size);
extern "C" Resource* fn_800BCC84(Resource* resource, const char* path, s32 flags);
extern "C" void* fn_80012994(u32 size);
extern "C" Archive* fn_800BC580(Resource* resource, s32 type, void* buffer);
extern "C" void* fn_801A4BBC(Archive* archive, const char* name);
extern "C" void fn_800126C8(void* buffer);
extern "C" void fn_800BCBD4(Resource* resource, s32 free);
extern "C" void fn_801A46D0(Archive* archive);

static inline void copy_pair(Pair* destination, const volatile Pair* source)
{
	u32 first  = source->first;
	u32 second = source->second;

	destination->first  = first;
	destination->second = second;
}

static inline f32 resource_to_float(u32 value)
{
	return (f32)value;
}

static inline Resource* create_resource(void)
{
	Resource* resource = fn_80057644(0x58);
	if (resource != NULL) {
		resource = fn_800BCC84(resource, lbl_2_data_468, 0);
	}
	return resource;
}

extern "C" AutosaveWindow* fn_2_3A70(AutosaveWindow* window, s32 flags)
{
	if (window != NULL) {
		window->methods = lbl_2_data_43C;
		fn_2_4798(&window->selector, -1);
		dtor_800186D0(window, 0);
		if ((s16)flags > 0) {
			fn_2_13F4(window);
		}
	}
	return window;
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

extern "C" void fn_2_3D64(AutosaveState* destination, const AutosaveState* source)
{
	destination->unk_0x0    = source->unk_0x0;
	destination->resource_1 = source->resource_1;
	destination->resource_2 = source->resource_2;
	destination->resource_3 = source->resource_3;
	destination->mode       = source->mode;
	copy_pair(&destination->unk_0x14, &source->unk_0x14);
	destination->unk_0x1C = source->unk_0x1C;
	copy_pair(&destination->unk_0x20, &source->unk_0x20);
	copy_pair(&destination->unk_0x28, &source->unk_0x28);
	copy_pair(&destination->unk_0x30, &source->unk_0x30);
	destination->unk_0x38 = source->unk_0x38;
	destination->unk_0x3C = source->unk_0x3C;
	destination->unk_0x40 = source->unk_0x40;
}

extern "C" AutosaveWindow* fn_2_3DF0(void* parent, AutosaveState* state)
{
	AutosaveWindow* window;

	window = fn_2_1424(0x838);
	if (window != NULL) {
		window = fn_2_3AE8(window, parent, state);
	}
	return window;
}

extern "C" void fn_2_3E4C(void)
{
	u32* asset = lbl_2_bss_54;
	s32 i;

	for (i = 0; i != 5; i++) {
		*asset++ = 0;
	}

	if (lbl_2_bss_50 != NULL) {
		fn_801A46D0(lbl_2_bss_50);
		lbl_2_bss_50 = NULL;
	}
}

extern "C" void fn_2_3EC0(void)
{
	Resource* resource;
	void* buffer;
	s32 i;

	resource = create_resource();

	if (resource != NULL) {
		buffer = fn_80012994(0x300000);
		if (buffer != NULL) {
			lbl_2_bss_50 = fn_800BC580(resource, 2, buffer);
			if (lbl_2_bss_50 != NULL) {
				for (i = 0; i != 5; i++) {
					void* entry = fn_801A4BBC(lbl_2_bss_50, lbl_2_data_418[i]);
					if (entry != NULL) {
						lbl_2_bss_54[i] = *(u32*)entry;
					}
				}
			}
			fn_800126C8(buffer);
		}
		fn_800BCBD4(resource, 1);
	}
}
