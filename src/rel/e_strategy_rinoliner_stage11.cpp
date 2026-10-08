#include "types.h"

// The rinoliner's mode-strategy object. The retained PS2 symbols have the same
// shape as TEnemyRinoliner_Strategy (StrategyMode_* handlers, IsReqChangeMode,
// ExecStrategyMode, SetUpFirst); this GameCube revision carries fifteen modes,
// so the handlers keep their address names. Slot 4 (fn_8_B06EC) is the mode
// dispatcher, slot 5 (fn_8_B0378) the change-request check.

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
	virtual s32 IsReqChangeMode();
	/* The per-mode handlers, in vtable order. The dispatcher's case labels
	 * reach them as 0, 1, 2, 5, 3, 4, 6, ..., 14. */
	virtual void Mode00(s32);
	virtual void Mode01(s32);
	virtual void Mode02(s32);
	virtual void Mode05(s32);
	virtual void Mode03(s32);
	virtual void Mode04(s32);
	virtual void Mode06(s32);
	virtual void Mode07(s32);
	virtual void Mode08(s32);
	virtual void Mode09(s32);
	virtual void Mode10(s32);
	virtual void Mode11(s32);
	virtual void Mode12(s32);
	virtual void Mode13(s32);
	virtual void Mode14(s32);
};

/* The mode change every handler performs: remember the current mode, let it
 * leave (phase 3), switch, and let the new one enter (phase 0). */
static inline void ChangeMode(void* self, s32 next)
{
	M2C_FIELD(self, s32*, 8) = M2C_FIELD(self, s32*, 4);
	((TObjectDispatch*)self)->Release(M2C_FIELD(self, s32*, 4), 3);
	M2C_FIELD(self, s32*, 4) = next;
	((TObjectDispatch*)self)->Release(M2C_FIELD(self, s32*, 4), 0);
}

extern "C" {

M2C_UNK __dl__FPv(void*);              /* extern */
M2C_UNK fn_800A31B8(void*, s32);       /* extern */
s32 fn_800A3ED4(void*);                /* extern */
s32 fn_800A6334(void*);                /* extern */
s32 DecreaseTimer__7nSystemFRi(void*); /* extern */
s32 fn_8_AABC8(void*);                 /* extern */
s32 fn_8_AAE98(void*);                 /* extern */
s32 fn_8_AAF4C(void*);                 /* extern */
s32 fn_8_AB014(u32);                   /* extern */
void fn_8_AF86C();
extern M2C_UNK lbl_8_data_16B98;
M2C_UNK** fn_8_B088C(M2C_UNK** arg0, s16 arg1);
void fn_8_B06EC(void* arg0, u32 arg1, s32 arg2);
s32 fn_8_B0378(void* arg0);
void fn_8_B02E0(void* arg0, s32 arg1);
void fn_8_B022C(void* arg0, s32 arg1);
void fn_8_B0178(void* arg0, s32 arg1);
void fn_8_B0158(void* arg0, s32 arg1);
void fn_8_AFF18(void* arg0, s32 arg1);
void fn_8_AFEF8(void* arg0, s32 arg1);
void fn_8_AFED8(void* arg0, s32 arg1);
void fn_8_AFE20(void* arg0, s32 arg1);
void fn_8_AFE00(void* arg0, s32 arg1);
void fn_8_AFD40(void* arg0, s32 arg1);
void fn_8_AFC80(void* arg0, s32 arg1);
void fn_8_AFBC8(void* arg0, s32 arg1);
void fn_8_AFB20(void* arg0, s32 arg1);
void fn_8_AFA68(void* arg0, s32 arg1);
void fn_8_AF9B4(void* arg0, s32 arg1);

/* The strategy's vtable: destructor, a base-class slot, the mode dispatcher,
 * the change-request check, then the fifteen mode handlers. */
void* lbl_8_data_16B08[21] = {
	0,
	0,
	(void*)fn_8_B088C,
	(void*)fn_8_AF86C,
	(void*)fn_8_B06EC,
	(void*)fn_8_B0378,
	(void*)fn_8_B02E0,
	(void*)fn_8_B022C,
	(void*)fn_8_B0178,
	(void*)fn_8_B0158,
	(void*)fn_8_AFF18,
	(void*)fn_8_AFEF8,
	(void*)fn_8_AFED8,
	(void*)fn_8_AFE20,
	(void*)fn_8_AFE00,
	(void*)fn_8_AFD40,
	(void*)fn_8_AFC80,
	(void*)fn_8_AFBC8,
	(void*)fn_8_AFB20,
	(void*)fn_8_AFA68,
	(void*)fn_8_AF9B4,
};

void fn_8_AF9B4(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x3C;
			M2C_FIELD(arg0, s32*, 0x10) = 0x3C;
			return;
		case 1:
			DecreaseTimer__7nSystemFRi((void*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
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
			DecreaseTimer__7nSystemFRi((void*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xE;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_AFB20(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x3A;
			break;
		case 1:
			if ((s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x2D8) == 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
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
			DecreaseTimer__7nSystemFRi((void*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xC;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
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
			DecreaseTimer__7nSystemFRi((void*)((u32)arg0 + 0x18));
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

void fn_8_AFD40(void* arg0, s32 arg1)
{
	s32 temp_r31;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x37;
			M2C_FIELD(arg0, s32*, 0x18) = 0x78;
			return;
		case 1:
			DecreaseTimer__7nSystemFRi((void*)((u32)arg0 + 0x18));
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
			DecreaseTimer__7nSystemFRi((void*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 8;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
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
				if (fn_800A6334(M2C_FIELD(arg0, void**, 0x14)) == 0) {
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
				DecreaseTimer__7nSystemFRi((void*)((u32)arg0 + 0x18));
				if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
					temp_r3 = fn_8_AABC8(M2C_FIELD(arg0, void**, 0x14));
					switch (temp_r3) { /* switch 2; irregular */
						case 0:        /* switch 2 */
							M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
							((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
							M2C_FIELD(arg0, s32*, 4) = 0xA;
							((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
							return;
						case 1: /* switch 2 */
							M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
							((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
							M2C_FIELD(arg0, s32*, 4) = 9;
							((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
							return;
						case 2: /* switch 2 */
							M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
							((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
							M2C_FIELD(arg0, s32*, 4) = 0xB;
							((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
							break;
					}
				}
			} else {
				return;
			}
			break;
		case 2:
		case 3:
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
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_8_AAE98(M2C_FIELD(arg0, void**, 0x14)) == 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B022C(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			return;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_8_AB014(M2C_FIELD(arg0, u32*, 0x14)) != 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
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
			fn_800A31B8((void*)M2C_FIELD(arg0, u32*, 0x14), M2C_FIELD(arg0, s32*, 0x10));
		}
	}
}

s32 fn_8_B0378(void* arg0)
{
	s32 mode;
	void* enemy;
	u32 flags;
	s32 command;
	s32 result;

	enemy = M2C_FIELD(arg0, void**, 0x14);
	mode  = M2C_FIELD(enemy, s32*, 0x19C);
	if (fn_8_AAF4C(enemy) != 0) {
		switch (mode) {
			case 2:
			case 0x1F:
				ChangeMode(arg0, 0xC);
				return 1;
		}
	}
	if (fn_800A3ED4(M2C_FIELD(arg0, void**, 0x14)) != 0 && mode != 0x1D) {
		ChangeMode(arg0, 5);
		return 1;
	}
	enemy   = M2C_FIELD(arg0, void**, 0x14);
	command = M2C_FIELD(enemy, s32*, 0x250);
	if (command != 0) {
		result = 0;
		switch (command) {
			case 0x1F:
				ChangeMode(arg0, 3);
				result = 1;
				break;
			case 0x3B:
				ChangeMode(arg0, 0xD);
				result = 1;
				break;
		}
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x250) = 0;
		return result;
	}
	flags = M2C_FIELD(enemy, s32*, 0x18C);
	if (flags & 0x1000) {
		switch (mode) {
			case 1:
			case 2:
			case 0x1F:
			case 0x36:
			case 0x3A:
				ChangeMode(arg0, 6);
				return 1;
		}
		return 0;
	}
	switch (mode) {
		case 0x1A:
			ChangeMode(arg0, M2C_FIELD(arg0, s32*, 8));
			return 1;
	}
	if (flags & 0x2000) {
		switch (M2C_FIELD(enemy, s32*, 0x19C)) {
			case 1:
			case 2:
			case 0x1F:
				ChangeMode(arg0, 7);
				return 1;
		}
		return 0;
	}
	return 0;
}

void fn_8_B06EC(void* arg0, u32 arg1, s32 arg2)
{
	TObjectDispatch* self = (TObjectDispatch*)arg0;

	switch (arg1) {
		case 0:
			self->Mode00(arg2);
			break;
		case 1:
			self->Mode01(arg2);
			break;
		case 2:
			self->Mode02(arg2);
			break;
		case 5:
			self->Mode05(arg2);
			break;
		case 3:
			self->Mode03(arg2);
			break;
		case 4:
			self->Mode04(arg2);
			break;
		case 6:
			self->Mode06(arg2);
			break;
		case 7:
			self->Mode07(arg2);
			break;
		case 8:
			self->Mode08(arg2);
			break;
		case 9:
			self->Mode09(arg2);
			break;
		case 10:
			self->Mode10(arg2);
			break;
		case 11:
			self->Mode11(arg2);
			break;
		case 12:
			self->Mode12(arg2);
			break;
		case 13:
			self->Mode13(arg2);
			break;
		case 14:
			self->Mode14(arg2);
			break;
	}
}

static inline void DestroyStrategyBase(M2C_UNK** self)
{
	if (self != NULL) {
		*self = &lbl_8_data_16B98;
	}
}

M2C_UNK** fn_8_B088C(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_16B08;
		DestroyStrategyBase(arg0);
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
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_16B08;
}
}
