#include "types.h"

typedef s32 M2C_UNK;
typedef struct {
	s32 words[2];
} M2C_BLOCK8;
typedef struct {
	s32 words[4];
} M2C_BLOCK16;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_BITWISE(type, value)      (*(type*)&(value))
#define M2C_ERROR(...)                0

u32 RwEngineRegisterPlugin(M2C_UNK, M2C_UNK, s32 (*)(s32), void (*)()); /* extern */
f64 __fabs(f64);                                                        /* extern */
f64 cos(f32);                                                           /* extern */
u32 fn_8019336C();                                                      /* extern */
u32 fn_80193474();                                                      /* extern */
u32 fn_8019357C();                                                      /* extern */
u32 fn_801936A0();                                                      /* extern */
u32 fn_801937A0();                                                      /* extern */
u32 fn_80193884();                                                      /* extern */
M2C_UNK fn_801990E0();                                                  /* extern */
f32 fn_801991F4();                                                      /* extern */
M2C_UNK fn_8019941C();                                                  /* extern */
M2C_UNK fn_8019947C();                                                  /* extern */
M2C_UNK fn_80199F50();                                                  /* extern */
M2C_UNK fn_80199F78();                                                  /* extern */
M2C_UNK fn_8019E880();                                                  /* extern */
s32 fn_8019E8EC();                                                      /* extern */
M2C_UNK fn_8019ECCC();                                                  /* extern */
s32 fn_8020C088();                                                      /* extern */
u8* fn_8020C1AC();                                                      /* extern */
M2C_UNK fn_8023239C();                                                  /* extern */
M2C_UNK fn_802332AC();                                                  /* extern */
M2C_UNK fn_80234058();                                                  /* extern */
M2C_UNK fn_802344D8();                                                  /* extern */
M2C_UNK fn_80234FD8();                                                  /* extern */
u32 fn_8023501C();                                                      /* extern */
s32 fn_8023506C();                                                      /* extern */
M2C_UNK fn_802355AC();                                                  /* extern */
M2C_UNK fn_802355C0();                                                  /* extern */
u8* fn_80235E64();                                                      /* extern */
u8* fn_80236AE4();                                                      /* extern */
s32 fn_8023943C();                                                      /* extern */
M2C_UNK fn_80239888();                                                  /* extern */
M2C_UNK fn_8023989C();                                                  /* extern */
M2C_UNK memcpy(u8*, u8*, s32);                                          /* extern */
M2C_UNK memset(u8* (**)(u8*, u8*, s32), M2C_UNK, M2C_UNK);              /* extern */
f64 sin();                                                              /* extern */
u8* fn_8022D948();                                                      /* static */
u8* fn_8022DE28();                                                      /* static */
u8* fn_8022E09C();                                                      /* static */
u8* fn_8022E46C();                                                      /* static */
u8* fn_8022E5D4();                                                      /* static */
u8* fn_8022E674();                                                      /* static */
u8* fn_8022E6D4();                                                      /* static */
u8* fn_8022E774();                                                      /* static */
u8* fn_8022E814();                                                      /* static */
u8* fn_8022EB2C();                                                      /* static */
u8* fn_8022FA00();                                                      /* static */
u8* fn_8022FB60();                                                      /* static */
u8* fn_8022FC2C();                                                      /* static */
u8* fn_8022FE30();                                                      /* static */
u8* fn_8022FF58();                                                      /* static */
u8* fn_802301CC();                                                      /* static */
u8* fn_8023031C();                                                      /* static */
u8* fn_80230794();                                                      /* static */
u8* fn_80230834();                                                      /* static */
u8* fn_802308A4();                                                      /* static */
u8* fn_8023096C();                                                      /* static */
u8* fn_802309F8();                                                      /* static */
u8* fn_80230AF0();                                                      /* static */
u8* fn_80230F78();                                                      /* static */
u8* fn_80231004();                                                      /* static */
u8* fn_80231064();                                                      /* static */
u8* fn_8023113C();                                                      /* static */
u8* fn_80231208();                                                      /* static */
u8* fn_802315DC();                                                      /* static */
u8* fn_80231668();                                                      /* static */
u8* fn_802316C8();                                                      /* static */
u8* fn_80231780();                                                      /* static */
u8* fn_8023182C();                                                      /* static */
u8* fn_80231CE8();                                                      /* static */
u8* fn_80231DB8();                                                      /* static */
u8* fn_80231E5C();                                                      /* static */
u8* fn_80231FAC();                                                      /* static */
u8* fn_80232114();                                                      /* static */
extern M2C_UNK fn_80237EBC;
extern M2C_UNK fn_80237F90;
extern M2C_UNK fn_80237FF4;
extern M2C_UNK fn_80238228;
extern M2C_UNK fn_80238328;
extern M2C_UNK fn_802383C0;
extern M2C_UNK fn_80238444;
extern M2C_UNK fn_802388D4;
extern M2C_UNK fn_80238D3C;
extern f32 lbl_80430118;
extern f32 lbl_8043011C;
extern f32 lbl_80430120;
extern f32 lbl_80430124;
extern f32 lbl_80430128;
extern f32 lbl_8043012C;
extern f32 lbl_80430130;
extern f32 lbl_80430134;
extern f32 lbl_80430138;
extern f32 lbl_8043013C;
extern f32 lbl_80430140;
extern f32 lbl_80430144;
extern f32 lbl_80430148;
extern f32 lbl_8043014C;
extern f32 lbl_80430150;
extern f32 lbl_80430154;
extern f32 lbl_80430158;
extern f32 lbl_8043015C;
extern f32 lbl_80430160;
extern f32 lbl_80430164;
extern f32 lbl_80430168;
extern f32 lbl_8043016C;
extern f32 lbl_80430170;
extern f32 lbl_80430174;
extern f32 lbl_80430178;
extern f32 lbl_8043017C;
extern f32 lbl_80430180;
extern f32 lbl_80430184;
extern f32 lbl_80430188;
extern f32 lbl_8043018C;
extern f32 lbl_80430190;
extern f32 lbl_80430194;
extern f32 lbl_804301A0;
extern f32 lbl_804301A4;
extern f32 lbl_804301A8;
extern f32 lbl_804301AC;
extern f64 lbl_804301B0;
extern f32 lbl_804301C0;
extern f32 lbl_804301C4;
extern f32 lbl_804301C8;
extern f32 lbl_804301CC;
extern f32 lbl_804301D8;
extern f32 lbl_804301DC;
extern f32 lbl_804301E0;
extern f32 lbl_804301E4;
extern f32 lbl_804301E8;
extern f32 lbl_80430200;
extern f32 lbl_80430204;
extern f32 lbl_80430208;
extern f32 lbl_8043020C;
extern f32 lbl_80430210;
extern f32 lbl_80430228;
extern f32 lbl_8043022C;
extern f32 lbl_80430230;
extern f32 lbl_80430234;
static u32 lbl_8042ABB0[0x2E];

u16 fn_8022B3E4(f32 farg0)
{
	u32 spC; /* compiler-managed */
	s32 sp8;
	s32 temp_r3;
	s32 temp_r3_2;
	u16 temp_r4_2;
	u16 var_r3;
	u8 temp_r4;

	spC = M2C_BITWISE(u32, farg0);
	if ((s32)(M2C_BITWISE(s32, spC) & 0xFFF) >= 0x800) {
		temp_r4 = (u8)(M2C_BITWISE(u32, spC) >> 0x17U);
		if (((s32)temp_r4 > 0xC)
		    && (((s32)temp_r4 < 0xFE)
		        || ((u32)((M2C_BITWISE(s32, spC) & 0x7FF000) + 0xFF810000) != -0x1000U))) {
			temp_r3 = M2C_BITWISE(s32, spC) & 0x80000000;
			sp8     = temp_r3;
			sp8     = temp_r3 | ((temp_r4 - 0xC) << 0x17);
			M2C_BITWISE(f32, spC) += M2C_BITWISE(f32, sp8);
		}
	}
	temp_r3_2 = M2C_BITWISE(s32, spC) & 0xFFFFF000;
	spC       = temp_r3_2;
	if ((s32)(temp_r3_2 & 0x7F800000) > 0x3F800000) {
		spC = (spC & 0x80000000) | 0x7FFF0000 | 0xF000;
	}
	if ((s32)(spC & 0x7F800000) < 0x38000000) {
		spC &= 0x80000000;
	}
	temp_r4_2 = (spC >> 0x10U) & 0x8000;
	var_r3    = temp_r4_2;
	if (spC & 0x7FFFFFFF) {
		var_r3 = (u16)(temp_r4_2 | (((u8)(spC >> 0x17U) - 0x70) << 0xB)) | ((spC >> 0xCU) & 0x7FF);
	}
	return var_r3;
}

void fn_8022B4F0(u8* arg0, u8* arg1)
{
	f32 temp_f10;
	f32 temp_f11;
	f32 temp_f12;
	f32 temp_f2;
	f32 temp_f3;
	f32 temp_f4;
	f32 temp_f5;
	f32 temp_f6;
	f32 temp_f7;
	f32 temp_f8;
	f32 temp_f8_2;
	f32 temp_f9;
	f32 temp_f9_2;

	temp_f8                     = M2C_FIELD(arg1, f32*, 0xC);
	temp_f11                    = M2C_FIELD(arg1, f32*, 0x10);
	temp_f7                     = temp_f8 * temp_f8;
	temp_f9                     = M2C_FIELD(arg1, f32*, 8);
	temp_f5                     = temp_f11 * temp_f11;
	temp_f12                    = M2C_FIELD(arg1, f32*, 0x14);
	temp_f3                     = temp_f9 * temp_f9;
	temp_f4                     = temp_f9 * temp_f8;
	temp_f6                     = temp_f12 * temp_f11;
	temp_f2                     = temp_f11 * temp_f9;
	temp_f10                    = temp_f12 * temp_f8;
	M2C_FIELD(arg0, f32*, 0)    = (f32) - ((lbl_8043011C * (temp_f7 + temp_f5)) - lbl_80430118);
	temp_f8_2                   = temp_f8 * temp_f11;
	temp_f9_2                   = temp_f12 * temp_f9;
	M2C_FIELD(arg0, f32*, 4)    = (f32)(lbl_8043011C * (temp_f4 + temp_f6));
	M2C_FIELD(arg0, f32*, 8)    = (f32)(lbl_8043011C * (temp_f2 - temp_f10));
	M2C_FIELD(arg0, f32*, 0x10) = (f32)(lbl_8043011C * (temp_f4 - temp_f6));
	M2C_FIELD(arg0, f32*, 0x14) = (f32) - ((lbl_8043011C * (temp_f3 + temp_f5)) - lbl_80430118);
	M2C_FIELD(arg0, f32*, 0x18) = (f32)(lbl_8043011C * (temp_f8_2 + temp_f9_2));
	M2C_FIELD(arg0, f32*, 0x20) = (f32)(lbl_8043011C * (temp_f2 + temp_f10));
	M2C_FIELD(arg0, f32*, 0x24) = (f32)(lbl_8043011C * (temp_f8_2 - temp_f9_2));
	M2C_FIELD(arg0, f32*, 0x28) = (f32) - ((lbl_8043011C * (temp_f3 + temp_f7)) - lbl_80430118);
	M2C_FIELD(arg0, f32*, 0x30) = (f32)lbl_80430120;
	M2C_FIELD(arg0, f32*, 0x34) = (f32)lbl_80430120;
	M2C_FIELD(arg0, f32*, 0x38) = (f32)lbl_80430120;
	M2C_FIELD(arg0, s32*, 0xC)  = 3;
	M2C_FIELD(arg0, f32*, 0x30) = (f32)M2C_FIELD(arg1, f32*, 0x18);
	M2C_FIELD(arg0, f32*, 0x34) = (f32)M2C_FIELD(arg1, f32*, 0x1C);
	M2C_FIELD(arg0, f32*, 0x38) = (f32)M2C_FIELD(arg1, f32*, 0x20);
}

void fn_8022B5FC(u8* arg0, u8* arg1, u8* arg2, u8* arg3, f32 farg0)
{
	s32 sp48;
	s32 sp44;
	s32 sp40;
	s32 sp3C;
	s32 sp38;
	s32 sp34;
	s32 sp30;
	s32 sp2C;
	s32 sp28;
	s32 sp24;
	s32 sp20;
	s32 sp1C;
	s32 sp18;
	s32 sp14;
	f32 sp10;
	f32 spC;
	s32 sp8;
	f32 temp_f0;
	f32 temp_f0_2;
	f32 temp_f13;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f1_4;
	f32 temp_f25;
	f32 temp_f26;
	f32 temp_f27;
	f32 temp_f27_2;
	f32 temp_f2;
	f32 temp_f3;
	f32 temp_f3_2;
	f32 temp_f5;
	f32 temp_f6;
	f32 temp_f6_2;
	f32 temp_f7;
	f32 temp_f8;
	f32 temp_f8_2;
	f32 var_f12;
	f32 var_f25;
	f32 var_f26;
	f32 var_f28;
	f32 var_f29;
	f32 var_f30;
	f32 var_f31;
	f32 var_f4;
	s32 temp_r3;
	s32 temp_r3_10;
	s32 temp_r3_11;
	s32 temp_r3_12;
	s32 temp_r3_13;
	s32 temp_r3_14;
	s32 temp_r3_2;
	s32 temp_r3_3;
	s32 temp_r3_4;
	s32 temp_r3_5;
	s32 temp_r3_6;
	s32 temp_r3_7;
	s32 temp_r3_8;
	s32 temp_r3_9;
	s32 temp_r4;
	s32 temp_r7;
	s32 temp_r7_10;
	s32 temp_r7_11;
	s32 temp_r7_12;
	s32 temp_r7_13;
	s32 temp_r7_14;
	s32 temp_r7_2;
	s32 temp_r7_3;
	s32 temp_r7_4;
	s32 temp_r7_5;
	s32 temp_r7_6;
	s32 temp_r7_7;
	s32 temp_r7_8;
	s32 temp_r7_9;
	u16 temp_r8;
	u16 temp_r8_10;
	u16 temp_r8_11;
	u16 temp_r8_12;
	u16 temp_r8_13;
	u16 temp_r8_14;
	u16 temp_r8_2;
	u16 temp_r8_3;
	u16 temp_r8_4;
	u16 temp_r8_5;
	u16 temp_r8_6;
	u16 temp_r8_7;
	u16 temp_r8_8;
	u16 temp_r8_9;

	temp_r8 = M2C_FIELD(arg1, u16*, 8);
	temp_r7 = (temp_r8 << 0x10) & 0x80000000;
	sp48    = temp_r7;
	if (temp_r8 & 0x7FFF) {
		temp_r3 = temp_r7 | (((temp_r8 << 0xC) & 0x07800000) + 0x38000000);
		sp48    = temp_r3;
		sp48    = temp_r3 | ((temp_r8 << 0xC) & 0x7FF000);
	}
	temp_r8_2 = M2C_FIELD(arg1, u16*, 0xA);
	temp_r7_2 = (temp_r8_2 << 0x10) & 0x80000000;
	sp44      = temp_r7_2;
	if (temp_r8_2 & 0x7FFF) {
		temp_r3_2 = temp_r7_2 | (((temp_r8_2 << 0xC) & 0x07800000) + 0x38000000);
		sp44      = temp_r3_2;
		sp44      = temp_r3_2 | ((temp_r8_2 << 0xC) & 0x7FF000);
	}
	temp_r8_3 = M2C_FIELD(arg1, u16*, 0xC);
	temp_r7_3 = (temp_r8_3 << 0x10) & 0x80000000;
	sp40      = temp_r7_3;
	if (temp_r8_3 & 0x7FFF) {
		temp_r3_3 = temp_r7_3 | (((temp_r8_3 << 0xC) & 0x07800000) + 0x38000000);
		sp40      = temp_r3_3;
		sp40      = temp_r3_3 | ((temp_r8_3 << 0xC) & 0x7FF000);
	}
	temp_r8_4 = M2C_FIELD(arg1, u16*, 0xE);
	temp_r7_4 = (temp_r8_4 << 0x10) & 0x80000000;
	sp3C      = temp_r7_4;
	if (temp_r8_4 & 0x7FFF) {
		temp_r3_4 = temp_r7_4 | (((temp_r8_4 << 0xC) & 0x07800000) + 0x38000000);
		sp3C      = temp_r3_4;
		sp3C      = temp_r3_4 | ((temp_r8_4 << 0xC) & 0x7FF000);
	}
	temp_r8_5 = M2C_FIELD(arg1, u16*, 0x10);
	temp_r7_5 = (temp_r8_5 << 0x10) & 0x80000000;
	sp38      = temp_r7_5;
	if (temp_r8_5 & 0x7FFF) {
		temp_r3_5 = temp_r7_5 | (((temp_r8_5 << 0xC) & 0x07800000) + 0x38000000);
		sp38      = temp_r3_5;
		sp38      = temp_r3_5 | ((temp_r8_5 << 0xC) & 0x7FF000);
	}
	temp_r8_6 = M2C_FIELD(arg1, u16*, 0x12);
	temp_r7_6 = (temp_r8_6 << 0x10) & 0x80000000;
	sp34      = temp_r7_6;
	if (temp_r8_6 & 0x7FFF) {
		temp_r3_6 = temp_r7_6 | (((temp_r8_6 << 0xC) & 0x07800000) + 0x38000000);
		sp34      = temp_r3_6;
		sp34      = temp_r3_6 | ((temp_r8_6 << 0xC) & 0x7FF000);
	}
	temp_r8_7 = M2C_FIELD(arg1, u16*, 0x14);
	temp_r7_7 = (temp_r8_7 << 0x10) & 0x80000000;
	sp30      = temp_r7_7;
	if (temp_r8_7 & 0x7FFF) {
		temp_r3_7 = temp_r7_7 | (((temp_r8_7 << 0xC) & 0x07800000) + 0x38000000);
		sp30      = temp_r3_7;
		sp30      = temp_r3_7 | ((temp_r8_7 << 0xC) & 0x7FF000);
	}
	temp_r8_8 = M2C_FIELD(arg2, u16*, 8);
	temp_r7_8 = (temp_r8_8 << 0x10) & 0x80000000;
	sp2C      = temp_r7_8;
	if (temp_r8_8 & 0x7FFF) {
		temp_r3_8 = temp_r7_8 | (((temp_r8_8 << 0xC) & 0x07800000) + 0x38000000);
		sp2C      = temp_r3_8;
		sp2C      = temp_r3_8 | ((temp_r8_8 << 0xC) & 0x7FF000);
	}
	temp_r8_9 = M2C_FIELD(arg2, u16*, 0xA);
	var_f31   = M2C_BITWISE(f32, sp2C);
	temp_r7_9 = (temp_r8_9 << 0x10) & 0x80000000;
	sp28      = temp_r7_9;
	if (temp_r8_9 & 0x7FFF) {
		temp_r3_9 = temp_r7_9 | (((temp_r8_9 << 0xC) & 0x07800000) + 0x38000000);
		sp28      = temp_r3_9;
		sp28      = temp_r3_9 | ((temp_r8_9 << 0xC) & 0x7FF000);
	}
	temp_r8_10 = M2C_FIELD(arg2, u16*, 0xC);
	var_f30    = M2C_BITWISE(f32, sp28);
	temp_r7_10 = (temp_r8_10 << 0x10) & 0x80000000;
	sp24       = temp_r7_10;
	if (temp_r8_10 & 0x7FFF) {
		temp_r3_10 = temp_r7_10 | (((temp_r8_10 << 0xC) & 0x07800000) + 0x38000000);
		sp24       = temp_r3_10;
		sp24       = temp_r3_10 | ((temp_r8_10 << 0xC) & 0x7FF000);
	}
	temp_r8_11 = M2C_FIELD(arg2, u16*, 0xE);
	var_f29    = M2C_BITWISE(f32, sp24);
	temp_r7_11 = (temp_r8_11 << 0x10) & 0x80000000;
	sp20       = temp_r7_11;
	if (temp_r8_11 & 0x7FFF) {
		temp_r3_11 = temp_r7_11 | (((temp_r8_11 << 0xC) & 0x07800000) + 0x38000000);
		sp20       = temp_r3_11;
		sp20       = temp_r3_11 | ((temp_r8_11 << 0xC) & 0x7FF000);
	}
	temp_r8_12 = M2C_FIELD(arg2, u16*, 0x10);
	var_f28    = M2C_BITWISE(f32, sp20);
	temp_r7_12 = (temp_r8_12 << 0x10) & 0x80000000;
	sp1C       = temp_r7_12;
	if (temp_r8_12 & 0x7FFF) {
		temp_r3_12 = temp_r7_12 | (((temp_r8_12 << 0xC) & 0x07800000) + 0x38000000);
		sp1C       = temp_r3_12;
		sp1C       = temp_r3_12 | ((temp_r8_12 << 0xC) & 0x7FF000);
	}
	temp_r8_13 = M2C_FIELD(arg2, u16*, 0x12);
	temp_r7_13 = (temp_r8_13 << 0x10) & 0x80000000;
	sp18       = temp_r7_13;
	if (temp_r8_13 & 0x7FFF) {
		temp_r3_13 = temp_r7_13 | (((temp_r8_13 << 0xC) & 0x07800000) + 0x38000000);
		sp18       = temp_r3_13;
		sp18       = temp_r3_13 | ((temp_r8_13 << 0xC) & 0x7FF000);
	}
	temp_r8_14 = M2C_FIELD(arg2, u16*, 0x14);
	temp_r7_14 = (temp_r8_14 << 0x10) & 0x80000000;
	sp14       = temp_r7_14;
	if (temp_r8_14 & 0x7FFF) {
		temp_r3_14 = temp_r7_14 | (((temp_r8_14 << 0xC) & 0x07800000) + 0x38000000);
		sp14       = temp_r3_14;
		sp14       = temp_r3_14 | ((temp_r8_14 << 0xC) & 0x7FF000);
	}
	temp_f3                     = M2C_FIELD(arg1, f32*, 4);
	temp_f8                     = M2C_BITWISE(f32, sp38);
	temp_f6                     = M2C_BITWISE(f32, sp34);
	var_f26                     = (farg0 - temp_f3) / (M2C_FIELD(arg2, f32*, 4) - temp_f3);
	temp_f5                     = M2C_BITWISE(f32, sp30);
	temp_f0                     = M2C_BITWISE(f32, sp28);
	temp_f1                     = M2C_BITWISE(f32, sp2C);
	temp_f2                     = M2C_BITWISE(f32, sp24);
	temp_f3_2                   = M2C_BITWISE(f32, sp20);
	M2C_FIELD(arg0, f32*, 0x18) = (f32)((var_f26 * (M2C_BITWISE(f32, sp1C) - temp_f8)) + temp_f8);
	M2C_FIELD(arg0, f32*, 0x1C) = (f32)((var_f26 * (M2C_BITWISE(f32, sp18) - temp_f6)) + temp_f6);
	M2C_FIELD(arg0, f32*, 0x20) = (f32)((var_f26 * (M2C_BITWISE(f32, sp14) - temp_f5)) + temp_f5);
	var_f4                      = (M2C_BITWISE(f32, sp3C) * temp_f3_2)
	    + ((M2C_BITWISE(f32, sp40) * temp_f2)
	        + ((M2C_BITWISE(f32, sp48) * temp_f1) + (M2C_BITWISE(f32, sp44) * temp_f0)));
	M2C_FIELD(arg0, f32*, 0x18) = (f32)(M2C_FIELD(arg0, f32*, 0x18) * M2C_FIELD(arg3, f32*, 0xC));
	M2C_FIELD(arg0, f32*, 0x1C) = (f32)(M2C_FIELD(arg0, f32*, 0x1C) * M2C_FIELD(arg3, f32*, 0x10));
	M2C_FIELD(arg0, f32*, 0x20) = (f32)(M2C_FIELD(arg0, f32*, 0x20) * M2C_FIELD(arg3, f32*, 0x14));
	M2C_FIELD(arg0, f32*, 0x18) = (f32)(M2C_FIELD(arg0, f32*, 0x18) + M2C_FIELD(arg3, f32*, 0));
	M2C_FIELD(arg0, f32*, 0x1C) = (f32)(M2C_FIELD(arg0, f32*, 0x1C) + M2C_FIELD(arg3, f32*, 4));
	M2C_FIELD(arg0, f32*, 0x20) = (f32)(M2C_FIELD(arg0, f32*, 0x20) + M2C_FIELD(arg3, f32*, 8));
	if (var_f4 < lbl_80430120) {
		var_f4  = -var_f4;
		var_f31 = -temp_f1;
		var_f30 = -temp_f0;
		var_f29 = -temp_f2;
		var_f28 = -temp_f3_2;
	}
	var_f25 = lbl_80430118 - var_f26;
	M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
	if (var_f4 != lbl_80430124) {
		sp10    = var_f4;
		temp_r4 = M2C_BITWISE(s32, sp10) & 0x7FFFFFFF;
		if (temp_r4 >= 0x3F800000) {
			if (M2C_BITWISE(s32, sp10) > 0) {
				var_f12 = lbl_80430120;
			} else {
				var_f12 = lbl_80430128;
			}
		} else if (temp_r4 < 0x3F000000) {
			if (temp_r4 <= 0x23000000) {
				var_f12 = lbl_8043012C;
			} else {
				temp_f8_2 = var_f4 * var_f4;
				var_f12   = lbl_80430130
				    - (var_f4
				        - -((var_f4
				                * ((temp_f8_2
				                       * ((temp_f8_2
				                              * ((temp_f8_2
				                                     * ((temp_f8_2
				                                            * ((temp_f8_2
				                                                   * ((lbl_8043014C * temp_f8_2)
				                                                       + lbl_80430148))
				                                                + lbl_80430144))
				                                         + lbl_80430140))
				                                  + lbl_8043013C))
				                           + lbl_80430138))
				                    / ((temp_f8_2
				                           * ((temp_f8_2
				                                  * ((temp_f8_2
				                                         * ((lbl_8043015C * temp_f8_2)
				                                             + lbl_80430158))
				                                      + lbl_80430154))
				                               + lbl_80430150))
				                        + lbl_80430118)))
				            - lbl_80430134));
			}
		} else if (M2C_BITWISE(s32, sp10) < 0) {
			temp_f27  = lbl_80430160 * (lbl_80430118 + var_f4);
			temp_f1_2 = fn_801991F4(temp_f27);
			var_f12   = -(
			    (lbl_8043011C
			        * (temp_f1_2
			            + ((((temp_f27
			                     * ((temp_f27
			                            * ((temp_f27
			                                   * ((temp_f27
			                                          * ((temp_f27
			                                                 * ((lbl_8043014C * temp_f27)
			                                                     + lbl_80430148))
			                                              + lbl_80430144))
			                                       + lbl_80430140))
			                                + lbl_8043013C))
			                         + lbl_80430138))
			                    / ((temp_f27
			                           * ((temp_f27
			                                  * ((temp_f27
			                                         * ((lbl_8043015C * temp_f27) + lbl_80430158))
			                                      + lbl_80430154))
			                               + lbl_80430150))
			                        + lbl_80430118))
			                   * temp_f1_2)
			                - lbl_80430134)))
			    - lbl_80430164);
		} else {
			temp_f27_2 = lbl_80430160 * (lbl_80430118 - var_f4);
			temp_f1_3  = fn_801991F4(temp_f27_2);
			spC        = temp_f1_3;
			sp8        = M2C_BITWISE(s32, spC) & 0xFFFFF000;
			temp_f6_2  = M2C_BITWISE(f32, sp8);
			var_f12    = lbl_8043011C
			    * (temp_f6_2
			        + ((((temp_f27_2
			                 * ((temp_f27_2
			                        * ((temp_f27_2
			                               * ((temp_f27_2
			                                      * ((temp_f27_2
			                                             * ((lbl_8043014C * temp_f27_2)
			                                                 + lbl_80430148))
			                                          + lbl_80430144))
			                                   + lbl_80430140))
			                            + lbl_8043013C))
			                     + lbl_80430138))
			                / ((temp_f27_2
			                       * ((temp_f27_2
			                              * ((temp_f27_2
			                                     * ((lbl_8043015C * temp_f27_2) + lbl_80430158))
			                                  + lbl_80430154))
			                           + lbl_80430150))
			                    + lbl_80430118))
			               * temp_f1_3)
			            + (-((temp_f6_2 * temp_f6_2) - temp_f27_2) / (temp_f1_3 + temp_f6_2))));
		}
		temp_f13  = var_f12 * var_f12;
		temp_f25  = var_f25 * var_f12;
		temp_f26  = var_f26 * var_f12;
		temp_f0_2 = temp_f25 * temp_f25;
		temp_f1_4 = temp_f26 * temp_f26;
		temp_f7   = lbl_80430118
		    / ((temp_f13 * var_f12
		           * ((temp_f13
		                  * ((temp_f13
		                         * ((temp_f13
		                                * ((temp_f13 * ((lbl_8043017C * temp_f13) + lbl_80430178))
		                                    + lbl_80430174))
		                             + lbl_80430170))
		                      + lbl_8043016C))
		               + lbl_80430168))
		        + var_f12);
		var_f25
		    = ((temp_f0_2 * temp_f25
		           * ((temp_f0_2
		                  * ((temp_f0_2
		                         * ((temp_f0_2
		                                * ((temp_f0_2 * ((lbl_8043017C * temp_f0_2) + lbl_80430178))
		                                    + lbl_80430174))
		                             + lbl_80430170))
		                      + lbl_8043016C))
		               + lbl_80430168))
		          + temp_f25)
		    * temp_f7;
		var_f26
		    = ((temp_f1_4 * temp_f26
		           * ((temp_f1_4
		                  * ((temp_f1_4
		                         * ((temp_f1_4
		                                * ((temp_f1_4 * ((lbl_8043017C * temp_f1_4) + lbl_80430178))
		                                    + lbl_80430174))
		                             + lbl_80430170))
		                      + lbl_8043016C))
		               + lbl_80430168))
		          + temp_f26)
		    * temp_f7;
	}
	M2C_FIELD(arg0, f32*, 8)    = (f32)((var_f25 * M2C_BITWISE(f32, sp48)) + (var_f26 * var_f31));
	M2C_FIELD(arg0, f32*, 0xC)  = (f32)((var_f25 * M2C_BITWISE(f32, sp44)) + (var_f26 * var_f30));
	M2C_FIELD(arg0, f32*, 0x10) = (f32)((var_f25 * M2C_BITWISE(f32, sp40)) + (var_f26 * var_f29));
	M2C_FIELD(arg0, f32*, 0x14) = (f32)((var_f25 * M2C_BITWISE(f32, sp3C)) + (var_f26 * var_f28));
}

void fn_8022BD18(u8* arg0, u8* arg1, u8* arg2, f32 farg0)
{
	f32 sp10;
	f32 spC;
	s32 sp8;
	f32 temp_f11;
	f32 temp_f12;
	f32 temp_f13;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f29;
	f32 temp_f2;
	f32 temp_f2_2;
	f32 temp_f30;
	f32 temp_f31;
	f32 temp_f31_2;
	f32 temp_f5;
	f32 temp_f6;
	f32 temp_f8;
	f32 temp_f9;
	f32 var_f0;
	f32 var_f10;
	f32 var_f29;
	f32 var_f30;
	s32 temp_r4;

	temp_f2 = M2C_FIELD(arg1, f32*, 0x18);
	var_f29 = farg0;
	M2C_FIELD(arg0, f32*, 0x18)
	    = (f32)((var_f29 * (M2C_FIELD(arg2, f32*, 0x18) - temp_f2)) + temp_f2);
	temp_f9 = M2C_FIELD(arg1, f32*, 0x1C);
	var_f0  = (M2C_FIELD(arg1, f32*, 0x14) * M2C_FIELD(arg2, f32*, 0x14))
	    + ((M2C_FIELD(arg1, f32*, 0x10) * M2C_FIELD(arg2, f32*, 0x10))
	        + ((M2C_FIELD(arg1, f32*, 8) * M2C_FIELD(arg2, f32*, 8))
	            + (M2C_FIELD(arg1, f32*, 0xC) * M2C_FIELD(arg2, f32*, 0xC))));
	M2C_FIELD(arg0, f32*, 0x1C)
	    = (f32)((var_f29 * (M2C_FIELD(arg2, f32*, 0x1C) - temp_f9)) + temp_f9);
	temp_f2_2 = M2C_FIELD(arg1, f32*, 0x20);
	M2C_FIELD(arg0, f32*, 0x20)
	    = (f32)((var_f29 * (M2C_FIELD(arg2, f32*, 0x20) - temp_f2_2)) + temp_f2_2);
	if (var_f0 < lbl_80430120) {
		var_f0                      = -var_f0;
		M2C_FIELD(arg2, f32*, 8)    = (f32)-M2C_FIELD(arg2, f32*, 8);
		M2C_FIELD(arg2, f32*, 0xC)  = (f32)-M2C_FIELD(arg2, f32*, 0xC);
		M2C_FIELD(arg2, f32*, 0x10) = (f32)-M2C_FIELD(arg2, f32*, 0x10);
		M2C_FIELD(arg2, f32*, 0x14) = (f32)-M2C_FIELD(arg2, f32*, 0x14);
	}
	var_f30 = lbl_80430118 - var_f29;
	M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
	if (var_f0 != lbl_80430124) {
		sp10    = var_f0;
		temp_r4 = M2C_BITWISE(s32, sp10) & 0x7FFFFFFF;
		if (temp_r4 >= 0x3F800000) {
			if (M2C_BITWISE(s32, sp10) > 0) {
				var_f10 = lbl_80430120;
			} else {
				var_f10 = lbl_80430128;
			}
		} else if (temp_r4 < 0x3F000000) {
			if (temp_r4 <= 0x23000000) {
				var_f10 = lbl_8043012C;
			} else {
				temp_f8 = var_f0 * var_f0;
				var_f10 = lbl_80430130
				    - (var_f0
				        - -((var_f0
				                * ((temp_f8
				                       * ((temp_f8
				                              * ((temp_f8
				                                     * ((temp_f8
				                                            * ((temp_f8
				                                                   * ((lbl_8043014C * temp_f8)
				                                                       + lbl_80430148))
				                                                + lbl_80430144))
				                                         + lbl_80430140))
				                                  + lbl_8043013C))
				                           + lbl_80430138))
				                    / ((temp_f8
				                           * ((temp_f8
				                                  * ((temp_f8
				                                         * ((lbl_8043015C * temp_f8)
				                                             + lbl_80430158))
				                                      + lbl_80430154))
				                               + lbl_80430150))
				                        + lbl_80430118)))
				            - lbl_80430134));
			}
		} else if (M2C_BITWISE(s32, sp10) < 0) {
			temp_f31 = lbl_80430160 * (lbl_80430118 + var_f0);
			temp_f1  = fn_801991F4(temp_f31);
			var_f10  = -(
			    (lbl_8043011C
			        * (temp_f1
			            + ((((temp_f31
			                     * ((temp_f31
			                            * ((temp_f31
			                                   * ((temp_f31
			                                          * ((temp_f31
			                                                 * ((lbl_8043014C * temp_f31)
			                                                     + lbl_80430148))
			                                              + lbl_80430144))
			                                       + lbl_80430140))
			                                + lbl_8043013C))
			                         + lbl_80430138))
			                    / ((temp_f31
			                           * ((temp_f31
			                                  * ((temp_f31
			                                         * ((lbl_8043015C * temp_f31) + lbl_80430158))
			                                      + lbl_80430154))
			                               + lbl_80430150))
			                        + lbl_80430118))
			                   * temp_f1)
			                - lbl_80430134)))
			    - lbl_80430164);
		} else {
			temp_f31_2 = lbl_80430160 * (lbl_80430118 - var_f0);
			temp_f1_2  = fn_801991F4(temp_f31_2);
			spC        = temp_f1_2;
			sp8        = M2C_BITWISE(s32, spC) & 0xFFFFF000;
			temp_f6    = M2C_BITWISE(f32, sp8);
			var_f10    = lbl_8043011C
			    * (temp_f6
			        + ((((temp_f31_2
			                 * ((temp_f31_2
			                        * ((temp_f31_2
			                               * ((temp_f31_2
			                                      * ((temp_f31_2
			                                             * ((lbl_8043014C * temp_f31_2)
			                                                 + lbl_80430148))
			                                          + lbl_80430144))
			                                   + lbl_80430140))
			                            + lbl_8043013C))
			                     + lbl_80430138))
			                / ((temp_f31_2
			                       * ((temp_f31_2
			                              * ((temp_f31_2
			                                     * ((lbl_8043015C * temp_f31_2) + lbl_80430158))
			                                  + lbl_80430154))
			                           + lbl_80430150))
			                    + lbl_80430118))
			               * temp_f1_2)
			            + (-((temp_f6 * temp_f6) - temp_f31_2) / (temp_f1_2 + temp_f6))));
		}
		temp_f11 = var_f10 * var_f10;
		temp_f30 = var_f30 * var_f10;
		temp_f29 = var_f29 * var_f10;
		temp_f12 = temp_f30 * temp_f30;
		temp_f13 = temp_f29 * temp_f29;
		temp_f5  = lbl_80430118
		    / ((temp_f11 * var_f10
		           * ((temp_f11
		                  * ((temp_f11
		                         * ((temp_f11
		                                * ((temp_f11 * ((lbl_8043017C * temp_f11) + lbl_80430178))
		                                    + lbl_80430174))
		                             + lbl_80430170))
		                      + lbl_8043016C))
		               + lbl_80430168))
		        + var_f10);
		var_f30
		    = ((temp_f12 * temp_f30
		           * ((temp_f12
		                  * ((temp_f12
		                         * ((temp_f12
		                                * ((temp_f12 * ((lbl_8043017C * temp_f12) + lbl_80430178))
		                                    + lbl_80430174))
		                             + lbl_80430170))
		                      + lbl_8043016C))
		               + lbl_80430168))
		          + temp_f30)
		    * temp_f5;
		var_f29
		    = ((temp_f13 * temp_f29
		           * ((temp_f13
		                  * ((temp_f13
		                         * ((temp_f13
		                                * ((temp_f13 * ((lbl_8043017C * temp_f13) + lbl_80430178))
		                                    + lbl_80430174))
		                             + lbl_80430170))
		                      + lbl_8043016C))
		               + lbl_80430168))
		          + temp_f29)
		    * temp_f5;
	}
	M2C_FIELD(arg0, f32*, 8)
	    = (f32)((var_f30 * M2C_FIELD(arg1, f32*, 8)) + (var_f29 * M2C_FIELD(arg2, f32*, 8)));
	M2C_FIELD(arg0, f32*, 0xC)
	    = (f32)((var_f30 * M2C_FIELD(arg1, f32*, 0xC)) + (var_f29 * M2C_FIELD(arg2, f32*, 0xC)));
	M2C_FIELD(arg0, f32*, 0x10)
	    = (f32)((var_f30 * M2C_FIELD(arg1, f32*, 0x10)) + (var_f29 * M2C_FIELD(arg2, f32*, 0x10)));
	M2C_FIELD(arg0, f32*, 0x14)
	    = (f32)((var_f30 * M2C_FIELD(arg1, f32*, 0x14)) + (var_f29 * M2C_FIELD(arg2, f32*, 0x14)));
}

u8* fn_8022C11C(s32 arg0, u8* arg1, M2C_UNK arg_sp0)
{
	u32 sp8;
	s32* temp_r28;
	s32* var_r30;
	s32 var_r29;
	u8* temp_r27;

	temp_r28 = M2C_FIELD(arg1, s32**, 0x10);
	temp_r27 = M2C_FIELD(arg1, u8**, 0x14);
	var_r30  = temp_r28;
	var_r29  = 0;
loop_8:
	if (var_r29 >= (s32)M2C_FIELD(arg1, s32*, 4)) {
		if (fn_801937A0(arg0, temp_r27, 0x18) != 0U) {
			return arg1;
		}
		return NULL;
	}
	if (fn_801937A0(arg0, var_r30 + 4, 4) == 0U) {
		return NULL;
	}
	if (fn_801936A0(arg0, var_r30 + 8, 0xE) == 0U) {
		return NULL;
	}
	if (fn_80193884(arg0, &sp8, 4) == 0U) {
		return NULL;
	}
	var_r29 += 1;
	*var_r30 = (s32)(temp_r28 + ((sp8 / 24) * 0x18));
	var_r30 += 0x18;
	goto loop_8;
}

s32 fn_8022C21C(u8* arg0, s32 arg1, M2C_UNK arg_sp0)
{
	u32 sp8;
	s32* temp_r29;
	s32* var_r31;
	s32 var_r30;
	u8* temp_r28;

	temp_r29 = M2C_FIELD(arg0, s32**, 0x10);
	var_r30  = 0;
	temp_r28 = M2C_FIELD(arg0, u8**, 0x14);
	var_r31  = temp_r29;
loop_8:
	if (var_r30 >= (s32)M2C_FIELD(arg0, s32*, 4)) {
		return fn_8019336C(arg1, temp_r28, 0x18) != 0U;
	}
	if (fn_8019336C(arg1, var_r31 + 4, 4) == 0U) {
		return 0;
	}
	if (fn_8019357C(arg1, var_r31 + 8, 0xE) == 0U) {
		return 0;
	}
	sp8 = *var_r31 - (s32)temp_r29;
	if (fn_80193474(arg1, &sp8, 4) == 0U) {
		return 0;
	}
	var_r31 += 0x18;
	var_r30 += 1;
	goto loop_8;
}

s32 fn_8022C300(u8* arg0)
{
	return (0x16 * M2C_FIELD(arg0, s32*, 4)) + 0x18;
}

void fn_8022C314(u8* arg0, u8* arg1, f32 farg6, f32 farg7, f32 farg8, f32 farg9)
{
	s32 sp74;
	s32 sp70;
	s32 sp6C;
	s32 sp68;
	s32 sp64;
	s32 sp60;
	s32 sp5C;
	s32 sp58;
	s32 sp54;
	s32 sp50;
	s32 sp4C;
	s32 sp48;
	s32 sp44;
	s32 sp40;
	s32 sp3C;
	u32 sp38; /* compiler-managed */
	s32 sp34;
	u32 sp30; /* compiler-managed */
	s32 sp2C;
	u32 sp28; /* compiler-managed */
	s32 sp24;
	u32 sp20; /* compiler-managed */
	s32 sp1C;
	u32 sp18; /* compiler-managed */
	s32 sp14;
	u32 sp10; /* compiler-managed */
	s32 spC;
	u32 sp8; /* compiler-managed */
	f32 temp_f0;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f2;
	f32 temp_f3;
	f32 temp_f3_2;
	f32 temp_f4;
	f32 temp_f4_2;
	f32 temp_f5;
	f32 temp_f5_2;
	f32 temp_f6;
	f32 var_f10;
	f32 var_f7;
	f32 var_f8;
	f32 var_f9;
	s32 temp_r4;
	s32 temp_r4_10;
	s32 temp_r4_2;
	s32 temp_r4_3;
	s32 temp_r4_4;
	s32 temp_r4_5;
	s32 temp_r4_6;
	s32 temp_r4_7;
	s32 temp_r4_8;
	s32 temp_r4_9;
	s32 temp_r5;
	s32 temp_r5_10;
	s32 temp_r5_11;
	s32 temp_r5_12;
	s32 temp_r5_13;
	s32 temp_r5_14;
	s32 temp_r5_15;
	s32 temp_r5_16;
	s32 temp_r5_17;
	s32 temp_r5_18;
	s32 temp_r5_19;
	s32 temp_r5_20;
	s32 temp_r5_21;
	s32 temp_r5_22;
	s32 temp_r5_2;
	s32 temp_r5_3;
	s32 temp_r5_4;
	s32 temp_r5_5;
	s32 temp_r5_6;
	s32 temp_r5_7;
	s32 temp_r5_8;
	s32 temp_r5_9;
	s32 temp_r6;
	s32 temp_r6_13;
	s32 temp_r6_14;
	s32 temp_r6_2;
	s32 temp_r6_3;
	s32 temp_r6_4;
	s32 temp_r6_5;
	s32 temp_r6_6;
	s32 temp_r6_7;
	s32 temp_r6_8;
	u16 temp_r6_15;
	u16 temp_r6_16;
	u16 temp_r6_17;
	u16 temp_r6_18;
	u16 temp_r7;
	u16 temp_r7_10;
	u16 temp_r7_2;
	u16 temp_r7_3;
	u16 temp_r7_4;
	u16 temp_r7_5;
	u16 temp_r7_6;
	u16 temp_r7_7;
	u16 temp_r7_8;
	u16 temp_r7_9;
	u16 var_r5;
	u16 var_r5_2;
	u16 var_r5_3;
	u16 var_r6;
	u16 var_r6_2;
	u16 var_r6_3;
	u16 var_r6_4;
	u8 temp_r5_23;
	u8 temp_r5_24;
	u8 temp_r5_25;
	u8 temp_r6_10;
	u8 temp_r6_11;
	u8 temp_r6_12;
	u8 temp_r6_9;

	var_f7  = farg6;
	var_f8  = farg7;
	var_f9  = farg8;
	var_f10 = farg9;
	temp_r7 = M2C_FIELD(arg1, u16*, 8);
	temp_r6 = (temp_r7 << 0x10) & 0x80000000;
	sp74    = temp_r6;
	if (temp_r7 & 0x7FFF) {
		temp_r5 = temp_r6 | (((temp_r7 << 0xC) & 0x07800000) + 0x38000000);
		sp74    = temp_r5;
		sp74    = temp_r5 | ((temp_r7 << 0xC) & 0x7FF000);
	}
	temp_r7_2 = M2C_FIELD(arg1, u16*, 0xA);
	temp_r6_2 = (temp_r7_2 << 0x10) & 0x80000000;
	sp70      = temp_r6_2;
	if (temp_r7_2 & 0x7FFF) {
		temp_r5_2 = temp_r6_2 | (((temp_r7_2 << 0xC) & 0x07800000) + 0x38000000);
		sp70      = temp_r5_2;
		sp70      = temp_r5_2 | ((temp_r7_2 << 0xC) & 0x7FF000);
	}
	temp_r7_3 = M2C_FIELD(arg1, u16*, 0xC);
	temp_r6_3 = (temp_r7_3 << 0x10) & 0x80000000;
	sp6C      = temp_r6_3;
	if (temp_r7_3 & 0x7FFF) {
		temp_r5_3 = temp_r6_3 | (((temp_r7_3 << 0xC) & 0x07800000) + 0x38000000);
		sp6C      = temp_r5_3;
		sp6C      = temp_r5_3 | ((temp_r7_3 << 0xC) & 0x7FF000);
	}
	temp_r7_4 = M2C_FIELD(arg1, u16*, 0xE);
	temp_r6_4 = (temp_r7_4 << 0x10) & 0x80000000;
	sp68      = temp_r6_4;
	if (temp_r7_4 & 0x7FFF) {
		temp_r5_4 = temp_r6_4 | (((temp_r7_4 << 0xC) & 0x07800000) + 0x38000000);
		sp68      = temp_r5_4;
		sp68      = temp_r5_4 | ((temp_r7_4 << 0xC) & 0x7FF000);
	}
	temp_f2 = M2C_BITWISE(f32, sp70);
	temp_f3 = M2C_BITWISE(f32, sp74);
	temp_f4 = M2C_BITWISE(f32, sp6C);
	temp_f5 = M2C_BITWISE(f32, sp68);
	temp_f1
	    = (temp_f5 * temp_f5) + ((temp_f4 * temp_f4) + ((temp_f3 * temp_f3) + (temp_f2 * temp_f2)));
	if (temp_f1 > lbl_80430120) {
		temp_f1_2 = lbl_80430118 / temp_f1;
		temp_f0   = -temp_f1_2;
		var_f7    = temp_f5 * temp_f1_2;
		var_f8    = temp_f3 * temp_f0;
		var_f9    = temp_f2 * temp_f0;
		var_f10   = temp_f4 * temp_f0;
	}
	temp_r7_5 = M2C_FIELD(arg0, u16*, 8);
	temp_r6_5 = (temp_r7_5 << 0x10) & 0x80000000;
	sp64      = temp_r6_5;
	if (temp_r7_5 & 0x7FFF) {
		temp_r5_5 = temp_r6_5 | (((temp_r7_5 << 0xC) & 0x07800000) + 0x38000000);
		sp64      = temp_r5_5;
		sp64      = temp_r5_5 | ((temp_r7_5 << 0xC) & 0x7FF000);
	}
	temp_r7_6 = M2C_FIELD(arg0, u16*, 0xA);
	temp_r6_6 = (temp_r7_6 << 0x10) & 0x80000000;
	sp60      = temp_r6_6;
	if (temp_r7_6 & 0x7FFF) {
		temp_r5_6 = temp_r6_6 | (((temp_r7_6 << 0xC) & 0x07800000) + 0x38000000);
		sp60      = temp_r5_6;
		sp60      = temp_r5_6 | ((temp_r7_6 << 0xC) & 0x7FF000);
	}
	temp_r7_7 = M2C_FIELD(arg0, u16*, 0xC);
	temp_r6_7 = (temp_r7_7 << 0x10) & 0x80000000;
	sp5C      = temp_r6_7;
	if (temp_r7_7 & 0x7FFF) {
		temp_r5_7 = temp_r6_7 | (((temp_r7_7 << 0xC) & 0x07800000) + 0x38000000);
		sp5C      = temp_r5_7;
		sp5C      = temp_r5_7 | ((temp_r7_7 << 0xC) & 0x7FF000);
	}
	temp_r7_8 = M2C_FIELD(arg0, u16*, 0xE);
	temp_r6_8 = (temp_r7_8 << 0x10) & 0x80000000;
	sp58      = temp_r6_8;
	if (temp_r7_8 & 0x7FFF) {
		temp_r5_8 = temp_r6_8 | (((temp_r7_8 << 0xC) & 0x07800000) + 0x38000000);
		sp58      = temp_r5_8;
		sp58      = temp_r5_8 | ((temp_r7_8 << 0xC) & 0x7FF000);
	}
	temp_f3_2              = M2C_BITWISE(f32, sp60);
	temp_f5_2              = M2C_BITWISE(f32, sp5C);
	temp_f4_2              = M2C_BITWISE(f32, sp64);
	temp_f6                = M2C_BITWISE(f32, sp58);
	M2C_BITWISE(f32, sp38) = (var_f8 * temp_f6)
	    + ((temp_f4_2 * var_f7) + ((var_f9 * temp_f5_2) - (var_f10 * temp_f3_2)));
	if ((s32)(M2C_BITWISE(s32, sp38) & 0xFFF) >= 0x800) {
		temp_r6_9 = (u8)(M2C_BITWISE(u32, sp38) >> 0x17U);
		if (((s32)temp_r6_9 > 0xC)
		    && (((s32)temp_r6_9 < 0xFE)
		        || ((u32)((M2C_BITWISE(s32, sp38) & 0x7FF000) + 0xFF810000) != -0x1000U))) {
			temp_r5_9 = M2C_BITWISE(s32, sp38) & 0x80000000;
			sp3C      = temp_r5_9;
			sp3C      = temp_r5_9 | ((temp_r6_9 - 0xC) << 0x17);
			sp38 += M2C_BITWISE(f32, sp3C);
		}
	}
	temp_r5_10 = M2C_BITWISE(s32, sp38) & 0xFFFFF000;
	sp38       = temp_r5_10;
	if ((s32)(temp_r5_10 & 0x7F800000) > 0x3F800000) {
		sp38 = (sp38 & 0x80000000) | 0x7FFF0000 | 0xF000;
	}
	if ((s32)(sp38 & 0x7F800000) < 0x38000000) {
		sp38 &= 0x80000000;
	}
	var_r6 = (sp38 >> 0x10U) & 0x8000;
	if (sp38 & 0x7FFFFFFF) {
		var_r6 = (u16)(var_r6 | (((u8)(sp38 >> 0x17U) - 0x70) << 0xB)) | ((sp38 >> 0xCU) & 0x7FF);
	}
	M2C_BITWISE(f32, sp30) = (var_f9 * temp_f6)
	    + ((temp_f3_2 * var_f7) + ((var_f10 * temp_f4_2) - (var_f8 * temp_f5_2)));
	M2C_FIELD(arg0, u16*, 8) = var_r6;
	if ((s32)(M2C_BITWISE(s32, sp30) & 0xFFF) >= 0x800) {
		temp_r6_10 = (u8)(M2C_BITWISE(u32, sp30) >> 0x17U);
		if (((s32)temp_r6_10 > 0xC)
		    && (((s32)temp_r6_10 < 0xFE)
		        || ((u32)((M2C_BITWISE(s32, sp30) & 0x7FF000) + 0xFF810000) != -0x1000U))) {
			temp_r5_11 = M2C_BITWISE(s32, sp30) & 0x80000000;
			sp34       = temp_r5_11;
			sp34       = temp_r5_11 | ((temp_r6_10 - 0xC) << 0x17);
			sp30 += M2C_BITWISE(f32, sp34);
		}
	}
	temp_r5_12 = M2C_BITWISE(s32, sp30) & 0xFFFFF000;
	sp30       = temp_r5_12;
	if ((s32)(temp_r5_12 & 0x7F800000) > 0x3F800000) {
		sp30 = (sp30 & 0x80000000) | 0x7FFF0000 | 0xF000;
	}
	if ((s32)(sp30 & 0x7F800000) < 0x38000000) {
		sp30 &= 0x80000000;
	}
	var_r6_2 = (sp30 >> 0x10U) & 0x8000;
	if (sp30 & 0x7FFFFFFF) {
		var_r6_2
		    = (u16)(var_r6_2 | (((u8)(sp30 >> 0x17U) - 0x70) << 0xB)) | ((sp30 >> 0xCU) & 0x7FF);
	}
	M2C_BITWISE(f32, sp28) = (var_f10 * temp_f6)
	    + ((temp_f5_2 * var_f7) + ((var_f8 * temp_f3_2) - (var_f9 * temp_f4_2)));
	M2C_FIELD(arg0, u16*, 0xA) = var_r6_2;
	if ((s32)(M2C_BITWISE(s32, sp28) & 0xFFF) >= 0x800) {
		temp_r6_11 = (u8)(M2C_BITWISE(u32, sp28) >> 0x17U);
		if (((s32)temp_r6_11 > 0xC)
		    && (((s32)temp_r6_11 < 0xFE)
		        || ((u32)((M2C_BITWISE(s32, sp28) & 0x7FF000) + 0xFF810000) != -0x1000U))) {
			temp_r5_13 = M2C_BITWISE(s32, sp28) & 0x80000000;
			sp2C       = temp_r5_13;
			sp2C       = temp_r5_13 | ((temp_r6_11 - 0xC) << 0x17);
			sp28 += M2C_BITWISE(f32, sp2C);
		}
	}
	temp_r5_14 = M2C_BITWISE(s32, sp28) & 0xFFFFF000;
	sp28       = temp_r5_14;
	if ((s32)(temp_r5_14 & 0x7F800000) > 0x3F800000) {
		sp28 = (sp28 & 0x80000000) | 0x7FFF0000 | 0xF000;
	}
	if ((s32)(sp28 & 0x7F800000) < 0x38000000) {
		sp28 &= 0x80000000;
	}
	var_r6_3 = (sp28 >> 0x10U) & 0x8000;
	if (sp28 & 0x7FFFFFFF) {
		var_r6_3
		    = (u16)(var_r6_3 | (((u8)(sp28 >> 0x17U) - 0x70) << 0xB)) | ((sp28 >> 0xCU) & 0x7FF);
	}
	M2C_BITWISE(f32, sp20) = (var_f7 * temp_f6)
	    - ((var_f10 * temp_f5_2) + ((var_f8 * temp_f4_2) + (var_f9 * temp_f3_2)));
	M2C_FIELD(arg0, u16*, 0xC) = var_r6_3;
	if ((s32)(M2C_BITWISE(s32, sp20) & 0xFFF) >= 0x800) {
		temp_r6_12 = (u8)(M2C_BITWISE(u32, sp20) >> 0x17U);
		if (((s32)temp_r6_12 > 0xC)
		    && (((s32)temp_r6_12 < 0xFE)
		        || ((u32)((M2C_BITWISE(s32, sp20) & 0x7FF000) + 0xFF810000) != -0x1000U))) {
			temp_r5_15 = M2C_BITWISE(s32, sp20) & 0x80000000;
			sp24       = temp_r5_15;
			sp24       = temp_r5_15 | ((temp_r6_12 - 0xC) << 0x17);
			sp20 += M2C_BITWISE(f32, sp24);
		}
	}
	temp_r5_16 = M2C_BITWISE(s32, sp20) & 0xFFFFF000;
	sp20       = temp_r5_16;
	if ((s32)(temp_r5_16 & 0x7F800000) > 0x3F800000) {
		sp20 = (sp20 & 0x80000000) | 0x7FFF0000 | 0xF000;
	}
	if ((s32)(sp20 & 0x7F800000) < 0x38000000) {
		sp20 &= 0x80000000;
	}
	var_r6_4 = (sp20 >> 0x10U) & 0x8000;
	if (sp20 & 0x7FFFFFFF) {
		var_r6_4
		    = (u16)(var_r6_4 | (((u8)(sp20 >> 0x17U) - 0x70) << 0xB)) | ((sp20 >> 0xCU) & 0x7FF);
	}
	M2C_FIELD(arg0, u16*, 0xE) = var_r6_4;
	temp_r7_9                  = M2C_FIELD(arg1, u16*, 0x10);
	temp_r6_13                 = (temp_r7_9 << 0x10) & 0x80000000;
	sp54                       = temp_r6_13;
	if (temp_r7_9 & 0x7FFF) {
		temp_r5_17 = temp_r6_13 | (((temp_r7_9 << 0xC) & 0x07800000) + 0x38000000);
		sp54       = temp_r5_17;
		sp54       = temp_r5_17 | ((temp_r7_9 << 0xC) & 0x7FF000);
	}
	temp_r7_10 = M2C_FIELD(arg1, u16*, 0x12);
	temp_r6_14 = (temp_r7_10 << 0x10) & 0x80000000;
	sp50       = temp_r6_14;
	if (temp_r7_10 & 0x7FFF) {
		temp_r5_18 = temp_r6_14 | (((temp_r7_10 << 0xC) & 0x07800000) + 0x38000000);
		sp50       = temp_r5_18;
		sp50       = temp_r5_18 | ((temp_r7_10 << 0xC) & 0x7FF000);
	}
	temp_r6_15 = M2C_FIELD(arg1, u16*, 0x14);
	temp_r5_19 = (temp_r6_15 << 0x10) & 0x80000000;
	sp4C       = temp_r5_19;
	if (temp_r6_15 & 0x7FFF) {
		temp_r4 = temp_r5_19 | (((temp_r6_15 << 0xC) & 0x07800000) + 0x38000000);
		sp4C    = temp_r4;
		sp4C    = temp_r4 | ((temp_r6_15 << 0xC) & 0x7FF000);
	}
	temp_r6_16 = M2C_FIELD(arg0, u16*, 0x10);
	temp_r5_20 = (temp_r6_16 << 0x10) & 0x80000000;
	sp48       = temp_r5_20;
	if (temp_r6_16 & 0x7FFF) {
		temp_r4_2 = temp_r5_20 | (((temp_r6_16 << 0xC) & 0x07800000) + 0x38000000);
		sp48      = temp_r4_2;
		sp48      = temp_r4_2 | ((temp_r6_16 << 0xC) & 0x7FF000);
	}
	temp_r6_17 = M2C_FIELD(arg0, u16*, 0x12);
	temp_r5_21 = (temp_r6_17 << 0x10) & 0x80000000;
	sp44       = temp_r5_21;
	if (temp_r6_17 & 0x7FFF) {
		temp_r4_3 = temp_r5_21 | (((temp_r6_17 << 0xC) & 0x07800000) + 0x38000000);
		sp44      = temp_r4_3;
		sp44      = temp_r4_3 | ((temp_r6_17 << 0xC) & 0x7FF000);
	}
	temp_r6_18 = M2C_FIELD(arg0, u16*, 0x14);
	temp_r5_22 = (temp_r6_18 << 0x10) & 0x80000000;
	sp40       = temp_r5_22;
	if (temp_r6_18 & 0x7FFF) {
		temp_r4_4 = temp_r5_22 | (((temp_r6_18 << 0xC) & 0x07800000) + 0x38000000);
		sp40      = temp_r4_4;
		sp40      = temp_r4_4 | ((temp_r6_18 << 0xC) & 0x7FF000);
	}
	M2C_BITWISE(f32, sp18) = M2C_BITWISE(f32, sp48) - M2C_BITWISE(f32, sp54);
	if ((s32)(M2C_BITWISE(s32, sp18) & 0xFFF) >= 0x800) {
		temp_r5_23 = (u8)(M2C_BITWISE(u32, sp18) >> 0x17U);
		if (((s32)temp_r5_23 > 0xC)
		    && (((s32)temp_r5_23 < 0xFE)
		        || ((u32)((M2C_BITWISE(s32, sp18) & 0x7FF000) + 0xFF810000) != -0x1000U))) {
			temp_r4_5 = M2C_BITWISE(s32, sp18) & 0x80000000;
			sp1C      = temp_r4_5;
			sp1C      = temp_r4_5 | ((temp_r5_23 - 0xC) << 0x17);
			sp18 += M2C_BITWISE(f32, sp1C);
		}
	}
	temp_r4_6 = M2C_BITWISE(s32, sp18) & 0xFFFFF000;
	sp18      = temp_r4_6;
	if ((s32)(temp_r4_6 & 0x7F800000) > 0x3F800000) {
		sp18 = (sp18 & 0x80000000) | 0x7FFF0000 | 0xF000;
	}
	if ((s32)(sp18 & 0x7F800000) < 0x38000000) {
		sp18 &= 0x80000000;
	}
	var_r5 = (sp18 >> 0x10U) & 0x8000;
	if (sp18 & 0x7FFFFFFF) {
		var_r5 = (u16)(var_r5 | (((u8)(sp18 >> 0x17U) - 0x70) << 0xB)) | ((sp18 >> 0xCU) & 0x7FF);
	}
	M2C_BITWISE(f32, sp10)      = M2C_BITWISE(f32, sp44) - M2C_BITWISE(f32, sp50);
	M2C_FIELD(arg0, u16*, 0x10) = var_r5;
	if ((s32)(M2C_BITWISE(s32, sp10) & 0xFFF) >= 0x800) {
		temp_r5_24 = (u8)(M2C_BITWISE(u32, sp10) >> 0x17U);
		if (((s32)temp_r5_24 > 0xC)
		    && (((s32)temp_r5_24 < 0xFE)
		        || ((u32)((M2C_BITWISE(s32, sp10) & 0x7FF000) + 0xFF810000) != -0x1000U))) {
			temp_r4_7 = M2C_BITWISE(s32, sp10) & 0x80000000;
			sp14      = temp_r4_7;
			sp14      = temp_r4_7 | ((temp_r5_24 - 0xC) << 0x17);
			sp10 += M2C_BITWISE(f32, sp14);
		}
	}
	temp_r4_8 = M2C_BITWISE(s32, sp10) & 0xFFFFF000;
	sp10      = temp_r4_8;
	if ((s32)(temp_r4_8 & 0x7F800000) > 0x3F800000) {
		sp10 = (sp10 & 0x80000000) | 0x7FFF0000 | 0xF000;
	}
	if ((s32)(sp10 & 0x7F800000) < 0x38000000) {
		sp10 &= 0x80000000;
	}
	var_r5_2 = (sp10 >> 0x10U) & 0x8000;
	if (sp10 & 0x7FFFFFFF) {
		var_r5_2
		    = (u16)(var_r5_2 | (((u8)(sp10 >> 0x17U) - 0x70) << 0xB)) | ((sp10 >> 0xCU) & 0x7FF);
	}
	M2C_BITWISE(f32, sp8)       = M2C_BITWISE(f32, sp40) - M2C_BITWISE(f32, sp4C);
	M2C_FIELD(arg0, u16*, 0x12) = var_r5_2;
	if ((s32)(M2C_BITWISE(s32, sp8) & 0xFFF) >= 0x800) {
		temp_r5_25 = (u8)(M2C_BITWISE(u32, sp8) >> 0x17U);
		if (((s32)temp_r5_25 > 0xC)
		    && (((s32)temp_r5_25 < 0xFE)
		        || ((u32)((M2C_BITWISE(s32, sp8) & 0x7FF000) + 0xFF810000) != -0x1000U))) {
			temp_r4_9 = M2C_BITWISE(s32, sp8) & 0x80000000;
			spC       = temp_r4_9;
			spC       = temp_r4_9 | ((temp_r5_25 - 0xC) << 0x17);
			sp8 += M2C_BITWISE(f32, spC);
		}
	}
	temp_r4_10 = M2C_BITWISE(s32, sp8) & 0xFFFFF000;
	sp8        = temp_r4_10;
	if ((s32)(temp_r4_10 & 0x7F800000) > 0x3F800000) {
		sp8 = (sp8 & 0x80000000) | 0x7FFF0000 | 0xF000;
	}
	if ((s32)(sp8 & 0x7F800000) < 0x38000000) {
		sp8 &= 0x80000000;
	}
	var_r5_3 = (sp8 >> 0x10U) & 0x8000;
	if (sp8 & 0x7FFFFFFF) {
		var_r5_3 = (u16)(var_r5_3 | (((u8)(sp8 >> 0x17U) - 0x70) << 0xB)) | ((sp8 >> 0xCU) & 0x7FF);
	}
	M2C_FIELD(arg0, u16*, 0x14) = var_r5_3;
}

void fn_8022CD7C(u8* arg0, u8* arg1, u8* arg2)
{
	M2C_FIELD(arg0, f32*, 0x14) = (f32)((M2C_FIELD(arg1, f32*, 0x14) * M2C_FIELD(arg2, f32*, 0x14))
	    - ((M2C_FIELD(arg1, f32*, 0x10) * M2C_FIELD(arg2, f32*, 0x10))
	        + ((M2C_FIELD(arg1, f32*, 8) * M2C_FIELD(arg2, f32*, 8))
	            + (M2C_FIELD(arg1, f32*, 0xC) * M2C_FIELD(arg2, f32*, 0xC)))));
	M2C_FIELD(arg0, f32*, 8)    = (f32)((M2C_FIELD(arg1, f32*, 0xC) * M2C_FIELD(arg2, f32*, 0x10))
	    - (M2C_FIELD(arg1, f32*, 0x10) * M2C_FIELD(arg2, f32*, 0xC)));
	M2C_FIELD(arg0, f32*, 0xC)  = (f32)((M2C_FIELD(arg1, f32*, 0x10) * M2C_FIELD(arg2, f32*, 8))
	    - (M2C_FIELD(arg1, f32*, 8) * M2C_FIELD(arg2, f32*, 0x10)));
	M2C_FIELD(arg0, f32*, 0x10) = (f32)((M2C_FIELD(arg1, f32*, 8) * M2C_FIELD(arg2, f32*, 0xC))
	    - (M2C_FIELD(arg1, f32*, 0xC) * M2C_FIELD(arg2, f32*, 8)));
	M2C_FIELD(arg0, f32*, 8)    = (f32)((M2C_FIELD(arg2, f32*, 8) * M2C_FIELD(arg1, f32*, 0x14))
	    + M2C_FIELD(arg0, f32*, 8));
	M2C_FIELD(arg0, f32*, 0xC)  = (f32)((M2C_FIELD(arg2, f32*, 0xC) * M2C_FIELD(arg1, f32*, 0x14))
	    + M2C_FIELD(arg0, f32*, 0xC));
	M2C_FIELD(arg0, f32*, 0x10) = (f32)((M2C_FIELD(arg2, f32*, 0x10) * M2C_FIELD(arg1, f32*, 0x14))
	    + M2C_FIELD(arg0, f32*, 0x10));
	M2C_FIELD(arg0, f32*, 8)    = (f32)((M2C_FIELD(arg1, f32*, 8) * M2C_FIELD(arg2, f32*, 0x14))
	    + M2C_FIELD(arg0, f32*, 8));
	M2C_FIELD(arg0, f32*, 0xC)  = (f32)((M2C_FIELD(arg1, f32*, 0xC) * M2C_FIELD(arg2, f32*, 0x14))
	    + M2C_FIELD(arg0, f32*, 0xC));
	M2C_FIELD(arg0, f32*, 0x10) = (f32)((M2C_FIELD(arg1, f32*, 0x10) * M2C_FIELD(arg2, f32*, 0x14))
	    + M2C_FIELD(arg0, f32*, 0x10));
	M2C_FIELD(arg0, f32*, 0x18) = (f32)(M2C_FIELD(arg1, f32*, 0x18) + M2C_FIELD(arg2, f32*, 0x18));
	M2C_FIELD(arg0, f32*, 0x1C) = (f32)(M2C_FIELD(arg1, f32*, 0x1C) + M2C_FIELD(arg2, f32*, 0x1C));
	M2C_FIELD(arg0, f32*, 0x20) = (f32)(M2C_FIELD(arg1, f32*, 0x20) + M2C_FIELD(arg2, f32*, 0x20));
}

s32 fn_8022CEB0(void)
{
	s32 sp34;
	s32 (*sp30)(u8*);
	s32 (*sp2C)(u8*, s32, M2C_UNK);
	u8* (*sp28)(s32, u8*, M2C_UNK);
	void (*sp24)(u8*, u8*, f32, f32, f32, f32);
	void (*sp20)(u8*, u8*, u8*);
	void (*sp1C)(u8*, u8*, u8*, u8*, f32);
	void (*sp18)(u8*, u8*, u8*, f32);
	void (*sp14)(u8*, u8*);
	s32 sp10;
	s32 spC;
	s32 sp8;

	sp8  = 2;
	sp10 = 0x18;
	spC  = 0x24;
	sp14 = fn_8022B4F0;
	sp18 = fn_8022BD18;
	sp1C = fn_8022B5FC;
	sp20 = fn_8022CD7C;
	sp24 = fn_8022C314;
	sp28 = fn_8022C11C;
	sp2C = fn_8022C21C;
	sp30 = fn_8022C300;
	sp34 = 0x18;
	return fn_8020C088(&sp8, fn_8022C21C, fn_8022C11C, fn_8022C314, fn_8022CD7C, fn_8022B5FC,
	           fn_8022BD18, fn_8022B4F0)
	    != 0;
}

#pragma dont_inline on
u8* fn_8022CF5C(u8* arg0)
{
	f32 sp34;
	f32 sp30;
	f32 sp2C;
	f32 sp28;
	f32 sp24;
	f32 sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f0;
	f32 temp_f1;
	f32 temp_f24;
	f32 temp_f26;
	f32 temp_f27;
	f32 temp_f28;
	f32 temp_f29;
	f32 temp_f2;
	f32 temp_f3;
	f32 temp_f3_2;
	f32 temp_f4;
	s32 var_r27;
	u8* var_r29;
	s32 var_r29_2;
	u8* temp_r3;
	u8* temp_r4;
	u8* temp_r4_2;
	u8* var_r30;
	u8* var_r31;

	temp_r3 = fn_8020C1AC(
	    2, M2C_FIELD(arg0, s32*, 4), M2C_FIELD(arg0, s32*, 8), M2C_FIELD(arg0, f32*, 0xC));
	var_r31 = M2C_FIELD(arg0, u8**, 0x10);
	var_r30 = M2C_FIELD(temp_r3, u8**, 0x10);
	fn_80199F50(&sp20, var_r31 + 0x18);
	var_r29 = var_r31 + 0x24;
	for (var_r27 = 1; var_r27 < (s32)M2C_FIELD(temp_r3, s32*, 4); var_r29 += 0x24, var_r27 += 1) {
		fn_80199F78(&sp20, var_r29 + 0x18);
	}
	var_r29_2                      = 0;
	temp_f3                        = sp20 - sp2C;
	temp_f4                        = sp24 - sp30;
	temp_f1                        = lbl_80430180 * temp_f3;
	sp14                           = temp_f3;
	temp_f26                       = lbl_80430180 * temp_f4;
	sp18                           = temp_f4;
	temp_f3_2                      = sp28 - sp34;
	temp_r4                        = M2C_FIELD(temp_r3, u8**, 0x14);
	sp14                           = temp_f1;
	temp_f0                        = temp_f1 + sp2C;
	temp_f27                       = lbl_80430180 * temp_f3_2;
	sp1C                           = temp_f3_2;
	temp_f28                       = temp_f26 + sp30;
	sp18                           = temp_f26;
	temp_f29                       = temp_f27 + sp34;
	sp1C                           = temp_f27;
	M2C_FIELD(temp_r4, f32*, 0xC)  = sp14;
	M2C_FIELD(temp_r4, f32*, 0x10) = sp18;
	M2C_FIELD(temp_r4, f32*, 0x14) = sp1C;
	sp8                            = temp_f0;
	temp_r4_2                      = M2C_FIELD(temp_r3, u8**, 0x14);
	spC                            = temp_f28;
	sp10                           = temp_f29;
	M2C_FIELD(temp_r4_2, f32*, 0)  = sp8;
	M2C_FIELD(temp_r4_2, f32*, 4)  = spC;
	M2C_FIELD(temp_r4_2, f32*, 8)  = sp10;
	for (; var_r29_2 < (s32)M2C_FIELD(temp_r3, s32*, 4);
	    var_r31 += 0x24, var_r30 += 0x18, var_r29_2 += 1) {
		M2C_FIELD(var_r30, u16*, 8)   = fn_8022B3E4(M2C_FIELD(var_r31, f32*, 8));
		M2C_FIELD(var_r30, u16*, 0xA) = fn_8022B3E4(M2C_FIELD(var_r31, f32*, 0xC));
		M2C_FIELD(var_r30, u16*, 0xC) = fn_8022B3E4(M2C_FIELD(var_r31, f32*, 0x10));
		M2C_FIELD(var_r30, u16*, 0xE) = fn_8022B3E4(M2C_FIELD(var_r31, f32*, 0x14));
		temp_f2                       = M2C_FIELD(var_r31, f32*, 0x1C);
		temp_f24                      = (M2C_FIELD(var_r31, f32*, 0x20) - temp_f29) / temp_f27;
		M2C_FIELD(var_r30, u16*, 0x10)
		    = fn_8022B3E4((M2C_FIELD(var_r31, f32*, 0x18) - (f32)temp_f0) / (f32)temp_f1);
		M2C_FIELD(var_r30, u16*, 0x12) = fn_8022B3E4((temp_f2 - temp_f28) / temp_f26);
		M2C_FIELD(var_r30, u16*, 0x14) = fn_8022B3E4(temp_f24);
		M2C_FIELD(var_r30, f32*, 4)    = (f32)M2C_FIELD(var_r31, f32*, 4);
		if (lbl_80430184 == M2C_FIELD(var_r30, f32*, 4)) {
			M2C_FIELD(var_r30, s32*, 0) = 0;
		} else {
			M2C_FIELD(var_r30, s32*, 0)
			    = (s32)(var_r30 - (((var_r31 - (u8*)M2C_FIELD(var_r31, s32*, 0)) / 36) * 0x18));
		}
	}
	return temp_r3;
}
#pragma dont_inline reset

u8* fn_8022D1F0(u8* arg0)
{
	s32 temp_r4_2;
	s32 temp_r4_4;
	s32 temp_r5;
	u8* temp_r5_2;
	u8* temp_r5_3;
	s32 temp_r7;
	s32 var_ctr;
	s32 var_ctr_2;
	s32 var_r3;
	s32 var_r6;
	s32 var_r6_2;
	s32 var_r7;
	s32 var_r7_2;
	s32 var_r8;
	s32 var_r8_2;
	u32 temp_r4;
	u32 temp_r4_3;
	u32 var_r0;

	if (fn_8023943C() < 3) {
		temp_r5 = M2C_FIELD(arg0, s32*, 0x10);
		var_r0  = *M2C_FIELD(arg0, u32**, 0x20);
		if (var_r0 == 0x10U) {
			var_r3  = 1;
			var_r6  = 4;
			var_ctr = temp_r5 - 1;
			if (temp_r5 > 1) {
				do {
					temp_r5_2 = M2C_FIELD(arg0, u8**, 0x24);
					temp_r7   = *(temp_r5_2 + var_r6);
					temp_r4   = *(M2C_FIELD(arg0, u8**, 0x18) + var_r6) + 0xFF000000;
					switch (temp_r4) { /* switch 1; irregular */
						case 2:        /* switch 1 */
							var_r8 = temp_r7 - 0xC;
							var_r7 = (var_r8 + 3) & 0xFFFFFFFC;
							break;
						case 3: /* switch 1 */
							var_r8 = temp_r7 - 0x14;
							var_r7 = (var_r8 + 3) & 0xFFFFFFFC;
							break;
						case 4: /* switch 1 */
							var_r8 = temp_r7 - 0xC;
							var_r7 = (var_r8 + 3) & 0xFFFFFFFC;
							break;
						case 5: /* switch 1 */
							var_r8 = temp_r7 - 0xC;
							var_r7 = (var_r8 + 3) & 0xFFFFFFFC;
							break;
						default: /* switch 1 */
							var_r8 = temp_r7;
							var_r7 = *(M2C_FIELD(arg0, u32**, 0x20) + var_r6);
							break;
					}
					*(temp_r5_2 + var_r6) = var_r8;
					var_r3 += 1;
					*(M2C_FIELD(arg0, u32**, 0x20) + var_r6) = var_r7;
					*(M2C_FIELD(arg0, u8**, 0x1C) + var_r6)  = var_r0;
					temp_r4_2 = *(M2C_FIELD(arg0, u32**, 0x20) + var_r6);
					var_r6 += 4;
					var_r0 += temp_r4_2;
					var_ctr -= 1;
				} while (var_ctr != 0);
			}
		} else {
			var_r3    = 1;
			var_r6_2  = 4;
			var_ctr_2 = temp_r5 - 1;
			if (temp_r5 > 1) {
				do {
					temp_r5_3 = M2C_FIELD(arg0, u8**, 0x24);
					var_r7_2  = *(temp_r5_3 + var_r6_2);
					temp_r4_3 = *(M2C_FIELD(arg0, u8**, 0x18) + var_r6_2) + 0xFF000000;
					switch (temp_r4_3) { /* switch 2; irregular */
						case 2:          /* switch 2 */
							var_r7_2 += 0xC;
							var_r8_2 = (var_r7_2 + 3) & 0xFFFFFFFC;
							break;
						case 3: /* switch 2 */
						case 4: /* switch 2 */
							var_r7_2 += 0x14;
							var_r8_2 = (var_r7_2 + 3) & 0xFFFFFFFC;
							break;
						case 5: /* switch 2 */
							var_r7_2 += 0xC;
							var_r8_2 = (var_r7_2 + 3) & 0xFFFFFFFC;
							break;
						default: /* switch 2 */
							var_r8_2 = *(M2C_FIELD(arg0, u32**, 0x20) + var_r6_2);
							break;
					}
					*(temp_r5_3 + var_r6_2) = var_r7_2;
					var_r3 += 1;
					*(M2C_FIELD(arg0, u32**, 0x20) + var_r6_2) = var_r8_2;
					*(M2C_FIELD(arg0, u8**, 0x1C) + var_r6_2)  = var_r0;
					temp_r4_4 = *(M2C_FIELD(arg0, u32**, 0x20) + var_r6_2);
					var_r6_2 += 4;
					var_r0 += temp_r4_4;
					var_ctr_2 -= 1;
				} while (var_ctr_2 != 0);
			}
		}
		*(M2C_FIELD(arg0, u8**, 0x1C) + (var_r3 * 4)) = var_r0;
	}
	return arg0;
}

void fn_8022D3C0(u32 arg0)
{
	if ((u32)lbl_8042ABB0[3] == arg0) {
		lbl_8042ABB0[3] = 0;
		return;
	}
	if ((u32)lbl_8042ABB0[2] == arg0) {
		lbl_8042ABB0[2] = 0;
	}
}

s32 fn_8022D3F8(s32 arg0)
{
	fn_802355AC(fn_8022D1F0, fn_8022D1F0);
	fn_802355C0(fn_8022D3C0);
	return arg0;
}

void fn_8022D43C(void) { }

u8* fn_8022D440(u8* arg0)
{
	u32 temp_r3;
	u32 temp_r3_2;

	temp_r3 = M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10);
	if (temp_r3 != (u32)lbl_8042ABB0[2]) {
		lbl_8042ABB0[2] = temp_r3;
		lbl_8042ABB0[5] = fn_8023506C(1U);
		lbl_8042ABB0[6]
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10), 2, lbl_8042ABB0);
		lbl_8042ABB0[7]
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10), 3, lbl_8042ABB0);
		lbl_8042ABB0[8]
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10), 5, lbl_8042ABB0);
		lbl_8042ABB0[9]
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10), 6, lbl_8042ABB0);
		lbl_8042ABB0[0xB] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10), 0x01000000, lbl_8042ABB0);
		lbl_8042ABB0[0xC] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10), 0x01000001, lbl_8042ABB0);
		lbl_8042ABB0[0xE] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10), 0x01000002, lbl_8042ABB0);
		lbl_8042ABB0[0xF] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10), 0x01000003, lbl_8042ABB0);
		lbl_8042ABB0[0x10] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10), 0x01000004, lbl_8042ABB0);
		lbl_8042ABB0[0x11] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10), 0x01000005, lbl_8042ABB0);
		lbl_8042ABB0[0x1F] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10), 0x01000006, lbl_8042ABB0);
		lbl_8042ABB0[0x20] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10), 0x01000007, lbl_8042ABB0);
		lbl_8042ABB0[0x21] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0xC), u32*, 0x10), 0x01000008, lbl_8042ABB0);
	}
	temp_r3_2 = M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10);
	if (temp_r3_2 != (u32)lbl_8042ABB0[3]) {
		lbl_8042ABB0[3]    = temp_r3_2;
		lbl_8042ABB0[0x13] = fn_8023506C(0U);
		lbl_8042ABB0[0x14]
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 2, lbl_8042ABB0);
		lbl_8042ABB0[0x15]
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 3, lbl_8042ABB0);
		lbl_8042ABB0[0x16]
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 5, lbl_8042ABB0);
		lbl_8042ABB0[0x12]
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 1, lbl_8042ABB0);
		lbl_8042ABB0[0x17]
		    = fn_8023506C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 6, lbl_8042ABB0);
		lbl_8042ABB0[0x19] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 0x01000000, lbl_8042ABB0);
		lbl_8042ABB0[0x1A] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 0x01000001, lbl_8042ABB0);
		lbl_8042ABB0[0x1B] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 0x01000002, lbl_8042ABB0);
		lbl_8042ABB0[0x1C] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 0x01000003, lbl_8042ABB0);
		lbl_8042ABB0[0x1D] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 0x01000004, lbl_8042ABB0);
		lbl_8042ABB0[0x1E] = fn_8023506C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 0x01000005, lbl_8042ABB0);
		lbl_8042ABB0[0x23]
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 0, lbl_8042ABB0);
		lbl_8042ABB0[0x24]
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 2, lbl_8042ABB0);
		lbl_8042ABB0[0x25]
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 3, lbl_8042ABB0);
		lbl_8042ABB0[0x26]
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 5, lbl_8042ABB0);
		lbl_8042ABB0[0x22]
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 1, lbl_8042ABB0);
		lbl_8042ABB0[0x27]
		    = fn_8023501C(M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 6, lbl_8042ABB0);
		lbl_8042ABB0[0x29] = fn_8023501C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 0x01000000, lbl_8042ABB0);
		lbl_8042ABB0[0x2A] = fn_8023501C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 0x01000001, lbl_8042ABB0);
		lbl_8042ABB0[0x2B] = fn_8023501C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 0x01000002, lbl_8042ABB0);
		lbl_8042ABB0[0x2C] = fn_8023501C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 0x01000003, lbl_8042ABB0);
		lbl_8042ABB0[0x2D] = fn_8023501C(
		    M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), u32*, 0x10), 0x01000005, lbl_8042ABB0);
	}
	return arg0;
}

s32 fn_8022D8EC(void)
{
	*lbl_8042ABB0 = RwEngineRegisterPlugin(0, 0x132, fn_8022D3F8, fn_8022D43C);
	fn_80239888(fn_8022D948, fn_8022D948, lbl_8042ABB0);
	fn_8023989C(fn_8022DE28);
	return 1;
}

u8* fn_8022D948(u8* arg0)
{
	u8* (*sp1C0)(u8*, u8*, s32);
	u8* (*sp110)(u8*, u8*, s32);
	u8* (*sp88)(u8*, u8*);
	u8* (*sp84)(u8*, s32*);
	u8* (*sp80)(u8*, s32);
	u8* (*sp7C)(u8*, s32);
	u8* (*sp74)(u8*);
	u8* (*sp60)(u8*, u8*, s32);
	M2C_UNK sp5C;
	M2C_UNK sp58;
	M2C_UNK sp54;
	M2C_UNK sp50;
	M2C_UNK sp48;
	u8* (*sp34)(u8*, u8*, s32);
	M2C_UNK* sp30;
	M2C_UNK* sp2C;
	M2C_UNK* sp28;
	M2C_UNK* sp24;
	M2C_UNK* sp20;
	M2C_UNK* sp1C;
	M2C_UNK* sp14;
	M2C_UNK* sp10;
	M2C_UNK* spC;
	u8* (*sp8)(u8*, u8*, s32);
	s32 temp_r3;
	s32 temp_r3_2;
	s32 temp_r6;
	s32 temp_r6_2;
	s32 temp_r6_3;
	s32 var_ctr;
	s32 var_r10;
	s32 var_r31;
	u32 temp_r12_2;
	u32 temp_r12_3;
	u32 temp_r12_4;
	u32 temp_r12_6;
	u32 temp_r12_7;
	u32 temp_r12_8;
	u8* (**temp_r5)(u8*, u8*, s32);
	u8* (**var_r11)(u8*, u8*, s32);
	u8* (**var_r6)(u8*, u8*, s32);
	u8* (**var_r7)(u8*, u8*, s32);
	s32* var_r8;
	u8* (**var_r9)(u8*, u8*, s32);
	u8* (*temp_r12)(u8*, u8*, s32);
	u8* (*temp_r12_5)(u8*, u8*, s32);
	s32 temp_r4;
	s32 temp_r4_2;
	s32 temp_r4_3;
	s32 temp_r4_4;
	s32 temp_r4_5;
	s32 temp_r4_6;
	s32 temp_r4_7;
	s32 temp_r4_8;
	s32 temp_r4_9;

	memset(&sp1C0, 0, 0x160);
	memset(&sp110, 0, 0xB0);
	memset(&sp60, 0, 0xB0);
	memset(&sp8, 0, 0x2C);
	var_r31 = 1;
	temp_r3 = M2C_FIELD(arg0, s32*, 4) & 0xFF0000;
	switch (temp_r3) { /* irregular */
		case 0x0:
			break;
		case 0x10000:
			sp60    = fn_8023182C;
			var_r31 = 2;
			sp7C    = fn_80231E5C;
			sp80    = fn_80231FAC;
			sp84    = fn_80231DB8;
			sp74    = fn_80232114;
			sp88    = fn_80231CE8;
			break;
		case 0x20000:
			sp60    = fn_80230AF0;
			var_r31 = 2;
			sp7C    = fn_80231064;
			sp80    = fn_8023113C;
			sp84    = fn_80231004;
			sp88    = fn_80230F78;
			break;
		case 0x30000:
			sp60    = fn_80231208;
			var_r31 = 2;
			sp7C    = fn_802316C8;
			sp80    = fn_80231780;
			sp84    = fn_80231668;
			sp88    = fn_802315DC;
			break;
	}
	sp1C = &fn_80237EBC;
	sp20 = &fn_80237F90;
	sp8  = fn_80236AE4;
	spC  = &fn_80238228;
	sp10 = &fn_80238328;
	sp14 = &fn_802383C0;
	sp24 = &fn_80238444;
	sp28 = &fn_802388D4;
	sp2C = &fn_80238D3C;
	sp30 = &fn_80237FF4;
	if (M2C_FIELD(arg0, s32*, 4) & 0x100) {
		temp_r6            = var_r31 * 0x2C;
		*(&sp34 + temp_r6) = (u8 * (*)(u8*, u8*, s32)) fn_8022E46C;
		*(&sp50 + temp_r6) = (s32)fn_8022E6D4;
		*(&sp54 + temp_r6) = (s32)fn_8022E774;
		var_r31 += 1;
		*(&sp58 + temp_r6) = (s32)fn_8022E674;
		*(&sp5C + temp_r6) = (s32)fn_8022E5D4;
	}
	temp_r3_2 = M2C_FIELD(arg0, s32*, 4);
	if ((temp_r3_2 & 0x200) || (temp_r3_2 & 0x400) || (temp_r3_2 & 0x1000)) {
		temp_r6_2            = var_r31 * 0x2C;
		*(&sp34 + temp_r6_2) = (u8 * (*)(u8*, u8*, s32)) fn_8022EB2C;
		*(&sp50 + temp_r6_2) = (s32)fn_8022FC2C;
		*(&sp54 + temp_r6_2) = (s32)fn_8022FE30;
		*(&sp58 + temp_r6_2) = (s32)fn_8022FB60;
		var_r31 += 1;
		*(&sp48 + temp_r6_2) = (s32)fn_8022FF58;
		*(&sp5C + temp_r6_2) = (s32)fn_8022FA00;
	}
	if (M2C_FIELD(arg0, s32*, 4) & 0x800) {
		temp_r6_3            = var_r31 * 0x2C;
		*(&sp34 + temp_r6_3) = (u8 * (*)(u8*, u8*, s32)) fn_8023031C;
		*(&sp50 + temp_r6_3) = (s32)fn_802308A4;
		*(&sp54 + temp_r6_3) = (s32)fn_8023096C;
		*(&sp58 + temp_r6_3) = (s32)fn_80230834;
		var_r31 += 1;
		*(&sp48 + temp_r6_3) = (s32)fn_802309F8;
		*(&sp5C + temp_r6_3) = (s32)fn_80230794;
	}
	memset(&sp34, 0, 0x2C);
	var_r7  = &sp1C0;
	temp_r5 = var_r7;
	var_r6  = &sp110;
	var_r8  = (s32*)&sp34;
	var_r9  = &sp8;
	var_r11 = &sp60;
	var_r10 = 0;
	var_ctr = 0xB;
	do {
		temp_r12 = M2C_FIELD(var_r6, u8 * (**)(u8*, u8*, s32), 0);
		if (temp_r12 != NULL) {
			temp_r4                           = *var_r8;
			*var_r8                           = temp_r4 + 1;
			*(var_r7 + ((s32)temp_r4 * 0x2C)) = temp_r12;
		}
		temp_r12_2 = M2C_FIELD(var_r6, u32*, 0x2C);
		if (temp_r12_2 != 0U) {
			temp_r4_2                           = *var_r8;
			*var_r8                             = temp_r4_2 + 1;
			*(var_r7 + ((s32)temp_r4_2 * 0x2C)) = (u8 * (*)(u8*, u8*, s32)) temp_r12_2;
		}
		temp_r12_3 = M2C_FIELD(var_r6, u32*, 0x58);
		if (temp_r12_3 != 0U) {
			temp_r4_3                           = *var_r8;
			*var_r8                             = temp_r4_3 + 1;
			*(var_r7 + ((s32)temp_r4_3 * 0x2C)) = (u8 * (*)(u8*, u8*, s32)) temp_r12_3;
		}
		temp_r12_4 = M2C_FIELD(var_r6, u32*, 0x84);
		if (temp_r12_4 != 0U) {
			temp_r4_4                           = *var_r8;
			*var_r8                             = temp_r4_4 + 1;
			*(var_r7 + ((s32)temp_r4_4 * 0x2C)) = (u8 * (*)(u8*, u8*, s32)) temp_r12_4;
		}
		temp_r4_5  = *var_r8;
		temp_r12_5 = M2C_FIELD(var_r11, u8 * (**)(u8*, u8*, s32), 0);
		*var_r8    = temp_r4_5 + 1;
		*(temp_r5 + (((s32)temp_r4_5 * 0x2C) + var_r10)) = *var_r9;
		if (temp_r12_5 != NULL) {
			temp_r4_6                           = *var_r8;
			*var_r8                             = temp_r4_6 + 1;
			*(var_r7 + ((s32)temp_r4_6 * 0x2C)) = temp_r12_5;
		}
		temp_r12_6 = M2C_FIELD(var_r11, u32*, 0x2C);
		if (temp_r12_6 != 0U) {
			temp_r4_7                           = *var_r8;
			*var_r8                             = temp_r4_7 + 1;
			*(var_r7 + ((s32)temp_r4_7 * 0x2C)) = (u8 * (*)(u8*, u8*, s32)) temp_r12_6;
		}
		temp_r12_7 = M2C_FIELD(var_r11, u32*, 0x58);
		if (temp_r12_7 != 0U) {
			temp_r4_8                           = *var_r8;
			*var_r8                             = temp_r4_8 + 1;
			*(var_r7 + ((s32)temp_r4_8 * 0x2C)) = (u8 * (*)(u8*, u8*, s32)) temp_r12_7;
		}
		temp_r12_8 = M2C_FIELD(var_r11, u32*, 0x84);
		if (temp_r12_8 != 0U) {
			temp_r4_9                           = *var_r8;
			*var_r8                             = temp_r4_9 + 1;
			*(var_r7 + ((s32)temp_r4_9 * 0x2C)) = (u8 * (*)(u8*, u8*, s32)) temp_r12_8;
		}
		var_r6 += 4;
		var_r7 += 4;
		var_r8 += 4;
		var_r9 += 4;
		var_r10 += 4;
		var_r11 += 4;
		var_ctr -= 1;
	} while (var_ctr != 0);
	fn_8023239C(arg0, var_r31, &sp1C0);
	return arg0;
}

u8* fn_8022DE28(u8* arg0)
{
	u8* (*sp124)(u8*, u8*, s32);
	u8* (*spB4)(u8*, u8*, s32);
	M2C_UNK sp98;
	u8* (*sp44)(u8*, u8*, s32);
	u8* (*sp24)(u8*, u8*, s32);
	u8* (*sp8)(u8*, u8*, s32);
	s32 temp_r3;
	s32 var_ctr;
	s32 var_r10;
	s32 var_r31;
	u32 temp_r12_2;
	u32 temp_r12_3;
	u32 temp_r12_4;
	u32 temp_r12_6;
	u32 temp_r12_7;
	u32 temp_r12_8;
	u8* (**temp_r5)(u8*, u8*, s32);
	u8* (**var_r11)(u8*, u8*, s32);
	u8* (**var_r6)(u8*, u8*, s32);
	u8* (**var_r7)(u8*, u8*, s32);
	s32* var_r8;
	u8* (**var_r9)(u8*, u8*, s32);
	u8* (*temp_r12)(u8*, u8*, s32);
	u8* (*temp_r12_5)(u8*, u8*, s32);
	s32 temp_r4;
	s32 temp_r4_2;
	s32 temp_r4_3;
	s32 temp_r4_4;
	s32 temp_r4_5;
	s32 temp_r4_6;
	s32 temp_r4_7;
	s32 temp_r4_8;
	s32 temp_r4_9;

	memset(&sp124, 0, 0xE0);
	memset(&spB4, 0, 0x70);
	memset(&sp44, 0, 0x70);
	memset(&sp8, 0, 0x1C);
	var_r31 = 1;
	sp8     = fn_80235E64;
	if (M2C_FIELD(arg0, s32*, 4) & 0x100) {
		var_r31 = 2;
		spB4    = fn_8022E09C;
	}
	temp_r3 = M2C_FIELD(arg0, s32*, 4);
	if ((temp_r3 & 0x200) || (temp_r3 & 0x400) || (temp_r3 & 0x1000)) {
		*(&sp98 + (var_r31 * 0x1C)) = (s32)fn_8022E814;
		var_r31 += 1;
	}
	if (M2C_FIELD(arg0, s32*, 4) & 0x800) {
		*(&sp98 + (var_r31 * 0x1C)) = (s32)fn_802301CC;
		var_r31 += 1;
	}
	memset(&sp24, 0, 0x20);
	var_r7  = &sp124;
	temp_r5 = var_r7;
	var_r6  = &spB4;
	var_r8  = (s32*)&sp24;
	var_r9  = &sp8;
	var_r11 = &sp44;
	var_r10 = 0;
	var_ctr = 7;
	do {
		temp_r12 = M2C_FIELD(var_r6, u8 * (**)(u8*, u8*, s32), 0);
		if (temp_r12 != NULL) {
			temp_r4                           = *var_r8;
			*var_r8                           = temp_r4 + 1;
			*(var_r7 + ((s32)temp_r4 * 0x1C)) = temp_r12;
		}
		temp_r12_2 = M2C_FIELD(var_r6, u32*, 0x1C);
		if (temp_r12_2 != 0U) {
			temp_r4_2                           = *var_r8;
			*var_r8                             = temp_r4_2 + 1;
			*(var_r7 + ((s32)temp_r4_2 * 0x1C)) = (u8 * (*)(u8*, u8*, s32)) temp_r12_2;
		}
		temp_r12_3 = M2C_FIELD(var_r6, u32*, 0x38);
		if (temp_r12_3 != 0U) {
			temp_r4_3                           = *var_r8;
			*var_r8                             = temp_r4_3 + 1;
			*(var_r7 + ((s32)temp_r4_3 * 0x1C)) = (u8 * (*)(u8*, u8*, s32)) temp_r12_3;
		}
		temp_r12_4 = M2C_FIELD(var_r6, u32*, 0x54);
		if (temp_r12_4 != 0U) {
			temp_r4_4                           = *var_r8;
			*var_r8                             = temp_r4_4 + 1;
			*(var_r7 + ((s32)temp_r4_4 * 0x1C)) = (u8 * (*)(u8*, u8*, s32)) temp_r12_4;
		}
		temp_r4_5  = *var_r8;
		temp_r12_5 = M2C_FIELD(var_r11, u8 * (**)(u8*, u8*, s32), 0);
		*var_r8    = temp_r4_5 + 1;
		*(temp_r5 + (((s32)temp_r4_5 * 0x1C) + var_r10)) = *var_r9;
		if (temp_r12_5 != NULL) {
			temp_r4_6                           = *var_r8;
			*var_r8                             = temp_r4_6 + 1;
			*(var_r7 + ((s32)temp_r4_6 * 0x1C)) = temp_r12_5;
		}
		temp_r12_6 = M2C_FIELD(var_r11, u32*, 0x1C);
		if (temp_r12_6 != 0U) {
			temp_r4_7                           = *var_r8;
			*var_r8                             = temp_r4_7 + 1;
			*(var_r7 + ((s32)temp_r4_7 * 0x1C)) = (u8 * (*)(u8*, u8*, s32)) temp_r12_6;
		}
		temp_r12_7 = M2C_FIELD(var_r11, u32*, 0x38);
		if (temp_r12_7 != 0U) {
			temp_r4_8                           = *var_r8;
			*var_r8                             = temp_r4_8 + 1;
			*(var_r7 + ((s32)temp_r4_8 * 0x1C)) = (u8 * (*)(u8*, u8*, s32)) temp_r12_7;
		}
		temp_r12_8 = M2C_FIELD(var_r11, u32*, 0x54);
		if (temp_r12_8 != 0U) {
			temp_r4_9                           = *var_r8;
			*var_r8                             = temp_r4_9 + 1;
			*(var_r7 + ((s32)temp_r4_9 * 0x1C)) = (u8 * (*)(u8*, u8*, s32)) temp_r12_8;
		}
		var_r6 += 4;
		var_r7 += 4;
		var_r8 += 4;
		var_r9 += 4;
		var_r10 += 4;
		var_r11 += 4;
		var_ctr -= 1;
	} while (var_ctr != 0);
	fn_802344D8(arg0, var_r31, &sp124);
	return arg0;
}

u8* fn_8022E09C(u8* arg0, u8* arg1, s32 arg2)
{
	s32 sp80;
	s32 sp7C;
	s32 sp78;
	f32 sp70;
	f32 sp6C;
	f32 sp68;
	f32 sp60;
	f32 sp5C;
	f32 sp58;
	f32 sp50;
	f32 sp4C;
	f32 sp48;
	s32 sp44;
	s32 sp40;
	s32 sp3C;
	s32 sp38;
	s32 sp34;
	s32 sp30;
	s32 sp2C;
	s32 sp28;
	s32 sp24;
	s32 sp20;
	s32 sp1C;
	s32 sp18;
	s32 sp14;
	s32 sp10;
	s32 spC;
	f32 sp8;
	f32 temp_f0;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f2;
	f32 temp_f2_2;
	f32 temp_f30;
	f32 temp_f31;
	f32 temp_f3;
	f32 temp_f4;
	f32 temp_f6;
	f32 var_f3;
	f32 var_f4;
	f32 var_f6;
	s32 temp_cr0_gt;
	s32 temp_r18;
	s32 temp_r6;
	s32 var_r17;
	s32 var_r29;
	u32 temp_r25;
	u32 temp_r26;
	u32 temp_r27;
	u8* temp_r20;
	u8* temp_r21;
	u8* temp_r24;
	u8* temp_r28;
	u8* temp_r30;
	u8* temp_r31;
	u8* var_r18;
	u8* var_r19;
	u8* var_r19_2;
	u8* var_r22;
	u8* var_r23;

	temp_r30 = M2C_FIELD(arg0, u8**, 8);
	var_r18  = NULL;
	var_r23  = NULL;
	var_r17  = 0;
	fn_8022D440(arg0);
	var_r19 = NULL;
	if ((s32)lbl_8042ABB0[9] >= 0) {
		var_r19 = arg0 + lbl_8042ABB0[9];
	}
	if ((s32)lbl_8042ABB0[0xC] >= 0) {
		var_r23 = arg0 + lbl_8042ABB0[0xC];
		if ((u8*)M2C_FIELD(var_r23, u8**, 0x10) == NULL) {
			M2C_FIELD(var_r23, u8**, 0x10) = (u8*)M2C_FIELD(arg0, u8**, 0);
		}
		var_r18 = M2C_FIELD(var_r23, u8**, 0x10);
	}
	if ((u32)M2C_FIELD(M2C_FIELD(var_r18, u8**, 0xC), u32*, 0x10) != (u32)lbl_8042ABB0[4]) {
		lbl_8042ABB0[0xD] = fn_8023506C(1U);
		lbl_8042ABB0[4]   = M2C_FIELD(M2C_FIELD(var_r18, u8**, 0xC), u32*, 0x10);
	}
	temp_r27 = lbl_8042ABB0[0x17];
	temp_r26 = lbl_8042ABB0[0x1A];
	temp_r24 = var_r18 + lbl_8042ABB0[0xD];
	temp_r25 = lbl_8042ABB0[0x13];
	if (var_r19 != NULL) {
		if (M2C_FIELD(var_r19, s32*, 0) & 1) {
			var_r19_2 = *M2C_FIELD(var_r19, u8***, 0x1C);
			var_r17   = *M2C_FIELD(var_r19, s32**, 0x24);
		} else {
			var_r19_2 = NULL;
		}
		temp_r28 = M2C_FIELD(temp_r30, u8**, 4);
		temp_r18 = M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), s32*, 0xC);
		var_r22  = arg1 + M2C_FIELD(arg1, s32*, 0x14);
		var_r29  = M2C_FIELD(arg1, s32*, 8);
		sp8      = M2C_FIELD(temp_r28, f32*, 0x10);
		spC      = M2C_FIELD(temp_r28, s32*, 0x14);
		sp10     = M2C_FIELD(temp_r28, s32*, 0x18);
		sp14     = M2C_FIELD(temp_r28, s32*, 0x1C);
		sp18     = M2C_FIELD(temp_r28, s32*, 0x20);
		sp1C     = M2C_FIELD(temp_r28, s32*, 0x24);
		sp20     = M2C_FIELD(temp_r28, s32*, 0x28);
		sp24     = M2C_FIELD(temp_r28, s32*, 0x2C);
		sp28     = M2C_FIELD(temp_r28, s32*, 0x30);
		sp2C     = M2C_FIELD(temp_r28, s32*, 0x34);
		sp30     = M2C_FIELD(temp_r28, s32*, 0x38);
		sp34     = M2C_FIELD(temp_r28, s32*, 0x3C);
		sp38     = M2C_FIELD(temp_r28, s32*, 0x40);
		sp3C     = M2C_FIELD(temp_r28, s32*, 0x44);
		sp40     = M2C_FIELD(temp_r28, s32*, 0x48);
		sp44     = M2C_FIELD(temp_r28, s32*, 0x4C);
	loop_24:
		temp_cr0_gt = var_r29 > 0;
		var_r29 -= 1;
		if (temp_cr0_gt != 0) {
			if (M2C_FIELD(var_r22, f32*, 4) < M2C_FIELD(var_r22, f32*, 8)) {
				temp_r21 = var_r22 + temp_r25;
				temp_r20 = var_r22 + temp_r26;
				if (M2C_FIELD(temp_r21, f32*, 4) > M2C_FIELD(temp_r20, f32*, 0)) {
					temp_r31 = M2C_FIELD(var_r23, u8**, 0x10);
					fn_801990E0(&sp68, var_r22 + temp_r27);
					var_f3  = lbl_80430188;
					var_f6  = var_f3;
					temp_f1 = (f32)__fabs(sp68);
					temp_f2 = (f32)__fabs(sp6C);
					var_f4  = var_f3;
					temp_f0 = (f32)__fabs(sp70);
					M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
					if (temp_f1 == temp_f2) {
						M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
						if (temp_f1 == temp_f0) {
							var_f3 = lbl_8043018C;
						} else {
							var_f4 = lbl_8043018C;
						}
					} else {
						M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
						if (temp_f2 == temp_f0) {
							var_f6 = lbl_8043018C;
						} else {
							var_f4 = lbl_8043018C;
						}
					}
					temp_f4   = (var_f4 * sp68) - (var_f3 * sp70);
					temp_f6   = (var_f6 * sp70) - (var_f4 * sp6C);
					temp_f3   = (var_f3 * sp6C) - (var_f6 * sp68);
					sp4C      = temp_f4;
					sp48      = temp_f6;
					temp_f2_2 = (sp6C * temp_f3) - (sp70 * temp_f4);
					sp50      = temp_f3;
					temp_f1_2 = (sp70 * temp_f6) - (sp68 * temp_f3);
					sp58      = temp_f2_2;
					sp5C      = temp_f1_2;
					sp60      = (sp68 * temp_f4) - (sp6C * temp_f6);
					temp_r6   = M2C_FIELD(var_r19_2, s32*, 0);
					sp78      = temp_r6;
					sp7C      = M2C_FIELD(var_r19_2, s32*, 4);
					sp80      = M2C_FIELD(var_r19_2, s32*, 8);
					fn_8019ECCC(temp_r28, &sp48, 0, temp_r6, temp_f1_2, temp_f2_2, temp_f3, temp_f4,
					    sp68, temp_f6, sp6C, sp70);
					M2C_FIELD(temp_r24, s32*, 0xA8) = fn_8019E8EC(temp_r28);
					temp_f31                        = M2C_FIELD(temp_r24, f32*, 8);
					temp_f30                        = M2C_FIELD(temp_r24, f32*, 0x40);
					M2C_FIELD(temp_r24, f32*, 8)    = (f32)M2C_FIELD(temp_r21, f32*, 4);
					M2C_FIELD(temp_r24, f32*, 0x40) = (f32)M2C_FIELD(temp_r21, f32*, 4);
					M2C_FIELD(temp_r31, s32*, 4)    = (s32)(M2C_FIELD(temp_r31, s32*, 4) | 8);
					M2C_FIELD(temp_r31, s32*, 4)    = (s32)(M2C_FIELD(temp_r31, s32*, 4) | 0x100);
					M2C_FIELD(temp_r31, s32*, 4) = (s32)(M2C_FIELD(temp_r31, s32*, 4) & 0xFFFFFFDF);
					fn_802332AC(temp_r30, temp_r31, arg2);
					M2C_FIELD(temp_r31, s32*, 4) = (s32)(M2C_FIELD(temp_r31, s32*, 4) & 0xFFFFFFF7);
					M2C_FIELD(temp_r31, s32*, 4) = (s32)(M2C_FIELD(temp_r31, s32*, 4) & 0xFFFFFEFF);
					M2C_FIELD(temp_r31, s32*, 4) = (s32)(M2C_FIELD(temp_r31, s32*, 4) | 0x20);
					M2C_FIELD(temp_r24, f32*, 8) = temp_f31;
					M2C_FIELD(temp_r24, f32*, 0x40) = temp_f30;
					M2C_FIELD(temp_r20, f32*, 0)
					    = (f32)(M2C_FIELD(temp_r20, f32*, 0) + M2C_FIELD(temp_r20, f32*, 4));
				}
			}
			var_r22 += temp_r18;
			var_r19_2 += var_r17;
			goto loop_24;
		}
		fn_8019ECCC(temp_r28, &sp8, 0);
		fn_8019E880(temp_r28);
		fn_8019E8EC(temp_r28);
		fn_80234058(arg0);
	}
	return arg1;
}

u8* fn_8022E46C(void* arg0, u8* arg1)
{
	f32 temp_f1;
	f32 temp_f4;
	s32 temp_r12;
	s32 temp_r5;
	s32 temp_r7;
	s32 var_ctr;
	u32 temp_r3;
	u32 var_r10;
	u8* temp_r5_2;
	u8* temp_r8;
	u8* var_r11;
	u8* var_r31;

	var_r31 = NULL;
	fn_8022D440(arg1);
	if ((s32)lbl_8042ABB0[0xC] >= 0) {
		var_r31 = arg1 + lbl_8042ABB0[0xC];
	}
	temp_r8 = M2C_FIELD(arg1, u8**, 0x20);
	var_r10 = *(arg1 + lbl_8042ABB0[5]);
	if (temp_r8 != NULL) {
		temp_r7 = M2C_FIELD(temp_r8, s32*, 0x10);
		if (temp_r7 != -1) {
			temp_r12 = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x18), s32*, 0xC);
			if (temp_r7 >= 0) {
				temp_r5 = M2C_FIELD(temp_r8, s32*, 8) - temp_r7;
				var_r11 = temp_r8 + M2C_FIELD(temp_r8, s32*, 0x14) + (temp_r7 * temp_r12);
				var_ctr = temp_r5;
				if (temp_r5 > 0) {
					do {
						temp_r3   = (var_r10 * 0x0BB38435) + 0x3619636B;
						temp_r5_2 = var_r11 + lbl_8042ABB0[0x1A];
						temp_f1   = *(var_r11 + (lbl_8042ABB0[0x13] + 4));
						var_r11 += temp_r12;
						temp_f4 = (f32)temp_r3;
						var_r10 = (temp_r3 * 0x0BB38435) + 0x3619636B;
						M2C_FIELD(temp_r5_2, f32*, 0)
						    = (f32)((((lbl_80430190 * (lbl_80430194 * temp_f4)) - lbl_8043018C)
						                * M2C_FIELD(var_r31, f32*, 4))
						        + (temp_f1 + M2C_FIELD(var_r31, f32*, 0)));
						M2C_FIELD(temp_r5_2, f32*, 4)
						    = (f32)((((lbl_80430190 * (lbl_80430194 * (f32)var_r10)) - lbl_8043018C)
						                * M2C_FIELD(var_r31, f32*, 0xC))
						        + M2C_FIELD(var_r31, f32*, 8));
						var_ctr -= 1;
					} while (var_ctr != 0);
				}
				*(arg1 + lbl_8042ABB0[5]) = var_r10;
			}
		}
	}
	return arg1;
}

u8* fn_8022E5D4(void* arg0, u8* arg1, u8* arg2)
{
	s32 temp_r31;
	s32 temp_r3;
	u32* temp_r5;
	u8* temp_r29;

	temp_r5  = M2C_FIELD(arg2, u32**, 0xC);
	temp_r31 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u32*, 0x10), 0x01000001);
	temp_r3  = fn_8023506C(temp_r5[4], 0x01000001, temp_r5);
	if ((temp_r31 >= 0) && (temp_r3 >= 0)) {
		temp_r29 = arg2 + temp_r3;
		memcpy(temp_r29, arg1 + temp_r31, 0x14);
		M2C_FIELD(temp_r29, s32*, 0x10) = 0;
	}
	return arg2;
}

u8* fn_8022E674(void* arg0, u8* arg1, s32* arg2)
{
	s32 var_r0;
	u32* temp_r6;

	temp_r6 = M2C_FIELD(arg1, u32**, 0xC);
	var_r0  = 0;
	if (fn_8023506C(temp_r6[4], 0x01000001, temp_r6) > 0) {
		var_r0 = 0x10;
	}
	*arg2 = var_r0;
	return arg1;
}

u8* fn_8022E6D4(void* arg0, u8* arg1, s32 arg2)
{
	s32 temp_r3;
	u8* temp_r30;

	temp_r3 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u32*, 0x10), 0x01000001);
	if (temp_r3 >= 0) {
		temp_r30 = arg1 + temp_r3;
		fn_801937A0(arg2, temp_r30, 4);
		fn_801937A0(arg2, temp_r30 + 4, 4);
		fn_801937A0(arg2, temp_r30 + 8, 4);
		fn_801937A0(arg2, temp_r30 + 0xC, 4);
	}
	return arg1;
}

u8* fn_8022E774(void* arg0, u8* arg1, s32 arg2)
{
	s32 temp_r3;
	u8* temp_r30;

	temp_r3 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u32*, 0x10), 0x01000001);
	if (temp_r3 >= 0) {
		temp_r30 = arg1 + temp_r3;
		fn_8019336C(arg2, temp_r30, 4);
		fn_8019336C(arg2, temp_r30 + 4, 4);
		fn_8019336C(arg2, temp_r30 + 8, 4);
		fn_8019336C(arg2, temp_r30 + 0xC, 4);
	}
	return arg1;
}

u8* fn_8022E814(u8* arg0, u8* arg1, f32* arg2)
{
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f31;
	s32 temp_r5;
	s32 var_ctr;
	u32* temp_r4;
	u32* temp_r4_3;
	u32* temp_r5_2;
	u32 temp_r7;
	u32 temp_r8;
	u32 temp_r8_3;
	u8* temp_r4_2;
	u8* temp_r5_3;
	u8* temp_r7_2;
	u8* temp_r7_3;
	u8* temp_r7_4;
	u8* temp_r8_2;
	u8* temp_r8_4;
	u8* temp_r9;
	u8* var_r29;
	u8* var_r30;
	u8* var_r31;
	u8* var_r6;

	temp_f31 = *arg2;
	var_r31  = NULL;
	var_r30  = NULL;
	var_r29  = NULL;
	fn_8022D440(arg0);
	if ((s32)lbl_8042ABB0[0xE] >= 0) {
		var_r31 = arg0 + lbl_8042ABB0[0xE];
	}
	if ((s32)lbl_8042ABB0[0xF] >= 0) {
		var_r30 = arg0 + lbl_8042ABB0[0xF];
	}
	if ((s32)lbl_8042ABB0[0x11] >= 0) {
		var_r29 = arg0 + lbl_8042ABB0[0x11];
	}
	temp_r5 = M2C_FIELD(arg1, s32*, 8);
	var_r6  = arg1 + M2C_FIELD(arg1, s32*, 0x14);
	var_ctr = temp_r5;
	if (temp_r5 > 0) {
		do {
			temp_f1 = M2C_FIELD(var_r6, f32*, 4);
			if (temp_f1 < M2C_FIELD(var_r6, f32*, 8)) {
				temp_f1_2 = temp_f1 + temp_f31;
				if ((s32)lbl_8042ABB0[0x1B] >= 0) {
					temp_r4 = (u32*)(var_r6 + lbl_8042ABB0[0x1B]);
					temp_r8 = *temp_r4;
					if (temp_r8 < (u32)M2C_FIELD(var_r31, u32*, 0)) {
						M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
						if ((temp_f1_2 == M2C_FIELD((temp_r4 + (temp_r8 * 4)), f32*, 4))
						    && ((s32)lbl_8042ABB0[0x14] >= 0)) {
							temp_r9                        = var_r6 + lbl_8042ABB0[0x14];
							*(M2C_BLOCK16*)(temp_r9)       = *(M2C_BLOCK16*)(temp_r4
							    + (M2C_FIELD(var_r31, s32*, 0xC) + (temp_r8 * 0x10)));
							temp_r8_2                      = (u8*)(temp_r4
							    + (M2C_FIELD(var_r31, s32*, 0x10) + (*temp_r4 * 0x10)));
							M2C_FIELD(temp_r9, s32*, 0x10) = (s32)M2C_FIELD(temp_r8_2, s32*, 0);
							M2C_FIELD(temp_r9, s32*, 0x14) = (s32)M2C_FIELD(temp_r8_2, s32*, 4);
							M2C_FIELD(temp_r9, s32*, 0x18) = (s32)M2C_FIELD(temp_r8_2, s32*, 8);
							M2C_FIELD(temp_r9, s32*, 0x1C) = (s32)M2C_FIELD(temp_r8_2, s32*, 0xC);
							*temp_r4 += 1;
						}
					}
				}
				if ((s32)lbl_8042ABB0[0x1C] >= 0) {
					temp_r5_2 = (u32*)(var_r6 + lbl_8042ABB0[0x1C]);
					temp_r7   = *temp_r5_2;
					if (temp_r7 < (u32)M2C_FIELD(var_r30, u32*, 0)) {
						M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
						if ((temp_f1_2 == M2C_FIELD((temp_r5_2 + (temp_r7 * 4)), f32*, 4))
						    && ((s32)lbl_8042ABB0[0x15] >= 0)) {
							temp_r4_2                        = var_r6 + lbl_8042ABB0[0x15];
							*(M2C_BLOCK8*)(temp_r4_2)        = *(M2C_BLOCK8*)(temp_r5_2
							    + (M2C_FIELD(var_r30, s32*, 0xC) + (temp_r7 * 8)));
							temp_r7_2                        = (u8*)(temp_r5_2
							    + (M2C_FIELD(var_r30, s32*, 0x10) + (*temp_r5_2 * 8)));
							M2C_FIELD(temp_r4_2, s32*, 0x10) = (s32)M2C_FIELD(temp_r7_2, s32*, 0);
							M2C_FIELD(temp_r4_2, s32*, 0x14) = (s32)M2C_FIELD(temp_r7_2, s32*, 4);
							temp_r7_3                        = (u8*)(temp_r5_2
							    + (M2C_FIELD(var_r30, s32*, 0x14) + (*temp_r5_2 * 8)));
							M2C_FIELD(temp_r4_2, s32*, 8)    = (s32)M2C_FIELD(temp_r7_3, s32*, 0);
							M2C_FIELD(temp_r4_2, s32*, 0xC)  = (s32)M2C_FIELD(temp_r7_3, s32*, 4);
							temp_r7_4                        = (u8*)(temp_r5_2
							    + (M2C_FIELD(var_r30, s32*, 0x18) + (*temp_r5_2 * 8)));
							M2C_FIELD(temp_r4_2, s32*, 0x18) = (s32)M2C_FIELD(temp_r7_4, s32*, 0);
							M2C_FIELD(temp_r4_2, s32*, 0x1C) = (s32)M2C_FIELD(temp_r7_4, s32*, 4);
							*temp_r5_2 += 1;
						}
					}
				}
				if ((s32)lbl_8042ABB0[0x1E] >= 0) {
					temp_r4_3 = (u32*)(var_r6 + lbl_8042ABB0[0x1E]);
					temp_r8_3 = *temp_r4_3;
					if (temp_r8_3 < (u32)M2C_FIELD(var_r29, u32*, 0)) {
						M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
						if ((temp_f1_2 == M2C_FIELD((temp_r4_3 + (temp_r8_3 * 4)), f32*, 4))
						    && ((s32)lbl_8042ABB0[0x16] >= 0)) {
							temp_r8_4                       = var_r6 + lbl_8042ABB0[0x16];
							*(M2C_BLOCK8*)(temp_r8_4)       = *(M2C_BLOCK8*)(temp_r4_3
							    + (M2C_FIELD(var_r29, s32*, 0xC) + (temp_r8_3 * 8)));
							temp_r5_3                       = (u8*)(temp_r4_3
							    + (M2C_FIELD(var_r29, s32*, 0x10) + (*temp_r4_3 * 8)));
							M2C_FIELD(temp_r8_4, s32*, 8)   = (s32)M2C_FIELD(temp_r5_3, s32*, 0);
							M2C_FIELD(temp_r8_4, s32*, 0xC) = (s32)M2C_FIELD(temp_r5_3, s32*, 4);
							*temp_r4_3 += 1;
						}
					}
				}
			}
			var_r6 += M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), s32*, 0xC);
			var_ctr -= 1;
		} while (var_ctr != 0);
	}
	return arg1;
}

u8* fn_8022EB2C(void* arg0, u8* arg1)
{
	s32 spB8;
	s32 spB4;
	s32 spB0;
	s32 spAC;
	u8* spA8;
	f32 sp7C;
	f32 sp78;
	f32 sp74;
	f32 sp70;
	f32 sp6C;
	f32 sp68;
	f32 sp64;
	f32 sp60;
	f32 sp5C;
	f32 sp58;
	f32 sp54;
	f32 sp50;
	f32 sp4C;
	f32 sp48;
	f32 sp44;
	f32 sp40;
	f32 sp3C;
	f32 sp38;
	f32 sp34;
	f32 sp30;
	f32 sp2C;
	f32 sp28;
	f32 sp24;
	f32 sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32* temp_r12;
	f32* temp_r24;
	f32* temp_r9_2;
	f32* var_r4;
	f32* var_r4_2;
	f32* var_r9_2;
	f32 temp_f0;
	f32 temp_f0_2;
	f32 temp_f0_3;
	f32 temp_f0_4;
	f32 temp_f10;
	f32 temp_f10_2;
	f32 temp_f10_3;
	f32 temp_f11;
	f32 temp_f11_2;
	f32 temp_f11_3;
	f32 temp_f13;
	f32 temp_f13_2;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f1_4;
	f32 temp_f24;
	f32 temp_f24_2;
	f32 temp_f24_3;
	f32 temp_f24_4;
	f32 temp_f24_5;
	f32 temp_f25;
	f32 temp_f25_2;
	f32 temp_f26;
	f32 temp_f26_2;
	f32 temp_f27;
	f32 temp_f28;
	f32 temp_f29;
	f32 temp_f29_2;
	f32 temp_f2;
	f32 temp_f2_2;
	f32 temp_f2_3;
	f32 temp_f2_4;
	f32 temp_f2_5;
	f32 temp_f2_6;
	f32 temp_f31;
	f32 temp_f3;
	f32 temp_f4;
	f32 temp_f4_2;
	f32 temp_f5;
	f32 temp_f5_2;
	f32 temp_f5_3;
	f32 temp_f6;
	f32 temp_f6_2;
	f32 temp_f6_3;
	f32 temp_f7;
	f32 temp_f7_2;
	f32 temp_f8;
	f32 temp_f8_2;
	f32 temp_f8_3;
	f32 temp_f8_4;
	f32 temp_f9;
	f32 temp_f9_2;
	f32 temp_f9_3;
	f32 temp_f9_4;
	f32 var_f10;
	f32 var_f12;
	f32 var_f12_2;
	f32 var_f13;
	f32 var_f25;
	f32 var_f26;
	f32 var_f2;
	f32 var_f8;
	f32 var_f9;
	s32* temp_r11;
	s32* temp_r12_2;
	s32* temp_r19_2;
	s32* var_r28;
	s32* var_r29;
	s32* var_r30;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r0_3;
	s32 temp_r0_4;
	s32 temp_r18_5;
	s32 temp_r22;
	s32 temp_r3;
	s32 temp_r3_2;
	s32 temp_r3_3;
	s32 temp_r7;
	s32 temp_r9;
	s32 var_ctr;
	s32 var_r10_2;
	s32 var_r14;
	s32 var_r23;
	s32 var_r31;
	s32 var_r9;
	u32 temp_r17_2;
	u32 temp_r18;
	u32 temp_r18_2;
	u32 temp_r18_3;
	u32 temp_r19;
	u32 temp_r19_3;
	u32 temp_r3_6;
	u32 temp_r4;
	u32 temp_r4_3;
	u32 temp_r5;
	u32 temp_r5_10;
	u32 temp_r5_2;
	u32 temp_r5_3;
	u32 temp_r5_4;
	u32 temp_r5_5;
	u32 temp_r5_6;
	u32 temp_r5_7;
	u32 temp_r5_8;
	u32 temp_r6;
	u32 temp_r6_3;
	u32 var_r25;
	u8* temp_r10;
	u8* temp_r10_2;
	u8* temp_r11_2;
	u8* temp_r15;
	u8* temp_r15_2;
	u8* temp_r15_3;
	u8* temp_r16;
	u8* temp_r16_2;
	u8* temp_r16_3;
	u8* temp_r17;
	u8* temp_r18_4;
	u8* temp_r18_6;
	u8* temp_r20;
	u8* temp_r3_4;
	u8* temp_r3_5;
	u8* temp_r3_7;
	u8* temp_r3_8;
	u8* temp_r4_2;
	u8* temp_r4_4;
	u8* temp_r4_5;
	u8* temp_r4_6;
	u8* temp_r4_7;
	u8* temp_r5_9;
	u8* temp_r6_2;
	u8* temp_r7_2;
	u8* temp_r7_3;
	u8* temp_r7_4;
	u8* temp_r7_5;
	u8* var_r10;
	u8* var_r11;
	u8* var_r12;
	u8* var_r15;
	u8* var_r21;
	u8* var_r26;
	u8* var_r5;
	u8* var_r5_2;
	u8* var_r6;
	u8* var_r6_2;

	spB8    = 0;
	var_r31 = 0;
	spB4    = 0;
	var_r14 = 0;
	var_r30 = NULL;
	spB0    = 0;
	var_r29 = NULL;
	var_r28 = NULL;
	spAC    = 0;
	var_r15 = NULL;
	fn_8022D440(arg1);
	spA8 = arg1 + lbl_8042ABB0[5];
	if ((s32)lbl_8042ABB0[0xE] >= 0) {
		var_r30 = (s32*)(arg1 + lbl_8042ABB0[0xE]);
		temp_r3 = *var_r30;
		spB8    = temp_r3 * 4;
		spB4    = temp_r3 * 0x10;
	}
	if ((s32)lbl_8042ABB0[0xF] >= 0) {
		var_r29   = (s32*)(arg1 + lbl_8042ABB0[0xF]);
		temp_r3_2 = *var_r29;
		var_r31   = temp_r3_2 * 8;
		spB0      = temp_r3_2 * 4;
	}
	if ((s32)lbl_8042ABB0[0x11] >= 0) {
		var_r28   = (s32*)(arg1 + lbl_8042ABB0[0x11]);
		temp_r3_3 = *var_r28;
		var_r14   = temp_r3_3 * 8;
		spAC      = temp_r3_3 * 4;
	}
	M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
	if (M2C_FIELD(spA8, f32*, 8) == M2C_FIELD(spA8, f32*, 0x40)) {
		temp_r10 = M2C_FIELD(arg1, u8**, 0x20);
		if (temp_r10 != NULL) {
			temp_r7 = M2C_FIELD(temp_r10, s32*, 0x10);
			if (temp_r7 != -1) {
				if (temp_r7 >= 0) {
					temp_r22 = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x18), s32*, 0xC);
					temp_r9  = M2C_FIELD(temp_r10, s32*, 8) - temp_r7;
					var_r21  = temp_r10 + (M2C_FIELD(temp_r10, s32*, 0x14) + (temp_r7 * temp_r22));
					var_ctr  = temp_r9;
					var_r25  = (M2C_FIELD(spA8, u32*, 0) * 0x0BB38435) + 0x3619636B;
					if (temp_r9 > 0) {
						do {
							if (lbl_804301A0 == M2C_FIELD(var_r21, f32*, 4)) {
								if ((s32)lbl_8042ABB0[0x1B] >= 0) {
									temp_r7_2  = M2C_FIELD(var_r30, u8**, 4);
									temp_r11   = (s32*)(var_r21 + lbl_8042ABB0[0x1B]);
									temp_r12   = (f32*)(temp_r11 + 4);
									temp_r10_2 = var_r21 + lbl_8042ABB0[0x14];
									temp_r6    = (var_r25 * 0x0BB38435) + 0x3619636B;
									temp_r15   = (u8*)(temp_r12 + spB8);
									temp_r16   = temp_r15 + spB4;
									temp_r5    = (temp_r6 * 0x0BB38435) + 0x3619636B;
									temp_r5_2  = (temp_r5 * 0x0BB38435) + 0x3619636B;
									temp_r4    = (temp_r5_2 * 0x0BB38435) + 0x3619636B;
									temp_f4    = (lbl_804301A4 * (lbl_804301A8 * (f32)temp_r6))
									    - lbl_804301AC;
									temp_f11 = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r5))
									                - lbl_804301AC)
									               * M2C_FIELD(temp_r7_2, f32*, 0x18))
									    + M2C_FIELD(temp_r7_2, f32*, 8);
									temp_f10 = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r5_2))
									                - lbl_804301AC)
									               * M2C_FIELD(temp_r7_2, f32*, 0x1C))
									    + M2C_FIELD(temp_r7_2, f32*, 0xC);
									temp_f9 = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r4))
									               - lbl_804301AC)
									              * M2C_FIELD(temp_r7_2, f32*, 0x20))
									    + M2C_FIELD(temp_r7_2, f32*, 0x10);
									var_r25 = (temp_r4 * 0x0BB38435) + 0x3619636B;
									sp60    = temp_f11;
									var_f12 = (temp_f4 * M2C_FIELD(temp_r7_2, f32*, 4))
									    + M2C_FIELD(temp_r7_2, f32*, 0);
									sp64       = temp_f10;
									sp68       = temp_f9;
									temp_f11_2 = var_f12;
									var_r4     = temp_r12;
									var_r5     = temp_r15;
									var_r6     = temp_r16;
									var_r9     = 0;
									sp70       = sp60;
									sp74       = sp64;
									sp78       = sp68;
									sp6C       = (((lbl_804301A4 * (lbl_804301A8 * (f32)var_r25))
									                  - lbl_804301AC)
									                 * M2C_FIELD(temp_r7_2, f32*, 0x24))
									    + M2C_FIELD(temp_r7_2, f32*, 0x14);
									sp7C = sp6C;
								loop_18:
									if (var_r9 < (s32)(M2C_FIELD(var_r30, s32*, 0) - 1)) {
										temp_r19 = (var_r25 * 0x0BB38435) + 0x3619636B;
										temp_r7_3
										    = M2C_FIELD(var_r30, u8**, 4) + ((var_r9 + 1) * 0x28);
										*var_r4  = var_f12 * M2C_FIELD(var_r21, f32*, 8);
										temp_f13 = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r19))
										                - lbl_804301AC)
										               * M2C_FIELD(temp_r7_3, f32*, 4))
										    + M2C_FIELD(temp_r7_3, f32*, 0);
										temp_f1 = temp_f13 - var_f12;
										if (temp_f1 > (f32)lbl_804301B0) {
											var_f10 = lbl_804301AC / temp_f1;
										} else {
											var_f10 = lbl_804301A0;
										}
										var_r4 += 4;
										var_r9 += 1;
										temp_r18   = (temp_r19 * 0x0BB38435) + 0x3619636B;
										temp_r18_2 = (temp_r18 * 0x0BB38435) + 0x3619636B;
										temp_r18_3 = (temp_r18_2 * 0x0BB38435) + 0x3619636B;
										temp_f1_2
										    = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r18))
										           - lbl_804301AC)
										          * M2C_FIELD(temp_r7_3, f32*, 0x18))
										    + M2C_FIELD(temp_r7_3, f32*, 8);
										var_r25   = (temp_r18_3 * 0x0BB38435) + 0x3619636B;
										temp_f9_2 = var_f10 * (temp_f1_2 - sp60);
										sp50      = temp_f1_2;
										temp_f0
										    = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r18_2))
										           - lbl_804301AC)
										          * M2C_FIELD(temp_r7_3, f32*, 0x1C))
										    + M2C_FIELD(temp_r7_3, f32*, 0xC);
										temp_f31
										    = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r18_3))
										           - lbl_804301AC)
										          * M2C_FIELD(temp_r7_3, f32*, 0x20))
										    + M2C_FIELD(temp_r7_3, f32*, 0x10);
										M2C_FIELD(var_r5, f32*, 0)
										    = (f32) - ((temp_f9_2 * var_f12) - sp60);
										temp_f28 = (((lbl_804301A4 * (lbl_804301A8 * (f32)var_r25))
										                - lbl_804301AC)
										               * M2C_FIELD(temp_r7_3, f32*, 0x24))
										    + M2C_FIELD(temp_r7_3, f32*, 0x14);
										sp54     = temp_f0;
										temp_f24 = var_f10 * (temp_f0 - sp64);
										temp_f29 = var_f10 * (temp_f31 - sp68);
										sp58     = temp_f31;
										sp5C     = temp_f28;
										M2C_FIELD(var_r5, f32*, 4)
										    = (f32) - ((temp_f24 * var_f12) - sp64);
										temp_f2 = var_f10 * (temp_f28 - sp6C);
										M2C_FIELD(var_r5, f32*, 8)
										    = (f32) - ((temp_f29 * var_f12) - sp68);
										temp_f1_3 = -((temp_f2 * var_f12) - sp6C);
										var_f12   = temp_f13;
										sp60      = sp50;
										M2C_FIELD(var_r5, f32*, 0xC) = temp_f1_3;
										var_r5 += 0x10;
										M2C_FIELD(var_r6, f32*, 0)   = temp_f9_2;
										M2C_FIELD(var_r6, f32*, 4)   = temp_f24;
										M2C_FIELD(var_r6, f32*, 8)   = temp_f29;
										M2C_FIELD(var_r6, f32*, 0xC) = temp_f2;
										var_r6 += 0x10;
										sp64 = sp54;
										sp68 = sp58;
										sp6C = sp5C;
										goto loop_18;
									}
									*(temp_r12 + (var_r9 * 4))
									    = var_f12 * M2C_FIELD(var_r21, f32*, 8);
									temp_f2_2 = lbl_804301AC - var_f12;
									if (temp_f2_2 > (f32)lbl_804301B0) {
										var_f25 = lbl_804301AC / temp_f2_2;
									} else {
										var_f25 = lbl_804301A0;
									}
									temp_r0   = var_r9 * 0x10;
									temp_r3_4 = temp_r15 + temp_r0;
									temp_r4_2 = temp_r16 + temp_r0;
									temp_f7   = var_f25
									    * ((M2C_FIELD(temp_r10_2, f32*, 0)
									           + M2C_FIELD(temp_r10_2, f32*, 0x10))
									        - sp60);
									temp_f26 = var_f25
									    * ((M2C_FIELD(temp_r10_2, f32*, 4)
									           + M2C_FIELD(temp_r10_2, f32*, 0x14))
									        - sp64);
									temp_f8 = var_f25
									    * ((M2C_FIELD(temp_r10_2, f32*, 8)
									           + M2C_FIELD(temp_r10_2, f32*, 0x18))
									        - sp68);
									temp_f24_2 = var_f25
									    * ((M2C_FIELD(temp_r10_2, f32*, 0xC)
									           + M2C_FIELD(temp_r10_2, f32*, 0x1C))
									        - sp6C);
									M2C_FIELD(temp_r3_4, f32*, 0)
									    = (f32) - ((temp_f7 * var_f12) - sp60);
									M2C_FIELD(temp_r3_4, f32*, 4)
									    = (f32) - ((temp_f26 * var_f12) - sp64);
									M2C_FIELD(temp_r3_4, f32*, 8)
									    = (f32) - ((temp_f8 * var_f12) - sp68);
									M2C_FIELD(temp_r3_4, f32*, 0xC)
									    = (f32) - ((temp_f24_2 * var_f12) - sp6C);
									M2C_FIELD(temp_r4_2, f32*, 0)   = temp_f7;
									M2C_FIELD(temp_r4_2, f32*, 4)   = temp_f26;
									M2C_FIELD(temp_r4_2, f32*, 8)   = temp_f8;
									M2C_FIELD(temp_r4_2, f32*, 0xC) = temp_f24_2;
									*temp_r11                       = 0;
									temp_f5                         = lbl_804301AC / temp_f11_2;
									M2C_FIELD(temp_r10_2, f32*, 0x10)
									    = (f32)(temp_f5 * (sp70 - M2C_FIELD(temp_r10_2, f32*, 0)));
									M2C_FIELD(temp_r10_2, f32*, 0x14)
									    = (f32)(temp_f5 * (sp74 - M2C_FIELD(temp_r10_2, f32*, 4)));
									M2C_FIELD(temp_r10_2, f32*, 0x18)
									    = (f32)(temp_f5 * (sp78 - M2C_FIELD(temp_r10_2, f32*, 8)));
									M2C_FIELD(temp_r10_2, f32*, 0x1C) = (f32)(temp_f5
									    * (sp7C - M2C_FIELD(temp_r10_2, f32*, 0xC)));
								}
								if ((s32)lbl_8042ABB0[0x1C] >= 0) {
									temp_r3_5  = M2C_FIELD(var_r29, u8**, 4);
									temp_r19_2 = (s32*)(var_r21 + lbl_8042ABB0[0x1C]);
									temp_r24   = (f32*)(temp_r19_2 + 4);
									temp_r20   = var_r21 + lbl_8042ABB0[0x15];
									temp_r5_3  = (var_r25 * 0x0BB38435) + 0x3619636B;
									temp_r18_4 = (u8*)(temp_r24 + spB0);
									temp_r17   = temp_r18_4 + var_r31;
									temp_r5_4  = (temp_r5_3 * 0x0BB38435) + 0x3619636B;
									temp_r16_2 = temp_r17 + var_r31;
									temp_r15_2 = temp_r16_2 + var_r31;
									temp_r5_5  = (temp_r5_4 * 0x0BB38435) + 0x3619636B;
									temp_r4_3  = (temp_r5_5 * 0x0BB38435) + 0x3619636B;
									sp40       = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r5_4))
									                  - lbl_804301AC)
									                 * M2C_FIELD(temp_r3_5, f32*, 0x10))
									    + M2C_FIELD(temp_r3_5, f32*, 8);
									sp44 = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r5_5))
									            - lbl_804301AC)
									           * M2C_FIELD(temp_r3_5, f32*, 0x14))
									    + M2C_FIELD(temp_r3_5, f32*, 0xC);
									var_f9 = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r5_3))
									              - lbl_804301AC)
									             * M2C_FIELD(temp_r3_5, f32*, 4))
									    + M2C_FIELD(temp_r3_5, f32*, 0);
									sp28 = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r4_3))
									            - lbl_804301AC)
									           * M2C_FIELD(temp_r3_5, f32*, 0x20))
									    + M2C_FIELD(temp_r3_5, f32*, 0x18);
									temp_f10_2 = var_f9;
									var_r9_2   = temp_r24;
									var_r25    = (temp_r4_3 * 0x0BB38435) + 0x3619636B;
									var_r10    = temp_r18_4;
									var_r11    = temp_r16_2;
									var_r12    = temp_r17;
									sp48       = sp40;
									var_r26    = temp_r15_2;
									var_r23    = 0;
									sp4C       = sp44;
									sp30       = sp28;
									sp2C       = (((lbl_804301A4 * (lbl_804301A8 * (f32)var_r25))
									                  - lbl_804301AC)
									                 * M2C_FIELD(temp_r3_5, f32*, 0x24))
									    + M2C_FIELD(temp_r3_5, f32*, 0x1C);
									sp34 = sp2C;
								loop_29:
									if (var_r23 < (s32)(M2C_FIELD(var_r29, s32*, 0) - 1)) {
										temp_r3_6 = (var_r25 * 0x0BB38435) + 0x3619636B;
										temp_r0_2 = (var_r23 + 1) * 0x28;
										temp_r4_4 = M2C_FIELD(var_r29, u8**, 4) + temp_r0_2;
										*var_r9_2 = var_f9 * M2C_FIELD(var_r21, f32*, 8);
										temp_f11_3
										    = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r3_6))
										           - lbl_804301AC)
										          * M2C_FIELD(temp_r4_4, f32*, 4))
										    + M2C_FIELD(temp_r4_4, f32*, 0);
										temp_f1_4 = temp_f11_3 - var_f9;
										if (temp_f1_4 > (f32)lbl_804301B0) {
											var_f12_2 = lbl_804301AC / temp_f1_4;
										} else {
											var_f12_2 = lbl_804301A0;
										}
										var_r9_2 += 4;
										temp_r4_5 = M2C_FIELD(var_r29, u8**, 4) + temp_r0_2;
										temp_r5_6 = (temp_r3_6 * 0x0BB38435) + 0x3619636B;
										var_r23 += 1;
										temp_r5_7 = (temp_r5_6 * 0x0BB38435) + 0x3619636B;
										temp_r5_8 = (temp_r5_7 * 0x0BB38435) + 0x3619636B;
										temp_f0_2
										    = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r5_6))
										           - lbl_804301AC)
										          * M2C_FIELD(temp_r4_5, f32*, 0x10))
										    + M2C_FIELD(temp_r4_5, f32*, 8);
										var_r25 = (temp_r5_8 * 0x0BB38435) + 0x3619636B;
										temp_f25
										    = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r5_7))
										           - lbl_804301AC)
										          * M2C_FIELD(temp_r4_5, f32*, 0x14))
										    + M2C_FIELD(temp_r4_5, f32*, 0xC);
										temp_f26_2
										    = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r5_8))
										           - lbl_804301AC)
										          * M2C_FIELD(temp_r4_5, f32*, 0x20))
										    + M2C_FIELD(temp_r4_5, f32*, 0x18);
										temp_f24_3 = var_f12_2 * (temp_f0_2 - sp40);
										sp38       = temp_f0_2;
										temp_f27   = var_f12_2 * (temp_f25 - sp44);
										temp_f29_2
										    = (((lbl_804301A4 * (lbl_804301A8 * (f32)var_r25))
										           - lbl_804301AC)
										          * M2C_FIELD(temp_r4_5, f32*, 0x24))
										    + M2C_FIELD(temp_r4_5, f32*, 0x1C);
										sp3C = temp_f25;
										sp20 = temp_f26_2;
										M2C_FIELD(var_r10, f32*, 0)
										    = (f32) - ((temp_f24_3 * var_f9) - sp40);
										temp_f8_2 = var_f12_2 * (temp_f26_2 - sp28);
										sp24      = temp_f29_2;
										temp_f2_3 = var_f12_2 * (temp_f29_2 - sp2C);
										M2C_FIELD(var_r10, f32*, 4)
										    = (f32) - ((temp_f27 * var_f9) - sp44);
										var_r10 += 8;
										temp_f0_3 = -((temp_f2_3 * var_f9) - sp2C);
										M2C_FIELD(var_r11, f32*, 0)
										    = (f32) - ((temp_f8_2 * var_f9) - sp28);
										var_f9                      = temp_f11_3;
										sp40                        = sp38;
										M2C_FIELD(var_r11, f32*, 4) = temp_f0_3;
										var_r11 += 8;
										M2C_FIELD(var_r12, f32*, 0) = temp_f24_3;
										M2C_FIELD(var_r12, f32*, 4) = temp_f27;
										var_r12 += 8;
										M2C_FIELD(var_r26, f32*, 0) = temp_f8_2;
										M2C_FIELD(var_r26, f32*, 4) = temp_f2_3;
										var_r26 += 8;
										sp44 = sp3C;
										sp28 = sp20;
										sp2C = sp24;
										goto loop_29;
									}
									*(temp_r24 + (var_r23 * 4))
									    = var_f9 * M2C_FIELD(var_r21, f32*, 8);
									temp_f2_4 = lbl_804301AC - var_f9;
									if (temp_f2_4 > (f32)lbl_804301B0) {
										var_f13 = lbl_804301AC / temp_f2_4;
									} else {
										var_f13 = lbl_804301A0;
									}
									temp_r0_3  = var_r23 * 8;
									temp_r3_7  = temp_r18_4 + temp_r0_3;
									temp_r4_6  = temp_r16_2 + temp_r0_3;
									temp_f24_4 = var_f13
									    * ((M2C_FIELD(temp_r20, f32*, 0)
									           + M2C_FIELD(temp_r20, f32*, 0x10))
									        - sp40);
									temp_r5_9  = temp_r17 + temp_r0_3;
									temp_f25_2 = var_f13
									    * ((M2C_FIELD(temp_r20, f32*, 4)
									           + M2C_FIELD(temp_r20, f32*, 0x14))
									        - sp44);
									temp_r6_2 = temp_r15_2 + temp_r0_3;
									temp_f7_2 = var_f13
									    * ((M2C_FIELD(temp_r20, f32*, 8)
									           + M2C_FIELD(temp_r20, f32*, 0x18))
									        - sp28);
									temp_f13_2 = var_f13
									    * ((M2C_FIELD(temp_r20, f32*, 0xC)
									           + M2C_FIELD(temp_r20, f32*, 0x1C))
									        - sp2C);
									M2C_FIELD(temp_r3_7, f32*, 0)
									    = (f32) - ((temp_f24_4 * var_f9) - sp40);
									M2C_FIELD(temp_r3_7, f32*, 4)
									    = (f32) - ((temp_f25_2 * var_f9) - sp44);
									M2C_FIELD(temp_r4_6, f32*, 0)
									    = (f32) - ((temp_f7_2 * var_f9) - sp28);
									M2C_FIELD(temp_r4_6, f32*, 4)
									    = (f32) - ((temp_f13_2 * var_f9) - sp2C);
									M2C_FIELD(temp_r5_9, f32*, 0) = temp_f24_4;
									M2C_FIELD(temp_r5_9, f32*, 4) = temp_f25_2;
									M2C_FIELD(temp_r6_2, f32*, 0) = temp_f7_2;
									M2C_FIELD(temp_r6_2, f32*, 4) = temp_f13_2;
									*temp_r19_2                   = 0;
									temp_f5_2                     = lbl_804301AC / temp_f10_2;
									M2C_FIELD(temp_r20, f32*, 0x10)
									    = (f32)(temp_f5_2 * (sp48 - M2C_FIELD(temp_r20, f32*, 0)));
									M2C_FIELD(temp_r20, f32*, 0x14)
									    = (f32)(temp_f5_2 * (sp4C - M2C_FIELD(temp_r20, f32*, 4)));
									M2C_FIELD(temp_r20, f32*, 0x18)
									    = (f32)(temp_f5_2 * (sp30 - M2C_FIELD(temp_r20, f32*, 8)));
									M2C_FIELD(temp_r20, f32*, 0x1C) = (f32)(temp_f5_2
									    * (sp34 - M2C_FIELD(temp_r20, f32*, 0xC)));
								}
								if ((s32)lbl_8042ABB0[0x1E] >= 0) {
									temp_r12_2 = (s32*)(var_r21 + lbl_8042ABB0[0x1E]);
									temp_r7_4  = M2C_FIELD(var_r28, u8**, 4);
									temp_r11_2 = var_r21 + lbl_8042ABB0[0x16];
									temp_r9_2  = (f32*)(temp_r12_2 + 4);
									temp_r6_3  = (var_r25 * 0x0BB38435) + 0x3619636B;
									temp_r15_3 = (u8*)(temp_r9_2 + spAC);
									var_r4_2   = temp_r9_2;
									temp_r16_3 = temp_r15_3 + var_r14;
									temp_r5_10 = (temp_r6_3 * 0x0BB38435) + 0x3619636B;
									var_r5_2   = temp_r15_3;
									var_r6_2   = temp_r16_3;
									temp_f2_5  = (f32)temp_r6_3;
									temp_f0_4  = (f32)temp_r5_10;
									var_r25    = (temp_r5_10 * 0x0BB38435) + 0x3619636B;
									var_r10_2  = 0;
									sp10       = (((lbl_804301A4 * (lbl_804301A8 * temp_f0_4))
									                  - lbl_804301AC)
									                 * M2C_FIELD(temp_r7_4, f32*, 0x10))
									    + M2C_FIELD(temp_r7_4, f32*, 8);
									var_f2 = (((lbl_804301A4 * (lbl_804301A8 * temp_f2_5))
									              - lbl_804301AC)
									             * M2C_FIELD(temp_r7_4, f32*, 4))
									    + M2C_FIELD(temp_r7_4, f32*, 0);
									temp_f3 = var_f2;
									sp14    = (((lbl_804301A4 * (lbl_804301A8 * (f32)var_r25))
									               - lbl_804301AC)
									              * M2C_FIELD(temp_r7_4, f32*, 0x14))
									    + M2C_FIELD(temp_r7_4, f32*, 0xC);
									sp18 = sp10;
									sp1C = sp14;
								loop_40:
									if (var_r10_2 < (s32)(M2C_FIELD(var_r28, s32*, 0) - 1)) {
										temp_r19_3 = (var_r25 * 0x0BB38435) + 0x3619636B;
										temp_r18_5 = (var_r10_2 + 1) * 0x18;
										temp_r7_5  = M2C_FIELD(var_r28, u8**, 4) + temp_r18_5;
										*var_r4_2  = var_f2 * M2C_FIELD(var_r21, f32*, 8);
										temp_f4_2
										    = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r19_3))
										           - lbl_804301AC)
										          * M2C_FIELD(temp_r7_5, f32*, 4))
										    + M2C_FIELD(temp_r7_5, f32*, 0);
										temp_f6 = temp_f4_2 - var_f2;
										if (temp_f6 > (f32)lbl_804301B0) {
											var_f26 = lbl_804301AC / temp_f6;
										} else {
											var_f26 = lbl_804301A0;
										}
										var_r4_2 += 4;
										temp_r18_6 = M2C_FIELD(var_r28, u8**, 4) + temp_r18_5;
										temp_r17_2 = (temp_r19_3 * 0x0BB38435) + 0x3619636B;
										var_r10_2 += 1;
										var_r25    = (temp_r17_2 * 0x0BB38435) + 0x3619636B;
										temp_f24_5 = sp10;
										temp_f10_3
										    = (((lbl_804301A4 * (lbl_804301A8 * (f32)temp_r17_2))
										           - lbl_804301AC)
										          * M2C_FIELD(temp_r18_6, f32*, 0x10))
										    + M2C_FIELD(temp_r18_6, f32*, 8);
										sp8       = temp_f10_3;
										temp_f8_3 = (((lbl_804301A4 * (lbl_804301A8 * (f32)var_r25))
										                 - lbl_804301AC)
										                * M2C_FIELD(temp_r18_6, f32*, 0x14))
										    + M2C_FIELD(temp_r18_6, f32*, 0xC);
										temp_f9_3 = var_f26 * (temp_f10_3 - temp_f24_5);
										sp10      = sp8;
										spC       = temp_f8_3;
										temp_f6_2 = var_f26 * (temp_f8_3 - sp14);
										M2C_FIELD(var_r5_2, f32*, 0)
										    = (f32) - ((temp_f9_3 * var_f2) - temp_f24_5);
										temp_f5_3 = -((temp_f6_2 * var_f2) - sp14);
										sp14      = spC;
										var_f2    = temp_f4_2;
										M2C_FIELD(var_r5_2, f32*, 4) = temp_f5_3;
										var_r5_2 += 8;
										M2C_FIELD(var_r6_2, f32*, 0) = temp_f9_3;
										M2C_FIELD(var_r6_2, f32*, 4) = temp_f6_2;
										var_r6_2 += 8;
										goto loop_40;
									}
									*(temp_r9_2 + (var_r10_2 * 4))
									    = var_f2 * M2C_FIELD(var_r21, f32*, 8);
									temp_f6_3 = lbl_804301AC - var_f2;
									if (temp_f6_3 > (f32)lbl_804301B0) {
										var_f8 = lbl_804301AC / temp_f6_3;
									} else {
										var_f8 = lbl_804301A0;
									}
									temp_r0_4 = var_r10_2 * 8;
									temp_r3_8 = temp_r15_3 + temp_r0_4;
									temp_r4_7 = temp_r16_3 + temp_r0_4;
									temp_f9_4 = var_f8
									    * ((M2C_FIELD(temp_r11_2, f32*, 0)
									           + M2C_FIELD(temp_r11_2, f32*, 8))
									        - sp10);
									temp_f8_4 = var_f8
									    * ((M2C_FIELD(temp_r11_2, f32*, 4)
									           + M2C_FIELD(temp_r11_2, f32*, 0xC))
									        - sp14);
									M2C_FIELD(temp_r3_8, f32*, 0)
									    = (f32) - ((temp_f9_4 * var_f2) - sp10);
									M2C_FIELD(temp_r3_8, f32*, 4)
									    = (f32) - ((temp_f8_4 * var_f2) - sp14);
									M2C_FIELD(temp_r4_7, f32*, 0)    = temp_f9_4;
									M2C_FIELD(temp_r4_7, f32*, 4)    = temp_f8_4;
									*temp_r12_2                      = 0;
									temp_f2_6                        = lbl_804301AC / temp_f3;
									M2C_FIELD(temp_r11_2, f32*, 8)   = (f32)(temp_f2_6
									    * (sp18 - M2C_FIELD(temp_r11_2, f32*, 0)));
									M2C_FIELD(temp_r11_2, f32*, 0xC) = (f32)(temp_f2_6
									    * (sp1C - M2C_FIELD(temp_r11_2, f32*, 4)));
								}
							}
							var_r21 += temp_r22;
							var_ctr -= 1;
						} while (var_ctr != 0);
					}
					M2C_FIELD(spA8, u32*, 0) = var_r25;
				}
				var_r15 = arg1;
			}
		}
	} else {
		var_r15 = arg1;
	}
	return var_r15;
}

u8* fn_8022FA00(void* arg0, u8* arg1, u8* arg2)
{
	s32* temp_r4;
	s32* temp_r4_2;
	s32* temp_r4_3;
	s32 temp_r29;
	s32 temp_r29_3;
	s32 temp_r29_5;
	s32 temp_r3;
	s32 temp_r3_2;
	s32 temp_r3_3;
	u32* temp_r5;
	u32* temp_r5_2;
	u32* temp_r5_3;
	u32* temp_r5_4;
	u32* temp_r5_5;
	u8* temp_r29_2;
	u8* temp_r29_4;
	u8* temp_r29_6;

	temp_r5  = M2C_FIELD(arg2, u32**, 0xC);
	temp_r29 = fn_8023506C(M2C_FIELD(arg1, u32**, 0xC)[4], 0x01000002);
	temp_r3  = fn_8023506C(temp_r5[4], 0x01000002, temp_r5);
	if ((temp_r29 >= 0) && (temp_r3 >= 0)) {
		temp_r4    = (s32*)(arg1 + temp_r29);
		temp_r29_2 = arg2 + temp_r3;
		memcpy(temp_r29_2, (u8*)temp_r4, (*temp_r4 * 0x28) + 0x14);
		M2C_FIELD(temp_r29_2, u8**, 4) = (u8*)(temp_r29_2 + 0x14);
	}
	temp_r5_2  = M2C_FIELD(arg1, u32**, 0xC);
	temp_r5_3  = M2C_FIELD(arg2, u32**, 0xC);
	temp_r29_3 = fn_8023506C(temp_r5_2[4], 0x01000003, temp_r5_2);
	temp_r3_2  = fn_8023506C(temp_r5_3[4], 0x01000003, temp_r5_3);
	if ((temp_r29_3 >= 0) && (temp_r3_2 >= 0)) {
		temp_r4_2  = (s32*)(arg1 + temp_r29_3);
		temp_r29_4 = arg2 + temp_r3_2;
		memcpy(temp_r29_4, (u8*)temp_r4_2, (*temp_r4_2 * 0x28) + 0x1C);
		M2C_FIELD(temp_r29_4, u8**, 4) = (u8*)(temp_r29_4 + 0x1C);
	}
	temp_r5_4  = M2C_FIELD(arg1, u32**, 0xC);
	temp_r5_5  = M2C_FIELD(arg2, u32**, 0xC);
	temp_r29_5 = fn_8023506C(temp_r5_4[4], 0x01000005, temp_r5_4);
	temp_r3_3  = fn_8023506C(temp_r5_5[4], 0x01000005, temp_r5_5);
	if ((temp_r29_5 >= 0) && (temp_r3_3 >= 0)) {
		temp_r4_3  = (s32*)(arg1 + temp_r29_5);
		temp_r29_6 = arg2 + temp_r3_3;
		memcpy(temp_r29_6, (u8*)temp_r4_3, (*temp_r4_3 * 0x18) + 0x14);
		M2C_FIELD(temp_r29_6, u8**, 4) = (u8*)(temp_r29_6 + 0x14);
	}
	return arg2;
}

u8* fn_8022FB60(void* arg0, u8* arg1, s32* arg2)
{
	s32 temp_r3;
	s32 temp_r3_2;
	s32 temp_r3_3;
	s32 var_r31;
	u32* temp_r6;
	u32 temp_r30;

	var_r31  = 0;
	temp_r6  = M2C_FIELD(arg1, u32**, 0xC);
	temp_r30 = temp_r6[4];
	temp_r3  = fn_8023506C(temp_r30, 0x01000002, temp_r6);
	if (temp_r3 >= 0) {
		var_r31 = (*(arg1 + temp_r3) * 0x28) + 4;
	}
	temp_r3_2 = fn_8023506C(temp_r30, 0x01000003);
	if (temp_r3_2 >= 0) {
		var_r31 = var_r31 + 4 + (*(arg1 + temp_r3_2) * 0x28);
	}
	temp_r3_3 = fn_8023506C(temp_r30, 0x01000005);
	if (temp_r3_3 >= 0) {
		var_r31 = var_r31 + 4 + (*(arg1 + temp_r3_3) * 0x18);
	}
	*arg2 = var_r31;
	return arg1;
}

u8* fn_8022FC2C(void* arg0, u8* arg1, s32 arg2)
{
	s32 temp_r3;
	s32 temp_r3_2;
	s32 temp_r3_3;
	u32* temp_r29;
	u32* temp_r29_2;
	u32* temp_r29_3;
	u32 temp_r0;
	u32 temp_r0_2;
	u32 temp_r0_3;
	u32 temp_r30;

	temp_r30 = M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u32*, 0x10);
	temp_r3  = fn_8023506C(temp_r30, 0x01000002);
	if (temp_r3 >= 0) {
		temp_r29 = (u32*)(arg1 + temp_r3);
		fn_80193884(arg2, temp_r29, 4);
		temp_r0 = M2C_FIELD(temp_r29, u32*, 0);
		if (temp_r0 != 0) {
			fn_801937A0(arg2, M2C_FIELD(temp_r29, u8**, 4), temp_r0 * 0x28);
			if (fn_8023943C() < 3) {
				M2C_FIELD(temp_r29, s32*, 8) = 4;
				M2C_FIELD(temp_r29, s32*, 0xC)
				    = (s32)(M2C_FIELD(temp_r29, s32*, 8) + (M2C_FIELD(temp_r29, u32*, 0) * 4));
				M2C_FIELD(temp_r29, s32*, 0x10)
				    = (s32)(M2C_FIELD(temp_r29, s32*, 0xC) + (M2C_FIELD(temp_r29, u32*, 0) * 0x10));
			}
		}
	}
	temp_r3_2 = fn_8023506C(temp_r30, 0x01000003);
	if (temp_r3_2 >= 0) {
		temp_r29_2 = (u32*)(arg1 + temp_r3_2);
		fn_80193884(arg2, temp_r29_2, 4);
		temp_r0_2 = M2C_FIELD(temp_r29_2, u32*, 0);
		if (temp_r0_2 != 0) {
			fn_801937A0(arg2, M2C_FIELD(temp_r29_2, u8**, 4), temp_r0_2 * 0x28);
			if (fn_8023943C() < 3) {
				M2C_FIELD(temp_r29_2, s32*, 8) = 4;
				M2C_FIELD(temp_r29_2, s32*, 0xC)
				    = (s32)(M2C_FIELD(temp_r29_2, s32*, 8) + (M2C_FIELD(temp_r29_2, u32*, 0) * 4));
				M2C_FIELD(temp_r29_2, s32*, 0x10) = (s32)(M2C_FIELD(temp_r29_2, s32*, 0xC)
				    + (M2C_FIELD(temp_r29_2, u32*, 0) * 8));
				M2C_FIELD(temp_r29_2, s32*, 0x14) = (s32)(M2C_FIELD(temp_r29_2, s32*, 0x10)
				    + (M2C_FIELD(temp_r29_2, u32*, 0) * 8));
				M2C_FIELD(temp_r29_2, s32*, 0x18) = (s32)(M2C_FIELD(temp_r29_2, s32*, 0x14)
				    + (M2C_FIELD(temp_r29_2, u32*, 0) * 8));
			}
		}
	}
	temp_r3_3 = fn_8023506C(temp_r30, 0x01000005);
	if (temp_r3_3 >= 0) {
		temp_r29_3 = (u32*)(arg1 + temp_r3_3);
		fn_80193884(arg2, temp_r29_3, 4);
		temp_r0_3 = M2C_FIELD(temp_r29_3, u32*, 0);
		if (temp_r0_3 != 0) {
			fn_801937A0(arg2, M2C_FIELD(temp_r29_3, u8**, 4), temp_r0_3 * 0x18);
			if (fn_8023943C() < 3) {
				M2C_FIELD(temp_r29_3, s32*, 8) = 4;
				M2C_FIELD(temp_r29_3, s32*, 0xC)
				    = (s32)(M2C_FIELD(temp_r29_3, s32*, 8) + (M2C_FIELD(temp_r29_3, u32*, 0) * 4));
				M2C_FIELD(temp_r29_3, s32*, 0x10) = (s32)(M2C_FIELD(temp_r29_3, s32*, 0xC)
				    + (M2C_FIELD(temp_r29_3, u32*, 0) * 8));
			}
		}
	}
	return arg1;
}

u8* fn_8022FE30(void* arg0, u8* arg1, s32 arg2)
{
	s32 temp_r3;
	s32 temp_r3_2;
	s32 temp_r3_3;
	u32* temp_r29;
	u32* temp_r29_2;
	u32* temp_r29_3;
	u32 temp_r0;
	u32 temp_r0_2;
	u32 temp_r0_3;
	u32 temp_r30;

	temp_r30 = M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u32*, 0x10);
	temp_r3  = fn_8023506C(temp_r30, 0x01000002);
	if (temp_r3 >= 0) {
		temp_r29 = (u32*)(arg1 + temp_r3);
		fn_80193474(arg2, temp_r29, 4);
		temp_r0 = M2C_FIELD(temp_r29, u32*, 0);
		if (temp_r0 != 0) {
			fn_8019336C(arg2, M2C_FIELD(temp_r29, u8**, 4), temp_r0 * 0x28);
		}
	}
	temp_r3_2 = fn_8023506C(temp_r30, 0x01000003);
	if (temp_r3_2 >= 0) {
		temp_r29_2 = (u32*)(arg1 + temp_r3_2);
		fn_80193474(arg2, temp_r29_2, 4);
		temp_r0_2 = M2C_FIELD(temp_r29_2, u32*, 0);
		if (temp_r0_2 != 0) {
			fn_8019336C(arg2, M2C_FIELD(temp_r29_2, u8**, 4), temp_r0_2 * 0x28);
		}
	}
	temp_r3_3 = fn_8023506C(temp_r30, 0x01000005);
	if (temp_r3_3 >= 0) {
		temp_r29_3 = (u32*)(arg1 + temp_r3_3);
		fn_80193474(arg2, temp_r29_3, 4);
		temp_r0_3 = M2C_FIELD(temp_r29_3, u32*, 0);
		if (temp_r0_3 != 0) {
			fn_8019336C(arg2, M2C_FIELD(temp_r29_3, u8**, 4), temp_r0_3 * 0x18);
		}
	}
	return arg1;
}

u8* fn_8022FF58(void* arg0, u8* arg1)
{
	u8* sp8;
	s32 temp_r3;
	s32 temp_r3_2;
	s32 temp_r3_3;
	u32* temp_r5;
	u32* temp_r5_2;
	u32* temp_r5_3;
	u32* temp_r5_4;
	u32* temp_r5_5;
	u32* temp_r5_6;
	u32 temp_r29;
	u32 temp_r29_2;
	u32 temp_r29_3;
	u8* temp_r31;
	u8* temp_r31_2;
	u8* temp_r31_3;

	temp_r5 = M2C_FIELD(arg1, u32**, 0xC);
	temp_r3 = fn_8023506C(temp_r5[4], 0x01000002, temp_r5);
	if (temp_r3 > 0) {
		temp_r5_2 = M2C_FIELD(arg1, u32**, 0xC);
		temp_r31  = arg1 + temp_r3;
		temp_r29  = fn_8023501C(temp_r5_2[4], 0x01000002, temp_r5_2);
		fn_80234FD8(M2C_FIELD(arg1, u32**, 0xC)[4], 0, 0, 0, &sp8);
		M2C_FIELD(temp_r31, s32*, 0) = (s32)((*(sp8 + (temp_r29 * 4)) - 0x14) / 40);
		M2C_FIELD(temp_r31, u8**, 4) = (u8*)(temp_r31 + 0x14);
		M2C_FIELD(temp_r31, s32*, 8) = 4;
		M2C_FIELD(temp_r31, s32*, 0xC)
		    = (s32)(M2C_FIELD(temp_r31, s32*, 8) + (M2C_FIELD(temp_r31, s32*, 0) * 4));
		M2C_FIELD(temp_r31, s32*, 0x10)
		    = (s32)(M2C_FIELD(temp_r31, s32*, 0xC) + (M2C_FIELD(temp_r31, s32*, 0) * 0x10));
	}
	temp_r5_3 = M2C_FIELD(arg1, u32**, 0xC);
	temp_r3_2 = fn_8023506C(temp_r5_3[4], 0x01000003, temp_r5_3);
	if (temp_r3_2 > 0) {
		temp_r5_4  = M2C_FIELD(arg1, u32**, 0xC);
		temp_r31_2 = arg1 + temp_r3_2;
		temp_r29_2 = fn_8023501C(temp_r5_4[4], 0x01000003, temp_r5_4);
		fn_80234FD8(M2C_FIELD(arg1, u32**, 0xC)[4], 0, 0, 0, &sp8);
		M2C_FIELD(temp_r31_2, s32*, 0) = (s32)((*(sp8 + (temp_r29_2 * 4)) - 0x1C) / 40);
		M2C_FIELD(temp_r31_2, u8**, 4) = (u8*)(temp_r31_2 + 0x1C);
		M2C_FIELD(temp_r31_2, s32*, 8) = 4;
		M2C_FIELD(temp_r31_2, s32*, 0xC)
		    = (s32)(M2C_FIELD(temp_r31_2, s32*, 8) + (M2C_FIELD(temp_r31_2, s32*, 0) * 4));
		M2C_FIELD(temp_r31_2, s32*, 0x10)
		    = (s32)(M2C_FIELD(temp_r31_2, s32*, 0xC) + (M2C_FIELD(temp_r31_2, s32*, 0) * 8));
		M2C_FIELD(temp_r31_2, s32*, 0x14)
		    = (s32)(M2C_FIELD(temp_r31_2, s32*, 0x10) + (M2C_FIELD(temp_r31_2, s32*, 0) * 8));
		M2C_FIELD(temp_r31_2, s32*, 0x18)
		    = (s32)(M2C_FIELD(temp_r31_2, s32*, 0x14) + (M2C_FIELD(temp_r31_2, s32*, 0) * 8));
	}
	temp_r5_5 = M2C_FIELD(arg1, u32**, 0xC);
	temp_r3_3 = fn_8023506C(temp_r5_5[4], 0x01000005, temp_r5_5);
	if (temp_r3_3 > 0) {
		temp_r5_6  = M2C_FIELD(arg1, u32**, 0xC);
		temp_r31_3 = arg1 + temp_r3_3;
		temp_r29_3 = fn_8023501C(temp_r5_6[4], 0x01000005, temp_r5_6);
		fn_80234FD8(M2C_FIELD(arg1, u32**, 0xC)[4], 0, 0, 0, &sp8);
		M2C_FIELD(temp_r31_3, s32*, 0) = (s32)((*(sp8 + (temp_r29_3 * 4)) - 0x14) / 24);
		M2C_FIELD(temp_r31_3, u8**, 4) = (u8*)(temp_r31_3 + 0x14);
		M2C_FIELD(temp_r31_3, s32*, 8) = 4;
		M2C_FIELD(temp_r31_3, s32*, 0xC)
		    = (s32)(M2C_FIELD(temp_r31_3, s32*, 8) + (M2C_FIELD(temp_r31_3, s32*, 0) * 4));
		M2C_FIELD(temp_r31_3, s32*, 0x10)
		    = (s32)(M2C_FIELD(temp_r31_3, s32*, 0xC) + (M2C_FIELD(temp_r31_3, s32*, 0) * 8));
	}
	return arg1;
}

u8* fn_802301CC(u8* arg0, u8* arg1, f32* arg2)
{
	f32 temp_f1;
	f32 temp_f31;
	s32 temp_r3;
	s32 var_ctr;
	u32* temp_r7;
	u32 temp_r4;
	u8* temp_r4_2;
	u8* temp_r6;
	u8* var_r31;
	u8* var_r8;

	temp_f31 = *arg2;
	var_r31  = NULL;
	fn_8022D440(arg0);
	if ((s32)lbl_8042ABB0[0x10] >= 0) {
		var_r31 = arg0 + lbl_8042ABB0[0x10];
	}
	temp_r3 = M2C_FIELD(arg1, s32*, 8);
	var_r8  = arg1 + M2C_FIELD(arg1, s32*, 0x14);
	for (var_ctr = 0; var_ctr < temp_r3; var_ctr += 1) {
		temp_f1 = M2C_FIELD(var_r8, f32*, 4);
		if ((temp_f1 < M2C_FIELD(var_r8, f32*, 8)) && ((s32)lbl_8042ABB0[0x1D] >= 0)) {
			temp_r7 = (u32*)(var_r8 + lbl_8042ABB0[0x1D]);
			temp_r4 = *temp_r7;
			if (temp_r4 < (u32)M2C_FIELD(var_r31, u32*, 0)) {
				if (((temp_f1 + temp_f31) >= M2C_FIELD(temp_r7 + (temp_r4 * 4), f32*, 4))
				    && ((s32)lbl_8042ABB0[0x15] >= 0)) {
					temp_r6 = var_r8 + lbl_8042ABB0[0x15];
					*(M2C_BLOCK8*)(temp_r6)
					    = *(M2C_BLOCK8*)(temp_r7 + (M2C_FIELD(var_r31, s32*, 0xC) + (temp_r4 * 8)));
					temp_r4_2 = (u8*)(temp_r7 + (M2C_FIELD(var_r31, s32*, 0x14) + (*temp_r7 * 8)));
					M2C_FIELD(temp_r6, s32*, 8)   = (s32)M2C_FIELD(temp_r4_2, s32*, 0);
					M2C_FIELD(temp_r6, s32*, 0xC) = (s32)M2C_FIELD(temp_r4_2, s32*, 4);
					*temp_r7 += 1;
				}
			}
		}
		var_r8 += M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), s32*, 0xC);
		var_r8 += M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), s32*, 0xC);
	}
	return arg1;
}

u8* fn_8023031C(void* arg0, u8* arg1, M2C_UNK arg_sp0)
{
	f32 sp24;
	f32 sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32* temp_r24;
	f32* var_r5;
	f32 temp_f0;
	f32 temp_f13;
	f32 temp_f2;
	f32 temp_f4;
	f32 temp_f7;
	f32 var_f2;
	s32* temp_r25;
	s32* var_r28;
	s32 temp_r0;
	s32 temp_r0_2;
	s32 temp_r10;
	s32 temp_r11;
	s32 temp_r20_5;
	s32 temp_r8;
	s32 var_ctr;
	s32 var_r10;
	s32 var_r29;
	s32 var_r30;
	u32 temp_r19;
	u32 temp_r19_2;
	u32 temp_r20;
	u32 temp_r20_2;
	u32 temp_r20_3;
	u32 temp_r20_4;
	u32 temp_r21;
	u32 temp_r7;
	u32 var_r9;
	u8* temp_r12;
	u8* temp_r22;
	u8* temp_r23;
	u8* temp_r26;
	u8* temp_r5;
	u8* temp_r6;
	u8* temp_r8_2;
	u8* temp_r8_3;
	u8* temp_r8_4;
	u8* temp_r9;
	u8* var_r19;
	u8* var_r27;
	u8* var_r6;
	u8* var_r7;

	var_r30 = 0;
	var_r29 = 0;
	var_r28 = NULL;
	var_r19 = NULL;
	fn_8022D440(arg1);
	temp_r12 = arg1 + lbl_8042ABB0[5];
	if ((s32)lbl_8042ABB0[0x10] >= 0) {
		var_r28 = (s32*)(arg1 + lbl_8042ABB0[0x10]);
		temp_r0 = *var_r28;
		var_r30 = temp_r0 * 4;
		var_r29 = temp_r0 * 8;
	}
	M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
	if (M2C_FIELD(temp_r12, f32*, 8) == M2C_FIELD(temp_r12, f32*, 0x40)) {
		temp_r9 = M2C_FIELD(arg1, u8**, 0x20);
		if (temp_r9 != NULL) {
			temp_r8 = M2C_FIELD(temp_r9, s32*, 0x10);
			if (temp_r8 != -1) {
				temp_r11 = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x18), s32*, 0xC);
				temp_r10 = M2C_FIELD(temp_r9, s32*, 8) - temp_r8;
				var_r27  = temp_r9 + (M2C_FIELD(temp_r9, s32*, 0x14) + (temp_r8 * temp_r11));
				var_ctr  = temp_r10;
				var_r9   = (M2C_FIELD(temp_r12, u32*, 0) * 0x0BB38435) + 0x3619636B;
				if (temp_r10 > 0) {
					do {
						if ((lbl_804301C0 == M2C_FIELD(var_r27, f32*, 4))
						    && ((s32)lbl_8042ABB0[0x1D] >= 0)) {
							temp_r8_2  = M2C_FIELD(var_r28, u8**, 4);
							temp_r25   = (s32*)(var_r27 + lbl_8042ABB0[0x1D]);
							temp_r26   = var_r27 + lbl_8042ABB0[0x15];
							temp_r24   = (f32*)(temp_r25 + 4);
							temp_r20   = (var_r9 * 0x0BB38435) + 0x3619636B;
							temp_r23   = (u8*)(temp_r24 + var_r30);
							var_r10    = 0;
							temp_r22   = temp_r23 + var_r29;
							temp_r7    = (temp_r20 * 0x0BB38435) + 0x3619636B;
							var_r5     = temp_r24;
							var_r6     = temp_r23;
							temp_r19   = (temp_r7 * 0x0BB38435) + 0x3619636B;
							temp_f4    = (f32)temp_r20;
							temp_r19_2 = (temp_r19 * 0x0BB38435) + 0x3619636B;
							temp_f13
							    = (lbl_804301C4 * (lbl_804301C8 * (f32)temp_r7)) - lbl_804301CC;
							temp_f2 = lbl_804301C8 * (f32)temp_r19;
							temp_f0 = (f32)temp_r19_2;
							var_r9  = (temp_r19_2 * 0x0BB38435) + 0x3619636B;
							var_r7  = temp_r22;
							sp20    = (temp_f13 * M2C_FIELD(temp_r8_2, f32*, 0x10))
							    + M2C_FIELD(temp_r8_2, f32*, 8);
							sp24 = (((lbl_804301C4 * temp_f2) - lbl_804301CC)
							           * M2C_FIELD(temp_r8_2, f32*, 0x14))
							    + M2C_FIELD(temp_r8_2, f32*, 0xC);
							sp10 = (((lbl_804301C4 * (lbl_804301C8 * temp_f0)) - lbl_804301CC)
							           * M2C_FIELD(temp_r8_2, f32*, 0x20))
							    + M2C_FIELD(temp_r8_2, f32*, 0x18);
							var_f2 = (((lbl_804301C4 * (lbl_804301C8 * temp_f4)) - lbl_804301CC)
							             * M2C_FIELD(temp_r8_2, f32*, 4))
							    + M2C_FIELD(temp_r8_2, f32*, 0);
							sp14 = (((lbl_804301C4 * (lbl_804301C8 * (f32)var_r9)) - lbl_804301CC)
							           * M2C_FIELD(temp_r8_2, f32*, 0x24))
							    + M2C_FIELD(temp_r8_2, f32*, 0x1C);
						loop_10:
							if (var_r10 < (s32)(M2C_FIELD(var_r28, s32*, 0) - 1)) {
								temp_r21   = (var_r9 * 0x0BB38435) + 0x3619636B;
								temp_r20_2 = (temp_r21 * 0x0BB38435) + 0x3619636B;
								temp_f7    = (lbl_804301C4 * (lbl_804301C8 * (f32)temp_r21))
								    - lbl_804301CC;
								temp_r20_3 = (temp_r20_2 * 0x0BB38435) + 0x3619636B;
								temp_r20_4 = (temp_r20_3 * 0x0BB38435) + 0x3619636B;
								temp_r20_5 = (var_r10 + 1) * 0x28;
								temp_r8_3  = M2C_FIELD(var_r28, u8**, 4) + temp_r20_5;
								var_r9     = (temp_r20_4 * 0x0BB38435) + 0x3619636B;
								*var_r5    = var_f2 * M2C_FIELD(var_r27, f32*, 8);
								temp_r8_4  = M2C_FIELD(var_r28, u8**, 4) + temp_r20_5;
								sp18       = (((lbl_804301C4 * (lbl_804301C8 * (f32)temp_r20_2))
								                  - lbl_804301CC)
								                 * M2C_FIELD(temp_r8_4, f32*, 0x10))
								    + M2C_FIELD(temp_r8_4, f32*, 8);
								sp1C = (((lbl_804301C4 * (lbl_804301C8 * (f32)temp_r20_3))
								            - lbl_804301CC)
								           * M2C_FIELD(temp_r8_4, f32*, 0x14))
								    + M2C_FIELD(temp_r8_4, f32*, 0xC);
								sp8 = (((lbl_804301C4 * (lbl_804301C8 * (f32)temp_r20_4))
								           - lbl_804301CC)
								          * M2C_FIELD(temp_r8_4, f32*, 0x20))
								    + M2C_FIELD(temp_r8_4, f32*, 0x18);
								spC = (((lbl_804301C4 * (lbl_804301C8 * (f32)var_r9))
								           - lbl_804301CC)
								          * M2C_FIELD(temp_r8_4, f32*, 0x24))
								    + M2C_FIELD(temp_r8_4, f32*, 0x1C);
								var_f2 = (temp_f7 * M2C_FIELD(temp_r8_3, f32*, 4))
								    + M2C_FIELD(temp_r8_3, f32*, 0);
								var_r5 += 4;
								M2C_FIELD(var_r6, f32*, 0) = sp20;
								var_r10 += 1;
								M2C_FIELD(var_r6, f32*, 4) = sp24;
								var_r6 += 8;
								M2C_FIELD(var_r7, f32*, 0) = sp10;
								M2C_FIELD(var_r7, f32*, 4) = sp14;
								var_r7 += 8;
								sp20 = sp18;
								sp24 = sp1C;
								sp10 = sp8;
								sp14 = spC;
								goto loop_10;
							}
							temp_r0_2                       = var_r10 * 8;
							temp_r5                         = temp_r23 + temp_r0_2;
							temp_r6                         = temp_r22 + temp_r0_2;
							*(temp_r24 + (var_r10 * 4))     = var_f2 * M2C_FIELD(var_r27, f32*, 8);
							M2C_FIELD(temp_r5, f32*, 0)     = sp20;
							M2C_FIELD(temp_r5, f32*, 4)     = sp24;
							M2C_FIELD(temp_r6, f32*, 0)     = sp10;
							M2C_FIELD(temp_r6, f32*, 4)     = sp14;
							*temp_r25                       = 0;
							M2C_FIELD(temp_r26, f32*, 0x10) = (f32)lbl_804301C0;
							M2C_FIELD(temp_r26, f32*, 0x14) = (f32)lbl_804301C0;
							M2C_FIELD(temp_r26, f32*, 0x18) = (f32)lbl_804301C0;
							M2C_FIELD(temp_r26, f32*, 0x1C) = (f32)lbl_804301C0;
						}
						var_r27 += temp_r11;
						var_ctr -= 1;
					} while (var_ctr != 0);
				}
				M2C_FIELD(temp_r12, u32*, 0) = var_r9;
				var_r19                      = arg1;
			}
		}
	} else {
		var_r19 = arg1;
	}
	return var_r19;
}

u8* fn_80230794(void* arg0, u8* arg1, u8* arg2)
{
	s32* temp_r4;
	s32 temp_r31;
	s32 temp_r3;
	u32* temp_r5;
	u8* temp_r31_2;

	temp_r5  = M2C_FIELD(arg2, u32**, 0xC);
	temp_r31 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u32*, 0x10), 0x01000003);
	temp_r3  = fn_8023506C(temp_r5[4], 0x01000003, temp_r5);
	if ((temp_r31 >= 0) && (temp_r3 >= 0)) {
		temp_r4    = (s32*)(arg1 + temp_r31);
		temp_r31_2 = arg2 + temp_r3;
		memcpy(temp_r31_2, (u8*)temp_r4, (*temp_r4 * 0x28) + 0x1C);
		M2C_FIELD(temp_r31_2, u8**, 4) = (u8*)(temp_r31_2 + 0x1C);
	}
	return arg2;
}

u8* fn_80230834(void* arg0, u8* arg1, s32* arg2)
{
	s32 temp_r3;
	s32 var_r31;
	u32* temp_r6;

	var_r31 = 0;
	temp_r6 = M2C_FIELD(arg1, u32**, 0xC);
	temp_r3 = fn_8023506C(temp_r6[4], 0x01000004, temp_r6);
	if (temp_r3 >= 0) {
		var_r31 = (*(arg1 + temp_r3) * 0x28) + 4;
	}
	*arg2 = var_r31;
	return arg1;
}

u8* fn_802308A4(void* arg0, u8* arg1, s32 arg2)
{
	s32 temp_r3;
	u32* temp_r30;
	u32 temp_r0;

	temp_r3 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u32*, 0x10), 0x01000004);
	if (temp_r3 >= 0) {
		temp_r30 = (u32*)(arg1 + temp_r3);
		fn_80193884(arg2, temp_r30, 4);
		temp_r0 = M2C_FIELD(temp_r30, u32*, 0);
		if (temp_r0 != 0) {
			fn_801937A0(arg2, M2C_FIELD(temp_r30, u8**, 4), temp_r0 * 0x28);
			if (fn_8023943C() < 3) {
				M2C_FIELD(temp_r30, s32*, 8) = 4;
				M2C_FIELD(temp_r30, s32*, 0xC)
				    = (s32)(M2C_FIELD(temp_r30, s32*, 8) + (M2C_FIELD(temp_r30, u32*, 0) * 4));
				M2C_FIELD(temp_r30, s32*, 0x14)
				    = (s32)(M2C_FIELD(temp_r30, s32*, 0xC) + (M2C_FIELD(temp_r30, u32*, 0) * 8));
			}
		}
	}
	return arg1;
}

u8* fn_8023096C(void* arg0, u8* arg1, s32 arg2)
{
	s32 temp_r3;
	u32* temp_r30;
	u32 temp_r0;

	temp_r3 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u32*, 0x10), 0x01000004);
	if (temp_r3 >= 0) {
		temp_r30 = (u32*)(arg1 + temp_r3);
		fn_80193474(arg2, temp_r30, 4);
		temp_r0 = M2C_FIELD(temp_r30, u32*, 0);
		if (temp_r0 != 0) {
			fn_8019336C(arg2, M2C_FIELD(temp_r30, u8**, 4), temp_r0 * 0x28);
		}
	}
	return arg1;
}

u8* fn_802309F8(void* arg0, u8* arg1)
{
	u8* sp8;
	s32 temp_r3;
	u32* temp_r5;
	u32* temp_r5_2;
	u32 temp_r29;
	u8* temp_r31;

	temp_r5 = M2C_FIELD(arg1, u32**, 0xC);
	temp_r3 = fn_8023506C(temp_r5[4], 0x01000004, temp_r5);
	if (temp_r3 > 0) {
		temp_r5_2 = M2C_FIELD(arg1, u32**, 0xC);
		temp_r31  = arg1 + temp_r3;
		temp_r29  = fn_8023501C(temp_r5_2[4], 0x01000004, temp_r5_2);
		fn_80234FD8(M2C_FIELD(arg1, u32**, 0xC)[4], 0, 0, 0, &sp8);
		M2C_FIELD(temp_r31, s32*, 0) = (s32)((*(sp8 + (temp_r29 * 4)) - 0x1C) / 40);
		M2C_FIELD(temp_r31, u8**, 4) = (u8*)(temp_r31 + 0x1C);
		M2C_FIELD(temp_r31, s32*, 8) = 4;
		M2C_FIELD(temp_r31, s32*, 0xC)
		    = (s32)(M2C_FIELD(temp_r31, s32*, 8) + (M2C_FIELD(temp_r31, s32*, 0) * 4));
		M2C_FIELD(temp_r31, s32*, 0x14)
		    = (s32)(M2C_FIELD(temp_r31, s32*, 0xC) + (M2C_FIELD(temp_r31, s32*, 0) * 8));
		M2C_FIELD(temp_r31, s32*, 0x10) = 0;
		M2C_FIELD(temp_r31, s32*, 0x18) = 0;
	}
	return arg1;
}

u8* fn_80230AF0(void* arg0, u8* arg1)
{
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f29;
	f32 temp_f29_2;
	f32 temp_f2;
	f32 temp_f30;
	f32 temp_f31;
	f32 temp_f3;
	f32 temp_f7;
	s32 temp_r0;
	s32 temp_r26;
	s32 temp_r27;
	s32 temp_r3_2;
	s32 temp_r3_3;
	s32 temp_r5_2;
	s32 temp_r6;
	s32 temp_r7;
	s32 var_r24;
	s32 var_r30;
	s32 var_r8;
	u32 temp_r19;
	u32 temp_r28;
	u32 temp_r29;
	u32 temp_r5;
	u32 temp_r7_2;
	u32 var_r29;
	u8* temp_r19_2;
	u8* temp_r23;
	u8* temp_r3;
	u8* temp_r3_4;
	u8* var_r20;
	u8* var_r21;
	u8* var_r22;
	u8* var_r25;

	var_r25 = NULL;
	var_r24 = 0;
	var_r21 = NULL;
	fn_8022D440(arg1);
	var_r22  = NULL;
	temp_r23 = arg1 + lbl_8042ABB0[5];
	if ((s32)lbl_8042ABB0[9] >= 0) {
		var_r22 = arg1 + lbl_8042ABB0[9];
	}
	if ((s32)lbl_8042ABB0[0x20] >= 0) {
		var_r21 = arg1 + lbl_8042ABB0[0x20];
	}
	temp_r3 = M2C_FIELD(arg1, u8**, 0x20);
	if (temp_r3 != NULL) {
		temp_r7 = M2C_FIELD(temp_r3, s32*, 0x10);
		if (temp_r7 != -1) {
			temp_r27 = M2C_FIELD(temp_r3, s32*, 8) - temp_r7;
			if (var_r22 != NULL) {
				temp_r6 = M2C_FIELD(var_r22, s32*, 0);
				var_r8  = 0;
				var_r25 = NULL;
				var_r24 = 0;
				if (temp_r6 & 1) {
					var_r8  = 1;
					var_r24 = *M2C_FIELD(var_r22, s32**, 0x24);
					var_r25 = (u8*)((s32)*M2C_FIELD(var_r22, s32**, 0x20) - (temp_r27 * var_r24));
				}
				if (temp_r6 & 8) {
					temp_r0 = var_r8 * 4;
					var_r24 = *(M2C_FIELD(var_r22, s32**, 0x24) + temp_r0);
					var_r25 = (u8*)((s32) * (M2C_FIELD(var_r22, s32**, 0x20) + temp_r0)
					    - (temp_r27 * var_r24));
				}
			}
			temp_r26 = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x18), s32*, 0xC);
			var_r30  = 0;
			temp_r28 = M2C_FIELD(temp_r23, u32*, 0xA8);
			var_r29  = M2C_FIELD(temp_r23, u32*, 0);
			var_r20  = temp_r3 + (M2C_FIELD(temp_r3, s32*, 0x14) + (temp_r7 * temp_r26));
		loop_25:
			if (var_r30 < temp_r27) {
				if ((s32)lbl_8042ABB0[0x17] >= 0) {
					temp_r3_2 = var_r29 * 0x0BB38435;
					temp_r19  = temp_r3_2 + 0x3619636B;
					temp_f29  = lbl_804301D8
					    * ((lbl_804301DC * (lbl_804301E0 * (f32)temp_r19)) - lbl_804301E4);
					temp_f31
					    = (f32)sin(temp_r3_2, temp_f29, lbl_804301E0, lbl_804301DC, lbl_804301D8);
					temp_f30  = (f32)cos(temp_f29);
					temp_r3_3 = (temp_r19 * 0x0BB38435) + 0x3619636B;
					var_r29   = (temp_r3_3 * 0x0BB38435) + 0x3619636B;
					temp_f1   = ((lbl_804301E8 + (lbl_804301E0 * (f32)temp_r3_3))
					                * M2C_FIELD(var_r21, f32*, 4))
					    + M2C_FIELD(var_r21, f32*, 0);
					temp_f1_2 = temp_f30 * temp_f1;
					sp14      = temp_f31 * temp_f1;
					sp18      = temp_f1_2;
					sp1C      = M2C_FIELD(var_r21, f32*, 8)
					    * ((lbl_804301DC * (lbl_804301E0 * (f32)var_r29)) - lbl_804301E4);
					if (temp_r28 != 0U) {
						fn_8019941C(&sp8, &sp14, 1, temp_r28);
					}
					if ((s32)M2C_FIELD(var_r21, s32*, 0xC) == 1) {
						temp_r19_2 = var_r20 + lbl_8042ABB0[0x17];
						temp_f29_2 = (f32)sin(M2C_BITWISE(s32, M2C_FIELD(var_r21, f32*, 0x10)));
						temp_f7    = (f32)cos(M2C_FIELD(var_r21, f32*, 0x10));
						temp_r5    = (var_r29 * 0x0BB38435) + 0x3619636B;
						temp_r7_2  = (temp_r5 * 0x0BB38435) + 0x3619636B;
						temp_r5_2  = temp_r7_2 * 0x0BB38435;
						temp_r29   = temp_r5_2 + 0x3619636B;
						sp14       = (temp_f29_2 * temp_f31)
						    + (((lbl_804301DC * (lbl_804301E0 * (f32)temp_r5)) - lbl_804301E4)
						        * M2C_FIELD(temp_r23, f32*, 0x68));
						temp_f2 = ((lbl_804301DC * (lbl_804301E0 * (f32)temp_r7_2)) - lbl_804301E4)
						    * M2C_FIELD(temp_r23, f32*, 0x6C);
						temp_f1_3 = (lbl_804301DC * (lbl_804301E0 * (f32)temp_r29)) - lbl_804301E4;
						sp18      = (temp_f29_2 * temp_f30) + temp_f2;
						sp1C      = (temp_f1_3 * M2C_FIELD(temp_r23, f32*, 0x70)) + temp_f7;
						fn_801990E0(&sp14, &sp14, temp_r5_2, 0x0BB38435, temp_r7_2, temp_f1_3,
						    temp_f2, lbl_804301E4, lbl_804301E0, lbl_804301DC, temp_f7);
						if (temp_r28 != 0U) {
							fn_8019947C(&sp14, &sp14, 1, temp_r28);
						}
						var_r29 = (temp_r29 * 0x0BB38435) + 0x3619636B;
						temp_f3 = (lbl_804301DC * (lbl_804301E0 * (f32)var_r29)) - lbl_804301E4;
						M2C_FIELD(temp_r19_2, f32*, 0) = (f32)(sp14
						    * ((temp_f3 * M2C_FIELD(temp_r23, f32*, 0x50))
						        + M2C_FIELD(temp_r23, f32*, 0x4C)));
						M2C_FIELD(temp_r19_2, f32*, 4) = (f32)(sp18
						    * ((temp_f3 * M2C_FIELD(temp_r23, f32*, 0x50))
						        + M2C_FIELD(temp_r23, f32*, 0x4C)));
						M2C_FIELD(temp_r19_2, f32*, 8) = (f32)(sp1C
						    * ((temp_f3 * M2C_FIELD(temp_r23, f32*, 0x50))
						        + M2C_FIELD(temp_r23, f32*, 0x4C)));
					}
				}
				if ((s32)lbl_8042ABB0[0x12] >= 0) {
					temp_r3_4                     = var_r20 + lbl_8042ABB0[0x12];
					M2C_FIELD(temp_r3_4, f32*, 0) = sp8;
					M2C_FIELD(temp_r3_4, f32*, 4) = spC;
					M2C_FIELD(temp_r3_4, f32*, 8) = sp10;
				}
				if ((var_r22 != NULL)
				    && (M2C_FIELD(var_r22, s32*, 0) & M2C_FIELD(var_r22, s32*, 0x10) & 1)) {
					M2C_FIELD(var_r25, f32*, 0) = sp8;
					M2C_FIELD(var_r25, f32*, 4) = spC;
					M2C_FIELD(var_r25, f32*, 8) = sp10;
					var_r25 += var_r24;
				}
				var_r20 += temp_r26;
				var_r30 += 1;
				goto loop_25;
			}
			M2C_FIELD(temp_r23, u32*, 0) = var_r29;
		}
	}
	return arg1;
}

u8* fn_80230F78(void* arg0, u8* arg1, u8* arg2)
{
	s32 temp_r31;
	s32 temp_r3;
	u32* temp_r5;

	temp_r5  = M2C_FIELD(arg2, u32**, 0xC);
	temp_r31 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u32*, 0x10), 0x01000007);
	temp_r3  = fn_8023506C(temp_r5[4], 0x01000007, temp_r5);
	if ((temp_r31 >= 0) && (temp_r3 >= 0)) {
		memcpy(arg2 + temp_r3, arg1 + temp_r31, 0x14);
	}
	return arg2;
}

u8* fn_80231004(void* arg0, u8* arg1, s32* arg2)
{
	s32 var_r0;
	u32* temp_r6;

	temp_r6 = M2C_FIELD(arg1, u32**, 0xC);
	var_r0  = 0;
	if (fn_8023506C(temp_r6[4], 0x01000007, temp_r6) >= 0) {
		var_r0 = 0x14;
	}
	*arg2 = var_r0;
	return arg1;
}

u8* fn_80231064(void* arg0, u8* arg1, s32 arg2)
{
	u32 sp8;
	s32 temp_r3;
	u32* temp_r5;
	u8* temp_r30;

	sp8     = 0;
	temp_r5 = M2C_FIELD(arg1, u32**, 0xC);
	temp_r3 = fn_8023506C(temp_r5[4], 0x01000007, temp_r5);
	if (temp_r3 >= 0) {
		temp_r30 = arg1 + temp_r3;
		fn_801937A0(arg2, temp_r30, 4);
		fn_801937A0(arg2, temp_r30 + 4, 4);
		fn_801937A0(arg2, temp_r30 + 8, 4);
		fn_80193884(arg2, &sp8, 4);
		if ((s32)sp8 == 1) {
			M2C_FIELD(temp_r30, s32*, 0xC) = 1;
		} else {
			M2C_FIELD(temp_r30, s32*, 0xC) = 0;
		}
		fn_801937A0(arg2, temp_r30 + 0x10, 4);
	}
	return arg1;
}

u8* fn_8023113C(void* arg0, u8* arg1, s32 arg2)
{
	u32 sp8;
	s32 temp_r3;
	u32* temp_r5;
	u8* temp_r30;

	sp8     = 0;
	temp_r5 = M2C_FIELD(arg1, u32**, 0xC);
	temp_r3 = fn_8023506C(temp_r5[4], 0x01000007, temp_r5);
	if (temp_r3 >= 0) {
		temp_r30 = arg1 + temp_r3;
		fn_8019336C(arg2, temp_r30, 4);
		fn_8019336C(arg2, temp_r30 + 4, 4);
		fn_8019336C(arg2, temp_r30 + 8, 4);
		if ((s32)M2C_FIELD(temp_r30, s32*, 0xC) == 1) {
			sp8 = 1;
		}
		fn_80193474(arg2, &sp8, 4);
		fn_8019336C(arg2, temp_r30 + 0x10, 4);
	}
	return arg1;
}

u8* fn_80231208(void* arg0, u8* arg1)
{
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f0;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f29;
	f32 temp_f2;
	f32 temp_f30;
	f32 temp_f30_2;
	f32 temp_f31;
	f32 temp_f3;
	s32 temp_r0;
	s32 temp_r26;
	s32 temp_r27;
	s32 temp_r3_2;
	s32 temp_r3_3;
	s32 temp_r6;
	s32 temp_r7;
	s32 var_r24;
	s32 var_r29;
	s32 var_r30;
	s32 var_r8;
	u32 temp_r19;
	u32 temp_r19_2;
	u32 temp_r28;
	u8* temp_r19_3;
	u8* temp_r23;
	u8* temp_r3;
	u8* temp_r3_4;
	u8* var_r20;
	u8* var_r21;
	u8* var_r22;
	u8* var_r25;

	var_r25 = NULL;
	var_r24 = 0;
	var_r21 = NULL;
	fn_8022D440(arg1);
	var_r22  = NULL;
	temp_r23 = arg1 + lbl_8042ABB0[5];
	if ((s32)lbl_8042ABB0[9] >= 0) {
		var_r22 = arg1 + lbl_8042ABB0[9];
	}
	if ((s32)lbl_8042ABB0[0x21] >= 0) {
		var_r21 = arg1 + lbl_8042ABB0[0x21];
	}
	temp_r3 = M2C_FIELD(arg1, u8**, 0x20);
	if (temp_r3 != NULL) {
		temp_r7 = M2C_FIELD(temp_r3, s32*, 0x10);
		if (temp_r7 != -1) {
			temp_r27 = M2C_FIELD(temp_r3, s32*, 8) - temp_r7;
			if (var_r22 != NULL) {
				temp_r6 = M2C_FIELD(var_r22, s32*, 0);
				var_r8  = 0;
				var_r25 = NULL;
				var_r24 = 0;
				if (temp_r6 & 1) {
					var_r8  = 1;
					var_r24 = *M2C_FIELD(var_r22, s32**, 0x24);
					var_r25 = (u8*)((s32)*M2C_FIELD(var_r22, s32**, 0x20) - (temp_r27 * var_r24));
				}
				if (temp_r6 & 8) {
					temp_r0 = var_r8 * 4;
					var_r24 = *(M2C_FIELD(var_r22, s32**, 0x24) + temp_r0);
					var_r25 = (u8*)((s32) * (M2C_FIELD(var_r22, s32**, 0x20) + temp_r0)
					    - (temp_r27 * var_r24));
				}
			}
			temp_r26 = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x18), s32*, 0xC);
			var_r30  = 0;
			temp_r28 = M2C_FIELD(temp_r23, u32*, 0xA8);
			var_r29  = M2C_FIELD(temp_r23, s32*, 0);
			var_r20  = temp_r3 + (M2C_FIELD(temp_r3, s32*, 0x14) + (temp_r7 * temp_r26));
		loop_25:
			if (var_r30 < temp_r27) {
				if ((s32)lbl_8042ABB0[0x17] >= 0) {
					temp_r3_2 = var_r29 * 0x0BB38435;
					temp_r19  = temp_r3_2 + 0x3619636B;
					temp_f30  = lbl_80430200
					    * ((lbl_80430204 * (lbl_80430208 * (f32)temp_r19)) - lbl_8043020C);
					temp_f31
					    = (f32)sin(temp_r3_2, temp_f30, lbl_80430208, lbl_80430204, lbl_80430200);
					temp_r3_3  = temp_r19 * 0x0BB38435;
					temp_f30_2 = (f32)cos(temp_f30);
					temp_r19_2 = temp_r3_3 + 0x3619636B;
					temp_f29   = (lbl_80430204 * (lbl_80430208 * (f32)temp_r19_2)) - lbl_8043020C;
					var_r29    = (temp_r19_2 * 0x0BB38435) + 0x3619636B;
					temp_f0    = ((lbl_80430210 + (lbl_80430208 * (f32)var_r29))
					                 * M2C_FIELD(var_r21, f32*, 4))
					    + M2C_FIELD(var_r21, f32*, 0);
					temp_f1
					    = fn_801991F4(M2C_BITWISE(f32, temp_r3_3),
					          -((temp_f29 * temp_f29) - lbl_8043020C), lbl_80430208, lbl_80430204)
					    * temp_f0;
					temp_f2   = temp_f30_2 * temp_f1;
					temp_f1_2 = temp_f31 * temp_f1;
					sp1C      = temp_f29 * temp_f0;
					sp14      = temp_f2;
					sp18      = temp_f1_2;
					if (temp_r28 != 0U) {
						fn_8019941C(&sp8, &sp14, 1, temp_r28);
					}
					if ((s32)M2C_FIELD(var_r21, s32*, 8) == 1) {
						temp_r19_3 = var_r20 + lbl_8042ABB0[0x17];
						fn_801990E0(&sp14, &sp14);
						if (temp_r28 != 0U) {
							fn_8019947C(&sp14, &sp14, 1, temp_r28);
						}
						var_r29 = (var_r29 * 0x0BB38435) + 0x3619636B;
						temp_f3 = (lbl_80430204 * (lbl_80430208 * (f32)var_r29)) - lbl_8043020C;
						M2C_FIELD(temp_r19_3, f32*, 0) = (f32)(sp14
						    * ((temp_f3 * M2C_FIELD(temp_r23, f32*, 0x50))
						        + M2C_FIELD(temp_r23, f32*, 0x4C)));
						M2C_FIELD(temp_r19_3, f32*, 4) = (f32)(sp18
						    * ((temp_f3 * M2C_FIELD(temp_r23, f32*, 0x50))
						        + M2C_FIELD(temp_r23, f32*, 0x4C)));
						M2C_FIELD(temp_r19_3, f32*, 8) = (f32)(sp1C
						    * ((temp_f3 * M2C_FIELD(temp_r23, f32*, 0x50))
						        + M2C_FIELD(temp_r23, f32*, 0x4C)));
					}
				}
				if ((s32)lbl_8042ABB0[0x12] >= 0) {
					temp_r3_4                     = var_r20 + lbl_8042ABB0[0x12];
					M2C_FIELD(temp_r3_4, f32*, 0) = sp8;
					M2C_FIELD(temp_r3_4, f32*, 4) = spC;
					M2C_FIELD(temp_r3_4, f32*, 8) = sp10;
				}
				if ((var_r22 != NULL)
				    && (M2C_FIELD(var_r22, s32*, 0) & M2C_FIELD(var_r22, s32*, 0x10) & 1)) {
					M2C_FIELD(var_r25, f32*, 0) = sp8;
					M2C_FIELD(var_r25, f32*, 4) = spC;
					M2C_FIELD(var_r25, f32*, 8) = sp10;
					var_r25 += var_r24;
				}
				var_r20 += temp_r26;
				var_r30 += 1;
				goto loop_25;
			}
			M2C_FIELD(temp_r23, s32*, 0) = var_r29;
		}
	}
	return arg1;
}

u8* fn_802315DC(void* arg0, u8* arg1, u8* arg2)
{
	s32 temp_r31;
	s32 temp_r3;
	u32* temp_r5;

	temp_r5  = M2C_FIELD(arg2, u32**, 0xC);
	temp_r31 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u32*, 0x10), 0x01000008);
	temp_r3  = fn_8023506C(temp_r5[4], 0x01000008, temp_r5);
	if ((temp_r31 >= 0) && (temp_r3 >= 0)) {
		memcpy(arg2 + temp_r3, arg1 + temp_r31, 0xC);
	}
	return arg2;
}

u8* fn_80231668(void* arg0, u8* arg1, s32* arg2)
{
	s32 var_r0;
	u32* temp_r6;

	temp_r6 = M2C_FIELD(arg1, u32**, 0xC);
	var_r0  = 0;
	if (fn_8023506C(temp_r6[4], 0x01000008, temp_r6) >= 0) {
		var_r0 = 0xC;
	}
	*arg2 = var_r0;
	return arg1;
}

u8* fn_802316C8(void* arg0, u8* arg1, s32 arg2)
{
	u32 sp8;
	s32 temp_r3;
	u32* temp_r5;
	u8* temp_r30;

	sp8     = 0;
	temp_r5 = M2C_FIELD(arg1, u32**, 0xC);
	temp_r3 = fn_8023506C(temp_r5[4], 0x01000008, temp_r5);
	if (temp_r3 >= 0) {
		temp_r30 = arg1 + temp_r3;
		fn_801937A0(arg2, temp_r30, 4);
		fn_801937A0(arg2, temp_r30 + 4, 4);
		fn_80193884(arg2, &sp8, 4);
		if ((s32)sp8 == 1) {
			M2C_FIELD(temp_r30, s32*, 8) = 1;
		} else {
			M2C_FIELD(temp_r30, s32*, 8) = 0;
		}
	}
	return arg1;
}

u8* fn_80231780(void* arg0, u8* arg1, s32 arg2)
{
	u32 sp8;
	s32 temp_r3;
	u32* temp_r5;
	u8* temp_r30;

	sp8     = 0;
	temp_r5 = M2C_FIELD(arg1, u32**, 0xC);
	temp_r3 = fn_8023506C(temp_r5[4], 0x01000008, temp_r5);
	if (temp_r3 >= 0) {
		temp_r30 = arg1 + temp_r3;
		fn_8019336C(arg2, temp_r30, 4);
		fn_8019336C(arg2, temp_r30 + 4, 4);
		if ((s32)M2C_FIELD(temp_r30, s32*, 8) == 1) {
			sp8 = 1;
		}
		fn_80193474(arg2, &sp8, 4);
	}
	return arg1;
}

u8* fn_8023182C(void* arg0, u8* arg1, u8* arg_sp0)
{
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	f32 temp_f1;
	f32 temp_f2;
	f32 temp_f3;
	f32 temp_f4;
	s32 temp_r0;
	s32 temp_r25;
	s32 temp_r26;
	s32 temp_r30;
	s32 temp_r5;
	u8* temp_r5_2;
	s32 temp_r5_4;
	s32 temp_r6;
	s32 temp_r6_2;
	s32 temp_r7;
	s32 var_r23;
	s32 var_r29;
	s32 var_r6;
	s32 var_r8;
	u32 temp_r27;
	u32 temp_r28;
	u32 temp_r3_2;
	u32 temp_r3_3;
	u32 temp_r4;
	u32 temp_r5_3;
	u8* temp_r7_2;
	u32 var_r28;
	u8* temp_r22;
	u8* temp_r30_2;
	u8* temp_r3;
	u8* temp_r3_4;
	u8* var_r19;
	u8* var_r20;
	u8* var_r21;
	u8* var_r24;

	var_r24 = NULL;
	var_r23 = 0;
	fn_8022D440(arg1);
	var_r21  = NULL;
	var_r20  = NULL;
	temp_r22 = arg1 + lbl_8042ABB0[5];
	if ((s32)lbl_8042ABB0[9] >= 0) {
		var_r21 = arg1 + lbl_8042ABB0[9];
	}
	if ((s32)lbl_8042ABB0[0x1F] >= 0) {
		var_r20 = arg1 + lbl_8042ABB0[0x1F];
	}
	temp_r3 = M2C_FIELD(arg1, u8**, 0x20);
	if (temp_r3 != NULL) {
		temp_r7 = M2C_FIELD(temp_r3, s32*, 0x10);
		if (temp_r7 != -1) {
			temp_r26 = M2C_FIELD(temp_r3, s32*, 8) - temp_r7;
			if (var_r21 != NULL) {
				temp_r6 = M2C_FIELD(var_r21, s32*, 0);
				var_r8  = 0;
				var_r24 = NULL;
				var_r23 = 0;
				if (temp_r6 & 1) {
					var_r8  = 1;
					var_r23 = *M2C_FIELD(var_r21, s32**, 0x24);
					var_r24 = (u8*)((s32)*M2C_FIELD(var_r21, s32**, 0x20) - (temp_r26 * var_r23));
				}
				if (temp_r6 & 8) {
					temp_r0 = var_r8 * 4;
					var_r23 = *(M2C_FIELD(var_r21, s32**, 0x24) + temp_r0);
					var_r24 = (u8*)((s32) * (M2C_FIELD(var_r21, s32**, 0x20) + temp_r0)
					    - (temp_r26 * var_r23));
				}
			}
			temp_r25 = M2C_FIELD(M2C_FIELD(arg1, u8**, 0x18), s32*, 0xC);
			var_r29  = 0;
			temp_r27 = M2C_FIELD(temp_r22, u32*, 0xA8);
			var_r28  = M2C_FIELD(temp_r22, u32*, 0);
			var_r19  = temp_r3 + (M2C_FIELD(temp_r3, s32*, 0x14) + (temp_r7 * temp_r25));
		loop_29:
			if (var_r29 < temp_r26) {
				if ((s32)lbl_8042ABB0[0x17] >= 0) {
					temp_r5 = (var_r28 * 0x0BB38435) + 0x3619636B;
					if ((s32)M2C_FIELD(var_r20, s32*, 0xC) != 0) {
						var_r6 = (s32)((lbl_80430228 + (lbl_8043022C * (f32)temp_r5))
						    * (f32)M2C_FIELD(var_r20, u32*, 0));
					} else {
						var_r6                      = M2C_FIELD(var_r20, s32*, 4);
						M2C_FIELD(var_r20, s32*, 4) = (s32)(var_r6 + 1);
						if ((u32)M2C_FIELD(var_r20, s32*, 4) >= (u32)M2C_FIELD(var_r20, u32*, 0)) {
							M2C_FIELD(var_r20, s32*, 4) = 0;
						}
					}
					temp_r3_2 = (temp_r5 * 0x0BB38435) + 0x3619636B;
					temp_r5_2 = (u8*)M2C_FIELD(var_r20, s32*, 0x10);
					temp_r3_3 = (temp_r3_2 * 0x0BB38435) + 0x3619636B;
					temp_r30  = var_r6 * 0xC;
					var_r28   = (temp_r3_3 * 0x0BB38435) + 0x3619636B;
					sp14      = (((lbl_80430230 * (lbl_8043022C * (f32)temp_r3_2)) - lbl_80430234)
					                * M2C_FIELD(temp_r22, f32*, 0x28))
					    + *(temp_r5_2 + temp_r30);
					sp18 = (((lbl_80430230 * (lbl_8043022C * (f32)temp_r3_3)) - lbl_80430234)
					           * M2C_FIELD(temp_r22, f32*, 0x2C))
					    + *(temp_r5_2 + (temp_r30 + 4));
					sp1C = (((lbl_80430230 * (lbl_8043022C * (f32)var_r28)) - lbl_80430234)
					           * M2C_FIELD(temp_r22, f32*, 0x30))
					    + *(temp_r5_2 + (temp_r30 + 8));
					if (temp_r27 != 0U) {
						fn_8019941C(&sp8, &sp14, 1, temp_r27);
					}
					if ((s32)M2C_FIELD(var_r20, s32*, 8) == 1) {
						temp_r7_2  = (u8*)M2C_FIELD(var_r20, u32*, 0x14);
						temp_r6_2  = temp_r30 + 4;
						temp_r4    = (var_r28 * 0x0BB38435) + 0x3619636B;
						temp_r5_3  = (temp_r4 * 0x0BB38435) + 0x3619636B;
						temp_r5_4  = temp_r5_3 * 0x0BB38435;
						temp_r28   = temp_r5_4 + 0x3619636B;
						temp_r30_2 = var_r19 + lbl_8042ABB0[0x17];
						sp14 = (((lbl_80430230 * (lbl_8043022C * (f32)temp_r4)) - lbl_80430234)
						           * M2C_FIELD(temp_r22, f32*, 0x68))
						    + *(temp_r7_2 + temp_r30);
						temp_f4 = (lbl_80430230 * (lbl_8043022C * (f32)temp_r5_3)) - lbl_80430234;
						temp_f2 = (lbl_80430230 * (lbl_8043022C * (f32)temp_r28)) - lbl_80430234;
						sp18    = (temp_f4 * M2C_FIELD(temp_r22, f32*, 0x6C))
						    + *(temp_r7_2 + temp_r6_2);
						temp_f1 = M2C_FIELD(temp_r22, f32*, 0x70);
						sp1C    = (temp_f2 * temp_f1) + *(temp_r7_2 + (temp_r30 + 8));
						fn_801990E0(&sp14, &sp14, temp_r5_4, temp_r6_2, temp_r7_2, 6.9147215e-32f,
						    M2C_BITWISE(f32, lbl_8042ABB0[0x17]), temp_f1, temp_f2, lbl_80430234,
						    temp_f4, lbl_8043022C, lbl_80430230);
						if (temp_r27 != 0U) {
							fn_8019947C(&sp14, &sp14, 1, temp_r27);
						}
						var_r28 = (temp_r28 * 0x0BB38435) + 0x3619636B;
						temp_f3 = (lbl_80430230 * (lbl_8043022C * (f32)var_r28)) - lbl_80430234;
						M2C_FIELD(temp_r30_2, f32*, 0) = (f32)(sp14
						    * ((temp_f3 * M2C_FIELD(temp_r22, f32*, 0x50))
						        + M2C_FIELD(temp_r22, f32*, 0x4C)));
						M2C_FIELD(temp_r30_2, f32*, 4) = (f32)(sp18
						    * ((temp_f3 * M2C_FIELD(temp_r22, f32*, 0x50))
						        + M2C_FIELD(temp_r22, f32*, 0x4C)));
						M2C_FIELD(temp_r30_2, f32*, 8) = (f32)(sp1C
						    * ((temp_f3 * M2C_FIELD(temp_r22, f32*, 0x50))
						        + M2C_FIELD(temp_r22, f32*, 0x4C)));
					}
				}
				if ((s32)lbl_8042ABB0[0x12] >= 0) {
					temp_r3_4                     = var_r19 + lbl_8042ABB0[0x12];
					M2C_FIELD(temp_r3_4, f32*, 0) = sp8;
					M2C_FIELD(temp_r3_4, f32*, 4) = spC;
					M2C_FIELD(temp_r3_4, f32*, 8) = sp10;
				}
				if ((var_r21 != NULL)
				    && (M2C_FIELD(var_r21, s32*, 0) & M2C_FIELD(var_r21, s32*, 0x10) & 1)) {
					M2C_FIELD(var_r24, f32*, 0) = sp8;
					M2C_FIELD(var_r24, f32*, 4) = spC;
					M2C_FIELD(var_r24, f32*, 8) = sp10;
					var_r24 += var_r23;
				}
				var_r19 += temp_r25;
				var_r29 += 1;
				goto loop_29;
			}
			M2C_FIELD(temp_r22, u32*, 0) = var_r28;
		}
	}
	return arg1;
}

u8* fn_80231CE8(void* arg0, u8* arg1, u8* arg2)
{
	s32 temp_r31;
	s32 temp_r3;
	u32* temp_r5;
	u8* temp_r29;
	u8* temp_r31_2;

	temp_r5  = M2C_FIELD(arg2, u32**, 0xC);
	temp_r31 = fn_8023506C(M2C_FIELD(M2C_FIELD(arg1, u8**, 0xC), u32*, 0x10), 0x01000006);
	temp_r3  = fn_8023506C(temp_r5[4], 0x01000006, temp_r5);
	if ((temp_r31 >= 0) && (temp_r3 >= 0)) {
		temp_r31_2                     = arg1 + temp_r31;
		temp_r29                       = arg2 + temp_r3;
		M2C_FIELD(temp_r29, s32*, 0)   = (s32)M2C_FIELD(temp_r31_2, s32*, 0);
		M2C_FIELD(temp_r29, s32*, 8)   = (s32)M2C_FIELD(temp_r31_2, s32*, 8);
		M2C_FIELD(temp_r29, s32*, 0xC) = (s32)M2C_FIELD(temp_r31_2, s32*, 0xC);
		memcpy(M2C_FIELD(temp_r29, u8**, 0x10), M2C_FIELD(temp_r31_2, u8**, 0x10),
		    M2C_FIELD(temp_r29, s32*, 0) * 0xC);
		if ((s32)M2C_FIELD(temp_r31_2, s32*, 8) == 1) {
			memcpy(M2C_FIELD(temp_r29, u8**, 0x14), M2C_FIELD(temp_r31_2, u8**, 0x14),
			    M2C_FIELD(temp_r29, s32*, 0) * 0xC);
		}
	}
	return arg2;
}

u8* fn_80231DB8(void* arg0, u8* arg1, s32* arg2)
{
	s32 temp_r3;
	s32 var_r4;
	s32 var_r4_2;
	u32* temp_r6;
	u8* temp_r5;

	temp_r6 = M2C_FIELD(arg1, u32**, 0xC);
	temp_r3 = fn_8023506C(temp_r6[4], 0x01000006, temp_r6);
	var_r4  = 0;
	if (temp_r3 >= 0) {
		temp_r5 = arg1 + temp_r3;
		if ((u32)M2C_FIELD(temp_r5, u32*, 0x10) != 0U) {
			var_r4_2 = (M2C_FIELD(temp_r5, s32*, 0) * 0xC) + 0x10;
		} else {
			var_r4_2 = 0x10;
		}
		if ((u32)M2C_FIELD(temp_r5, u32*, 0x14) != 0U) {
			var_r4 = var_r4_2 + 4 + (M2C_FIELD(temp_r5, s32*, 0) * 0xC);
		} else {
			var_r4 = var_r4_2 + 4;
		}
	}
	*arg2 = var_r4;
	return arg1;
}

u8* fn_80231E5C(void* arg0, u8* arg1, s32 arg2)
{
	u32 sp8;
	s32 temp_r3;
	u32* temp_r29;
	u32* temp_r5;

	sp8     = 0;
	temp_r5 = M2C_FIELD(arg1, u32**, 0xC);
	temp_r3 = fn_8023506C(temp_r5[4], 0x01000006, temp_r5);
	if (temp_r3 >= 0) {
		temp_r29 = (u32*)(arg1 + temp_r3);
		fn_80193884(arg2, temp_r29, 4);
		fn_80193884(arg2, &sp8, 4);
		if ((s32)sp8 == 1) {
			M2C_FIELD(temp_r29, s32*, 8) = 1;
		} else {
			M2C_FIELD(temp_r29, s32*, 8) = 0;
		}
		fn_80193884(arg2, &sp8, 4);
		if ((s32)sp8 == 1) {
			M2C_FIELD(temp_r29, s32*, 0xC) = 1;
		} else {
			M2C_FIELD(temp_r29, s32*, 0xC) = 0;
		}
		fn_80193884(arg2, &sp8, 4);
		if ((s32)sp8 == 1) {
			fn_801937A0(arg2, M2C_FIELD(temp_r29, u8**, 0x10), M2C_FIELD(temp_r29, u32*, 0) * 0xC);
		} else {
			M2C_FIELD(temp_r29, u8**, 0x10) = NULL;
		}
		fn_80193884(arg2, &sp8, 4);
		if ((s32)sp8 == 1) {
			fn_801937A0(arg2, M2C_FIELD(temp_r29, u8**, 0x14), M2C_FIELD(temp_r29, u32*, 0) * 0xC);
		} else {
			M2C_FIELD(temp_r29, u8**, 0x14) = NULL;
		}
	}
	return arg1;
}

u8* fn_80231FAC(void* arg0, u8* arg1, s32 arg2)
{
	u32 sp8;
	s32 temp_r3;
	u32* temp_r29;
	u32* temp_r5;

	sp8     = 0;
	temp_r5 = M2C_FIELD(arg1, u32**, 0xC);
	temp_r3 = fn_8023506C(temp_r5[4], 0x01000006, temp_r5);
	if (temp_r3 >= 0) {
		temp_r29 = (u32*)(arg1 + temp_r3);
		fn_80193474(arg2, temp_r29, 4);
		if ((s32)M2C_FIELD(temp_r29, s32*, 8) == 1) {
			sp8 = 1;
		}
		fn_80193474(arg2, &sp8, 4);
		sp8 = M2C_FIELD(temp_r29, s32*, 0xC) == 1;
		fn_80193474(arg2, &sp8, 4);
		if ((u8*)M2C_FIELD(temp_r29, u8**, 0x10) != NULL) {
			sp8 = 1;
			fn_80193474(arg2, &sp8, 4);
			fn_8019336C(arg2, M2C_FIELD(temp_r29, u8**, 0x10), M2C_FIELD(temp_r29, u32*, 0) * 0xC);
		} else {
			sp8 = 0;
			fn_80193474(arg2, &sp8, 4);
		}
		if ((u8*)M2C_FIELD(temp_r29, u8**, 0x14) != NULL) {
			sp8 = 1;
			fn_80193474(arg2, &sp8, 4);
			fn_8019336C(arg2, M2C_FIELD(temp_r29, u8**, 0x14), M2C_FIELD(temp_r29, u32*, 0) * 0xC);
		} else {
			sp8 = 0;
			fn_80193474(arg2, &sp8, 4);
		}
	}
	return arg1;
}

u8* fn_80232114(void* arg0, u8* arg1)
{
	u8* sp8;
	u32* temp_r5;
	u32* temp_r5_2;
	u32 temp_r30;
	u8* temp_r31;

	temp_r5   = M2C_FIELD(arg1, u32**, 0xC);
	temp_r5_2 = M2C_FIELD(arg1, u32**, 0xC);
	temp_r31  = arg1 + fn_8023506C(temp_r5[4], 0x01000006, temp_r5);
	temp_r30  = fn_8023501C(temp_r5_2[4], 0x01000006, temp_r5_2);
	fn_80234FD8(M2C_FIELD(arg1, u32**, 0xC)[4], 0, 0, 0, &sp8);
	M2C_FIELD(temp_r31, s32*, 0)    = (s32)((*(sp8 + (temp_r30 * 4)) - 0x18) / 24);
	M2C_FIELD(temp_r31, u8**, 0x10) = (u8*)(temp_r31 + 0x18);
	M2C_FIELD(temp_r31, u8**, 0x14)
	    = (u8*)(M2C_FIELD(temp_r31, u8**, 0x10) + (M2C_FIELD(temp_r31, s32*, 0) * 0xC));
	M2C_FIELD(temp_r31, s32*, 8)   = 0;
	M2C_FIELD(temp_r31, s32*, 4)   = 0;
	M2C_FIELD(temp_r31, s32*, 0xC) = 0;
	return arg1;
}
