#include "types.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

/* The renderer class keeps its vtable pointer at object offset 0x18, which is
 * what a polymorphic class derived from a 0x18-byte non-polymorphic base
 * looks like: the base's data is laid out first and `this` is not adjusted,
 * exactly as retail's `lwz r12, 0x18(r3)` reads it. Slot numbers are the
 * retail vtable offsets divided by four, and the two implicit deleting
 * destructor slots occupy 0 and 1, so a method at slot k needs k - 2
 * placeholders ahead of it. */
class TRendererBase
{
public:
	u8 pad0[0x18];
};

class TRenderer : public TRendererBase
{
public:
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void vslot6();
	virtual void vslot7();
	virtual void vslot8();
	virtual void vslot9();
	virtual void vslot10();
	virtual void vslot11();
	virtual void vslot12();
	virtual void vslot13();
	virtual void Slot38();
	virtual void Slot3C();
	virtual void Slot40();
	virtual void vslot17();
	virtual void vslot18();
	virtual void vslot19();
	virtual void Slot50(s32, s32);
	virtual void vslot21();
	virtual void vslot22();
	virtual void vslot23();
	virtual void vslot24();
	virtual void vslot25();
	virtual void vslot26();
	virtual void vslot27();
	virtual void vslot28();
	virtual void vslot29();
	virtual void vslot30();
	virtual void Slot7C();
	virtual void vslot32();
	virtual void vslot33();
	virtual void Slot88(void*);
	virtual void vslot35();
	virtual s32 Slot90();
};

extern "C" {

M2C_UNK __dl__FPv(void*); /* extern */
s32 fn_80017800(...);     /* extern */
void* fn_80020BD8(...);   /* extern */
M2C_UNK fn_80021824(...); /* extern */
M2C_UNK fn_8003BC38(...); /* extern */
M2C_UNK fn_8003BE78(...); /* extern */
s32 fn_8005B8BC(...);     /* extern */
M2C_UNK fn_8006298C(...); /* extern */
M2C_UNK fn_800A3D48(...); /* extern */
s32 fn_800A3F60(...);     /* extern */
M2C_UNK fn_800A5B34(...); /* extern */
s32 fn_800A6D60(...);     /* extern */
f32 fn_800AEF48(...);     /* extern */
s32 fn_800AF3AC(...);     /* extern */
M2C_UNK fn_800AFB50(...); /* extern */
M2C_UNK fn_800B4A38(...); /* extern */
f32 fn_800D71DC(...);     /* extern */
M2C_UNK fn_800D735C(...); /* extern */
s32 fn_800D7A94(...);     /* extern */
f32 fn_800D7B00(...);     /* extern */
f32 fn_800D7BD8(...);     /* extern */
s32 fn_80103324(...);     /* extern */
M2C_UNK fn_80113874(...); /* extern */
M2C_UNK fn_8011C1F8(...); /* extern */
M2C_UNK fn_8011C6EC(...); /* extern */
M2C_UNK fn_8014FF2C(...); /* extern */
M2C_UNK fn_801990E0(...); /* extern */
M2C_UNK fn_8_90B10(...);  /* extern */
M2C_UNK fn_8_B5160(...);  /* extern */
M2C_UNK fn_8_B2BB4(...);  /* static */
M2C_UNK fn_8_B3598(...);  /* static */
extern M2C_UNK lbl_802AD090;
extern void* lbl_8042C180;
extern M2C_UNK lbl_8042C1A4;
extern void* lbl_8042C208;
extern void* lbl_8042C380;
extern u32 lbl_8042C388;
extern u32 lbl_8042C6D0;
extern M2C_UNK lbl_8_data_16B98;
extern M2C_UNK lbl_8_rodata_1BB8;
extern M2C_UNK lbl_8_rodata_1BC4;
extern f32 lbl_8_rodata_1BD0;
extern f32 lbl_8_rodata_1BD4;
extern f32 lbl_8_rodata_1BD8;
extern f32 lbl_8_rodata_1BDC;
extern f32 lbl_8_rodata_1BE0;
extern f32 lbl_8_rodata_1BE4;
extern f32 lbl_8_rodata_1BE8;
extern f32 lbl_8_rodata_1BEC;
extern f32 lbl_8_rodata_1BF0;
extern f32 lbl_8_rodata_1BF4;
extern f32 lbl_8_rodata_1BF8;
extern f32 lbl_8_rodata_1BFC;
extern f32 lbl_8_rodata_1C00;
extern f32 lbl_8_rodata_1C04;

M2C_UNK** fn_8_B0924(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = &lbl_8_data_16B98;
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

s32 fn_8_B0974(void* arg0)
{
	u32 var_r0;
	void* temp_r3;

	fn_80021824(&lbl_8042C1A4);
	temp_r3 = fn_80020BD8((u8*)arg0 + 0x28, 0x16);
	if (temp_r3 != NULL) {
		var_r0 = M2C_FIELD(temp_r3, u32*, 4);
	} else {
		var_r0 = 0U;
	}
	if (var_r0 != 0U) {
		M2C_FIELD(arg0, f32*, 0x1A4) = (f32)lbl_8_rodata_1BD0;
		M2C_FIELD(arg0, s32*, 0x230) = -1;
		return 1;
	}
	return fn_800A3F60(arg0);
}

void fn_8_B09F8(s32 arg1)
{
	fn_8_90B10(arg1);
}

void fn_8_B0A1C(void* arg0)
{
	if ((u32)lbl_8042C6D0 == 0U) {
		fn_8011C6EC();
	}
	fn_8011C1F8(lbl_8042C6D0, M2C_FIELD(arg0, s32*, 0x230), 0xC8);
}

s32 fn_8_B0A74(void* arg0)
{
	f32 temp_f1;
	s32 temp_r0;
	u32 temp_r3;

	temp_r0 = M2C_FIELD(arg0, s32*, 0x2CC);
	if (temp_r0 != -1) {
		temp_r3 = *(&lbl_802AD090 + (temp_r0 * 4));
		if (temp_r3 != 0U) {
			temp_f1 = fn_800D71DC((u8*)temp_r3 + 0x18, (u8*)arg0 + 0x140);
			M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
			if (lbl_8_rodata_1BD4 == temp_f1) {
				M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
				if (temp_f1 == lbl_8_rodata_1BD8) {
					return 1;
				}
			}
		}
	}
	return 0;
}

void fn_8_B0B00(void* arg0)
{
	f32 temp_f1;

	temp_f1 = M2C_FIELD(arg0, f32*, 0x2FC);
	if (temp_f1 < lbl_8_rodata_1BDC) {
		M2C_FIELD(arg0, s32*, 0x2B8) = 0x70;
		M2C_FIELD(arg0, s32*, 0x2BC) = 0x70;
		return;
	}
	M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
	if ((temp_f1 == lbl_8_rodata_1BDC) && (temp_f1 < lbl_8_rodata_1BE0)) {
		M2C_FIELD(arg0, s32*, 0x2B8) = 0x100;
		M2C_FIELD(arg0, s32*, 0x2BC) = 0x100;
		return;
	}
	M2C_FIELD(arg0, s32*, 0x2B8) = 0x400;
	M2C_FIELD(arg0, s32*, 0x2BC) = 0x400;
}

s32 fn_8_B0B64(s32 arg0)
{
	return fn_8005B8BC((u8*)arg0 + 0xB0) != 0;
}

s32 fn_8_B0B94(void* arg0)
{
	f32 sp60;
	f32 sp5C;
	f32 sp58;
	f32 sp30;
	M2C_UNK sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f1;
	s32 temp_r3;
	void* temp_r31;

	if ((s16*)M2C_FIELD(arg0, s16**, 0x24C) == NULL) {
		return 2;
	}
	temp_r3 = fn_80103324((u8*)arg0 + 0x140, &lbl_8_rodata_1BE4, lbl_8_rodata_1BE4);
	if (temp_r3 != -1) {
		temp_r31 = (void*)*(&lbl_802AD090 + (temp_r3 * 4));
		if ((temp_r31 != NULL)
		    && (fn_800D71DC((u8*)temp_r31 + 0x18, (u8*)arg0 + 0x140) > lbl_8_rodata_1BE8)) {
			sp14    = M2C_FIELD(temp_r31, f32*, 0x18) - M2C_FIELD(arg0, f32*, 0x140);
			sp18    = M2C_FIELD(temp_r31, f32*, 0x1C) - M2C_FIELD(arg0, f32*, 0x144);
			temp_f1 = M2C_FIELD(temp_r31, f32*, 0x20);
			sp1C    = temp_f1 - M2C_FIELD(arg0, f32*, 0x148);
			fn_801990E0(&sp14, &sp14, temp_f1);
			sp30 = M2C_FIELD(arg0, f32*, 0x248);
			if (fn_800AF3AC(M2C_FIELD(arg0, s16**, 0x24C), &sp20) == 0) {
				return 2;
			}
			sp8  = sp58;
			spC  = sp5C;
			sp10 = sp60;
			if ((s32)M2C_FIELD(arg0, s32*, 0x2B4) == 0) {
				sp8 *= lbl_8_rodata_1BEC;
				spC *= lbl_8_rodata_1BEC;
				sp10 *= lbl_8_rodata_1BEC;
			}
			if (((sp1C * sp10) + ((sp14 * sp8) + (sp18 * spC))) < lbl_8_rodata_1BD0) {
				return 0;
			}
			return 1;
		}
	}
	return 2;
}

void fn_8_B0D34(void* arg0)
{
	f32 sp60;
	f32 sp5C;
	f32 sp58;
	f32 sp30;
	M2C_UNK sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f0;
	f32 temp_f0_2;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f1_4;
	f32 temp_f1_5;
	f32 temp_f1_6;
	f32 temp_f1_7;
	s32 temp_r0;
	s32 temp_r3;
	s32 var_r0;
	void* temp_r30;

	temp_r0 = M2C_FIELD(arg0, s32*, 0x31C);
	switch (temp_r0) { /* switch 1; irregular */
		case 0:        /* switch 1 */
			if ((s16*)M2C_FIELD(arg0, s16**, 0x24C) == NULL) {
				var_r0 = 2;
			} else {
				temp_r3 = fn_80103324((u8*)arg0 + 0x140, &lbl_8_rodata_1BE4, lbl_8_rodata_1BE4);
				if ((temp_r3 != -1)
				    && (temp_r30 = (void*)*(&lbl_802AD090 + (temp_r3 * 4)),
				        ((temp_r30 == NULL) == 0))
				    && (fn_800D71DC((u8*)temp_r30 + 0x18, (u8*)arg0 + 0x140) > lbl_8_rodata_1BE8)) {
					sp8     = M2C_FIELD(temp_r30, f32*, 0x18) - M2C_FIELD(arg0, f32*, 0x140);
					spC     = M2C_FIELD(temp_r30, f32*, 0x1C) - M2C_FIELD(arg0, f32*, 0x144);
					temp_f1 = M2C_FIELD(temp_r30, f32*, 0x20);
					sp10    = temp_f1 - M2C_FIELD(arg0, f32*, 0x148);
					fn_801990E0(&sp8, &sp8, temp_f1);
					sp30 = M2C_FIELD(arg0, f32*, 0x248);
					if (fn_800AF3AC(M2C_FIELD(arg0, s16**, 0x24C), &sp20) == 0) {
						var_r0 = 2;
					} else {
						sp14 = sp58;
						sp18 = sp5C;
						sp1C = sp60;
						if ((s32)M2C_FIELD(arg0, s32*, 0x2B4) == 0) {
							sp14 *= lbl_8_rodata_1BEC;
							sp18 *= lbl_8_rodata_1BEC;
							sp1C *= lbl_8_rodata_1BEC;
						}
						if (((sp10 * sp1C) + ((sp8 * sp14) + (spC * sp18))) < lbl_8_rodata_1BD0) {
							var_r0 = 0;
						} else {
							var_r0 = 1;
						}
					}
				} else {
					var_r0 = 2;
				}
			}
			switch (var_r0) { /* switch 2; irregular */
				case 0:       /* switch 2 */
					M2C_FIELD(arg0, f32*, 0x2FC)
					    = (f32)(M2C_FIELD(arg0, f32*, 0x2FC) * lbl_8_rodata_1BF0);
					temp_f1_2 = M2C_FIELD(arg0, f32*, 0x2F4);
					if (M2C_FIELD(arg0, f32*, 0x2FC) < temp_f1_2) {
						M2C_FIELD(arg0, f32*, 0x2FC) = temp_f1_2;
						return;
					}
				case 1: /* switch 2 */
					M2C_FIELD(arg0, f32*, 0x2FC)
					    = (f32)(M2C_FIELD(arg0, f32*, 0x2FC) * lbl_8_rodata_1BF4);
					temp_f1_3 = M2C_FIELD(arg0, f32*, 0x2F8);
					if (M2C_FIELD(arg0, f32*, 0x2FC) > temp_f1_3) {
						M2C_FIELD(arg0, f32*, 0x2FC) = temp_f1_3;
						return;
					}
					break;
				case 2: /* switch 2 */
					temp_f1_4 = M2C_FIELD(arg0, f32*, 0x2FC);
					temp_f0   = M2C_FIELD(arg0, f32*, 0x2F0);
					if (temp_f1_4 > temp_f0) {
						M2C_FIELD(arg0, f32*, 0x2FC) = (f32)(temp_f1_4 * lbl_8_rodata_1BF0);
						return;
					}
					if (temp_f1_4 < temp_f0) {
						M2C_FIELD(arg0, f32*, 0x2FC) = (f32)(temp_f1_4 * lbl_8_rodata_1BF4);
						return;
					}
					M2C_FIELD(arg0, f32*, 0x2FC) = temp_f0;
					return;
			}
			break;
		case 2: /* switch 1 */
			M2C_FIELD(arg0, f32*, 0x2FC) = (f32)(M2C_FIELD(arg0, f32*, 0x2FC) * lbl_8_rodata_1BF0);
			temp_f1_5                    = M2C_FIELD(arg0, f32*, 0x2F4);
			if (M2C_FIELD(arg0, f32*, 0x2FC) < temp_f1_5) {
				M2C_FIELD(arg0, f32*, 0x2FC) = temp_f1_5;
				return;
			}
			break;
		case 3: /* switch 1 */
			temp_f1_6 = M2C_FIELD(arg0, f32*, 0x2FC);
			temp_f0_2 = M2C_FIELD(arg0, f32*, 0x2F0);
			if (temp_f1_6 > temp_f0_2) {
				M2C_FIELD(arg0, f32*, 0x2FC) = (f32)(temp_f1_6 * lbl_8_rodata_1BF0);
				return;
			}
			if (temp_f1_6 < temp_f0_2) {
				M2C_FIELD(arg0, f32*, 0x2FC) = (f32)(temp_f1_6 * lbl_8_rodata_1BF4);
				return;
			}
			M2C_FIELD(arg0, f32*, 0x2FC) = temp_f0_2;
			return;
		case 4: /* switch 1 */
			M2C_FIELD(arg0, f32*, 0x2FC) = (f32)(M2C_FIELD(arg0, f32*, 0x2FC) * lbl_8_rodata_1BF4);
			temp_f1_7                    = M2C_FIELD(arg0, f32*, 0x2F8);
			if (M2C_FIELD(arg0, f32*, 0x2FC) > temp_f1_7) {
				M2C_FIELD(arg0, f32*, 0x2FC) = temp_f1_7;
			}
			break;
	}
}
}

void fn_8_B1078(void* arg0)
{
	f32 saved_reg_f31;
	f32 sp4C;
	f32 sp48;
	f32 sp44;
	f32 sp70;
	f32 sp6C;
	f32 sp68;
	f32 sp40;
	M2C_UNK sp30;
	M2C_UNK sp24;
	f32 sp20;
	f32 sp1C;
	f32 sp18;
	s32 sp14;
	s32 sp10;
	s32 spC;
	f32 sp8;
	f32* temp_r3_2;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 var_f30;
	f32 var_f31;
	s16** var_r29;
	s16* temp_r3;
	s16* var_r28;

	var_f31 = saved_reg_f31;
	var_r28 = NULL;
	var_f30 = lbl_8_rodata_1BF8;
	var_r29 = M2C_FIELD(lbl_8042C380, s16***, 0x28);
loop_5:
	temp_r3 = *var_r29;
	if (temp_r3 != NULL) {
		if ((s16)*temp_r3 == 1) {
			temp_f1 = fn_800AEF48((u8*)arg0 + 0x254, &sp24, &sp8, lbl_8_rodata_1BD0);
			if (temp_f1 < var_f30) {
				var_f30 = temp_f1;
				var_r28 = *var_r29;
				var_f31 = sp8;
			}
		}
		var_r29 += 4;
		goto loop_5;
	}
	if (var_r28 != NULL) {
		M2C_FIELD(arg0, s16**, 0x24C) = var_r28;
		sp40                          = var_f31;
		if (fn_800AF3AC(M2C_FIELD(arg0, s16**, 0x24C), &sp30) == 1) {
			sp18 = sp44 - M2C_FIELD(arg0, f32*, 0x140);
			sp1C = sp48 - M2C_FIELD(arg0, f32*, 0x144);
			sp20 = sp4C - M2C_FIELD(arg0, f32*, 0x148);
			fn_801990E0(&sp18, &sp18, sp4C);
			if (((sp20 * sp70) + ((sp18 * sp68) + (sp1C * sp6C))) < lbl_8_rodata_1BD0) {
				M2C_FIELD(arg0, s32*, 0x2B4) = 0;
				M2C_FIELD(arg0, f32*, 0x248) = var_f31;
			} else {
				M2C_FIELD(arg0, s32*, 0x2B4) = 1;
				M2C_FIELD(arg0, f32*, 0x248) = var_f31;
			}
			spC = 0;
			fn_800D735C(&sp68, 0, &spC);
			if ((s32)M2C_FIELD(arg0, s32*, 0x2B4) != 0) {
				M2C_FIELD(arg0, f32*, 0x254) = sp44;
				M2C_FIELD(arg0, f32*, 0x258) = sp48;
				M2C_FIELD(arg0, f32*, 0x25C) = sp4C;
				M2C_FIELD(arg0, s32*, 0x26C) = spC;
				M2C_FIELD(arg0, s32*, 0x270) = sp10;
				M2C_FIELD(arg0, s32*, 0x274) = sp14;
			} else {
				M2C_FIELD(arg0, f32*, 0x254) = sp44;
				M2C_FIELD(arg0, f32*, 0x258) = sp48;
				M2C_FIELD(arg0, f32*, 0x25C) = sp4C;
				M2C_FIELD(arg0, s32*, 0x26C) = spC;
				M2C_FIELD(arg0, s32*, 0x270) = (s32)(u16)(sp10 + 0x8000);
				M2C_FIELD(arg0, s32*, 0x274) = (s32)(u16)(sp14 * -1);
			}
			M2C_FIELD(arg0, s32*, 0x27C) = 0;
			M2C_FIELD(arg0, f32*, 0x260)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x254) - M2C_FIELD(arg0, f32*, 0x140));
			M2C_FIELD(arg0, f32*, 0x264)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x258) - M2C_FIELD(arg0, f32*, 0x144));
			temp_f1_2                    = M2C_FIELD(arg0, f32*, 0x25C);
			M2C_FIELD(arg0, f32*, 0x268) = (f32)(temp_f1_2 - M2C_FIELD(arg0, f32*, 0x148));
			temp_r3_2                    = (f32*)((u8*)arg0 + 0x260);
			fn_801990E0(temp_r3_2, temp_r3_2, temp_f1_2);
			M2C_FIELD(arg0, f32*, 0x260)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x260) * M2C_FIELD(arg0, f32*, 0x2FC));
			M2C_FIELD(arg0, f32*, 0x264)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x264) * M2C_FIELD(arg0, f32*, 0x2FC));
			M2C_FIELD(arg0, f32*, 0x268)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x268) * M2C_FIELD(arg0, f32*, 0x2FC));
			M2C_FIELD(arg0, s32*, 0xD4) = 1;
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(0x4038, (u8*)arg0 + 0x140, 0, 1, 0, 0);
			}
		}
	}
}

void fn_8_B134C(void* arg0)
{
	f32 sp58;
	f32 sp3C;
	f32 sp38;
	f32 sp34;
	f32 sp30;
	s16 sp20;
	s32 sp1C;
	s32 sp18;
	s32 sp14;
	M2C_UNK sp8;
	f32* temp_r3_2;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 var_f31;
	s16** var_r27;
	s16* temp_r3;
	s16* var_r28;

	var_r28 = NULL;
	var_f31 = lbl_8_rodata_1BF8;
	var_r27 = M2C_FIELD(lbl_8042C380, s16***, 0x28);
loop_5:
	temp_r3 = *var_r27;
	if (temp_r3 != NULL) {
		if ((s16)*temp_r3 == 1) {
			fn_800AFB50(NULL, &sp8);
			temp_f1 = fn_800D71DC((u8*)arg0 + 0x140, &sp8);
			if (temp_f1 < var_f31) {
				var_f31                      = temp_f1;
				var_r28                      = *var_r27;
				M2C_FIELD(arg0, s32*, 0x2B4) = 1;
			}
		}
		var_r27 += 4;
		goto loop_5;
	}
	M2C_FIELD(arg0, s16**, 0x24C) = var_r28;
	if ((s16*)M2C_FIELD(arg0, s16**, 0x24C) != NULL) {
		sp30 = lbl_8_rodata_1BD0;
		if (fn_800AF3AC(&sp20) == 1) {
			sp14 = M2C_FIELD(&lbl_8_rodata_1BC4, s32*, 0);
			sp18 = M2C_FIELD(&lbl_8_rodata_1BC4, s32*, 4);
			sp1C = M2C_FIELD(&lbl_8_rodata_1BC4, s32*, 8);
			fn_800D735C(&sp58, 0, &sp14);
			M2C_FIELD(arg0, f32*, 0x254) = sp34;
			M2C_FIELD(arg0, f32*, 0x258) = sp38;
			M2C_FIELD(arg0, f32*, 0x25C) = sp3C;
			M2C_FIELD(arg0, s32*, 0x26C) = sp14;
			M2C_FIELD(arg0, s32*, 0x270) = sp18;
			M2C_FIELD(arg0, s32*, 0x274) = sp1C;
		}
		M2C_FIELD(arg0, f32*, 0x248) = (f32)lbl_8_rodata_1BD0;
		M2C_FIELD(arg0, s32*, 0x27C) = 0;
		M2C_FIELD(arg0, f32*, 0x260)
		    = (f32)(M2C_FIELD(arg0, f32*, 0x254) - M2C_FIELD(arg0, f32*, 0x140));
		M2C_FIELD(arg0, f32*, 0x264)
		    = (f32)(M2C_FIELD(arg0, f32*, 0x258) - M2C_FIELD(arg0, f32*, 0x144));
		temp_f1_2                    = M2C_FIELD(arg0, f32*, 0x25C);
		M2C_FIELD(arg0, f32*, 0x268) = (f32)(temp_f1_2 - M2C_FIELD(arg0, f32*, 0x148));
		temp_r3_2                    = (f32*)((u8*)arg0 + 0x260);
		fn_801990E0(temp_r3_2, temp_r3_2, temp_f1_2);
		M2C_FIELD(arg0, f32*, 0x260)
		    = (f32)(M2C_FIELD(arg0, f32*, 0x260) * M2C_FIELD(arg0, f32*, 0x2FC));
		M2C_FIELD(arg0, f32*, 0x264)
		    = (f32)(M2C_FIELD(arg0, f32*, 0x264) * M2C_FIELD(arg0, f32*, 0x2FC));
		M2C_FIELD(arg0, f32*, 0x268)
		    = (f32)(M2C_FIELD(arg0, f32*, 0x268) * M2C_FIELD(arg0, f32*, 0x2FC));
		M2C_FIELD(arg0, s32*, 0xD4) = 1;
		if ((u32)lbl_8042C388 != 0U) {
			fn_800B4A38(0x4038, (u8*)arg0 + 0x140, 0, 1, 0, 0);
		}
	}
}

s32 fn_8_B154C(void* arg0)
{
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f1;

	M2C_FIELD(arg0, s32*, 0x27C) = (s32)(M2C_FIELD(arg0, s32*, 0x27C) + 0x250);
	M2C_FIELD(arg0, f32*, 0x278)
	    = (f32)(lbl_8_rodata_1BFC * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x27C)));
	M2C_FIELD(arg0, s32*, 0x14C) = (s32)M2C_FIELD(arg0, s32*, 0x26C);
	M2C_FIELD(arg0, s32*, 0x150)
	    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150), M2C_FIELD(arg0, s32*, 0x270), 0x80);
	M2C_FIELD(arg0, s32*, 0x154)
	    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x154), M2C_FIELD(arg0, s32*, 0x274), 0x80);
	sp8  = M2C_FIELD(arg0, f32*, 0x140);
	spC  = M2C_FIELD(arg0, f32*, 0x144);
	sp10 = M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, f32*, 0x140)
	    = (f32)(M2C_FIELD(arg0, f32*, 0x260) + M2C_FIELD(arg0, f32*, 0x140));
	M2C_FIELD(arg0, f32*, 0x144)
	    = (f32)(M2C_FIELD(arg0, f32*, 0x264) + M2C_FIELD(arg0, f32*, 0x144));
	temp_f1                      = M2C_FIELD(arg0, f32*, 0x268);
	M2C_FIELD(arg0, f32*, 0x148) = (f32)(temp_f1 + M2C_FIELD(arg0, f32*, 0x148));
	if (fn_800D7BD8((u8*)arg0 + 0x254, &sp8, (u8*)arg0 + 0x140, 0, temp_f1) < lbl_8_rodata_1BDC) {
		M2C_FIELD(arg0, f32*, 0x140) = (f32)M2C_FIELD(arg0, f32*, 0x254);
		M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(arg0, f32*, 0x258);
		M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(arg0, f32*, 0x25C);
		return 1;
	}
	return 0;
}

void fn_8_B1660(void*, u32) { }

void* fn_8_B1828(void* arg0, void* arg1, u32 arg2, f32 farg0)
{
	M2C_UNK sp8;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 var_f31;
	void** var_r27;
	void* temp_r3;
	void* temp_r3_2;
	void* var_r31;

	var_r31 = NULL;
	var_f31 = lbl_8_rodata_1BF8;
	if (lbl_8_rodata_1BEC != farg0) {
		var_f31 = farg0 * farg0;
	}
	var_r27 = M2C_FIELD(lbl_8042C380, void***, 0x28);
loop_10:
	temp_r3 = *var_r27;
	if (temp_r3 != NULL) {
		if ((temp_r3 != (void*)arg2) && ((s16)M2C_FIELD(temp_r3, s16*, 0) == 1)) {
			fn_800AFB50(NULL, &sp8);
			temp_f1 = fn_800D71DC(arg1, &sp8);
			if (temp_f1 < var_f31) {
				var_f31                      = temp_f1;
				var_r31                      = *var_r27;
				M2C_FIELD(arg0, s32*, 0x2B4) = 1;
			}
			temp_r3_2 = *var_r27;
			fn_800AFB50(temp_r3_2, M2C_FIELD(temp_r3_2, s16*, 2) - 1, &sp8);
			temp_f1_2 = fn_800D71DC(arg1, &sp8);
			if (temp_f1_2 < var_f31) {
				var_f31                      = temp_f1_2;
				var_r31                      = *var_r27;
				M2C_FIELD(arg0, s32*, 0x2B4) = 0;
			}
		}
		var_r27 += 4;
		goto loop_10;
	}
	return var_r31;
}

s16* fn_8_B193C(void* arg0, void* arg1, f32 farg0)
{
	M2C_UNK sp8;
	f32 temp_f1;
	f32 var_f31;
	s16** var_r30;
	s16* temp_r3;
	s16* var_r29;

	var_r29 = NULL;
	var_f31 = lbl_8_rodata_1BF8;
	if (lbl_8_rodata_1BEC != farg0) {
		var_f31 = farg0 * farg0;
	}
	var_r30 = M2C_FIELD(lbl_8042C380, s16***, 0x28);
loop_7:
	temp_r3 = *var_r30;
	if (temp_r3 != NULL) {
		if ((s16)*temp_r3 == 1) {
			fn_800AFB50(NULL, &sp8);
			temp_f1 = fn_800D71DC(arg1, &sp8);
			if (temp_f1 < var_f31) {
				var_f31                      = temp_f1;
				var_r29                      = *var_r30;
				M2C_FIELD(arg0, s32*, 0x2B4) = 1;
			}
		}
		var_r30 += 4;
		goto loop_7;
	}
	return var_r29;
}

s32 fn_8_B1A0C(s32 arg0, s32 arg1, f32 farg0)
{
	if (fn_800D71DC(lbl_8042C208) > lbl_8_rodata_1C00) {
		return 0;
	}
	return fn_800A6D60(arg0, arg1, farg0);
}

void fn_8_B1A90(void) { }

void fn_8_B1A94(void* arg0)
{
	((TRenderer*)arg0)->Slot90();
	fn_80113874();
	fn_8014FF2C(M2C_FIELD(arg0, s32*, 0xE8));
	fn_8014FF2C(M2C_FIELD(arg0, s32*, 0x310));
	fn_8014FF2C(M2C_FIELD(arg0, s32*, 0x314));
}

void fn_8_B1AE8(void* arg0)
{
	void* temp_r4;
	void* temp_r4_2;
	void* temp_r4_3;
	void* temp_r5;

	if ((s32)M2C_FIELD(arg0, s32*, 0x2B4) != 0) {
		M2C_FIELD(arg0, f32*, 0x248) = (f32)lbl_8_rodata_1BD0;
	} else {
		temp_r4 = M2C_FIELD(arg0, void**, 0x24C);
		if (temp_r4 != NULL) {
			M2C_FIELD(arg0, f32*, 0x248) = (f32)(M2C_FIELD(temp_r4, f32*, 4) - lbl_8_rodata_1C04);
		}
	}
	temp_r5                      = M2C_FIELD(M2C_FIELD(arg0, void**, 0xB0), void**, 0x2C);
	M2C_FIELD(arg0, s32*, 0x2E8) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 0);
	M2C_FIELD(arg0, s32*, 0x2EC) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 1);
	M2C_FIELD(arg0, f32*, 0x2F0) = (f32)M2C_FIELD(temp_r5, f32*, 0x10);
	M2C_FIELD(arg0, f32*, 0x2F4) = (f32)M2C_FIELD(temp_r5, f32*, 0xC);
	M2C_FIELD(arg0, f32*, 0x2F8) = (f32)M2C_FIELD(temp_r5, f32*, 0x14);
	M2C_FIELD(arg0, s32*, 0x300) = (s32)(s8)M2C_FIELD(temp_r5, u8*, 2);
	temp_r4_2                    = M2C_FIELD(arg0, void**, 0xB0);
	M2C_FIELD(arg0, f32*, 0x140) = (f32)M2C_FIELD(temp_r4_2, f32*, 0);
	M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(temp_r4_2, f32*, 4);
	M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(temp_r4_2, f32*, 8);
	M2C_FIELD(arg0, f32*, 0x1C0) = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1C4) = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1C8) = (f32)M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, f32*, 0x1CC) = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1D0) = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1D4) = (f32)M2C_FIELD(arg0, f32*, 0x148);
	temp_r4_3                    = M2C_FIELD(arg0, void**, 0xB0);
	M2C_FIELD(arg0, s32*, 0x150) = (s32)M2C_FIELD(temp_r4_3, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0x154) = 0;
	M2C_FIELD(arg0, s32*, 0x14C) = 0;
	M2C_FIELD(arg0, f32*, 0x1C0) = (f32)M2C_FIELD(arg0, f32*, 0x140);
	M2C_FIELD(arg0, f32*, 0x1C4) = (f32)M2C_FIELD(arg0, f32*, 0x144);
	M2C_FIELD(arg0, f32*, 0x1C8) = (f32)M2C_FIELD(arg0, f32*, 0x148);
	M2C_FIELD(arg0, f32*, 0x2AC) = (f32)M2C_FIELD(temp_r5, f32*, 4);
	M2C_FIELD(arg0, s32*, 0x2B0) = (s32)M2C_FIELD(temp_r5, s32*, 8);
	fn_8_B3598(temp_r4_3, temp_r5);
}

void fn_8_B1C1C(void* arg0)
{
	f32 temp_f1;
	s32 var_r0;
	s32 var_r0_2;
	void** temp_r3;

	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x20) != 0) {
		var_r0 = 0;
	} else if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x21) != 0) {
		var_r0 = 0;
	} else {
		var_r0 = 1;
	}
	M2C_FIELD(arg0, s32*, 0x2E0) = var_r0;
	if ((s8)M2C_FIELD(lbl_8042C180, u8*, 0x1F) != 0) {
		var_r0_2 = 0;
	} else {
		var_r0_2 = 1;
	}
	M2C_FIELD(arg0, s32*, 0x2E4) = var_r0_2;
	if ((u32)M2C_FIELD(arg0, u32*, 0x38) != 0U) {
		M2C_FIELD(arg0, f32*, 0x140) = (f32)M2C_FIELD(arg0, f32*, 0x88);
		M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(arg0, f32*, 0x8C);
		M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(arg0, f32*, 0x90);
	}
	fn_800A5B34(arg0);
	((TRenderer*)arg0)->Slot38();
	temp_r3 = M2C_FIELD(arg0, void***, 0x244);
	if (temp_r3 != NULL) {
		M2C_FIELD(*temp_r3, M2C_UNK(**)(void*), 0xC)(arg0);
	}
	((TRenderer*)arg0)->Slot50(M2C_FIELD(arg0, s32*, 0x19C), 1);
	fn_8_B3598(arg0);
	fn_800A3D48(arg0);
	if ((s32)M2C_FIELD(arg0, s32*, 0x2E0) != 0) {
		temp_f1 = M2C_FIELD(arg0, f32*, 0x2FC);
		if (temp_f1 < lbl_8_rodata_1BDC) {
			M2C_FIELD(arg0, s32*, 0x2B8) = 0x70;
			M2C_FIELD(arg0, s32*, 0x2BC) = 0x70;
		} else {
			M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
			if ((temp_f1 == lbl_8_rodata_1BDC) && (temp_f1 < lbl_8_rodata_1BE0)) {
				M2C_FIELD(arg0, s32*, 0x2B8) = 0x100;
				M2C_FIELD(arg0, s32*, 0x2BC) = 0x100;
			} else {
				M2C_FIELD(arg0, s32*, 0x2B8) = 0x400;
				M2C_FIELD(arg0, s32*, 0x2BC) = 0x400;
			}
		}
	}
	if ((fn_80017800(arg0) != 0) && ((u32)M2C_FIELD(arg0, u32*, 0x38) != 0U)) {
		fn_8003BE78((u8*)arg0 + 0x28);
		M2C_FIELD(arg0, f32*, 0xA4) = (f32)M2C_FIELD(arg0, f32*, 0x88);
		M2C_FIELD(arg0, f32*, 0xA8) = (f32)M2C_FIELD(arg0, f32*, 0x8C);
		M2C_FIELD(arg0, f32*, 0xAC) = (f32)M2C_FIELD(arg0, f32*, 0x90);
		M2C_FIELD(arg0, f32*, 0x88) = (f32)M2C_FIELD(arg0, f32*, 0x140);
		M2C_FIELD(arg0, f32*, 0x8C) = (f32)M2C_FIELD(arg0, f32*, 0x144);
		M2C_FIELD(arg0, f32*, 0x90) = (f32)M2C_FIELD(arg0, f32*, 0x148);
		M2C_FIELD(arg0, s32*, 0x94) = (s32)M2C_FIELD(arg0, s32*, 0x14C);
		M2C_FIELD(arg0, s32*, 0x98) = (s32)M2C_FIELD(arg0, s32*, 0x150);
		M2C_FIELD(arg0, s32*, 0x9C) = (s32)M2C_FIELD(arg0, s32*, 0x154);
		fn_8003BC38((u8*)arg0 + 0x28);
	}
}

void fn_8_B1E38(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			((TRenderer*)arg0)->Slot3C();
			return;
		case 1:
			M2C_FIELD(arg0, u16*, 4) = (u16)(M2C_FIELD(arg0, u16*, 4) | 1);
			return;
	}
}

void fn_8_B1E98(void) { }

void fn_8_B1E9C(void* arg0, s32 arg1)
{
	f32 sp64;
	f32 sp48;
	f32 sp44;
	f32 sp40;
	f32 sp3C;
	s16 sp2C;
	s32 sp28;
	s32 sp24;
	s32 sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	M2C_UNK sp8;
	f32* temp_r3_2;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 var_f31;
	s16** var_r27;
	s16* temp_r3;
	s16* var_r28;
	s32 temp_r0;
	s32 var_r0;

	switch (arg1) { /* switch 1; irregular */
		case 0:     /* switch 1 */
			temp_r0 = M2C_FIELD(arg0, s32*, 0x318);
			switch (temp_r0) { /* switch 2; irregular */
				case 0:        /* switch 2 */
					var_r28 = NULL;
					var_f31 = lbl_8_rodata_1BF8;
					var_r27 = M2C_FIELD(lbl_8042C380, s16***, 0x28);
				loop_16:
					temp_r3 = *var_r27;
					if (temp_r3 != NULL) {
						if ((s16)*temp_r3 == 1) {
							fn_800AFB50(NULL, &sp8);
							temp_f1 = fn_800D71DC((u8*)arg0 + 0x140, &sp8);
							if (temp_f1 < var_f31) {
								var_f31                      = temp_f1;
								var_r28                      = *var_r27;
								M2C_FIELD(arg0, s32*, 0x2B4) = 1;
							}
						}
						var_r27 += 4;
						goto loop_16;
					}
					M2C_FIELD(arg0, s16**, 0x24C) = var_r28;
					if ((s16*)M2C_FIELD(arg0, s16**, 0x24C) != NULL) {
						sp3C = lbl_8_rodata_1BD0;
						if (fn_800AF3AC(&sp2C) == 1) {
							sp20 = M2C_FIELD(&lbl_8_rodata_1BC4, s32*, 0);
							sp24 = M2C_FIELD(&lbl_8_rodata_1BC4, s32*, 4);
							sp28 = M2C_FIELD(&lbl_8_rodata_1BC4, s32*, 8);
							fn_800D735C(&sp64, 0, &sp20);
							M2C_FIELD(arg0, f32*, 0x254) = sp40;
							M2C_FIELD(arg0, f32*, 0x258) = sp44;
							M2C_FIELD(arg0, f32*, 0x25C) = sp48;
							M2C_FIELD(arg0, s32*, 0x26C) = sp20;
							M2C_FIELD(arg0, s32*, 0x270) = sp24;
							M2C_FIELD(arg0, s32*, 0x274) = sp28;
						}
						M2C_FIELD(arg0, f32*, 0x248) = (f32)lbl_8_rodata_1BD0;
						M2C_FIELD(arg0, s32*, 0x27C) = 0;
						M2C_FIELD(arg0, f32*, 0x260)
						    = (f32)(M2C_FIELD(arg0, f32*, 0x254) - M2C_FIELD(arg0, f32*, 0x140));
						M2C_FIELD(arg0, f32*, 0x264)
						    = (f32)(M2C_FIELD(arg0, f32*, 0x258) - M2C_FIELD(arg0, f32*, 0x144));
						temp_f1_2 = M2C_FIELD(arg0, f32*, 0x25C);
						M2C_FIELD(arg0, f32*, 0x268)
						    = (f32)(temp_f1_2 - M2C_FIELD(arg0, f32*, 0x148));
						temp_r3_2 = (f32*)((u8*)arg0 + 0x260);
						fn_801990E0(temp_r3_2, temp_r3_2, temp_f1_2);
						M2C_FIELD(arg0, f32*, 0x260)
						    = (f32)(M2C_FIELD(arg0, f32*, 0x260) * M2C_FIELD(arg0, f32*, 0x2FC));
						M2C_FIELD(arg0, f32*, 0x264)
						    = (f32)(M2C_FIELD(arg0, f32*, 0x264) * M2C_FIELD(arg0, f32*, 0x2FC));
						M2C_FIELD(arg0, f32*, 0x268)
						    = (f32)(M2C_FIELD(arg0, f32*, 0x268) * M2C_FIELD(arg0, f32*, 0x2FC));
						M2C_FIELD(arg0, s32*, 0xD4) = 1;
						if ((u32)lbl_8042C388 != 0U) {
							fn_800B4A38(0x4038, (u8*)arg0 + 0x140, 0, 1, 0, 0);
							return;
						}
					} else {
						case 2: /* switch 1 */
							return;
					}
					break;
				case 1: /* switch 2 */
					fn_8_B1078(arg0);
					return;
			}
			break;
		case 1: /* switch 1 */
			M2C_FIELD(arg0, s32*, 0x27C) = (s32)(M2C_FIELD(arg0, s32*, 0x27C) + 0x250);
			M2C_FIELD(arg0, f32*, 0x278)
			    = (f32)(lbl_8_rodata_1BFC * fn_800D7B00(M2C_FIELD(arg0, s32*, 0x27C)));
			M2C_FIELD(arg0, s32*, 0x14C) = (s32)M2C_FIELD(arg0, s32*, 0x26C);
			M2C_FIELD(arg0, s32*, 0x150)
			    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x150), M2C_FIELD(arg0, s32*, 0x270), 0x80);
			M2C_FIELD(arg0, s32*, 0x154)
			    = fn_800D7A94(M2C_FIELD(arg0, s32*, 0x154), M2C_FIELD(arg0, s32*, 0x274), 0x80);
			sp14 = M2C_FIELD(arg0, f32*, 0x140);
			sp18 = M2C_FIELD(arg0, f32*, 0x144);
			sp1C = M2C_FIELD(arg0, f32*, 0x148);
			M2C_FIELD(arg0, f32*, 0x140)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x260) + M2C_FIELD(arg0, f32*, 0x140));
			M2C_FIELD(arg0, f32*, 0x144)
			    = (f32)(M2C_FIELD(arg0, f32*, 0x264) + M2C_FIELD(arg0, f32*, 0x144));
			temp_f1_3                    = M2C_FIELD(arg0, f32*, 0x268);
			M2C_FIELD(arg0, f32*, 0x148) = (f32)(temp_f1_3 + M2C_FIELD(arg0, f32*, 0x148));
			if (fn_800D7BD8((u8*)arg0 + 0x254, &sp14, (u8*)arg0 + 0x140, 0, temp_f1_3)
			    < lbl_8_rodata_1BDC) {
				M2C_FIELD(arg0, f32*, 0x140) = (f32)M2C_FIELD(arg0, f32*, 0x254);
				M2C_FIELD(arg0, f32*, 0x144) = (f32)M2C_FIELD(arg0, f32*, 0x258);
				M2C_FIELD(arg0, f32*, 0x148) = (f32)M2C_FIELD(arg0, f32*, 0x25C);
				var_r0                       = 1;
			} else {
				var_r0 = 0;
			}
			if (var_r0 == 1) {
				M2C_FIELD(arg0, s32*, 0x240) = 2;
				if ((u32)lbl_8042C388 != 0U) {
					fn_800B4A38(0x4039, (u8*)arg0 + 0x140, 0, 1, 0, 0);
					return;
				}
			}
			break;
		case 3: /* switch 1 */
			M2C_FIELD(arg0, s32*, 0xD4) = 0;
			break;
	}
}

void fn_8_B2224(void* arg0, s32 arg1)
{
	s32 sp44;
	s32 sp40;
	s32 sp3C;
	s32 sp38;
	s32 sp34;
	s32 sp30;
	f32 sp2C;
	f32 sp28;
	f32 sp24;
	f32 sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	s32 sp10;
	s32 spC;
	s32 sp8;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x2C4) = 0;
			return;
		case 1:
			fn_8_B2BB4();
			fn_8_B0D34(arg0);
			if ((s32)M2C_FIELD(arg0, s32*, 0x2C4) == 0) {
				sp1C = lbl_8_rodata_1BD0;
				sp18 = lbl_8_rodata_1BD0;
				sp14 = lbl_8_rodata_1BD0;
				sp28 = lbl_8_rodata_1BD0;
				sp24 = lbl_8_rodata_1BD0;
				sp20 = lbl_8_rodata_1BD0;
				sp38 = 0;
				sp34 = 0;
				sp30 = 0;
				sp3C = 0x12C;
				sp40 = 1;
				sp44 = 8;
				sp14 = M2C_FIELD(arg0, f32*, 0x294);
				sp18 = M2C_FIELD(arg0, f32*, 0x298);
				sp1C = M2C_FIELD(arg0, f32*, 0x29C);
				sp20 = M2C_FIELD(arg0, f32*, 0x2A0);
				sp24 = M2C_FIELD(arg0, f32*, 0x2A4);
				sp28 = M2C_FIELD(arg0, f32*, 0x2A8);
				sp2C = M2C_FIELD(arg0, f32*, 0x2AC);
				if ((s32)M2C_FIELD(arg0, s32*, 0x300) == 0) {
					sp40 = 1;
				} else {
					sp40 = 0;
				}
				sp3C = 0x258;
				sp44 = ((TRenderer*)arg0)->Slot90();
				fn_8_B5160(&sp14);
				sp8  = M2C_FIELD(&lbl_8_rodata_1BB8, s32*, 0);
				spC  = M2C_FIELD(&lbl_8_rodata_1BB8, s32*, 4);
				sp10 = M2C_FIELD(&lbl_8_rodata_1BB8, s32*, 8);
				fn_8006298C(5, (u8*)arg0 + 0x294, &sp8);
				if ((u32)lbl_8042C388 != 0U) {
					fn_800B4A38(0x403B, (u8*)arg0 + 0x140, 0, 1, 0, 0);
				}
				M2C_FIELD(arg0, s32*, 0x2C4) = 1;
			}
			return;
	}
}

void fn_8_B23BC(void* arg0, s32 arg1)
{
	if (arg1 != 1) {
		if (arg1 < 1) {
			return;
		}
		return;
	}
	fn_8_B2BB4();
	fn_8_B0D34(arg0);
}

void fn_8_B240C(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			if ((u32)lbl_8042C388 != 0U) {
				fn_800B4A38(0x403D, (u8*)arg0 + 0x140, 0, 1, 0, 0);
				return;
			}
			return;
		case 1:
			fn_8_B2BB4();
			M2C_FIELD(arg0, f32*, 0x2FC) = (f32)(M2C_FIELD(arg0, f32*, 0x2FC) * lbl_8_rodata_1BF0);
			if (M2C_FIELD(arg0, f32*, 0x2FC) < lbl_8_rodata_1BD0) {
				M2C_FIELD(arg0, f32*, 0x2FC) = (f32)lbl_8_rodata_1BD0;
			}
			break;
	}
}

void fn_8_B24C0(void* arg0, s32 arg1)
{
	s32 var_r0;
	void* temp_r4;

	if (arg1 != 1) {
		if (arg1 < 1) {
			return;
		}
		return;
	}
	temp_r4 = M2C_FIELD(arg0, void**, 0x24C);
	if (temp_r4 == NULL) {
		var_r0 = 0;
	} else if ((s32)M2C_FIELD(arg0, s32*, 0x2B4) != 0) {
		if (lbl_8_rodata_1BD0 == M2C_FIELD(arg0, f32*, 0x248)) {
			var_r0 = 1;
		} else {
			var_r0 = 0;
		}
	} else if (M2C_FIELD(arg0, f32*, 0x248) == (M2C_FIELD(temp_r4, f32*, 4) - lbl_8_rodata_1C04)) {
		var_r0 = 1;
	} else {
		var_r0 = 0;
	}
	if (var_r0 != 0) {
		fn_8_B2BB4();
	}
}
