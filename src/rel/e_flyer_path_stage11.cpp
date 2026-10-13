#include "types.h"

// stage11D's flyer path strategy: the TEnemyStrategy the flyer
// (rel/e_flyer_stage11.cpp) runs while it follows its path, its per-mode
// handlers, the mode transition test (AA100) and the dispatcher, and the
// strategy's ctor/dtors with their two vtables.

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))

/* The vector the stage 11 units carry unreferenced at the head of their
 * .rodata (see e_capture_collision_stage11.cpp). */
struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

#pragma force_active on
static const RwV3d lbl_8_rodata_1A10 = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

/* Dispatch view of the strategy's vtable. The handler at vtable offset 0x10 is
 * reached through genuine virtual dispatch in retail: the target loads the
 * vtable through the already-materialised `this` in r3 and keeps the slot in
 * r12, which manual vtable indexing does not reproduce. Two implicit
 * destructor slots plus the two placeholders below put Release at slot 4. */
class TObjectDispatch
{
public:
	virtual void vslot2();
	virtual void vslot3();
	virtual void Release(s32, s32);
};

extern "C" {

M2C_UNK __dl__FPv(void*);
M2C_UNK fn_800A31B8(void*, s32);
s32 fn_800A3ED4(void*);
s32 DecreaseTimer__7nSystemFRi(void*);
M2C_UNK fn_8_A353C(void*);
s32 fn_8_A35BC(M2C_UNK);
void fn_8_A6D2C(void*, s32);
M2C_UNK** fn_8_AA528(M2C_UNK**, s16);
s32 fn_8_AA100(void*);
void fn_8_AA3B8(void*, s32, s32);
M2C_UNK** fn_8_AA5C0(M2C_UNK**, s16);

/* The strategy's vtable and its TEnemyStrategy base's (slot 3 is the shared
 * mode-change hook in rel/e_flyer_stage11.cpp). */
void* lbl_8_data_16520[6] = {
	NULL,
	NULL,
	(void*)fn_8_AA528,
	(void*)fn_8_A6D2C,
	(void*)fn_8_AA3B8,
	(void*)fn_8_AA100,
};
void* lbl_8_data_16538[6] = {
	NULL,
	NULL,
	(void*)fn_8_AA5C0,
	(void*)fn_8_A6D2C,
	NULL,
	NULL,
};

void fn_8_A9F48(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x1D;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_A9F68(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x24;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_A9F88(void* arg0, s32 arg1)
{
	s32 temp_r31;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = fn_8_A35BC(M2C_FIELD(arg0, s32*, 0x14));
			M2C_FIELD(arg0, s32*, 0x10) = 0x20;
			return;
		case 1:
			DecreaseTimer__7nSystemFRi((u8*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				temp_r31                 = M2C_FIELD(arg0, s32*, 8);
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = temp_r31;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_AA04C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_AA06C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 1;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_AA08C(void* arg0, u32 arg1)
{
	M2C_FIELD(arg0, u32*, 0x14) = arg1;
	if ((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) {
		M2C_FIELD(arg0, s32*, 0xC)  = 0;
		M2C_FIELD(arg0, s32*, 0x10) = 0;
		M2C_FIELD(arg0, s32*, 4)    = 0;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
			fn_800A31B8((void*)M2C_FIELD(arg0, u32*, 0x14), M2C_FIELD(arg0, s32*, 0x10));
		}
	}
}

s32 fn_8_AA100(void* arg0)
{
	s32 var_r3;
	void* temp_r3;
	s32 temp_r0;
	s32 temp_r0_2;

	fn_8_A353C(M2C_FIELD(arg0, void**, 0x14));
	if ((fn_800A3ED4(M2C_FIELD(arg0, void**, 0x14)) != 0)
	    && ((s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x19C) != 0x1D)) {
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 2;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	}
	temp_r3 = M2C_FIELD(arg0, void**, 0x14);
	temp_r0 = M2C_FIELD(temp_r3, s32*, 0x25C);
	if (temp_r0 != 0) {
		var_r3 = 0;
		switch (temp_r0) { /* irregular */
			case 1:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 2:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 32:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 29:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 2;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
		}
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x25C) = 0;
		return var_r3;
	}
	if ((u32)(M2C_FIELD(temp_r3, s32*, 0x18C) & 0x2000) != 0) {
		temp_r0_2 = M2C_FIELD(temp_r3, s32*, 0x19C);
		switch (temp_r0_2) {
			case 2:
			case 0x20:
				break;
			default:
				goto block_23;
		}
	block_22:
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 4;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	block_23:
		return 0;
	}
	return 0;
}

/* TEnemyStrategy<T>::ExecStrategyMode for this strategy: each mode's handler
 * runs the given phase (0 entry, 1 update, ...). */
void fn_8_AA3B8(void* arg0, s32 arg1, s32 arg2)
{
	switch (arg1) {
		case 0:
			fn_8_AA06C(arg0, arg2);
			break;
		case 1:
			fn_8_AA04C(arg0, arg2);
			break;
		case 3:
			fn_8_A9F88(arg0, arg2);
			break;
		case 2:
			fn_8_A9F48(arg0, arg2);
			break;
		case 4:
			fn_8_A9F68(arg0, arg2);
			break;
	}
}

M2C_UNK** fn_8_AA528(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_16520;
		if (arg0 != NULL) {
			*arg0 = (M2C_UNK*)lbl_8_data_16538;
		}
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_AA58C(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_16538;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_16520;
}

M2C_UNK** fn_8_AA5C0(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_16538;
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}
}
