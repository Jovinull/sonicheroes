#include "types.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_BITWISE(type, value)      (*(type*)&(value))
#define M2C_ERROR(...)                0

s32 RwEngineRegisterPlugin(M2C_UNK, M2C_UNK, void (*)(), s32 (*)(s32)); /* extern */
void fn_8014F1B0();                                                     /* extern */
M2C_UNK fn_8014F854();                                                  /* extern */
u8* fn_80150140();                                                      /* extern */
M2C_UNK fn_8015028C();                                                  /* extern */
M2C_UNK fn_80150358();                                                  /* extern */
s32 fn_801520D0();                                                      /* extern */
s32 fn_80152150();                                                      /* extern */
M2C_UNK fn_80152220();                                                  /* extern */
s32 fn_80152288();                                                      /* extern */
M2C_UNK fn_80152EEC();                                                  /* extern */
M2C_UNK fn_8015498C();                                                  /* extern */
u32 fn_80192ED8();                                                      /* extern */
s32 fn_80192F38();                                                      /* extern */
M2C_UNK fn_8019336C();                                                  /* extern */
M2C_UNK fn_80193474();                                                  /* extern */
M2C_UNK fn_801937A0();                                                  /* extern */
M2C_UNK fn_80193884();                                                  /* extern */
s32 fn_80193B58();                                                      /* extern */
M2C_UNK fn_80193B60();                                                  /* extern */
M2C_UNK fn_80193DA4();                                                  /* extern */
M2C_UNK fn_80195674();                                                  /* extern */
M2C_UNK fn_801979AC();                                                  /* extern */
M2C_UNK fn_80197B48();                                                  /* extern */
M2C_UNK fn_801990E0();                                                  /* extern */
f32 fn_801991F4();                                                      /* extern */
M2C_UNK fn_8019941C();                                                  /* extern */
M2C_UNK fn_8019947C();                                                  /* extern */
s32 fn_8019AA5C();                                                      /* extern */
M2C_UNK fn_8019AAFC();                                                  /* extern */
s32 fn_8019ADB4();                                                      /* extern */
u8* fn_8019E344();                                                      /* extern */
M2C_UNK fn_8019E480();                                                  /* extern */
s32 fn_8019E8EC();                                                      /* extern */
M2C_UNK fn_801A491C();                                                  /* extern */
u8* fn_801FCEA0();                                                      /* extern */
s32* fn_801FD214();                                                     /* extern */
s32 fn_801FD224();                                                      /* extern */
M2C_UNK fn_801FD3B4();                                                  /* extern */
M2C_UNK memcpy();                                                       /* extern */
M2C_UNK memset(M2C_UNK*, M2C_UNK, s32);                                 /* extern */
M2C_UNK* fn_802321EC();                                                 /* static */
s32 fn_80232288();                                                      /* static */
u8* fn_8023239C();                                                      /* static */
u8* fn_802324E0();                                                      /* static */
M2C_UNK* fn_80232604();                                                 /* static */
M2C_UNK* fn_80232648();                                                 /* static */
u8* fn_8023268C();                                                      /* static */
M2C_UNK* fn_8023271C();                                                 /* static */
s32 fn_80232960();                                                      /* static */
u8* fn_80232968();                                                      /* static */
s32 fn_80232A9C();                                                      /* static */
u8* fn_80232BAC();                                                      /* static */
M2C_UNK* fn_80232E34();                                                 /* static */
u8* fn_80232E58();                                                      /* static */
M2C_UNK* fn_80232F98();                                                 /* static */
u8* fn_8023312C();                                                      /* static */
M2C_UNK* fn_802332AC();                                                 /* static */
M2C_UNK* fn_80233714();                                                 /* static */
u8* fn_802338B8();                                                      /* static */
u8* fn_80233DF8();                                                      /* static */
M2C_UNK* fn_80233F50();                                                 /* static */
M2C_UNK* fn_80234058();                                                 /* static */
M2C_UNK* fn_80234338();                                                 /* static */
s32 fn_802343C4();                                                      /* static */
u8* fn_802344D8();                                                      /* static */
u8* fn_802345C8();                                                      /* static */
M2C_UNK* fn_802346EC();                                                 /* static */
M2C_UNK* fn_80234730();                                                 /* static */
u8* fn_80234774();                                                      /* static */
M2C_UNK* fn_80234804();                                                 /* static */
s32 fn_80234A30();                                                      /* static */
s32 fn_80234A38();                                                      /* static */
s32 fn_80234EA0();                                                      /* static */
s32 fn_8023501C();                                                      /* static */
s32 fn_8023506C();                                                      /* static */
u8* fn_802350D4();                                                      /* static */
u8* fn_80235118();                                                      /* static */
u8* fn_8023521C();                                                      /* static */
u8* fn_802354D4();                                                      /* static */
s32 fn_80235590();                                                      /* static */
void fn_802355D4();                                                     /* static */
u8* fn_80235614();                                                      /* static */
void fn_802356AC();                                                     /* static */
u8* fn_802356F0();                                                      /* static */
u8* fn_802357A8();                                                      /* static */
u8* fn_8023582C();                                                      /* static */
s32 fn_802358B0();                                                      /* static */
M2C_UNK* fn_802358B8();                                                 /* static */
M2C_UNK* fn_80235CEC();                                                 /* static */
u8* fn_80235E64();                                                      /* static */
u8* fn_80236AE4();                                                      /* static */
u8* fn_80237EBC();                                                      /* static */
u8* fn_80237F90();                                                      /* static */
u8* fn_80237FF4();                                                      /* static */
s32 fn_80238228();                                                      /* static */
s32 fn_80238328();                                                      /* static */
u8* fn_802383C0();                                                      /* static */
u8* fn_80238444();                                                      /* static */
u8* fn_802388D4();                                                      /* static */
u8* fn_80238D3C();                                                      /* static */
u8* fn_80238E6C();                                                      /* static */
s32 fn_80238F88();                                                      /* static */
void fn_80238FEC();                                                     /* static */
s32 fn_80238FF0();                                                      /* static */
void fn_8023914C();                                                     /* static */
void fn_80239178();                                                     /* static */
s32 fn_80239184();                                                      /* static */
s32 fn_802391FC();                                                      /* static */
s32 fn_8023927C();                                                      /* static */
s32 fn_80239290();                                                      /* static */
s32* fn_802392DC();                                                     /* static */
s32* fn_802393A0();                                                     /* static */
s32 fn_8023943C();                                                      /* static */
M2C_UNK* (*fn_80239690())();                                            /* static */
u8* fn_80239738();                                                      /* static */
s32 fn_80239888();                                                      /* static */
s32 fn_8023989C();                                                      /* static */
extern M2C_UNK* lbl_8042C9A4;
extern s32 lbl_8042CF48;
extern f32 lbl_80430248;
extern f32 lbl_80430250;
extern f32 lbl_80430254;
extern f32 lbl_80430258;
extern f32 lbl_8043025C;
extern f32 lbl_80430260;
extern f32 lbl_80430268;
extern f32 lbl_8043026C;
extern f32 lbl_80430270;
extern f32 lbl_80430274;
extern f32 lbl_80430278;
extern f32 lbl_8043027C;
extern f64 lbl_80430280;
extern f32 lbl_80430298;
/* The engine-wide RenderWare state block. m2c declared this as a single word,
 * because every access it saw went through a computed offset; symbols.txt has
 * it as .bss:0x8042AC68 size 0xF4, and the offsets reached from here run past
 * 0x6C. Declared at four bytes it fits under mwcc's small-data threshold, so
 * the compiler addressed it with a one-instruction @sda21 reference where
 * retail uses the lis/addi pair, and every function that touched it came out
 * an instruction short. */
static M2C_UNK lbl_8042AC68[0xF4 / sizeof(M2C_UNK)];

M2C_UNK* fn_802321EC(void)
{
	M2C_UNK* sp8;
	M2C_UNK* temp_r3;
	M2C_UNK* temp_r4;

	temp_r3 = M2C_FIELD(lbl_8042C9A4, M2C_UNK * (**)(M2C_UNK, M2C_UNK*), 0x134)(0x1C, lbl_8042C9A4);
	if (temp_r3 != NULL) {
		sp8 = temp_r3;
		memset(temp_r3, 0, 0x1C);
		M2C_FIELD(sp8, M2C_UNK**, 0)  = sp8;
		M2C_FIELD(sp8, M2C_UNK***, 4) = &sp8;
		M2C_FIELD(sp8, s32*, 8)       = 1;
		temp_r4                       = M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60);
		if (temp_r4 == NULL) {
			*temp_r3 = (M2C_UNK)temp_r3;
		} else {
			*temp_r3 = *temp_r4;
			*temp_r4 = (M2C_UNK)temp_r3;
		}
		M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60) = temp_r3;
	}
	return temp_r3;
}

s32 fn_80232288(M2C_UNK* arg0)
{
	M2C_UNK* temp_r0;
	u8* temp_r3_2;
	u8* temp_r3_3;
	M2C_UNK* var_r4;
	M2C_UNK* var_r5;

	M2C_FIELD(arg0, s32*, 8) = (s32)(M2C_FIELD(arg0, s32*, 8) - 1);
	if ((s32)M2C_FIELD(arg0, s32*, 8) > 0) {
		return 1;
	}
	if ((M2C_UNK*)M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60) != NULL) {
		if (((M2C_UNK*)M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60) == arg0)
		    && ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0) == arg0)) {
			M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60) = NULL;
		} else {
			temp_r0 = (M2C_UNK*)*M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60);
			var_r5  = M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60);
			var_r4  = temp_r0;
		loop_7:
			if (var_r4 == arg0) {
				*var_r5                       = (M2C_UNK)M2C_FIELD(arg0, M2C_UNK**, 0);
				M2C_FIELD(arg0, M2C_UNK**, 0) = arg0;
			} else {
				var_r5 = var_r4;
				var_r4 = (M2C_UNK*)*var_r4;
				if (var_r4 != temp_r0) {
					goto loop_7;
				}
			}
			if ((M2C_UNK*)M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60) == arg0) {
				M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60) = var_r5;
			}
		}
	}
	temp_r3_2 = M2C_FIELD(arg0, u8**, 0x18);
	if (temp_r3_2 != NULL) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(temp_r3_2, lbl_8042C9A4);
	}
	temp_r3_3 = M2C_FIELD(arg0, u8**, 0x10);
	if (temp_r3_3 != NULL) {
		fn_80234EA0(temp_r3_3);
	}
	memset(arg0, 0, 4);
	M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(M2C_UNK*, M2C_UNK*), 0x138)(arg0, lbl_8042C9A4);
	return 1;
}

u8* fn_8023239C(u8* arg0, s32 arg1, u8* arg2)
{
	s32* var_r4;
	s32* var_r5;
	s32 temp_r0;
	s32 var_ctr;
	s32 var_r8;
	u8* var_r6;
	u8* temp_r3;
	u8* var_r28;
	u8* var_r7;

	var_r28 = NULL;
	temp_r3 = M2C_FIELD(lbl_8042C9A4, u8 * (**)(s32, M2C_UNK*), 0x134)(arg1 * 0x2C, lbl_8042C9A4);
	if (temp_r3 != NULL) {
		var_r6 = arg2;
		var_r7 = temp_r3;
		var_r8 = 0;
	loop_5:
		if (var_r8 < arg1) {
			M2C_FIELD(var_r7, s32*, 0)    = (s32)M2C_FIELD(var_r6, u8 * (**)(u8*), 0);
			var_r4                        = (s32*)(var_r6 + 0x28);
			var_r5                        = (s32*)(var_r7 + 0x28);
			M2C_FIELD(var_r7, s32*, 4)    = (s32)M2C_FIELD(var_r6, s32*, 4);
			M2C_FIELD(var_r7, s32*, 8)    = (s32)M2C_FIELD(var_r6, s32*, 8);
			M2C_FIELD(var_r7, s32*, 0xC)  = (s32)M2C_FIELD(var_r6, s32*, 0xC);
			M2C_FIELD(var_r7, s32*, 0x10) = (s32)M2C_FIELD(var_r6, s32*, 0x10);
			M2C_FIELD(var_r7, s32*, 0x14) = (s32)M2C_FIELD(var_r6, s32*, 0x14);
			M2C_FIELD(var_r7, s32*, 0x18) = (s32)M2C_FIELD(var_r6, s32*, 0x18);
			M2C_FIELD(var_r7, s32*, 0x1C) = (s32)M2C_FIELD(var_r6, s32*, 0x1C);
			M2C_FIELD(var_r7, s32*, 0x20) = (s32)M2C_FIELD(var_r6, s32*, 0x20);
			M2C_FIELD(var_r7, s32*, 0x24) = (s32)M2C_FIELD(var_r6, s32*, 0x24);
			var_ctr                       = 0xB - 0xA;
			if (0xA < 0xB) {
				do {
					temp_r0 = *var_r4;
					var_r4 += 4;
					*var_r5 = temp_r0;
					var_r5 += 4;
					var_ctr -= 1;
				} while (var_ctr != 0);
			}
			var_r6 += 0x2C;
			var_r7 += 0x2C;
			var_r8 += 1;
			goto loop_5;
		}
		if ((u8*)M2C_FIELD(arg0, u8**, 0x18) != NULL) {
			M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(
			    M2C_FIELD(arg0, u8**, 0x18), lbl_8042C9A4);
		}
		M2C_FIELD(arg0, s32*, 0x14) = arg1;
		var_r28                     = arg0;
		M2C_FIELD(arg0, u8**, 0x18) = temp_r3;
	}
	return var_r28;
}

void fn_802324CC(u8* arg0, s32* arg1, s32* arg2)
{
	*arg1 = M2C_FIELD(arg0, s32*, 0x14);
	*arg2 = M2C_FIELD(arg0, s32*, 0x18);
}

u8* fn_802324E0(u8* arg0, u8* arg1)
{
	s32 temp_r0;
	s32 temp_r3;
	s32 temp_r5;
	s32 var_ctr_2;
	s32 var_r4;
	s32 var_r4_2;
	s32 var_r7;
	s32 var_r8;
	u32 var_ctr;
	u8* temp_r6;

	if ((u8*)M2C_FIELD(arg0, u8**, 0x10) != NULL) {
		fn_80234EA0(M2C_FIELD(arg0, u8**, 0x10));
	}
	var_r8                      = 0;
	M2C_FIELD(arg1, s32*, 0xC)  = (s32)(M2C_FIELD(arg1, s32*, 0xC) + 1);
	M2C_FIELD(arg0, u8**, 0x10) = arg1;
	if (arg1 != NULL) {
		temp_r5 = M2C_FIELD(arg1, s32*, 0x10);
		var_r7  = 0;
		if (temp_r5 > 0) {
			temp_r3 = temp_r5 - 8;
			if (temp_r5 > 8) {
				var_r4  = 0;
				var_ctr = (u32)(temp_r3 + 7) >> 3U;
				if (temp_r3 > 0) {
					do {
						var_r7 += 8;
						temp_r6 = (u8*)M2C_FIELD(arg1, s32*, 0x20) + var_r4;
						var_r4 += 0x20;
						var_r8 = var_r8 + M2C_FIELD(temp_r6, s32*, 0) + M2C_FIELD(temp_r6, s32*, 4)
						    + M2C_FIELD(temp_r6, s32*, 8) + M2C_FIELD(temp_r6, s32*, 0xC)
						    + M2C_FIELD(temp_r6, s32*, 0x10) + M2C_FIELD(temp_r6, s32*, 0x14)
						    + M2C_FIELD(temp_r6, s32*, 0x18) + M2C_FIELD(temp_r6, s32*, 0x1C);
						var_ctr -= 1;
					} while (var_ctr != 0);
				}
			}
			var_r4_2  = var_r7 * 4;
			var_ctr_2 = temp_r5 - var_r7;
			if (var_r7 < temp_r5) {
				do {
					temp_r0 = *(s32*)((u8*)M2C_FIELD(arg1, s32*, 0x20) + var_r4_2);
					var_r4_2 += 4;
					var_r8 += temp_r0;
					var_ctr_2 -= 1;
				} while (var_ctr_2 != 0);
			}
		}
	}
	M2C_FIELD(arg0, s32*, 0xC) = var_r8;
	return arg0;
}

void fn_802325F8(u8* arg0, s32* arg1)
{
	*arg1 = M2C_FIELD(arg0, s32*, 0x10);
}

M2C_UNK* fn_80232604(s32 arg0)
{
	M2C_UNK* var_r4;
	M2C_UNK* var_r5;
	M2C_UNK* var_r6;

	var_r6 = NULL;
	var_r5 = M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60);
	var_r4 = var_r5;
	if (var_r5 != NULL) {
	loop_1:
		if ((s32)M2C_FIELD(var_r4, s32*, 4) == arg0) {
			var_r6 = var_r4;
		} else {
			var_r4 = M2C_FIELD(var_r4, M2C_UNK**, 0);
			if (var_r4 != var_r5) {
				goto loop_1;
			}
		}
	}
	return var_r6;
}

M2C_UNK* fn_80232648(u8* arg0)
{
	M2C_UNK* var_r4;
	M2C_UNK* var_r5;
	M2C_UNK* var_r6;

	var_r6 = NULL;
	var_r5 = M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60);
	var_r4 = var_r5;
	if (var_r5 != NULL) {
	loop_1:
		if ((u32)M2C_FIELD(var_r4, u32*, 0x10) == (u32)arg0) {
			var_r6 = var_r4;
		} else {
			var_r4 = M2C_FIELD(var_r4, M2C_UNK**, 0);
			if (var_r4 != var_r5) {
				goto loop_1;
			}
		}
	}
	return var_r6;
}

u8* fn_8023268C(u8* arg0, s32* arg1)
{
	if (fn_80192ED8(arg1, 0x25, fn_80232960(arg0), 0x35000, 0xFFFF) == 0U) {
		return NULL;
	}
	fn_80193474(arg1, arg0 + 4, 4);
	fn_80193474(arg1, M2C_FIELD(arg0, s32*, 0x10) + 8, 4);
	return arg0;
}

M2C_UNK* fn_8023271C(s32* arg0)
{
	s32 sp10;
	s32 spC;
	M2C_UNK* sp8;
	M2C_UNK* var_r30;
	M2C_UNK* var_r4;
	M2C_UNK* var_r5;
	s32 temp_r0_2;
	s32 temp_r3;
	s32 temp_r7;
	s32 var_ctr_2;
	s32 var_r4_2;
	s32 var_r5_2;
	s32 var_r6;
	s32 var_r6_2;
	u32 var_ctr;
	u8* temp_r0;
	u8* temp_r31;
	u8* temp_r8;

	fn_80193884(&spC, (s32*)4U);
	fn_80193884(arg0, &sp10, 4);
	var_r4 = NULL;
	var_r5 = M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60);
	if ((M2C_UNK*)M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60) != NULL) {
	loop_1:
		if ((s32)M2C_FIELD(var_r5, s32*, 4) == spC) {
			var_r4 = var_r5;
		} else {
			var_r5 = M2C_FIELD(var_r5, M2C_UNK**, 0);
			if (var_r5 != (M2C_UNK*)M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60)) {
				goto loop_1;
			}
		}
	}
	var_r30 = var_r4;
	if (var_r4 == NULL) {
		var_r30
		    = M2C_FIELD(lbl_8042C9A4, M2C_UNK * (**)(M2C_UNK, M2C_UNK*), 0x134)(0x1C, lbl_8042C9A4);
		if (var_r30 != NULL) {
			sp8 = var_r30;
			memset(var_r30, 0, 0x1C);
			M2C_FIELD(sp8, M2C_UNK**, 0)  = sp8;
			M2C_FIELD(sp8, M2C_UNK***, 4) = &sp8;
			M2C_FIELD(sp8, s32*, 8)       = 1;
			if ((M2C_UNK*)M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60) == NULL) {
				M2C_FIELD(var_r30, M2C_UNK**, 0) = var_r30;
			} else {
				M2C_FIELD(var_r30, M2C_UNK**, 0)         = M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60);
				M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60) = var_r30;
			}
			M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x60) = var_r30;
		}
		if (var_r30 != NULL) {
			temp_r0  = M2C_FIELD(var_r30, u8**, 0x10);
			temp_r31 = fn_802350D4(sp10);
			if (temp_r0 != NULL) {
				fn_80234EA0(temp_r0);
			}
			var_r4_2                       = 0;
			M2C_FIELD(temp_r31, s32*, 0xC) = (s32)(M2C_FIELD(temp_r31, s32*, 0xC) + 1);
			M2C_FIELD(var_r30, u8**, 0x10) = temp_r31;
			if (temp_r31 != NULL) {
				temp_r7  = M2C_FIELD(temp_r31, s32*, 0x10);
				var_r5_2 = 0;
				if (temp_r7 > 0) {
					temp_r3 = temp_r7 - 8;
					if (temp_r7 > 8) {
						var_r6  = 0;
						var_ctr = (u32)(temp_r3 + 7) >> 3U;
						if (temp_r3 > 0) {
							do {
								var_r5_2 += 8;
								temp_r8 = (u8*)M2C_FIELD(temp_r31, s32*, 0x20) + var_r6;
								var_r6 += 0x20;
								var_r4_2 = var_r4_2 + M2C_FIELD(temp_r8, s32*, 0)
								    + M2C_FIELD(temp_r8, s32*, 4) + M2C_FIELD(temp_r8, s32*, 8)
								    + M2C_FIELD(temp_r8, s32*, 0xC) + M2C_FIELD(temp_r8, s32*, 0x10)
								    + M2C_FIELD(temp_r8, s32*, 0x14)
								    + M2C_FIELD(temp_r8, s32*, 0x18)
								    + M2C_FIELD(temp_r8, s32*, 0x1C);
								var_ctr -= 1;
							} while (var_ctr != 0);
						}
					}
					var_r6_2  = var_r5_2 * 4;
					var_ctr_2 = temp_r7 - var_r5_2;
					if (var_r5_2 < temp_r7) {
						do {
							temp_r0_2 = *(s32*)((u8*)M2C_FIELD(temp_r31, s32*, 0x20) + var_r6_2);
							var_r6_2 += 4;
							var_r4_2 += temp_r0_2;
							var_ctr_2 -= 1;
						} while (var_ctr_2 != 0);
					}
				}
			}
			M2C_FIELD(var_r30, s32*, 0xC)  = var_r4_2;
			M2C_FIELD(var_r30, s32*, 4)    = spC;
			M2C_FIELD(var_r30, s32*, 0x14) = 0;
			M2C_FIELD(var_r30, s32*, 0x18) = 0;
			M2C_FIELD(lbl_8042AC68, M2C_UNK(**)(M2C_UNK*, M2C_UNK*, s32), 0x6C)(
			    var_r30, lbl_8042AC68, spC);
		}
	} else {
		M2C_FIELD(var_r4, s32*, 8) = (s32)(M2C_FIELD(var_r4, s32*, 8) + 1);
	}
	return var_r30;
}

s32 fn_80232960(u8* arg0)
{
	return 8;
}

u8* fn_80232968(u8* arg0)
{
	s32 temp_r3;
	s32 var_r29;
	s32 var_r30;
	u32 (*temp_r12)(M2C_UNK, u8*, M2C_UNK);
	u8* temp_r31;
	u8* var_r0;
	u8* var_r28;

	var_r28 = M2C_FIELD(lbl_8042C9A4, u8 * (**)(s32, M2C_UNK*), 0x134)(
	    M2C_FIELD(arg0, s32*, 0xC) + 0x28, lbl_8042C9A4);
	if (var_r28 != NULL) {
		M2C_FIELD(arg0, s32*, 8)       = (s32)(M2C_FIELD(arg0, s32*, 8) + 1);
		M2C_FIELD(var_r28, u8**, 0xC)  = arg0;
		M2C_FIELD(var_r28, u8**, 0)    = var_r28;
		M2C_FIELD(var_r28, s32*, 4)    = 0;
		M2C_FIELD(var_r28, s32*, 8)    = 0;
		M2C_FIELD(var_r28, s32*, 0x10) = 0;
		M2C_FIELD(var_r28, s32*, 0x14) = 0;
		M2C_FIELD(var_r28, s32*, 0x18) = 0;
		M2C_FIELD(var_r28, s32*, 0x1C) = 0;
		M2C_FIELD(var_r28, s32*, 0x20) = 0;
		memset((M2C_UNK*)(var_r28 + 0x28), 0,
		    M2C_FIELD(M2C_FIELD(var_r28, u8**, 0xC), s32*, 0xC) - 0x28);
		temp_r3 = fn_8023506C(M2C_FIELD(M2C_FIELD(var_r28, u8**, 0xC), u8**, 0x10), 6);
		if (temp_r3 >= 0) {
			fn_802355D4(var_r28 + temp_r3);
		}
		var_r30  = 0;
		temp_r31 = M2C_FIELD(var_r28, u8**, 0xC);
		var_r29  = 0;
	loop_8:
		if (var_r30 >= (s32)M2C_FIELD(temp_r31, s32*, 0x14)) {
			var_r0 = var_r28;
		} else {
			temp_r12 = (u32 (*)(M2C_UNK, u8*, M2C_UNK))
			    * (u32*)((u8*)M2C_FIELD(temp_r31, u8**, 0x18) + var_r29 + 0x14);
			if ((temp_r12 != NULL) && ((u8*)temp_r12(0, var_r28, 0) != var_r28)) {
				var_r0 = NULL;
			} else {
				var_r29 += 0x2C;
				var_r30 += 1;
				goto loop_8;
			}
		}
		var_r28 = var_r0;
	}
	return var_r28;
}

#pragma dont_inline on
s32 fn_80232A9C(u8* arg0)
{
	M2C_UNK* temp_r31;
	s32 temp_r3;
	s32 var_r28;
	s32 var_r29;
	s32 var_r30;
	u32 (*temp_r12)(M2C_UNK, u8*, M2C_UNK);
	u8* var_r0;

	var_r28 = 0;
	fn_80232E58();
	var_r30  = 0;
	temp_r31 = M2C_FIELD(arg0, M2C_UNK**, 0xC);
	var_r29  = 0;
loop_5:
	if (var_r30 >= (s32)M2C_FIELD(temp_r31, s32*, 0x14)) {
		M2C_FIELD(arg0, s32*, 0)    = 0;
		M2C_FIELD(arg0, s32*, 4)    = 0;
		M2C_FIELD(arg0, s32*, 0x10) = 0;
		M2C_FIELD(arg0, s32*, 0x14) = 0;
		M2C_FIELD(arg0, s32*, 0x1C) = 0;
		M2C_FIELD(arg0, s32*, 0x20) = 0;
		M2C_FIELD(arg0, f32*, 0x24) = (f32)lbl_80430248;
		temp_r3 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, M2C_UNK**, 0xC), u8**, 0x10), 6);
		if (temp_r3 >= 0) {
			fn_80235614(arg0 + temp_r3);
		}
		fn_80232288(M2C_FIELD(arg0, M2C_UNK**, 0xC));
		fn_802343C4(M2C_FIELD(arg0, M2C_UNK**, 0x18));
		var_r0 = arg0;
	} else {
		temp_r12 = (u32 (*)(M2C_UNK, u8*, M2C_UNK))
		    * (u32*)((u8*)M2C_FIELD(temp_r31, u8**, 0x18) + var_r29 + 0x18);
		if ((temp_r12 != NULL) && ((u8*)temp_r12(0, arg0, 0) != arg0)) {
			var_r0 = NULL;
		} else {
			var_r29 += 0x2C;
			var_r30 += 1;
			goto loop_5;
		}
	}
	if (var_r0 == arg0) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(arg0, lbl_8042C9A4);
		var_r28 = 1;
	}
	return var_r28;
}
#pragma dont_inline reset

#pragma dont_inline on
u8* fn_80232BAC(M2C_UNK* arg0)
{
	M2C_UNK* temp_r28_2;
	s32 temp_r3;
	s32 temp_r3_2;
	s32 var_r27;
	s32 var_r27_2;
	s32 var_r27_3;
	s32 var_r28;
	s32 var_r29;
	s32 var_r29_2;
	u32 (*temp_r12)(M2C_UNK, u8*, M2C_UNK);
	u32 (*temp_r12_2)(s32, M2C_UNK*, u8*);
	u32 (*temp_r12_3)(M2C_UNK, u8*, M2C_UNK);
	u8* temp_r28;
	u8* temp_r29;
	u8* temp_r29_2;
	u8* var_r0;
	u8* var_r0_2;
	u8* var_r26;
	u8* var_r31;

	temp_r29 = M2C_FIELD(arg0, u8**, 0xC);
	var_r31 = M2C_FIELD(lbl_8042C9A4, u8 * (**)(s32), 0x134)(M2C_FIELD(temp_r29, s32*, 0xC) + 0x28);
	if (var_r31 != NULL) {
		M2C_FIELD(temp_r29, s32*, 8)   = (s32)(M2C_FIELD(temp_r29, s32*, 8) + 1);
		M2C_FIELD(var_r31, u8**, 0xC)  = temp_r29;
		M2C_FIELD(var_r31, u8**, 0)    = var_r31;
		M2C_FIELD(var_r31, s32*, 4)    = 0;
		M2C_FIELD(var_r31, s32*, 8)    = 0;
		M2C_FIELD(var_r31, s32*, 0x10) = 0;
		M2C_FIELD(var_r31, s32*, 0x14) = 0;
		M2C_FIELD(var_r31, s32*, 0x18) = 0;
		M2C_FIELD(var_r31, s32*, 0x1C) = 0;
		M2C_FIELD(var_r31, s32*, 0x20) = 0;
		memset((M2C_UNK*)(var_r31 + 0x28), 0,
		    M2C_FIELD(M2C_FIELD(var_r31, u8**, 0xC), s32*, 0xC) - 0x28);
		temp_r3 = fn_8023506C(M2C_FIELD(M2C_FIELD(var_r31, u8**, 0xC), u8**, 0x10), 6);
		if (temp_r3 >= 0) {
			fn_802355D4(var_r31 + temp_r3);
		}
		var_r29  = 0;
		temp_r28 = M2C_FIELD(var_r31, u8**, 0xC);
		var_r27  = 0;
	loop_8:
		if (var_r29 < (s32)M2C_FIELD(temp_r28, s32*, 0x14)) {
			temp_r12 = (u32 (*)(M2C_UNK, u8*, M2C_UNK))
			    * (u32*)((u8*)M2C_FIELD(temp_r28, u8**, 0x18) + var_r27 + 0x14);
			if ((temp_r12 != NULL) && ((u8*)temp_r12(0, var_r31, 0) != var_r31)) {
				var_r31 = NULL;
			} else {
				var_r27 += 0x2C;
				var_r29 += 1;
				goto loop_8;
			}
		}
	}
	var_r26 = var_r31;
	if (var_r31 != NULL) {
		M2C_FIELD(var_r31, s32*, 4) = (s32)M2C_FIELD(arg0, s32*, 4);
		fn_8023312C(var_r31, M2C_FIELD(arg0, M2C_UNK**, 0x18), M2C_FIELD(arg0, s32*, 0x14));
		var_r28    = 0;
		temp_r29_2 = M2C_FIELD(arg0, u8**, 0xC);
		var_r27_2  = 0;
	loop_15:
		if (var_r28 >= (s32)M2C_FIELD(temp_r29_2, s32*, 0x14)) {
			var_r0 = var_r31;
		} else {
			temp_r12_2 = (u32 (*)(s32, M2C_UNK*, u8*))
			    * (u32*)((u8*)M2C_FIELD(temp_r29_2, u8**, 0x18) + var_r27_2 + 0x28);
			if ((temp_r12_2 != NULL)
			    && ((u8*)temp_r12_2(M2C_FIELD(arg0, s32*, 8), (M2C_UNK*)arg0, var_r31)
			        != var_r31)) {
				var_r0 = NULL;
			} else {
				var_r27_2 += 0x2C;
				var_r28 += 1;
				goto loop_15;
			}
		}
		if (var_r0 != var_r31) {
			fn_80232E58(var_r31);
			var_r29_2  = 0;
			temp_r28_2 = M2C_FIELD(var_r31, M2C_UNK**, 0xC);
			var_r27_3  = 0;
		loop_23:
			if (var_r29_2 >= (s32)M2C_FIELD(temp_r28_2, s32*, 0x14)) {
				M2C_FIELD(var_r31, s32*, 0)    = 0;
				M2C_FIELD(var_r31, s32*, 4)    = 0;
				M2C_FIELD(var_r31, s32*, 0x10) = 0;
				M2C_FIELD(var_r31, s32*, 0x14) = 0;
				M2C_FIELD(var_r31, s32*, 0x1C) = 0;
				M2C_FIELD(var_r31, s32*, 0x20) = 0;
				M2C_FIELD(var_r31, f32*, 0x24) = (f32)lbl_80430248;
				temp_r3_2
				    = fn_8023506C(M2C_FIELD(M2C_FIELD(var_r31, M2C_UNK**, 0xC), u8**, 0x10), 6);
				if (temp_r3_2 >= 0) {
					fn_80235614(var_r31 + temp_r3_2);
				}
				fn_80232288(M2C_FIELD(var_r31, M2C_UNK**, 0xC));
				fn_802343C4(M2C_FIELD(var_r31, M2C_UNK**, 0x18));
				var_r0_2 = var_r31;
			} else {
				temp_r12_3 = (u32 (*)(M2C_UNK, u8*, M2C_UNK))
				    * (u32*)((u8*)M2C_FIELD(temp_r28_2, u8**, 0x18) + var_r27_3 + 0x18);
				if ((temp_r12_3 != NULL) && ((u8*)temp_r12_3(0, var_r31, 0) != var_r31)) {
					var_r0_2 = NULL;
				} else {
					var_r27_3 += 0x2C;
					var_r29_2 += 1;
					goto loop_23;
				}
			}
			if (var_r0_2 == var_r31) {
				M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(var_r31, lbl_8042C9A4);
			}
			var_r26 = NULL;
		}
	}
	return var_r26;
}
#pragma dont_inline reset

M2C_UNK* fn_80232E34(M2C_UNK* arg0, M2C_UNK* arg1)
{
	if (arg0 == NULL) {
		*arg1 = (M2C_UNK)arg1;
	} else {
		*arg1 = *arg0;
		*arg0 = (M2C_UNK)arg1;
	}
	return arg1;
}

u8* fn_80232E58(u8* arg0)
{
	s32 spC;
	u8** sp8;
	s32 var_r27;
	s32 var_r28;
	s32 var_r31;
	u32 (*temp_r12)(M2C_UNK, u8*, M2C_UNK);
	u8*** var_r26;
	u8** temp_r3;
	u8* temp_r23;
	u8* temp_r25;
	u8* temp_r29;
	u8* var_r24;

	var_r26 = &sp8;
	var_r31 = 0;
	sp8     = M2C_FIELD(arg0, u8***, 0x20);
	spC     = M2C_FIELD(arg0, s32*, 0x1C);
loop_1:
	temp_r3 = *var_r26;
	if (temp_r3 != NULL) {
		temp_r25 = *temp_r3;
		var_r24  = temp_r25;
	loop_3:
		temp_r23 = M2C_FIELD(var_r24, u8**, 0);
		if (var_r31 == 0) {
			var_r28 = 0;
			if (var_r24 != NULL) {
				temp_r29 = M2C_FIELD(var_r24, u8**, 4);
				var_r27  = 0;
			loop_9:
				if (var_r28 >= (s32)M2C_FIELD(temp_r29, s32*, 0x14)) {
					M2C_FIELD(var_r24, s32*, 8)    = 0;
					M2C_FIELD(var_r24, s32*, 0x10) = 0;
					M2C_FIELD(var_r24, u8**, 0)    = NULL;
				} else {
					temp_r12 = (u32 (*)(M2C_UNK, u8*, M2C_UNK))
					    * (u32*)((u8*)M2C_FIELD(temp_r29, u8**, 0x18) + var_r27 + 0xC);
					if ((temp_r12 == NULL) || ((u8*)temp_r12(0, var_r24, 0) == var_r24)) {
						var_r27 += 0x1C;
						var_r28 += 1;
						goto loop_9;
					}
				}
				M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(var_r24, lbl_8042C9A4);
				var_r28 = 1;
			}
			if (var_r28 == 0) {
				return NULL;
			}
			goto block_15;
		}
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(var_r24, lbl_8042C9A4);
	block_15:
		var_r24 = temp_r23;
		if (temp_r23 == temp_r25) {
			goto block_16;
		}
		goto loop_3;
	}
block_16:
	var_r31 += 1;
	var_r26 += 4;
	if (var_r31 >= 2) {
		M2C_FIELD(arg0, u8***, 0x20) = NULL;
		M2C_FIELD(arg0, s32*, 0x1C)  = 0;
		M2C_FIELD(arg0, s32*, 0x10)  = 0;
		return arg0;
	}
	goto loop_1;
}

M2C_UNK* fn_80232F98(u8* arg0)
{
	M2C_UNK** temp_r3;
	M2C_UNK* temp_r3_2;
	M2C_UNK* temp_r3_3;
	M2C_UNK* var_r28;
	s32 temp_r29;
	s32 temp_r4;
	s32 var_r27;
	s32 var_r27_2;
	s32 var_r28_2;
	s32 var_r30;
	u32 (*temp_r12)(M2C_UNK, M2C_UNK*, M2C_UNK);
	u32 (*temp_r12_2)(M2C_UNK, M2C_UNK*, M2C_UNK);
	u8* temp_r27;
	u8* temp_r29_2;
	u8* temp_r29_3;

	temp_r3  = M2C_FIELD(arg0, M2C_UNK***, 0x1C);
	temp_r27 = M2C_FIELD(arg0, u8**, 0x18);
	if (temp_r3 == NULL) {
		temp_r29 = M2C_FIELD(arg0, s32*, 0x14);
		temp_r4  = M2C_FIELD(temp_r27, s32*, 0xC) * temp_r29;
		temp_r3_2
		    = M2C_FIELD(lbl_8042C9A4, M2C_UNK * (**)(s32, s32), 0x134)(temp_r4 + 0x20, temp_r4);
		if (temp_r3_2 != NULL) {
			M2C_FIELD(temp_r3_2, s32*, 0xC)    = temp_r29;
			var_r28_2                          = 0;
			M2C_FIELD(temp_r3_2, u8**, 4)      = temp_r27;
			var_r27                            = 0;
			M2C_FIELD(temp_r3_2, s32*, 0x14)   = 0x20;
			M2C_FIELD(temp_r3_2, s32*, 8)      = 0;
			M2C_FIELD(temp_r3_2, s32*, 0x10)   = 0;
			M2C_FIELD(temp_r3_2, M2C_UNK**, 0) = temp_r3_2;
			temp_r29_2                         = M2C_FIELD(temp_r3_2, u8**, 4);
		loop_6:
			if (var_r28_2 < (s32)M2C_FIELD(temp_r29_2, s32*, 0x14)) {
				temp_r12 = (u32 (*)(M2C_UNK, M2C_UNK*, M2C_UNK))
				    * (u32*)((u8*)M2C_FIELD(temp_r29_2, u8**, 0x18) + var_r27 + 8);
				if ((temp_r12 == NULL) || ((M2C_UNK*)temp_r12(0, temp_r3_2, 0) == temp_r3_2)) {
					var_r27 += 0x1C;
					var_r28_2 += 1;
					goto loop_6;
				}
			}
		}
		var_r28 = temp_r3_2;
	} else {
		var_r28 = *temp_r3;
		if (var_r28 == (M2C_UNK*)temp_r3) {
			M2C_FIELD(arg0, M2C_UNK***, 0x1C) = NULL;
		} else {
			*temp_r3 = M2C_FIELD(var_r28, M2C_UNK**, 0);
		}
		M2C_FIELD(var_r28, M2C_UNK**, 0) = var_r28;
		var_r30                          = 0;
		var_r27_2                        = 0;
		M2C_FIELD(var_r28, s32*, 8)      = 0;
		M2C_FIELD(var_r28, s32*, 0x10)   = 0;
		M2C_FIELD(var_r28, M2C_UNK**, 0) = var_r28;
		temp_r29_3                       = M2C_FIELD(var_r28, u8**, 4);
	loop_15:
		if (var_r30 < (s32)M2C_FIELD(temp_r29_3, s32*, 0x14)) {
			temp_r12_2 = (u32 (*)(M2C_UNK, M2C_UNK*, M2C_UNK))
			    * (u32*)((u8*)M2C_FIELD(temp_r29_3, u8**, 0x18) + var_r27_2 + 8);
			if ((temp_r12_2 == NULL) || ((M2C_UNK*)temp_r12_2(0, var_r28, 0) == var_r28)) {
				var_r27_2 += 0x1C;
				var_r30 += 1;
				goto loop_15;
			}
		}
	}
	if (var_r28 != NULL) {
		temp_r3_3 = M2C_FIELD(arg0, M2C_UNK**, 0x20);
		if (temp_r3_3 == NULL) {
			*var_r28 = (M2C_UNK)var_r28;
		} else {
			*var_r28   = *temp_r3_3;
			*temp_r3_3 = (M2C_UNK)var_r28;
		}
		M2C_FIELD(arg0, M2C_UNK**, 0x20) = var_r28;
	}
	return var_r28;
}

u8* fn_8023312C(u8* arg0, M2C_UNK* arg1, s32 arg2)
{
	s32 spC;
	u8** sp8;
	s32 var_r21;
	s32 var_r22;
	s32 var_r31;
	u32 (*temp_r12)(M2C_UNK, u8*, M2C_UNK);
	u8*** var_r30;
	u8** temp_r3;
	u8* temp_r23;
	u8* temp_r25;
	u8* temp_r29;
	u8* var_r24;

	if ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0x18) != NULL) {
		var_r30 = &sp8;
		var_r31 = 0;
		sp8     = M2C_FIELD(arg0, u8***, 0x20);
		spC     = M2C_FIELD(arg0, s32*, 0x1C);
	loop_2:
		temp_r3 = *var_r30;
		if (temp_r3 != NULL) {
			temp_r29 = *temp_r3;
			var_r24  = temp_r29;
		loop_4:
			temp_r25 = M2C_FIELD(var_r24, u8**, 0);
			if (var_r31 == 0) {
				var_r22 = 0;
				if (var_r24 != NULL) {
					temp_r23 = M2C_FIELD(var_r24, u8**, 4);
					var_r21  = 0;
				loop_10:
					if (var_r22 >= (s32)M2C_FIELD(temp_r23, s32*, 0x14)) {
						M2C_FIELD(var_r24, s32*, 8)    = 0;
						M2C_FIELD(var_r24, s32*, 0x10) = 0;
						M2C_FIELD(var_r24, u8**, 0)    = NULL;
					} else {
						temp_r12 = (u32 (*)(M2C_UNK, u8*, M2C_UNK))
						    * (u32*)((u8*)M2C_FIELD(temp_r23, u8**, 0x18) + var_r21 + 0xC);
						if ((temp_r12 == NULL) || ((u8*)temp_r12(0, var_r24, 0) == var_r24)) {
							var_r21 += 0x1C;
							var_r22 += 1;
							goto loop_10;
						}
					}
					M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(
					    var_r24, lbl_8042C9A4);
					var_r22 = 1;
				}
				if (var_r22 == 0) {

				} else {
					goto block_16;
				}
			} else {
				M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(var_r24, lbl_8042C9A4);
			block_16:
				var_r24 = temp_r25;
				if (temp_r25 == temp_r29) {
					goto block_17;
				}
				goto loop_4;
			}
		} else {
		block_17:
			var_r31 += 1;
			var_r30 += 4;
			if (var_r31 >= 2) {
				M2C_FIELD(arg0, u8***, 0x20) = NULL;
				M2C_FIELD(arg0, s32*, 0x1C)  = 0;
				M2C_FIELD(arg0, s32*, 0x10)  = 0;
			} else {
				goto loop_2;
			}
		}
		fn_802343C4(M2C_FIELD(arg0, M2C_UNK**, 0x18));
	}
	M2C_FIELD(arg0, M2C_UNK**, 0x18) = arg1;
	M2C_FIELD(arg0, s32*, 0x14)      = arg2;
	M2C_FIELD(arg1, s32*, 8)         = (s32)(M2C_FIELD(arg1, s32*, 8) + 1);
	return arg0;
}

void fn_80233298(u8* arg0, s32* arg1, s32* arg2)
{
	*arg1 = M2C_FIELD(arg0, s32*, 0x18);
	*arg2 = M2C_FIELD(arg0, s32*, 0x14);
}

M2C_UNK* fn_802332AC(u8* arg0, M2C_UNK* arg1, s32 arg2)
{
	M2C_UNK* temp_r27;
	M2C_UNK* temp_r28;
	M2C_UNK* temp_r3;
	M2C_UNK* temp_r3_2;
	M2C_UNK* var_r29;
	f32 temp_f1;
	s32* temp_r3_3;
	s32 temp_r4;
	u8* temp_r6;
	u8* temp_r6_2;
	s32 var_r19;
	s32 var_r19_2;
	s32 var_r19_3;
	s32 var_r20;
	s32 var_r20_2;
	s32 var_r20_3;
	s32 var_r20_4;
	s32 var_r24_2;
	s32 var_r25;
	s32 var_r26;
	s32 var_r26_2;
	s32 var_r26_3;
	s32 var_r7;
	s32 var_r8;
	u32 (*temp_r12)(u8*, M2C_UNK*, s32);
	u32 (*temp_r12_2)(M2C_UNK*, M2C_UNK*, s32);
	u32 (*temp_r12_3)(M2C_UNK*, M2C_UNK*, s32);
	u32 (*temp_r12_4)(u8*, M2C_UNK*, s32);
	u32 (*temp_r12_5)(u8*, M2C_UNK*, s32);
	u8* temp_r30;
	u8* temp_r31;
	u8* temp_r3_4;
	u8* var_r24;

	temp_r31 = M2C_FIELD(arg1, u8**, 0xC);
	temp_r30 = M2C_FIELD(arg1, u8**, 0x18);
	if (M2C_FIELD(arg1, s32*, 4) & 2) {
		fn_80234058(arg1);
		var_r25 = 0;
		if (M2C_FIELD(arg1, s32*, 4) & 4) {
			var_r24 = (u8*)arg1 + M2C_FIELD(lbl_8042AC68, s32*, 0xA8);
			if ((u32)M2C_FIELD(var_r24, u32*, 0x18) == 0U) {
				fn_802358B8(arg1);
			}
			if ((u32)M2C_FIELD(var_r24, u32*, 0x18) == 0U) {
				return NULL;
			}
			goto block_7;
		}
		var_r24 = NULL;
	block_7:
		if (M2C_FIELD(arg1, s32*, 4) & 0x10) {
			var_r25 = 2;
			var_r19 = 0;
			var_r26 = 0;
		loop_13:
			if (var_r19 >= (s32)M2C_FIELD(temp_r31, s32*, 0x14)) {
				goto block_14;
			}
			temp_r12 = (u32 (*)(u8*, M2C_UNK*, s32))
			    * (u32*)((u8*)M2C_FIELD(temp_r31, u8**, 0x18) + var_r26 + 4);
			if ((temp_r12 != NULL) && ((M2C_UNK*)temp_r12(arg0, arg1, arg2) != arg1)) {
				return NULL;
			}
			var_r26 += 0x2C;
			var_r19 += 1;
			goto loop_13;
		}
	block_14:
		if (M2C_FIELD(arg0, s32*, 0x4C) & 2) {
			fn_8014F854(arg0);
		}
		var_r26_2                   = 0;
		M2C_FIELD(arg1, f32*, 0x24) = (f32)lbl_80430248;
		if (((M2C_UNK*)M2C_FIELD(arg1, M2C_UNK**, 0x20) != NULL)
		    && (M2C_FIELD(arg1, s32*, 4) & 0x20)) {
			if (var_r24 != NULL) {
				fn_802356F0(var_r24);
				var_r25 |= 1;
				M2C_FIELD(var_r24, s32*, 8) = 0;
			}
			temp_r28                         = M2C_FIELD(arg1, M2C_UNK**, 0x20);
			M2C_FIELD(arg1, M2C_UNK**, 0x20) = NULL;
			var_r29                          = temp_r28;
		loop_21:
			M2C_FIELD(var_r29, s32*, 0x10) = -1;
			temp_r27                       = M2C_FIELD(var_r29, M2C_UNK**, 0);
			if ((s32)M2C_FIELD(var_r29, s32*, 8) <= 0) {
				var_r19_2 = 0;
				var_r20   = 0;
			loop_27:
				if (var_r19_2 >= (s32)M2C_FIELD(temp_r30, s32*, 0x14)) {
					temp_r3 = M2C_FIELD(arg1, M2C_UNK**, 0x1C);
					if (temp_r3 == NULL) {
						M2C_FIELD(var_r29, M2C_UNK**, 0) = var_r29;
					} else {
						M2C_FIELD(var_r29, M2C_UNK**, 0) = temp_r3;
						*temp_r3                         = (M2C_UNK)var_r29;
					}
					M2C_FIELD(arg1, M2C_UNK**, 0x1C) = var_r29;
					goto block_42;
				}
				temp_r12_2 = (u32 (*)(M2C_UNK*, M2C_UNK*, s32))
				    * (u32*)((u8*)M2C_FIELD(temp_r30, u8**, 0x18) + var_r20 + 0xC);
				if ((temp_r12_2 != NULL)
				    && ((M2C_UNK*)temp_r12_2(arg1, var_r29, arg2) != var_r29)) {
					return NULL;
				}
				var_r20 += 0x1C;
				var_r19_2 += 1;
				goto loop_27;
			}
			var_r19_3 = 0;
			var_r20_2 = 0;
		loop_37:
			if (var_r19_3 >= (s32)M2C_FIELD(temp_r30, s32*, 0x14)) {
				temp_r3_2 = M2C_FIELD(arg1, M2C_UNK**, 0x20);
				if (temp_r3_2 == NULL) {
					M2C_FIELD(var_r29, M2C_UNK**, 0) = var_r29;
				} else {
					M2C_FIELD(var_r29, M2C_UNK**, 0) = temp_r3_2;
					*temp_r3_2                       = (M2C_UNK)var_r29;
				}
				M2C_FIELD(arg1, M2C_UNK**, 0x20) = var_r29;
				var_r26_2 += M2C_FIELD(var_r29, s32*, 8);
			block_42:
				var_r29 = temp_r27;
				if (temp_r27 == temp_r28) {
					goto block_45;
				}
				goto loop_21;
			}
			temp_r12_3 = (u32 (*)(M2C_UNK*, M2C_UNK*, s32))
			    * (u32*)((u8*)M2C_FIELD(temp_r30, u8**, 0x18) + var_r20_2);
			if ((temp_r12_3 != NULL) && ((M2C_UNK*)temp_r12_3(arg1, var_r29, arg2) != var_r29)) {
				return NULL;
			}
			var_r20_2 += 0x1C;
			var_r19_3 += 1;
			goto loop_37;
		}
		var_r26_2 = M2C_FIELD(arg1, s32*, 0x10);
	block_45:
		M2C_FIELD(arg1, s32*, 0x10) = var_r26_2;
		if ((var_r24 != NULL) && !(var_r25 & 1)) {
			fn_802356F0(var_r24);
			temp_r3_3 = fn_801FD214(M2C_FIELD(var_r24, u8**, 0x18));
			var_r8    = 0;
			var_r7    = 0;
		loop_49:
			if (var_r8 < (s32)*temp_r3_3) {
				var_r8 += 1;
				temp_r6                   = (u8*)M2C_FIELD(var_r24, s32*, 0x1C);
				*(s32*)(temp_r6 + var_r7) = *(s32*)(temp_r6 + var_r7)
				    + (M2C_FIELD(var_r24, s32*, 8)
				        * *(s32*)((u8*)M2C_FIELD(var_r24, s32*, 0x24) + var_r7));
				temp_r6_2                   = (u8*)M2C_FIELD(var_r24, s32*, 0x20);
				*(s32*)(temp_r6_2 + var_r7) = *(s32*)(temp_r6_2 + var_r7)
				    + (M2C_FIELD(var_r24, s32*, 8)
				        * *(s32*)((u8*)M2C_FIELD(var_r24, s32*, 0x24) + var_r7));
				var_r7 += 4;
				goto loop_49;
			}
			var_r25 |= 1;
		}
		if (M2C_FIELD(arg1, s32*, 4) & 8) {
			var_r26_3 = 0;
			var_r25 |= 2;
			var_r20_3 = 0;
		loop_57:
			if (var_r26_3 >= (s32)M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), s32*, 0x14)) {
				goto block_58;
			}
			temp_r12_4 = (u32 (*)(u8*, M2C_UNK*, s32))
			    * (u32*)((u8*)M2C_FIELD(temp_r31, u8**, 0x18) + var_r20_3);
			if ((temp_r12_4 != NULL) && ((M2C_UNK*)temp_r12_4(arg0, arg1, arg2) != arg1)) {
				return NULL;
			}
			var_r20_3 += 0x2C;
			var_r26_3 += 1;
			goto loop_57;
		}
	block_58:
		if ((var_r24 != NULL) && (var_r25 & 1)) {
			temp_r3_4 = *(u8**)(M2C_FIELD(var_r24, u8**, 0x18) + lbl_8042CF48);
			M2C_FIELD(temp_r3_4, s32*, 0x40) = (s32)(M2C_FIELD(temp_r3_4, s32*, 0x40) | 0x800000);
			temp_r4                          = M2C_FIELD(var_r24, s32*, 8);
			M2C_FIELD(*(u8**)(M2C_FIELD(var_r24, u8**, 0x18) + lbl_8042CF48), s32*, 4) = temp_r4;
			fn_801FD3B4(M2C_FIELD(var_r24, u8**, 0x18), temp_r4);
		}
		if (M2C_FIELD(arg1, s32*, 4) & 0x10) {
			var_r24_2 = 0;
			var_r20_4 = 0;
		loop_67:
			if (var_r24_2 >= (s32)M2C_FIELD(temp_r31, s32*, 0x14)) {
				goto block_68;
			}
			temp_r12_5 = (u32 (*)(u8*, M2C_UNK*, s32))
			    * (u32*)((u8*)M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u8**, 0x18) + var_r20_4 + 8);
			if ((temp_r12_5 != NULL) && ((M2C_UNK*)temp_r12_5(arg0, arg1, arg2) != arg1)) {
				return NULL;
			}
			var_r20_4 += 0x2C;
			var_r24_2 += 1;
			goto loop_67;
		}
	block_68:
		if (M2C_FIELD(arg1, f32*, 0x24) > lbl_80430248) {
			M2C_FIELD(arg1, f32*, 0x24) = fn_801991F4();
		}
		temp_f1 = M2C_FIELD(arg1, f32*, 0x24);
		if (temp_f1 > M2C_FIELD(arg0, f32*, 0x28)) {
			M2C_FIELD(arg0, f32*, 0x28) = temp_f1;
		}
		goto block_72;
	}
block_72:
	return arg1;
}

M2C_UNK* fn_80233714(s32 arg0, M2C_UNK* arg1, s32* arg2)
{
	M2C_UNK** temp_r3;
	M2C_UNK* temp_r23;
	M2C_UNK* var_r24;
	s32 var_r25;
	s32 var_r25_2;
	s32 var_r26;
	s32 var_r26_2;
	s32 var_r26_3;
	s32 var_r30;
	u32 (*temp_r12)(s32, M2C_UNK*, s32*);
	u32 (*temp_r12_2)(M2C_UNK*, M2C_UNK*, s32*);
	u32 (*temp_r12_3)(s32, M2C_UNK*, s32*);
	u8* temp_r30;
	u8* temp_r31;

	temp_r31 = M2C_FIELD(arg1, u8**, 0xC);
	temp_r30 = M2C_FIELD(arg1, u8**, 0x18);
	if (M2C_FIELD(arg1, s32*, 4) & 2) {
		fn_80234058(arg1);
		if (M2C_FIELD(arg1, s32*, 4) & 0x40) {
			var_r25 = 0;
			var_r26 = 0;
		loop_7:
			if (var_r25 >= (s32)M2C_FIELD(temp_r31, s32*, 0x14)) {
				goto block_8;
			}
			temp_r12 = (u32 (*)(s32, M2C_UNK*, s32*))
			    * (u32*)((u8*)M2C_FIELD(temp_r31, u8**, 0x18) + var_r26 + 0xC);
			if ((temp_r12 != NULL) && ((M2C_UNK*)temp_r12(arg0, arg1, arg2) != arg1)) {
				return NULL;
			}
			var_r26 += 0x2C;
			var_r25 += 1;
			goto loop_7;
		}
	block_8:
		temp_r3 = M2C_FIELD(arg1, M2C_UNK***, 0x20);
		if ((temp_r3 != NULL) && (M2C_FIELD(arg1, s32*, 4) & 0x80)) {
			temp_r23 = *temp_r3;
			var_r24  = temp_r23;
		loop_11:
			var_r25_2 = 0;
			var_r26_2 = 0;
		loop_16:
			if (var_r25_2 >= (s32)M2C_FIELD(temp_r31, s32*, 0x14)) {
				var_r24 = (M2C_UNK*)*var_r24;
				if (var_r24 == temp_r23) {
					goto block_18;
				}
				goto loop_11;
			}
			temp_r12_2 = (u32 (*)(M2C_UNK*, M2C_UNK*, s32*))
			    * (u32*)((u8*)M2C_FIELD(temp_r30, u8**, 0x18) + var_r26_2 + 4);
			if ((temp_r12_2 != NULL) && ((M2C_UNK*)temp_r12_2(arg1, var_r24, arg2) != var_r24)) {
				return NULL;
			}
			var_r26_2 += 0x1C;
			var_r25_2 += 1;
			goto loop_16;
		}
	block_18:
		if (M2C_FIELD(arg1, s32*, 4) & 0x40) {
			var_r30   = 0;
			var_r26_3 = 0;
		loop_24:
			if (var_r30 >= (s32)M2C_FIELD(temp_r31, s32*, 0x14)) {
				goto block_25;
			}
			temp_r12_3 = (u32 (*)(s32, M2C_UNK*, s32*))
			    * (u32*)((u8*)M2C_FIELD(temp_r31, u8**, 0x18) + var_r26_3 + 0x10);
			if ((temp_r12_3 != NULL) && ((M2C_UNK*)temp_r12_3(arg0, arg1, arg2) != arg1)) {
				return NULL;
			}
			var_r26_3 += 0x2C;
			var_r30 += 1;
			goto loop_24;
		}
		goto block_25;
	}
block_25:
	return arg1;
}

#pragma dont_inline on
u8* fn_802338B8(u8* arg0, s32* arg1)
{
	s32 sp20;
	u8** sp1C;
	s32 sp18;
	s32 sp14;
	s32 sp10;
	s32 spC;
	s32 sp8;
	M2C_UNK* temp_r18;
	M2C_UNK* var_r19;
	M2C_UNK* var_r19_2;
	M2C_UNK* var_r28;
	M2C_UNK* var_r29;
	s32 temp_r3;
	s32 temp_r4;
	s32 temp_r5;
	s32 temp_r5_2;
	s32 var_r18_2;
	s32 var_r18_3;
	s32 var_r19_3;
	s32 var_r19_4;
	s32 var_r19_5;
	s32 var_r20_2;
	s32 var_r21;
	u32 (*temp_r12)(M2C_UNK, u8*, M2C_UNK);
	u32 (*temp_r12_2)(M2C_UNK, u8*, M2C_UNK);
	u32 (*temp_r12_3)(u8*, u8*, s32*);
	u8*** var_r27;
	u8** temp_r3_2;
	u8* temp_r20;
	u8* temp_r23;
	u8* temp_r26;
	u8* var_r18;
	u8* var_r20;
	u8* var_r22;
	u8* var_r24;

	fn_80193884(arg1, &sp18, 4);
	fn_80193884(arg1, &spC, 4);
	fn_80193884(arg1, &sp14, 4);
	fn_80193884(arg1, &sp10, 4);
	fn_80193884(arg1, &sp8, 4);
	if (sp8 != 0) {
		if (fn_80192F38(arg1, 0x25, 0, 0) == 0) {
			return NULL;
		}
		var_r18 = fn_8023521C(arg1);
		if (fn_80192F38(arg1, 0x25, 0, 0) == 0) {
			return NULL;
		}
		var_r20 = fn_8023521C(arg1);
		if (fn_80192F38(arg1, 0x25, 0, 0) == 0) {
			return NULL;
		}
		var_r28 = fn_80234804(arg1);
		if (fn_80192F38(arg1, 0x25, 0, 0) == 0) {
			return NULL;
		}
		var_r29 = fn_8023271C(arg1);
		goto block_11;
	}
	var_r18 = NULL;
	var_r20 = NULL;
	var_r29 = fn_80232604(sp18);
	var_r28 = fn_802346EC(sp14);
block_11:
	if (var_r20 != NULL) {
		var_r19 = fn_80232648(var_r20);
		if (var_r19 != var_r29) {
			if (var_r19 == NULL) {
				var_r19 = fn_802321EC();
				fn_802324E0((u8*)var_r19, (u8*)var_r20);
				temp_r5                        = M2C_FIELD(var_r29, s32*, 4);
				M2C_FIELD(var_r19, s32*, 4)    = temp_r5;
				M2C_FIELD(var_r19, s32*, 0x14) = 0;
				M2C_FIELD(var_r19, s32*, 0x18) = 0;
				M2C_FIELD(lbl_8042AC68, M2C_UNK(**)(M2C_UNK*, M2C_UNK*, s32), 0x6C)(
				    var_r19, lbl_8042AC68, temp_r5);
			} else {
				M2C_FIELD(var_r19, s32*, 8) = (s32)(M2C_FIELD(var_r19, s32*, 8) + 1);
			}
			fn_80232288(var_r29);
			var_r29 = var_r19;
		}
		var_r19_2 = fn_80234730(var_r18);
		if (var_r19_2 != var_r28) {
			if (var_r19_2 == NULL) {
				var_r19_2 = fn_80234338();
				fn_802345C8(var_r18);
				temp_r5_2                        = M2C_FIELD(var_r28, s32*, 4);
				M2C_FIELD(var_r19_2, s32*, 4)    = temp_r5_2;
				M2C_FIELD(var_r19_2, s32*, 0x14) = 0;
				M2C_FIELD(var_r19_2, s32*, 0x18) = 0;
				M2C_FIELD(lbl_8042AC68, M2C_UNK(**)(M2C_UNK*, M2C_UNK*, s32), 0x70)(
				    var_r19_2, lbl_8042AC68, temp_r5_2);
			} else {
				M2C_FIELD(var_r19_2, s32*, 8) = (s32)(M2C_FIELD(var_r19_2, s32*, 8) + 1);
			}
			fn_802343C4(var_r28);
			var_r28 = var_r19_2;
		}
	}
	temp_r4 = M2C_FIELD(var_r29, s32*, 0xC);
	var_r24 = M2C_FIELD(lbl_8042C9A4, u8 * (**)(s32, s32), 0x134)(temp_r4 + 0x28, temp_r4);
	if (var_r24 != NULL) {
		M2C_FIELD(var_r29, s32*, 8)        = (s32)(M2C_FIELD(var_r29, s32*, 8) + 1);
		M2C_FIELD(var_r24, M2C_UNK**, 0xC) = var_r29;
		M2C_FIELD(var_r24, u8**, 0)        = var_r24;
		M2C_FIELD(var_r24, s32*, 4)        = 0;
		M2C_FIELD(var_r24, s32*, 8)        = 0;
		M2C_FIELD(var_r24, s32*, 0x10)     = 0;
		M2C_FIELD(var_r24, s32*, 0x14)     = 0;
		M2C_FIELD(var_r24, s32*, 0x18)     = 0;
		M2C_FIELD(var_r24, s32*, 0x1C)     = 0;
		M2C_FIELD(var_r24, s32*, 0x20)     = 0;
		memset((M2C_UNK*)(var_r24 + 0x28), 0,
		    M2C_FIELD(M2C_FIELD(var_r24, M2C_UNK**, 0xC), s32*, 0xC) - 0x28);
		temp_r3 = fn_8023506C(M2C_FIELD(M2C_FIELD(var_r24, M2C_UNK**, 0xC), u8**, 0x10), 6);
		if (temp_r3 >= 0) {
			fn_802355D4(var_r24 + temp_r3);
		}
		var_r19_3 = 0;
		temp_r18  = M2C_FIELD(var_r24, M2C_UNK**, 0xC);
		var_r20_2 = 0;
	loop_30:
		if (var_r19_3 < (s32)M2C_FIELD(temp_r18, s32*, 0x14)) {
			temp_r12 = (u32 (*)(M2C_UNK, u8*, M2C_UNK))
			    * (u32*)((u8*)M2C_FIELD(temp_r18, u8**, 0x18) + var_r20_2 + 0x14);
			if ((temp_r12 != NULL) && ((u8*)temp_r12(0, var_r24, 0) != var_r24)) {
				var_r24 = NULL;
			} else {
				var_r20_2 += 0x2C;
				var_r19_3 += 1;
				goto loop_30;
			}
		}
	}
	if (var_r24 == NULL) {
		return NULL;
	}
	M2C_FIELD(var_r24, s32*, 4) = (s32)(spC | 0x200);
	if ((M2C_UNK*)M2C_FIELD(var_r24, M2C_UNK**, 0x18) != NULL) {
		var_r27 = &sp1C;
		var_r21 = 0;
		sp1C    = M2C_FIELD(var_r24, u8***, 0x20);
		sp20    = M2C_FIELD(var_r24, s32*, 0x1C);
	loop_35:
		temp_r3_2 = *var_r27;
		if (temp_r3_2 != NULL) {
			temp_r26 = *temp_r3_2;
			var_r22  = temp_r26;
		loop_37:
			temp_r23 = M2C_FIELD(var_r22, u8**, 0);
			if (var_r21 == 0) {
				var_r19_4 = 0;
				if (var_r22 != NULL) {
					temp_r20  = M2C_FIELD(var_r22, u8**, 4);
					var_r18_2 = 0;
				loop_43:
					if (var_r19_4 >= (s32)M2C_FIELD(temp_r20, s32*, 0x14)) {
						M2C_FIELD(var_r22, s32*, 8)    = 0;
						M2C_FIELD(var_r22, s32*, 0x10) = 0;
						M2C_FIELD(var_r22, u8**, 0)    = NULL;
					} else {
						temp_r12_2 = (u32 (*)(M2C_UNK, u8*, M2C_UNK))
						    * (u32*)((u8*)M2C_FIELD(temp_r20, u8**, 0x18) + var_r18_2 + 0xC);
						if ((temp_r12_2 == NULL) || ((u8*)temp_r12_2(0, var_r22, 0) == var_r22)) {
							var_r18_2 += 0x1C;
							var_r19_4 += 1;
							goto loop_43;
						}
					}
					M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(
					    var_r22, lbl_8042C9A4);
					var_r19_4 = 1;
				}
				if (var_r19_4 == 0) {

				} else {
					goto block_49;
				}
			} else {
				M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(var_r22, lbl_8042C9A4);
			block_49:
				var_r22 = temp_r23;
				if (temp_r23 == temp_r26) {
					goto block_50;
				}
				goto loop_37;
			}
		} else {
		block_50:
			var_r21 += 1;
			var_r27 += 4;
			if (var_r21 >= 2) {
				M2C_FIELD(var_r24, u8***, 0x20) = NULL;
				M2C_FIELD(var_r24, s32*, 0x1C)  = 0;
				M2C_FIELD(var_r24, s32*, 0x10)  = 0;
			} else {
				goto loop_35;
			}
		}
		fn_802343C4(M2C_FIELD(var_r24, M2C_UNK**, 0x18));
	}
	M2C_FIELD(var_r24, M2C_UNK**, 0x18) = var_r28;
	var_r19_5                           = 0;
	var_r18_3                           = 0;
	M2C_FIELD(var_r24, s32*, 0x14)      = sp10;
	M2C_FIELD(var_r28, s32*, 8)         = (s32)(M2C_FIELD(var_r28, s32*, 8) + 1);
loop_58:
	if (var_r19_5 >= (s32)M2C_FIELD(var_r29, s32*, 0x14)) {
		fn_80239738(arg0, var_r24);
		if (sp8 != 0) {
			fn_80234EA0(M2C_FIELD(var_r29, u8**, 0x10));
			fn_80234EA0(M2C_FIELD(var_r28, u8**, 0x10));
			fn_80232288(var_r29);
			fn_802343C4(var_r28);
		}
		return var_r24;
	}
	temp_r12_3 = (u32 (*)(u8*, u8*, s32*))
	    * (u32*)((u8*)M2C_FIELD(var_r29, u8**, 0x18) + var_r18_3 + 0x1C);
	if ((temp_r12_3 != NULL) && ((u8*)temp_r12_3(arg0, var_r24, arg1) != var_r24)) {
		return NULL;
	}
	var_r18_3 += 0x2C;
	var_r19_5 += 1;
	goto loop_58;
}
#pragma dont_inline reset

#pragma dont_inline on
u8* fn_80233DF8(s32 arg0, u8* arg1, s32* arg2)
{
	s32 spC;
	s32 sp8;
	s32 var_r30;
	s32 var_r31;
	u32 (*temp_r12)(s32, u8*, s32*);
	u8* temp_r29;
	u8* temp_r31;

	temp_r29 = M2C_FIELD(arg1, u8**, 0xC);
	temp_r31 = M2C_FIELD(arg1, u8**, 0x18);
	fn_80193474(arg2, temp_r29 + 4, 4);
	fn_80193474(arg2, arg1 + 4, 4);
	fn_80193474(arg2, temp_r31 + 4, 4);
	fn_80193474(arg2, arg1 + 0x14, 4);
	if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0x7C) == 1) {
		spC = 1;
		fn_80193474(arg2, &spC, 4);
		fn_802354D4(M2C_FIELD(temp_r31, u8**, 0x10), arg2);
		fn_802354D4(M2C_FIELD(temp_r29, u8**, 0x10), arg2);
		fn_80234774(temp_r31, arg2);
		fn_8023268C(temp_r29, arg2);
	} else {
		sp8 = 0;
		fn_80193474(arg2, &sp8, 4);
	}
	var_r30 = 0;
	var_r31 = 0;
loop_8:
	if (var_r30 >= (s32)M2C_FIELD(temp_r29, s32*, 0x14)) {
		return arg1;
	}
	temp_r12
	    = (u32 (*)(s32, u8*, s32*)) * (u32*)((u8*)M2C_FIELD(temp_r29, u8**, 0x18) + var_r31 + 0x20);
	if ((temp_r12 != NULL) && ((u8*)temp_r12(arg0, arg1, arg2) != arg1)) {
		return NULL;
	}
	var_r31 += 0x2C;
	var_r30 += 1;
	goto loop_8;
}
#pragma dont_inline reset

#pragma dont_inline on
M2C_UNK* fn_80233F50(s32 arg0, M2C_UNK* arg1, s32* arg2)
{
	s32 sp8;
	s32 temp_r29;
	s32 temp_r29_2;
	s32 temp_r29_3;
	s32 var_r29;
	s32 var_r30;
	s32 var_r31;
	u32 (*temp_r12)(s32, M2C_UNK*, s32*);
	u8* temp_r28;
	u8* temp_r30;

	temp_r28 = M2C_FIELD(arg1, u8**, 0xC);
	temp_r30 = M2C_FIELD(arg1, u8**, 0x18);
	var_r29  = 0x14;
	if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0x7C) == 1) {
		var_r29 = fn_80235590(M2C_FIELD(temp_r30, u8**, 0x10)) + 0x14;
		var_r29 += 0xC;
		var_r29 += fn_80235590(M2C_FIELD(temp_r28, u8**, 0x10));
		var_r29 += 0xC;
		var_r29 += fn_80234A30(temp_r30);
		var_r29 += 0xC;
		var_r29 += fn_80232960(temp_r28);
		var_r29 += 0xC;
	}
	for (var_r30 = 0, var_r31 = 0; var_r30 < (s32)M2C_FIELD(temp_r28, s32*, 0x14);
	    var_r31 += 0x2C, var_r30 += 1) {
		temp_r12 = (u32 (*)(s32, M2C_UNK*, s32*))
		    * (u32*)((u8*)M2C_FIELD(temp_r28, u8**, 0x18) + var_r31 + 0x24);
		if (temp_r12 != NULL) {
			if ((M2C_UNK*)temp_r12(arg0, arg1, &sp8) != arg1) {
				return NULL;
			}
			var_r29 += sp8;
		}
	}
	*arg2 += var_r29;
	return arg1;
}
#pragma dont_inline reset

M2C_UNK* fn_80234058(M2C_UNK* arg0)
{
	u8* temp_r3;
	u8* temp_r3_2;

	temp_r3 = M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10);
	if (temp_r3 != (u8*)M2C_FIELD(lbl_8042AC68, u8**, 0x90)) {
		M2C_FIELD(lbl_8042AC68, u8**, 0x90) = temp_r3;
		M2C_FIELD(lbl_8042AC68, s32*, 0x98) = fn_8023506C(temp_r3, 1, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0x9C)
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 2, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xA0)
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 3, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xA4)
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 5, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xA8)
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 6, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xAC)
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 8, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xB0)
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 4, lbl_8042AC68);
	}
	temp_r3_2 = M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10);
	if (temp_r3_2 != (u8*)M2C_FIELD(lbl_8042AC68, u8**, 0x94)) {
		M2C_FIELD(lbl_8042AC68, u8**, 0x94) = temp_r3_2;
		M2C_FIELD(lbl_8042AC68, s32*, 0xB8) = fn_8023506C(temp_r3_2, 0, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xBC)
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 2, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xC0)
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 3, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xC4)
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 5, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xB4)
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 1, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xC8)
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 6, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xCC)
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 7, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xD0)
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 4, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xD8)
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 0, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xDC)
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 2, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xE0)
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 3, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xE4)
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 5, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xD4)
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 1, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xE8)
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 6, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xEC)
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 7, lbl_8042AC68);
		M2C_FIELD(lbl_8042AC68, s32*, 0xF0)
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x10), 4, lbl_8042AC68);
	}
	return arg0;
}

M2C_UNK* fn_80234338(void)
{
	M2C_UNK* temp_r3;
	M2C_UNK* temp_r4;

	temp_r3 = M2C_FIELD(lbl_8042C9A4, M2C_UNK * (**)(M2C_UNK, M2C_UNK*), 0x134)(0x1C, lbl_8042C9A4);
	if (temp_r3 != NULL) {
		memset(temp_r3, 0, 0x1C);
		M2C_FIELD(temp_r3, M2C_UNK**, 0) = temp_r3;
		M2C_FIELD(temp_r3, M2C_UNK**, 4) = temp_r3;
		M2C_FIELD(temp_r3, s32*, 8)      = 1;
		temp_r4                          = M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64);
		if (temp_r4 == NULL) {
			*temp_r3 = (M2C_UNK)temp_r3;
		} else {
			*temp_r3 = *temp_r4;
			*temp_r4 = (M2C_UNK)temp_r3;
		}
		M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64) = temp_r3;
	}
	return temp_r3;
}

s32 fn_802343C4(M2C_UNK* arg0)
{
	M2C_UNK* temp_r0;
	u8* temp_r3;
	M2C_UNK* var_r4;
	M2C_UNK* var_r5;

	M2C_FIELD(arg0, s32*, 8) = (s32)(M2C_FIELD(arg0, s32*, 8) - 1);
	if ((s32)M2C_FIELD(arg0, s32*, 8) > 0) {
		return 1;
	}
	if ((M2C_UNK*)M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64) != NULL) {
		if (((M2C_UNK*)M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64) == arg0)
		    && ((M2C_UNK*)M2C_FIELD(arg0, M2C_UNK**, 0) == arg0)) {
			M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64) = NULL;
		} else {
			temp_r0 = (M2C_UNK*)*M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64);
			var_r5  = M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64);
			var_r4  = temp_r0;
		loop_7:
			if (var_r4 == arg0) {
				*var_r5                       = (M2C_UNK)M2C_FIELD(arg0, M2C_UNK**, 0);
				M2C_FIELD(arg0, M2C_UNK**, 0) = arg0;
			} else {
				var_r5 = var_r4;
				var_r4 = (M2C_UNK*)*var_r4;
				if (var_r4 != temp_r0) {
					goto loop_7;
				}
			}
			if ((M2C_UNK*)M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64) == arg0) {
				M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64) = var_r5;
			}
		}
	}
	if ((u32)M2C_FIELD(arg0, u32*, 0x18) != 0U) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(M2C_UNK*, M2C_UNK*), 0x138)(
		    (M2C_UNK*)M2C_FIELD(arg0, u32*, 0x18), lbl_8042C9A4);
	}
	temp_r3 = M2C_FIELD(arg0, u8**, 0x10);
	if (temp_r3 != NULL) {
		fn_80234EA0(temp_r3);
	}
	memset(arg0, 0, 0x1C);
	M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(M2C_UNK*, M2C_UNK*), 0x138)(arg0, lbl_8042C9A4);
	return 1;
}

u8* fn_802344D8(u8* arg0, s32 arg1, u8* arg2)
{
	s32 temp_r0;
	s32 var_ctr;
	u8* temp_r3;
	u8* var_r31;
	u8* var_r3;
	u8* var_r4;

	var_r31 = NULL;
	temp_r3 = M2C_FIELD(lbl_8042C9A4, u8 * (**)(s32, M2C_UNK*), 0x134)(arg1 * 0x1C, lbl_8042C9A4);
	if (temp_r3 != NULL) {
		var_r3  = arg2;
		var_r4  = temp_r3;
		var_ctr = arg1;
		if (arg1 > 0) {
			do {
				M2C_FIELD(var_r4, s32*, 0)    = (s32)M2C_FIELD(var_r3, s32*, 0);
				M2C_FIELD(var_r4, s32*, 4)    = (s32)M2C_FIELD(var_r3, s32*, 4);
				M2C_FIELD(var_r4, s32*, 8)    = (s32)M2C_FIELD(var_r3, s32*, 8);
				M2C_FIELD(var_r4, s32*, 0xC)  = (s32)M2C_FIELD(var_r3, s32*, 0xC);
				M2C_FIELD(var_r4, s32*, 0x10) = (s32)M2C_FIELD(var_r3, s32*, 0x10);
				M2C_FIELD(var_r4, s32*, 0x14) = (s32)M2C_FIELD(var_r3, s32*, 0x14);
				temp_r0                       = M2C_FIELD(var_r3, s32*, 0x18);
				var_r3 += 0x1C;
				M2C_FIELD(var_r4, s32*, 0x18) = temp_r0;
				var_r4 += 0x1C;
				var_ctr -= 1;
			} while (var_ctr != 0);
		}
		if ((u8*)M2C_FIELD(arg0, u8**, 0x18) != NULL) {
			M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(
			    M2C_FIELD(arg0, u8**, 0x18), lbl_8042C9A4);
		}
		M2C_FIELD(arg0, s32*, 0x14) = arg1;
		var_r31                     = arg0;
		M2C_FIELD(arg0, u8**, 0x18) = temp_r3;
	}
	return var_r31;
}

void fn_802345B4(u8* arg0, s32* arg1, s32* arg2)
{
	*arg1 = M2C_FIELD(arg0, s32*, 0x14);
	*arg2 = M2C_FIELD(arg0, s32*, 0x18);
}

u8* fn_802345C8(u8* arg0, u8* arg1)
{
	s32 temp_r0;
	s32 temp_r3;
	s32 temp_r5;
	s32 var_ctr_2;
	s32 var_r4;
	s32 var_r4_2;
	s32 var_r7;
	s32 var_r8;
	u32 var_ctr;
	u8* temp_r6;

	if ((u8*)M2C_FIELD(arg0, u8**, 0x10) != NULL) {
		fn_80234EA0(M2C_FIELD(arg0, u8**, 0x10));
	}
	var_r8                      = 0;
	M2C_FIELD(arg1, s32*, 0xC)  = (s32)(M2C_FIELD(arg1, s32*, 0xC) + 1);
	M2C_FIELD(arg0, u8**, 0x10) = arg1;
	if (arg1 != NULL) {
		temp_r5 = M2C_FIELD(arg1, s32*, 0x10);
		var_r7  = 0;
		if (temp_r5 > 0) {
			temp_r3 = temp_r5 - 8;
			if (temp_r5 > 8) {
				var_r4  = 0;
				var_ctr = (u32)(temp_r3 + 7) >> 3U;
				if (temp_r3 > 0) {
					do {
						var_r7 += 8;
						temp_r6 = (u8*)M2C_FIELD(arg1, s32*, 0x20) + var_r4;
						var_r4 += 0x20;
						var_r8 = var_r8 + M2C_FIELD(temp_r6, s32*, 0) + M2C_FIELD(temp_r6, s32*, 4)
						    + M2C_FIELD(temp_r6, s32*, 8) + M2C_FIELD(temp_r6, s32*, 0xC)
						    + M2C_FIELD(temp_r6, s32*, 0x10) + M2C_FIELD(temp_r6, s32*, 0x14)
						    + M2C_FIELD(temp_r6, s32*, 0x18) + M2C_FIELD(temp_r6, s32*, 0x1C);
						var_ctr -= 1;
					} while (var_ctr != 0);
				}
			}
			var_r4_2  = var_r7 * 4;
			var_ctr_2 = temp_r5 - var_r7;
			if (var_r7 < temp_r5) {
				do {
					temp_r0 = *(s32*)((u8*)M2C_FIELD(arg1, s32*, 0x20) + var_r4_2);
					var_r4_2 += 4;
					var_r8 += temp_r0;
					var_ctr_2 -= 1;
				} while (var_ctr_2 != 0);
			}
		}
	}
	M2C_FIELD(arg0, s32*, 0xC) = var_r8;
	return arg0;
}

void fn_802346E0(u8* arg0, s32* arg1)
{
	*arg1 = M2C_FIELD(arg0, s32*, 0x10);
}

M2C_UNK* fn_802346EC(s32 arg0)
{
	M2C_UNK* var_r4;
	M2C_UNK* var_r5;
	M2C_UNK* var_r6;

	var_r6 = NULL;
	var_r5 = M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64);
	var_r4 = var_r5;
	if (var_r5 != NULL) {
	loop_1:
		if ((s32)M2C_FIELD(var_r4, s32*, 4) == arg0) {
			var_r6 = var_r4;
		} else {
			var_r4 = M2C_FIELD(var_r4, M2C_UNK**, 0);
			if (var_r4 != var_r5) {
				goto loop_1;
			}
		}
	}
	return var_r6;
}

M2C_UNK* fn_80234730(u8* arg0)
{
	M2C_UNK* var_r4;
	M2C_UNK* var_r5;
	M2C_UNK* var_r6;

	var_r6 = NULL;
	var_r5 = M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64);
	var_r4 = var_r5;
	if (var_r5 != NULL) {
	loop_1:
		if ((u32)M2C_FIELD(var_r4, u32*, 0x10) == (u32)arg0) {
			var_r6 = var_r4;
		} else {
			var_r4 = M2C_FIELD(var_r4, M2C_UNK**, 0);
			if (var_r4 != var_r5) {
				goto loop_1;
			}
		}
	}
	return var_r6;
}

u8* fn_80234774(u8* arg0, s32* arg1)
{
	if (fn_80192ED8(arg1, 0x25, fn_80234A30(), 0x35000, 0xFFFF) == 0U) {
		return NULL;
	}
	fn_80193474(arg1, arg0 + 4, 4);
	fn_80193474(arg1, M2C_FIELD(arg0, s32*, 0x10) + 8, 4);
	return arg0;
}

M2C_UNK* fn_80234804(s32* arg0)
{
	s32 spC;
	s32 sp8;
	M2C_UNK* var_r30;
	M2C_UNK* var_r4;
	M2C_UNK* var_r5;
	s32 temp_r0_2;
	s32 temp_r3;
	s32 temp_r7;
	s32 var_ctr_2;
	s32 var_r4_2;
	s32 var_r5_2;
	s32 var_r6;
	s32 var_r6_2;
	u32 var_ctr;
	u8* temp_r0;
	u8* temp_r31;
	u8* temp_r8;

	fn_80193884(arg0, &sp8, 4);
	fn_80193884(arg0, &spC, 4);
	var_r4 = NULL;
	var_r5 = M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64);
	if ((M2C_UNK*)M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64) != NULL) {
	loop_1:
		if ((s32)M2C_FIELD(var_r5, s32*, 4) == sp8) {
			var_r4 = var_r5;
		} else {
			var_r5 = M2C_FIELD(var_r5, M2C_UNK**, 0);
			if (var_r5 != (M2C_UNK*)M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64)) {
				goto loop_1;
			}
		}
	}
	var_r30 = var_r4;
	if (var_r4 == NULL) {
		var_r30
		    = M2C_FIELD(lbl_8042C9A4, M2C_UNK * (**)(M2C_UNK, M2C_UNK*), 0x134)(0x1C, lbl_8042C9A4);
		if (var_r30 != NULL) {
			memset(var_r30, 0, 0x1C);
			M2C_FIELD(var_r30, M2C_UNK**, 0) = var_r30;
			M2C_FIELD(var_r30, M2C_UNK**, 4) = var_r30;
			M2C_FIELD(var_r30, s32*, 8)      = 1;
			if ((M2C_UNK*)M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64) == NULL) {
				M2C_FIELD(var_r30, M2C_UNK**, 0) = var_r30;
			} else {
				M2C_FIELD(var_r30, M2C_UNK**, 0)         = M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64);
				M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64) = var_r30;
			}
			M2C_FIELD(lbl_8042AC68, M2C_UNK**, 0x64) = var_r30;
		}
		if (var_r30 != NULL) {
			temp_r0  = M2C_FIELD(var_r30, u8**, 0x10);
			temp_r31 = fn_802350D4(spC);
			if (temp_r0 != NULL) {
				fn_80234EA0(temp_r0);
			}
			var_r4_2                       = 0;
			M2C_FIELD(temp_r31, s32*, 0xC) = (s32)(M2C_FIELD(temp_r31, s32*, 0xC) + 1);
			M2C_FIELD(var_r30, u8**, 0x10) = temp_r31;
			if (temp_r31 != NULL) {
				temp_r7  = M2C_FIELD(temp_r31, s32*, 0x10);
				var_r5_2 = 0;
				if (temp_r7 > 0) {
					temp_r3 = temp_r7 - 8;
					if (temp_r7 > 8) {
						var_r6  = 0;
						var_ctr = (u32)(temp_r3 + 7) >> 3U;
						if (temp_r3 > 0) {
							do {
								var_r5_2 += 8;
								temp_r8 = (u8*)M2C_FIELD(temp_r31, s32*, 0x20) + var_r6;
								var_r6 += 0x20;
								var_r4_2 = var_r4_2 + M2C_FIELD(temp_r8, s32*, 0)
								    + M2C_FIELD(temp_r8, s32*, 4) + M2C_FIELD(temp_r8, s32*, 8)
								    + M2C_FIELD(temp_r8, s32*, 0xC) + M2C_FIELD(temp_r8, s32*, 0x10)
								    + M2C_FIELD(temp_r8, s32*, 0x14)
								    + M2C_FIELD(temp_r8, s32*, 0x18)
								    + M2C_FIELD(temp_r8, s32*, 0x1C);
								var_ctr -= 1;
							} while (var_ctr != 0);
						}
					}
					var_r6_2  = var_r5_2 * 4;
					var_ctr_2 = temp_r7 - var_r5_2;
					if (var_r5_2 < temp_r7) {
						do {
							temp_r0_2 = *(s32*)((u8*)M2C_FIELD(temp_r31, s32*, 0x20) + var_r6_2);
							var_r6_2 += 4;
							var_r4_2 += temp_r0_2;
							var_ctr_2 -= 1;
						} while (var_ctr_2 != 0);
					}
				}
			}
			M2C_FIELD(var_r30, s32*, 0xC)    = var_r4_2;
			M2C_FIELD(var_r30, M2C_UNK**, 4) = (M2C_UNK*)sp8;
			M2C_FIELD(var_r30, s32*, 0x14)   = 0;
			M2C_FIELD(var_r30, s32*, 0x18)   = 0;
			M2C_FIELD(lbl_8042AC68, M2C_UNK(**)(M2C_UNK*, M2C_UNK*, s32), 0x70)(
			    var_r30, lbl_8042AC68, sp8);
		}
	} else {
		M2C_FIELD(var_r4, s32*, 8) = (s32)(M2C_FIELD(var_r4, s32*, 8) + 1);
	}
	return var_r30;
}

s32 fn_80234A30(void)
{
	return 8;
}

s32 fn_80234A38(s32 arg0, s32* arg1, s32* arg2)
{
	s32* var_r26;
	s32* var_r31;
	s32* var_r3;
	s32* var_r4;
	s32* var_r4_2;
	s32* var_r5;
	s32* var_r5_2;
	s32* var_r5_3;
	s32* var_r6;
	s32* var_r6_2;
	s32* var_r6_3;
	s32* var_r8;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 temp_r0_4;
	s32 temp_r0_5;
	s32 temp_r0_6;
	s32 temp_r0_7;
	s32 temp_r0_8;
	s32 temp_r28;
	s32 temp_r29;
	s32 temp_r3;
	s32 temp_r3_2;
	s32 temp_r3_4;
	s32 temp_r3_5;
	s32 temp_r6;
	s32 temp_r7;
	s32 temp_r7_2;
	s32 temp_r7_3;
	s32 temp_r8;
	s32 temp_r8_2;
	s32 temp_r8_3;
	s32 temp_r8_4;
	s32 temp_r8_5;
	s32 temp_r9;
	s32 var_ctr_2;
	s32 var_ctr_4;
	s32 var_r0;
	s32 var_r0_2;
	s32 var_r3_2;
	s32 var_r7;
	u32 temp_r3_3;
	u32 var_ctr;
	u32 var_ctr_3;
	u8* var_r25;

	temp_r28 = arg0 * 4;
	var_r31  = arg2;
	if (temp_r28 > (s32)M2C_FIELD(lbl_8042AC68, s32*, 0x84)) {
		var_r3 = M2C_FIELD(lbl_8042C9A4, s32 * (**)(s32*, s32, M2C_UNK*), 0x13C)(
		    M2C_FIELD(lbl_8042AC68, s32**, 0x80), temp_r28, lbl_8042C9A4);
		if (var_r3 == NULL) {
			return 0;
		}
		M2C_FIELD(lbl_8042AC68, s32**, 0x80) = var_r3;
		M2C_FIELD(lbl_8042AC68, s32*, 0x84)  = temp_r28;
		goto block_5;
	}
	var_r3 = M2C_FIELD(lbl_8042AC68, s32**, 0x80);
block_5:
	var_r26 = var_r3;
	if (var_r3 == NULL) {
		return 0;
	}
	var_r0 = 0;
	var_r7 = 0;
	if (arg0 > 0) {
		temp_r9 = arg0 - 8;
		if (arg0 > 8) {
			var_r4  = var_r31;
			var_r5  = var_r3;
			var_r6  = arg1;
			var_ctr = (u32)(temp_r9 + 7) >> 3U;
			if (temp_r9 > 0) {
				do {
					var_r7 += 8;
					M2C_FIELD(var_r5, s32*, 0) = (M2C_FIELD(var_r4, s32*, 0) + 3) & 0xFFFFFFFC;
					M2C_FIELD(var_r5, s32*, 4)
					    = (s32)((M2C_FIELD(var_r4, s32*, 4) + 3) & 0xFFFFFFFC);
					M2C_FIELD(var_r5, s32*, 8)
					    = (s32)((M2C_FIELD(var_r4, s32*, 8) + 3) & 0xFFFFFFFC);
					M2C_FIELD(var_r5, s32*, 0xC)
					    = (s32)((M2C_FIELD(var_r4, s32*, 0xC) + 3) & 0xFFFFFFFC);
					M2C_FIELD(var_r5, s32*, 0x10)
					    = (s32)((M2C_FIELD(var_r4, s32*, 0x10) + 3) & 0xFFFFFFFC);
					M2C_FIELD(var_r5, s32*, 0x14)
					    = (s32)((M2C_FIELD(var_r4, s32*, 0x14) + 3) & 0xFFFFFFFC);
					M2C_FIELD(var_r5, s32*, 0x18)
					    = (s32)((M2C_FIELD(var_r4, s32*, 0x18) + 3) & 0xFFFFFFFC);
					temp_r8 = M2C_FIELD(var_r4, s32*, 0x1C);
					var_r4 += 0x20;
					temp_r0 = var_r0 + M2C_FIELD(var_r6, s32*, 0) + M2C_FIELD(var_r6, s32*, 4)
					    + M2C_FIELD(var_r6, s32*, 8) + M2C_FIELD(var_r6, s32*, 0xC)
					    + M2C_FIELD(var_r6, s32*, 0x10) + M2C_FIELD(var_r6, s32*, 0x14)
					    + M2C_FIELD(var_r6, s32*, 0x18);
					M2C_FIELD(var_r5, s32*, 0x1C) = (s32)((temp_r8 + 3) & 0xFFFFFFFC);
					var_r5 += 0x20;
					temp_r8_2 = M2C_FIELD(var_r6, s32*, 0x1C);
					var_r6 += 0x20;
					var_r0 = temp_r0 + temp_r8_2;
					var_ctr -= 1;
				} while (var_ctr != 0);
			}
		}
		temp_r8_3 = var_r7 * 4;
		var_r5_2  = var_r31 + temp_r8_3;
		var_r6_2  = var_r3 + temp_r8_3;
		var_r8    = arg1 + temp_r8_3;
		var_ctr_2 = arg0 - var_r7;
		if (var_r7 < arg0) {
			do {
				temp_r3 = *var_r5_2;
				var_r5_2 += 4;
				*var_r6_2 = (temp_r3 + 3) & 0xFFFFFFFC;
				var_r6_2 += 4;
				temp_r3_2 = *var_r8;
				var_r8 += 4;
				var_r0 += temp_r3_2;
				var_ctr_2 -= 1;
			} while (var_ctr_2 != 0);
		}
	}
	temp_r7   = arg0 + 1;
	temp_r6   = var_r0 >> 0xA;
	temp_r8_4 = temp_r7 * 0x10;
	temp_r29  = temp_r7 * 4;
	var_r25   = fn_80235118(arg0, arg1, var_r31, temp_r6, temp_r7, temp_r8_4);
	if (var_r25 == NULL) {
		temp_r3_3 = M2C_FIELD(lbl_8042C9A4, u32(**)(s32, M2C_UNK*), 0x134)(
		    temp_r8_4 + 0x2B, lbl_8042C9A4);
		if (temp_r3_3 != 0U) {
			var_r25                         = (u8*)((temp_r3_3 + 3) & 0xFFFFFFFC);
			M2C_FIELD(var_r25, u32*, 0)     = temp_r3_3;
			M2C_FIELD(var_r25, s32*, 0xC)   = 1;
			M2C_FIELD(var_r25, s32**, 0x18) = (s32*)(var_r25 + 0x28);
			M2C_FIELD(var_r25, s32**, 0x1C) = (s32*)(M2C_FIELD(var_r25, s32**, 0x18) + temp_r29);
			M2C_FIELD(var_r25, s32**, 0x20) = (s32*)(M2C_FIELD(var_r25, s32**, 0x1C) + temp_r29);
			M2C_FIELD(var_r25, s32**, 0x24) = (s32*)(M2C_FIELD(var_r25, s32**, 0x20) + temp_r29);
			memcpy(M2C_FIELD(var_r25, s32**, 0x18), arg1, temp_r28, 1);
			var_r5_3 = M2C_FIELD(var_r25, s32**, 0x1C);
			var_r4_2 = M2C_FIELD(var_r25, s32**, 0x20);
			var_r0_2 = 0;
			var_r6_3 = M2C_FIELD(var_r25, s32**, 0x24);
			var_r3_2 = 0;
			if (arg0 > 0) {
				temp_r8_5 = arg0 - 8;
				if (arg0 > 8) {
					var_ctr_3 = (u32)(temp_r8_5 + 7) >> 3U;
					if (temp_r8_5 > 0) {
						do {
							M2C_FIELD(var_r5_3, s32*, 0) = var_r0_2;
							var_r3_2 += 8;
							M2C_FIELD(var_r6_3, s32*, 0) = M2C_FIELD(var_r31, s32*, 0);
							M2C_FIELD(var_r4_2, s32*, 0) = M2C_FIELD(var_r26, s32*, 0);
							temp_r0_2                    = var_r0_2 + M2C_FIELD(var_r26, s32*, 0);
							M2C_FIELD(var_r5_3, s32*, 4) = temp_r0_2;
							M2C_FIELD(var_r6_3, s32*, 4) = (s32)M2C_FIELD(var_r31, s32*, 4);
							M2C_FIELD(var_r4_2, s32*, 4) = (s32)M2C_FIELD(var_r26, s32*, 4);
							temp_r0_3                    = temp_r0_2 + M2C_FIELD(var_r26, s32*, 4);
							M2C_FIELD(var_r5_3, s32*, 8) = temp_r0_3;
							M2C_FIELD(var_r6_3, s32*, 8) = (s32)M2C_FIELD(var_r31, s32*, 8);
							M2C_FIELD(var_r4_2, s32*, 8) = (s32)M2C_FIELD(var_r26, s32*, 8);
							temp_r0_4                    = temp_r0_3 + M2C_FIELD(var_r26, s32*, 8);
							M2C_FIELD(var_r5_3, s32*, 0xC) = temp_r0_4;
							M2C_FIELD(var_r6_3, s32*, 0xC) = (s32)M2C_FIELD(var_r31, s32*, 0xC);
							M2C_FIELD(var_r4_2, s32*, 0xC) = (s32)M2C_FIELD(var_r26, s32*, 0xC);
							temp_r0_5 = temp_r0_4 + M2C_FIELD(var_r26, s32*, 0xC);
							M2C_FIELD(var_r5_3, s32*, 0x10) = temp_r0_5;
							M2C_FIELD(var_r6_3, s32*, 0x10) = (s32)M2C_FIELD(var_r31, s32*, 0x10);
							M2C_FIELD(var_r4_2, s32*, 0x10) = (s32)M2C_FIELD(var_r26, s32*, 0x10);
							temp_r0_6 = temp_r0_5 + M2C_FIELD(var_r26, s32*, 0x10);
							M2C_FIELD(var_r5_3, s32*, 0x14) = temp_r0_6;
							M2C_FIELD(var_r6_3, s32*, 0x14) = (s32)M2C_FIELD(var_r31, s32*, 0x14);
							M2C_FIELD(var_r4_2, s32*, 0x14) = (s32)M2C_FIELD(var_r26, s32*, 0x14);
							temp_r0_7 = temp_r0_6 + M2C_FIELD(var_r26, s32*, 0x14);
							M2C_FIELD(var_r5_3, s32*, 0x18) = temp_r0_7;
							M2C_FIELD(var_r6_3, s32*, 0x18) = (s32)M2C_FIELD(var_r31, s32*, 0x18);
							M2C_FIELD(var_r4_2, s32*, 0x18) = (s32)M2C_FIELD(var_r26, s32*, 0x18);
							temp_r0_8 = temp_r0_7 + M2C_FIELD(var_r26, s32*, 0x18);
							M2C_FIELD(var_r5_3, s32*, 0x1C) = temp_r0_8;
							var_r5_3 += 0x20;
							temp_r7_2 = M2C_FIELD(var_r31, s32*, 0x1C);
							var_r31 += 0x20;
							M2C_FIELD(var_r6_3, s32*, 0x1C) = temp_r7_2;
							var_r6_3 += 0x20;
							M2C_FIELD(var_r4_2, s32*, 0x1C) = (s32)M2C_FIELD(var_r26, s32*, 0x1C);
							var_r4_2 += 0x20;
							temp_r7_3 = M2C_FIELD(var_r26, s32*, 0x1C);
							var_r26 += 0x20;
							var_r0_2 = temp_r0_8 + temp_r7_3;
							var_ctr_3 -= 1;
						} while (var_ctr_3 != 0);
					}
				}
				var_ctr_4 = arg0 - var_r3_2;
				if (var_r3_2 < arg0) {
					do {
						*var_r5_3 = var_r0_2;
						var_r5_3 += 4;
						temp_r3_4 = *var_r31;
						var_r31 += 4;
						*var_r6_3 = temp_r3_4;
						var_r6_3 += 4;
						*var_r4_2 = *var_r26;
						var_r4_2 += 4;
						temp_r3_5 = *var_r26;
						var_r26 += 4;
						var_r0_2 += temp_r3_5;
						var_ctr_4 -= 1;
					} while (var_ctr_4 != 0);
				}
			}
			*var_r5_3                      = var_r0_2;
			M2C_FIELD(var_r25, s32*, 0x10) = arg0;
			M2C_FIELD(var_r25, u8**, 4)    = var_r25;
			M2C_FIELD(var_r25, s32*, 8)
			    = (s32)(temp_r6 | ((var_r0 << 0xA) | ((temp_r7 * 0x10) & 0xFFF0)));
			if ((u8*)M2C_FIELD(lbl_8042AC68, u8**, 0x68) == NULL) {
				M2C_FIELD(var_r25, u8**, 4) = var_r25;
			} else {
				M2C_FIELD(var_r25, u8**, 4)
				    = (u8*)M2C_FIELD(M2C_FIELD(lbl_8042AC68, u8**, 0x68), u8**, 4);
				M2C_FIELD(M2C_FIELD(lbl_8042AC68, u8**, 0x68), u8**, 4) = var_r25;
			}
			M2C_FIELD(lbl_8042AC68, u8**, 0x68) = var_r25;
		}
	} else {
		M2C_FIELD(var_r25, s32*, 0xC) = (s32)(M2C_FIELD(var_r25, s32*, 0xC) + 1);
	}
	return (s32)var_r25;
}

s32 fn_80234EA0(u8* arg0)
{
	u8* temp_r0;
	u8* var_r4;
	u8* var_r5;

	if (arg0 == NULL) {
		return 0;
	}
	M2C_FIELD(arg0, s32*, 0xC) = (s32)(M2C_FIELD(arg0, s32*, 0xC) - 1);
	if ((s32)M2C_FIELD(arg0, s32*, 0xC) > 0) {
		return 1;
	}
	if ((u8*)M2C_FIELD(lbl_8042AC68, u8**, 0x68) != NULL) {
		if (((u8*)M2C_FIELD(lbl_8042AC68, u8**, 0x68) == arg0)
		    && ((u8*)M2C_FIELD(arg0, u8**, 4) == arg0)) {
			M2C_FIELD(lbl_8042AC68, u8**, 0x68) = NULL;
		} else {
			temp_r0 = M2C_FIELD(M2C_FIELD(lbl_8042AC68, u8**, 0x68), u8**, 4);
			var_r5  = M2C_FIELD(lbl_8042AC68, u8**, 0x68);
			var_r4  = temp_r0;
		loop_9:
			if (var_r4 == arg0) {
				M2C_FIELD(var_r5, u8**, 4) = (u8*)M2C_FIELD(arg0, u8**, 4);
				M2C_FIELD(arg0, u8**, 4)   = arg0;
			} else {
				var_r5 = var_r4;
				var_r4 = M2C_FIELD(var_r4, u8**, 4);
				if (var_r4 != temp_r0) {
					goto loop_9;
				}
			}
			if ((u8*)M2C_FIELD(lbl_8042AC68, u8**, 0x68) == arg0) {
				M2C_FIELD(lbl_8042AC68, u8**, 0x68) = var_r5;
			}
		}
	}
	if ((u32)M2C_FIELD(lbl_8042AC68, u32*, 0x94) == (u32)arg0) {
		M2C_FIELD(lbl_8042AC68, u32*, 0x94) = 0U;
	} else if ((u32)M2C_FIELD(lbl_8042AC68, u32*, 0x90) == (u32)arg0) {
		M2C_FIELD(lbl_8042AC68, u32*, 0x90) = 0U;
	}
	if (((M2C_UNK (*)(u8*))M2C_FIELD(lbl_8042AC68, M2C_UNK(**)(u8*), 0x78)) != NULL) {
		M2C_FIELD(lbl_8042AC68, M2C_UNK(**)(u8*), 0x78)(arg0);
	}
	M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(s32, M2C_UNK*), 0x138)(
	    M2C_FIELD(arg0, s32*, 0), lbl_8042C9A4);
	return 1;
}

void fn_80234FD8(u8* arg0, s32* arg1, s32* arg2, s32* arg3, s32* arg4)
{
	if (arg1 != NULL) {
		*arg1 = M2C_FIELD(arg0, s32*, 0x10);
	}
	if (arg2 != NULL) {
		*arg2 = M2C_FIELD(arg0, s32*, 0x18);
	}
	if (arg3 != NULL) {
		*arg3 = M2C_FIELD(arg0, s32*, 0x1C);
	}
	if (arg4 != NULL) {
		*arg4 = M2C_FIELD(arg0, s32*, 0x20);
	}
}

s32 fn_8023501C(u8* arg0, s32 arg1)
{
	s32 var_r6;
	s32 var_r7;
	s32 var_r8;
	s32 var_r9;

	var_r8 = -1;
	var_r9 = 0;
	var_r7 = 0;
	var_r6 = 0;
loop_4:
	if ((var_r9 == 0) && (var_r7 < (s32)M2C_FIELD(arg0, s32*, 0x10))) {
		if (arg1 == *(s32*)((u8*)M2C_FIELD(arg0, s32*, 0x18) + var_r6)) {
			var_r9 = 1;
			var_r8 = var_r7;
		}
		var_r6 += 4;
		var_r7 += 1;
		goto loop_4;
	}
	return var_r8;
}

s32 fn_8023506C(u8* arg0, s32 arg1)
{
	s32 var_r6;
	s32 var_r7;
	s32 var_r8;
	s32 var_r9;

	var_r6 = 0;
	var_r7 = -1;
	var_r8 = 0;
	var_r9 = 0;
loop_4:
	if ((var_r6 == 0) && (var_r8 < (s32)M2C_FIELD(arg0, s32*, 0x10))) {
		if (arg1 == *(s32*)((u8*)M2C_FIELD(arg0, s32*, 0x18) + var_r9)) {
			var_r6 = 1;
			var_r7 = var_r8;
		}
		var_r9 += 4;
		var_r8 += 1;
		goto loop_4;
	}
	if (var_r7 >= 0) {
		return *(s32*)((u8*)M2C_FIELD(arg0, s32*, 0x1C) + (var_r7 * 4));
	}
	return -1;
}

u8* fn_802350D4(s32 arg0)
{
	u8* var_r4;
	u8* var_r5;
	u8* var_r6;

	var_r6 = NULL;
	var_r5 = M2C_FIELD(lbl_8042AC68, u8**, 0x68);
	var_r4 = var_r5;
	if (var_r5 != NULL) {
	loop_1:
		if ((s32)M2C_FIELD(var_r4, s32*, 8) == arg0) {
			var_r6 = var_r4;
		} else {
			var_r4 = M2C_FIELD(var_r4, u8**, 4);
			if (var_r4 != var_r5) {
				goto loop_1;
			}
		}
	}
	return var_r6;
}

u8* fn_80235118(s32 arg0, s32* arg1, s32* arg2)
{
	s32* var_r12;
	s32* var_r31;
	s32 temp_cr0_eq;
	s32 temp_r30;
	s32 var_r10;
	s32 var_r11;
	s32 var_r8;
	s32 var_r9;
	u8* var_r27;
	u8* var_r29;

	var_r27 = NULL;
	var_r29 = M2C_FIELD(lbl_8042AC68, u8**, 0x68);
	if ((u8*)M2C_FIELD(lbl_8042AC68, u8**, 0x68) != NULL) {
	loop_1:
		temp_r30    = M2C_FIELD(var_r29, s32*, 0x10);
		temp_cr0_eq = temp_r30 == arg0;
		if (temp_cr0_eq != 0) {
			var_r8 = 1;
			if (temp_cr0_eq != 0) {
				var_r12 = arg1;
				var_r31 = arg2;
				var_r10 = 0;
			loop_14:
				if ((var_r8 != 0) && (var_r10 < arg0)) {
					var_r9  = 0;
					var_r11 = 0;
				loop_9:
					if ((var_r8 != 0) && (var_r9 < temp_r30)) {
						if ((s32)*var_r12
						    == *(s32*)((u8*)M2C_FIELD(var_r29, s32*, 0x18) + var_r11)) {
							if ((s32)*var_r31
							    != *(s32*)((u8*)M2C_FIELD(var_r29, s32*, 0x20) + var_r11)) {
								var_r8 = 0;
								goto block_8;
							}
						} else {
						block_8:
							var_r11 += 4;
							var_r9 += 1;
							goto loop_9;
						}
					}
					if (var_r9 >= temp_r30) {
						var_r8 = 0;
					}
					var_r12 += 4;
					var_r31 += 4;
					var_r10 += 1;
					goto loop_14;
				}
			}
			if (var_r8 != 0) {
				var_r27 = var_r29;
			} else {
				goto block_18;
			}
		} else {
		block_18:
			var_r29 = M2C_FIELD(var_r29, u8**, 4);
			if (var_r29 != (u8*)M2C_FIELD(lbl_8042AC68, u8**, 0x68)) {
				goto loop_1;
			}
		}
	}
	return var_r27;
}

u8* fn_8023521C(s32* arg0)
{
	s32 spC;
	s32 sp8;
	s32* var_r28;
	s32* var_r29_2;
	s32* var_r30;
	s32* var_r31;
	s32 temp_cr0_eq;
	s32 temp_r0;
	s32 temp_r27;
	s32 temp_r27_2;
	s32 temp_r4;
	u8* temp_r4_2;
	s32 temp_r5;
	s32 var_ctr;
	s32 var_r0;
	s32 var_r10;
	s32 var_r11;
	s32 var_r12;
	s32 var_r5;
	s32 var_r6_2;
	s32 var_r8_2;
	s32 var_r9;
	u32 var_r7;
	u8* var_r29;
	u8* var_r6;
	u8* var_r8;

	fn_80193884(&spC, (s32*)4U);
	fn_80193884(arg0, &sp8, 4);
	if (sp8 > 0) {
		temp_r27 = sp8 * 8;
		if (temp_r27 > (s32)M2C_FIELD(lbl_8042AC68, s32*, 0x8C)) {
			var_r31 = M2C_FIELD(lbl_8042C9A4, s32 * (**)(s32*, s32, M2C_UNK*), 0x13C)(
			    M2C_FIELD(lbl_8042AC68, s32**, 0x88), temp_r27, lbl_8042C9A4);
			if (var_r31 == NULL) {
				return NULL;
			}
			M2C_FIELD(lbl_8042AC68, s32**, 0x88) = var_r31;
			M2C_FIELD(lbl_8042AC68, s32*, 0x8C)  = temp_r27;
			goto block_6;
		}
		var_r31 = M2C_FIELD(lbl_8042AC68, s32**, 0x88);
	block_6:
		temp_r5 = sp8 * 4;
		var_r30 = var_r31 + temp_r5;
		fn_80193884(arg0, var_r31, temp_r5);
		fn_80193884(arg0, var_r30, sp8 * 4);
		goto block_8;
	}
	var_r31 = NULL;
	var_r30 = NULL;
block_8:
	var_r6 = NULL;
	var_r8 = M2C_FIELD(lbl_8042AC68, u8**, 0x68);
	if ((u8*)M2C_FIELD(lbl_8042AC68, u8**, 0x68) != NULL) {
	loop_9:
		temp_r27_2  = M2C_FIELD(var_r8, s32*, 0x10);
		temp_cr0_eq = temp_r27_2 == sp8;
		if (temp_cr0_eq != 0) {
			var_r9 = 1;
			if (temp_cr0_eq != 0) {
				var_r29_2 = var_r31;
				var_r28   = var_r30;
				var_r11   = 0;
			loop_22:
				if ((var_r9 != 0) && (var_r11 < sp8)) {
					var_r10 = 0;
					var_r12 = 0;
				loop_17:
					if ((var_r9 != 0) && (var_r10 < temp_r27_2)) {
						if ((s32)*var_r29_2
						    == *(s32*)((u8*)M2C_FIELD(var_r8, s32*, 0x18) + var_r12)) {
							if ((s32)*var_r28
							    != *(s32*)((u8*)M2C_FIELD(var_r8, s32*, 0x20) + var_r12)) {
								var_r9 = 0;
								goto block_16;
							}
						} else {
						block_16:
							var_r12 += 4;
							var_r10 += 1;
							goto loop_17;
						}
					}
					if (var_r10 >= temp_r27_2) {
						var_r9 = 0;
					}
					var_r29_2 += 4;
					var_r28 += 4;
					var_r11 += 1;
					goto loop_22;
				}
			}
			if (var_r9 != 0) {
				var_r6 = var_r8;
			} else {
				goto block_26;
			}
		} else {
		block_26:
			var_r8 = M2C_FIELD(var_r8, u8**, 4);
			if (var_r8 != (u8*)M2C_FIELD(lbl_8042AC68, u8**, 0x68)) {
				goto loop_9;
			}
		}
	}
	var_r29 = var_r6;
	if (var_r6 == NULL) {
		var_r29 = (u8*)fn_80234A38(sp8, var_r31, var_r30);
	} else {
		M2C_FIELD(var_r6, s32*, 0xC) = (s32)(M2C_FIELD(var_r6, s32*, 0xC) + 1);
	}
	if (var_r29 != NULL) {
		M2C_FIELD(var_r29, s32*, 8) = spC;
	}
	if (fn_8023943C() < 3) {
		temp_r4 = M2C_FIELD(var_r29, s32*, 0x10);
		var_r7  = *(u32*)M2C_FIELD(var_r29, u8**, 0x20);
		if (var_r7 != 0x10U) {
			var_r5   = 1;
			var_r6_2 = 4;
			var_ctr  = temp_r4 - 1;
			if (temp_r4 > 1) {
				do {
					temp_r4_2 = (u8*)M2C_FIELD(var_r29, s32*, 0x24);
					var_r8_2  = *(s32*)(temp_r4_2 + var_r6_2);
					if (*(s32*)((u8*)M2C_FIELD(var_r29, s32*, 0x18) + var_r6_2) == 1) {
						var_r8_2 += 4;
						var_r0 = (var_r8_2 + 3) & 0xFFFFFFFC;
					} else {
						var_r0 = *(u32*)((u8*)M2C_FIELD(var_r29, u8**, 0x20) + var_r6_2);
					}
					*(s32*)(temp_r4_2 + var_r6_2) = var_r8_2;
					var_r5 += 1;
					*(u32*)((u8*)M2C_FIELD(var_r29, u8**, 0x20) + var_r6_2) = var_r0;
					*(u32*)((u8*)M2C_FIELD(var_r29, s32*, 0x1C) + var_r6_2) = var_r7;
					temp_r0 = *(u32*)((u8*)M2C_FIELD(var_r29, u8**, 0x20) + var_r6_2);
					var_r6_2 += 4;
					var_r7 += temp_r0;
					var_ctr -= 1;
				} while (var_ctr != 0);
			}
			*(u32*)((u8*)M2C_FIELD(var_r29, s32*, 0x1C) + (var_r5 * 4)) = var_r7;
		}
	}
	if (((M2C_UNK (*)(u8*))M2C_FIELD(lbl_8042AC68, M2C_UNK(**)(u8*), 0x74)) != NULL) {
		M2C_FIELD(lbl_8042AC68, M2C_UNK(**)(u8*), 0x74)(var_r29);
	}
	return var_r29;
}

u8* fn_802354D4(u8* arg0, s32* arg1)
{
	s32 temp_r0;

	if (fn_80192ED8(arg1, 0x25, fn_80235590(), 0x35000, 0xFFFF) == 0U) {
		return NULL;
	}
	fn_80193474(arg1, arg0 + 8, 4);
	fn_80193474(arg1, arg0 + 0x10, 4);
	temp_r0 = M2C_FIELD(arg0, s32*, 0x10);
	if (temp_r0 > 0) {
		fn_80193474(arg1, M2C_FIELD(arg0, s32**, 0x18), temp_r0 * 4);
		fn_80193474(arg1, M2C_FIELD(arg0, s32**, 0x24), M2C_FIELD(arg0, s32*, 0x10) * 4);
	}
	return arg0;
}

s32 fn_80235590(u8* arg0)
{
	s32 temp_r0;

	temp_r0 = M2C_FIELD(arg0, s32*, 0x10);
	if (temp_r0 > 0) {
		return (temp_r0 * 8) + 8;
	}
	return 8;
}

s32 fn_802355AC(s32 arg0)
{
	M2C_FIELD(lbl_8042AC68, s32*, 0x74) = arg0;
	return 1;
}

s32 fn_802355C0(s32 arg0)
{
	M2C_FIELD(lbl_8042AC68, s32*, 0x78) = arg0;
	return 1;
}

void fn_802355D4(u8* arg0)
{
	M2C_FIELD(arg0, s32*, 0)    = 0;
	M2C_FIELD(arg0, s32*, 4)    = 0;
	M2C_FIELD(arg0, s32*, 0x10) = -1;
	M2C_FIELD(arg0, s32*, 0x14) = -1;
	M2C_FIELD(arg0, s32*, 0xC)  = 0;
	M2C_FIELD(arg0, s32*, 0x18) = 0;
	M2C_FIELD(arg0, s32*, 0x1C) = 0;
	M2C_FIELD(arg0, s32*, 0x20) = 0;
	M2C_FIELD(arg0, s32*, 0x28) = 2;
	M2C_FIELD(arg0, s32*, 0x2C) = 2;
	M2C_FIELD(arg0, s32*, 0x30) = 1;
}

u8* fn_80235614(u8* arg0)
{
	u32 temp_r31;
	u8* temp_r3;
	u8* temp_r3_2;

	temp_r3 = M2C_FIELD(arg0, u8**, 0x18);
	if (temp_r3 != NULL) {
		temp_r31 = M2C_FIELD(temp_r3, u32*, 4);
		fn_80152220(temp_r3, NULL);
		if (temp_r31 != 0U) {
			fn_8019E480(temp_r31);
		}
		fn_80150358(M2C_FIELD(arg0, u8**, 0x18));
	}
	M2C_FIELD(arg0, u8**, 0x18) = NULL;
	temp_r3_2                   = M2C_FIELD(arg0, u8**, 0x1C);
	if (temp_r3_2 != NULL) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(temp_r3_2, lbl_8042C9A4);
	}
	M2C_FIELD(arg0, u32*, 0x1C) = 0U;
	M2C_FIELD(arg0, s32*, 0x20) = 0;
	M2C_FIELD(arg0, s32*, 0xC)  = 0;
	return arg0;
}

void fn_802356AC(u8* arg0, u8* arg1)
{
	M2C_FIELD(arg0, s32*, 0)    = (s32)M2C_FIELD(arg1, s32*, 0);
	M2C_FIELD(arg0, s32*, 4)    = (s32)M2C_FIELD(arg1, s32*, 4);
	M2C_FIELD(arg0, s32*, 0xC)  = (s32)M2C_FIELD(arg1, s32*, 0xC);
	M2C_FIELD(arg0, s32*, 0x10) = (s32)M2C_FIELD(arg1, s32*, 0x10);
	M2C_FIELD(arg0, s32*, 0x14) = (s32)M2C_FIELD(arg1, s32*, 0x14);
	M2C_FIELD(arg0, s32*, 0x28) = (s32)M2C_FIELD(arg1, s32*, 0x28);
	M2C_FIELD(arg0, s32*, 0x2C) = (s32)M2C_FIELD(arg1, s32*, 0x2C);
	M2C_FIELD(arg0, s32*, 0x30) = (s32)M2C_FIELD(arg1, s32*, 0x30);
}

u8* fn_802356F0(u8* arg0)
{
	s32 spC;
	s32 sp8;
	s32* temp_r31;
	s32 var_r28;
	s32 var_r29;
	s32 var_r30;

	var_r30                  = 0;
	temp_r31                 = fn_801FD214(M2C_FIELD(arg0, u8**, 0x18));
	M2C_FIELD(arg0, s32*, 0) = 0;
	var_r29                  = 0;
	var_r28                  = 1;
loop_4:
	if (var_r29 < (s32)*temp_r31) {
		if (fn_801FD224(M2C_FIELD(arg0, u8**, 0x18), &sp8, var_r28, 0x40000000) != 0) {
			var_r29 += 1;
			*(s32*)((u8*)M2C_FIELD(arg0, s32*, 0x1C) + var_r30) = sp8;
			*(s32*)((u8*)M2C_FIELD(arg0, s32*, 0x20) + var_r30) = sp8;
			*(s32*)((u8*)M2C_FIELD(arg0, s32*, 0x24) + var_r30) = spC;
			var_r30 += 4;
			M2C_FIELD(arg0, s32*, 0) = (s32)(M2C_FIELD(arg0, s32*, 0) | var_r28);
		}
		var_r28 *= 2;
		goto loop_4;
	}
	return arg0;
}

u8* fn_802357A8(s32* arg0, u8* arg1)
{
	fn_801979AC(arg0, arg1 + 0x10, 4);
	fn_801979AC(arg0, arg1 + 0x14, 4);
	fn_80193884(arg0, arg1 + 0x28, 4);
	fn_80193884(arg0, arg1 + 0x2C, 4);
	fn_80193884(arg0, arg1 + 0x30, 4);
	return arg1;
}

u8* fn_8023582C(s32* arg0, u8* arg1)
{
	fn_80197B48(arg0, arg1 + 0x10, 4);
	fn_80197B48(arg0, arg1 + 0x14, 4);
	fn_80193474(arg0, arg1 + 0x28, 4);
	fn_80193474(arg0, arg1 + 0x2C, 4);
	fn_80193474(arg0, arg1 + 0x30, 4);
	return arg1;
}

s32 fn_802358B0(void)
{
	return 0x14;
}

#pragma dont_inline on
M2C_UNK* fn_802358B8(M2C_UNK* arg0)
{
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f1;
	s32* temp_r3;
	s32 temp_cr0_eq;
	s32 temp_r3_3;
	s32 var_r28;
	s32 var_r31;
	u32 temp_r3_2;
	u8* temp_r29;
	u8* temp_r3_4;
	u8* temp_r3_5;
	u8* temp_r3_6;
	u8* temp_r3_7;
	u8* temp_r3_8;
	u8* temp_r3_9;
	u8* temp_r4;
	u8* temp_r4_2;
	u8* temp_r4_3;
	u8* temp_r4_4;
	u8* var_r30;

	temp_r29 = (u8*)arg0 + fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 6);
	if ((u32)M2C_FIELD(temp_r29, u32*, 0x18) != 0U) {
		temp_cr0_eq = (u32)M2C_FIELD(temp_r29, u32*, 0x1C) == 0U;
		if (temp_cr0_eq == 0) {
			if (temp_cr0_eq == 0) {
				M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(M2C_UNK*), 0x138)(lbl_8042C9A4);
			}
			M2C_FIELD(temp_r29, u32*, 0x1C) = 0U;
			M2C_FIELD(temp_r29, s32*, 0x20) = 0;
			M2C_FIELD(temp_r29, s32*, 0x24) = 0;
			if ((u32)M2C_FIELD(temp_r29, u32*, 0x18) != 0U) {
				temp_r3 = fn_801FD214();
				M2C_FIELD(temp_r29, u32*, 0x1C)
				    = M2C_FIELD(lbl_8042C9A4, u32(**)(s32), 0x134)(*temp_r3 * 0xC);
				temp_r3_2 = M2C_FIELD(temp_r29, u32*, 0x1C);
				if (temp_r3_2 != 0U) {
					M2C_FIELD(temp_r29, s32*, 0x20) = (s32)(temp_r3_2 + (*temp_r3 * 4));
					M2C_FIELD(temp_r29, s32*, 0x24)
					    = (s32)(M2C_FIELD(temp_r29, s32*, 0x20) + (*temp_r3 * 4));
				}
			}
		}
		return arg0;
	}
	var_r30   = NULL;
	temp_r3_3 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 1);
	if (temp_r3_3 >= 0) {
		var_r30 = (u8*)arg0 + temp_r3_3;
	}
	var_r28 = 1;
	if (fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 8) >= 0) {
		var_r28 = 8;
	}
	var_r31 = var_r28;
	if (fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 2) >= 0) {
		var_r31 = var_r28 | 2;
	}
	if ((u32)M2C_FIELD(var_r30, u32*, 0xA4) != 0U) {
		if (fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 3) >= 0) {
			var_r31 |= 0x80;
		} else {
			var_r31 |= 0x80000;
		}
	}
	if ((fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 5) >= 0) && (var_r31 & 1)) {
		var_r31 |= 4;
	}
	M2C_FIELD(temp_r29, s32*, 0x10) = (s32)(M2C_FIELD(temp_r29, s32*, 0x10) & 0xFFFDFFFF);
	if (var_r31 & 1) {
		if (fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 4) >= 0) {
			var_r31 |= 0x20;
		} else {
			temp_f1 = M2C_FIELD(var_r30, f32*, 0x80);
			if ((temp_f1 > lbl_80430250) || (temp_f1 < lbl_80430254)) {
				var_r31 |= 0x20000;
				M2C_FIELD(temp_r29, s32*, 0x10) = (s32)(M2C_FIELD(temp_r29, s32*, 0x10) | 0x20000);
			}
		}
	}
	temp_r3_4 = fn_801FCEA0(M2C_FIELD(var_r30, s32*, 4), var_r31, M2C_FIELD(temp_r29, s32*, 4));
	if (temp_r3_4 == NULL) {
		return NULL;
	}
	temp_r3_5                        = fn_8019E344();
	M2C_FIELD(temp_r3_5, f32*, 0x38) = (f32)lbl_80430258;
	M2C_FIELD(temp_r3_5, f32*, 0x24) = (f32)lbl_80430258;
	M2C_FIELD(temp_r3_5, f32*, 0x10) = (f32)lbl_80430258;
	M2C_FIELD(temp_r3_5, f32*, 0x20) = (f32)lbl_8043025C;
	M2C_FIELD(temp_r3_5, f32*, 0x18) = (f32)lbl_8043025C;
	M2C_FIELD(temp_r3_5, f32*, 0x14) = (f32)lbl_8043025C;
	M2C_FIELD(temp_r3_5, f32*, 0x34) = (f32)lbl_8043025C;
	M2C_FIELD(temp_r3_5, f32*, 0x30) = (f32)lbl_8043025C;
	M2C_FIELD(temp_r3_5, f32*, 0x28) = (f32)lbl_8043025C;
	M2C_FIELD(temp_r3_5, f32*, 0x48) = (f32)lbl_8043025C;
	M2C_FIELD(temp_r3_5, f32*, 0x44) = (f32)lbl_8043025C;
	M2C_FIELD(temp_r3_5, f32*, 0x40) = (f32)lbl_8043025C;
	M2C_FIELD(temp_r3_5, s32*, 0x1C) = (s32)(M2C_FIELD(temp_r3_5, s32*, 0x1C) | 0x20000 | 3);
	fn_80152220(temp_r3_4, temp_r3_5);
	sp8                              = lbl_80430260;
	temp_r4                          = *(u8**)(temp_r3_4 + lbl_8042CF48);
	spC                              = lbl_80430260;
	M2C_FIELD(temp_r4, f32*, 0xB0)   = sp8;
	M2C_FIELD(temp_r4, f32*, 0xB4)   = spC;
	temp_r3_6                        = *(u8**)(temp_r3_4 + lbl_8042CF48);
	M2C_FIELD(temp_r3_6, s32*, 0x40) = (s32)(M2C_FIELD(temp_r3_6, s32*, 0x40) | 0x01000000);
	if (!(var_r31 & 2)) {
		M2C_FIELD(*(u8**)(temp_r3_4 + lbl_8042CF48), s32*, 0xC4)
		    = (s32)M2C_FIELD(var_r30, s32*, 0x7C);
		temp_r4_2 = *M2C_FIELD(M2C_FIELD(temp_r3_4, u8**, 0x18), u8***, 0x20);
		if (temp_r4_2 != NULL) {
			M2C_FIELD(temp_r4_2, s32*, 4)
			    = (s32)M2C_FIELD(*(u8**)(temp_r3_4 + lbl_8042CF48), s32*, 0xC4);
		}
		temp_r3_7                        = *(u8**)(temp_r3_4 + lbl_8042CF48);
		M2C_FIELD(temp_r3_7, s32*, 0x40) = (s32)(M2C_FIELD(temp_r3_7, s32*, 0x40) | 0x2000);
	}
	if (var_r31 & 0x80000) {
		sp10 = M2C_FIELD(var_r30, f32*, 0x84);
		sp14 = M2C_FIELD(var_r30, f32*, 0x88);
		sp18 = M2C_FIELD(var_r30, f32*, 0x8C);
		sp1C = M2C_FIELD(var_r30, f32*, 0x90);
		memcpy((M2C_UNK*)(*(u8**)(temp_r3_4 + lbl_8042CF48) + 0xD8), (s32*)&sp10, 0x10);
		temp_r3_8                        = *(u8**)(temp_r3_4 + lbl_8042CF48);
		M2C_FIELD(temp_r3_8, s32*, 0x40) = (s32)(M2C_FIELD(temp_r3_8, s32*, 0x40) | 0x80000);
	}
	if (!(var_r31 & 4)) {
		sp8                              = M2C_FIELD(var_r30, f32*, 0x74);
		spC                              = M2C_FIELD(var_r30, f32*, 0x78);
		temp_r4_3                        = *(u8**)(temp_r3_4 + lbl_8042CF48);
		M2C_FIELD(temp_r4_3, f32*, 0xB8) = sp8;
		M2C_FIELD(temp_r4_3, f32*, 0xBC) = spC;
		temp_r3_9                        = *(u8**)(temp_r3_4 + lbl_8042CF48);
		M2C_FIELD(temp_r3_9, s32*, 0x40) = (s32)(M2C_FIELD(temp_r3_9, s32*, 0x40) | 0x4000);
	}
	if ((u32)M2C_FIELD(var_r30, u32*, 0xA4) != 0U) {
		fn_8015498C(*M2C_FIELD(M2C_FIELD(temp_r3_4, u8**, 0x18), u8***, 0x20));
	}
	if (fn_80235CEC(arg0, temp_r3_4) == NULL) {
		return NULL;
	}
	M2C_FIELD(*(u8**)((u8*)M2C_FIELD(temp_r29, u32*, 0x18) + lbl_8042CF48), s32*, 0xA4)
	    = (s32)M2C_FIELD(temp_r29, s32*, 0x28);
	M2C_FIELD(*(u8**)((u8*)M2C_FIELD(temp_r29, u32*, 0x18) + lbl_8042CF48), s32*, 0xA8)
	    = (s32)M2C_FIELD(temp_r29, s32*, 0x2C);
	temp_r4_4                        = *(u8**)((u8*)M2C_FIELD(temp_r29, u32*, 0x18) + lbl_8042CF48);
	M2C_FIELD(temp_r4_4, s32*, 0x40) = (s32)(M2C_FIELD(temp_r4_4, s32*, 0x40) | 0x10000000);
	M2C_FIELD(*(u8**)((u8*)M2C_FIELD(temp_r29, u32*, 0x18) + lbl_8042CF48), s32*, 0xAC)
	    = (s32)M2C_FIELD(temp_r29, s32*, 0x30);
	return arg0;
}
#pragma dont_inline reset

#pragma dont_inline on
M2C_UNK* fn_80235CEC(M2C_UNK* arg0, u8* arg1)
{
	s32 temp_r0_2;
	s32* temp_r3;
	s32* temp_r3_3;
	u32 temp_r3_4;
	u8* temp_r31;
	u8* temp_r3_2;
	u8* var_r0;

	temp_r31 = (u8*)arg0 + fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 6);
	if ((u8*)M2C_FIELD(temp_r31, u8**, 0x18) != NULL) {
		return NULL;
	}
	fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u8**, 0x10), 1);
	temp_r3                          = fn_801FD214(arg1);
	M2C_FIELD(temp_r31, s32*, 0xC)   = **(s32**)(arg1 + lbl_8042CF48);
	M2C_FIELD(temp_r31, u8**, 0x18)  = arg1;
	M2C_FIELD(temp_r31, s32*, 0)     = (s32)M2C_FIELD(temp_r3, s32*, 8);
	M2C_FIELD(temp_r31, s32*, 4)     = -1;
	M2C_FIELD(temp_r31, s32*, 8)     = 0;
	temp_r3_2                        = *(u8**)(arg1 + lbl_8042CF48);
	M2C_FIELD(temp_r3_2, s32*, 0x40) = (s32)(M2C_FIELD(temp_r3_2, s32*, 0x40) | 0x800000);
	M2C_FIELD(*(u8**)(arg1 + lbl_8042CF48), s32*, 4) = 0;
	if ((u32)M2C_FIELD(temp_r31, u32*, 0x1C) != 0U) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(
		    M2C_FIELD(temp_r31, u8**, 0x1C), lbl_8042C9A4);
	}
	M2C_FIELD(temp_r31, u32*, 0x1C) = 0U;
	M2C_FIELD(temp_r31, s32*, 0x20) = 0;
	M2C_FIELD(temp_r31, s32*, 0x24) = 0;
	if ((u8*)M2C_FIELD(temp_r31, u8**, 0x18) != NULL) {
		temp_r3_3 = fn_801FD214(M2C_FIELD(temp_r31, u8**, 0x18));
		temp_r0_2 = *temp_r3_3 * 3;
		M2C_FIELD(temp_r31, u32*, 0x1C)
		    = M2C_FIELD(lbl_8042C9A4, u32(**)(s32), 0x134)(temp_r0_2 * 4);
		temp_r3_4 = M2C_FIELD(temp_r31, u32*, 0x1C);
		if (temp_r3_4 == 0U) {
			var_r0 = NULL;
		} else {
			M2C_FIELD(temp_r31, s32*, 0x20) = (s32)(temp_r3_4 + (*temp_r3_3 * 4));
			M2C_FIELD(temp_r31, s32*, 0x24)
			    = (s32)(M2C_FIELD(temp_r31, s32*, 0x20) + (*temp_r3_3 * 4));
			goto block_8;
		}
	} else {
	block_8:
		var_r0 = temp_r31;
	}
	if (var_r0 != temp_r31) {
		return NULL;
	}
	return arg0;
}
#pragma dont_inline reset

u8* fn_80235E64(u8* arg0, u8* arg1, f32* arg2)
{
	s32 spF8;
	u8* spF4;
	u8* spF0;
	s32 spEC;
	s32 spE8;
	s32 spE4;
	s32 spE0;
	s32 spDC;
	s32 spD8;
	s32 spD4;
	s32 spD0;
	u8* spCC;
	u8* spC8;
	s32 spA4;
	f32 spA0;
	f32 sp9C;
	f32 sp98;
	s32 sp94;
	s32 sp90;
	s32 sp8C;
	s32 sp88;
	s32 sp84;
	s32 sp80;
	s32 sp7C;
	s32 sp78;
	s32 sp74;
	s32 sp70;
	s32 sp6C;
	s32 sp68;
	s32 sp64;
	f32 sp60;
	f32 sp5C;
	f32 sp58;
	s32 sp54;
	s32 sp50;
	s32 sp4C;
	s32 sp48;
	s32 sp44;
	s32 sp40;
	s32 sp3C;
	s32 sp38;
	s32 sp34;
	s32 sp30;
	s32 sp2C;
	s32 sp28;
	f32 sp24;
	f32 sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	u8* spC;
	u8* sp8;
	f32* var_r17;
	f32* var_r18;
	f32 temp_f0;
	f32 temp_f0_2;
	f32 temp_f0_3;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f26;
	f32 temp_f2;
	f32 temp_f3;
	f32 temp_f3_2;
	f32 temp_f4;
	f32 var_f25;
	f32 var_f29;
	f32 var_f30;
	f32 var_f31;
	s32* var_r14;
	s32* var_r16;
	s32* var_r26;
	s32 temp_cr0_gt;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 temp_r0_4;
	s32 temp_r0_5;
	s32 temp_r0_6;
	s32 temp_r5;
	s32 temp_r7;
	s32 temp_r7_2;
	s32 temp_r7_3;
	s32 temp_r7_4;
	s32 var_r3;
	s32 var_r3_2;
	u32 var_r20;
	u32 var_r22;
	u8* temp_r15;
	u8* temp_r27;
	u8* temp_r28;
	u8* temp_r29;
	u8* temp_r3;
	u8* temp_r3_2;
	u8* temp_r5_2;
	u8* var_r19;
	u8* var_r21;
	u8* var_r23;
	u8* var_r24;
	u8* var_r25;
	u8* var_r30;

	var_f29  = 0.0f;
	var_f30  = 0.0f;
	sp8      = arg0;
	temp_f26 = *arg2;
	var_r26  = NULL;
	var_r25  = NULL;
	spC      = arg1;
	var_r24  = NULL;
	var_f25  = lbl_80430268;
	spF4     = sp8 + M2C_FIELD(lbl_8042AC68, s32*, 0x98);
	var_r23  = NULL;
	var_r22  = 0U;
	spE4     = 0;
	var_r21  = NULL;
	var_r20  = 0U;
	spE0     = 0;
	var_r19  = NULL;
	var_r18  = NULL;
	spDC     = 0;
	var_r17  = NULL;
	var_r30  = NULL;
	spD8     = 0;
	spD4     = 0;
	spC8     = NULL;
	if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xAC) >= 0) {
		temp_r3 = sp8 + M2C_FIELD(lbl_8042AC68, s32*, 0xAC);
		if ((s32)M2C_FIELD(temp_r3, s32*, 0x70) != 0) {
			spC8 = temp_r3;
		}
	}
	if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xA8) >= 0) {
		var_r30 = sp8 + M2C_FIELD(lbl_8042AC68, s32*, 0xA8);
	}
	if (var_r30 != NULL) {
		temp_r0 = M2C_FIELD(var_r30, s32*, 0);
		spE0    = 0;
		var_r3  = 0;
		var_r24 = NULL;
		var_r23 = NULL;
		if (temp_r0 & 1) {
			var_r24 = *M2C_FIELD(var_r30, u8***, 0x1C);
			var_r23 = *M2C_FIELD(var_r30, u8***, 0x20);
			if (M2C_FIELD(var_r30, s32*, 0x10) & 1) {
				spE0 = *M2C_FIELD(var_r30, s32**, 0x24);
			}
			var_r3 = 1;
		}
		var_r26 = NULL;
		var_r25 = NULL;
		spE4    = 0;
		if (temp_r0 & 2) {
			temp_r7 = var_r3 * 4;
			var_r26 = *(s32**)((u8*)M2C_FIELD(var_r30, u8***, 0x1C) + temp_r7);
			var_r25 = *(u8**)((u8*)M2C_FIELD(var_r30, u8***, 0x20) + temp_r7);
			if (M2C_FIELD(var_r30, s32*, 0x10) & 2) {
				spE4 = *(s32*)((u8*)M2C_FIELD(var_r30, s32**, 0x24) + temp_r7);
			}
			var_r3 += 1;
		}
		var_r20 = 0U;
		var_r19 = NULL;
		spD8    = 0;
		if (temp_r0 & 4) {
			temp_r7_2 = var_r3 * 4;
			var_r20   = *(u32*)((u8*)M2C_FIELD(var_r30, u8***, 0x1C) + temp_r7_2);
			var_r19   = *(u8**)((u8*)M2C_FIELD(var_r30, u8***, 0x20) + temp_r7_2);
			if (M2C_FIELD(var_r30, s32*, 0x10) & 4) {
				spD8 = *(s32*)((u8*)M2C_FIELD(var_r30, s32**, 0x24) + temp_r7_2);
			}
			var_r3 += 1;
		}
		if (temp_r0 & 8) {
			temp_r7_3 = var_r3 * 4;
			var_r24   = *(u8**)((u8*)M2C_FIELD(var_r30, u8***, 0x1C) + temp_r7_3);
			var_r23   = *(u8**)((u8*)M2C_FIELD(var_r30, u8***, 0x20) + temp_r7_3);
			if (M2C_FIELD(var_r30, s32*, 0x10) & 8) {
				spE0 = *(s32*)((u8*)M2C_FIELD(var_r30, s32**, 0x24) + temp_r7_3);
			}
			var_r3 += 1;
		}
		var_r18 = NULL;
		var_r17 = NULL;
		spD4    = 0;
		if (temp_r0 & 0x20) {
			temp_r7_4 = var_r3 * 4;
			var_r18   = *(f32**)((u8*)M2C_FIELD(var_r30, u8***, 0x1C) + temp_r7_4);
			var_r17   = *(f32**)((u8*)M2C_FIELD(var_r30, u8***, 0x20) + temp_r7_4);
			if (M2C_FIELD(var_r30, s32*, 0x10) & 0x20) {
				spD4 = *(s32*)((u8*)M2C_FIELD(var_r30, s32**, 0x24) + temp_r7_4);
			}
			var_r3 += 1;
		}
		var_r22 = 0U;
		var_r21 = NULL;
		spDC    = 0;
		if (temp_r0 & 0x80) {
			temp_r5 = var_r3 * 4;
			var_r22 = *(u32*)((u8*)M2C_FIELD(var_r30, u8***, 0x1C) + temp_r5);
			var_r21 = *(u8**)((u8*)M2C_FIELD(var_r30, u8***, 0x20) + temp_r5);
			if (M2C_FIELD(var_r30, s32*, 0x10) & 0x80) {
				spDC = *(s32*)((u8*)M2C_FIELD(var_r30, s32**, 0x24) + temp_r5);
			}
		}
	}
	temp_r5_2 = M2C_FIELD(spF4, u8**, 0xA8);
	spD0      = M2C_FIELD(M2C_FIELD(sp8, u8**, 0x18), s32*, 0xC);
	var_r16   = (s32*)(spC + M2C_FIELD(spC, s32*, 0x14));
	var_r14   = var_r16;
	if (temp_r5_2 != NULL) {
		sp1C = M2C_FIELD(temp_r5_2, f32*, 0x30);
		sp20 = M2C_FIELD(temp_r5_2, f32*, 0x34);
		sp24 = M2C_FIELD(temp_r5_2, f32*, 0x38);
	} else {
		sp1C = lbl_80430268;
		sp20 = lbl_80430268;
		sp24 = lbl_80430268;
	}
	spEC = M2C_FIELD(spC, s32*, 8);
	spF8 = spD0;
	spE8 = 0;
loop_103:
	temp_cr0_gt = spEC > 0;
	spEC -= 1;
	if (temp_cr0_gt != 0) {
		temp_f1 = M2C_FIELD(var_r16, f32*, 4);
		if (temp_f1 < M2C_FIELD(var_r16, f32*, 8)) {
			M2C_FIELD(var_r16, f32*, 4) = (f32)(temp_f1 + temp_f26);
			var_f31                     = lbl_8043026C;
			temp_f0 = M2C_FIELD(var_r16, f32*, 4) * M2C_FIELD(var_r16, f32*, 0xC);
			if (temp_f0 > var_f31) {

			} else {
				var_f31 = temp_f0;
			}
			temp_r29 = (u8*)var_r16 + M2C_FIELD(lbl_8042AC68, s32*, 0xBC);
			temp_r15 = (u8*)var_r16 + M2C_FIELD(lbl_8042AC68, s32*, 0xC8);
			spCC     = (u8*)var_r16 + M2C_FIELD(lbl_8042AC68, s32*, 0xCC);
			temp_r28 = (u8*)var_r16 + M2C_FIELD(lbl_8042AC68, s32*, 0xC0);
			temp_r27 = (u8*)var_r16 + M2C_FIELD(lbl_8042AC68, s32*, 0xC4);
			spF0     = (u8*)var_r16 + M2C_FIELD(lbl_8042AC68, s32*, 0xD0);
			if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xC8) >= 0) {
				M2C_FIELD(temp_r15, f32*, 0) = (f32)((temp_f26 * M2C_FIELD(spF4, f32*, 0x10))
				    + M2C_FIELD(temp_r15, f32*, 0));
				M2C_FIELD(temp_r15, f32*, 4) = (f32)((temp_f26 * M2C_FIELD(spF4, f32*, 0x14))
				    + M2C_FIELD(temp_r15, f32*, 4));
				M2C_FIELD(temp_r15, f32*, 8) = (f32)((temp_f26 * M2C_FIELD(spF4, f32*, 0x18))
				    + M2C_FIELD(temp_r15, f32*, 8));
			}
			if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xB4) >= 0) {
				temp_r3_2                     = (u8*)var_r16 + M2C_FIELD(lbl_8042AC68, s32*, 0xB4);
				M2C_FIELD(temp_r3_2, f32*, 0) = (f32)((temp_f26 * M2C_FIELD(temp_r15, f32*, 0))
				    + M2C_FIELD(temp_r3_2, f32*, 0));
				M2C_FIELD(temp_r3_2, f32*, 4) = (f32)((temp_f26 * M2C_FIELD(temp_r15, f32*, 4))
				    + M2C_FIELD(temp_r3_2, f32*, 4));
				M2C_FIELD(temp_r3_2, f32*, 8) = (f32)((temp_f26 * M2C_FIELD(temp_r15, f32*, 8))
				    + M2C_FIELD(temp_r3_2, f32*, 8));
			}
			if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xC4) >= 0) {
				var_f30                         = M2C_FIELD(temp_r27, f32*, 0x10);
				var_f29                         = M2C_FIELD(temp_r27, f32*, 0x14);
				M2C_FIELD(temp_r27, f32*, 0x10) = (f32)((var_f31 * M2C_FIELD(temp_r27, f32*, 8))
				    + M2C_FIELD(temp_r27, f32*, 0));
				M2C_FIELD(temp_r27, f32*, 0x14) = (f32)((var_f31 * M2C_FIELD(temp_r27, f32*, 0xC))
				    + M2C_FIELD(temp_r27, f32*, 4));
			}
			if (var_r16 != var_r14) {
				memcpy(var_r14, var_r16, spF8);
			}
			if (var_r30 != NULL) {
				if (M2C_FIELD(var_r30, s32*, 0) & M2C_FIELD(var_r30, s32*, 0x10) & 1) {
					if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xC8) >= 0) {
						M2C_FIELD(var_r23, f32*, 0)
						    = (f32)((temp_f26 * M2C_FIELD(temp_r15, f32*, 0))
						        + M2C_FIELD(var_r24, f32*, 0));
						M2C_FIELD(var_r23, f32*, 4)
						    = (f32)((temp_f26 * M2C_FIELD(temp_r15, f32*, 4))
						        + M2C_FIELD(var_r24, f32*, 4));
						M2C_FIELD(var_r23, f32*, 8)
						    = (f32)((temp_f26 * M2C_FIELD(temp_r15, f32*, 8))
						        + M2C_FIELD(var_r24, f32*, 8));
						temp_f3   = M2C_FIELD(var_r23, f32*, 4) - sp20;
						temp_f1_2 = M2C_FIELD(var_r23, f32*, 0) - sp1C;
						temp_f2   = M2C_FIELD(var_r23, f32*, 8) - sp24;
						temp_f0_2
						    = (temp_f2 * temp_f2) + ((temp_f1_2 * temp_f1_2) + (temp_f3 * temp_f3));
						if (var_f25 > temp_f0_2) {

						} else {
							var_f25 = temp_f0_2;
						}
					}
					var_r23 += spE0;
				}
				if (M2C_FIELD(var_r30, s32*, 0) & M2C_FIELD(var_r30, s32*, 0x10) & 8) {
					if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xC4) >= 0) {
						if (lbl_80430268 != var_f30) {
							var_f30 = M2C_FIELD(temp_r27, f32*, 0x10) / var_f30;
						} else {
							var_f30 = lbl_8043026C;
						}
						if (lbl_80430268 != var_f29) {
							var_f29 = M2C_FIELD(temp_r27, f32*, 0x14) / var_f29;
						} else {
							var_f29 = lbl_8043026C;
						}
					}
					if (((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xCC) >= 0) || (spC8 != NULL)) {
						sp10                           = M2C_FIELD(var_r24, f32*, 0x30);
						M2C_FIELD(var_r24, f32*, 0x30) = (f32)lbl_80430268;
						sp14                           = M2C_FIELD(var_r24, f32*, 0x34);
						M2C_FIELD(var_r24, f32*, 0x34) = (f32)lbl_80430268;
						sp18                           = M2C_FIELD(var_r24, f32*, 0x38);
						M2C_FIELD(var_r24, f32*, 0x38) = (f32)lbl_80430268;
						if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xC4) >= 0) {
							M2C_FIELD(var_r24, f32*, 0)
							    = (f32)(M2C_FIELD(var_r24, f32*, 0) * var_f30);
							M2C_FIELD(var_r24, f32*, 4)
							    = (f32)(M2C_FIELD(var_r24, f32*, 4) * var_f30);
							M2C_FIELD(var_r24, f32*, 8)
							    = (f32)(M2C_FIELD(var_r24, f32*, 8) * var_f30);
							M2C_FIELD(var_r24, f32*, 0x10)
							    = (f32)(M2C_FIELD(var_r24, f32*, 0x10) * var_f29);
							M2C_FIELD(var_r24, f32*, 0x14)
							    = (f32)(M2C_FIELD(var_r24, f32*, 0x14) * var_f29);
							M2C_FIELD(var_r24, f32*, 0x18)
							    = (f32)(M2C_FIELD(var_r24, f32*, 0x18) * var_f29);
						}
						if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xCC) >= 0) {
							fn_80195674(&sp68, var_r24, spCC);
							M2C_FIELD(var_r23, s32*, 0)    = sp68;
							M2C_FIELD(var_r23, s32*, 4)    = sp6C;
							M2C_FIELD(var_r23, s32*, 8)    = sp70;
							M2C_FIELD(var_r23, s32*, 0xC)  = sp74;
							M2C_FIELD(var_r23, s32*, 0x10) = sp78;
							M2C_FIELD(var_r23, s32*, 0x14) = sp7C;
							M2C_FIELD(var_r23, s32*, 0x18) = sp80;
							M2C_FIELD(var_r23, s32*, 0x1C) = sp84;
							M2C_FIELD(var_r23, s32*, 0x20) = sp88;
							M2C_FIELD(var_r23, s32*, 0x24) = sp8C;
							M2C_FIELD(var_r23, s32*, 0x28) = sp90;
							M2C_FIELD(var_r23, s32*, 0x2C) = sp94;
							M2C_FIELD(var_r23, f32*, 0x30) = sp98;
							M2C_FIELD(var_r23, f32*, 0x34) = sp9C;
							M2C_FIELD(var_r23, f32*, 0x38) = spA0;
							M2C_FIELD(var_r23, s32*, 0x3C) = spA4;
						} else {
							fn_80195674(&sp28, var_r24, spC8);
							M2C_FIELD(var_r23, s32*, 0)    = sp28;
							M2C_FIELD(var_r23, s32*, 4)    = sp2C;
							M2C_FIELD(var_r23, s32*, 8)    = sp30;
							M2C_FIELD(var_r23, s32*, 0xC)  = sp34;
							M2C_FIELD(var_r23, s32*, 0x10) = sp38;
							M2C_FIELD(var_r23, s32*, 0x14) = sp3C;
							M2C_FIELD(var_r23, s32*, 0x18) = sp40;
							M2C_FIELD(var_r23, s32*, 0x1C) = sp44;
							M2C_FIELD(var_r23, s32*, 0x20) = sp48;
							M2C_FIELD(var_r23, s32*, 0x24) = sp4C;
							M2C_FIELD(var_r23, s32*, 0x28) = sp50;
							M2C_FIELD(var_r23, s32*, 0x2C) = sp54;
							M2C_FIELD(var_r23, f32*, 0x30) = sp58;
							M2C_FIELD(var_r23, f32*, 0x34) = sp5C;
							M2C_FIELD(var_r23, f32*, 0x38) = sp60;
							M2C_FIELD(var_r23, s32*, 0x3C) = sp64;
						}
						M2C_FIELD(var_r23, f32*, 0x30) = (f32)(M2C_FIELD(var_r23, f32*, 0x30)
						    + ((temp_f26 * M2C_FIELD(temp_r15, f32*, 0)) + sp10));
						M2C_FIELD(var_r23, f32*, 0x34) = (f32)(M2C_FIELD(var_r23, f32*, 0x34)
						    + ((temp_f26 * M2C_FIELD(temp_r15, f32*, 4)) + sp14));
						M2C_FIELD(var_r23, f32*, 0x38) = (f32)(M2C_FIELD(var_r23, f32*, 0x38)
						    + ((temp_f26 * M2C_FIELD(temp_r15, f32*, 8)) + sp18));
					} else {
						if (var_r23 != var_r24) {
							M2C_STRUCT_COPY(var_r23, var_r24, 0xC);
							M2C_STRUCT_COPY(var_r23, var_r24, 0xC);
							M2C_STRUCT_COPY(var_r23, var_r24, 0xC);
							M2C_FIELD(var_r23, s32*, 0xC) = (s32)M2C_FIELD(var_r24, s32*, 0xC);
						}
						sp10 = M2C_FIELD(var_r24, f32*, 0x30);
						sp14 = M2C_FIELD(var_r24, f32*, 0x34);
						sp18 = M2C_FIELD(var_r24, f32*, 0x38);
						if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xC4) >= 0) {
							M2C_FIELD(var_r24, f32*, 0)
							    = (f32)(M2C_FIELD(var_r24, f32*, 0) * var_f30);
							M2C_FIELD(var_r24, f32*, 4)
							    = (f32)(M2C_FIELD(var_r24, f32*, 4) * var_f30);
							M2C_FIELD(var_r24, f32*, 8)
							    = (f32)(M2C_FIELD(var_r24, f32*, 8) * var_f30);
							M2C_FIELD(var_r24, f32*, 0x10)
							    = (f32)(M2C_FIELD(var_r24, f32*, 0x10) * var_f29);
							M2C_FIELD(var_r24, f32*, 0x14)
							    = (f32)(M2C_FIELD(var_r24, f32*, 0x14) * var_f29);
							M2C_FIELD(var_r24, f32*, 0x18)
							    = (f32)(M2C_FIELD(var_r24, f32*, 0x18) * var_f29);
						}
						M2C_FIELD(var_r23, f32*, 0x30) = (f32)(M2C_FIELD(var_r23, f32*, 0x30)
						    + ((temp_f26 * M2C_FIELD(temp_r15, f32*, 0)) + sp10));
						M2C_FIELD(var_r23, f32*, 0x34) = (f32)(M2C_FIELD(var_r23, f32*, 0x34)
						    + ((temp_f26 * M2C_FIELD(temp_r15, f32*, 4)) + sp14));
						M2C_FIELD(var_r23, f32*, 0x38) = (f32)(M2C_FIELD(var_r23, f32*, 0x38)
						    + ((temp_f26 * M2C_FIELD(temp_r15, f32*, 8)) + sp18));
					}
					temp_f3_2 = M2C_FIELD(var_r23, f32*, 0x34) - sp20;
					temp_f4   = M2C_FIELD(var_r23, f32*, 0x38) - sp24;
					temp_f1_3 = M2C_FIELD(var_r23, f32*, 0x30) - sp1C;
					temp_f0_3
					    = (temp_f4 * temp_f4) + ((temp_f1_3 * temp_f1_3) + (temp_f3_2 * temp_f3_2));
					if (var_f25 > temp_f0_3) {

					} else {
						var_f25 = temp_f0_3;
					}
					var_r23 += spE0;
				}
				if (M2C_FIELD(var_r30, s32*, 0) & M2C_FIELD(var_r30, s32*, 0x10) & 4) {
					if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xC4) >= 0) {
						M2C_FIELD(var_r19, f32*, 0) = (f32)((var_f31 * M2C_FIELD(temp_r27, f32*, 8))
						    + M2C_FIELD(temp_r27, f32*, 0));
						M2C_FIELD(var_r19, f32*, 4)
						    = (f32)((var_f31 * M2C_FIELD(temp_r27, f32*, 0xC))
						        + M2C_FIELD(temp_r27, f32*, 4));
					} else if ((u32)var_r19 != var_r20) {
						M2C_STRUCT_COPY(var_r19, var_r20, 8);
					}
					var_r19 += spD8;
				}
				if (M2C_FIELD(var_r30, s32*, 0) & M2C_FIELD(var_r30, s32*, 0x10) & 2) {
					if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xBC) >= 0) {
						M2C_FIELD(var_r25, s8*, 0)
						    = (s8)((var_f31 * M2C_FIELD(temp_r29, f32*, 0x10))
						        + M2C_FIELD(temp_r29, f32*, 0));
						M2C_FIELD(var_r25, s8*, 1)
						    = (s8)((var_f31 * M2C_FIELD(temp_r29, f32*, 0x14))
						        + M2C_FIELD(temp_r29, f32*, 4));
						M2C_FIELD(var_r25, s8*, 2)
						    = (s8)((var_f31 * M2C_FIELD(temp_r29, f32*, 0x18))
						        + M2C_FIELD(temp_r29, f32*, 8));
						M2C_FIELD(var_r25, s8*, 3)
						    = (s8)((var_f31 * M2C_FIELD(temp_r29, f32*, 0x1C))
						        + M2C_FIELD(temp_r29, f32*, 0xC));
					} else if ((u32)var_r25 != (u32)var_r26) {
						M2C_FIELD(var_r25, s8*, 0) = (s32)*var_r26;
					}
					var_r25 += spE4;
				}
				if (M2C_FIELD(var_r30, s32*, 0) & M2C_FIELD(var_r30, s32*, 0x10) & 0x80) {
					if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xC0) >= 0) {
						M2C_FIELD(var_r21, f32*, 0)
						    = (f32)((var_f31 * M2C_FIELD(temp_r28, f32*, 0x10))
						        + M2C_FIELD(temp_r28, f32*, 0));
						M2C_FIELD(var_r21, f32*, 4)
						    = (f32)((var_f31 * M2C_FIELD(temp_r28, f32*, 0x14))
						        + M2C_FIELD(temp_r28, f32*, 4));
						M2C_FIELD(var_r21, f32*, 8)
						    = (f32)((var_f31 * M2C_FIELD(temp_r28, f32*, 0x18))
						        + M2C_FIELD(temp_r28, f32*, 8));
						M2C_FIELD(var_r21, f32*, 0xC)
						    = (f32)((var_f31 * M2C_FIELD(temp_r28, f32*, 0x1C))
						        + M2C_FIELD(temp_r28, f32*, 0xC));
					} else if ((u32)var_r21 != var_r22) {
						M2C_STRUCT_COPY(var_r21, var_r22, 0x10);
					}
					var_r21 += spDC;
				}
				if (M2C_FIELD(var_r30, s32*, 0) & M2C_FIELD(var_r30, s32*, 0x10) & 0x20) {
					if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xD0) >= 0) {
						*var_r17 = (var_f31 * M2C_FIELD(spF0, f32*, 4)) + M2C_FIELD(spF0, f32*, 0);
					} else if (var_r17 != var_r18) {
						*var_r17 = *var_r18;
					}
					var_r17 += spD4;
				}
			}
			spE8 += 1;
			var_r14 += spD0;
		}
		var_r16 += spD0;
		var_r24 += spE0;
		var_r26 += spE4;
		var_r22 += spDC;
		var_r20 += spD8;
		var_r18 += spD4;
		goto loop_103;
	}
	M2C_FIELD(spC, s32*, 8) = spE8;
	if (var_r30 != NULL) {
		var_r3_2                    = 0;
		M2C_FIELD(var_r30, s32*, 8) = (s32)(M2C_FIELD(var_r30, s32*, 8) + spE8);
		if (M2C_FIELD(var_r30, s32*, 0) & 1) {
			var_r3_2                         = 1;
			*M2C_FIELD(var_r30, u8***, 0x1C) = var_r24;
			*M2C_FIELD(var_r30, u8***, 0x20) = var_r23;
		}
		if (M2C_FIELD(var_r30, s32*, 0) & 2) {
			temp_r0_2 = var_r3_2 * 4;
			var_r3_2 += 1;
			*(s32**)((u8*)M2C_FIELD(var_r30, u8***, 0x1C) + temp_r0_2) = var_r26;
			*(u8**)((u8*)M2C_FIELD(var_r30, u8***, 0x20) + temp_r0_2)  = var_r25;
		}
		if (M2C_FIELD(var_r30, s32*, 0) & 4) {
			temp_r0_3 = var_r3_2 * 4;
			var_r3_2 += 1;
			*(u32*)((u8*)M2C_FIELD(var_r30, u8***, 0x1C) + temp_r0_3) = var_r20;
			*(u8**)((u8*)M2C_FIELD(var_r30, u8***, 0x20) + temp_r0_3) = var_r19;
		}
		if (M2C_FIELD(var_r30, s32*, 0) & 8) {
			temp_r0_4 = var_r3_2 * 4;
			var_r3_2 += 1;
			*(u8**)((u8*)M2C_FIELD(var_r30, u8***, 0x1C) + temp_r0_4) = var_r24;
			*(u8**)((u8*)M2C_FIELD(var_r30, u8***, 0x20) + temp_r0_4) = var_r23;
		}
		if (M2C_FIELD(var_r30, s32*, 0) & 0x20) {
			temp_r0_5 = var_r3_2 * 4;
			var_r3_2 += 1;
			*(f32**)((u8*)M2C_FIELD(var_r30, u8***, 0x1C) + temp_r0_5) = var_r18;
			*(f32**)((u8*)M2C_FIELD(var_r30, u8***, 0x20) + temp_r0_5) = var_r17;
		}
		if (M2C_FIELD(var_r30, s32*, 0) & 0x80) {
			temp_r0_6                                                 = var_r3_2 * 4;
			*(u32*)((u8*)M2C_FIELD(var_r30, u8***, 0x1C) + temp_r0_6) = var_r22;
			*(u8**)((u8*)M2C_FIELD(var_r30, u8***, 0x20) + temp_r0_6) = var_r21;
		}
	}
	if (var_f25 > M2C_FIELD(sp8, f32*, 0x24)) {
		M2C_FIELD(sp8, f32*, 0x24) = var_f25;
	}
	return spC;
}

u8* fn_80236AE4(u8* arg1)
{
	s32 sp90;
	M2C_UNK* sp8C;
	M2C_UNK* sp88;
	M2C_UNK* sp84;
	M2C_UNK* sp80;
	s32 sp7C;
	s32 sp78;
	M2C_UNK* sp74;
	s32 sp70;
	s32 sp6C;
	s32 sp68;
	s32 sp64;
	s32 sp60;
	f32 sp2C;
	f32 sp28;
	f32 sp24;
	f32 sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	u8* sp8;
	M2C_UNK* temp_r3_2;
	M2C_UNK* temp_r5;
	f32* var_r26;
	f32 temp_f0;
	f32 temp_f0_2;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f2;
	f32 temp_f2_2;
	f32 temp_f2_3;
	f32 temp_f4;
	f32 temp_f4_2;
	f32 temp_f4_3;
	f32 temp_f6;
	f32 var_f21;
	f32 var_f22;
	f32 var_f23;
	f32 var_f24;
	f32 var_f25;
	f32 var_f26;
	f32 var_f27;
	f32 var_f28;
	f32 var_f29;
	f32 var_f30;
	f32 var_f31;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 temp_r0_4;
	s32 temp_r0_5;
	s32 temp_r0_6;
	s32 temp_r0_7;
	s32 temp_r0_8;
	s32 temp_r3;
	s32 temp_r3_3;
	s32 temp_r4;
	s32 temp_r5_13;
	s32 temp_r5_16;
	s32 temp_r5_4;
	s32 temp_r6;
	s32 temp_r6_2;
	s32 temp_r6_3;
	s32 temp_r6_4;
	s32 var_r14_2;
	s32 var_r3;
	s32 var_r3_2;
	u32 temp_r15;
	u32 temp_r15_2;
	u32 temp_r31;
	u32 temp_r3_4;
	u32 temp_r3_5;
	u32 temp_r5_10;
	u32 temp_r5_11;
	u32 temp_r5_12;
	u32 temp_r5_14;
	u32 temp_r5_15;
	u32 temp_r5_2;
	u32 temp_r5_3;
	u32 temp_r5_5;
	u32 temp_r5_6;
	u32 temp_r5_7;
	u32 temp_r5_8;
	u32 temp_r5_9;
	u32 temp_r6_10;
	u32 temp_r6_11;
	u32 temp_r6_12;
	u32 temp_r6_13;
	u32 temp_r6_14;
	u32 temp_r6_5;
	u32 temp_r6_7;
	u32 temp_r6_8;
	u32 temp_r6_9;
	u32 var_r15;
	u8* temp_r17;
	u8* temp_r25;
	u8* temp_r3_6;
	u8* temp_r3_7;
	u8* temp_r4_2;
	u8* temp_r6_6;
	u8* temp_r7;
	u8* temp_r7_2;
	u8* var_r14;
	u8* var_r18;
	u8* var_r19;
	u8* var_r20;
	u8* var_r21;
	u8* var_r22;
	u8* var_r23;
	u8* var_r24;
	u8* var_r27;
	u8* var_r28;
	u8* var_r29;
	u8* var_r30;

	var_f22  = 0.0f;
	var_f23  = 0.0f;
	var_f24  = 0.0f;
	var_f25  = 0.0f;
	var_f26  = 0.0f;
	var_f27  = 0.0f;
	var_f28  = 0.0f;
	var_f29  = 0.0f;
	sp8      = arg1;
	var_r30  = NULL;
	sp80     = lbl_8042AC68;
	var_r29  = NULL;
	var_r28  = NULL;
	var_r27  = NULL;
	var_r26  = NULL;
	temp_r25 = sp8 + M2C_FIELD(lbl_8042AC68, s32*, 0x98);
	sp70     = 0;
	var_r23  = NULL;
	var_r22  = NULL;
	sp6C     = 0;
	var_r21  = NULL;
	var_r20  = NULL;
	sp68     = 0;
	var_r19  = NULL;
	var_r14  = NULL;
	sp64     = 0;
	var_r24  = NULL;
	sp60     = 0;
	if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0x9C) >= 0) {
		var_r23 = sp8 + M2C_FIELD(lbl_8042AC68, s32*, 0x9C);
	}
	sp84 = lbl_8042AC68;
	if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xA0) >= 0) {
		var_r22 = sp8 + M2C_FIELD(lbl_8042AC68, s32*, 0xA0);
	}
	if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xA8) >= 0) {
		var_r24 = sp8 + M2C_FIELD(lbl_8042AC68, s32*, 0xA8);
	}
	if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xAC) >= 0) {
		var_r21 = sp8 + M2C_FIELD(lbl_8042AC68, s32*, 0xAC);
	}
	sp88 = lbl_8042AC68;
	if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xA4) >= 0) {
		var_r20 = sp8 + M2C_FIELD(lbl_8042AC68, s32*, 0xA4);
	}
	sp8C = lbl_8042AC68;
	if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xB0) >= 0) {
		var_r19 = sp8 + M2C_FIELD(lbl_8042AC68, s32*, 0xB0);
	}
	M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
	if (M2C_FIELD(temp_r25, f32*, 8) == M2C_FIELD(temp_r25, f32*, 0x40)) {
		var_r15 = (M2C_FIELD(temp_r25, u32*, 0) * 0x0BB38435) + 0x3619636B;
		sp74    = NULL;
		temp_r0 = M2C_FIELD(temp_r25, s32*, 0x44)
		    + (s32)(((lbl_80430270 * (lbl_80430274 * (f32)var_r15)) - lbl_8043026C)
		        * (f32)M2C_FIELD(temp_r25, s32*, 0x48));
		sp7C = temp_r0;
		if (var_r24 != NULL) {
			temp_r4 = M2C_FIELD(var_r24, s32*, 0xC);
			temp_r3 = M2C_FIELD(sp8, s32*, 0x10);
			if ((s32)(temp_r3 + temp_r0) > temp_r4) {
				sp7C = temp_r4 - temp_r3;
			}
		}
		if (sp7C > 0) {
			temp_r5 = M2C_FIELD(sp8, M2C_UNK**, 0x20);
			if ((temp_r5 != NULL)
			    && ((s32)(M2C_FIELD(temp_r5, s32*, 8) + sp7C)
			        <= (s32)M2C_FIELD(temp_r5, s32*, 0xC))) {
				sp74 = temp_r5;
			}
		}
		if ((sp7C > 0) && (sp74 == NULL)) {
			temp_r3_2 = fn_80232F98(sp8);
			sp74      = temp_r3_2;
			if (temp_r3_2 != NULL) {
				M2C_FIELD(temp_r3_2, s32*, 0x10) = 0;
				M2C_FIELD(temp_r3_2, s32*, 8)    = 0;
				temp_r3_3                        = M2C_FIELD(temp_r3_2, s32*, 0xC);
				if (sp7C > temp_r3_3) {
					sp7C = temp_r3_3;
				}
			}
		}
		if (sp7C <= 0) {
			return sp8;
		}
		if (sp74 != NULL) {
			if (var_r24 != NULL) {
				temp_r0_2 = M2C_FIELD(var_r24, s32*, 0);
				sp70      = 0;
				var_r3    = 0;
				var_r30   = NULL;
				if (temp_r0_2 & 1) {
					var_r3  = 1;
					var_r30 = *M2C_FIELD(var_r24, u8***, 0x20);
					sp70    = *M2C_FIELD(var_r24, s32**, 0x24);
				}
				var_r29 = NULL;
				sp6C    = 0;
				if (temp_r0_2 & 2) {
					temp_r6 = var_r3 * 4;
					var_r3 += 1;
					var_r29 = *(u8**)((u8*)M2C_FIELD(var_r24, u8***, 0x20) + temp_r6);
					sp6C    = *(s32*)((u8*)M2C_FIELD(var_r24, s32**, 0x24) + temp_r6);
				}
				var_r27 = NULL;
				sp64    = 0;
				if (temp_r0_2 & 4) {
					temp_r6_2 = var_r3 * 4;
					var_r3 += 1;
					var_r27 = *(u8**)((u8*)M2C_FIELD(var_r24, u8***, 0x20) + temp_r6_2);
					sp64    = *(s32*)((u8*)M2C_FIELD(var_r24, s32**, 0x24) + temp_r6_2);
				}
				if (temp_r0_2 & 8) {
					temp_r6_3 = var_r3 * 4;
					var_r3 += 1;
					var_r30 = *(u8**)((u8*)M2C_FIELD(var_r24, u8***, 0x20) + temp_r6_3);
					sp70    = *(s32*)((u8*)M2C_FIELD(var_r24, s32**, 0x24) + temp_r6_3);
				}
				var_r26 = NULL;
				sp60    = 0;
				if (temp_r0_2 & 0x20) {
					temp_r6_4 = var_r3 * 4;
					var_r3 += 1;
					var_r26 = *(f32**)((u8*)M2C_FIELD(var_r24, u8***, 0x20) + temp_r6_4);
					sp60    = *(s32*)((u8*)M2C_FIELD(var_r24, s32**, 0x24) + temp_r6_4);
				}
				var_r28 = NULL;
				sp68    = 0;
				if (temp_r0_2 & 0x80) {
					temp_r0_3 = var_r3 * 4;
					var_r28   = *(u8**)((u8*)M2C_FIELD(var_r24, u8***, 0x20) + temp_r0_3);
					sp68      = *(s32*)((u8*)M2C_FIELD(var_r24, s32**, 0x24) + temp_r0_3);
				}
			}
			temp_r31  = M2C_FIELD(temp_r25, u32*, 0xA8);
			var_r14_2 = 0;
			temp_r0_4 = M2C_FIELD(M2C_FIELD(sp8, u8**, 0x18), s32*, 0xC);
			sp78      = temp_r0_4;
			sp90      = 0x0BB38435;
			var_r18   = (u8*)sp74
			    + (M2C_FIELD(sp74, s32*, 0x14) + (M2C_FIELD(sp74, s32*, 8) * temp_r0_4));
		loop_84:
			if (var_r14_2 < sp7C) {
				M2C_FIELD(var_r18, f32*, 4) = (f32)lbl_80430268;
				var_r15                     = (var_r15 * sp90) + 0x3619636B;
				M2C_FIELD(var_r18, f32*, 8)
				    = (f32)((((lbl_80430270 * (lbl_80430274 * (f32)var_r15)) - lbl_8043026C)
				                * M2C_FIELD(temp_r25, f32*, 0x58))
				        + M2C_FIELD(temp_r25, f32*, 0x54));
				M2C_FIELD(var_r18, f32*, 0xC) = (f32)(lbl_8043026C / M2C_FIELD(var_r18, f32*, 8));
				if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xC8) >= 0) {
					temp_r17  = var_r18 + M2C_FIELD(lbl_8042AC68, s32*, 0xC8);
					temp_r5_2 = (var_r15 * 0x0BB38435) + 0x3619636B;
					temp_r5_3 = (temp_r5_2 * 0x0BB38435) + 0x3619636B;
					temp_r5_4 = temp_r5_3 * 0x0BB38435;
					temp_r15  = temp_r5_4 + 0x3619636B;
					sp24      = (((lbl_80430270 * (lbl_80430274 * (f32)temp_r5_2)) - lbl_8043026C)
					                * M2C_FIELD(temp_r25, f32*, 0x68))
					    + M2C_FIELD(temp_r25, f32*, 0x5C);
					temp_f4 = (lbl_80430270 * (lbl_80430274 * (f32)temp_r5_3)) - lbl_8043026C;
					sp28    = (temp_f4 * M2C_FIELD(temp_r25, f32*, 0x6C))
					    + M2C_FIELD(temp_r25, f32*, 0x60);
					temp_f2 = (lbl_80430270 * (lbl_80430274 * (f32)temp_r15)) - lbl_8043026C;
					temp_f1 = M2C_FIELD(temp_r25, f32*, 0x70);
					sp2C    = (temp_f2 * temp_f1) + M2C_FIELD(temp_r25, f32*, 0x64);
					fn_801990E0(&sp24, &sp24, temp_r5_4, 0x0BB38435, temp_f1, temp_f2, lbl_8043026C,
					    temp_f4, lbl_80430274, lbl_80430270);
					if (temp_r31 != 0U) {
						fn_8019947C(&sp24, &sp24, 1, temp_r31);
					}
					temp_r3_4 = (temp_r15 * 0x0BB38435) + 0x3619636B;
					temp_r5_5 = (temp_r3_4 * 0x0BB38435) + 0x3619636B;
					temp_f6   = (lbl_80430270 * (lbl_80430274 * (f32)temp_r3_4)) - lbl_8043026C;
					temp_r3_5 = (temp_r5_5 * 0x0BB38435) + 0x3619636B;
					M2C_FIELD(temp_r17, f32*, 0) = (f32)(sp24
					    * ((temp_f6 * M2C_FIELD(temp_r25, f32*, 0x50))
					        + M2C_FIELD(temp_r25, f32*, 0x4C)));
					var_r15                      = (temp_r3_5 * 0x0BB38435) + 0x3619636B;
					M2C_FIELD(temp_r17, f32*, 4) = (f32)(sp28
					    * ((temp_f6 * M2C_FIELD(temp_r25, f32*, 0x50))
					        + M2C_FIELD(temp_r25, f32*, 0x4C)));
					M2C_FIELD(temp_r17, f32*, 8) = (f32)(sp2C
					    * ((temp_f6 * M2C_FIELD(temp_r25, f32*, 0x50))
					        + M2C_FIELD(temp_r25, f32*, 0x4C)));
					sp24 = (((lbl_80430270 * (lbl_80430274 * (f32)temp_r5_5)) - lbl_8043026C)
					           * M2C_FIELD(temp_r25, f32*, 0x28))
					    + M2C_FIELD(temp_r25, f32*, 0x1C);
					sp28 = (((lbl_80430270 * (lbl_80430274 * (f32)temp_r3_5)) - lbl_8043026C)
					           * M2C_FIELD(temp_r25, f32*, 0x2C))
					    + M2C_FIELD(temp_r25, f32*, 0x20);
					sp2C = (((lbl_80430270 * (lbl_80430274 * (f32)var_r15)) - lbl_8043026C)
					           * M2C_FIELD(temp_r25, f32*, 0x30))
					    + M2C_FIELD(temp_r25, f32*, 0x24);
					if (temp_r31 != 0U) {
						fn_8019941C(&spC, &sp24, 1, temp_r31);
					}
				}
				if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xB4) >= 0) {
					temp_r3_6                     = var_r18 + M2C_FIELD(lbl_8042AC68, s32*, 0xB4);
					M2C_FIELD(temp_r3_6, f32*, 0) = spC;
					M2C_FIELD(temp_r3_6, f32*, 4) = sp10;
					M2C_FIELD(temp_r3_6, f32*, 8) = sp14;
				}
				if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xCC) >= 0) {
					temp_r3_7 = var_r18 + M2C_FIELD(lbl_8042AC68, s32*, 0xCC);
					M2C_FIELD(temp_r3_7, f32*, 0x28) = (f32)lbl_8043026C;
					M2C_FIELD(temp_r3_7, f32*, 0x14) = (f32)lbl_8043026C;
					M2C_FIELD(temp_r3_7, f32*, 0)    = (f32)lbl_8043026C;
					M2C_FIELD(temp_r3_7, f32*, 0x10) = (f32)lbl_80430268;
					M2C_FIELD(temp_r3_7, f32*, 8)    = (f32)lbl_80430268;
					M2C_FIELD(temp_r3_7, f32*, 4)    = (f32)lbl_80430268;
					M2C_FIELD(temp_r3_7, f32*, 0x24) = (f32)lbl_80430268;
					M2C_FIELD(temp_r3_7, f32*, 0x20) = (f32)lbl_80430268;
					M2C_FIELD(temp_r3_7, f32*, 0x18) = (f32)lbl_80430268;
					M2C_FIELD(temp_r3_7, f32*, 0x38) = (f32)lbl_80430268;
					M2C_FIELD(temp_r3_7, f32*, 0x34) = (f32)lbl_80430268;
					M2C_FIELD(temp_r3_7, f32*, 0x30) = (f32)lbl_80430268;
					M2C_FIELD(temp_r3_7, s32*, 0xC)
					    = (s32)(M2C_FIELD(temp_r3_7, s32*, 0xC) | 0x20000 | 3);
				}
				if ((s32)M2C_FIELD(sp88, s32*, 0xA4) >= 0) {
					temp_r6_5 = (var_r15 * 0x0BB38435) + 0x3619636B;
					temp_f0   = (f32)temp_r6_5;
					var_r15   = (temp_r6_5 * 0x0BB38435) + 0x3619636B;
					var_f31   = (((lbl_80430270 * (lbl_80430274 * temp_f0)) - lbl_8043026C)
					                * M2C_FIELD(var_r20, f32*, 8))
					    + M2C_FIELD(var_r20, f32*, 0);
					var_f30 = (((lbl_80430270 * (lbl_80430274 * (f32)var_r15)) - lbl_8043026C)
					              * M2C_FIELD(var_r20, f32*, 0xC))
					    + M2C_FIELD(var_r20, f32*, 4);
					if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xC4) >= 0) {
						temp_r6_6 = var_r18 + M2C_FIELD(lbl_8042AC68, s32*, 0xC4);
						M2C_FIELD(temp_r6_6, f32*, 0)    = var_f31;
						M2C_FIELD(temp_r6_6, f32*, 4)    = var_f30;
						M2C_FIELD(temp_r6_6, f32*, 0x10) = var_f31;
						temp_r5_6                        = (var_r15 * 0x0BB38435) + 0x3619636B;
						M2C_FIELD(temp_r6_6, f32*, 0x14) = var_f30;
						temp_f0_2                        = (f32)temp_r5_6;
						var_r15                          = (temp_r5_6 * 0x0BB38435) + 0x3619636B;
						M2C_FIELD(temp_r6_6, f32*, 8)
						    = (f32)(((((lbl_80430270 * (lbl_80430274 * temp_f0_2)) - lbl_8043026C)
						                 * M2C_FIELD(var_r20, f32*, 0x18))
						                + M2C_FIELD(var_r20, f32*, 0x10))
						        - M2C_FIELD(temp_r6_6, f32*, 0));
						M2C_FIELD(temp_r6_6, f32*, 0xC)
						    = (f32)(((((lbl_80430270 * (lbl_80430274 * (f32)var_r15))
						                  - lbl_8043026C)
						                 * M2C_FIELD(var_r20, f32*, 0x1C))
						                + M2C_FIELD(var_r20, f32*, 0x14))
						        - M2C_FIELD(temp_r6_6, f32*, 4));
					}
				} else {
					var_f31 = M2C_FIELD(temp_r25, f32*, 0x74);
					var_f30 = M2C_FIELD(temp_r25, f32*, 0x78);
				}
				if ((s32)M2C_FIELD(sp80, s32*, 0x9C) >= 0) {
					temp_r6_7 = (var_r15 * 0x0BB38435) + 0x3619636B;
					temp_r6_8 = (temp_r6_7 * 0x0BB38435) + 0x3619636B;
					temp_r6_9 = (temp_r6_8 * 0x0BB38435) + 0x3619636B;
					var_f29   = (((lbl_80430270 * (lbl_80430274 * (f32)temp_r6_7)) - lbl_8043026C)
					                * M2C_FIELD(var_r23, f32*, 0x10))
					    + M2C_FIELD(var_r23, f32*, 0);
					var_r15 = (temp_r6_9 * 0x0BB38435) + 0x3619636B;
					var_f28 = (((lbl_80430270 * (lbl_80430274 * (f32)temp_r6_8)) - lbl_8043026C)
					              * M2C_FIELD(var_r23, f32*, 0x14))
					    + M2C_FIELD(var_r23, f32*, 4);
					var_f27 = (((lbl_80430270 * (lbl_80430274 * (f32)temp_r6_9)) - lbl_8043026C)
					              * M2C_FIELD(var_r23, f32*, 0x18))
					    + M2C_FIELD(var_r23, f32*, 8);
					var_f26 = (((lbl_80430270 * (lbl_80430274 * (f32)var_r15)) - lbl_8043026C)
					              * M2C_FIELD(var_r23, f32*, 0x1C))
					    + M2C_FIELD(var_r23, f32*, 0xC);
					if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xBC) >= 0) {
						temp_r7                     = var_r18 + M2C_FIELD(lbl_8042AC68, s32*, 0xBC);
						M2C_FIELD(temp_r7, f32*, 0) = var_f29;
						M2C_FIELD(temp_r7, f32*, 4) = var_f28;
						M2C_FIELD(temp_r7, f32*, 8) = var_f27;
						temp_r5_7                   = (var_r15 * 0x0BB38435) + 0x3619636B;
						M2C_FIELD(temp_r7, f32*, 0xC) = var_f26;
						temp_r6_10                    = (temp_r5_7 * 0x0BB38435) + 0x3619636B;
						temp_r5_8                     = (temp_r6_10 * 0x0BB38435) + 0x3619636B;
						M2C_FIELD(temp_r7, f32*, 0x10)
						    = (f32)(((((lbl_80430270 * (lbl_80430274 * (f32)temp_r5_7))
						                  - lbl_8043026C)
						                 * M2C_FIELD(var_r23, f32*, 0x30))
						                + M2C_FIELD(var_r23, f32*, 0x20))
						        - M2C_FIELD(temp_r7, f32*, 0));
						var_r15 = (temp_r5_8 * 0x0BB38435) + 0x3619636B;
						M2C_FIELD(temp_r7, f32*, 0x14)
						    = (f32)(((((lbl_80430270 * (lbl_80430274 * (f32)temp_r6_10))
						                  - lbl_8043026C)
						                 * M2C_FIELD(var_r23, f32*, 0x34))
						                + M2C_FIELD(var_r23, f32*, 0x24))
						        - M2C_FIELD(temp_r7, f32*, 4));
						M2C_FIELD(temp_r7, f32*, 0x18)
						    = (f32)(((((lbl_80430270 * (lbl_80430274 * (f32)temp_r5_8))
						                  - lbl_8043026C)
						                 * M2C_FIELD(var_r23, f32*, 0x38))
						                + M2C_FIELD(var_r23, f32*, 0x28))
						        - M2C_FIELD(temp_r7, f32*, 8));
						M2C_FIELD(temp_r7, f32*, 0x1C)
						    = (f32)(((((lbl_80430270 * (lbl_80430274 * (f32)var_r15))
						                  - lbl_8043026C)
						                 * M2C_FIELD(var_r23, f32*, 0x3C))
						                + M2C_FIELD(var_r23, f32*, 0x2C))
						        - M2C_FIELD(temp_r7, f32*, 0xC));
					}
				}
				var_f21 = lbl_80430268;
				if ((s32)M2C_FIELD(sp8C, s32*, 0xB0) >= 0) {
					var_r15 = (var_r15 * 0x0BB38435) + 0x3619636B;
					var_f21 = (((lbl_80430270 * (lbl_80430274 * (f32)var_r15)) - lbl_8043026C)
					              * M2C_FIELD(var_r19, f32*, 4))
					    + M2C_FIELD(var_r19, f32*, 0);
					if ((var_f21 > lbl_80430278) || (var_f21 < lbl_8043027C)) {
						if (var_f21 > lbl_80430278) {
							var_f21 = (f32)((f64)var_f21 - lbl_80430280);
						}
						if (var_f21 < lbl_8043027C) {
							var_f21 = (f32)((f64)var_f21 + lbl_80430280);
						}
					}
					if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xD0) >= 0) {
						temp_r4_2 = var_r18 + M2C_FIELD(lbl_8042AC68, s32*, 0xD0);
						M2C_FIELD(temp_r4_2, f32*, 0) = var_f21;
						var_r15                       = (var_r15 * 0x0BB38435) + 0x3619636B;
						M2C_FIELD(temp_r4_2, f32*, 4)
						    = (f32)(((((lbl_80430270 * (lbl_80430274 * (f32)var_r15))
						                  - lbl_8043026C)
						                 * M2C_FIELD(var_r19, f32*, 0xC))
						                + M2C_FIELD(var_r19, f32*, 8))
						        - M2C_FIELD(temp_r4_2, f32*, 0));
					}
				}
				if ((s32)M2C_FIELD(sp84, s32*, 0xA0) >= 0) {
					temp_r6_11 = (var_r15 * 0x0BB38435) + 0x3619636B;
					temp_r6_12 = (temp_r6_11 * 0x0BB38435) + 0x3619636B;
					temp_r6_13 = (temp_r6_12 * 0x0BB38435) + 0x3619636B;
					var_f25    = (((lbl_80430270 * (lbl_80430274 * (f32)temp_r6_11)) - lbl_8043026C)
					                 * M2C_FIELD(var_r22, f32*, 8))
					    + M2C_FIELD(var_r22, f32*, 0);
					var_r15 = (temp_r6_13 * 0x0BB38435) + 0x3619636B;
					var_f24 = (((lbl_80430270 * (lbl_80430274 * (f32)temp_r6_12)) - lbl_8043026C)
					              * M2C_FIELD(var_r22, f32*, 0xC))
					    + M2C_FIELD(var_r22, f32*, 4);
					var_f23 = (((lbl_80430270 * (lbl_80430274 * (f32)temp_r6_13)) - lbl_8043026C)
					              * M2C_FIELD(var_r22, f32*, 0x28))
					    + M2C_FIELD(var_r22, f32*, 0x20);
					var_f22 = (((lbl_80430270 * (lbl_80430274 * (f32)var_r15)) - lbl_8043026C)
					              * M2C_FIELD(var_r22, f32*, 0x2C))
					    + M2C_FIELD(var_r22, f32*, 0x24);
					if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xC0) >= 0) {
						temp_r7_2 = var_r18 + M2C_FIELD(lbl_8042AC68, s32*, 0xC0);
						M2C_FIELD(temp_r7_2, f32*, 0)   = var_f25;
						M2C_FIELD(temp_r7_2, f32*, 4)   = var_f24;
						M2C_FIELD(temp_r7_2, f32*, 8)   = var_f23;
						temp_r5_9                       = (var_r15 * 0x0BB38435) + 0x3619636B;
						M2C_FIELD(temp_r7_2, f32*, 0xC) = var_f22;
						temp_r6_14                      = (temp_r5_9 * 0x0BB38435) + 0x3619636B;
						temp_r5_10                      = (temp_r6_14 * 0x0BB38435) + 0x3619636B;
						M2C_FIELD(temp_r7_2, f32*, 0x10)
						    = (f32)(((((lbl_80430270 * (lbl_80430274 * (f32)temp_r5_9))
						                  - lbl_8043026C)
						                 * M2C_FIELD(var_r22, f32*, 0x18))
						                + M2C_FIELD(var_r22, f32*, 0x10))
						        - M2C_FIELD(temp_r7_2, f32*, 0));
						var_r15 = (temp_r5_10 * 0x0BB38435) + 0x3619636B;
						M2C_FIELD(temp_r7_2, f32*, 0x14)
						    = (f32)(((((lbl_80430270 * (lbl_80430274 * (f32)temp_r6_14))
						                  - lbl_8043026C)
						                 * M2C_FIELD(var_r22, f32*, 0x1C))
						                + M2C_FIELD(var_r22, f32*, 0x14))
						        - M2C_FIELD(temp_r7_2, f32*, 4));
						M2C_FIELD(temp_r7_2, f32*, 0x18)
						    = (f32)(((((lbl_80430270 * (lbl_80430274 * (f32)temp_r5_10))
						                  - lbl_8043026C)
						                 * M2C_FIELD(var_r22, f32*, 0x38))
						                + M2C_FIELD(var_r22, f32*, 0x30))
						        - M2C_FIELD(temp_r7_2, f32*, 8));
						M2C_FIELD(temp_r7_2, f32*, 0x1C)
						    = (f32)(((((lbl_80430270 * (lbl_80430274 * (f32)var_r15))
						                  - lbl_8043026C)
						                 * M2C_FIELD(var_r22, f32*, 0x3C))
						                + M2C_FIELD(var_r22, f32*, 0x34))
						        - M2C_FIELD(temp_r7_2, f32*, 0xC));
					}
				}
				if (var_r24 != NULL) {
					if (M2C_FIELD(var_r24, s32*, 0) & M2C_FIELD(var_r24, s32*, 0x14) & 1) {
						M2C_FIELD(var_r30, f32*, 0) = spC;
						M2C_FIELD(var_r30, f32*, 4) = sp10;
						M2C_FIELD(var_r30, f32*, 8) = sp14;
						var_r30 += sp70;
					}
					if (M2C_FIELD(var_r24, s32*, 0) & M2C_FIELD(var_r24, s32*, 0x14) & 8) {
						temp_r5_11 = (var_r15 * 0x0BB38435) + 0x3619636B;
						temp_r5_12 = (temp_r5_11 * 0x0BB38435) + 0x3619636B;
						temp_r5_13 = temp_r5_12 * 0x0BB38435;
						temp_r15_2 = temp_r5_13 + 0x3619636B;
						sp24 = (((lbl_80430270 * (lbl_80430274 * (f32)temp_r5_11)) - lbl_8043026C)
						           * M2C_FIELD(var_r21, f32*, 0x4C))
						    + M2C_FIELD(var_r21, f32*, 0x40);
						temp_f4_2
						    = (lbl_80430270 * (lbl_80430274 * (f32)temp_r5_12)) - lbl_8043026C;
						sp28 = (temp_f4_2 * M2C_FIELD(var_r21, f32*, 0x50))
						    + M2C_FIELD(var_r21, f32*, 0x44);
						temp_f2_2
						    = (lbl_80430270 * (lbl_80430274 * (f32)temp_r15_2)) - lbl_8043026C;
						temp_f1_2 = M2C_FIELD(var_r21, f32*, 0x54);
						sp2C      = (temp_f2_2 * temp_f1_2) + M2C_FIELD(var_r21, f32*, 0x48);
						fn_801990E0(&sp24, &sp24, temp_r5_13, 0x0BB38435, temp_f1_2, temp_f2_2,
						    lbl_8043026C, temp_f4_2, lbl_80430274, lbl_80430270);
						temp_r5_14 = (temp_r15_2 * 0x0BB38435) + 0x3619636B;
						temp_r5_15 = (temp_r5_14 * 0x0BB38435) + 0x3619636B;
						temp_r5_16 = temp_r5_15 * 0x0BB38435;
						var_r15    = temp_r5_16 + 0x3619636B;
						sp18 = (((lbl_80430270 * (lbl_80430274 * (f32)temp_r5_14)) - lbl_8043026C)
						           * M2C_FIELD(var_r21, f32*, 0x64))
						    + M2C_FIELD(var_r21, f32*, 0x58);
						temp_f4_3
						    = (lbl_80430270 * (lbl_80430274 * (f32)temp_r5_15)) - lbl_8043026C;
						sp1C = (temp_f4_3 * M2C_FIELD(var_r21, f32*, 0x68))
						    + M2C_FIELD(var_r21, f32*, 0x5C);
						temp_f2_3 = (lbl_80430270 * (lbl_80430274 * (f32)var_r15)) - lbl_8043026C;
						temp_f1_3 = M2C_FIELD(var_r21, f32*, 0x6C);
						sp20      = (temp_f2_3 * temp_f1_3) + M2C_FIELD(var_r21, f32*, 0x60);
						fn_801990E0(&sp18, &sp18, temp_r5_16, 0x0BB38435, temp_f1_3, temp_f2_3,
						    lbl_8043026C, temp_f4_3, lbl_80430274, lbl_80430270);
						M2C_FIELD(var_r30, f32*, 0x20) = sp24;
						M2C_FIELD(var_r30, f32*, 0x24) = sp28;
						M2C_FIELD(var_r30, f32*, 0x28) = sp2C;
						M2C_FIELD(var_r30, f32*, 0)    = (f32)((sp28 * sp20) - (sp2C * sp1C));
						M2C_FIELD(var_r30, f32*, 4)    = (f32)((sp2C * sp18) - (sp24 * sp20));
						M2C_FIELD(var_r30, f32*, 8)    = (f32)((sp24 * sp1C) - (sp28 * sp18));
						sp1C                           = M2C_FIELD(var_r30, f32*, 4);
						sp18                           = M2C_FIELD(var_r30, f32*, 0);
						sp20                           = M2C_FIELD(var_r30, f32*, 8);
						M2C_FIELD(var_r30, f32*, 0x10) = (f32)((sp1C * sp2C) - (sp20 * sp28));
						M2C_FIELD(var_r30, f32*, 0x14) = (f32)((sp20 * sp24) - (sp18 * sp2C));
						M2C_FIELD(var_r30, f32*, 0x18) = (f32)((sp18 * sp28) - (sp1C * sp24));
						M2C_FIELD(var_r30, f32*, 0) = (f32)(M2C_FIELD(var_r30, f32*, 0) * var_f31);
						M2C_FIELD(var_r30, f32*, 4) = (f32)(M2C_FIELD(var_r30, f32*, 4) * var_f31);
						M2C_FIELD(var_r30, f32*, 8) = (f32)(M2C_FIELD(var_r30, f32*, 8) * var_f31);
						M2C_FIELD(var_r30, f32*, 0x10)
						    = (f32)(M2C_FIELD(var_r30, f32*, 0x10) * var_f30);
						M2C_FIELD(var_r30, f32*, 0x14)
						    = (f32)(M2C_FIELD(var_r30, f32*, 0x14) * var_f30);
						M2C_FIELD(var_r30, f32*, 0x18)
						    = (f32)(M2C_FIELD(var_r30, f32*, 0x18) * var_f30);
						M2C_FIELD(var_r30, f32*, 0x30) = spC;
						M2C_FIELD(var_r30, f32*, 0x34) = sp10;
						M2C_FIELD(var_r30, f32*, 0x38) = sp14;
						var_r30 += sp70;
					}
					if (M2C_FIELD(var_r24, s32*, 0) & M2C_FIELD(var_r24, s32*, 0x14) & 4) {
						M2C_FIELD(var_r27, f32*, 0) = var_f31;
						M2C_FIELD(var_r27, f32*, 4) = var_f30;
						var_r27 += sp64;
					}
					if (M2C_FIELD(var_r24, s32*, 0) & M2C_FIELD(var_r24, s32*, 0x14) & 2) {
						M2C_FIELD(var_r29, s8*, 0) = (s8)var_f29;
						M2C_FIELD(var_r29, s8*, 1) = (s8)var_f28;
						M2C_FIELD(var_r29, s8*, 2) = (s8)var_f27;
						M2C_FIELD(var_r29, s8*, 3) = (s8)var_f26;
						var_r29 += sp6C;
					}
					if (M2C_FIELD(var_r24, s32*, 0) & M2C_FIELD(var_r24, s32*, 0x14) & 0x80) {
						M2C_FIELD(var_r28, f32*, 0)   = var_f25;
						M2C_FIELD(var_r28, f32*, 4)   = var_f24;
						M2C_FIELD(var_r28, f32*, 8)   = var_f23;
						M2C_FIELD(var_r28, f32*, 0xC) = var_f22;
						var_r28 += sp68;
					}
					if (M2C_FIELD(var_r24, s32*, 0) & M2C_FIELD(var_r24, s32*, 0x14) & 0x20) {
						*var_r26 = var_f21;
						var_r26 += sp60;
					}
				}
				var_r14_2 += 1;
				var_r18 += sp78;
				goto loop_84;
			}
			if (var_r24 != NULL) {
				var_r3_2                    = 0;
				M2C_FIELD(var_r24, s32*, 8) = (s32)(M2C_FIELD(var_r24, s32*, 8) + sp7C);
				if (M2C_FIELD(var_r24, s32*, 0) & 1) {
					var_r3_2                         = 1;
					*M2C_FIELD(var_r24, u8***, 0x20) = var_r30;
				}
				if (M2C_FIELD(var_r24, s32*, 0) & 2) {
					temp_r0_5 = var_r3_2 * 4;
					var_r3_2 += 1;
					*(u8**)((u8*)M2C_FIELD(var_r24, u8***, 0x20) + temp_r0_5) = var_r29;
				}
				if (M2C_FIELD(var_r24, s32*, 0) & 4) {
					temp_r0_6 = var_r3_2 * 4;
					var_r3_2 += 1;
					*(u8**)((u8*)M2C_FIELD(var_r24, u8***, 0x20) + temp_r0_6) = var_r27;
				}
				if (M2C_FIELD(var_r24, s32*, 0) & 8) {
					temp_r0_7 = var_r3_2 * 4;
					var_r3_2 += 1;
					*(u8**)((u8*)M2C_FIELD(var_r24, u8***, 0x20) + temp_r0_7) = var_r30;
				}
				if (M2C_FIELD(var_r24, s32*, 0) & 0x20) {
					temp_r0_8 = var_r3_2 * 4;
					var_r3_2 += 1;
					*(f32**)((u8*)M2C_FIELD(var_r24, u8***, 0x20) + temp_r0_8) = var_r26;
				}
				if (M2C_FIELD(var_r24, s32*, 0) & 0x80) {
					*(u8**)((u8*)M2C_FIELD(var_r24, u8***, 0x20) + (var_r3_2 * 4)) = var_r28;
				}
			}
			var_r14                        = sp8;
			M2C_FIELD(sp74, s32*, 0x10)    = (s32)M2C_FIELD(sp74, s32*, 8);
			M2C_FIELD(sp74, s32*, 8)       = (s32)(M2C_FIELD(sp74, s32*, 8) + sp7C);
			M2C_FIELD(var_r14, s32*, 0x10) = (s32)(M2C_FIELD(var_r14, s32*, 0x10) + sp7C);
			M2C_FIELD(temp_r25, u32*, 0)   = var_r15;
		}
		goto block_100;
	}
	var_r14 = sp8;
block_100:
	return var_r14;
}

#pragma dont_inline on
u8* fn_80237EBC(u8* arg1)
{
	s32 temp_r3;
	u8* temp_r6;

	temp_r3 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u8**, 0x10), 1);
	if (temp_r3 >= 0) {
		temp_r6                        = arg1 + temp_r3;
		M2C_FIELD(arg1, s32*, 4)       = (s32)(M2C_FIELD(arg1, s32*, 4) | 0x7F);
		M2C_FIELD(temp_r6, s32*, 0)    = 1;
		M2C_FIELD(temp_r6, s32*, 4)    = 0;
		M2C_FIELD(temp_r6, f32*, 0x74) = (f32)lbl_8043026C;
		M2C_FIELD(temp_r6, f32*, 0x78) = (f32)lbl_8043026C;
		M2C_FIELD(temp_r6, s8*, 0x7C)  = 0xFF;
		M2C_FIELD(temp_r6, s8*, 0x7D)  = 0xFF;
		M2C_FIELD(temp_r6, s8*, 0x7E)  = 0xFF;
		M2C_FIELD(temp_r6, s8*, 0x7F)  = 0xFF;
		M2C_FIELD(temp_r6, f32*, 0x84) = (f32)lbl_80430268;
		M2C_FIELD(temp_r6, f32*, 0x88) = (f32)lbl_80430268;
		M2C_FIELD(temp_r6, f32*, 0x8C) = (f32)lbl_8043026C;
		M2C_FIELD(temp_r6, f32*, 0x90) = (f32)lbl_8043026C;
		M2C_FIELD(temp_r6, f32*, 0x94) = (f32)lbl_80430268;
		M2C_FIELD(temp_r6, f32*, 0x98) = (f32)lbl_80430268;
		M2C_FIELD(temp_r6, f32*, 0x9C) = (f32)lbl_80430268;
		M2C_FIELD(temp_r6, f32*, 0xA0) = (f32)lbl_80430268;
		M2C_FIELD(temp_r6, f32*, 0x80) = (f32)lbl_80430268;
		M2C_FIELD(temp_r6, s32*, 0xA4) = 0;
	}
	return arg1;
}
#pragma dont_inline reset

#pragma dont_inline on
u8* fn_80237F90(u8* arg1)
{
	s32 temp_r3;

	temp_r3 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u8**, 0x10), 1);
	if ((temp_r3 >= 0) && (M2C_FIELD(arg1, s32*, 4) & 0x200)
	    && ((u32)M2C_FIELD((arg1 + temp_r3), u32*, 0xA4) != 0U)) {
		fn_801A491C();
	}
	return arg1;
}
#pragma dont_inline reset

#pragma dont_inline on
u8* fn_80237FF4(u8* arg1, u8* arg2)
{
	M2C_UNK* temp_r5;
	M2C_UNK* temp_r5_2;
	M2C_UNK* temp_r5_3;
	M2C_UNK* temp_r5_4;
	M2C_UNK* temp_r5_5;
	M2C_UNK* temp_r5_6;
	M2C_UNK* temp_r5_7;
	u8* temp_r29_2;
	s32 temp_r29;
	s32 temp_r29_3;
	s32 temp_r29_4;
	s32 temp_r29_5;
	s32 temp_r29_6;
	s32 temp_r29_7;
	s32 temp_r29_8;
	s32 temp_r3;
	s32 temp_r3_2;
	s32 temp_r3_3;
	s32 temp_r3_4;
	s32 temp_r3_5;
	s32 temp_r3_6;
	s32 temp_r3_7;
	u8* temp_r4;

	temp_r5  = M2C_FIELD(arg2, M2C_UNK**, 0xC);
	temp_r29 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u8**, 0x10), 1);
	temp_r3  = fn_8023506C(M2C_FIELD(temp_r5, u8**, 0x10), 1);
	if ((temp_r29 >= 0) && (temp_r3 >= 0)) {
		temp_r29_2 = arg1 + temp_r29;
		memcpy(arg2 + temp_r3, temp_r29_2, 0xAC);
		temp_r4 = M2C_FIELD(temp_r29_2, u8**, 0xA4);
		if (temp_r4 != NULL) {
			M2C_FIELD(temp_r4, s32*, 0x54) = (s32)(M2C_FIELD(temp_r4, s32*, 0x54) + 1);
		}
	}
	temp_r5_2  = M2C_FIELD(arg2, M2C_UNK**, 0xC);
	temp_r29_3 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u8**, 0x10), 2);
	temp_r3_2  = fn_8023506C(M2C_FIELD(temp_r5_2, u8**, 0x10), 2);
	if ((temp_r29_3 >= 0) && (temp_r3_2 >= 0)) {
		memcpy(arg2 + temp_r3_2, arg1 + temp_r29_3, 0x40);
	}
	temp_r5_3  = M2C_FIELD(arg2, M2C_UNK**, 0xC);
	temp_r29_4 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u8**, 0x10), 3);
	temp_r3_3  = fn_8023506C(M2C_FIELD(temp_r5_3, u8**, 0x10), 3);
	if ((temp_r29_4 >= 0) && (temp_r3_3 >= 0)) {
		memcpy(arg2 + temp_r3_3, arg1 + temp_r29_4, 0x40);
	}
	temp_r5_4  = M2C_FIELD(arg2, M2C_UNK**, 0xC);
	temp_r29_5 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u8**, 0x10), 8);
	temp_r3_4  = fn_8023506C(M2C_FIELD(temp_r5_4, u8**, 0x10), 8);
	if ((temp_r29_5 >= 0) && (temp_r3_4 >= 0)) {
		memcpy(arg2 + temp_r3_4, arg1 + temp_r29_5, 0x74);
	}
	temp_r5_5  = M2C_FIELD(arg2, M2C_UNK**, 0xC);
	temp_r29_6 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u8**, 0x10), 5);
	temp_r3_5  = fn_8023506C(M2C_FIELD(temp_r5_5, u8**, 0x10), 5);
	if ((temp_r29_6 >= 0) && (temp_r3_5 >= 0)) {
		memcpy(arg2 + temp_r3_5, arg1 + temp_r29_6, 0x20);
	}
	temp_r5_6  = M2C_FIELD(arg2, M2C_UNK**, 0xC);
	temp_r29_7 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u8**, 0x10), 4);
	temp_r3_6  = fn_8023506C(M2C_FIELD(temp_r5_6, u8**, 0x10), 4);
	if ((temp_r29_7 >= 0) && (temp_r3_6 >= 0)) {
		memcpy(arg2 + temp_r3_6, arg1 + temp_r29_7, 0x10);
	}
	temp_r5_7  = M2C_FIELD(arg2, M2C_UNK**, 0xC);
	temp_r29_8 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u8**, 0x10), 6);
	temp_r3_7  = fn_8023506C(M2C_FIELD(temp_r5_7, u8**, 0x10), 6);
	if ((temp_r29_8 >= 0) && (temp_r3_7 >= 0)) {
		fn_802356AC(arg2 + temp_r3_7, arg1 + temp_r29_8);
	}
	return arg2;
}
#pragma dont_inline reset

s32 fn_80238228(u8* arg0, u8* arg1, f32* arg2)
{
	f32 temp_f2;
	f32 var_f3;
	u32 temp_r3;
	u8* temp_r30;
	u8* temp_r3_2;
	u8* temp_r3_3;
	u8* temp_r4;

	temp_r30                        = arg1 + M2C_FIELD(lbl_8042AC68, s32*, 0x98);
	M2C_FIELD(temp_r30, s32*, 0xA8) = fn_8019E8EC(M2C_FIELD(arg0, s32*, 4), lbl_8042AC68);
	temp_f2                         = *arg2;
	M2C_FIELD(temp_r30, f32*, 8)    = (f32)(M2C_FIELD(temp_r30, f32*, 8) + temp_f2);
	if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xA8) >= 0) {
		temp_r4 = arg1 + M2C_FIELD(lbl_8042AC68, s32*, 0xA8);
		if (M2C_FIELD(temp_r4, s32*, 0x10) & 0x20000) {
			temp_r3 = M2C_FIELD(temp_r4, u32*, 0x18);
			if (temp_r3 != 0U) {
				temp_r3_2 = *(u8**)((u8*)temp_r3 + lbl_8042CF48);
				var_f3    = (temp_f2 * M2C_FIELD(temp_r30, f32*, 0x80))
				    + M2C_FIELD(temp_r3_2, f32*, 0xC0);
				if (var_f3 > lbl_80430278) {
					var_f3 = (f32)((f64)var_f3 - lbl_80430280);
				} else if (var_f3 < lbl_8043027C) {
					var_f3 = (f32)((f64)var_f3 + lbl_80430280);
				}
				M2C_FIELD(temp_r3_2, f32*, 0xC0) = var_f3;
				temp_r3_3 = *(u8**)((u8*)M2C_FIELD(temp_r4, u32*, 0x18) + lbl_8042CF48);
				M2C_FIELD(temp_r3_3, s32*, 0x40)
				    = (s32)(M2C_FIELD(temp_r3_3, s32*, 0x40) | 0x20000);
			}
		}
	}
	return (s32)arg1;
}

s32 fn_80238328(s32 arg1)
{
	f32 temp_f1;
	u32 temp_r3;
	u8* temp_r5;

	temp_r5 = (u8*)arg1 + M2C_FIELD(lbl_8042AC68, s32*, 0x98);
	temp_f1 = M2C_FIELD(temp_r5, f32*, 8);
	M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
	if (temp_f1 == M2C_FIELD(temp_r5, f32*, 0x40)) {
		M2C_FIELD(temp_r5, f32*, 0x3C) = temp_f1;
		temp_r3                        = (M2C_FIELD(temp_r5, u32*, 0) * 0x0BB38435) + 0x3619636B;
		M2C_FIELD(temp_r5, f32*, 0x40)
		    = (f32)((((lbl_80430270 * (lbl_80430274 * (f32)temp_r3)) - lbl_8043026C)
		                * M2C_FIELD(temp_r5, f32*, 0x38))
		        + (M2C_FIELD(temp_r5, f32*, 8) + M2C_FIELD(temp_r5, f32*, 0x34)));
		M2C_FIELD(temp_r5, u32*, 0) = temp_r3;
	}
	return arg1;
}

#pragma dont_inline on
u8* fn_802383C0(s32 arg0, u8* arg1)
{
	s32 temp_r3;
	u8* temp_r3_2;
	u8* temp_r3_3;
	u8* var_r31;

	var_r31 = arg1;
	if ((s32)M2C_FIELD(arg1, s32*, 0x10) > 0) {
		temp_r3 = fn_8023506C(M2C_FIELD(M2C_FIELD(var_r31, u8**, 0xC), u8**, 0x10), 6);
		if (temp_r3 >= 0) {
			temp_r3_2 = var_r31 + temp_r3;
			if ((u32)M2C_FIELD(temp_r3_2, u32*, 8) != 0U) {
				temp_r3_3 = M2C_FIELD(temp_r3_2, u8**, 0x18);
				if (M2C_FIELD(temp_r3_3, u32(**)(u8*), 0x48)(temp_r3_3) == 0U) {
					var_r31 = NULL;
				}
			}
		} else {
			var_r31 = NULL;
		}
	}
	return var_r31;
}
#pragma dont_inline reset

#pragma dont_inline on
u8* fn_80238444(u8* arg1, s32* arg2)
{
	s32 sp8;
	u8* temp_r29;
	u8* temp_r29_2;
	u8* temp_r29_3;
	u8* temp_r29_5;
	u8* temp_r29_6;
	s32 temp_r3;
	s32 temp_r3_2;
	s32 temp_r3_3;
	s32 temp_r3_4;
	s32 temp_r3_5;
	s32 temp_r3_6;
	s32 temp_r3_7;
	u8* temp_r29_4;
	u8* temp_r30;

	temp_r30 = M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u8**, 0x10);
	temp_r3  = fn_8023506C(temp_r30, 1);
	if (temp_r3 >= 0) {
		temp_r29 = arg1 + temp_r3;
		fn_80193884(arg2, temp_r29, 4);
		fn_80193884(arg2, temp_r29 + 4, 4);
		fn_801937A0(arg2, temp_r29 + 0x10, 0xC);
		fn_801937A0(arg2, temp_r29 + 0x1C, 0xC);
		fn_801937A0(arg2, temp_r29 + 0x28, 0xC);
		fn_801937A0(arg2, temp_r29 + 0x34, 4);
		fn_801937A0(arg2, temp_r29 + 0x38, 4);
		fn_80193884(arg2, temp_r29 + 0x44, 4);
		fn_80193884(arg2, temp_r29 + 0x48, 4);
		fn_801937A0(arg2, temp_r29 + 0x4C, 4);
		fn_801937A0(arg2, temp_r29 + 0x50, 4);
		fn_801937A0(arg2, temp_r29 + 0x54, 4);
		fn_801937A0(arg2, temp_r29 + 0x58, 4);
		fn_801937A0(arg2, temp_r29 + 0x5C, 0xC);
		fn_801937A0(arg2, temp_r29 + 0x68, 0xC);
		fn_801937A0(arg2, temp_r29 + 0x74, 0xC);
		fn_80193884(arg2, &sp8, 4);
		M2C_FIELD(temp_r29, s8*, 0x7C) = (s8)((u32)sp8 >> 0x18U);
		M2C_FIELD(temp_r29, u8*, 0x7D) = (u8)((u32)sp8 >> 0x10U);
		M2C_FIELD(temp_r29, u8*, 0x7E) = (u8)((u32)sp8 >> 8U);
		M2C_FIELD(temp_r29, s8*, 0x7F) = (s8)sp8;
		sp8                            = 0;
	loop_3:
		if (sp8 < 4) {
			fn_801937A0(arg2, temp_r29 + ((sp8 * 8) + 0x84), 8);
			sp8 += 1;
			goto loop_3;
		}
		fn_80193884(arg2, &sp8, 4);
		if ((sp8 > 0) && (fn_80192F38(arg2, 6, 0, 0) != 0)) {
			M2C_FIELD(temp_r29, s32*, 0xA4) = fn_8019ADB4(arg2);
		}
		if ((s32)M2C_FIELD(lbl_8042AC68, s32*, 0xC) >= 3) {
			fn_801937A0(arg2, temp_r29 + 0x80, 4);
		}
	}
	temp_r3_2 = fn_8023506C(temp_r30, 2);
	if (temp_r3_2 >= 0) {
		temp_r29_2 = arg1 + temp_r3_2;
		fn_801937A0(arg2, temp_r29_2, 0x10);
		fn_801937A0(arg2, temp_r29_2 + 0x10, 0x10);
		fn_801937A0(arg2, temp_r29_2 + 0x20, 0x10);
		fn_801937A0(arg2, temp_r29_2 + 0x30, 0x10);
	}
	temp_r3_3 = fn_8023506C(temp_r30, 3);
	if (temp_r3_3 >= 0) {
		temp_r29_3 = arg1 + temp_r3_3;
		fn_801937A0(arg2, temp_r29_3, 8);
		fn_801937A0(arg2, temp_r29_3 + 8, 8);
		fn_801937A0(arg2, temp_r29_3 + 0x10, 8);
		fn_801937A0(arg2, temp_r29_3 + 0x18, 8);
		fn_801937A0(arg2, temp_r29_3 + 0x20, 8);
		fn_801937A0(arg2, temp_r29_3 + 0x28, 8);
		fn_801937A0(arg2, temp_r29_3 + 0x30, 8);
		fn_801937A0(arg2, temp_r29_3 + 0x38, 8);
	}
	temp_r3_4 = fn_8023506C(temp_r30, 8);
	if (temp_r3_4 >= 0) {
		temp_r29_4 = arg1 + temp_r3_4;
		fn_80192F38(arg2, 0xD, 0, 0);
		fn_80193DA4(arg2, temp_r29_4);
		fn_801937A0(arg2, temp_r29_4 + 0x40, 0xC);
		fn_801937A0(arg2, temp_r29_4 + 0x4C, 0xC);
		fn_801937A0(arg2, temp_r29_4 + 0x58, 0xC);
		fn_801937A0(arg2, temp_r29_4 + 0x64, 0xC);
		fn_80193884(arg2, temp_r29_4 + 0x70, 4);
	}
	temp_r3_5 = fn_8023506C(temp_r30, 5);
	if (temp_r3_5 >= 0) {
		temp_r29_5 = arg1 + temp_r3_5;
		fn_801937A0(arg2, temp_r29_5, 8);
		fn_801937A0(arg2, temp_r29_5 + 8, 8);
		fn_801937A0(arg2, temp_r29_5 + 0x10, 8);
		fn_801937A0(arg2, temp_r29_5 + 0x18, 8);
	}
	temp_r3_6 = fn_8023506C(temp_r30, 4);
	if (temp_r3_6 >= 0) {
		temp_r29_6 = arg1 + temp_r3_6;
		fn_801937A0(arg2, temp_r29_6, 4);
		fn_801937A0(arg2, temp_r29_6 + 4, 4);
		fn_801937A0(arg2, temp_r29_6 + 8, 4);
		fn_801937A0(arg2, temp_r29_6 + 0xC, 4);
	}
	temp_r3_7 = fn_8023506C(temp_r30, 6);
	if (temp_r3_7 >= 0) {
		fn_802357A8(arg2, arg1 + temp_r3_7);
	}
	return arg1;
}
#pragma dont_inline reset

#pragma dont_inline on
u8* fn_802388D4(u8* arg1, s32* arg2)
{
	s32 sp8;
	u8* temp_r29;
	u8* temp_r29_2;
	u8* temp_r29_3;
	u8* temp_r29_5;
	u8* temp_r29_6;
	s32 temp_r3;
	s32 temp_r3_2;
	s32 temp_r3_3;
	s32 temp_r3_4;
	s32 temp_r3_5;
	s32 temp_r3_6;
	s32 temp_r3_7;
	u8 temp_r6;
	u8 temp_r7;
	u8* temp_r29_4;
	u8* temp_r30;

	temp_r30 = M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u8**, 0x10);
	temp_r3  = fn_8023506C(temp_r30, 1);
	if (temp_r3 >= 0) {
		temp_r29 = arg1 + temp_r3;
		fn_80193474(arg2, temp_r29, 4);
		fn_80193474(arg2, temp_r29 + 4, 4);
		fn_8019336C(arg2, temp_r29 + 0x10, 0xC);
		fn_8019336C(arg2, temp_r29 + 0x1C, 0xC);
		fn_8019336C(arg2, temp_r29 + 0x28, 0xC);
		fn_8019336C(arg2, temp_r29 + 0x34, 4);
		fn_8019336C(arg2, temp_r29 + 0x38, 4);
		fn_80193474(arg2, temp_r29 + 0x44, 4);
		fn_80193474(arg2, temp_r29 + 0x48, 4);
		fn_8019336C(arg2, temp_r29 + 0x4C, 4);
		fn_8019336C(arg2, temp_r29 + 0x50, 4);
		fn_8019336C(arg2, temp_r29 + 0x54, 4);
		fn_8019336C(arg2, temp_r29 + 0x58, 4);
		fn_8019336C(arg2, temp_r29 + 0x5C, 0xC);
		fn_8019336C(arg2, temp_r29 + 0x68, 0xC);
		fn_8019336C(arg2, temp_r29 + 0x74, 0xC);
		temp_r6 = M2C_FIELD(temp_r29, u8*, 0x7E);
		temp_r7 = M2C_FIELD(temp_r29, u8*, 0x7F);
		sp8     = temp_r7
		    | (((((M2C_FIELD(temp_r29, u8*, 0x7D) << 0x10) & ~0xFF000000)
		            | (M2C_FIELD(temp_r29, u8*, 0x7C) << 0x18))
		           & ~0xFF00)
		        | ((temp_r6 << 8) & 0xFF00));
		fn_80193474(arg2, &sp8, 4, temp_r6, temp_r7);
		sp8 = 0;
	loop_3:
		if (sp8 < 4) {
			fn_8019336C(arg2, temp_r29 + ((sp8 * 8) + 0x84), 8);
			sp8 += 1;
			goto loop_3;
		}
		if ((u32)M2C_FIELD(temp_r29, u32*, 0xA4) != 0U) {
			sp8 = 1;
			fn_80193474(arg2, &sp8, 4);
			fn_8019AAFC(M2C_FIELD(temp_r29, u32*, 0xA4), arg2);
		} else {
			sp8 = 0;
			fn_80193474(arg2, &sp8, 4);
		}
		fn_8019336C(arg2, temp_r29 + 0x80, 4);
	}
	temp_r3_2 = fn_8023506C(temp_r30, 2);
	if (temp_r3_2 >= 0) {
		temp_r29_2 = arg1 + temp_r3_2;
		fn_8019336C(arg2, temp_r29_2, 0x10);
		fn_8019336C(arg2, temp_r29_2 + 0x10, 0x10);
		fn_8019336C(arg2, temp_r29_2 + 0x20, 0x10);
		fn_8019336C(arg2, temp_r29_2 + 0x30, 0x10);
	}
	temp_r3_3 = fn_8023506C(temp_r30, 3);
	if (temp_r3_3 >= 0) {
		temp_r29_3 = arg1 + temp_r3_3;
		fn_8019336C(arg2, temp_r29_3, 8);
		fn_8019336C(arg2, temp_r29_3 + 8, 8);
		fn_8019336C(arg2, temp_r29_3 + 0x10, 8);
		fn_8019336C(arg2, temp_r29_3 + 0x18, 8);
		fn_8019336C(arg2, temp_r29_3 + 0x20, 8);
		fn_8019336C(arg2, temp_r29_3 + 0x28, 8);
		fn_8019336C(arg2, temp_r29_3 + 0x30, 8);
		fn_8019336C(arg2, temp_r29_3 + 0x38, 8);
	}
	temp_r3_4 = fn_8023506C(temp_r30, 8);
	if (temp_r3_4 >= 0) {
		temp_r29_4 = arg1 + temp_r3_4;
		fn_80193B60(temp_r29_4, arg2);
		fn_8019336C(arg2, temp_r29_4 + 0x40, 0xC);
		fn_8019336C(arg2, temp_r29_4 + 0x4C, 0xC);
		fn_8019336C(arg2, temp_r29_4 + 0x58, 0xC);
		fn_8019336C(arg2, temp_r29_4 + 0x64, 0xC);
		fn_80193474(arg2, temp_r29_4 + 0x70, 4);
	}
	temp_r3_5 = fn_8023506C(temp_r30, 5);
	if (temp_r3_5 >= 0) {
		temp_r29_5 = arg1 + temp_r3_5;
		fn_8019336C(arg2, temp_r29_5, 8);
		fn_8019336C(arg2, temp_r29_5 + 8, 8);
		fn_8019336C(arg2, temp_r29_5 + 0x10, 8);
		fn_8019336C(arg2, temp_r29_5 + 0x18, 8);
	}
	temp_r3_6 = fn_8023506C(temp_r30, 4);
	if (temp_r3_6 >= 0) {
		temp_r29_6 = arg1 + temp_r3_6;
		fn_8019336C(arg2, temp_r29_6, 4);
		fn_8019336C(arg2, temp_r29_6 + 4, 4);
		fn_8019336C(arg2, temp_r29_6 + 8, 4);
		fn_8019336C(arg2, temp_r29_6 + 0xC, 4);
	}
	temp_r3_7 = fn_8023506C(temp_r30, 6);
	if (temp_r3_7 >= 0) {
		fn_8023582C(arg2, arg1 + temp_r3_7);
	}
	return arg1;
}
#pragma dont_inline reset

#pragma dont_inline on
u8* fn_80238D3C(u8* arg1, s32* arg2)
{
	s32 temp_r3;
	s32 temp_r3_2;
	s32 temp_r3_3;
	s32 var_r31;
	s32 var_r31_2;
	u8* temp_r30;

	var_r31  = 0;
	temp_r30 = M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u8**, 0x10);
	temp_r3  = fn_8023506C(temp_r30, 1);
	if (temp_r3 >= 0) {
		var_r31_2 = 0x98;
		if ((u32) * (arg1 + (temp_r3 + 0xA4)) != 0U) {
			var_r31_2 = fn_8019AA5C() + 0xA4;
		}
		var_r31 = var_r31_2 + 4;
	}
	if (fn_8023506C(temp_r30, 2) >= 0) {
		var_r31 += 0x40;
	}
	if (fn_8023506C(temp_r30, 3) >= 0) {
		var_r31 += 0x40;
	}
	temp_r3_2 = fn_8023506C(temp_r30, 8);
	if (temp_r3_2 >= 0) {
		var_r31 = var_r31 + fn_80193B58(arg1 + temp_r3_2) + 0x40;
	}
	if (fn_8023506C(temp_r30, 5) >= 0) {
		var_r31 += 0x20;
	}
	if (fn_8023506C(temp_r30, 4) >= 0) {
		var_r31 += 0x10;
	}
	temp_r3_3 = fn_8023506C(temp_r30, 6);
	if (temp_r3_3 >= 0) {
		var_r31 += fn_802358B0();
	}
	*arg2 = var_r31;
	return arg1;
}
#pragma dont_inline reset

u8* fn_80238E6C(u8* arg0)
{
	u8* (*sp30)(u8*, u8*);
	u8* (*sp2C)(u8*, s32*);
	u8* (*sp28)(u8*, s32*);
	u8* (*sp24)(u8*, s32*);
	u8* (*sp20)(u8*);
	u8* (*sp1C)(u8*);
	s32 sp18;
	u8* (*sp14)(s32, u8*);
	s32 (*sp10)(s32);
	s32 (*spC)(u8*, u8*, f32*);
	u8* (*sp8)(u8*);
	s32 var_ctr;
	u8* (**var_r6)(u8*);

	var_r6  = &sp8 + 0x28;
	sp8     = NULL;
	spC     = NULL;
	sp10    = NULL;
	sp14    = NULL;
	sp18    = 0;
	sp1C    = NULL;
	sp20    = NULL;
	sp24    = NULL;
	sp28    = NULL;
	sp2C    = NULL;
	var_ctr = 0xB - 0xA;
	if (0xA < 0xB) {
		do {
			*var_r6 = NULL;
			var_r6 += 4;
			var_ctr -= 1;
		} while (var_ctr != 0);
	}
	sp1C = fn_80237EBC;
	sp20 = fn_80237F90;
	sp8  = fn_80236AE4;
	spC  = fn_80238228;
	sp10 = fn_80238328;
	sp14 = fn_802383C0;
	sp24 = fn_80238444;
	sp28 = fn_802388D4;
	sp2C = fn_80238D3C;
	sp30 = fn_80237FF4;
	fn_8023239C(arg0, 1, (u8*)&sp8);
	return arg0;
}

#pragma dont_inline on
s32 fn_80238F88(s32 arg0)
{
	s32 sp20;
	s32 sp1C;
	s32 sp18;
	s32 sp14;
	s32 sp10;
	s32 spC;
	u8* (*sp8)(u8*, u8*, f32*);

	sp8  = NULL;
	spC  = 0;
	sp10 = 0;
	sp14 = 0;
	sp18 = 0;
	sp1C = 0;
	sp20 = 0;
	sp8  = fn_80235E64;
	fn_802344D8((u8*)1, (s32)&sp8, NULL);
	return arg0;
}
#pragma dont_inline reset

void fn_80238FEC(void) { }

#pragma dont_inline on
s32 fn_80238FF0(s32 arg0)
{
	M2C_UNK* var_r27;
	M2C_UNK* var_r28;
	M2C_UNK* var_r30;
	M2C_UNK* var_r30_2;
	u8* var_r26;
	u8* var_r27_2;

	var_r28 = NULL;
	var_r27 = NULL;
	var_r26 = NULL;
	if ((M2C_UNK**)M2C_FIELD(lbl_8042AC68, M2C_UNK***, 0x64) != NULL) {
		var_r30 = *M2C_FIELD(lbl_8042AC68, M2C_UNK***, 0x64);
	loop_3:
		if (var_r30 != var_r27) {
			var_r27 = var_r30;
			var_r30 = (M2C_UNK*)*var_r30;
			fn_802343C4(var_r27);
			goto loop_3;
		}
		M2C_FIELD(lbl_8042AC68, M2C_UNK***, 0x64) = NULL;
	}
	if ((M2C_UNK**)M2C_FIELD(lbl_8042AC68, M2C_UNK***, 0x60) != NULL) {
		var_r30_2 = *M2C_FIELD(lbl_8042AC68, M2C_UNK***, 0x60);
	loop_8:
		if (var_r30_2 != var_r28) {
			var_r28   = var_r30_2;
			var_r30_2 = (M2C_UNK*)*var_r30_2;
			fn_80232288(var_r28);
			goto loop_8;
		}
		M2C_FIELD(lbl_8042AC68, M2C_UNK***, 0x60) = NULL;
	}
	if ((u8*)M2C_FIELD(lbl_8042AC68, u8**, 0x68) != NULL) {
		var_r27_2 = M2C_FIELD(M2C_FIELD(lbl_8042AC68, u8**, 0x68), u8**, 4);
	loop_13:
		if (var_r27_2 != var_r26) {
			var_r26   = var_r27_2;
			var_r27_2 = M2C_FIELD(var_r27_2, u8**, 4);
			fn_80234EA0(var_r26);
			goto loop_13;
		}
		M2C_FIELD(lbl_8042AC68, u8**, 0x68) = NULL;
	}
	if ((u32)M2C_FIELD(lbl_8042AC68, u32*, 0x80) != 0U) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(
		    M2C_FIELD(lbl_8042AC68, u8**, 0x80), lbl_8042C9A4);
	}
	M2C_FIELD(lbl_8042AC68, u32*, 0x80) = 0U;
	M2C_FIELD(lbl_8042AC68, s32*, 0x84) = 0;
	if ((u32)M2C_FIELD(lbl_8042AC68, u32*, 0x88) != 0U) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, M2C_UNK*), 0x138)(
		    M2C_FIELD(lbl_8042AC68, u8**, 0x88), lbl_8042C9A4);
	}
	M2C_FIELD(lbl_8042AC68, u32*, 0x88) = 0U;
	M2C_FIELD(lbl_8042AC68, s32*, 0x8C) = 0;
	return arg0;
}
#pragma dont_inline reset

void fn_8023914C(s32 arg0)
{
	fn_80239690(arg0, fn_80233714, NULL);
}

void fn_80239178(s32 arg0, s32 arg1)
{
	*(s32*)(arg0 + arg1) = 0;
}

s32 fn_80239184(s32 arg0, s32 arg1)
{
	M2C_UNK** temp_r3;
	M2C_UNK* temp_r30;
	M2C_UNK* temp_r31;
	M2C_UNK* var_r3;

	temp_r3 = *(M2C_UNK***)(arg0 + arg1);
	if (temp_r3 != NULL) {
		temp_r31 = *temp_r3;
		var_r3   = temp_r31;
		do {
			temp_r30 = (M2C_UNK*)*var_r3;
			fn_80232A9C((u8*)var_r3);
			var_r3 = temp_r30;
		} while (temp_r30 != temp_r31);
	}
	*(s32*)(arg0 + arg1) = 0;
	return arg0;
}

#pragma dont_inline on
s32 fn_802391FC(s32 arg0, s32 arg1, s32 arg2)
{
	M2C_UNK** temp_r3;
	M2C_UNK* temp_r31;
	M2C_UNK* var_r29;
	M2C_UNK* var_r30;
	u8* temp_r3_2;

	temp_r3 = *(M2C_UNK***)(arg1 + arg2);
	var_r29 = NULL;
	if (temp_r3 != NULL) {
		temp_r31 = *temp_r3;
		var_r30  = temp_r31;
		do {
			temp_r3_2 = fn_80232BAC(var_r30);
			if (temp_r3_2 != NULL) {
				M2C_FIELD(temp_r3_2, s32*, 8) = arg0;
				var_r29                       = fn_80232E34(var_r29, (M2C_UNK*)temp_r3_2);
			}
			var_r30 = (M2C_UNK*)*var_r30;
		} while (var_r30 != temp_r31);
	}
	*(M2C_UNK**)(arg0 + arg2) = var_r29;
	return arg0;
}
#pragma dont_inline reset

s32 fn_8023927C(s32 arg1, s32* arg2)
{
	*arg2 += 1;
	return arg1;
}

s32 fn_80239290(s32 arg0, s32 arg1)
{
	s32 sp8;

	sp8 = 0;
	if (*(u32*)(arg0 + arg1) != 0U) {
		sp8 = 4;
		fn_80239690(arg0, fn_80233F50, &sp8);
	}
	return sp8;
}

s32* fn_802392DC(s32* arg0, s32 arg1, u8* arg2)
{
	s32 sp8;
	s32 temp_r0;
	s32 var_r30;

	fn_80193884(arg0, &sp8, 4);
	temp_r0                            = sp8 & 0xFFFFFF;
	M2C_FIELD(lbl_8042AC68, u32*, 0xC) = (u32)((u32)sp8 >> 0x18U);
	sp8                                = temp_r0;
	if (temp_r0 > 0) {
		for (var_r30 = 0; var_r30 < sp8; var_r30 += 1) {
			fn_802338B8(arg2, arg0);
		}
		M2C_FIELD(arg2, void (**)(s32), 0x48) = fn_8023914C;
		if (((void (*)())M2C_FIELD(arg2, void (**)(), 0x48)) == NULL) {
			M2C_FIELD(arg2, void (**)(), 0x48) = fn_8014F1B0;
		}
	}
	M2C_FIELD(lbl_8042AC68, u32*, 0xC) = 0U;
	return arg0;
}

s32* fn_802393A0(s32* arg0, s32 arg1, M2C_UNK* (*arg2)(s32, M2C_UNK*, s32*, M2C_UNK), s32 arg3)
{
	s32 sp8;

	if (*(u32*)((u8*)arg2 + arg3) != 0U) {
		sp8 = 0;
		fn_80239690(arg2, (s32*)fn_8023927C, &sp8);
		sp8 |= 0x03000000;
		fn_80193474(arg0, &sp8, 4);
		fn_80239690(arg2, (s32*)fn_80233DF8, arg0);
		goto block_ok;
	}
	return NULL;
block_ok:
	return arg0;
}

s32 fn_8023943C(void)
{
	return M2C_FIELD(lbl_8042AC68, s32*, 0xC);
}

s32 fn_8023944C(void)
{
	M2C_FIELD(lbl_8042AC68, s32*, 0) = RwEngineRegisterPlugin(0, 0x130, fn_80238FEC, fn_80238FF0);
	M2C_FIELD(lbl_8042AC68, s32*, 4) = fn_801520D0(4, 0x130, fn_80239178, fn_80239184, fn_802391FC);
	M2C_FIELD(lbl_8042AC68, s32*, 8)
	    = fn_80152150(0x130, fn_802392DC, fn_802393A0, fn_80239290, lbl_8042AC68);
	M2C_FIELD(lbl_8042AC68, s32*, 0x60) = 0;
	M2C_FIELD(lbl_8042AC68, s32*, 0x64) = 0;
	M2C_FIELD(lbl_8042AC68, s32*, 0x68) = 0;
	M2C_FIELD(lbl_8042AC68, s32*, 0x7C) = 1;
	fn_80239888(fn_80238E6C, fn_80238E6C, 0, lbl_8042AC68);
	fn_8023989C(fn_80238F88);
	M2C_FIELD(lbl_8042AC68, s32*, 0x94) = 0;
	M2C_FIELD(lbl_8042AC68, s32*, 0x90) = 0;
	M2C_FIELD(lbl_8042AC68, s32*, 0x98) = -1;
	M2C_FIELD(lbl_8042AC68, s32*, 0x9C) = -1;
	M2C_FIELD(lbl_8042AC68, s32*, 0xA0) = -1;
	M2C_FIELD(lbl_8042AC68, s32*, 0xA4) = -1;
	M2C_FIELD(lbl_8042AC68, s32*, 0xA8) = -1;
	M2C_FIELD(lbl_8042AC68, s32*, 0xB4) = -1;
	M2C_FIELD(lbl_8042AC68, s32*, 0xB8) = -1;
	M2C_FIELD(lbl_8042AC68, s32*, 0xBC) = -1;
	M2C_FIELD(lbl_8042AC68, s32*, 0xC0) = -1;
	M2C_FIELD(lbl_8042AC68, s32*, 0xC4) = -1;
	M2C_FIELD(lbl_8042AC68, s32*, 0x88) = M2C_FIELD(
	    lbl_8042C9A4, s32(**)(M2C_UNK, M2C_UNK*, M2C_UNK), 0x134)(0x80, lbl_8042C9A4, 0);
	M2C_FIELD(lbl_8042AC68, s32*, 0x8C) = 0x80;
	M2C_FIELD(lbl_8042AC68, s32*, 0x80) = M2C_FIELD(
	    lbl_8042C9A4, s32(**)(M2C_UNK, M2C_UNK*, M2C_UNK), 0x134)(0x80, lbl_8042C9A4, 0);
	M2C_FIELD(lbl_8042AC68, s32*, 0x84) = 0x80;
	M2C_FIELD(lbl_8042AC68, s32*, 0x74) = 0;
	M2C_FIELD(lbl_8042AC68, s32*, 0x78) = 0;
	return 1;
}

u8* fn_802395BC(void)
{
	s32 temp_r3_2;
	u8* temp_r3;
	u8* var_r29;

	temp_r3 = fn_80232968(NULL);
	var_r29 = NULL;
	if (temp_r3 != NULL) {
		temp_r3_2 = fn_80152288(lbl_80430298);
		if (temp_r3_2 != 0) {
			var_r29 = fn_80150140();
			if (var_r29 != NULL) {
				*(u8**)(var_r29 + M2C_FIELD(lbl_8042AC68, s32*, 4)) = temp_r3;
				M2C_FIELD(temp_r3, u8**, 8)                         = var_r29;
				M2C_FIELD(var_r29, void (**)(s32), 0x48)            = fn_8023914C;
				if (((void (*)())M2C_FIELD(var_r29, void (**)(), 0x48)) == NULL) {
					M2C_FIELD(var_r29, void (**)(), 0x48) = fn_8014F1B0;
				}
				fn_8015028C(var_r29, temp_r3_2, 0);
				fn_80152EEC(temp_r3_2);
			} else {
				fn_80152EEC(temp_r3_2);
				fn_80232A9C(temp_r3);
			}
		} else {
			fn_80232A9C(temp_r3);
		}
	}
	return var_r29;
}

M2C_UNK* (*fn_80239690(M2C_UNK* (*arg0)(s32, M2C_UNK*, s32*, M2C_UNK),
    u32 (*arg1)(M2C_UNK* (*)(s32, M2C_UNK*, s32*, M2C_UNK), M2C_UNK*, s32*), s32* arg2,
    M2C_UNK arg_sp0))(s32, M2C_UNK*, s32*, M2C_UNK)
{
	M2C_UNK** temp_r3;
	M2C_UNK* temp_r29;
	M2C_UNK* temp_r31;
	M2C_UNK* var_r30;

	temp_r3 = *(M2C_UNK***)((u8*)arg0 + M2C_FIELD(lbl_8042AC68, s32*, 4));
	if (temp_r3 != NULL) {
		temp_r31 = *temp_r3;
		var_r30  = temp_r31;
	loop_2:
		temp_r29 = (M2C_UNK*)*var_r30;
		if ((M2C_UNK*)arg1(arg0, var_r30, arg2) != var_r30) {
			return NULL;
		}
		var_r30 = temp_r29;
		if (temp_r29 == temp_r31) {
			goto block_5;
		}
		goto loop_2;
	}
block_5:
	return arg0;
}

s32 fn_80239724(s32 arg0)
{
	return *(s32*)(arg0 + M2C_FIELD(lbl_8042AC68, s32*, 4));
}

#pragma dont_inline on
u8* fn_80239738(u8* arg0, u8* arg1)
{
	*(M2C_UNK**)(arg0 + M2C_FIELD(lbl_8042AC68, s32*, 4))
	    = fn_80232E34(*(M2C_UNK**)(arg0 + M2C_FIELD(lbl_8042AC68, s32*, 4)), (M2C_UNK*)arg1);
	M2C_FIELD(arg1, u8**, 8) = arg0;
	return arg0;
}
#pragma dont_inline reset

u8* fn_80239798(u8* arg0, s32 arg1)
{
	M2C_UNK** temp_r3;
	M2C_UNK* temp_r29;
	M2C_UNK* temp_r30;
	M2C_UNK* var_r28;
	u8* temp_r4;
	u8* var_r0;
	u8* var_r5;

	var_r5 = NULL;
	if (*(u32*)(arg0 + M2C_FIELD(lbl_8042AC68, s32*, 4)) != 0U) {
		if (M2C_FIELD(arg0, s32*, 0x4C) & 2) {
			fn_8014F854();
		}
		M2C_FIELD(arg0, f32*, 0x28) = (f32)lbl_80430298;
		temp_r3                     = *(M2C_UNK***)(arg0 + M2C_FIELD(lbl_8042AC68, s32*, 4));
		if (temp_r3 != NULL) {
			temp_r29 = *temp_r3;
			var_r28  = temp_r29;
		loop_5:
			temp_r30 = (M2C_UNK*)*var_r28;
			if (fn_802332AC(arg0, var_r28, arg1) != var_r28) {
				var_r0 = NULL;
			} else {
				var_r28 = temp_r30;
				if (temp_r30 == temp_r29) {
					goto block_8;
				}
				goto loop_5;
			}
		} else {
		block_8:
			var_r0 = arg0;
		}
		var_r5                         = var_r0;
		temp_r4                        = M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, 0x5C);
		M2C_FIELD(temp_r4, s32*, 4)    = (s32)M2C_FIELD(arg0, s32*, 0x1C);
		M2C_FIELD(temp_r4, s32*, 8)    = (s32)M2C_FIELD(arg0, s32*, 0x20);
		M2C_FIELD(temp_r4, s32*, 0xC)  = (s32)M2C_FIELD(arg0, s32*, 0x24);
		M2C_FIELD(temp_r4, f32*, 0x10) = (f32)M2C_FIELD(arg0, f32*, 0x28);
		M2C_FIELD(arg0, u8*, 3)        = (u8)(M2C_FIELD(arg0, u8*, 3) | 1);
	}
	return var_r5;
}

s32 fn_80239888(u8* (*arg0)(u8*))
{
	M2C_FIELD(lbl_8042AC68, u8 * (**)(u8*), 0x6C) = arg0;
	return 1;
}

s32 fn_8023989C(s32 (*arg0)(s32))
{
	M2C_FIELD(lbl_8042AC68, s32(**)(s32), 0x70) = arg0;
	return 1;
}
