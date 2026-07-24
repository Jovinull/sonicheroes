#include "types.h"

struct AutosaveState {
	u32 resource_0;
	u32 resource_1;
	u32 resource_2;
	u32 resource_3;
	s32 mode;
	f32 value_0;
	f32 value_1;
	f32 value_2;
	f32 value_3;
	f32 value_4;
	u8 remaining[0x1C];
};

struct Animation {
	u8 padding_0x0[4];
	f32 start;
	u8 padding_0x8[4];
	f32 end;
};

struct AnimationResource {
	u8 padding[8];
	Animation* animation;
};

struct Task {
	u8 base[0x18];
	void* methods;
	u16 flags;
	u16 size;
	u8 padding_0x20[8];
	f32 frame;
	void* callback;
	s32 counter;
	void* window;
};

extern u8 lbl_2_data_3C0[];
extern void* lbl_2_data_3BC;
extern AnimationResource lbl_2_data_314;
extern s32 lbl_2_bss_44;
extern void* lbl_8042C388;

extern const f32 lbl_2_rodata_88;
extern const f32 lbl_2_rodata_8C;
extern const f32 lbl_2_rodata_90;
extern const f32 lbl_2_rodata_94;
extern const f32 lbl_2_rodata_98;
extern const f32 lbl_2_rodata_9C;

extern "C" void fn_8012CC20(void* callback);
extern "C" void fn_2_13E0(Task* task);
extern "C" void fn_8012CEF0(void* callback, f32 frame);
extern "C" void fn_800B52E8(void* object, s32 id, s32 arg2, s32 arg3);
extern "C" void fn_80130464(s32 type);
extern "C" Task* dtor_800186D0(Task* task, s32 flags);
extern "C" void fn_2_13F4(void* memory);
extern "C" void fn_80018818(Task* task, void* context);
extern "C" void fn_2_4004(AutosaveState* state);
extern "C" u32 fn_8012ECA8(s32 group, s32 id);
extern "C" void* fn_2_3DF0(void* parent, AutosaveState* state);

extern "C" void fn_2_1FB4(Task* task)
{
	if (task->callback != NULL) {
		fn_8012CC20(task->callback);
	}
}

extern "C" void fn_2_1FE0(Task* task)
{
	s32 counter = task->counter++;

	if (counter > 300) {
		fn_2_13E0(task);
	} else {
		Animation* animation;

		task->frame += lbl_2_rodata_88;
		animation = lbl_2_data_314.animation;
		if (animation->end <= task->frame) {
			task->frame = animation->start;
		}

		if (task->callback != NULL) {
			fn_8012CEF0(task->callback, task->frame);
		}

		if (task->counter == 60 && lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x1034, 0, 0);
		}
	}
}

extern "C" Task* fn_2_20A8(Task* task, s16 flags)
{
	if (task != NULL) {
		task->methods = lbl_2_data_3C0;
		fn_80130464(2);
		dtor_800186D0(task, 0);

		if (flags > 0) {
			fn_2_13F4(task);
		}
	}

	return task;
}

extern "C" Task* fn_2_211C(Task* task, void* context)
{
	AutosaveState state;
	s32 index;

	fn_80018818(task, context);
	task->methods           = lbl_2_data_3C0;
	*(void**)&task->base[0] = lbl_2_data_3BC;
	task->size              = 0x38;
	task->frame             = lbl_2_rodata_8C;
	task->callback          = &lbl_2_data_314;
	task->counter           = 0;

	fn_2_4004(&state);

	switch (lbl_2_bss_44) {
		case 1:
			index = 0;
			break;
		case 2:
			index = 1;
			break;
		case 3:
			index = 2;
			break;
		case 4:
			index = 3;
			break;
		case 5:
			index = 4;
			break;
		case 6:
			index = 5;
			break;
		default:
			index = 0;
			break;
	}

	state.resource_0 = fn_8012ECA8(7, index);
	state.resource_1 = 0;
	state.resource_2 = 0;
	state.resource_3 = 0;
	state.mode       = 1;
	state.value_0    = lbl_2_rodata_90;
	state.value_1    = lbl_2_rodata_94;
	state.value_2    = lbl_2_rodata_8C;
	state.value_3    = lbl_2_rodata_98;
	state.value_4    = lbl_2_rodata_9C;
	task->window     = fn_2_3DF0(task, &state);

	return task;
}
