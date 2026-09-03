#include "types.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

/* Dispatch view of the object's vtable. The handler at vtable offset 0x10 is
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

M2C_UNK __dl__FPv(void*); /* extern */
M2C_UNK fn_800A31B8(...); /* extern */
s32 fn_800A3ED4(void*);   /* extern */
s32 fn_800A6334(void);    /* extern */
s32 fn_80137FE8(void*);   /* extern */
s32 fn_8_AABC8(...);      /* extern */
s32 fn_8_AAE98(...);      /* extern */
s32 fn_8_AAF4C(...);      /* extern */
s32 fn_8_AB014(...);      /* extern */
M2C_UNK fn_8_AF3E8(...);  /* extern */
extern M2C_UNK lbl_8_data_16B98;
static M2C_UNK lbl_8_data_16B08; /* unable to generate initializer: unknown type */

void fn_8_AF9AC(s32 arg0)
{
	fn_8_AF3E8(arg0 - 0xB0);
}

void fn_8_AF9B4(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x3C;
			M2C_FIELD(arg0, s32*, 0x10) = 0x3C;
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_AFA68(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x3B;
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xE;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_AFB20(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x3A;
			return;
		case 1:
			if ((s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x2D8) == 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_AFBC8(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x39;
			M2C_FIELD(arg0, s32*, 0x18) = 0x12C;
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xC;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_AFC80(void* arg0, s32 arg1)
{
	s32 temp_r31;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x38;
			M2C_FIELD(arg0, s32*, 0x18) = 0x78;
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				temp_r31                 = M2C_FIELD(arg0, s32*, 8);
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = temp_r31;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_AFD40(void* arg0, s32 arg1)
{
	s32 temp_r31;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x37;
			M2C_FIELD(arg0, s32*, 0x18) = 0x78;
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				temp_r31                 = M2C_FIELD(arg0, s32*, 8);
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = temp_r31;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_AFE00(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x25;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_AFE20(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x24;
			return;
		case 1:
			fn_80137FE8((u8*)arg0 + 0x18);
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 8;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_AFED8(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x1A;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_AFEF8(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x20;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_AFF18(void* arg0, s32 arg1)
{
	s32 temp_r3;

	switch (arg1) { /* switch 1; irregular */
		case 0:     /* switch 1 */
			M2C_FIELD(arg0, s32*, 0x18)
			    = (s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x354);
			M2C_FIELD(arg0, s32*, 0x10) = 0x1F;
			return;
		case 1: /* switch 1 */
			if ((void*)M2C_FIELD(arg0, void**, 0x14) != NULL) {
				if (fn_800A6334() == 0) {
					M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 1;
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
					return;
				}
				if (fn_8_AAE98(M2C_FIELD(arg0, void**, 0x14)) != 0) {
					M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 2;
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
					return;
				}
				fn_80137FE8((u8*)arg0 + 0x18);
				if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
					temp_r3 = fn_8_AABC8(M2C_FIELD(arg0, void**, 0x14));
					switch (temp_r3) { /* switch 2; irregular */
						case 0:        /* switch 2 */
							M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
							M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
							    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 3);
							M2C_FIELD(arg0, s32*, 4) = 0xA;
							M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
							    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 0);
							return;
						case 1: /* switch 2 */
							M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
							M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
							    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 3);
							M2C_FIELD(arg0, s32*, 4) = 9;
							M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
							    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 0);
							return;
						case 2: /* switch 2 */
							M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
							M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
							    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 3);
							M2C_FIELD(arg0, s32*, 4) = 0xB;
							M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, s32, M2C_UNK),
							    0x10)(arg0, M2C_FIELD(arg0, s32*, 4), 0);
							break;
					}
				}
			} else {
				return;
			}
			break;
	}
}

void fn_8_B0158(void* arg0, s32 arg1)
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

void fn_8_B0178(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x36;
			return;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) && (fn_8_AAE98() == 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_B022C(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			return;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) && (fn_8_AB014() != 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
	}
}

void fn_8_B02E0(void* arg0, s32 arg1)
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

void fn_8_B0300(void* arg0, u32 arg1)
{
	M2C_FIELD(arg0, u32*, 0x14) = arg1;
	if ((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) {
		M2C_FIELD(arg0, s32*, 0xC)  = 1;
		M2C_FIELD(arg0, s32*, 0x10) = 0;
		M2C_FIELD(arg0, s32*, 4)    = 1;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
			fn_800A31B8(M2C_FIELD(arg0, u32*, 0x14));
		}
	}
}

s32 fn_8_B0378(void* arg0)
{
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r30;
	s32 temp_r30_2;
	s32 temp_r4;
	s32 var_r3;
	void* temp_r3;
	void* temp_r3_2;

	temp_r3  = M2C_FIELD(arg0, void**, 0x14);
	temp_r30 = M2C_FIELD(temp_r3, s32*, 0x19C);
	if (fn_8_AAF4C(temp_r3) != 0) {
		if (temp_r30 != 0x1F) {
			if (temp_r30 < 0x1F) {
				if (temp_r30 != 2) {
					goto block_6;
				}
				goto block_5;
			}
			goto block_6;
		}
	block_5:
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 0xC;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	}
block_6:
	if ((fn_800A3ED4(M2C_FIELD(arg0, void**, 0x14)) != 0) && (temp_r30 != 0x1D)) {
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 5;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	}
	temp_r3_2 = M2C_FIELD(arg0, void**, 0x14);
	temp_r0   = M2C_FIELD(temp_r3_2, s32*, 0x250);
	if (temp_r0 != 0) {
		var_r3 = 0;
		switch (temp_r0) { /* irregular */
			case 0x1F:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 0x3B:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xD;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
		}
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x250) = 0;
		return var_r3;
	}
	temp_r4 = M2C_FIELD(temp_r3_2, s32*, 0x18C);
	if ((u32)(temp_r4 & 0x1000) != 0) {
		if (temp_r30 != 0x36) {
			if (temp_r30 < 0x36) {
				if (temp_r30 != 0x1F) {
					if ((temp_r30 < 0x1F) && (temp_r30 < 3)) {
						if (temp_r30 < 1) {
							goto block_28;
						}
						goto block_27;
					}
					goto block_28;
				}
				goto block_27;
			}
			if (temp_r30 != 0x3A) {
			block_28:
				return 0;
			}
			goto block_27;
		}
	block_27:
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 6;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	}
	if (temp_r30 != 0x1A) {
		if ((u32)(temp_r4 & 0x2000) != 0) {
			temp_r0_2 = M2C_FIELD(temp_r3_2, s32*, 0x19C);
			if (temp_r0_2 != 0x1F) {
				if ((temp_r0_2 < 0x1F) && (temp_r0_2 < 3)) {
					if (temp_r0_2 < 1) {
						goto block_39;
					}
					goto block_38;
				}
			block_39:
				return 0;
			}
		block_38:
			M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
			((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
			M2C_FIELD(arg0, s32*, 4) = 7;
			((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			return 1;
		}
		return 0;
	}
	temp_r30_2               = M2C_FIELD(arg0, s32*, 8);
	M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
	((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
	M2C_FIELD(arg0, s32*, 4) = temp_r30_2;
	((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
	return 1;
}

void fn_8_B06EC(void* arg0, u32 arg1, M2C_UNK arg2)
{
	if (arg1 <= 14) {
		M2C_FIELD(M2C_FIELD(arg0, void**, 0), M2C_UNK(**)(void*, M2C_UNK), 0x18 + arg1 * 4)(
		    arg0, arg2);
	}
}

M2C_UNK** fn_8_B088C(M2C_UNK** arg0, s16 arg1)
{
	s32 temp_cr0_eq;

	temp_cr0_eq = arg0 == NULL;
	if (temp_cr0_eq == 0) {
		*arg0 = &lbl_8_data_16B08;
		if (temp_cr0_eq == 0) {
			*arg0 = &lbl_8_data_16B98;
		}
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_B08F0(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = &lbl_8_data_16B98;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = &lbl_8_data_16B08;
}
}
