#include "types.h"

// RenderWare GameCube raster/native-data backend. The complete unit occupies
// .text 0x80225100-0x80228BEC, .rodata 0x80240648-0x8024065C, .data
// 0x8029BB30-0x8029BB6C, and .bss 0x8042AB68-0x8042AB90. The next function is
// the first user of the independent BSS object at 0x8042AB90.

typedef s32 M2C_UNK;
typedef struct {
	s32 words[16];
} M2C_BLOCK64;
#define M2C_FIELD(base, type, offset)   (*(type)((u8*)(base) + (offset)))
#define M2C_STRUCT_COPY(dst, src, size) memcpy((void*)(dst), (const void*)(src), (size))
#define M2C_ERROR(...)                  0
#define RW_LINK_HEAD                    (*(u8***)(lbl_8042C9A4 + lbl_8042C970 + 0x24))

M2C_UNK DCFlushRange(u32, s32);                                                      /* extern */
M2C_UNK GXCallDisplayList(s32, s32);                                                 /* extern */
M2C_UNK GXInvalidateVtxCache();                                                      /* extern */
M2C_UNK GXLoadNrmMtxImm(f32*, u32);                                                  /* extern */
M2C_UNK GXLoadPosMtxImm(f32*, u32);                                                  /* extern */
M2C_UNK GXSetDrawSync(u16);                                                          /* extern */
M2C_UNK GXSetVtxDesc(M2C_UNK, M2C_UNK);                                              /* extern */
s32 RwEngineRegisterPlugin(M2C_UNK, M2C_UNK, u8* (*)(u8*), u8* (*)(u8*));            /* extern */
M2C_UNK RwFreeListDestroy(s32);                                                      /* extern */
s32 fn_801520D0(M2C_UNK, M2C_UNK, void (*)(u8*), void (*)(u8*), void (*)(u8*, u8*)); /* extern */
M2C_UNK fn_80152150(
    M2C_UNK, u32* (*)(u32*, s32, u8*, s32, s32), void (*)(), s32 (*)(), M2C_UNK*); /* extern */
M2C_UNK fn_8015218C(M2C_UNK, s32 (*)(u8*));                                        /* extern */
M2C_UNK fn_801521C0(M2C_UNK, s32 (*)(u8*, s32, s32, s32));                         /* extern */
s32 fn_801521F4(M2C_UNK);                                                          /* extern */
s32 fn_80152FDC(M2C_UNK, M2C_UNK, void (*)(u8*), u8* (*)(u8*), void (*)());        /* extern */
M2C_UNK fn_8015301C(M2C_UNK, u32* (*)(u32*, s32, u32*, s32, s32), s32* (*)(s32*, s32*, s32*),
    s32 (*)(u8*), M2C_UNK*);                                    /* extern */
M2C_UNK fn_8015C358(s32, u32);                                  /* extern */
M2C_UNK fn_8015C370(s32, u32);                                  /* extern */
M2C_UNK (*fn_8015C37C(s32))(u8*, u8**);                         /* extern */
M2C_UNK fn_8015C388(s32, u32);                                  /* extern */
M2C_UNK fn_8015C3A4(s32, u8*, u32*);                            /* extern */
M2C_UNK fn_8015C590();                                          /* extern */
s32* fn_8015D4B8();                                             /* extern */
M2C_UNK (*fn_8015ECF4(u32, s32, s32, s32))(u8*, u8*, u8*, f32); /* extern */
s32 fn_8015F3FC(u8*, u8*, s32, s32);                            /* extern */
u8* fn_8015F5EC(s32*, s32, s32);                                /* extern */
u8* fn_8015F8A4(s32*, s32, s32);                                /* extern */
s32 fn_801659DC(u32*, u8*, u8*);                                /* extern */
u32 fn_80192ED8(s32*, M2C_UNK, s32, M2C_UNK, M2C_UNK);          /* extern */
s32 fn_80192F38(M2C_UNK, u32*, u32*);                           /* extern */
u32 fn_8019336C(s32*, s32, s32);                                /* extern */
u32 fn_80193474(s32*, s32*, s32);                               /* extern */
u32 fn_801937A0(u32*, u32*, s32);                               /* extern */
u32 fn_80193884(u32*, s32*, s32);                               /* extern */
M2C_UNK fn_80193FE8(s32*);                                      /* extern */
s32 fn_8019408C(M2C_UNK);                                       /* extern */
M2C_UNK fn_80195674(M2C_UNK*, M2C_UNK*, M2C_UNK*);              /* extern */
M2C_UNK fn_80195B5C(M2C_UNK*, M2C_UNK*);                        /* extern */
s32 fn_801966CC(M2C_UNK, s32, M2C_UNK, s32, M2C_UNK*);          /* extern */
M2C_UNK fn_80197384(s32);                                       /* extern */
u8** fn_801974E0(u8*, u8*, s32, void (*)(u8*));                 /* extern */
u32 fn_801979AC(u32*, s32, s32);                                /* extern */
u32 fn_80197B48(s32*, s32, s32);                                /* extern */
u32 fn_80197D70(u32*, s32);                                     /* extern */
M2C_UNK fn_8019941C(u32, s32, M2C_UNK, s32);                    /* extern */
M2C_UNK fn_8019947C(s32, s32, M2C_UNK, s32);                    /* extern */
s32 fn_8019D41C(M2C_UNK);                                       /* extern */
M2C_UNK* fn_8019E8EC(s32);                                      /* extern */
M2C_UNK fn_801AD0AC(M2C_UNK*, s32);                             /* extern */
M2C_UNK fn_801AF914(s32, s32);                                  /* extern */
M2C_UNK fn_801B1D0C(s32**, M2C_UNK);                            /* extern */
s32 fn_801B2894(u16);                                           /* extern */
u8* fn_801B3984();                                              /* extern */
M2C_UNK fn_801B43EC();                                          /* extern */
s32 fn_801B4EB4();                                              /* extern */
s32 fn_801B51B8(u8*, s32, M2C_UNK, M2C_UNK);                    /* extern */
M2C_UNK fn_801B52BC(s32, M2C_UNK, s32*, M2C_UNK, ...);          /* extern */
void* memcpy(void*, const void*, u32);                          /* extern */
void* memset(void*, s32, u32);                                  /* extern */
u8* fn_80226468(u32* arg0);                                     /* static */
u32* fn_8022647C(u32* arg0, u8* arg1);                          /* static */
u8* fn_80226508(u8* arg0);                                      /* static */
u32* fn_80227D54(u32* arg0);                                    /* static */
s32 fn_80227DF0(s32 arg0);                                      /* static */
s32 fn_80227F48(u8* arg0);                                      /* static */
s32* fn_80228014(s32* arg0, u8* arg1);                          /* static */
u32* fn_8022824C(u32* arg0, u32* arg1);                         /* static */
s32 fn_802290F0(u32*, u8*, u8*);                                /* static */
s32 fn_8022A028(u32*, u8*, u8*);                                /* static */
M2C_UNK fn_8022A454(s32, s32, s32, M2C_UNK*, u8*, u32);         /* static */
M2C_UNK fn_8022A650(u8*, s32, u32, s32, u8, u8, s32);           /* static */
M2C_UNK fn_8022A87C(u8*, s32, u32, s32, u8, u8, s32);           /* static */
M2C_UNK fn_8022AB3C(u8*, s32, u32, s32, u8, u8, s32);           /* static */
M2C_UNK fn_8022B230(s32);                                       /* static */
M2C_UNK fn_8022B2A8();                                          /* static */
M2C_UNK fn_8022B308(u8*, s32);                                  /* static */
extern void fn_8015C004(void);
const u32 lbl_80240648[5]                        = { 3, 3, 6, 6, 12 };
__declspec(section ".data") u32 lbl_8029BB30[15] = { 0 };
extern M2C_UNK lbl_803EDB8C[12];
u8 lbl_8042AB68[0x28];
extern s32 lbl_8042BD28;
extern volatile u16 lbl_8042BE88;
extern s32 lbl_8042C090;
extern s32 lbl_8042C094;
extern s32 lbl_8042C930;
extern s32 lbl_8042C970;
extern u8* lbl_8042C9A4;
extern s32 lbl_8042CA48;
extern M2C_UNK (*lbl_8042CF80)(u8*, u8**);
extern s32 lbl_804300F8;
extern u8 lbl_804300FC;
extern s32 lbl_80430100;
extern u8 lbl_80430104;
extern s32 lbl_80430108;
extern u8 lbl_8043010C;
extern f32 lbl_80430110;

#pragma dont_inline on
s32 fn_80225100(u8* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x3C) != 0U) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(M2C_FIELD(arg0, u8**, 0x3C));
	}
	M2C_FIELD(arg0, s32*, 0x30) = 0;
	M2C_FIELD(arg0, s32*, 0x34) = 0;
	M2C_FIELD(arg0, s32*, 0x38) = 0;
	M2C_FIELD(arg0, u32*, 0x3C) = 0U;
	M2C_FIELD(arg0, s32*, 0x40) = 0;
	M2C_FIELD(arg0, s32*, 0x44) = 0;
	return 1;
}
#pragma dont_inline reset

#pragma dont_inline on
s32* fn_80225164(s32* arg0, u8* arg1)
{
	u8* temp_r31;
	s32 temp_r6;

	temp_r31 = arg1 + 0x30;
	if (fn_80193474(arg0, (s32*)temp_r31, 4) == 0U) {
		return NULL;
	}
	if (fn_80193474(arg0, (s32*)(temp_r31 + 4), 4) == 0U) {
		return NULL;
	}
	if (fn_80193474(arg0, (s32*)(temp_r31 + 8), 4) == 0U) {
		return NULL;
	}
	if ((u32)M2C_FIELD(arg1, u32*, 0x34) != 0U) {
		temp_r6 = M2C_FIELD(arg1, s32*, 0);
		if (fn_80197B48(arg0, M2C_FIELD(temp_r31, s32*, 0xC),
		        (s32)((u8*)temp_r6 + (M2C_FIELD(temp_r31, s32*, 4) * 2)
		            + (M2C_FIELD(temp_r31, s32*, 8) * 2)))
		    == 0U) {
			return NULL;
		}
	}
	return arg0;
}
#pragma dont_inline reset

u32* fn_80225248(u32* arg0, u8* arg1)
{
	s32 sp10;
	s32 spC;
	u32 sp8;
	s32 temp_r24;
	s32 temp_r25;
	s32 temp_r26;
	s32 temp_r27;
	s32 temp_r5x;
	s32 temp_r6;
	u32 temp_r28;
	u8* temp_r31;
	u8* var_r4;

	temp_r31 = arg1 + 0x30;
	if (fn_80193884(arg0, (s32*)&sp8, 4) == 0U) {
		return NULL;
	}
	if (fn_80193884(arg0, &sp10, 4) == 0U) {
		return NULL;
	}
	if (fn_80193884(arg0, &spC, 4) == 0U) {
		return NULL;
	}
	temp_r25 = sp10;
	if (temp_r25 > 0) {
		temp_r26 = spC;
		temp_r27 = M2C_FIELD(arg1, s32*, 0);
		temp_r28 = sp8;
		if ((u32)M2C_FIELD(arg1, u32*, 0x3C) != 0U) {
			M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(lbl_8042C9A4);
		}
		M2C_FIELD(arg1, u32*, 0x30) = 0U;
		M2C_FIELD(arg1, s32*, 0x34) = 0;
		temp_r24                    = (u32)temp_r25 * 2 + (temp_r26 * 2);
		temp_r24                    = temp_r27 + temp_r24;
		M2C_FIELD(arg1, s32*, 0x38) = 0;
		M2C_FIELD(arg1, u32*, 0x3C) = 0U;
		M2C_FIELD(arg1, s32*, 0x40) = 0;
		M2C_FIELD(arg1, s32*, 0x44) = 0;
		M2C_FIELD(arg1, u32*, 0x3C)
		    = M2C_FIELD(lbl_8042C9A4, u32(**)(), 0x134)(temp_r24, lbl_8042C9A4);
		if ((u32)M2C_FIELD(arg1, u32*, 0x3C) == 0U) {
			var_r4 = NULL;
		} else {
			memset(M2C_FIELD(arg1, void**, 0x3C), 0, temp_r24);
			M2C_FIELD(arg1, u32*, 0x30) = temp_r28;
			var_r4                      = arg1;
			M2C_FIELD(arg1, s32*, 0x34) = temp_r25;
			M2C_FIELD(arg1, s32*, 0x38) = temp_r26;
			M2C_FIELD(arg1, s32*, 0x40) = (s32)(M2C_FIELD(arg1, u32*, 0x3C) + temp_r27);
			M2C_FIELD(arg1, s32*, 0x44) = (s32)(M2C_FIELD(arg1, s32*, 0x40) + (temp_r25 * 2));
		}
		if (var_r4 == NULL) {
			return NULL;
		}
		temp_r6  = M2C_FIELD(arg1, s32*, 0);
		temp_r5x = (u32)M2C_FIELD(temp_r31, u32*, 4) * 2 + (M2C_FIELD(temp_r31, s32*, 8) * 2);
		if (fn_801979AC(arg0, M2C_FIELD(temp_r31, s32*, 0xC), temp_r6 + temp_r5x) == 0U) {
			M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(temp_r31, lbl_8042C9A4);
			return NULL;
		}
		goto block_16;
	}
block_16:
	return arg0;
}

#pragma dont_inline on
s32 fn_80225400(u8* arg0)
{
	s32 var_r0;
	u32 temp_r4;

	temp_r4 = M2C_FIELD(arg0, u32*, 0x34);
	var_r0  = 0xC;
	if (temp_r4 != 0) {
		var_r0 = (s32)(M2C_FIELD(arg0, u8**, 0) + (temp_r4 * 2) + (M2C_FIELD(arg0, s32*, 0x38) * 2)
		    + 0xC);
	}
	return var_r0;
}
#pragma dont_inline reset

u8* fn_80225434(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32* arg4, u32* arg5, u8* arg6)
{
	u8 sp8[0xF0];
	s32 temp_cr0_eq;
	s32 temp_r23;
	s32 temp_r4_2;
	s32 var_ctr;
	s32 var_r0;
	s32 var_r3;
	s32 var_r6_3;
	s32 var_r9;
	u32 var_i;
	u32 var_j;
	u8* var_r10;
	u32* var_r11;
	u8* var_r12;
	u32* var_r23;
	u32* var_r6;
	u32* var_r7;
	u8* var_r7_2;
	u32* var_r8;
	u32 temp_r0;
	u32 temp_r4;
	u32 var_ctr_2;
	u32 var_r26;
	u32 var_r5;
	u32 var_r5_2;
	u32 var_r6_2;
	u32 var_r7_3;
	u8* temp_r30;
	u8* temp_r4_3;
	u8* var_r5_3;

	var_r26  = arg2;
	temp_r30 = M2C_FIELD(lbl_8042C9A4, u8 * (**)(), 0x144)(
	    M2C_FIELD(lbl_8029BB30, s32*, 0x18), lbl_8042C9A4);
	memset(temp_r30, 0, 0x4C);
	if (arg3 == 0U) {
		var_r7                          = arg4;
		M2C_FIELD(temp_r30, u32*, 0x10) = 1U;
		for (var_r5 = 0U; var_r5 < arg0; var_r5 += 1, var_r7 += 4) {
			temp_r4 = M2C_FIELD(temp_r30, u32*, 0x10);
			var_r6  = &var_r7[temp_r4];
			for (var_i = temp_r4; var_i < 4U; var_i += 1, var_r6 += 1) {
				if ((u32)*var_r6 == 0U) {
					break;
				}
				M2C_FIELD(temp_r30, u32*, 0x10) = (u32)(M2C_FIELD(temp_r30, u32*, 0x10) + 1);
				if ((u32)M2C_FIELD(temp_r30, u32*, 0x10) == 4U) {
					goto block_8;
				}
			}
		}
	}
block_8:
	if (var_r26 == 0) {
		var_r11 = arg4;
		var_r12 = sp8;
		var_r23 = arg5;
		var_r26 = 0;
		for (var_r6_2 = 0U; var_r6_2 < arg0; var_r6_2 += 1, var_r11 += 4, var_r23 += 1) {
			var_r5_2 = 0U;
			var_r8   = var_r11;
			var_r9   = var_r5_2;
			var_r10  = var_r12;
			for (; var_r5_2 < (u32)M2C_FIELD(temp_r30, u32*, 0x10);
			    var_r5_2 += 1, var_r8 += 1, var_r9 += 8) {
				if ((u32)*var_r8 == 0U) {
					continue;
				}
				var_r7_2 = sp8;
				var_r3   = 1;
				temp_r0  = (u32)*var_r23 >> var_r9;
				for (var_j = 0U; var_j < var_r26; var_j += 1, var_r7_2 += 1) {
					if ((u8)temp_r0 == (u8)*var_r7_2) {
						var_r3 = 0;
						break;
					}
				}
				if (var_r3 != 0) {
					*var_r10 = (u8)temp_r0;
					var_r10 += 1;
					var_r12 += 1;
					var_r26 += 1;
				}
			}
		}
	}
	temp_r4_2 = (arg1 << 6) + var_r26;
	temp_r23  = temp_r4_2 + 0xF;
	temp_r23  = (arg0 * 0x14) + temp_r23;
	M2C_FIELD(temp_r30, u32*, 0x48)
	    = M2C_FIELD(lbl_8042C9A4, u32(**)(), 0x134)(temp_r23, temp_r4_2);
	if ((u32)M2C_FIELD(temp_r30, u32*, 0x48) == 0U) {
		var_r0 = 0;
	} else {
		memset(M2C_FIELD(temp_r30, void**, 0x48), 0, temp_r23);
		M2C_FIELD(temp_r30, u32*, 0) = arg1;
		M2C_FIELD(temp_r30, u32*, 4) = var_r26;
		M2C_FIELD(temp_r30, u32*, 8) = (u32)M2C_FIELD(temp_r30, u32*, 0x48);
		M2C_FIELD(temp_r30, s32*, 0xC)
		    = (s32)((M2C_FIELD(temp_r30, u32*, 8) + (var_r26 + 0xF)) & 0xFFFFFFF0);
		M2C_FIELD(temp_r30, u32*, 0x14) = (u32)(M2C_FIELD(temp_r30, s32*, 0xC) + (arg1 << 6));
		M2C_FIELD(temp_r30, u32*, 0x18) = (u32)(M2C_FIELD(temp_r30, u32*, 0x14) + (arg0 * 4));
		if ((sp8 != NULL) && (var_r26 != 0)) {
			memcpy((void*)M2C_FIELD(temp_r30, u32*, 8), sp8, var_r26);
		}
		if (arg6 != 0U) {
			var_r7_3 = M2C_FIELD(temp_r30, u32*, 0);
			var_r6_3 = var_r7_3 << 6;
			var_r5_3 = arg6 + var_r6_3;
			while (var_r5_3 -= 0x40, var_r6_3 -= 0x40, var_r7_3-- != 0U) {
				temp_r4_3                = (u8*)(M2C_FIELD(temp_r30, s32*, 0xC) + var_r6_3);
				*(M2C_BLOCK64*)temp_r4_3 = *(M2C_BLOCK64*)var_r5_3;
			}
		}
		if (arg5 != NULL) {
			memcpy((void*)M2C_FIELD(temp_r30, u32*, 0x14), arg5, arg0 * 4);
		}
		if (arg4 != NULL) {
			memcpy((void*)M2C_FIELD(temp_r30, u32*, 0x18), arg4, arg0 * 0x10);
		}
		var_r0 = 1;
	}
	if (var_r0 == 0) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x148)(
		    M2C_FIELD(lbl_8029BB30, s32*, 0x18), temp_r30, lbl_8042C9A4);
		return NULL;
	}
	return temp_r30;
}

u8* fn_802257A8(u8* arg0)
{
	s32 var_r31;

	if ((s32)M2C_FIELD(lbl_8029BB30, s32*, 0x20) == 0) {
		var_r31 = 1;
		if (fn_8019D41C(0x120) != -1) {
			var_r31 |= 2;
		}
		if (fn_8019D41C(0x12E) != -1) {
			var_r31 |= 4;
		}
		fn_8022B230(var_r31);
		M2C_FIELD(lbl_8029BB30, s32*, 0x18)
		    = fn_801966CC(0x4C, lbl_8042C090, 4, lbl_8042C094, (M2C_UNK*)lbl_8042AB68);
		M2C_FIELD(lbl_8029BB30, s32*, 0x10)
		    = M2C_FIELD(lbl_8042C9A4, s32(**)(), 0x134)(0x400F, lbl_8042C9A4);
		memset(M2C_FIELD(lbl_8029BB30, void**, 0x10), 0, 0x400F);
		M2C_FIELD(lbl_8029BB30, s32*, 0xC)
		    = (s32)((M2C_FIELD(lbl_8029BB30, s32*, 0x10) + 0xF) & 0xFFFFFFF0);
	}
	M2C_FIELD(lbl_8029BB30, s32*, 0x20) = (s32)(M2C_FIELD(lbl_8029BB30, s32*, 0x20) + 1);
	return arg0;
}

u8* fn_802258A4(u8* arg0)
{
	s32 temp_r0;
	s32 temp_r3;
	void (*temp_r12)(s32);

	temp_r0                             = M2C_FIELD(lbl_8029BB30, s32*, 0x20) - 1;
	M2C_FIELD(lbl_8029BB30, s32*, 0x20) = temp_r0;
	if (temp_r0 == 0) {
		fn_8022B2A8();
		RwFreeListDestroy(M2C_FIELD(lbl_8029BB30, s32*, 0x18));
		M2C_FIELD(lbl_8029BB30, s32*, 0x18) = 0;
		temp_r3                             = M2C_FIELD(lbl_8029BB30, s32*, 0x10);
		temp_r12                            = M2C_FIELD(lbl_8042C9A4, void (**)(s32), 0x138);
		temp_r12(temp_r3);
		M2C_FIELD(lbl_8029BB30, s32*, 0x10) = 0;
	}
	return arg0;
}

void fn_80225930(u8* arg0)
{
	M2C_FIELD(arg0, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8)) = 0;
}

u8* fn_80225948(u8* arg0)
{
	u8* temp_r30;

	temp_r30 = M2C_FIELD(arg0, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8));
	if (temp_r30 != NULL) {
		fn_80227DF0((s32)arg0);
		M2C_FIELD(arg0, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8)) = fn_80226508(temp_r30);
	}
	return arg0;
}

void fn_802259B0(void) { }

void fn_802259B4(u8* arg0)
{
	M2C_FIELD(arg0, s32*, M2C_FIELD(lbl_8029BB30, s32*, 4)) = 0;
}

void fn_802259CC(u8* arg0)
{
	if ((u32)M2C_FIELD(arg0, s32*, M2C_FIELD(lbl_8029BB30, s32*, 4)) != 0U) {
		M2C_FIELD(arg0, s32*, M2C_FIELD(lbl_8029BB30, s32*, 4)) = 0;
	}
}

void fn_802259F0(u8* arg0, u8* arg1)
{
	M2C_FIELD(arg0, s32*, M2C_FIELD(lbl_8029BB30, s32*, 4))
	    = M2C_FIELD(arg1, s32*, M2C_FIELD(lbl_8029BB30, s32*, 4));
}

s32 fn_80225A08(u8* arg0)
{
	s32 var_r31;

	var_r31 = 1;
	if ((fn_8019D41C(0x120) != -1) && ((u8) * (arg0 + fn_801521F4(0x120)) != 0)) {
		var_r31 = 2;
	}
	if (((u32)M2C_FIELD(arg0, u32*, 0x18) != 0U)
	    && (fn_80226468((u32*)M2C_FIELD(arg0, u32*, 0x18)) != NULL)) {
		if ((fn_8019D41C(0x120) == -1) && (var_r31 == 2)) {
			var_r31 = 1;
		} else if ((fn_8019D41C(0x12E) == -1) && (var_r31 == 3)) {
			var_r31 = 1;
		}
		fn_8022B308(arg0, var_r31);
	}
	return 1;
}

s32 fn_80225AC8(u8* arg0, s32 unused1, s32 unused2, s32 arg3)
{
	s32 var_r31;

	var_r31 = arg3;
	if (((u32)M2C_FIELD(arg0, u32*, 0x18) != 0U)
	    && (fn_80226468((u32*)M2C_FIELD(arg0, u32*, 0x18)) != NULL)) {
		if ((fn_8019D41C(0x120) == -1) && (var_r31 == 2)) {
			var_r31 = 1;
		} else if ((fn_8019D41C(0x12E) == -1) && (var_r31 == 3)) {
			var_r31 = 1;
		}
		fn_8022B308(arg0, var_r31);
	}
	return 1;
}

s32 fn_80225B60(u8* arg0)
{
	u8* temp_r5;
	s32 temp_r4;
	s32 temp_r5_2;
	s32 temp_r6;
	s32 var_r31;

	var_r31 = 0;
	temp_r5 = M2C_FIELD(arg0, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8));
	if (temp_r5 != NULL) {
		if (!(M2C_FIELD(arg0, s32*, 8) & 0x01000000)) {
			temp_r6   = M2C_FIELD(arg0, s32*, 0x14);
			temp_r5_2 = temp_r6 * 4;
			temp_r4   = temp_r6 * 0x10;
			var_r31   = (s32)((u8*)M2C_FIELD(temp_r5, s32*, 4) + 4);
			var_r31 += temp_r5_2;
			var_r31 += temp_r4;
			var_r31 += M2C_FIELD(temp_r5, s32*, 0) << 6;
			var_r31 += fn_80225400(temp_r5);
		} else {
			var_r31 = fn_80227F48(arg0);
		}
	}
	return var_r31;
}

s32* fn_80225BF0(s32* arg0, s32* unused_arg1, s32* arg2)
{
	s32 sp8;
	u8* temp_r31;
	s32 temp_r30;
	s32 temp_r6;
	s32 temp_r7;

	temp_r31 = M2C_FIELD(arg2, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8));
	if (temp_r31 != NULL) {
		if (!(M2C_FIELD(arg2, s32*, 8) & 0x01000000)) {
			temp_r6  = M2C_FIELD(temp_r31, s32*, 0x10);
			temp_r7  = M2C_FIELD(temp_r31, s32*, 0);
			temp_r30 = M2C_FIELD(arg2, s32*, 0x14);
			sp8      = ((((temp_r6 << 0x10) & 0xFF0000 & ~0xFF00)
			                | ((M2C_FIELD(temp_r31, s32*, 4) << 8) & 0xFF00))
			               & ~0xFF)
			    | (temp_r7 & 0xFF);
			if (fn_80193474(arg0, &sp8, 4) == 0U) {
				return NULL;
			}
			if (fn_80197B48(arg0, M2C_FIELD(temp_r31, s32*, 8), M2C_FIELD(temp_r31, s32*, 4))
			    == 0U) {
				return NULL;
			}
			if (fn_80193474(arg0, M2C_FIELD(temp_r31, s32**, 0x14), temp_r30 * 4) == 0U) {
				return NULL;
			}
			if (fn_8019336C(arg0, M2C_FIELD(temp_r31, s32*, 0x18), temp_r30 * 0x10) == 0U) {
				return NULL;
			}
			if (fn_8019336C(arg0, M2C_FIELD(temp_r31, s32*, 0xC), M2C_FIELD(temp_r31, s32*, 0) << 6)
			    == 0U) {
				return NULL;
			}
			if (fn_80225164(arg0, temp_r31) == NULL) {
				return NULL;
			}
			goto block_16;
		}
		if (fn_80228014(arg0, (u8*)arg2) == NULL) {
			return NULL;
		}
		goto block_16;
	}
block_16:
	return arg0;
}

u32* fn_80225D48(u32* arg0, s32 arg1, u32* arg2, s32 arg3, s32 arg4)
{
	u32 sp8;
	s32 var_r11;
	s32 var_r27;
	s32 var_r4;
	s32* var_r27_2;
	u32* var_r10;
	u32* var_r12;
	u32* var_r6;
	u32* var_r7;
	u32 temp_r0;
	u32 temp_r26_2;
	u32 temp_r30;
	u32 temp_r4;
	u32 var_i;
	u32 var_j;
	u32 var_r26;
	u32 var_r5;
	u32 var_r7_2;
	u32 var_r8;
	u8* temp_r9;
	u8 temp_r26;
	u8 temp_r4_2;
	u8 temp_r27;
	u8* var_r29;

	if (!(M2C_FIELD(arg2, s32*, 8) & 0x01000000)) {
		if (fn_80193884(arg0, (s32*)&sp8, 4) == 0U) {
			return NULL;
		}
		temp_r30  = M2C_FIELD(arg2, u32*, 0x14);
		temp_r26  = (u8)(sp8 >> 0x10U);
		temp_r4_2 = (u8)sp8;
		temp_r27  = (u8)(sp8 >> 8U);
		if (temp_r26 == 0) {
			var_r29 = fn_80225434(temp_r30, (u32)temp_r4_2, (u32)temp_r4_2, 4U, NULL, NULL, NULL);
			if (var_r29 == NULL) {
				return NULL;
			}
		} else {
			var_r29 = fn_80225434(
			    temp_r30, (u32)temp_r4_2, (u32)temp_r27, (u32)temp_r26, NULL, NULL, NULL);
			if (var_r29 == NULL) {
				return NULL;
			}
			if (temp_r27 != fn_801979AC(arg0, M2C_FIELD(var_r29, s32*, 8), temp_r27)) {
				return NULL;
			}
		}
		if (fn_80193884(arg0, M2C_FIELD(var_r29, s32**, 0x14), temp_r30 * 4) == 0U) {
			return NULL;
		}
		if (fn_801937A0(arg0, M2C_FIELD(var_r29, u32**, 0x18), temp_r30 * 0x10) == 0U) {
			return NULL;
		}
		if (temp_r26 == 0) {
			for (var_r26 = 0U, var_r27 = 0; var_r26 < (u32)M2C_FIELD(var_r29, u32*, 0);
			    var_r27 += 0x40, var_r26 += 1) {
				if (fn_80197D70(arg0, 4) == 0U) {
					return NULL;
				}
				if (fn_801937A0(arg0, (u32*)(M2C_FIELD(var_r29, s32*, 0xC) + var_r27), 0x40)
				    == 0U) {
					return NULL;
				}
			}
			var_r7                         = M2C_FIELD(var_r29, u32**, 0x18);
			var_r5                         = 0U;
			M2C_FIELD(var_r29, u32*, 0x10) = 1U;
			for (; var_r5 < temp_r30; var_r5 += 1, var_r7 += 4) {
				temp_r4 = M2C_FIELD(var_r29, u32*, 0x10);
				var_r6  = &var_r7[temp_r4];
				for (var_i = temp_r4; var_i < 4U; var_i += 1, var_r6 += 1) {
					if ((u32)*var_r6 == 0U) {
						break;
					}
					M2C_FIELD(var_r29, u32*, 0x10) = (u32)(M2C_FIELD(var_r29, u32*, 0x10) + 1);
					if ((u32)M2C_FIELD(var_r29, u32*, 0x10) == 4U) {
						goto block_42;
					}
				}
			}
		block_42:
			var_r12                     = M2C_FIELD(var_r29, u32**, 0x18);
			var_r8                      = 0U;
			var_r27_2                   = M2C_FIELD(var_r29, s32**, 0x14);
			temp_r9                     = M2C_FIELD(var_r29, u8**, 8);
			M2C_FIELD(var_r29, u32*, 4) = 0U;
			for (; var_r8 < temp_r30; var_r8 += 1, var_r12 += 4, var_r27_2 += 1) {
				var_r10 = var_r12;
				var_r11 = 0;
				for (var_r7_2 = 0U; var_r7_2 < (u32)M2C_FIELD(var_r29, u32*, 0x10);
				    var_r7_2 += 1, var_r10 += 1, var_r11 += 8) {
					if ((u32)*var_r10 == 0U) {
						continue;
					}
					temp_r0    = (u32)*var_r27_2 >> var_r11;
					temp_r26_2 = M2C_FIELD(var_r29, u32*, 4);
					var_r4     = 1;
					for (var_j = 0U; var_j < temp_r26_2; var_j += 1) {
						if ((u8)temp_r0 == (u8)temp_r9[var_j]) {
							var_r4 = 0;
							break;
						}
					}
					if (var_r4 != 0) {
						temp_r9[temp_r26_2]         = (u8)temp_r0;
						M2C_FIELD(var_r29, u32*, 4) = (u32)(M2C_FIELD(var_r29, u32*, 4) + 1);
					}
				}
			}
			goto block_47;
		}
		M2C_FIELD(var_r29, u32*, 0x10) = (u32)temp_r26;
		if (fn_801937A0(arg0, M2C_FIELD(var_r29, u32**, 0xC), M2C_FIELD(var_r29, u32*, 0) << 6)
		    == 0U) {
			return NULL;
		}
		if (fn_80225248(arg0, var_r29) == NULL) {
			return NULL;
		}
	block_47:
		fn_8022647C(arg2, var_r29);
		goto block_50;
	}
	if (fn_8022824C(arg0, arg2) == NULL) {
		return NULL;
	}
block_50:
	return arg0;
}

u32* fn_80226080(u32* arg0, s32 arg1, u8* arg2, s32 arg3, s32 arg4)
{
	s32 sp8;
	s32 var_r11;
	s32 var_r27;
	s32 var_r4;
	s32* var_r27_2;
	u32* temp_r30;
	u32* var_r10;
	u32* var_r12;
	u32* var_r6;
	u32* var_r7;
	u32 temp_r0;
	u32 temp_r26;
	u32 temp_r29;
	u32 temp_r4;
	u32 var_i;
	u32 var_j;
	u32 var_r26;
	u32 var_r5;
	u32 var_r7_2;
	u32 var_r8;
	u8* temp_r31;
	u8* temp_r9;

	temp_r30 = M2C_FIELD(arg2, u32**, 0x18);
	if (fn_80226468(temp_r30) == NULL) {
		if (fn_80193884(arg0, &sp8, 4) == 0U) {
			return NULL;
		}
		temp_r29 = M2C_FIELD(temp_r30, u32*, 0x14);
		temp_r31 = fn_80225434(temp_r29, (u32)sp8, (u32)sp8, 4U, NULL, NULL, NULL);
		if (fn_80197D70(arg0, 4) == 0U) {
			return NULL;
		}
		if (fn_80193884(arg0, M2C_FIELD(temp_r31, s32**, 0x14), temp_r29 * 4) == 0U) {
			return NULL;
		}
		if (fn_801937A0(arg0, M2C_FIELD(temp_r31, u32**, 0x18), temp_r29 * 0x10) == 0U) {
			return NULL;
		}
		for (var_r26 = 0U, var_r27 = 0; var_r26 < (u32)M2C_FIELD(temp_r31, u32*, 0);
		    var_r27 += 0x40, var_r26 += 1) {
			if (fn_80197D70(arg0, 0xC) == 0U) {
				return NULL;
			}
			if (fn_801937A0(arg0, (u32*)(M2C_FIELD(temp_r31, s32*, 0xC) + var_r27), 0x40) == 0U) {
				return NULL;
			}
		}
		var_r7                          = M2C_FIELD(temp_r31, u32**, 0x18);
		var_r5                          = 0U;
		M2C_FIELD(temp_r31, u32*, 0x10) = 1U;
		for (; var_r5 < temp_r29; var_r5 += 1, var_r7 += 4) {
			temp_r4 = M2C_FIELD(temp_r31, u32*, 0x10);
			var_r6  = &var_r7[temp_r4];
			for (var_i = temp_r4; var_i < 4U; var_i += 1, var_r6 += 1) {
				if ((u32)*var_r6 == 0U) {
					break;
				}
				M2C_FIELD(temp_r31, u32*, 0x10) = (u32)(M2C_FIELD(temp_r31, u32*, 0x10) + 1);
				if ((u32)M2C_FIELD(temp_r31, u32*, 0x10) == 4U) {
					goto block_36;
				}
			}
		}
	block_36:
		var_r12                      = M2C_FIELD(temp_r31, u32**, 0x18);
		var_r8                       = 0U;
		var_r27_2                    = M2C_FIELD(temp_r31, s32**, 0x14);
		temp_r9                      = M2C_FIELD(temp_r31, u8**, 8);
		M2C_FIELD(temp_r31, u32*, 4) = 0U;
		for (; var_r8 < temp_r29; var_r8 += 1, var_r12 += 4, var_r27_2 += 1) {
			var_r10 = var_r12;
			var_r11 = 0;
			for (var_r7_2 = 0U; var_r7_2 < (u32)M2C_FIELD(temp_r31, u32*, 0x10);
			    var_r7_2 += 1, var_r10 += 1, var_r11 += 8) {
				if ((u32)*var_r10 == 0U) {
					continue;
				}
				temp_r0  = (u32)*var_r27_2 >> var_r11;
				temp_r26 = M2C_FIELD(temp_r31, u32*, 4);
				var_r4   = 1;
				for (var_j = 0U; var_j < temp_r26; var_j += 1) {
					if ((u8)temp_r0 == (u8)temp_r9[var_j]) {
						var_r4 = 0;
						break;
					}
				}
				if (var_r4 != 0) {
					temp_r9[temp_r26]            = (u8)temp_r0;
					M2C_FIELD(temp_r31, u32*, 4) = (u32)(M2C_FIELD(temp_r31, u32*, 4) + 1);
				}
			}
		}
		fn_8022647C(temp_r30, temp_r31);
		goto block_39;
	}
	if (fn_80197D70(arg0, arg4) == 0U) {
		return NULL;
	}
block_39:
	return arg0;
}

void fn_8022632C(void) { }

s32 fn_80226330(void)
{
	return 0;
}

s32 fn_80226338(void)
{
	M2C_FIELD(lbl_8029BB30, s32*, 0) = RwEngineRegisterPlugin(0, 0x116, fn_802257A8, fn_802258A4);
	M2C_FIELD(lbl_8029BB30, s32*, 4) = fn_801520D0(4, 0x116, fn_802259B4, fn_802259CC, fn_802259F0);
	fn_80152150(0x116, fn_80226080, fn_8022632C, fn_80226330, (M2C_UNK*)lbl_8029BB30);
	fn_8015218C(0x116, fn_80225A08);
	fn_801521C0(0x116, fn_80225AC8);
	M2C_FIELD(lbl_8029BB30, s32*, 8) = fn_80152FDC(4, 0x116, fn_80225930, fn_80225948, fn_802259B0);
	fn_8015301C(0x116, fn_80225D48, fn_80225BF0, fn_80225B60, (M2C_UNK*)lbl_8029BB30);
	return 1;
}

void fn_80226440(s32 arg0, s32 arg1)
{
	M2C_FIELD(arg0, s32*, M2C_FIELD(lbl_8029BB30, s32*, 4)) = arg1;
}

s32 fn_80226454(s32 arg0)
{
	return M2C_FIELD(arg0, s32*, M2C_FIELD(lbl_8029BB30, s32*, 4));
}

u8* fn_80226468(u32* arg0)
{
	return M2C_FIELD(arg0, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8));
}

#pragma dont_inline on
u32* fn_8022647C(u32* arg0, u8* arg1)
{
	u8* temp_r0;

	temp_r0 = M2C_FIELD(arg0, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8));
	if (arg1 != temp_r0) {
		if (temp_r0 != NULL) {
			fn_80227DF0((s32)arg0);
		}
		M2C_FIELD(arg0, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8)) = arg1;
		if ((arg1 != NULL) && (fn_80227D54(arg0) == NULL)) {
			return NULL;
		}
		goto block_6;
	}
block_6:
	return arg0;
}
#pragma dont_inline reset

u8* fn_80226508(u8* arg0)
{
	if ((u32)M2C_FIELD(arg0, u32*, 0x48) != 0U) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(M2C_FIELD(arg0, u32*, 0x48));
	}
	fn_80225100(arg0);
	M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x148)(
	    M2C_FIELD(lbl_8029BB30, s32*, 0x18), arg0, lbl_8029BB30);
	return 0;
}

s32 fn_80226578(u8* arg0)
{
	return M2C_FIELD(arg0, s32*, 0x14);
}

void fn_80226580(u8* arg0, s32 arg1)
{
	s32 var_r31;

	var_r31 = arg1;
	if ((fn_8019D41C(0x120) == -1) && (var_r31 == 2)) {
		var_r31 = 1;
	} else if ((fn_8019D41C(0x12E) == -1) && (var_r31 == 3)) {
		var_r31 = 1;
	}
	fn_8022B308(arg0, var_r31);
}

void fn_802265FC(u8* arg0)
{
	u8* temp_r3;
	u8* temp_r4;
	u8* temp_r4_2;
	u8* var_r3;

	if ((u16)M2C_FIELD(arg0, u16*, 0x18) == (u16)lbl_8042BE88) {
		GXSetDrawSync(lbl_8042BE88);
		lbl_8042BE88 = (lbl_8042BE88 + 1) % 57344;
	}
	do {

	} while (fn_801B2894(M2C_FIELD(arg0, u16*, 0x18)) == 0);
	temp_r3 = M2C_FIELD(arg0, u8**, 0x24);
	if (temp_r3 != NULL) {
		fn_80197384(M2C_FIELD(temp_r3, s32*, -4));
	}
	temp_r4 = M2C_FIELD(arg0, u8**, 0xC);
	if ((u8)M2C_FIELD(temp_r4, u8*, 0) == 1) {
		temp_r4_2                   = M2C_FIELD(temp_r4, u8**, 0x18);
		var_r3                      = M2C_FIELD(temp_r4_2, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8));
		M2C_FIELD(arg0, u8**, 0x24) = (u8*)M2C_FIELD(var_r3, u8**, 0x1C);
		if (M2C_FIELD(temp_r4_2, s32*, 8) & 0x10) {
			M2C_FIELD(arg0, s32*, 0x2C) = (s32)M2C_FIELD(var_r3, s32*, 0x20);
		}
	} else {
		var_r3                      = M2C_FIELD(temp_r4, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8));
		M2C_FIELD(arg0, u8**, 0x24) = (u8*)M2C_FIELD(var_r3, u8**, 0x1C);
		if (M2C_FIELD(temp_r4, s32*, 8) & 0x10) {
			M2C_FIELD(arg0, s32*, 0x2C) = (s32)M2C_FIELD(var_r3, s32*, 0x20);
		}
	}
	M2C_FIELD(var_r3, s32*, 0x1C) = 0;
	M2C_FIELD(var_r3, s32*, 0x20) = 0;
	GXInvalidateVtxCache();
}

void fn_80226718(u8* arg0)
{
	if ((u16)M2C_FIELD(arg0, u16*, 0x18) == (u16)lbl_8042BE88) {
		GXSetDrawSync(lbl_8042BE88);
		lbl_8042BE88 = (lbl_8042BE88 + 1) % 57344;
	}
	do {

	} while (fn_801B2894(M2C_FIELD(arg0, u16*, 0x18)) == 0);
	GXInvalidateVtxCache();
}

s32 fn_802267A4(u8* arg0, u8* arg1, u8* arg2, u8** arg3)
{
	s32 sp8[5];
	s32 temp_r3_3;
	s32 temp_r4_2;
	s32 temp_r8;
	s32 var_r3;
	s32 var_r5;
	u32 var_r0;
	u8** temp_r3_4;
	u8** temp_r3_5;
	u8** temp_r3_6;
	u8* temp_r0;
	u8* temp_r0_2;
	u8* temp_r10;
	u8* temp_r31;
	u8* temp_r3;
	u8* temp_r3_2;
	u8* temp_r4;
	u8* temp_r7;

	temp_r7  = *arg3;
	temp_r31 = M2C_FIELD(arg1, u8**, 0x18);
	temp_r0  = M2C_FIELD(temp_r7, u8**, 0);
	if (temp_r0 != NULL) {
		*M2C_FIELD(temp_r7, u8***, 4)                    = temp_r0;
		temp_r4                                          = *arg3;
		M2C_FIELD(M2C_FIELD(temp_r4, u8**, 0), u8***, 4) = (u8**)M2C_FIELD(temp_r4, u8***, 4);
		M2C_FIELD(*arg3, u8**, 0)                        = *RW_LINK_HEAD;
		M2C_FIELD(*arg3, u8***, 4)                       = RW_LINK_HEAD;
		M2C_FIELD(*RW_LINK_HEAD, u8**, 4)                = *arg3;
		*RW_LINK_HEAD                                    = *arg3;
	}
	M2C_FIELD(*arg3, void (**)(), 0x14) = fn_802265FC;
	if ((u8*)M2C_FIELD(arg0, u8**, 0x1C) == NULL) {
		M2C_FIELD(arg0, u8**, 0x1C) = (u8*)M2C_FIELD(arg2, u8**, 0xC);
		M2C_FIELD(arg2, u8**, 0xC)  = NULL;
		if (M2C_FIELD(temp_r31, s32*, 8) & 0x10) {
			M2C_FIELD(arg0, u8**, 0x20) = (u8*)M2C_FIELD(arg2, u8**, 0x14);
			M2C_FIELD(arg2, u8**, 0x14) = NULL;
		}
	}
	temp_r3 = M2C_FIELD(arg2, u8**, 0xC);
	if (temp_r3 != NULL) {
		if (fn_801B2894(M2C_FIELD(M2C_FIELD(temp_r3, u8***, -4), u16*, 0x18)) == 0) {
			M2C_FIELD(M2C_FIELD(M2C_FIELD(arg2, u8**, 0xC), u8***, -4), s32*, 0x10) = 0;
			M2C_FIELD(arg2, u8**, 0xC)                                              = NULL;
			if (M2C_FIELD(temp_r31, s32*, 8) & 0x10) {
				M2C_FIELD(arg2, u8**, 0x14) = NULL;
			}
		} else {
			GXInvalidateVtxCache();
		}
	}
	temp_r3_2 = M2C_FIELD(arg2, u8**, 0xC);
	if (temp_r3_2 == NULL) {
		temp_r10 = M2C_FIELD(temp_r31, u8**, lbl_8042C930);
		if (temp_r10 != NULL) {
			sp8[0]  = M2C_FIELD(lbl_80240648, s32*, 0);
			temp_r8 = M2C_FIELD(temp_r31, s32*, 0x14);
			sp8[1]  = M2C_FIELD(lbl_80240648, s32*, 4);
			sp8[2]  = M2C_FIELD(lbl_80240648, s32*, 8);
			sp8[3]  = M2C_FIELD(lbl_80240648, s32*, 0xC);
			sp8[4]  = M2C_FIELD(lbl_80240648, s32*, 0x10);
			var_r5  = (((temp_r8 * sp8[M2C_FIELD(temp_r10, u8*, 0)]) + 0x1F) & 0xFFFFFFE0) + 6;
			if (M2C_FIELD(temp_r31, s32*, 8) & 0x10) {
				temp_r4_2 = sp8[M2C_FIELD(temp_r10, u8*, 1)];
				var_r3    = 1;
				if ((u8)M2C_FIELD(temp_r10, u8*, 0xD) != 0) {
					var_r3 = 3;
				}
				var_r5 += ((temp_r8 * (temp_r4_2 * var_r3)) + 0x1F) & 0xFFFFFFE0;
			}
		} else {
			temp_r3_3 = ((M2C_FIELD(temp_r31, s32*, 0x14) * 0xC) + 0x1F) & 0xFFFFFFE0;
			var_r5    = temp_r3_3 + 6;
			if (M2C_FIELD(temp_r31, s32*, 8) & 0x10) {
				var_r5 += temp_r3_3;
			}
		}
		temp_r3_4 = fn_801974E0(arg1, arg2 + 0xC, var_r5, fn_80226718);
		if ((s32)M2C_FIELD(temp_r31, s32*, 0x18) == 1) {
			var_r0 = M2C_FIELD(temp_r31, u32*, 0x58);
		} else {
			var_r0 = M2C_FIELD(arg1, u32*, 0x14);
		}
		if ((temp_r3_4 == NULL) || (var_r0 == 0U)) {
			if (temp_r3_4 != NULL) {
				fn_80197384((s32)temp_r3_4);
			}
			return 0;
		}
		M2C_FIELD(arg2, u8**, 0xC) = (u8*)((s32)(M2C_FIELD(arg2, u8**, 0xC) + 0x3D) & 0xFFFFFFE0);
		if (M2C_FIELD(temp_r31, s32*, 8) & 0x10) {
			M2C_FIELD(arg2, u8**, 0x14) = (u8*)(M2C_FIELD(arg2, u8**, 0xC)
			    + (((M2C_FIELD(temp_r31, s32*, 0x14) * M2C_FIELD(arg2, u8*, 0x11)) + 0x1F)
			        & 0xFFFFFFE0));
		}
		M2C_FIELD(M2C_FIELD(arg2, u8**, 0xC), u8***, -4) = temp_r3_4;
		goto block_31;
	}
	temp_r3_5 = M2C_FIELD(temp_r3_2, u8***, -4);
	temp_r0_2 = M2C_FIELD(temp_r3_5, u8**, 0);
	if (temp_r0_2 != NULL) {
		*M2C_FIELD(temp_r3_5, u8***, 4) = temp_r0_2;
		temp_r3_6                       = M2C_FIELD(M2C_FIELD(arg2, u8**, 0xC), u8***, -4);
		M2C_FIELD(M2C_FIELD(temp_r3_6, u8**, 0), s32*, 4) = (s32)M2C_FIELD(temp_r3_6, s32*, 4);
		*M2C_FIELD(M2C_FIELD(arg2, u8**, 0xC), u8***, -4) = *RW_LINK_HEAD;
		M2C_FIELD(M2C_FIELD(M2C_FIELD(arg2, u8**, 0xC), u8***, -4), s32*, 4) = (s32)RW_LINK_HEAD;
		M2C_FIELD(*RW_LINK_HEAD, u8***, 4) = M2C_FIELD(M2C_FIELD(arg2, u8**, 0xC), u8***, -4);
		*RW_LINK_HEAD                      = (u8*)M2C_FIELD(M2C_FIELD(arg2, u8**, 0xC), u8***, -4);
	}
block_31:
	M2C_FIELD(M2C_FIELD(M2C_FIELD(arg2, u8**, 0xC), u8***, -4), u16*, 0x18) = (u16)lbl_8042BE88;
	return 1;
}

void fn_80226B2C(s32 arg0, u8* arg1, M2C_UNK* arg2, u8* arg3)
{
	M2C_UNK spC8[16];
	M2C_UNK sp88[16];
	M2C_UNK sp48[16];
	M2C_UNK sp8[16];
	M2C_UNK* var_r29;
	M2C_UNK* var_r6;
	s32 temp_r23;
	s32 temp_r29;
	s32 temp_r3;
	s32 temp_r5;
	u32 temp_r24;
	u32 temp_r25;
	u32 var_r23;
	u32 var_r30;
	u8* var_r25;
	u8* var_r27;
	u8* var_r27_2;
	u8* var_r31;
	u8* temp_r4;

	if (arg3 != NULL) {
		temp_r3 = M2C_FIELD(arg3, s32*, 0);
		if (temp_r3 & 2) {
			if (((u32)M2C_FIELD(arg1, u32*, 0x10) > 1U)
			    || ((u32)M2C_FIELD(arg1, u32*, 0x2C) == 3U)) {
				spC8[3] = 0;
				fn_80195B5C(spC8, arg2);
				var_r29 = spC8;
			} else {
				var_r29 = lbl_803EDB8C;
			}
			var_r31  = M2C_FIELD(arg1, u8**, 8);
			var_r30  = 0U;
			temp_r23 = M2C_FIELD(arg1, s32*, 0xC);
			temp_r24 = M2C_FIELD(arg1, u32*, 4);
			var_r25  = var_r31;
			var_r27  = var_r31;
		loop_8:
			if (var_r30 < temp_r24) {
				sp88[3] = 0;
				temp_r4 = M2C_FIELD(arg3, u8**, 0x10);
				fn_80195674(sp88, (M2C_UNK*)(temp_r23 + (*var_r25 << 6)),
				    fn_8019E8EC(M2C_FIELD(temp_r4, s32*, (*var_r31 * 0x10) + 0xC)));
				fn_80195674((M2C_UNK*)(arg0 + (*var_r27 << 6)), sp88, (M2C_UNK*)var_r29);
				var_r30 += 1;
				var_r27 += 1;
				var_r25 += 1;
				var_r31 += 1;
				goto loop_8;
			}
			return;
		}
		if (temp_r3 & 0x4000) {
			if (((u32)M2C_FIELD(arg1, u32*, 0x10) > 1U)
			    || ((u32)M2C_FIELD(arg1, u32*, 0x2C) == 3U)) {
				var_r23   = 0U;
				temp_r29  = M2C_FIELD(arg1, s32*, 0xC);
				temp_r25  = M2C_FIELD(arg1, u32*, 4);
				var_r27_2 = M2C_FIELD(arg1, u8**, 8);
			loop_15:
				if (var_r23 < temp_r25) {
					temp_r5 = *var_r27_2 << 6;
					fn_80195674((M2C_UNK*)(arg0 + temp_r5), (M2C_UNK*)(temp_r29 + temp_r5),
					    (M2C_UNK*)(M2C_FIELD(arg3, s32*, 8) + temp_r5));
					var_r23 += 1;
					var_r27_2 += 1;
					goto loop_15;
				}
				return;
			}
			sp48[3] = 0;
			fn_80195674(sp48, arg2, lbl_803EDB8C);
			fn_8022A454(arg0, M2C_FIELD(arg1, s32*, 0xC), M2C_FIELD(arg3, s32*, 8), sp48,
			    M2C_FIELD(arg1, u8**, 8), M2C_FIELD(arg1, u32*, 4));
			return;
		}
		if (((u32)M2C_FIELD(arg1, u32*, 0x10) > 1U) || ((u32)M2C_FIELD(arg1, u32*, 0x2C) == 3U)) {
			sp8[3] = 0;
			fn_80195B5C(sp8, arg2);
			var_r6 = sp8;
		} else {
			var_r6 = lbl_803EDB8C;
		}
		fn_8022A454(arg0, M2C_FIELD(arg1, s32*, 0xC), M2C_FIELD(arg3, s32*, 8), var_r6,
		    M2C_FIELD(arg1, u8**, 8), M2C_FIELD(arg1, u32*, 4));
	}
}

void fn_80226D3C(u8* arg0, s32 arg1, u32 arg2, s32 arg3, u8* arg4, s32 arg5)
{
	u8 sp1C[5];
	u8 sp14[5];
	u8 spC[5];
	s32 sp8;
	s32 temp_r0;
	s32 temp_r19;
	s32 var_r19;
	s32 var_r20;
	s32 var_r20_2;
	s32 var_r21_2;
	s32 var_r22;
	s32 var_r23;
	s32 var_r28;
	s32 var_r29;
	u32 var_r21;
	u32 var_r22_2;
	register u32 saved_gqr5;
	register u32 new_gqr5;
	register u32 new_gqr6;
	register u32 new_gqr7;
	u8 temp_r4;
	u8 var_r30;
	u8 var_r31;

	new_gqr5 = 0x07040000;
	new_gqr6 = 0;
	new_gqr7 = 0;
	if (arg4 != NULL) {
		temp_r4                  = M2C_FIELD(arg4, u8*, 0xD);
		M2C_FIELD(sp14, s32*, 0) = lbl_80430100;
		sp14[4]                  = lbl_80430104;
		var_r30                  = sp14[M2C_FIELD(arg4, u8*, 1)];
		M2C_FIELD(spC, s32*, 0)  = lbl_80430108;
		var_r29                  = (var_r30 * 6) & ((s32)(-(s32)temp_r4 | temp_r4) >> 0x1F);
		spC[4]                   = lbl_8043010C;
		M2C_FIELD(sp1C, s32*, 0) = lbl_804300F8;
		sp1C[4]                  = lbl_804300FC;
		var_r31                  = sp14[M2C_FIELD(arg4, u8*, 0)];
		new_gqr6                 = sp1C[M2C_FIELD(arg4, u8*, 0)] | (M2C_FIELD(arg4, u8*, 0xC) << 8);
		new_gqr6 |= new_gqr6 << 16;
		new_gqr7 = sp1C[M2C_FIELD(arg4, u8*, 1)] | (spC[M2C_FIELD(arg4, u8*, 1)] << 8);
		new_gqr7 |= new_gqr7 << 16;
	} else {
		var_r31 = 4;
		var_r30 = 4;
		var_r29 = 0;
	}
	asm {
        mfspr saved_gqr5, 917
        mtspr 917, new_gqr5
        mtspr 918, new_gqr6
        mtspr 919, new_gqr7
	}
	sp8 = saved_gqr5;
	if ((u32)M2C_FIELD(arg0, u32*, 0x20) == 0U) {
		M2C_FIELD(arg0, u32*, 0x20) = (u32)M2C_FIELD(arg0, u32*, 0x1C);
	}
	temp_r0 = M2C_FIELD(arg0, s32*, 0x10);
	switch (temp_r0) { /* irregular */
		case 1:
			if ((u32)M2C_FIELD(arg0, u32*, 0x20) != (u32)M2C_FIELD(arg0, u32*, 0x1C)) {
				var_r23 = 0;
				var_r21 = arg2;
				var_r22 = 0;
				var_r20 = arg3;
				for (var_r28 = 0; var_r28 < arg5;
				    var_r23 += 4, var_r22 += 0xC, var_r21 += 0xC, var_r20 += 0xC, var_r28 += 1) {
					temp_r19 = arg1
					    + ((M2C_FIELD(M2C_FIELD(arg0, u32**, 0x14), u32*, var_r23) << 6) & 0x3FC0);
					fn_8019941C(var_r21, M2C_FIELD(arg0, u32*, 0x1C) + var_r22, 1, temp_r19);
					fn_8019947C(var_r20, M2C_FIELD(arg0, u32*, 0x20) + var_r22, 1, temp_r19);
				}
			} else {
				var_r20_2 = 0;
				var_r22_2 = arg2;
				var_r21_2 = 0;
				for (var_r19 = 0; var_r19 < arg5;
				    var_r20_2 += 4, var_r21_2 += 0xC, var_r22_2 += 0xC, var_r19 += 1) {
					fn_8019941C(var_r22_2, M2C_FIELD(arg0, u32*, 0x1C) + var_r21_2, 1,
					    arg1
					        + ((M2C_FIELD(M2C_FIELD(arg0, u32**, 0x14), u32*, var_r20_2) << 6)
					            & 0x3FC0));
				}
			}
			break;
		case 2:
			fn_8022A650(arg0, arg1, arg2, arg5, var_r31, var_r30, var_r29);
			break;
		case 3:
			fn_8022A87C(arg0, arg1, arg2, arg5, var_r31, var_r30, var_r29);
			break;
		case 4:
			fn_8022AB3C(arg0, arg1, arg2, arg5, var_r31, var_r30, var_r29);
			break;
	}
	asm { mtspr 917, saved_gqr5 }
	if ((u32)M2C_FIELD(arg0, u32*, 0x20) == (u32)M2C_FIELD(arg0, u32*, 0x1C))
	{
		M2C_FIELD(arg0, u32*, 0x20) = 0U;
		DCFlushRange(arg2, arg5 * (var_r31 * 3));
		return;
	}
	DCFlushRange(
	    arg2, (((arg5 * (var_r31 * 3)) + 0x1F) & 0xFFFFFFE0) + (arg5 * (var_r29 + (var_r30 * 3))));
}

#pragma dont_inline on
u8* fn_80227018(u8* arg0, s32* arg1)
{
	u32* temp_r30;
	u8* temp_r3;
	u8* var_r4;
	u8* var_r5;
	temp_r30 = M2C_FIELD(arg0, u32**, 0x18);
	temp_r3  = fn_80226468(temp_r30);
	if ((s32)M2C_FIELD(temp_r30, s32*, 0x18) != 1) {
		var_r4 = arg0;
		var_r5 = arg0 + 0x14;
	} else {
		var_r4 = (u8*)temp_r30;
		var_r5 = (u8*)temp_r30 + 0x58;
	}
	if (((u32)M2C_FIELD(temp_r3, u32*, 0x10) > 1U) || ((u32)M2C_FIELD(temp_r3, u32*, 0x2C) == 3U)) {
		if (M2C_FIELD(temp_r30, s32*, 8) & 0x02000000) {
			if ((s32)lbl_8042BD28 == 1) {
				*arg1 = fn_802290F0(temp_r30, var_r4, var_r5);
			} else {
				*arg1 = fn_801659DC(temp_r30, var_r4, var_r5);
			}
		} else {
			*arg1 = fn_801659DC(temp_r30, var_r4, var_r5);
		}
	} else if (M2C_FIELD(temp_r30, s32*, 8) & 0x02000000) {
		if ((s32)lbl_8042BD28 == 1) {
			*arg1 = fn_802290F0(temp_r30, var_r4, var_r5);
		} else {
			*arg1 = fn_8022A028(temp_r30, var_r4, var_r5);
		}
	} else {
		*arg1 = fn_8022A028(temp_r30, var_r4, var_r5);
	}
	M2C_FIELD(temp_r30, s16*, 0xC) = 0;
	return arg0;
}
#pragma dont_inline reset

u8* fn_80227130(u8* arg0, u8** arg1, M2C_UNK arg_sp0)
{
	u8* temp_r31;
	u8* temp_r30;
	u8* temp_r29;
	u8* temp_r28;
	u32 temp_r26;
	s32 temp_r25;
	s32 var_r6;
	u32 temp_r4;

	temp_r30 = arg0;
	temp_r29 = M2C_FIELD(temp_r30, u8**, 0x18);
	temp_r28 = M2C_FIELD(temp_r29, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8));
	if (((u32)M2C_FIELD(temp_r28, u32*, 0x10) > 1U)
	    || ((u32)M2C_FIELD(temp_r28, u32*, 0x2C) == 3U)) {
		temp_r4  = M2C_FIELD(temp_r28, u32*, 0x1C);
		temp_r31 = *arg1 + 0x18;
		if (temp_r4 == 0U) {
			if (!(M2C_FIELD(temp_r29, s32*, 8) & 0x01000000)) {
				lbl_8042CF80(temp_r30, arg1);
			}
			M2C_FIELD(temp_r28, u32*, 0x1C) = (u32)M2C_FIELD(temp_r31, u32*, 0xC);
			M2C_FIELD(temp_r31, u32*, 0xC)  = 0U;
			if (M2C_FIELD(temp_r29, s32*, 8) & 0x10) {
				M2C_FIELD(temp_r28, s32*, 0x20) = (s32)M2C_FIELD(temp_r31, s32*, 0x14);
				M2C_FIELD(temp_r31, s32*, 0x14) = 0;
			}
		} else if (!(M2C_FIELD(temp_r29, s32*, 8) & 0x01000000)) {
			temp_r26                       = M2C_FIELD(temp_r31, u32*, 0xC);
			M2C_FIELD(temp_r31, u32*, 0xC) = temp_r4;
			if (M2C_FIELD(temp_r29, s32*, 8) & 0x10) {
				temp_r25                        = M2C_FIELD(temp_r31, s32*, 0x14);
				M2C_FIELD(temp_r31, s32*, 0x14) = (s32)M2C_FIELD(temp_r28, s32*, 0x20);
				lbl_8042CF80(temp_r30, arg1);
				M2C_FIELD(temp_r31, s32*, 0x14) = temp_r25;
			} else {
				lbl_8042CF80(temp_r30, arg1);
			}
			M2C_FIELD(temp_r31, u32*, 0xC) = temp_r26;
		}
		if (fn_802267A4(temp_r28, temp_r30, temp_r31, arg1) == 0) {
			return NULL;
		}
		fn_80226B2C(M2C_FIELD(lbl_8029BB30, s32*, 0xC), temp_r28,
		    fn_8019E8EC(M2C_FIELD(temp_r30, s32*, 4)),
		    (u8*)M2C_FIELD(temp_r30, s32*, M2C_FIELD(lbl_8029BB30, s32*, 4)));
		if (M2C_FIELD(temp_r29, s32*, 8) & 0x10) {
			var_r6 = M2C_FIELD(temp_r31, s32*, 0x14);
		} else {
			var_r6 = 0;
		}
		fn_80226D3C(temp_r28, M2C_FIELD(lbl_8029BB30, s32*, 0xC), M2C_FIELD(temp_r31, u32*, 0xC),
		    var_r6, M2C_FIELD(temp_r29, u8**, lbl_8042C930), M2C_FIELD(temp_r29, s32*, 0x14));
		goto block_19;
	}
	fn_80226B2C(M2C_FIELD(lbl_8029BB30, s32*, 0xC), temp_r28,
	    fn_8019E8EC(M2C_FIELD(temp_r30, s32*, 4)),
	    (u8*)M2C_FIELD(temp_r30, s32*, M2C_FIELD(lbl_8029BB30, s32*, 4)));
block_19:
	return temp_r30;
}

void fn_80227300(u8* arg0, s32 arg1, u32 arg2)
{
	f32 sp8[12];
	s32 temp_r31;
	s32 temp_r30;

	temp_r31 = arg1;
	temp_r30 = arg2;
	sp8[0]   = -M2C_FIELD(arg0, f32*, 0);
	sp8[1]   = -M2C_FIELD(arg0, f32*, 0x10);
	sp8[2]   = -M2C_FIELD(arg0, f32*, 0x20);
	sp8[3]   = -M2C_FIELD(arg0, f32*, 0x30);
	sp8[4]   = M2C_FIELD(arg0, f32*, 4);
	sp8[5]   = M2C_FIELD(arg0, f32*, 0x14);
	sp8[6]   = M2C_FIELD(arg0, f32*, 0x24);
	sp8[7]   = M2C_FIELD(arg0, f32*, 0x34);
	sp8[8]   = -M2C_FIELD(arg0, f32*, 8);
	sp8[9]   = -M2C_FIELD(arg0, f32*, 0x18);
	sp8[10]  = -M2C_FIELD(arg0, f32*, 0x28);
	sp8[11]  = -M2C_FIELD(arg0, f32*, 0x38);
	GXLoadPosMtxImm(sp8, temp_r31);
	if (temp_r30 != 0) {
		GXLoadNrmMtxImm(sp8, temp_r31);
	}
}

void fn_802273D0(u8* arg0, s32 arg1, s32 arg2, M2C_UNK arg_sp0)
{
	f32 sp8[12];
	s32 temp_r24;
	s32 temp_r4;
	s32 temp_r6;
	s32 var_r29;
	u32 var_r21;
	u8 temp_r23;
	u8 temp_r26;
	u8 temp_r4_2;
	u8 var_r22;
	u8 var_r25;
	u8* temp_r3;
	u8* temp_r5;

	temp_r6  = M2C_FIELD(arg0, s32*, 0x40);
	temp_r4  = arg1 * 2;
	temp_r23 = M2C_FIELD((temp_r6 + temp_r4), u8*, 1);
	var_r22  = 0;
	temp_r24 = (M2C_FIELD(temp_r6, u8*, temp_r4) * 2) & 0xFE;
	for (var_r25 = 0; var_r25 < temp_r23; var_r25 += 1) {
		temp_r3  = (u8*)(temp_r24 + (M2C_FIELD(arg0, s32*, 0x44) + ((var_r25 * 2) & 0x1FE)));
		temp_r26 = M2C_FIELD(temp_r3, u8*, 1);
		var_r29  = M2C_FIELD(temp_r3, u8*, 0) << 6;
		for (var_r21 = 0U; var_r21 < temp_r26; var_r22 += 3, var_r29 += 0x40, var_r21 += 1) {
			temp_r5 = (u8*)(M2C_FIELD(lbl_8029BB30, s32*, 0xC) + var_r29);
			sp8[0]  = -M2C_FIELD(temp_r5, f32*, 0);
			sp8[1]  = -M2C_FIELD(temp_r5, f32*, 0x10);
			sp8[2]  = -M2C_FIELD(temp_r5, f32*, 0x20);
			sp8[3]  = -M2C_FIELD(temp_r5, f32*, 0x30);
			sp8[4]  = M2C_FIELD(temp_r5, f32*, 4);
			sp8[5]  = M2C_FIELD(temp_r5, f32*, 0x14);
			sp8[6]  = M2C_FIELD(temp_r5, f32*, 0x24);
			sp8[7]  = M2C_FIELD(temp_r5, f32*, 0x34);
			sp8[8]  = -M2C_FIELD(temp_r5, f32*, 8);
			sp8[9]  = -M2C_FIELD(temp_r5, f32*, 0x18);
			sp8[10] = -M2C_FIELD(temp_r5, f32*, 0x28);
			sp8[11] = -M2C_FIELD(temp_r5, f32*, 0x38);
			GXLoadPosMtxImm(sp8, var_r22);
			if (arg2 != 0) {
				GXLoadNrmMtxImm(sp8, var_r22);
			}
		}
	}
}

#pragma dont_inline on
u8* fn_80227528(u8* arg0, u8* arg1, M2C_UNK arg_sp0)
{
	f32 sp8[12];
	f32 sp38[12];
	f32 sp68[12];
	M2C_UNK (*temp_r28)(u8*, u8*, u8*, f32);
	M2C_UNK* temp_r15;
	s32** temp_r15_2;
	s32* temp_r4_3;
	s32 temp_cr0_eq;
	s32 temp_cr0_eq_2;
	s32 temp_r18;
	s32 temp_r3_6;
	s32 temp_r18_2;
	s32 temp_r20;
	s32 temp_r22;
	s32 temp_r4_4;
	s32 var_r15;
	s32 var_r15_2;
	u32 var_r31;
	u32* temp_r5;
	u32 temp_r6;
	u32 var_r16;
	u32 var_r19_2;
	u32 var_r23;
	u8 temp_r16_2;
	u8 temp_r17;
	u8 temp_r21;
	u8 temp_r21_2;
	u8 var_r18;
	u8 var_r19;
	u8 var_r20;
	u8 var_r22;
	u8 var_r23_2;
	u8* temp_r16;
	u8* temp_r3;
	u8* temp_r3_2;
	u8* temp_r3_3;
	u8* temp_r3_4;
	u8* temp_r3_5;
	u8* temp_r4;
	u8* temp_r4_2;
	u8* temp_r5_2;
	u8* temp_r5_3;
	u8* temp_r5_4;
	u8* temp_r5_5;
	u8* temp_r5_6;
	u8* var_r29;
	u8* var_r30;

	temp_r4                        = M2C_FIELD(arg1, u8**, 0);
	temp_r16                       = temp_r4 + 0x18;
	M2C_FIELD(temp_r4, u16*, 0x18) = (u16)lbl_8042BE88;
	var_r30                        = temp_r16 + ((M2C_FIELD(temp_r4, s32*, 0x20) - 1) * 8) + 0x14;
	temp_r5                        = M2C_FIELD(arg0, u32**, 0x18);
	temp_r15                       = fn_8019E8EC(M2C_FIELD(arg0, s32*, 4));
	fn_8015C3A4((s32)M2C_FIELD(temp_r5, u8**, lbl_8042C930), arg1, temp_r5);
	temp_r3 = fn_80226468(M2C_FIELD(arg0, u32**, 0x18));
	if (((u32)M2C_FIELD(temp_r3, u32*, 0x10) > 1U) || ((u32)M2C_FIELD(temp_r3, u32*, 0x2C) == 3U)) {
		fn_801AD0AC(temp_r15, ((u32)M2C_FIELD(arg1, u32*, 8) >> 4U) & 1);
	} else {
		GXSetVtxDesc(0, 1);
	}
	if ((u32)M2C_FIELD(M2C_FIELD(arg0, u32**, 0x18), u8**, lbl_8042C930) == 0U) {
		fn_8015C590();
	}
	temp_r28  = fn_8015ECF4(M2C_FIELD(arg1, u32*, 8), M2C_FIELD(arg1, s32*, 0x20),
	    M2C_FIELD(arg1, s32*, 0x1C), M2C_FIELD(temp_r16, s32*, 4) & 1);
	temp_r4_2 = M2C_FIELD(arg1, u8**, 4);
	var_r31   = M2C_FIELD(temp_r4_2, u16*, 4);
	var_r29   = temp_r4_2 + 0x10;
	if (((u32)M2C_FIELD(temp_r3, u32*, 0x10) == 1U)
	    && ((u32)M2C_FIELD(temp_r3, u32*, 0x34) == 0U)) {
		for (var_r16 = 0U, var_r18 = 0; var_r16 < (u32)M2C_FIELD(temp_r3, u32*, 4);
		    var_r18 += 3, var_r16 += 1) {
			temp_r6   = M2C_FIELD(arg1, u32*, 8);
			temp_r5_2 = (u8*)(M2C_FIELD(lbl_8029BB30, s32*, 0xC)
			    + (M2C_FIELD(M2C_FIELD(temp_r3, u32**, 8), u32*, var_r16) << 6));
			sp68[0]   = -M2C_FIELD(temp_r5_2, f32*, 0);
			sp68[1]   = -M2C_FIELD(temp_r5_2, f32*, 0x10);
			sp68[2]   = -M2C_FIELD(temp_r5_2, f32*, 0x20);
			sp68[3]   = -M2C_FIELD(temp_r5_2, f32*, 0x30);
			sp68[4]   = M2C_FIELD(temp_r5_2, f32*, 4);
			sp68[5]   = M2C_FIELD(temp_r5_2, f32*, 0x14);
			sp68[6]   = M2C_FIELD(temp_r5_2, f32*, 0x24);
			sp68[7]   = M2C_FIELD(temp_r5_2, f32*, 0x34);
			sp68[8]   = -M2C_FIELD(temp_r5_2, f32*, 8);
			sp68[9]   = -M2C_FIELD(temp_r5_2, f32*, 0x18);
			sp68[10]  = -M2C_FIELD(temp_r5_2, f32*, 0x28);
			sp68[11]  = -M2C_FIELD(temp_r5_2, f32*, 0x38);
			GXLoadPosMtxImm(sp68, var_r18);
			if ((s32)((temp_r6 >> 4U) & 1) != 0) {
				GXLoadNrmMtxImm(sp68, var_r18);
			}
		}
	}
	if (M2C_FIELD(arg1, u32*, 8) & 0x84) {
		while (temp_cr0_eq = var_r31 == 0, var_r31 -= 1, temp_cr0_eq == 0) {
			temp_r15_2 = M2C_FIELD(M2C_FIELD(var_r29, u8**, 8), s32***, 0);
			fn_801B1D0C(temp_r15_2, 0);
			if (temp_r15_2 != NULL) {
				temp_r4_3 = *temp_r15_2;
				if (temp_r4_3 != NULL) {
					temp_r4_4 = *temp_r4_3;
					temp_r3_6 = lbl_8042CA48 + 0x14;
					fn_801AF914((M2C_FIELD(temp_r4_4, u32*, temp_r3_6) & 1) ^ 1, (s32)temp_r4_4);
				}
			}
			if (temp_r28 != NULL) {
				temp_r5_3 = M2C_FIELD(var_r29, u8**, 8);
				temp_r28(arg1 + 0xC, temp_r5_3 + 4, temp_r5_3, M2C_FIELD(temp_r5_3, f32*, 0xC));
			}
			if (((u32)M2C_FIELD(temp_r3, u32*, 0x10) == 1U)
			    && ((u32)M2C_FIELD(temp_r3, u32*, 0x34) != 0U)) {
				var_r22   = 0;
				temp_r18  = ((u32)M2C_FIELD(arg1, u32*, 8) >> 4U) & 1;
				temp_r3_2 = (u8*)(M2C_FIELD(temp_r3, s32*, 0x40)
				    + ((M2C_FIELD(M2C_FIELD(arg1, u8**, 4), u16*, 4) - (var_r31 + 1)) * 2));
				temp_r21  = M2C_FIELD(temp_r3_2, u8*, 1);
				temp_r20  = (M2C_FIELD(temp_r3_2, u8*, 0) * 2) & 0xFE;
				for (var_r19 = 0; var_r19 < temp_r21; var_r19 += 1) {
					temp_r3_3  = (u8*)(temp_r20
					    + (M2C_FIELD(temp_r3, s32*, 0x44) + ((var_r19 * 2) & 0x1FE)));
					temp_r16_2 = M2C_FIELD(temp_r3_3, u8*, 1);
					var_r15    = M2C_FIELD(temp_r3_3, u8*, 0) << 6;
					for (var_r23 = 0U; var_r23 < temp_r16_2;
					    var_r22 += 3, var_r15 += 0x40, var_r23 += 1) {
						temp_r5_4 = (u8*)(M2C_FIELD(lbl_8029BB30, s32*, 0xC) + var_r15);
						sp38[0]   = -M2C_FIELD(temp_r5_4, f32*, 0);
						sp38[1]   = -M2C_FIELD(temp_r5_4, f32*, 0x10);
						sp38[2]   = -M2C_FIELD(temp_r5_4, f32*, 0x20);
						sp38[3]   = -M2C_FIELD(temp_r5_4, f32*, 0x30);
						sp38[4]   = M2C_FIELD(temp_r5_4, f32*, 4);
						sp38[5]   = M2C_FIELD(temp_r5_4, f32*, 0x14);
						sp38[6]   = M2C_FIELD(temp_r5_4, f32*, 0x24);
						sp38[7]   = M2C_FIELD(temp_r5_4, f32*, 0x34);
						sp38[8]   = -M2C_FIELD(temp_r5_4, f32*, 8);
						sp38[9]   = -M2C_FIELD(temp_r5_4, f32*, 0x18);
						sp38[10]  = -M2C_FIELD(temp_r5_4, f32*, 0x28);
						sp38[11]  = -M2C_FIELD(temp_r5_4, f32*, 0x38);
						GXLoadPosMtxImm(sp38, var_r22);
						if (temp_r18 != 0) {
							GXLoadNrmMtxImm(sp38, var_r22);
						}
					}
				}
			}
			GXCallDisplayList(M2C_FIELD(var_r30, s32*, 0), M2C_FIELD(var_r30, s32*, 4));
			var_r30 += 8;
			var_r29 += 0xC;
		}
	} else {
		while (temp_cr0_eq_2 = var_r31 == 0, var_r31 -= 1, temp_cr0_eq_2 == 0) {
			if (temp_r28 != NULL) {
				temp_r5_5 = M2C_FIELD(var_r29, u8**, 8);
				temp_r28(arg1 + 0xC, temp_r5_5 + 4, temp_r5_5, M2C_FIELD(temp_r5_5, f32*, 0xC));
			}
			if (((u32)M2C_FIELD(temp_r3, u32*, 0x10) == 1U)
			    && ((u32)M2C_FIELD(temp_r3, u32*, 0x34) != 0U)) {
				var_r20    = 0;
				temp_r18_2 = ((u32)M2C_FIELD(arg1, u32*, 8) >> 4U) & 1;
				temp_r3_4  = (u8*)(M2C_FIELD(temp_r3, s32*, 0x40)
				    + ((M2C_FIELD(M2C_FIELD(arg1, u8**, 4), u16*, 4) - (var_r31 + 1)) * 2));
				temp_r21_2 = M2C_FIELD(temp_r3_4, u8*, 1);
				temp_r22   = (M2C_FIELD(temp_r3_4, u8*, 0) * 2) & 0xFE;
				for (var_r23_2 = 0; var_r23_2 < temp_r21_2; var_r23_2 += 1) {
					temp_r3_5 = (u8*)(temp_r22
					    + (M2C_FIELD(temp_r3, s32*, 0x44) + ((var_r23_2 * 2) & 0x1FE)));
					temp_r17  = M2C_FIELD(temp_r3_5, u8*, 1);
					var_r15_2 = M2C_FIELD(temp_r3_5, u8*, 0) << 6;
					for (var_r19_2 = 0U; var_r19_2 < temp_r17;
					    var_r20 += 3, var_r15_2 += 0x40, var_r19_2 += 1) {
						temp_r5_6 = (u8*)(M2C_FIELD(lbl_8029BB30, s32*, 0xC) + var_r15_2);
						sp8[0]    = -M2C_FIELD(temp_r5_6, f32*, 0);
						sp8[1]    = -M2C_FIELD(temp_r5_6, f32*, 0x10);
						sp8[2]    = -M2C_FIELD(temp_r5_6, f32*, 0x20);
						sp8[3]    = -M2C_FIELD(temp_r5_6, f32*, 0x30);
						sp8[4]    = M2C_FIELD(temp_r5_6, f32*, 4);
						sp8[5]    = M2C_FIELD(temp_r5_6, f32*, 0x14);
						sp8[6]    = M2C_FIELD(temp_r5_6, f32*, 0x24);
						sp8[7]    = M2C_FIELD(temp_r5_6, f32*, 0x34);
						sp8[8]    = -M2C_FIELD(temp_r5_6, f32*, 8);
						sp8[9]    = -M2C_FIELD(temp_r5_6, f32*, 0x18);
						sp8[10]   = -M2C_FIELD(temp_r5_6, f32*, 0x28);
						sp8[11]   = -M2C_FIELD(temp_r5_6, f32*, 0x38);
						GXLoadPosMtxImm(sp8, var_r20);
						if (temp_r18_2 != 0) {
							GXLoadNrmMtxImm(sp8, var_r20);
						}
					}
				}
			}
			GXCallDisplayList(M2C_FIELD(var_r30, s32*, 0), M2C_FIELD(var_r30, s32*, 4));
			var_r30 += 8;
			var_r29 += 0xC;
		}
	}
	return arg0;
}

#pragma dont_inline reset
u8* fn_80227AA8(u8* arg0, u32 arg1)
{
	f32* temp_r11;
	f32 temp_f0;
	f32 temp_f1;
	s32 temp_r0;
	s32 temp_r0_3;
	s32 temp_r11_2;
	s32 temp_r26;
	s32 temp_r27;
	s32 temp_r28;
	s32 temp_r28_2;
	s32 temp_r29_2;
	s32 temp_r4;
	s32 var_ctr;
	s32 var_r10;
	s32 var_r3;
	s32 var_r3_2;
	s32 var_r3_3;
	s32 var_r4;
	s32 var_r4_3;
	s32 var_r5;
	s32 var_r5_2;
	s32 var_r6;
	s32 var_r7;
	s8* var_r5_3;
	s8* var_r7_2;
	u32 temp_r0_2;
	u32 temp_r0_5;
	u32 temp_r0_6;
	u32 temp_r12;
	u32 temp_r29;
	u32 var_ctr_2;
	u32 var_ctr_3;
	u32 var_r4_2;
	u32 var_r6_2;
	u32 var_r6_3;
	u32 var_r8;
	u32 var_r9;
	s8* temp_r4_2;
	u8 temp_r0_4;
	u8 var_r8_2;

	var_r6                      = 0;
	M2C_FIELD(arg0, s32*, 0x1C) = 0;
	var_r7                      = 0;
	var_r8                      = 0U;
	M2C_FIELD(arg0, s32*, 0x20) = 0;
	M2C_FIELD(arg0, s8**, 0x24) = NULL;
	M2C_FIELD(arg0, s8**, 0x28) = NULL;
	for (; var_r8 < arg1; var_r6 += 0x10, var_r7 += 4, var_r8 += 1) {
		var_r4 = var_r6;
		var_r9 = 0U;
		var_r5 = 0;
		do {
			temp_r12 = 4 - var_r9;
			temp_r0  = 0xFF << var_r5;
			for (var_r10 = 1, var_r3 = 4; var_r10 < temp_r12; var_r3 += 4, var_r10 += 1) {
				temp_r11 = (f32*)(var_r4 + M2C_FIELD(arg0, s32*, 0x18));
				temp_f1  = M2C_FIELD(temp_r11, f32*, var_r3);
				temp_f0  = *temp_r11;
				if (temp_f1 > temp_f0) {
					*temp_r11  = temp_f1;
					temp_r26   = (var_r9 + var_r10) * 8;
					temp_r11_2 = 0xFF << temp_r26;
					M2C_FIELD(M2C_FIELD(arg0, u8**, 0x18), f32*, var_r4 + var_r3) = temp_f0;
					temp_r28                               = M2C_FIELD(arg0, s32*, 0x14);
					temp_r29                               = M2C_FIELD((u8*)temp_r28, u32*, var_r7);
					M2C_FIELD((u8*)temp_r28, u32*, var_r7) = temp_r29 & ~(temp_r0 | temp_r0);
					temp_r27                               = M2C_FIELD(arg0, s32*, 0x14);
					M2C_FIELD((u8*)temp_r27, u32*, var_r7) = M2C_FIELD((u8*)temp_r27, u32*, var_r7)
					    | ((u8)(temp_r29 >> temp_r26) << var_r5);
					temp_r28_2 = M2C_FIELD(arg0, s32*, 0x14);
					M2C_FIELD((u8*)temp_r28_2, u32*, var_r7)
					    = M2C_FIELD((u8*)temp_r28_2, u32*, var_r7) & ~(temp_r11_2 | temp_r11_2);
					temp_r29_2 = M2C_FIELD(arg0, s32*, 0x14);
					M2C_FIELD((u8*)temp_r29_2, u32*, var_r7)
					    = M2C_FIELD((u8*)temp_r29_2, u32*, var_r7)
					    | ((u8)(temp_r29 >> var_r5) << temp_r26);
				}
			}
			var_r9 += 1;
			var_r5 += 8;
			var_r4 += 4;
		} while (var_r9 < 3U);
	}
	temp_r0_2 = M2C_FIELD(arg0, u32*, 0x10);
	if (temp_r0_2 > 1U) {
		temp_r4 = arg1 * (temp_r0_2 * 2);
		M2C_FIELD(arg0, s8**, 0x24)
		    = M2C_FIELD(lbl_8042C9A4, s8 * (**)(), 0x134)(temp_r4 + 3, temp_r4);
		var_r5_2 = 0;
		var_r7_2 = M2C_FIELD(arg0, s8**, 0x24);
		for (var_ctr_2 = 0U; var_ctr_2 < arg1; var_r5_2 += 0x10, var_ctr_2 += 1) {
			var_r8_2 = 0;
			var_r4_2 = 0U;
			var_r3_2 = 0;
			while (var_r4_2 < (u32)M2C_FIELD(arg0, u32*, 0x10)) {
				var_r4_2 += 1;
				temp_r0_3 = M2C_FIELD(arg0, s32*, 0x18) + var_r3_2;
				var_r3_2 += 4;
				*var_r7_2 = (s8)(lbl_80430110 * M2C_FIELD((u8*)temp_r0_3, f32*, var_r5_2));
				temp_r0_4 = (u8)*var_r7_2;
				var_r7_2 += 1;
				var_r8_2 += temp_r0_4;
			}
			if (var_r8_2 < 0x80U) {
				var_r6_2 = 0U;
				while (temp_r0_5 = M2C_FIELD(arg0, u32*, 0x10), var_r6_2 < temp_r0_5) {
					var_r8_2 += 1;
					temp_r4_2 = var_r7_2 - (temp_r0_5 - var_r6_2);
					*temp_r4_2 += 1;
					if (var_r8_2 == 0x80) {
						break;
					}
					var_r6_2 += 1;
				}
			}
		}
		var_r4_3 = 0;
		M2C_FIELD(arg0, s8**, 0x28)
		    = (s8*)(M2C_FIELD(arg0, s8**, 0x24) + (M2C_FIELD(arg0, u32*, 0x10) * arg1));
		M2C_FIELD(arg0, s8**, 0x28) = (s8*)((s32)(M2C_FIELD(arg0, s8**, 0x28) + 3) & 0xFFFFFFFC);
		var_r5_3                    = M2C_FIELD(arg0, s8**, 0x28);
		for (var_ctr_3 = 0U; var_ctr_3 < arg1; var_r4_3 += 4, var_ctr_3 += 1) {
			var_r6_3 = 0U;
			var_r3_3 = 0;
			while (var_r6_3 < (u32)M2C_FIELD(arg0, u32*, 0x10)) {
				var_r6_3 += 1;
				temp_r0_6 = M2C_FIELD(M2C_FIELD(arg0, u8**, 0x14), u32*, var_r4_3) >> var_r3_3;
				var_r3_3 += 8;
				*var_r5_3 = (s8)temp_r0_6;
				var_r5_3 += 1;
			}
		}
	}
	return arg0;
}

u32* fn_80227D54(u32* arg0)
{
	s32 temp_r4;
	u8* temp_r3;

	temp_r3 = M2C_FIELD(arg0, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8));
	if (temp_r3 != NULL) {
		temp_r4 = M2C_FIELD(arg0, s32*, 8);
		if (temp_r4 & 0x01000000) {
			if (temp_r4 & 0x10) {
				M2C_FIELD(arg0, u16*, 0xC) = (u16)(M2C_FIELD(arg0, u16*, 0xC) | 6);
			} else {
				M2C_FIELD(arg0, u16*, 0xC) = (u16)(M2C_FIELD(arg0, u16*, 0xC) | 2);
			}
			M2C_FIELD(temp_r3, s32*, 0x1C) = 0;
			M2C_FIELD(temp_r3, s32*, 0x20) = 0;
			goto block_8;
		}
		if (fn_80227AA8(temp_r3, (u32)M2C_FIELD(arg0, u8**, 0x14)) == NULL) {
			return NULL;
		}
		goto block_8;
	}
block_8:
	return arg0;
}

s32 fn_80227DF0(s32 arg0)
{
	u8* temp_r31;

	temp_r31 = M2C_FIELD(arg0, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8));
	if ((u32)M2C_FIELD(temp_r31, u32*, 0x24) != 0U) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(M2C_FIELD(temp_r31, u8**, 0x24));
		M2C_FIELD(temp_r31, u32*, 0x24) = 0U;
		M2C_FIELD(temp_r31, s32*, 0x28) = 0;
	}
	M2C_FIELD(temp_r31, s32*, 0x1C) = 0;
	M2C_FIELD(temp_r31, s32*, 0x20) = 0;
	return arg0;
}

u8* fn_80227E68(s32 arg0, u32 arg1, u32 arg2, u32 arg3, M2C_UNK arg_sp0)
{
	u8* temp_r3;
	s32* temp_r3_2;
	s32 temp_r30;
	s32 temp_r30_2;

	temp_r3                        = fn_801B3984();
	M2C_FIELD(temp_r3, s32*, 0x2C) = 0x116;
	M2C_FIELD(temp_r3, s32*, 0x30) = arg0;
	temp_r30                       = fn_801B4EB4();
	temp_r3_2                      = fn_8015D4B8();
	fn_801B52BC(temp_r30, 0, temp_r3_2, 0);
	fn_801B43EC();
	temp_r30_2 = fn_801B51B8(temp_r3, *temp_r3_2, 0, 0);
	if (arg1 != 0U) {
		fn_8015C358(temp_r30_2, arg1);
	}
	if (arg2 != 0U) {
		lbl_8042CF80 = fn_8015C37C(temp_r30_2);
		fn_8015C370(temp_r30_2, arg2);
	}
	if (arg3 != 0U) {
		fn_8015C388(temp_r30_2, arg3);
	}
	return temp_r3;
}

s32 fn_80227F48(u8* arg0)
{
	s32 temp_r31;
	s32 var_r5;
	s32 var_r31;
	u32 temp_r0;
	u8* temp_r6;
	u8* temp_r7;

	temp_r7 = M2C_FIELD(arg0, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8));
	temp_r0 = M2C_FIELD(temp_r7, u32*, 0x10);
	var_r31 = M2C_FIELD(temp_r7, s32*, 4) + 0x14;
	if (temp_r0 > 1U) {
		var_r31 += M2C_FIELD(arg0, s32*, 0x14) * (temp_r0 * 2);
	}
	temp_r31 = var_r31 + (M2C_FIELD(temp_r7, s32*, 0) << 6);
	if ((u8*)M2C_FIELD(temp_r7, u8**, 0x1C) != NULL) {
		var_r5  = 0;
		temp_r6 = M2C_FIELD(arg0, u8**, 0x58);
		M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_r6, u8**, 0x24), u8**, -4), s32*, 0x10) = var_r5;
		M2C_FIELD(temp_r6, u8**, 0x24) = (u8*)M2C_FIELD(temp_r7, u8**, 0x1C);
		if (M2C_FIELD(arg0, s32*, 8) & 0x10) {
			M2C_FIELD(temp_r6, s32*, 0x2C) = (s32)M2C_FIELD(temp_r7, s32*, 0x20);
		}
		M2C_FIELD(M2C_FIELD(arg0, u8**, 0x58), void (**)(), 0x14) = fn_8015C004;
		M2C_FIELD(temp_r7, s32*, 0x1C)                            = var_r5;
		M2C_FIELD(temp_r7, s32*, 0x20)                            = var_r5;
	}
	temp_r31 += fn_80225400(temp_r7);
	return temp_r31;
}

s32* fn_80228014(s32* arg0, u8* arg1)
{
	s32 spC;
	s32 sp8;
	s32 temp_r29_2;
	s32 temp_r30;
	s32 temp_r30_2;
	s32 var_r5;
	u32 temp_r0;
	u32 temp_r0_2;
	u32 temp_r0_3;
	u32 temp_r29;
	u8* temp_r31;
	u8* temp_r3;
	u8* temp_r6;

	spC      = 6;
	temp_r3  = M2C_FIELD(arg1, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8));
	temp_r0  = M2C_FIELD(temp_r3, u32*, 0x10);
	temp_r30 = M2C_FIELD(temp_r3, s32*, 4) + 0x14;
	if (temp_r0 > 1U) {
		temp_r30 += M2C_FIELD(arg1, s32*, 0x14) * (temp_r0 * 2);
	}
	temp_r30 += M2C_FIELD(temp_r3, s32*, 0) << 6;
	if ((u8*)M2C_FIELD(temp_r3, u8**, 0x1C) != NULL) {
		var_r5    = 0;
		temp_r6   = M2C_FIELD(arg1, u8**, 0x58);
		temp_r0_2 = M2C_FIELD(arg1, u32*, 8);
		M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_r6, u8**, 0x24), u8**, -4), s32*, 0x10) = var_r5;
		M2C_FIELD(temp_r6, u8**, 0x24) = (u8*)M2C_FIELD(temp_r3, u8**, 0x1C);
		if (temp_r0_2 & 0x10) {
			M2C_FIELD(temp_r6, s32*, 0x2C) = (s32)M2C_FIELD(temp_r3, s32*, 0x20);
		}
		M2C_FIELD(M2C_FIELD(arg1, u8**, 0x58), void (**)(), 0x14) = fn_8015C004;
		M2C_FIELD(temp_r3, s32*, 0x1C)                            = var_r5;
		M2C_FIELD(temp_r3, s32*, 0x20)                            = var_r5;
	}
	temp_r30 += fn_80225400(temp_r3);
	if (fn_80192ED8(arg0, 1, temp_r30 - 0xC, 0x35000, 0xFFFF) == 0U) {
		return NULL;
	}
	if (fn_80193474(arg0, &spC, 4) == 0U) {
		return NULL;
	}
	temp_r30_2 = M2C_FIELD(arg1, s32*, 0x14);
	temp_r31   = M2C_FIELD(arg1, u8**, M2C_FIELD(lbl_8029BB30, s32*, 8));
	temp_r0_3  = M2C_FIELD(temp_r31, u32*, 4);
	temp_r29   = M2C_FIELD(temp_r31, u32*, 0x10);
	sp8        = ((temp_r29 & 0xFF) << 16) | ((temp_r0_3 & 0xFF) << 8)
	    | (M2C_FIELD(temp_r31, u32*, 0) & 0xFF);
	if (fn_80193474(arg0, &sp8, 4) == 0U) {
		return NULL;
	}
	if (fn_80197B48(arg0, M2C_FIELD(temp_r31, s32*, 8), M2C_FIELD(temp_r31, s32*, 4)) == 0U) {
		return NULL;
	}
	if ((u32)M2C_FIELD(temp_r31, u32*, 0x10) > 1U) {
		temp_r29_2 = temp_r29 * temp_r30_2;
		if (fn_80197B48(arg0, M2C_FIELD(temp_r31, s32*, 0x28), temp_r29_2) == 0U) {
			return NULL;
		}
		if (fn_80197B48(arg0, M2C_FIELD(temp_r31, s32*, 0x24), temp_r29_2) == 0U) {
			return NULL;
		}
		goto block_19;
	}
block_19:
	if (fn_80197B48(arg0, M2C_FIELD(temp_r31, s32*, 0xC), M2C_FIELD(temp_r31, s32*, 0) << 6)
	    == 0U) {
		return NULL;
	}
	if (fn_80225164(arg0, temp_r31) != NULL) {
		return arg0;
	}
	return NULL;
}

u32* fn_8022824C(u32* arg0, u32* arg1)
{
	s32 sp24;
	s32 sp20;
	s32 sp1C;
	s32 sp18;
	u32 sp14;
	u32 sp10;
	s32 spC;
	s32 sp8;
	s32 temp_r31;
	u32 temp_r3;
	u32 temp_r5;
	u32 temp_r5_2;
	u32 temp_r5_3;
	u32 temp_r5_4;
	u32 temp_r5_5;
	u32 temp_r5_6;
	u8* temp_r30;

	if (fn_80192F38(1, &sp10, &sp14) == 0) {
		return NULL;
	}
	if ((sp14 < 0x31000U) || (sp14 > 0x35000U)) {
		sp20 = 0x116;
		sp24 = fn_8019408C(0x80000004);
		fn_80193FE8(&sp20);
		return NULL;
	}
	if (sp14 < 0x34002U) {
		sp18 = 0x116;
		sp1C = fn_8019408C(0x80000004);
		fn_80193FE8(&sp18);
		return NULL;
	}
	if (fn_80193884(arg0, &sp8, 4) == 0U) {
		return NULL;
	}
	if (sp8 != 6) {
		return NULL;
	}
	temp_r30 = M2C_FIELD(lbl_8042C9A4, u8 * (**)(), 0x144)(
	    M2C_FIELD(lbl_8029BB30, s32*, 0x18), lbl_8029BB30);
	memset(temp_r30, 0, 0x4C);
	if (fn_80193884(arg0, &spC, 4) == 0U) {
		return NULL;
	}
	M2C_FIELD(temp_r30, s32*, 0)    = (s32)(u8)spC;
	M2C_FIELD(temp_r30, u32*, 4)    = (u32)(u8)((u32)spC >> 8U);
	M2C_FIELD(temp_r30, u32*, 0x10) = (u32)(u8)((u32)spC >> 0x10U);
	temp_r31                        = M2C_FIELD(arg1, s32*, 0x14);
	temp_r3                         = sp10 - 8;
	sp10                            = temp_r3;
	if ((u32)M2C_FIELD(temp_r30, u32*, 0x10) > 1U) {
		M2C_FIELD(temp_r30, s32*, 0x24)
		    = M2C_FIELD(lbl_8042C9A4, s32(**)(), 0x134)(temp_r3 + 5, lbl_8042C9A4);
		M2C_FIELD(temp_r30, s32*, 0x28)
		    = (s32)(M2C_FIELD(temp_r30, s32*, 0x24) + (M2C_FIELD(temp_r30, u32*, 0x10) * temp_r31));
		M2C_FIELD(temp_r30, s32*, 0x28) = (s32)((M2C_FIELD(temp_r30, s32*, 0x28) + 3) & 0xFFFFFFFC);
		M2C_FIELD(temp_r30, s32*, 0xC)
		    = (s32)(M2C_FIELD(temp_r30, s32*, 0x28) + (M2C_FIELD(temp_r30, u32*, 0x10) * temp_r31));
		M2C_FIELD(temp_r30, s32*, 0xC) = (s32)((M2C_FIELD(temp_r30, s32*, 0xC) + 3) & 0xFFFFFFFC);
		M2C_FIELD(temp_r30, s32*, 8)
		    = (s32)(M2C_FIELD(temp_r30, s32*, 0xC) + (M2C_FIELD(temp_r30, s32*, 0) << 6));
		temp_r5 = M2C_FIELD(temp_r30, u32*, 4);
		sp10    = temp_r5;
		if (sp10 != fn_801979AC(arg0, M2C_FIELD(temp_r30, s32*, 8), (u8)temp_r5)) {
			return NULL;
		}
		temp_r5_2 = M2C_FIELD(temp_r30, u32*, 0x10) * temp_r31;
		sp10      = temp_r5_2;
		if (sp10 != fn_801979AC(arg0, M2C_FIELD(temp_r30, s32*, 0x28), (u8)temp_r5_2)) {
			return NULL;
		}
		temp_r5_3 = M2C_FIELD(temp_r30, u32*, 0x10) * temp_r31;
		sp10      = temp_r5_3;
		if (sp10 != fn_801979AC(arg0, M2C_FIELD(temp_r30, s32*, 0x24), (u8)temp_r5_3)) {
			return NULL;
		}
		temp_r5_4 = M2C_FIELD(temp_r30, s32*, 0) << 6;
		sp10      = temp_r5_4;
		if (sp10 != fn_801979AC(arg0, M2C_FIELD(temp_r30, s32*, 0xC), (u8)temp_r5_4)) {
			return NULL;
		}
		goto block_26;
	}
	M2C_FIELD(temp_r30, s32*, 0x24)
	    = M2C_FIELD(lbl_8042C9A4, s32(**)(), 0x134)(temp_r3 + 3, lbl_8042C9A4);
	M2C_FIELD(temp_r30, s32*, 0xC) = (s32)M2C_FIELD(temp_r30, s32*, 0x24);
	M2C_FIELD(temp_r30, s32*, 0xC) = (s32)((M2C_FIELD(temp_r30, s32*, 0xC) + 3) & 0xFFFFFFFC);
	M2C_FIELD(temp_r30, s32*, 8)
	    = (s32)(M2C_FIELD(temp_r30, s32*, 0xC) + (M2C_FIELD(temp_r30, s32*, 0) << 6));
	temp_r5_5 = M2C_FIELD(temp_r30, u32*, 4);
	sp10      = temp_r5_5;
	if (sp10 != fn_801979AC(arg0, M2C_FIELD(temp_r30, s32*, 8), (u8)temp_r5_5)) {
		return NULL;
	}
	temp_r5_6 = M2C_FIELD(temp_r30, s32*, 0) << 6;
	sp10      = temp_r5_6;
	if (sp10 != fn_801979AC(arg0, M2C_FIELD(temp_r30, s32*, 0xC), (u8)temp_r5_6)) {
		return NULL;
	}
block_26:
	if (fn_80225248(arg0, temp_r30) == NULL) {
		return NULL;
	}
	fn_8022647C(arg1, temp_r30);
	return arg0;
}

#pragma dont_inline on
s32 fn_802285D8(u32* arg0, u8** arg1, u8** arg2, M2C_UNK arg_sp0)
{
	u8 sp8[0x180];
	s32 temp_r0;
	s32 temp_r11;
	s32 temp_r18_2;
	s32 temp_r19;
	s32 temp_r20;
	s32 temp_r26;
	s32 temp_r29;
	s32 temp_r5;
	s32 temp_r5_2;
	s32 temp_r5_3;
	s32 temp_r6;
	s32 temp_r6_2;
	s32 temp_r6_3;
	s32 temp_r7;
	s32 temp_r7_2;
	s32 var_ctr_2;
	s32 var_r11;
	s32 var_r18;
	s32 var_r18_2;
	s32 var_r19;
	s32 var_r26;
	s32 var_r31;
	s32 var_r4;
	s32 var_r6_2;
	s32 var_r7;
	s32 var_r7_2;
	s8 temp_r10;
	s8 temp_r12;
	s8 temp_r18;
	s8 temp_r9;
	u16 temp_r24;
	u32* var_r5;
	u32 temp_r0_2;
	u32 temp_r0_3;
	u32 temp_r10_2;
	u32 temp_r5_4;
	u32 var_ctr;
	u32 var_r9;
	u8* temp_r3;
	u8* temp_r3_2;
	u8* temp_r3_3;
	u8* temp_r3_4;
	u8* temp_r4;
	u8* temp_r4_2;
	u8* temp_r8;
	u8* var_r6;

	if ((u32)M2C_FIELD(arg0, u8**, lbl_8042C930) == 0U) {
		fn_8015C590();
	}
	temp_r3                 = M2C_FIELD(arg0, u8**, 0x5C);
	var_r31                 = 1;
	M2C_FIELD(sp8, s32*, 0) = M2C_FIELD(temp_r3, s32*, 0x14);
	M2C_FIELD(sp8, s32*, 4) = 8;
	M2C_FIELD(sp8, s8*, 8)  = -1;
	if (M2C_FIELD(arg0, s32*, 8) & 0x10) {
		temp_r6                           = var_r31 * 0x18;
		var_r31                           = 2;
		M2C_FIELD(sp8, s32*, temp_r6)     = M2C_FIELD(temp_r3, s32*, 0x18);
		M2C_FIELD(sp8, s32*, temp_r6 + 4) = 8;
		M2C_FIELD(sp8, s8*, temp_r6 + 8)  = -1;
	}
	if (M2C_FIELD(arg0, s32*, 8) & 8) {
		temp_r5                       = var_r31 * 0x18;
		M2C_FIELD(sp8, s32*, temp_r5) = M2C_FIELD(arg0, s32*, 0x30);
		var_r31 += 1;
		M2C_FIELD(sp8, s32*, temp_r5 + 4) = 4;
		M2C_FIELD(sp8, s8*, temp_r5 + 8)  = -1;
	}
	if (M2C_FIELD(arg0, s32*, 8) & 0x84) {
		var_r5 = arg0;
		var_r6 = sp8 + (var_r31 * 0x18);
		for (var_r7 = 0; var_r7 < (s32)M2C_FIELD(arg0, s32*, 0x1C);
		    var_r31 += 1, var_r5 += 1, var_r7 += 1, var_r6 += 0x18) {
			M2C_FIELD(var_r6, s32*, 0) = M2C_FIELD(var_r5, s32*, 0x34);
			M2C_FIELD(var_r6, s32*, 4) = 7;
			M2C_FIELD(var_r6, s8*, 8)  = -1;
		}
	}
	temp_r3_2 = fn_80226468(arg0);
	if ((u32)M2C_FIELD(temp_r3_2, u32*, 0x10) > 1U) {
		temp_r5_2                       = var_r31 * 0x18;
		M2C_FIELD(sp8, s32*, temp_r5_2) = M2C_FIELD(temp_r3_2, s32*, 0x28);
		temp_r0_2                       = M2C_FIELD(temp_r3_2, u32*, 0x10);
		switch ((s32)temp_r0_2) { /* irregular */
			case 1:
				M2C_FIELD(sp8, s32*, temp_r5_2 + 4) = 1;
				break;
			case 2:
				M2C_FIELD(sp8, s32*, temp_r5_2 + 4) = 2;
				break;
			case 3:
				M2C_FIELD(sp8, s32*, temp_r5_2 + 4) = 3;
				break;
			case 4:
				M2C_FIELD(sp8, s32*, temp_r5_2 + 4) = 4;
				break;
		}
	} else {
		temp_r6_2                           = var_r31 * 0x18;
		M2C_FIELD(sp8, s32*, temp_r6_2)     = M2C_FIELD(temp_r3_2, s32*, 0x14);
		M2C_FIELD(sp8, s32*, temp_r6_2 + 4) = 4;
	}
	M2C_FIELD(sp8, s8*, (var_r31 * 0x18) + 8) = -1;
	if ((u32)M2C_FIELD(temp_r3_2, u32*, 0x10) > 1U) {
		temp_r7 = (var_r31 + 1) * 0x18;
		var_r31 += 2;
		M2C_FIELD(sp8, s32*, temp_r7)     = M2C_FIELD(temp_r3_2, s32*, 0x24);
		M2C_FIELD(sp8, s32*, temp_r7 + 4) = M2C_FIELD(sp8, s32*, temp_r7 - 0x14);
		M2C_FIELD(sp8, s8*, temp_r7 + 8)  = -1;
	} else {
		temp_r5_3 = (var_r31 + 1) * 0x18;
		var_r31 += 2;
		M2C_FIELD(sp8, s32*, temp_r5_3)     = M2C_FIELD(temp_r3_2, s32*, 0x18);
		M2C_FIELD(sp8, s32*, temp_r5_3 + 4) = 9;
		M2C_FIELD(sp8, s8*, temp_r5_3 + 8)  = -1;
	}
	if (M2C_FIELD(arg0, s32*, 8) & 0x10) {
		temp_r18                             = var_r31 - 2;
		temp_r12                             = var_r31 - 1;
		M2C_FIELD(sp8, s8*, 8)               = 1;
		temp_r20                             = var_r31 * 0x18;
		M2C_FIELD(sp8, s8*, 9)               = temp_r18;
		M2C_FIELD(sp8, s8*, 10)              = temp_r12;
		M2C_FIELD(sp8, s8*, 11)              = -1;
		M2C_FIELD(sp8, s8*, 0x20)            = 0;
		M2C_FIELD(sp8, s8*, 0x21)            = temp_r18;
		M2C_FIELD(sp8, s8*, 0x22)            = temp_r12;
		M2C_FIELD(sp8, s8*, 0x23)            = -1;
		M2C_FIELD(sp8, s8*, temp_r20 - 0x28) = 0;
		M2C_FIELD(sp8, s8*, temp_r20 - 0x27) = 1;
		M2C_FIELD(sp8, s8*, temp_r20 - 0x26) = temp_r12;
		M2C_FIELD(sp8, s8*, temp_r20 - 0x25) = -1;
		M2C_FIELD(sp8, s8*, temp_r20 - 0x10) = 0;
		M2C_FIELD(sp8, s8*, temp_r20 - 0xF)  = 1;
		M2C_FIELD(sp8, s8*, temp_r20 - 0xE)  = temp_r18;
		M2C_FIELD(sp8, s8*, temp_r20 - 0xD)  = -1;
	} else {
		temp_r10                             = var_r31 - 2;
		temp_r9                              = var_r31 - 1;
		M2C_FIELD(sp8, s8*, 8)               = temp_r10;
		temp_r11                             = var_r31 * 0x18;
		M2C_FIELD(sp8, s8*, 9)               = temp_r9;
		M2C_FIELD(sp8, s8*, 10)              = -1;
		M2C_FIELD(sp8, s8*, temp_r11 - 0x28) = 0;
		M2C_FIELD(sp8, s8*, temp_r11 - 0x27) = temp_r9;
		M2C_FIELD(sp8, s8*, temp_r11 - 0x26) = -1;
		M2C_FIELD(sp8, s8*, temp_r11 - 0x10) = 0;
		M2C_FIELD(sp8, s8*, temp_r11 - 0xF)  = temp_r10;
		M2C_FIELD(sp8, s8*, temp_r11 - 0xE)  = -1;
	}
	temp_r3_3 = fn_8015F8A4((s32*)sp8, var_r31, M2C_FIELD(arg0, s32*, 0x14));
	if (temp_r3_3 == NULL) {
		return 0;
	}
	*arg1 = fn_8015F5EC((s32*)sp8, var_r31, M2C_FIELD(arg0, s32*, 0x14));
	if ((u8*)*arg1 == NULL) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(temp_r3_3, lbl_8042C9A4);
		return 0;
	}
	temp_r4    = M2C_FIELD(arg0, u8**, 0x54);
	temp_r24   = M2C_FIELD(temp_r4, u16*, 4);
	temp_r26   = temp_r24 * 4;
	temp_r18_2 = (var_r31 - 2) * temp_r26;
	temp_r3_4  = M2C_FIELD(lbl_8042C9A4, u8 * (**)(), 0x134)(temp_r18_2, temp_r4);
	if (temp_r3_4 == NULL) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(*arg1, lbl_8042C9A4);
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(temp_r3_3, lbl_8042C9A4);
		return 0;
	}
	memset(temp_r3_4, 0, temp_r18_2);
	temp_r0_3 = var_r31 - 2;
	for (var_r7_2 = 0, var_r4 = 0; var_r7_2 < (s32)temp_r24; var_r4 += 0xC, var_r7_2 += 1) {
		temp_r8 = M2C_FIELD(arg0, u8**, 0x54) + var_r4;
		for (var_r9 = 0U; var_r9 < temp_r0_3; var_r9 += 1) {
			M2C_FIELD(temp_r3_4, s32*, ((var_r7_2 * temp_r0_3) + var_r9) * 4)
			    = M2C_FIELD(temp_r8, s32*, 0x10);
		}
	}
	*arg2 = M2C_FIELD(lbl_8042C9A4, u8 * (**)(), 0x134)(temp_r26, lbl_8042C9A4);
	if ((u8*)*arg2 == NULL) {
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(temp_r3_4, lbl_8042C9A4);
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(*arg1, lbl_8042C9A4);
		M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(temp_r3_3, lbl_8042C9A4);
		return 0;
	}
	temp_r29 = var_r31 - 2;
	for (var_r26 = 0, var_r18 = 0, var_r19 = 0; var_r26 < (s32)temp_r24;
	    var_r18 += 0xC, var_r19 += 4, var_r26 += 1) {
		temp_r7_2                       = var_r26 * temp_r29;
		M2C_FIELD(*arg2, s32*, var_r19) = fn_8015F3FC(temp_r3_3, temp_r3_4 + (temp_r7_2 * 4),
		    temp_r29, M2C_FIELD((M2C_FIELD(arg0, u8**, 0x54) + var_r18), s32*, 0x14));
		if ((u32)M2C_FIELD(*arg2, u32*, var_r19) == 0U) {
			var_r18_2 = var_r26 * 4;
			while (var_r26 -= 1, var_r18_2 -= 4, var_r26 > 0) {
				temp_r4_2 = *arg2;
				M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(
				    M2C_FIELD(temp_r4_2, s32*, var_r18_2), temp_r4_2);
			}
			return 0;
		}
	}
	M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(temp_r3_4, lbl_8042C9A4);
	M2C_FIELD(lbl_8042C9A4, M2C_UNK(**)(), 0x138)(temp_r3_3, lbl_8042C9A4);
	return 1;
}
#pragma dont_inline reset
