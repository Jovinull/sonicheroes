#include "types.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_ERROR(...)                0

M2C_UNK DCFlushRange();                                                    /* extern */
M2C_UNK GXInvalidateVtxCache();                                            /* extern */
M2C_UNK GXSetVtxDesc(M2C_UNK, M2C_UNK);                                    /* extern */
M2C_UNK fn_80140544();                                                     /* extern */
M2C_UNK fn_80141D0C(u8*, u8*, u8*, s32, u8*);                              /* extern */
M2C_UNK fn_80145004(s32, u8*, s32);                                        /* extern */
s32 fn_8014535C(s32);                                                      /* extern */
s32 fn_80149208(u8*);                                                      /* extern */
s32 fn_801521F4(M2C_UNK);                                                  /* extern */
M2C_UNK fn_8015C358(s32 (*)(u8*, s32));                                    /* extern */
M2C_UNK fn_8015C370(s32, u8* (*)(u8*, s32));                               /* extern */
M2C_UNK fn_8015C388(s32, u8* (*)(u8*, u8*, M2C_UNK));                      /* extern */
M2C_UNK fn_8015C394(M2C_UNK);                                              /* extern */
s32 fn_8015C39C();                                                         /* extern */
M2C_UNK fn_8015C3A4();                                                     /* extern */
u8* fn_8015C590();                                                         /* extern */
M2C_UNK fn_8015C878(s32);                                                  /* extern */
s32* fn_8015D4B8();                                                        /* extern */
s32 fn_801645E4(M2C_UNK*);                                                 /* extern */
s32 fn_801649BC(M2C_UNK*, s32, s32);                                       /* extern */
M2C_UNK fn_80164A08(u8*, u32, s32, s32);                                   /* extern */
M2C_UNK fn_801671B4(s32, s32, s32*, s32*, M2C_UNK);                        /* extern */
M2C_UNK fn_80167E80(M2C_UNK*, u8*, u8**, s32, s32, s32, M2C_UNK, M2C_UNK); /* extern */
s32 fn_80168778(M2C_UNK*);                                                 /* extern */
s32 fn_8016878C(M2C_UNK*, s32*);                                           /* extern */
M2C_UNK fn_80168AF4(M2C_UNK*, u8*, s32*, s32);                             /* extern */
M2C_UNK fn_80168FB8(M2C_UNK*, u8*, s32*, M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK fn_80169508();                                                     /* extern */
M2C_UNK fn_80169534();                                                     /* extern */
M2C_UNK fn_8016953C();                                                     /* extern */
M2C_UNK fn_80169820();                                                     /* extern */
M2C_UNK fn_80169D58();                                                     /* extern */
u8* fn_801974E0(s32, u8**, s32, M2C_UNK*);                                 /* extern */
s32 fn_8019E8EC(s32, u8*, u8*);                                            /* extern */
M2C_UNK fn_801AD0AC(s32, s32);                                             /* extern */
u8* fn_801B3984();                                                         /* extern */
M2C_UNK fn_801B3A10();                                                     /* extern */
M2C_UNK fn_801B43EC();                                                     /* extern */
s32 fn_801B4EB4(M2C_UNK);                                                  /* extern */
s32 fn_801B51B8(u8*, s32, M2C_UNK, M2C_UNK);                               /* extern */
M2C_UNK fn_801B52BC(s32, M2C_UNK, s32*, M2C_UNK);                          /* extern */
u8* fn_80226468();                                                         /* extern */
s32 fn_80227018(u8*, s32);                                                 /* extern */
u32 fn_80227130();                                                         /* extern */
M2C_UNK fn_80227300(s32, s32, s32, s32);                                   /* extern */
M2C_UNK fn_802273D0(u8*, s32, s32, s32);                                   /* extern */
s32 fn_80227E68(M2C_UNK, s32 (*)(u8*, s32), u32 (*)(), M2C_UNK*);          /* extern */
M2C_UNK fn_802285D8(u8**, u8**);                                           /* extern */
M2C_UNK memcpy(s32, s32, s32);                                             /* extern */
M2C_UNK memset(u8*, M2C_UNK, s32);                                         /* extern */
extern M2C_UNK fn_8015C004;
extern M2C_UNK fn_80227528;
extern M2C_UNK lbl_8029BB30;
extern u16 lbl_8042BE88;
extern s32 lbl_8042C830;
extern s32 lbl_8042C930;
extern u8* lbl_8042C9A4;
extern u16 lbl_8042CA68;
static u8 lbl_8042AB90[0x20];

M2C_UNK* fn_80228BEC(u8* arg0, u8* arg1)
{
	M2C_UNK var_r5;
	M2C_UNK var_r5_2;
	M2C_UNK var_r5_3;
	M2C_UNK var_r5_4;
	M2C_UNK var_r5_5;
	s32 var_r26;
	u8 temp_r6;
	u8 var_r28;
	u8* temp_r27;
	u8* temp_r5;
	u8* var_r29;
	u8* var_r31;

	temp_r27 = fn_80226468();
	var_r31  = M2C_FIELD(arg0, u8**, lbl_8042C930);
	if (var_r31 == NULL) {
		var_r31 = fn_8015C590();
	}
	fn_80169508(&lbl_8042AB90);
	fn_80169534(&lbl_8042AB90, 0);
	if ((u32)M2C_FIELD(temp_r27, u32*, 0x10) == 1U) {
		fn_80169820(&lbl_8042AB90, 0, 1);
	}
	fn_8016953C(&lbl_8042AB90, 9, 1U, M2C_FIELD(var_r31, u8*, 0), M2C_FIELD(var_r31, u8*, 0xC));
	var_r5 = 2;
	if ((u32)M2C_FIELD(arg1, u32*, 4) >= 0xFFU) {
		var_r5 = 3;
	}
	fn_80169820(&lbl_8042AB90, 9, var_r5);
	var_r28 = 1;
	if (M2C_FIELD(arg0, s32*, 8) & 0x10) {
		if ((u8)M2C_FIELD(var_r31, u8*, 0xD) != 0) {
			fn_8016953C(&lbl_8042AB90, 0x19, 1U, M2C_FIELD(var_r31, u8*, 1), 0U);
			var_r5_2 = 2;
			if ((u32)M2C_FIELD((arg1 + 8), u32*, 4) >= 0xFFU) {
				var_r5_2 = 3;
			}
			fn_80169820(&lbl_8042AB90, 0x19, var_r5_2);
		} else {
			fn_8016953C(&lbl_8042AB90, 0xA, 0U, M2C_FIELD(var_r31, u8*, 1), 0U);
			var_r5_3 = 2;
			if ((u32)M2C_FIELD((arg1 + 8), u32*, 4) >= 0xFFU) {
				var_r5_3 = 3;
			}
			fn_80169820(&lbl_8042AB90, 0xA, var_r5_3);
		}
		var_r28 = 2;
	}
	if (M2C_FIELD(arg0, s32*, 8) & 8) {
		temp_r6 = M2C_FIELD(var_r31, u8*, 0xA);
		fn_8016953C(&lbl_8042AB90, 0xB, (u32)(2 - temp_r6) >> 0x1FU, temp_r6, 0U);
		var_r5_4 = 2;
		if ((u32)M2C_FIELD((arg1 + (var_r28 * 8)), u32*, 4) >= 0xFFU) {
			var_r5_4 = 3;
		}
		fn_80169820(&lbl_8042AB90, 0xB, var_r5_4);
		var_r28 += 1;
	}
	if (M2C_FIELD(arg0, s32*, 8) & 0x84) {
		var_r26 = 0;
		var_r29 = arg1 + (var_r28 * 8);
	loop_24:
		if (var_r26 < (s32)M2C_FIELD(arg0, s32*, 0x1C)) {
			temp_r5 = var_r31 + var_r26;
			fn_8016953C(&lbl_8042AB90, var_r26 + 0xD, 1U, M2C_FIELD(temp_r5, u8*, 2),
			    M2C_FIELD(temp_r5, u8*, 0xE));
			var_r5_5 = 2;
			if ((u32)M2C_FIELD(var_r29, u32*, 4) >= 0xFFU) {
				var_r5_5 = 3;
			}
			fn_80169820(&lbl_8042AB90, var_r26 + 0xD, var_r5_5);
			var_r29 += 8;
			var_r28 += 1;
			var_r26 += 1;
			goto loop_24;
		}
	}
	fn_80169D58(&lbl_8042AB90, var_r28);
	return (M2C_UNK*)lbl_8042AB90;
}

void fn_80228E5C(u8* arg0, u16* arg1, u32* arg2, s32 arg3, u32 arg4, u8* arg_sp0)
{
	u8 sp8;
	s16* var_r6_2;
	s16* var_r7;
	s32 temp_r0;
	s32 temp_r0_3;
	u8* temp_r4;
	s32 temp_r9;
	s32 temp_r9_2;
	s32 temp_r9_3;
	s32 temp_r9_4;
	s32 var_ctr_2;
	s32 var_r7_2;
	s32 var_r8;
	s32 var_r8_2;
	s32 var_r9;
	s32 var_r9_2;
	u16* var_r5_2;
	u16* var_r6;
	u32 temp_r0_4;
	u32 var_ctr_3;
	u8* var_r10;
	u8* var_r5;
	u8 temp_r0_2;
	u8 temp_r12;
	u8 temp_r27;
	u8 temp_r3;
	u8 temp_r8;
	u8 var_ctr;
	u8 var_r26;
	u8* temp_r3_2;

	if ((u32)M2C_FIELD(arg0, u32*, 0x34) != 0U) {
		temp_r4 = M2C_FIELD(arg0, u8**, 0x40);
		temp_r0 = arg4 * 2;
		var_r10 = &sp8;
		var_r9  = 0;
		temp_r3 = M2C_FIELD((temp_r4 + temp_r0), u8*, 1);
		var_ctr = temp_r3;
		if ((s32)temp_r3 > 0) {
			do {
				var_r26 = 0;
				temp_r3_2
				    = M2C_FIELD(arg0, u8**, 0x44) + var_r9 + ((*(temp_r4 + temp_r0) * 2) & 0xFE);
				temp_r27 = M2C_FIELD(temp_r3_2, u8*, 1);
				temp_r12 = M2C_FIELD(temp_r3_2, u8*, 0);
				if (temp_r27 > 0U) {
					if (temp_r27 > 8U) {
					loop_6:
						if (var_r26 < (u8)(temp_r27 - 8)) {
							temp_r8 = temp_r12 + var_r26;
							var_r26 += 8;
							M2C_FIELD(var_r10, u8*, 0) = temp_r8;
							M2C_FIELD(var_r10, s8*, 1) = (s8)(temp_r8 + 1);
							M2C_FIELD(var_r10, s8*, 2) = (s8)(temp_r8 + 2);
							M2C_FIELD(var_r10, s8*, 3) = (s8)(temp_r8 + 3);
							M2C_FIELD(var_r10, s8*, 4) = (s8)(temp_r8 + 4);
							M2C_FIELD(var_r10, s8*, 5) = (s8)(temp_r8 + 5);
							M2C_FIELD(var_r10, s8*, 6) = (s8)(temp_r8 + 6);
							M2C_FIELD(var_r10, s8*, 7) = (s8)(temp_r8 + 7);
							var_r10 += 8;
							goto loop_6;
						}
					}
				loop_9:
					if (var_r26 < temp_r27) {
						temp_r0_2 = temp_r12 + var_r26;
						var_r26 += 1;
						*var_r10 = temp_r0_2;
						var_r10 += 1;
						goto loop_9;
					}
				}
				var_r9 += 2;
				var_ctr -= 1;
			} while (var_ctr != 0);
		}
		var_r6 = arg1;
		var_r8 = 0;
		var_r7 = M2C_FIELD(lbl_8042C9A4, s16 * (**)(s32, u8*), 0x134)(arg3 * 2, lbl_8042C9A4);
	loop_25:
		if (var_r8 < arg3) {
			var_r5    = &sp8;
			var_r9_2  = 0;
			var_ctr_2 = 2;
		loop_13:
			temp_r0_3 = *(arg2 + (*var_r6 * 4));
			if ((u8)M2C_FIELD(var_r5, u8*, 0) == (u8)temp_r0_3) {
				*var_r7 = var_r9_2 * 3;
			} else {
				temp_r9 = var_r9_2 + 1;
				if ((u8)M2C_FIELD(var_r5, u8*, 1) == (u8)temp_r0_3) {
					*var_r7 = temp_r9 * 3;
				} else {
					temp_r9_2 = temp_r9 + 1;
					if ((u8)M2C_FIELD(var_r5, u8*, 2) == (u8)temp_r0_3) {
						*var_r7 = temp_r9_2 * 3;
					} else {
						temp_r9_3 = temp_r9_2 + 1;
						if ((u8)M2C_FIELD(var_r5, u8*, 3) == (u8)temp_r0_3) {
							*var_r7 = temp_r9_3 * 3;
						} else {
							temp_r9_4 = temp_r9_3 + 1;
							if ((u8)M2C_FIELD(var_r5, u8*, 4) == (u8)temp_r0_3) {
								*var_r7 = temp_r9_4 * 3;
							} else {
								var_r5 += 5;
								var_r9_2 = temp_r9_4 + 1;
								var_ctr_2 -= 1;
								if (var_ctr_2 != 0) {
									goto loop_13;
								}
							}
						}
					}
				}
			}
			var_r6 += 2;
			var_r7 += 2;
			var_r8 += 1;
			goto loop_25;
		}
		return;
	}
	var_r5_2 = arg1;
	var_r7_2 = 0;
	var_r6_2 = M2C_FIELD(lbl_8042C9A4, s16 * (**)(s32, u8*), 0x134)(arg3 * 2, lbl_8042C9A4);
loop_33:
	if (var_r7_2 < arg3) {
		temp_r0_4 = M2C_FIELD(arg0, u32*, 4);
		var_r8_2  = 0;
		var_ctr_3 = temp_r0_4;
		if (temp_r0_4 > 0U) {
		loop_29:
			if (*(M2C_FIELD(arg0, u8**, 8) + var_r8_2) == (u8) * (arg2 + (*var_r5_2 * 4))) {
				*var_r6_2 = var_r8_2 * 3;
			} else {
				var_r8_2 += 1;
				var_ctr_3 -= 1;
				if (var_ctr_3 != 0U) {
					goto loop_29;
				}
			}
		}
		var_r5_2 += 2;
		var_r6_2 += 2;
		var_r7_2 += 1;
		goto loop_33;
	}
}

u8* fn_802290F0(u8* arg0, s32 arg1, u8** arg2, M2C_UNK arg_sp0)
{
	s32 sp90[64];
	u8* sp28[64];
	s32 sp124;
	s32 sp120;
	s32 sp11C;
	s32 spBC;
	s32 spB8;
	s32 spB4;
	s32 sp54;
	s32 sp50;
	s32 sp4C;
	u8* sp24;
	u8* sp20;
	s32 sp1C;
	s32 sp18;
	s32 sp14;
	s32 sp10;
	s32 sp8;
	M2C_UNK* temp_r22;
	M2C_UNK var_r3_2;
	s32* var_r4_3;
	s32* var_r4_4;
	s32* var_r5;
	s32* var_r6;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 temp_r0_4;
	s32 temp_r0_5;
	s32 temp_r0_6;
	s32 temp_r0_7;
	s32 temp_r0_8;
	s32 temp_r10_2;
	s32 temp_r10_3;
	s32 temp_r11_2;
	s32 temp_r11_3;
	s32 temp_r12_2;
	s32 temp_r12_3;
	s32 temp_r15_4;
	s32 temp_r15_5;
	s32 temp_r15_6;
	s32 temp_r19;
	s32 temp_r23;
	s32 temp_r25;
	s32 temp_r3_10;
	s32 temp_r3_12;
	s32 temp_r3_13;
	s32 temp_r3_14;
	s32 temp_r3_2;
	s32 temp_r3_6;
	s32 temp_r3_8;
	s32 temp_r3_9;
	s32 temp_r4_2;
	s32 temp_r4_3;
	s32 temp_r4_4;
	s32 temp_r4_5;
	s32 temp_r5;
	s32 temp_r8;
	s32 var_ctr_11;
	s32 var_ctr_2;
	s32 var_ctr_3;
	s32 var_ctr_5;
	s32 var_ctr_7;
	s32 var_ctr_9;
	s32 var_r15;
	s32 var_r15_2;
	s32 var_r19;
	s32 var_r23;
	s32 var_r25;
	s32 var_r29;
	s32 var_r30;
	s32 var_r4;
	s32 var_r4_2;
	s32 var_r5_4;
	s32 var_r5_6;
	s32 var_r6_2;
	s32 var_r6_4;
	s32 var_r6_5;
	s32 var_r7;
	s32 var_r7_4;
	s32 var_r8;
	s32 var_r8_2;
	u32 temp_r3_11;
	u32 temp_r3_7;
	u32 temp_r6;
	u32 temp_r6_3;
	u32 var_ctr;
	u32 var_ctr_10;
	u32 var_ctr_4;
	u32 var_ctr_6;
	u32 var_ctr_8;
	u32 var_r16;
	u32 var_r20;
	u32 var_r26;
	u32 var_r3;
	u32 var_r5_3;
	u32 var_r5_5;
	u8 temp_r16_2;
	u8 temp_r17;
	u8 temp_r18;
	u8** var_r6_3;
	u8** var_r6_6;
	u8** var_r7_2;
	u8** var_r7_3;
	u8* temp_r10;
	u8* temp_r11;
	u8* temp_r12;
	u8* temp_r15;
	u8* temp_r15_2;
	u8* temp_r15_3;
	u8* temp_r16;
	u8* temp_r17_2;
	u8* temp_r20;
	u8* temp_r3;
	u8* temp_r3_3;
	u8* temp_r3_4;
	u8* temp_r3_5;
	u8* temp_r4;
	u8* temp_r4_6;
	u8* temp_r5_2;
	u8* temp_r6_2;
	u8* temp_r9;
	u8* temp_r9_2;
	u8* var_r18;
	u8* var_r28;
	u8* var_r5_2;

	fn_802285D8(&sp24, &sp20);
	temp_r22 = fn_80228BEC(arg0, sp24);
	temp_r18 = (u8)M2C_FIELD(arg0, s32*, 0x1C);
	temp_r19 = M2C_FIELD(arg0, s32*, 8);
	if ((u32)M2C_FIELD(arg0, u8**, lbl_8042C930) == 0U) {
		fn_8015C590();
	}
	var_r4 = 1;
	spB4   = M2C_FIELD(sp24, s32*, 4);
	sp11C  = M2C_FIELD(sp24, s32*, 0);
	if (temp_r19 & 0x10) {
		var_r4 = 2;
		spB8   = M2C_FIELD((sp24 + 8), s32*, 4);
		sp120  = M2C_FIELD(sp24, s32*, 8);
	}
	if (temp_r19 & 8) {
		temp_r5 = var_r4 * 8;
		var_r4 += 1;
		spBC  = M2C_FIELD((sp24 + temp_r5), s32*, 4);
		sp124 = *(sp24 + temp_r5);
	}
	if (temp_r19 & 0x84) {
		var_r3 = 0;
		if (temp_r18 > 0U) {
			temp_r6 = temp_r18 - 8;
			if (temp_r18 > 8U) {
				var_r5  = &sp90[0];
				var_r7  = var_r4 * 8;
				var_ctr = (u32)(temp_r6 + 7) >> 3U;
				if (temp_r6 > 0U) {
					do {
						temp_r9                       = sp24 + var_r7;
						M2C_FIELD(var_r5, s32*, 0x34) = (s32)M2C_FIELD(temp_r9, s32*, 4);
						M2C_FIELD(var_r5, s32*, 0x9C) = (s32)M2C_FIELD(temp_r9, s32*, 0);
						temp_r15                      = sp24 + ((var_r4 + 1) * 8);
						temp_r11                      = sp24 + ((var_r4 + 2) * 8);
						M2C_FIELD(var_r5, s32*, 0x38) = (s32)M2C_FIELD(temp_r15, s32*, 4);
						temp_r12                      = sp24 + ((var_r4 + 5) * 8);
						temp_r10                      = sp24 + ((var_r4 + 3) * 8);
						temp_r9_2                     = sp24 + ((var_r4 + 4) * 8);
						temp_r15_2                    = sp24 + ((var_r4 + 6) * 8);
						temp_r6_2                     = sp24 + ((var_r4 + 7) * 8);
						var_r4 += 8;
						M2C_FIELD(var_r5, s32*, 0xA0) = (s32)M2C_FIELD(temp_r15, s32*, 0);
						var_r7 += 0x40;
						var_r3 += 8;
						M2C_FIELD(var_r5, s32*, 0x3C) = (s32)M2C_FIELD(temp_r11, s32*, 4);
						M2C_FIELD(var_r5, s32*, 0xA4) = (s32)M2C_FIELD(temp_r11, s32*, 0);
						M2C_FIELD(var_r5, s32*, 0x40) = (s32)M2C_FIELD(temp_r10, s32*, 4);
						M2C_FIELD(var_r5, s32*, 0xA8) = (s32)M2C_FIELD(temp_r10, s32*, 0);
						M2C_FIELD(var_r5, s32*, 0x44) = (s32)M2C_FIELD(temp_r9_2, s32*, 4);
						M2C_FIELD(var_r5, s32*, 0xAC) = (s32)M2C_FIELD(temp_r9_2, s32*, 0);
						M2C_FIELD(var_r5, s32*, 0x48) = (s32)M2C_FIELD(temp_r12, s32*, 4);
						M2C_FIELD(var_r5, s32*, 0xB0) = (s32)M2C_FIELD(temp_r12, s32*, 0);
						M2C_FIELD(var_r5, s32*, 0x4C) = (s32)M2C_FIELD(temp_r15_2, s32*, 4);
						M2C_FIELD(var_r5, s32*, 0xB4) = (s32)M2C_FIELD(temp_r15_2, s32*, 0);
						M2C_FIELD(var_r5, s32*, 0x50) = (s32)M2C_FIELD(temp_r6_2, s32*, 4);
						M2C_FIELD(var_r5, s32*, 0xB8) = (s32)M2C_FIELD(temp_r6_2, s32*, 0);
						var_r5 += 0x20;
						var_ctr -= 1;
					} while (var_ctr != 0);
				}
			}
			var_r5_2  = sp24 + (var_r4 * 8);
			var_r6    = &(&sp90[0])[var_r3];
			var_ctr_2 = temp_r18 - var_r3;
			if (var_r3 < temp_r18) {
				do {
					M2C_FIELD(var_r6, s32*, 0x34) = (s32)M2C_FIELD(var_r5_2, s32*, 4);
					temp_r0                       = M2C_FIELD(var_r5_2, s32*, 0);
					var_r5_2 += 8;
					M2C_FIELD(var_r6, s32*, 0x9C) = temp_r0;
					var_r6 += 4;
					var_ctr_2 -= 1;
				} while (var_ctr_2 != 0);
			}
		}
	}
	temp_r3_2 = fn_80168778(temp_r22);
	var_r3_2  = 0x90;
	temp_r25  = M2C_FIELD(M2C_FIELD(arg0, u8**, 0x54), u16*, 4) * 8;
	var_r23   = temp_r3_2 + temp_r25 + 0x1F;
	if (M2C_FIELD(arg0, s32*, 8) & 1) {
		var_r3_2 = 0x98;
	}
	var_r15 = 0;
	var_r19 = 0;
	var_r20 = 0U;
loop_20:
	temp_r3_3 = M2C_FIELD(arg0, u8**, 0x54);
	if (var_r20 < (u16)M2C_FIELD(temp_r3_3, u16*, 4)) {
		if (M2C_FIELD(arg0, s32*, 8) & 1) {
			fn_801671B4(**(s32**)(sp20 + var_r19), M2C_FIELD((temp_r3_3 + var_r15), s32*, 0x14),
			    &sp1C, &sp18, 1);
			var_r23 += fn_801649BC(temp_r22, sp1C, sp18);
		} else {
			var_r23 += fn_801649BC(temp_r22, 1, M2C_FIELD((temp_r3_3 + var_r15), s32*, 0x14));
		}
		var_r15 += 0xC;
		var_r19 += 4;
		var_r20 += 1;
		goto loop_20;
	}
	temp_r23 = var_r23 + fn_8016878C(temp_r22, &sp90[0]);
	temp_r3  = M2C_FIELD(lbl_8042C9A4, u8 * (**)(s32, u8*), 0x134)(temp_r23 + 0x18, lbl_8042C9A4);
	M2C_FIELD(temp_r3, s32*, 0)         = 0;
	temp_r15_3                          = temp_r3 + 0x18;
	M2C_FIELD(temp_r3, s32*, 4)         = 0;
	M2C_FIELD(temp_r3, s32*, 0xC)       = arg1;
	M2C_FIELD(temp_r3, s32*, 8)         = temp_r23;
	M2C_FIELD(temp_r3, u8***, 0x10)     = arg2;
	M2C_FIELD(temp_r3, M2C_UNK**, 0x14) = &fn_8015C004;
	*arg2                               = temp_r3;
	memset(temp_r15_3, 0, temp_r23);
	var_r4_2                       = 0;
	M2C_FIELD(temp_r3, u16*, 0x18) = (u16)lbl_8042CA68;
	M2C_FIELD(temp_r15_3, u16*, 2) = (u16)M2C_FIELD(M2C_FIELD(arg0, u8**, 0x54), u16*, 6);
	M2C_FIELD(temp_r15_3, s32*, 4) = 0;
	if (M2C_FIELD(arg0, s32*, 8) & 8) {
		temp_r3_4 = M2C_FIELD(arg0, u8**, lbl_8042C930);
		if (temp_r3_4 == NULL) {
			M2C_FIELD(temp_r15_3, s32*, 4) = (s32)(M2C_FIELD(temp_r15_3, s32*, 4) & 0xFFFFFFFE);
			temp_r0_2                      = M2C_FIELD(arg0, s32*, 0x14);
			var_ctr_3                      = temp_r0_2;
			if (temp_r0_2 > 0) {
			loop_24:
				if (*(M2C_FIELD(arg0, u8**, 0x30) + var_r4_2 + 3) < 0xFFU) {
					M2C_FIELD(temp_r15_3, s32*, 4) = (s32)(M2C_FIELD(temp_r15_3, s32*, 4) | 1);
				} else {
					var_r4_2 += 4;
					var_ctr_3 -= 1;
					if (var_ctr_3 == 0) {

					} else {
						goto loop_24;
					}
				}
			}
		} else if ((u8)M2C_FIELD(temp_r3_4, u8*, 0xA) > 2U) {
			M2C_FIELD(temp_r15_3, s32*, 4) = (s32)(M2C_FIELD(temp_r15_3, s32*, 4) | 1);
		} else {
			M2C_FIELD(temp_r15_3, s32*, 4) = (s32)(M2C_FIELD(temp_r15_3, s32*, 4) & 0xFFFFFFFE);
		}
	}
	temp_r5_2 = temp_r15_3 + temp_r3_2;
	temp_r4   = temp_r5_2 + temp_r25;
	var_r25   = (s32)(temp_r4 + 0x1F) & 0xFFFFFFE0;
	var_r26   = 0;
	temp_r20  = fn_80226468(arg0, temp_r4, temp_r5_2);
	var_r28   = temp_r5_2;
	var_r30   = 0;
	var_r29   = 0;
loop_79:
	temp_r3_5 = M2C_FIELD(arg0, u8**, 0x54);
	if (var_r26 < (u16)M2C_FIELD(temp_r3_5, u16*, 4)) {
		var_r18 = NULL;
		if (M2C_FIELD(arg0, s32*, 8) & 1) {
			fn_801671B4(**(s32**)(sp20 + var_r29), M2C_FIELD((temp_r3_5 + var_r30), s32*, 0x14),
			    &sp14, &sp10, 1);
		} else {
			sp10 = M2C_FIELD((temp_r3_5 + var_r30), s32*, 0x14);
			sp14 = 1;
		}
		temp_r3_6 = fn_801649BC(temp_r22, sp14, sp10);
		fn_80164A08(var_r28, var_r26, temp_r3_6, var_r25);
		if ((u32)M2C_FIELD(temp_r20, u32*, 0x10) > 1U) {
			temp_r16   = *(u8**)(sp20 + var_r29);
			temp_r15_4 = M2C_FIELD(arg0, s32*, 8);
			temp_r17   = (u8)M2C_FIELD(arg0, s32*, 0x1C);
			if ((u32)M2C_FIELD(arg0, u8**, lbl_8042C930) == 0U) {
				fn_8015C590();
			}
			var_r6_2 = 1;
			sp4C     = M2C_FIELD(temp_r16, s32*, 0);
			if (temp_r15_4 & 0x10) {
				var_r6_2 = 2;
				sp50     = M2C_FIELD(temp_r16, s32*, 4);
			}
			if (temp_r15_4 & 8) {
				temp_r0_3 = var_r6_2 * 4;
				var_r6_2 += 1;
				sp54 = *(temp_r16 + temp_r0_3);
			}
			if (temp_r15_4 & 0x84) {
				var_r5_3 = 0;
				if (temp_r17 > 0U) {
					temp_r3_7 = temp_r17 - 8;
					if (temp_r17 > 8U) {
						var_r7_2  = &sp28[0];
						var_r8    = var_r6_2 * 4;
						var_ctr_4 = (u32)(temp_r3_7 + 7) >> 3U;
						if (temp_r3_7 > 0U) {
							do {
								M2C_FIELD(var_r7_2, s32*, 0x34) = (s32) * (temp_r16 + var_r8);
								M2C_FIELD(var_r7_2, s32*, 0x38)
								    = (s32) * (temp_r16 + ((var_r6_2 + 1) * 4));
								temp_r3_8  = (var_r6_2 + 3) * 4;
								temp_r0_4  = (var_r6_2 + 4) * 4;
								temp_r11_2 = (var_r6_2 + 5) * 4;
								temp_r12_2 = *(temp_r16 + ((var_r6_2 + 2) * 4));
								temp_r10_2 = (var_r6_2 + 6) * 4;
								temp_r4_2  = (var_r6_2 + 7) * 4;
								var_r6_2 += 8;
								M2C_FIELD(var_r7_2, s32*, 0x3C) = temp_r12_2;
								var_r8 += 0x20;
								var_r5_3 += 8;
								M2C_FIELD(var_r7_2, s32*, 0x40) = (s32) * (temp_r16 + temp_r3_8);
								M2C_FIELD(var_r7_2, s32*, 0x44) = (s32) * (temp_r16 + temp_r0_4);
								M2C_FIELD(var_r7_2, s32*, 0x48) = (s32) * (temp_r16 + temp_r11_2);
								M2C_FIELD(var_r7_2, s32*, 0x4C) = (s32) * (temp_r16 + temp_r10_2);
								M2C_FIELD(var_r7_2, s32*, 0x50) = (s32) * (temp_r16 + temp_r4_2);
								var_r7_2 += 0x20;
								var_ctr_4 -= 1;
							} while (var_ctr_4 != 0);
						}
					}
					var_r4_3  = (s32*)(temp_r16 + (var_r6_2 * 4));
					var_r6_3  = &(&sp28[0])[var_r5_3];
					var_ctr_5 = temp_r17 - var_r5_3;
					if (var_r5_3 < temp_r17) {
						do {
							temp_r0_5 = *var_r4_3;
							var_r4_3 += 4;
							M2C_FIELD(var_r6_3, s32*, 0x34) = temp_r0_5;
							var_r6_3 += 4;
							var_ctr_5 -= 1;
						} while (var_ctr_5 != 0);
					}
				}
			}
		} else {
			temp_r3_9 = M2C_FIELD(arg0, s32*, 8);
			var_r5_4  = 1;
			if (temp_r3_9 & 0x10) {
				var_r5_4 = 2;
			}
			if (temp_r3_9 & 8) {
				var_r5_4 += 1;
			}
			if (temp_r3_9 & 0x84) {
				temp_r4_3 = M2C_FIELD(arg0, s32*, 0x1C);
				var_r6_4  = 0;
				if (temp_r4_3 > 0) {
					temp_r3_10 = temp_r4_3 - 8;
					if (temp_r4_3 > 8) {
						var_ctr_6 = (u32)(temp_r3_10 + 7) >> 3U;
						if (temp_r3_10 > 0) {
							do {
								var_r5_4 += 8;
								var_r6_4 += 8;
								var_ctr_6 -= 1;
							} while (var_ctr_6 != 0);
						}
					}
					var_ctr_7 = temp_r4_3 - var_r6_4;
					if (var_r6_4 < temp_r4_3) {
						do {
							var_r5_4 += 1;
							var_ctr_7 -= 1;
						} while (var_ctr_7 != 0);
					}
				}
			}
			fn_80228E5C(temp_r20, *(u16**)(sp20 + var_r29), *(u32**)(sp24 + (var_r5_4 * 8)),
			    M2C_FIELD((M2C_FIELD(arg0, u8**, 0x54) + var_r30), s32*, 0x14), var_r26, sp24);
			temp_r17_2 = *(u8**)(sp20 + var_r29);
			temp_r15_5 = M2C_FIELD(arg0, s32*, 8);
			temp_r16_2 = (u8)M2C_FIELD(arg0, s32*, 0x1C);
			if ((u32)M2C_FIELD(arg0, u8**, lbl_8042C930) == 0U) {
				fn_8015C590();
			}
			if (var_r18 != NULL) {
				sp28[0] = var_r18;
			}
			var_r6_5 = 1;
			sp4C     = M2C_FIELD(temp_r17_2, s32*, 0);
			if (temp_r15_5 & 0x10) {
				var_r6_5 = 2;
				sp50     = M2C_FIELD(temp_r17_2, s32*, 4);
			}
			if (temp_r15_5 & 8) {
				temp_r0_6 = var_r6_5 * 4;
				var_r6_5 += 1;
				sp54 = *(temp_r17_2 + temp_r0_6);
			}
			if (temp_r15_5 & 0x84) {
				var_r5_5 = 0;
				if (temp_r16_2 > 0U) {
					temp_r3_11 = temp_r16_2 - 8;
					if (temp_r16_2 > 8U) {
						var_r7_3  = &sp28[0];
						var_r8_2  = var_r6_5 * 4;
						var_ctr_8 = (u32)(temp_r3_11 + 7) >> 3U;
						if (temp_r3_11 > 0U) {
							do {
								M2C_FIELD(var_r7_3, s32*, 0x34) = (s32) * (temp_r17_2 + var_r8_2);
								M2C_FIELD(var_r7_3, s32*, 0x38)
								    = (s32) * (temp_r17_2 + ((var_r6_5 + 1) * 4));
								temp_r3_12 = (var_r6_5 + 3) * 4;
								temp_r0_7  = (var_r6_5 + 4) * 4;
								temp_r11_3 = (var_r6_5 + 5) * 4;
								temp_r12_3 = *(temp_r17_2 + ((var_r6_5 + 2) * 4));
								temp_r10_3 = (var_r6_5 + 6) * 4;
								temp_r4_4  = (var_r6_5 + 7) * 4;
								var_r6_5 += 8;
								M2C_FIELD(var_r7_3, s32*, 0x3C) = temp_r12_3;
								var_r8_2 += 0x20;
								var_r5_5 += 8;
								M2C_FIELD(var_r7_3, s32*, 0x40) = (s32) * (temp_r17_2 + temp_r3_12);
								M2C_FIELD(var_r7_3, s32*, 0x44) = (s32) * (temp_r17_2 + temp_r0_7);
								M2C_FIELD(var_r7_3, s32*, 0x48) = (s32) * (temp_r17_2 + temp_r11_3);
								M2C_FIELD(var_r7_3, s32*, 0x4C) = (s32) * (temp_r17_2 + temp_r10_3);
								M2C_FIELD(var_r7_3, s32*, 0x50) = (s32) * (temp_r17_2 + temp_r4_4);
								var_r7_3 += 0x20;
								var_ctr_8 -= 1;
							} while (var_ctr_8 != 0);
						}
					}
					var_r4_4  = (s32*)(temp_r17_2 + (var_r6_5 * 4));
					var_r6_6  = &(&sp28[0])[var_r5_5];
					var_ctr_9 = temp_r16_2 - var_r5_5;
					if (var_r5_5 < temp_r16_2) {
						do {
							temp_r0_8 = *var_r4_4;
							var_r4_4 += 4;
							M2C_FIELD(var_r6_6, s32*, 0x34) = temp_r0_8;
							var_r6_6 += 4;
							var_ctr_9 -= 1;
						} while (var_ctr_9 != 0);
					}
				}
			}
		}
		temp_r8 = fn_801645E4(temp_r22);
		sp8     = 0;
		fn_80167E80(temp_r22, var_r28, &sp28[0],
		    M2C_FIELD((M2C_FIELD(arg0, u8**, 0x54) + var_r30), s32*, 0x14), sp14, temp_r8, 1,
		    var_r3_2);
		if (var_r18 != NULL) {
			M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, u8*), 0x138)(var_r18, lbl_8042C9A4);
		}
		var_r25 += temp_r3_6;
		var_r30 += 0xC;
		var_r29 += 4;
		var_r28 += 8;
		var_r26 += 1;
		goto loop_79;
	}
	fn_80168AF4(temp_r22, temp_r15_3, &sp90[0], var_r25);
	fn_80168FB8(temp_r22, temp_r15_3, &sp90[0], 0, 0);
	temp_r6_3 = M2C_FIELD(temp_r20, u32*, 0x10);
	if (temp_r6_3 > 1U) {
		temp_r3_13 = M2C_FIELD(arg0, s32*, 8);
		var_r5_6   = 1;
		if (temp_r3_13 & 0x10) {
			var_r5_6 = 2;
		}
		if (temp_r3_13 & 8) {
			var_r5_6 += 1;
		}
		if (temp_r3_13 & 0x84) {
			temp_r4_5 = M2C_FIELD(arg0, s32*, 0x1C);
			var_r7_4  = 0;
			if (temp_r4_5 > 0) {
				temp_r3_14 = temp_r4_5 - 8;
				if (temp_r4_5 > 8) {
					var_ctr_10 = (u32)(temp_r3_14 + 7) >> 3U;
					if (temp_r3_14 > 0) {
						do {
							var_r5_6 += 8;
							var_r7_4 += 8;
							var_ctr_10 -= 1;
						} while (var_ctr_10 != 0);
					}
				}
				var_ctr_11 = temp_r4_5 - var_r7_4;
				if (var_r7_4 < temp_r4_5) {
					do {
						var_r5_6 += 1;
						var_ctr_11 -= 1;
					} while (var_ctr_11 != 0);
				}
			}
		}
		temp_r15_6 = var_r5_6 * 8;
		memcpy(M2C_FIELD(temp_r20, s32*, 0x28), *(sp24 + temp_r15_6),
		    temp_r6_3 * M2C_FIELD((sp24 + temp_r15_6), s32*, 4));
		temp_r4_6 = sp24 + temp_r15_6;
		memcpy(M2C_FIELD(temp_r20, s32*, 0x24), M2C_FIELD(temp_r4_6, s32*, 8),
		    M2C_FIELD(temp_r20, u32*, 0x10) * M2C_FIELD(temp_r4_6, s32*, 0xC));
	}
	M2C_FIELD(arg0, s32*, 0x14) = (s32)M2C_FIELD(sp24, s32*, 4);
	DCFlushRange(temp_r15_3, temp_r23, sp24);
	GXInvalidateVtxCache();
	var_r16   = 0U;
	var_r15_2 = 0;
loop_95:
	if (var_r16 < (u16)M2C_FIELD(M2C_FIELD(arg0, u8**, 0x54), u16*, 4)) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, u8*), 0x138)(*(u8**)(sp20 + var_r15_2), sp20);
		var_r15_2 += 4;
		var_r16 += 1;
		goto loop_95;
	}
	M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, u8*), 0x138)(sp20, lbl_8042C9A4);
	M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, u8*), 0x138)(sp24, lbl_8042C9A4);
	return temp_r3;
}

M2C_UNK* fn_80229B48(u8* arg0)
{
	M2C_UNK var_r5;
	M2C_UNK var_r5_2;
	M2C_UNK var_r5_3;
	M2C_UNK var_r5_4;
	M2C_UNK var_r5_5;
	s32 var_r26;
	u32 temp_r29;
	u8 temp_r6;
	u8 var_r28;
	u8* temp_r5;
	u8* var_r31;

	temp_r29 = M2C_FIELD(arg0, u32*, 0x14);
	var_r31  = M2C_FIELD(arg0, u8**, lbl_8042C930);
	if (var_r31 == NULL) {
		var_r31 = fn_8015C590();
	}
	fn_80169508(&lbl_8042AB90);
	fn_80169534(&lbl_8042AB90, 0);
	fn_80169820(&lbl_8042AB90, 0, 1);
	fn_8016953C(&lbl_8042AB90, 9, 1U, M2C_FIELD(var_r31, u8*, 0), M2C_FIELD(var_r31, u8*, 0xC));
	var_r5 = 2;
	if (temp_r29 >= 0xFFU) {
		var_r5 = 3;
	}
	fn_80169820(&lbl_8042AB90, 9, var_r5);
	var_r28 = 1;
	if (M2C_FIELD(arg0, s32*, 8) & 0x10) {
		if ((u8)M2C_FIELD(var_r31, u8*, 0xD) != 0) {
			fn_8016953C(&lbl_8042AB90, 0x19, 1U, M2C_FIELD(var_r31, u8*, 1), 0U);
			var_r5_2 = 2;
			if (temp_r29 >= 0xFFU) {
				var_r5_2 = 3;
			}
			fn_80169820(&lbl_8042AB90, 0x19, var_r5_2);
		} else {
			fn_8016953C(&lbl_8042AB90, 0xA, 0U, M2C_FIELD(var_r31, u8*, 1), 0U);
			var_r5_3 = 2;
			if (temp_r29 >= 0xFFU) {
				var_r5_3 = 3;
			}
			fn_80169820(&lbl_8042AB90, 0xA, var_r5_3);
		}
		var_r28 = 2;
	}
	if (M2C_FIELD(arg0, s32*, 8) & 8) {
		temp_r6 = M2C_FIELD(var_r31, u8*, 0xA);
		fn_8016953C(&lbl_8042AB90, 0xB, (u32)(2 - temp_r6) >> 0x1FU, temp_r6, 0U);
		var_r5_4 = 2;
		if (temp_r29 >= 0xFFU) {
			var_r5_4 = 3;
		}
		fn_80169820(&lbl_8042AB90, 0xB, var_r5_4);
		var_r28 += 1;
	}
	if (M2C_FIELD(arg0, s32*, 8) & 0x84) {
		var_r26 = 0;
	loop_22:
		if (var_r26 < (s32)M2C_FIELD(arg0, s32*, 0x1C)) {
			temp_r5 = var_r31 + var_r26;
			fn_8016953C(&lbl_8042AB90, var_r26 + 0xD, 1U, M2C_FIELD(temp_r5, u8*, 2),
			    M2C_FIELD(temp_r5, u8*, 0xE));
			var_r5_5 = 2;
			if (temp_r29 >= 0xFFU) {
				var_r5_5 = 3;
			}
			fn_80169820(&lbl_8042AB90, var_r26 + 0xD, var_r5_5);
			var_r28 += 1;
			var_r26 += 1;
			goto loop_22;
		}
	}
	fn_80169D58(&lbl_8042AB90, var_r28);
	return (M2C_UNK*)lbl_8042AB90;
}

u8* fn_80229D6C(u8* arg0, u8* arg1, u32 arg2)
{
	u8 sp8;
	s16* var_r7_2;
	s16* var_r8;
	s16* result;
	s32 temp_r0;
	s32 temp_r0_3;
	s32 temp_r10;
	s32 temp_r10_2;
	s32 temp_r10_3;
	s32 temp_r10_4;
	u8* temp_r4;
	s32 var_ctr_2;
	s32 var_r10_2;
	s32 var_r6_2;
	s32 var_r7;
	s32 var_r9;
	s32 var_r9_3;
	u32 temp_r0_4;
	u32 var_ctr_3;
	u32 var_r8_2;
	u32 var_r9_2;
	u8* var_r10;
	u8* var_r6;
	u8 temp_r0_2;
	u8 temp_r12;
	u8 temp_r29;
	u8 temp_r3;
	u8 temp_r8;
	u8 var_ctr;
	u8 var_r28;
	u8* temp_r3_2;

	if ((u32)M2C_FIELD(arg0, u32*, 0x34) != 0U) {
		temp_r4 = M2C_FIELD(arg0, u8**, 0x40);
		temp_r0 = arg2 * 2;
		var_r10 = &sp8;
		var_r9  = 0;
		temp_r3 = M2C_FIELD((temp_r4 + temp_r0), u8*, 1);
		var_ctr = temp_r3;
		if (temp_r3 > 0U) {
			do {
				var_r28 = 0;
				temp_r3_2
				    = M2C_FIELD(arg0, u8**, 0x44) + var_r9 + ((*(temp_r4 + temp_r0) * 2) & 0xFE);
				temp_r29 = M2C_FIELD(temp_r3_2, u8*, 1);
				temp_r12 = M2C_FIELD(temp_r3_2, u8*, 0);
				if (temp_r29 > 0U) {
					if (temp_r29 > 8U) {
					loop_6:
						if (var_r28 < (u8)(temp_r29 - 8)) {
							temp_r8 = temp_r12 + var_r28;
							var_r28 += 8;
							M2C_FIELD(var_r10, u8*, 0) = temp_r8;
							M2C_FIELD(var_r10, s8*, 1) = (s8)(temp_r8 + 1);
							M2C_FIELD(var_r10, s8*, 2) = (s8)(temp_r8 + 2);
							M2C_FIELD(var_r10, s8*, 3) = (s8)(temp_r8 + 3);
							M2C_FIELD(var_r10, s8*, 4) = (s8)(temp_r8 + 4);
							M2C_FIELD(var_r10, s8*, 5) = (s8)(temp_r8 + 5);
							M2C_FIELD(var_r10, s8*, 6) = (s8)(temp_r8 + 6);
							M2C_FIELD(var_r10, s8*, 7) = (s8)(temp_r8 + 7);
							var_r10 += 8;
							goto loop_6;
						}
					}
				loop_9:
					if (var_r28 < temp_r29) {
						temp_r0_2 = temp_r12 + var_r28;
						var_r28 += 1;
						*var_r10 = temp_r0_2;
						var_r10 += 1;
						goto loop_9;
					}
				}
				var_r9 += 2;
				var_ctr -= 1;
			} while (var_ctr != 0);
		}
		var_r9_2 = 0U;
		var_r8   = M2C_FIELD(lbl_8042C9A4, s16 * (**)(s32), 0x134)(M2C_FIELD(arg1, u32*, 4) * 2);
		result   = var_r8;
		var_r7   = 0;
	loop_25:
		if (var_r9_2 < (u32)M2C_FIELD(arg1, u32*, 4)) {
			var_r6    = &sp8;
			var_r10_2 = 0;
			var_ctr_2 = 2;
		loop_13:
			temp_r0_3 = M2C_FIELD(arg0, u32**, 0x14)[M2C_FIELD(arg1, u16**, 0)[var_r7]];
			if ((u8)M2C_FIELD(var_r6, u8*, 0) == (u8)temp_r0_3) {
				*var_r8 = var_r10_2 * 3;
			} else {
				temp_r10 = var_r10_2 + 1;
				if ((u8)M2C_FIELD(var_r6, u8*, 1) == (u8)temp_r0_3) {
					*var_r8 = temp_r10 * 3;
				} else {
					temp_r10_2 = temp_r10 + 1;
					if ((u8)M2C_FIELD(var_r6, u8*, 2) == (u8)temp_r0_3) {
						*var_r8 = temp_r10_2 * 3;
					} else {
						temp_r10_3 = temp_r10_2 + 1;
						if ((u8)M2C_FIELD(var_r6, u8*, 3) == (u8)temp_r0_3) {
							*var_r8 = temp_r10_3 * 3;
						} else {
							temp_r10_4 = temp_r10_3 + 1;
							if ((u8)M2C_FIELD(var_r6, u8*, 4) == (u8)temp_r0_3) {
								*var_r8 = temp_r10_4 * 3;
							} else {
								var_r6 += 5;
								var_r10_2 = temp_r10_4 + 1;
								var_ctr_2 -= 1;
								if (var_ctr_2 != 0) {
									goto loop_13;
								}
							}
						}
					}
				}
			}
			var_r7 += 2;
			var_r8 += 2;
			var_r9_2 += 1;
			goto loop_25;
		}
		return (u8*)result;
	}
	var_r8_2 = 0U;
	var_r7_2 = M2C_FIELD(lbl_8042C9A4, s16 * (**)(s32), 0x134)(M2C_FIELD(arg1, u32*, 4) * 2);
	result   = var_r7_2;
	var_r6_2 = 0;
loop_33:
	if (var_r8_2 < (u32)M2C_FIELD(arg1, u32*, 4)) {
		temp_r0_4 = M2C_FIELD(arg0, u32*, 4);
		var_r9_3  = 0;
		var_ctr_3 = temp_r0_4;
		if (temp_r0_4 > 0U) {
		loop_29:
			if (M2C_FIELD(arg0, u8**, 8)[var_r9_3]
			    == (u8)M2C_FIELD(arg0, u32**, 0x14)[M2C_FIELD(arg1, u16**, 0)[var_r6_2]]) {
				*var_r7_2 = var_r9_3 * 3;
			} else {
				var_r9_3 += 1;
				var_ctr_3 -= 1;
				if (var_ctr_3 != 0U) {
					goto loop_29;
				}
			}
		}
		var_r6_2 += 2;
		var_r7_2 += 2;
		var_r8_2 += 1;
		goto loop_33;
	}
	return (u8*)result;
}

u8* fn_8022A028(u8* arg0, s32 arg1, u8** arg2, M2C_UNK arg_sp0)
{
	s32 sp10C;
	s32 sp108;
	s32 sp104;
	s32 spA4;
	s32 spA0;
	s32 sp9C;
	s32 sp78;
	s32 sp3C;
	s32 sp38;
	s32 sp34;
	u8* sp10;
	s32 sp8;
	M2C_UNK* temp_r29;
	M2C_UNK var_r3_2;
	s32* var_r4;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r20;
	s32 temp_r21;
	s32 temp_r25;
	s32 temp_r3;
	s32 temp_r3_2;
	s32 temp_r3_6;
	s32 temp_r8;
	s32 var_ctr;
	s32 var_r20;
	s32 var_r21;
	s32 var_r22;
	s32 var_r24;
	s32 var_r3;
	s32 var_r3_3;
	s32 var_r4_2;
	u32 var_r22_2;
	u32 var_r23;
	u8** var_r4_3;
	u8* temp_r18;
	u8* temp_r18_2;
	u8* temp_r22;
	u8* temp_r27;
	u8* temp_r3_3;
	u8* temp_r3_4;
	u8* temp_r3_5;
	u8* temp_r4;
	u8* var_r20_2;
	u8* var_r31;
	u8* var_r5;

	temp_r27 = fn_80226468();
	temp_r29 = fn_80229B48(arg0);
	if ((u32)M2C_FIELD(arg0, u8**, lbl_8042C930) == 0U) {
		fn_8015C590();
	}
	temp_r4 = M2C_FIELD(arg0, u8**, 0x5C);
	temp_r3 = M2C_FIELD(arg0, s32*, 0x14);
	sp9C    = temp_r3;
	sp104   = M2C_FIELD(temp_r4, s32*, 0x14);
	if (M2C_FIELD(arg0, s32*, 8) & 0x10) {
		spA0  = temp_r3;
		sp108 = M2C_FIELD(temp_r4, s32*, 0x18);
	}
	if (M2C_FIELD(arg0, s32*, 8) & 8) {
		spA4  = M2C_FIELD(arg0, s32*, 0x14);
		sp10C = M2C_FIELD(arg0, s32*, 0x30);
	}
	if (M2C_FIELD(arg0, s32*, 8) & 0x84) {
		var_r5 = arg0;
		var_r4 = &sp78;
		var_r3 = 0;
	loop_9:
		if (var_r3 < (s32)M2C_FIELD(arg0, s32*, 0x1C)) {
			var_r3 += 1;
			M2C_FIELD(var_r4, s32*, 0x34) = (s32)M2C_FIELD(arg0, s32*, 0x14);
			temp_r0                       = M2C_FIELD(var_r5, s32*, 0x34);
			var_r5 += 4;
			M2C_FIELD(var_r4, s32*, 0x9C) = temp_r0;
			var_r4 += 4;
			goto loop_9;
		}
	}
	temp_r3_2 = fn_80168778(temp_r29);
	var_r3_2  = 0x90;
	temp_r21  = M2C_FIELD(M2C_FIELD(arg0, u8**, 0x54), u16*, 4) * 8;
	var_r20   = temp_r3_2 + temp_r21 + 0x1F;
	if (M2C_FIELD(arg0, s32*, 8) & 1) {
		var_r3_2 = 0x98;
	}
	var_r23 = 0U;
	var_r22 = 0;
loop_14:
	temp_r3_3 = M2C_FIELD(arg0, u8**, 0x54);
	if (var_r23 < (u16)M2C_FIELD(temp_r3_3, u16*, 4)) {
		var_r20 += fn_801649BC(temp_r29, 1, M2C_FIELD((temp_r3_3 + var_r22), s32*, 0x14));
		var_r22 += 0xC;
		var_r23 += 1;
		goto loop_14;
	}
	temp_r20 = var_r20 + fn_8016878C(temp_r29, &sp78);
	if (M2C_FIELD(arg0, s32*, 8) & 0x02000000) {
		var_r31
		    = M2C_FIELD(lbl_8042C9A4, u8 * (**)(s32, u8*), 0x134)(temp_r20 + 0x18, lbl_8042C9A4);
		M2C_FIELD(var_r31, s32*, 0)         = 0;
		M2C_FIELD(var_r31, s32*, 4)         = 0;
		M2C_FIELD(var_r31, s32*, 0xC)       = arg1;
		M2C_FIELD(var_r31, s32*, 8)         = temp_r20;
		M2C_FIELD(var_r31, u8***, 0x10)     = arg2;
		M2C_FIELD(var_r31, M2C_UNK**, 0x14) = &fn_8015C004;
		*arg2                               = var_r31;
	} else {
		var_r31 = fn_801974E0(arg1, arg2, temp_r20, &fn_8015C004);
	}
	temp_r22 = var_r31 + 0x18;
	memset(temp_r22, 0, temp_r20);
	var_r4_2                       = 0;
	M2C_FIELD(var_r31, u16*, 0x18) = (u16)lbl_8042CA68;
	M2C_FIELD(temp_r22, u16*, 2)   = (u16)M2C_FIELD(M2C_FIELD(arg0, u8**, 0x54), u16*, 6);
	M2C_FIELD(temp_r22, s32*, 4)   = 0;
	if (M2C_FIELD(arg0, s32*, 8) & 8) {
		temp_r3_4 = M2C_FIELD(arg0, u8**, lbl_8042C930);
		if (temp_r3_4 == NULL) {
			M2C_FIELD(temp_r22, s32*, 4) = (s32)(M2C_FIELD(temp_r22, s32*, 4) & 0xFFFFFFFE);
			temp_r0_2                    = M2C_FIELD(arg0, s32*, 0x14);
			var_ctr                      = temp_r0_2;
			if (temp_r0_2 > 0) {
			loop_21:
				if (*(M2C_FIELD(arg0, u8**, 0x30) + var_r4_2 + 3) < 0xFFU) {
					M2C_FIELD(temp_r22, s32*, 4) = (s32)(M2C_FIELD(temp_r22, s32*, 4) | 1);
				} else {
					var_r4_2 += 4;
					var_ctr -= 1;
					if (var_ctr == 0) {

					} else {
						goto loop_21;
					}
				}
			}
		} else if ((u8)M2C_FIELD(temp_r3_4, u8*, 0xA) > 2U) {
			M2C_FIELD(temp_r22, s32*, 4) = (s32)(M2C_FIELD(temp_r22, s32*, 4) | 1);
		} else {
			M2C_FIELD(temp_r22, s32*, 4) = (s32)(M2C_FIELD(temp_r22, s32*, 4) & 0xFFFFFFFE);
		}
	}
	var_r20_2 = temp_r22 + temp_r3_2;
	var_r22_2 = 0;
	var_r24   = 0;
	var_r21   = (s32)(var_r20_2 + temp_r21 + 0x1F) & 0xFFFFFFE0;
loop_40:
	temp_r3_5 = M2C_FIELD(arg0, u8**, 0x54);
	if (var_r22_2 < (u16)M2C_FIELD(temp_r3_5, u16*, 4)) {
		temp_r18  = temp_r3_5 + var_r24;
		temp_r3_6 = fn_801649BC(temp_r29, 1, M2C_FIELD(temp_r18, s32*, 0x14));
		fn_80164A08(var_r20_2, var_r22_2, temp_r3_6, var_r21);
		temp_r25   = M2C_FIELD(temp_r18, s32*, 0x10);
		temp_r18_2 = fn_80229D6C(temp_r27, temp_r18 + 0x10, var_r22_2);
		if ((u32)M2C_FIELD(arg0, u8**, lbl_8042C930) == 0U) {
			fn_8015C590();
		}
		sp10 = temp_r18_2;
		sp34 = temp_r25;
		if (M2C_FIELD(arg0, s32*, 8) & 0x10) {
			sp38 = temp_r25;
		}
		if (M2C_FIELD(arg0, s32*, 8) & 8) {
			sp3C = temp_r25;
		}
		if (M2C_FIELD(arg0, s32*, 8) & 0x84) {
			var_r4_3 = &sp10;
			var_r3_3 = 0;
		loop_38:
			if (var_r3_3 < (s32)M2C_FIELD(arg0, s32*, 0x1C)) {
				M2C_FIELD(var_r4_3, s32*, 0x34) = temp_r25;
				var_r4_3 += 4;
				var_r3_3 += 1;
				goto loop_38;
			}
		}
		temp_r8 = fn_801645E4(temp_r29);
		sp8     = 0;
		fn_80167E80(temp_r29, var_r20_2, &sp10,
		    M2C_FIELD((M2C_FIELD(arg0, u8**, 0x54) + var_r24), s32*, 0x14), 1, temp_r8, 1,
		    var_r3_2);
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(u8*, u8*), 0x138)(temp_r18_2, lbl_8042C9A4);
		var_r21 += temp_r3_6;
		var_r24 += 0xC;
		var_r20_2 += 8;
		var_r22_2 += 1;
		goto loop_40;
	}
	fn_80168AF4(temp_r29, temp_r22, &sp78, var_r21);
	fn_80168FB8(temp_r29, temp_r22, &sp78, 0, 0);
	DCFlushRange(temp_r22, temp_r20);
	GXInvalidateVtxCache();
	return var_r31;
}

f32 fn_8022A454(s32 arg0, s32 arg1, s32 arg2, s32 arg4, s32 arg5, f32 farg0)
{
	s32 var_ctr;

	var_ctr = arg5;
	do {
		M2C_ERROR(/* unknown instruction: ps_muls0 $f24, $f0, $f8 */);
		M2C_ERROR(/* unknown instruction: ps_muls0 $f25, $f1, $f8 */);
		M2C_ERROR(/* unknown instruction: ps_muls0 $f26, $f0, $f10 */);
		M2C_ERROR(/* unknown instruction: ps_muls0 $f27, $f1, $f10 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f24, $f2, $f8, $f24 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f25, $f3, $f8, $f25 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f26, $f2, $f10, $f26 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f27, $f3, $f10, $f27 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f4, $f9, $f24 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f5, $f9, $f25 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f26, $f4, $f11, $f26 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f27, $f5, $f11, $f27 */);
		M2C_ERROR(/* unknown instruction: ps_muls0 $f28, $f0, $f12 */);
		M2C_ERROR(/* unknown instruction: ps_muls0 $f29, $f1, $f12 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f30, $f0, $f14, $f6 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f31, $f1, $f14, $f7 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f28, $f2, $f12, $f28 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f29, $f3, $f12, $f29 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f30, $f2, $f14, $f30 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f31, $f3, $f14, $f31 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f28, $f4, $f13, $f28 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f29, $f5, $f13, $f29 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f30, $f4, $f15, $f30 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f31, $f5, $f15, $f31 */);
		M2C_ERROR(/* unknown instruction: ps_muls0 $f8, $f24, $f16 */);
		M2C_ERROR(/* unknown instruction: ps_muls0 $f9, $f25, $f16 */);
		M2C_ERROR(/* unknown instruction: ps_muls0 $f10, $f24, $f18 */);
		M2C_ERROR(/* unknown instruction: ps_muls0 $f11, $f25, $f18 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f8, $f26, $f16, $f8 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f9, $f27, $f16, $f9 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f10, $f26, $f18, $f10 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f11, $f27, $f18, $f11 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f8, $f28, $f17, $f8 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f9, $f29, $f17, $f9 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f10, $f28, $f19, $f10 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f11, $f29, $f19, $f11 */);
		M2C_ERROR(/* unknown instruction: ps_muls0 $f12, $f24, $f20 */);
		M2C_ERROR(/* unknown instruction: ps_muls0 $f13, $f25, $f20 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f24, $f22, $f30 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f25, $f22, $f31 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f12, $f26, $f20, $f12 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f13, $f27, $f20, $f13 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f14, $f26, $f22, $f14 */);
		M2C_ERROR(/* unknown instruction: ps_madds1 $f15, $f27, $f22, $f15 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f12, $f28, $f21, $f12 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f13, $f29, $f21, $f13 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f28, $f23, $f14 */);
		M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f29, $f23, $f15 */);
		var_ctr -= 1;
	} while (var_ctr != 0);
	return farg0;
}

f32 fn_8022A650(
    u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 farg0)
{
	f32 var_f1;
	s32 temp_cr0_gt;
	s32 temp_r20;
	s32 temp_r3;
	s32 var_ctr;

	var_f1  = farg0;
	var_ctr = arg4;
	if (arg4 > 0) {
		temp_r20    = M2C_FIELD(arg0, s32*, 0x1C);
		temp_r3     = M2C_FIELD(arg0, s32*, 0x20);
		temp_cr0_gt = temp_r20 > temp_r3;
		do {
			M2C_ERROR(/* unknown instruction: ps_sub $f0, $f0, $f0 */);
			M2C_ERROR(/* unknown instruction: psq_lu $f28, 0x1($r19), 0x1, qr5 */);
			M2C_ERROR(/* unknown instruction: psq_lu $f29, 0x1($r19), 0x1, qr5 */);
			M2C_ERROR(/* unknown instruction: ps_cmpo0 $cr5, $f29, $f0 */);
			if (temp_cr0_gt != 0) {
			}
			M2C_ERROR(/* unknown instruction: psq_lux $f16, $r20, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f17, $r20, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f18, $r20, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f21, $r3, $r9, 0x1, qr7 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f22, $r3, $r9, 0x1, qr7 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f23, $r3, $r9, 0x1, qr7 */);
			var_f1 = farg0;
			M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f0, $f16, $f6 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f1, $f16, $f7 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f24, $f0, $f21 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f25, $f1, $f21 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f2, $f17, $f6 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f3, $f17, $f7 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f2, $f22, $f24 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f3, $f22, $f25 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f4, $f18, $f6 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f5, $f18, $f7 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f4, $f23, $f24 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f5, $f23, $f25 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f19, $f6, $f28 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f20, $f7, $f28 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f26, $f24, $f28 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f27, $f25, $f28 */);
			if (temp_cr0_gt != 0) {
				M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f8, $f16, $f14 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f9, $f16, $f15 */);
				M2C_ERROR(/* unknown instruction: ps_muls0 $f24, $f8, $f21 */);
				M2C_ERROR(/* unknown instruction: ps_muls0 $f25, $f9, $f21 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f10, $f17, $f14 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f11, $f17, $f15 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f10, $f22, $f24 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f11, $f22, $f25 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f12, $f18, $f14 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f13, $f18, $f15 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f12, $f23, $f24 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f13, $f23, $f25 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f19, $f14, $f29, $f19 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f20, $f15, $f29, $f20 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f26, $f24, $f29, $f26 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f27, $f25, $f29, $f27 */);
			}
			M2C_ERROR(/* unknown instruction: ps_merge11 $f14, $f19, $f19 */);
			M2C_ERROR(/* unknown instruction: psq_stux $f19, $r5, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_stux $f14, $r5, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_stux $f20, $r5, $r8, 0x1, qr6 */);
			if (temp_r20 != temp_r3) {
				M2C_ERROR(/* unknown instruction: ps_merge11 $f24, $f26, $f26 */);
				M2C_ERROR(/* unknown instruction: psq_stux $f26, $r6, $r9, 0x1, qr7 */);
				M2C_ERROR(/* unknown instruction: psq_stux $f24, $r6, $r9, 0x1, qr7 */);
				M2C_ERROR(/* unknown instruction: psq_stux $f27, $r6, $r9, 0x1, qr7 */);
			}
			var_ctr -= 1;
		} while (var_ctr != 0);
	}
	return var_f1;
}

f32 fn_8022A87C(
    u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 farg0)
{
	f32 var_f1;
	s32 temp_cr0_gt;
	s32 temp_r20;
	s32 temp_r3;
	s32 var_ctr;

	var_f1  = farg0;
	var_ctr = arg4;
	if (arg4 > 0) {
		temp_r20    = M2C_FIELD(arg0, s32*, 0x1C);
		temp_r3     = M2C_FIELD(arg0, s32*, 0x20);
		temp_cr0_gt = temp_r20 > temp_r3;
		do {
			M2C_ERROR(/* unknown instruction: ps_sub $f0, $f0, $f0 */);
			M2C_ERROR(/* unknown instruction: psq_lu $f28, 0x1($r19), 0x1, qr5 */);
			M2C_ERROR(/* unknown instruction: psq_lu $f29, 0x1($r19), 0x1, qr5 */);
			M2C_ERROR(/* unknown instruction: psq_lu $f30, 0x1($r19), 0x1, qr5 */);
			M2C_ERROR(/* unknown instruction: ps_cmpo0 $cr5, $f29, $f0 */);
			M2C_ERROR(/* unknown instruction: ps_cmpo0 $cr6, $f30, $f0 */);
			if (temp_cr0_gt != 0) {
				if (temp_cr0_gt != 0) {
				}
			}
			M2C_ERROR(/* unknown instruction: psq_lux $f16, $r20, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f17, $r20, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f18, $r20, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f21, $r3, $r9, 0x1, qr7 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f22, $r3, $r9, 0x1, qr7 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f23, $r3, $r9, 0x1, qr7 */);
			var_f1 = farg0;
			M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f0, $f16, $f6 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f1, $f16, $f7 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f24, $f0, $f21 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f25, $f1, $f21 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f2, $f17, $f6 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f3, $f17, $f7 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f2, $f22, $f24 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f3, $f22, $f25 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f4, $f18, $f6 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f5, $f18, $f7 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f4, $f23, $f24 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f5, $f23, $f25 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f19, $f6, $f28 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f20, $f7, $f28 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f26, $f24, $f28 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f27, $f25, $f28 */);
			if (temp_cr0_gt != 0) {
				M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f8, $f16, $f14 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f9, $f16, $f15 */);
				M2C_ERROR(/* unknown instruction: ps_muls0 $f24, $f8, $f21 */);
				var_f1 = farg0;
				M2C_ERROR(/* unknown instruction: ps_muls0 $f25, $f9, $f21 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f10, $f17, $f14 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f11, $f17, $f15 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f10, $f22, $f24 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f11, $f22, $f25 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f12, $f18, $f14 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f13, $f18, $f15 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f12, $f23, $f24 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f13, $f23, $f25 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f19, $f14, $f29, $f19 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f20, $f15, $f29, $f20 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f26, $f24, $f29, $f26 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f27, $f25, $f29, $f27 */);
				if (temp_cr0_gt != 0) {
					M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f0, $f16, $f6 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f1, $f16, $f7 */);
					M2C_ERROR(/* unknown instruction: ps_muls0 $f24, $f0, $f21 */);
					M2C_ERROR(/* unknown instruction: ps_muls0 $f25, $f1, $f21 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f2, $f17, $f6 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f3, $f17, $f7 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f2, $f22, $f24 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f3, $f22, $f25 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f4, $f18, $f6 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f5, $f18, $f7 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f4, $f23, $f24 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f5, $f23, $f25 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f19, $f6, $f30, $f19 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f20, $f7, $f30, $f20 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f26, $f24, $f30, $f26 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f27, $f25, $f30, $f27 */);
				}
			}
			M2C_ERROR(/* unknown instruction: ps_merge11 $f14, $f19, $f19 */);
			M2C_ERROR(/* unknown instruction: psq_stux $f19, $r5, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_stux $f14, $r5, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_stux $f20, $r5, $r8, 0x1, qr6 */);
			if (temp_r20 != temp_r3) {
				M2C_ERROR(/* unknown instruction: ps_merge11 $f24, $f26, $f26 */);
				M2C_ERROR(/* unknown instruction: psq_stux $f26, $r6, $r9, 0x1, qr7 */);
				M2C_ERROR(/* unknown instruction: psq_stux $f24, $r6, $r9, 0x1, qr7 */);
				M2C_ERROR(/* unknown instruction: psq_stux $f27, $r6, $r9, 0x1, qr7 */);
			}
			var_ctr -= 1;
		} while (var_ctr != 0);
	}
	return var_f1;
}

f32 fn_8022AB3C(
    u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 farg0)
{
	f32 var_f1;
	s32 temp_cr0_gt;
	s32 temp_r20;
	s32 temp_r3;
	s32 var_ctr;

	var_f1  = farg0;
	var_ctr = arg4;
	if (arg4 > 0) {
		temp_r20    = M2C_FIELD(arg0, s32*, 0x1C);
		temp_r3     = M2C_FIELD(arg0, s32*, 0x20);
		temp_cr0_gt = temp_r20 > temp_r3;
		do {
			M2C_ERROR(/* unknown instruction: ps_sub $f0, $f0, $f0 */);
			M2C_ERROR(/* unknown instruction: psq_lu $f28, 0x1($r19), 0x1, qr5 */);
			M2C_ERROR(/* unknown instruction: psq_lu $f29, 0x1($r19), 0x1, qr5 */);
			M2C_ERROR(/* unknown instruction: psq_lu $f30, 0x1($r19), 0x1, qr5 */);
			M2C_ERROR(/* unknown instruction: psq_lu $f31, 0x1($r19), 0x1, qr5 */);
			M2C_ERROR(/* unknown instruction: ps_cmpo0 $cr5, $f29, $f0 */);
			M2C_ERROR(/* unknown instruction: ps_cmpo0 $cr6, $f30, $f0 */);
			M2C_ERROR(/* unknown instruction: ps_cmpo0 $cr7, $f31, $f0 */);
			if (temp_cr0_gt != 0) {
				if (temp_cr0_gt != 0) {
					if (temp_cr0_gt != 0) {
					}
				}
			}
			M2C_ERROR(/* unknown instruction: psq_lux $f16, $r20, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f17, $r20, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f18, $r20, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f21, $r3, $r9, 0x1, qr7 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f22, $r3, $r9, 0x1, qr7 */);
			M2C_ERROR(/* unknown instruction: psq_lux $f23, $r3, $r9, 0x1, qr7 */);
			var_f1 = farg0;
			M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f0, $f16, $f6 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f1, $f16, $f7 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f24, $f0, $f21 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f25, $f1, $f21 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f2, $f17, $f6 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f3, $f17, $f7 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f2, $f22, $f24 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f3, $f22, $f25 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f4, $f18, $f6 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f5, $f18, $f7 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f4, $f23, $f24 */);
			M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f5, $f23, $f25 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f19, $f6, $f28 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f20, $f7, $f28 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f26, $f24, $f28 */);
			M2C_ERROR(/* unknown instruction: ps_muls0 $f27, $f25, $f28 */);
			if (temp_cr0_gt != 0) {
				M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f8, $f16, $f14 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f9, $f16, $f15 */);
				M2C_ERROR(/* unknown instruction: ps_muls0 $f24, $f8, $f21 */);
				var_f1 = farg0;
				M2C_ERROR(/* unknown instruction: ps_muls0 $f25, $f9, $f21 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f10, $f17, $f14 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f11, $f17, $f15 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f10, $f22, $f24 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f11, $f22, $f25 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f12, $f18, $f14 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f13, $f18, $f15 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f12, $f23, $f24 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f13, $f23, $f25 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f19, $f14, $f29, $f19 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f20, $f15, $f29, $f20 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f26, $f24, $f29, $f26 */);
				M2C_ERROR(/* unknown instruction: ps_madds0 $f27, $f25, $f29, $f27 */);
				if (temp_cr0_gt != 0) {
					M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f0, $f16, $f6 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f1, $f16, $f7 */);
					M2C_ERROR(/* unknown instruction: ps_muls0 $f24, $f0, $f21 */);
					M2C_ERROR(/* unknown instruction: ps_muls0 $f25, $f1, $f21 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f2, $f17, $f6 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f3, $f17, $f7 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f2, $f22, $f24 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f3, $f22, $f25 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f6, $f4, $f18, $f6 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f7, $f5, $f18, $f7 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f4, $f23, $f24 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f5, $f23, $f25 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f19, $f6, $f30, $f19 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f20, $f7, $f30, $f20 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f26, $f24, $f30, $f26 */);
					M2C_ERROR(/* unknown instruction: ps_madds0 $f27, $f25, $f30, $f27 */);
					if (temp_cr0_gt != 0) {
						M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f8, $f16, $f14 */);
						M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f9, $f16, $f15 */);
						M2C_ERROR(/* unknown instruction: ps_muls0 $f24, $f8, $f21 */);
						M2C_ERROR(/* unknown instruction: ps_muls0 $f25, $f9, $f21 */);
						M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f10, $f17, $f14 */);
						M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f11, $f17, $f15 */);
						M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f10, $f22, $f24 */);
						M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f11, $f22, $f25 */);
						M2C_ERROR(/* unknown instruction: ps_madds0 $f14, $f12, $f18, $f14 */);
						M2C_ERROR(/* unknown instruction: ps_madds0 $f15, $f13, $f18, $f15 */);
						M2C_ERROR(/* unknown instruction: ps_madds0 $f24, $f12, $f23, $f24 */);
						M2C_ERROR(/* unknown instruction: ps_madds0 $f25, $f13, $f23, $f25 */);
						M2C_ERROR(/* unknown instruction: ps_madds0 $f19, $f14, $f31, $f19 */);
						M2C_ERROR(/* unknown instruction: ps_madds0 $f20, $f15, $f31, $f20 */);
						M2C_ERROR(/* unknown instruction: ps_madds0 $f26, $f24, $f31, $f26 */);
						M2C_ERROR(/* unknown instruction: ps_madds0 $f27, $f25, $f31, $f27 */);
					}
				}
			}
			M2C_ERROR(/* unknown instruction: ps_merge11 $f14, $f19, $f19 */);
			M2C_ERROR(/* unknown instruction: psq_stux $f19, $r5, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_stux $f14, $r5, $r8, 0x1, qr6 */);
			M2C_ERROR(/* unknown instruction: psq_stux $f20, $r5, $r8, 0x1, qr6 */);
			if (temp_r20 != temp_r3) {
				M2C_ERROR(/* unknown instruction: ps_merge11 $f24, $f26, $f26 */);
				M2C_ERROR(/* unknown instruction: psq_stux $f26, $r6, $r9, 0x1, qr7 */);
				M2C_ERROR(/* unknown instruction: psq_stux $f24, $r6, $r9, 0x1, qr7 */);
				M2C_ERROR(/* unknown instruction: psq_stux $f27, $r6, $r9, 0x1, qr7 */);
			}
			var_ctr -= 1;
		} while (var_ctr != 0);
	}
	return var_f1;
}

s32 fn_8022AE80(u8* arg0, s32 arg1)
{
	s32 temp_r29;
	s32 temp_r3;

	if (fn_8014535C(arg1) != 0) {
		if ((u32)M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u8**, lbl_8042C930) == 0U) {
			fn_8015C878(lbl_8042C830);
		}
		temp_r3 = fn_8015C39C();
		if (temp_r3 == 1) {
			fn_8015C394(0);
		}
		temp_r29 = fn_80227018(arg0, arg1);
		if (temp_r3 == 1) {
			fn_8015C394(1);
		}
		return temp_r29;
	}
	return fn_80227018(arg0, arg1);
}

u8* fn_8022AF34(u8* arg0, s32 arg1)
{
	u8* temp_r30;
	u8* temp_r31;

	if (fn_80227130() == 0U) {
		return NULL;
	}
	temp_r31 = M2C_FIELD(arg0, u8**, 0x18);
	temp_r30 = M2C_FIELD(temp_r31, u8**, lbl_8042C930);
	if (((u32)M2C_FIELD(fn_80226468(temp_r31), u32*, 0x10) > 1U) && (temp_r30 != NULL)
	    && ((u8)M2C_FIELD(temp_r30, u8*, 0xD) != 0) && (M2C_FIELD(temp_r31, s32*, 8) & 0x10)) {
		fn_80145004(arg1, temp_r30, M2C_FIELD(temp_r31, s32*, 0x14));
	}
	return arg0;
}

u8* fn_8022AFE0(u8* arg0, u8* arg1, M2C_UNK arg_sp0)
{
	s32 temp_cr0_eq;
	s32 temp_r28;
	s32 temp_r6;
	s32 var_r24;
	u16 var_r24_2;
	u32 var_r23;
	u8* temp_r30;
	u8* temp_r3;
	u8* temp_r4;
	u8* temp_r4_2;
	u8* temp_r5;
	u8* temp_r5_2;
	u8* var_r25;
	u8* var_r31;

	temp_r4                        = M2C_FIELD(arg1, u8**, 0);
	temp_r5                        = temp_r4 + 0x18;
	M2C_FIELD(temp_r4, u16*, 0x18) = (u16)lbl_8042BE88;
	temp_r4_2                      = M2C_FIELD(arg0, u8**, 0x18);
	var_r31                        = temp_r5 + ((M2C_FIELD(temp_r4, s32*, 0x20) - 1) * 8) + 0x14;
	temp_r30                       = M2C_FIELD(temp_r4_2, u8**, 0x54);
	temp_r5_2                      = M2C_FIELD(arg0, u8**, 0x18);
	temp_r28                       = fn_8019E8EC(M2C_FIELD(arg0, s32*, 4), temp_r4_2, temp_r5);
	fn_8015C3A4(M2C_FIELD(temp_r5_2, u8**, lbl_8042C930), arg1, temp_r5_2);
	temp_r3 = fn_80226468(M2C_FIELD(arg0, u8**, 0x18));
	if ((u32)M2C_FIELD(temp_r3, u32*, 0x10) > 1U) {
		fn_801AD0AC(temp_r28, ((u32)M2C_FIELD(arg1, u32*, 8) >> 4U) & 1);
	} else {
		GXSetVtxDesc(0, 1);
	}
	if (((u32)M2C_FIELD(temp_r3, u32*, 0x10) == 1U)
	    && ((u32)M2C_FIELD(temp_r3, u32*, 0x34) == 0U)) {
		var_r23 = 0U;
		var_r24 = 0;
	loop_7:
		if (var_r23 < (u32)M2C_FIELD(temp_r3, u32*, 4)) {
			fn_80227300(M2C_FIELD(&lbl_8029BB30, s32*, 0xC)
			        + (*(u32*)(M2C_FIELD(temp_r3, u8**, 8) + var_r23) << 6),
			    var_r24, ((u32)M2C_FIELD(arg1, u32*, 8) >> 4U) & 1,
			    M2C_FIELD(&lbl_8029BB30, s32*, 0xC));
			var_r24 += 3;
			var_r23 += 1;
			goto loop_7;
		}
	}
	fn_80140544();
	var_r24_2 = M2C_FIELD(temp_r30, u16*, 4);
	var_r25   = temp_r30 + 0x10;
loop_13:
	temp_cr0_eq = (s32)var_r24_2 == 0;
	var_r24_2 -= 1;
	if (temp_cr0_eq == 0) {
		if (((u32)M2C_FIELD(temp_r3, u32*, 0x10) == 1U)
		    && ((u32)M2C_FIELD(temp_r3, u32*, 0x34) != 0U)) {
			temp_r6 = var_r24_2 + 1;
			fn_802273D0(temp_r3, M2C_FIELD(M2C_FIELD(arg1, u8**, 4), u16*, 4) - temp_r6,
			    ((u32)M2C_FIELD(arg1, u32*, 8) >> 4U) & 1, temp_r6);
		}
		fn_80141D0C(var_r25, var_r31, arg0, temp_r28, arg1);
		var_r31 += 8;
		var_r25 += 0xC;
		goto loop_13;
	}
	return arg0;
}

u8* fn_8022B174(void)
{
	s32* temp_r3_2;
	s32 temp_r30;
	s32 temp_r30_2;
	u8* temp_r3;

	temp_r3                        = fn_801B3984();
	M2C_FIELD(temp_r3, s32*, 0x2C) = 0x116;
	M2C_FIELD(temp_r3, s32*, 0x30) = 2;
	temp_r30                       = fn_801B4EB4(0x116);
	temp_r3_2                      = fn_8015D4B8();
	fn_801B52BC(temp_r30, 0, temp_r3_2, 0);
	fn_801B43EC();
	temp_r30_2 = fn_801B51B8(temp_r3, *temp_r3_2, 0, 0);
	fn_8015C358(fn_8022AE80);
	fn_8015C370(temp_r30_2, fn_8022AF34);
	fn_8015C388(temp_r30_2, fn_8022AFE0);
	return temp_r3;
}

s32 fn_8022B230(s32 arg0)
{
	if (arg0 & 1) {
		M2C_FIELD(&lbl_8029BB30, s32*, 0x28)
		    = fn_80227E68(1, fn_80227018, fn_80227130, &fn_80227528);
	}
	if (arg0 & 2) {
		M2C_FIELD(&lbl_8029BB30, u8**, 0x2C) = fn_8022B174();
	}
	return 1;
}

s32 fn_8022B2A8(void)
{
	if ((u32)M2C_FIELD(&lbl_8029BB30, u32*, 0x28) != 0U) {
		fn_801B3A10();
		M2C_FIELD(&lbl_8029BB30, u32*, 0x28) = 0U;
	}
	if ((u32)M2C_FIELD(&lbl_8029BB30, u32*, 0x2C) != 0U) {
		fn_801B3A10();
		M2C_FIELD(&lbl_8029BB30, u32*, 0x2C) = 0U;
	}
	return 1;
}

u8* fn_8022B308(u8* arg0, s32 arg1)
{
	s32 var_r4;
	u8* temp_r31;

	temp_r31 = fn_80226468(M2C_FIELD(arg0, u8**, 0x18));
	switch (arg1) { /* irregular */
		case 1:
			var_r4                          = 1;
			M2C_FIELD(temp_r31, s32*, 0x2C) = 1;
			break;
		case 2:
			var_r4                          = 2;
			M2C_FIELD(temp_r31, s32*, 0x2C) = 2;
			break;
		default:
			if ((fn_801521F4(0x120) > 0) && (fn_80149208(arg0) != 0)) {
				var_r4                          = 2;
				M2C_FIELD(temp_r31, s32*, 0x2C) = 2;
			} else {
				var_r4                          = 1;
				M2C_FIELD(temp_r31, s32*, 0x2C) = 1;
			}
			break;
	}
	M2C_FIELD(arg0, s32*, 0x6C) = (s32)M2C_FIELD((&lbl_8029BB30 + (var_r4 * 4)), s32*, 0x24);
	return arg0;
}
