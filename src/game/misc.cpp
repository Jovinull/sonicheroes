// Complete GameCube misc.cpp candidate, 0x800D5844--0x800D7B18.
// NonMatching. Initial GameCube control flow recovered with m2c 708d2d2.
#include "types.h"
#include "Runtime.PPCEABI.H/__va_arg.h"
struct RwV3d {
	f32 x, y, z;
};
// Word-copy view preserves the observed 12-byte vector copy.
struct VectorCopyWords {
	u32 words[3];
};
struct NJS_LINE {
	RwV3d p, v;
};
struct sAngle {
	s32 x, y, z;
};
extern "C" {
f32 fn_801991B4(const RwV3d*);
f32 fn_801990E0(RwV3d*, const RwV3d*);
f64 floor(f64);
f64 acos(f64);
f64 atan2(f64, f64);
f64 __fabs(f64);
f64 __frsqrte(f64);
extern RwV3d* lbl_8042C208;
extern void* lbl_8042C178;
extern void* lbl_8042C0F0;
void fn_8001F24C(void);
void fn_8001F2D4(void);
void fn_8001F088(void*, const RwV3d*, RwV3d*);
void fn_8001F0C0(void*, s32);
void fn_8001F1C8(void*, s32);
void fn_8001F144(void*, s32);
void RsCameraSize(void*, const char*, s32, u32, s32);
void fn_80177C50(void);
void fn_801782D8(void*, u32*, u32*);
s32 fn_80194234(s32, s32);
s32 fn_80194294(s32, s32*);
s32 vsprintf(char*, const char*, __va_list);
extern f32 lbl_803A7028[65536];
extern u32 lbl_8042B680;
extern const __declspec(section ".sdata2") f32 lbl_8042E008;
extern const __declspec(section ".sdata2") f32 lbl_8042E00C;
extern const __declspec(section ".sdata2") f32 lbl_8042E010;
extern const __declspec(section ".sdata2") f32 lbl_8042E014;
extern const __declspec(section ".sdata2") f64 lbl_8042E018;
extern const __declspec(section ".sdata2") f64 lbl_8042E020;
extern const __declspec(section ".sdata2") f32 lbl_8042E028;
extern const __declspec(section ".sdata2") f32 lbl_8042E02C;
extern const __declspec(section ".sdata2") f32 lbl_8042E030;
extern const __declspec(section ".sdata2") f32 lbl_8042E034;
extern const __declspec(section ".sdata2") f32 lbl_8042E038;
void fn_800D5844(RwV3d* arg0, f32 farg0);
void fn_800D5938(void* arg0);
void fn_800D593C(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2, sAngle* arg3);
s32 fn_800D5A64(RwV3d* arg0, RwV3d* arg1, f32 farg0);
void fn_800D5B8C(u32 arg0);
void fn_800D5C08(s32 position, const char* format, ...);
void fn_800D5CB0(s32 position, const char* format, ...);
f32 fn_800D5D5C(NJS_LINE* arg0, NJS_LINE* arg1, RwV3d* arg2);
f32 fn_800D605C(NJS_LINE* arg0, NJS_LINE* arg1, RwV3d* arg2, RwV3d* arg3);
f32 fn_800D67D4(f32 farg0);
f32 fn_800D6818(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2);
f32 fn_800D689C(RwV3d* arg0, RwV3d* arg1, NJS_LINE* arg2);
f32 fn_800D6958(NJS_LINE* arg0, NJS_LINE* arg1, NJS_LINE* arg2);
f32 fn_800D6E0C(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2);
f32 fn_800D6F0C(RwV3d* arg0, NJS_LINE* arg1, RwV3d* arg2);
f32 fn_800D7044(RwV3d* arg0, NJS_LINE* arg1, RwV3d* arg2);
f32 fn_800D71DC(RwV3d* arg0, RwV3d* arg1);
f32 fn_800D7218(RwV3d* arg0, RwV3d* arg1);
void fn_800D72C0(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2);
void fn_800D72F4(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2);
f32 fn_800D7328(f32 farg0, f32 farg1, f32 farg2);
void fn_800D735C(RwV3d* arg0, RwV3d* arg1, s32* arg2);
f32 fn_800D7564(f32 farg0, f32 farg1);
s32 fn_800D75CC(const RwV3d* first, const RwV3d* second, const RwV3d* planeNormal);
s32 fn_800D7920(const RwV3d* first, const RwV3d* second, const RwV3d* orientation);
u16 fn_800D7A54(u32 first, u32 second);
s16 fn_800D7A80(u32 first, u32 second);
u16 fn_800D7A94(u32 first, u32 second, s32 limit);
f32 fn_800D7AE4(s32 arg0);
f32 fn_800D7B00(u16 arg0);

void fn_800D5844(RwV3d* arg0, f32 farg0)
{
	RwV3d delta;
	f32 z, y, x;
	x       = lbl_8042C208->x - arg0->x;
	delta.x = x;
	y       = lbl_8042C208->y - arg0->y;
	delta.y = y;
	z       = lbl_8042C208->z - arg0->z;
	delta.z = z;
	if (z * z + (x * x + y * y) >= lbl_8042E014) {
		fn_801990E0(&delta, &delta);
		delta.x *= farg0;
		delta.y *= farg0;
		delta.z *= farg0;
	}
	arg0->x += delta.x;
	arg0->y += delta.y;
	arg0->z += delta.z;
}

void fn_800D5938(void* arg0) { }

void fn_800D593C(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2, sAngle* arg3)
{
	RwV3d sp14;
	RwV3d sp8; /* compiler-managed */

	fn_8001F24C();
	if (arg2 != NULL) {
		sp8.x = arg1->x - arg2->x;
		sp8.y = arg1->y - arg2->y;
		sp8.z = arg1->z - arg2->z;
	} else {
		sp8.x = arg1->x;
		sp8.y = arg1->y;
		sp8.z = arg1->z;
	}
	fn_8001F0C0(lbl_8042C178, arg3->z);
	fn_8001F1C8(lbl_8042C178, arg3->x);
	fn_8001F144(lbl_8042C178, arg3->y);
	if (arg2 != NULL) {
		fn_8001F088(lbl_8042C178, (RwV3d*)&sp8, &sp14);
		arg0->x = sp14.x + arg2->x;
		arg0->y = sp14.y + arg2->y;
		arg0->z = sp14.z + arg2->z;
	} else {
		fn_8001F088(lbl_8042C178, (RwV3d*)&sp8, arg0);
	}
	fn_8001F2D4();
}

s32 fn_800D5A64(RwV3d* arg0, RwV3d* arg1, f32 farg0)
{
	RwV3d sp8; /* compiler-managed */
	f32 temp_f0;
	f32 temp_f3;
	f32 temp_f4;

	*(VectorCopyWords*)&sp8 = *(const VectorCopyWords*)arg1;
	temp_f4                 = sp8.x - arg0->x;
	sp8.x                   = temp_f4;
	temp_f3                 = sp8.y - arg0->y;
	sp8.y                   = temp_f3;
	temp_f0                 = sp8.z - arg0->z;
	sp8.z                   = temp_f0;
	if (((temp_f0 * temp_f0) + ((temp_f4 * temp_f4) + (temp_f3 * temp_f3))) <= (farg0 * farg0)) {
		arg0->x = arg1->x;
		arg0->y = arg1->y;
		arg0->z = arg1->z;
		return 1;
	}
	fn_801990E0((RwV3d*)&sp8, (RwV3d*)&sp8);
	sp8.x *= farg0;
	sp8.y *= farg0;
	sp8.z *= farg0;
	arg0->x += sp8.x;
	arg0->y += sp8.y;
	arg0->z += sp8.z;
	return 0;
}

void fn_800D5B8C(u32 arg0)
{
	s32 sp10;
	s32 spC;
	u32 sp8;

	sp8 = arg0;
	fn_80194294(6, &sp10);
	fn_80194294(8, &spC);
	fn_80194234(6, 0);
	fn_80194234(8, 1);
	fn_80177C50();
	fn_801782D8(lbl_8042C0F0, &sp8, &lbl_8042B680);
	fn_80194234(6, sp10);
	fn_80194234(8, spC);
}

void fn_800D5C08(s32 position, const char* format, ...)
{
	__va_list args;
	char buffer[64];
	__builtin_va_info(args);
	vsprintf(buffer, format, args);
	RsCameraSize(lbl_8042C0F0, buffer, position >> 16, (u16)position, 5);
}

void fn_800D5CB0(s32 position, const char* format, ...)
{
	__va_list args;
	char buffer[64];
	__builtin_va_info(args);
	vsprintf(buffer, format, args);
	RsCameraSize(lbl_8042C0F0, buffer, position >> 16, (u16)position + 6, 5);
}

f32 fn_800D5D5C(NJS_LINE* arg0, NJS_LINE* arg1, RwV3d* arg2)
{
	volatile f32 sp10;
	volatile f32 spC;
	volatile f32 sp8;
	f32 temp_f0;
	f32 temp_f0_13;
	f32 temp_f0_2;
	f32 temp_f0_3;
	f32 temp_f0_7;
	f32 temp_f0_8;
	f32 temp_f0_9;
	f32 temp_f1;
	f32 temp_f2;
	f32 temp_f2_2;
	f32 temp_f3;
	f32 temp_f3_2;
	f32 temp_f3_3;
	f32 temp_f4;
	f32 temp_f4_2;
	f32 temp_f6;
	f32 temp_f6_2;
	f32 temp_f7;
	f32 temp_f9;
	f32 var_f4;
	f32 var_f5;
	f32 var_f8;
	f64 temp_f0_10;
	f64 temp_f0_11;
	f64 temp_f0_12;
	f64 temp_f0_14;
	f64 temp_f0_15;
	f64 temp_f0_16;
	f64 temp_f0_4;
	f64 temp_f0_5;
	f64 temp_f0_6;

	temp_f0   = arg0->v.z;
	temp_f0_2 = arg0->v.x;
	temp_f0_3 = arg0->v.y;
	var_f4    = (temp_f0 * temp_f0) + ((temp_f0_2 * temp_f0_2) + (temp_f0_3 * temp_f0_3));
	if (var_f4 > lbl_8042E008) {
		temp_f0_4 = __frsqrte(var_f4);
		temp_f0_5
		    = lbl_8042E018 * temp_f0_4 * (lbl_8042E020 - ((f64)var_f4 * (temp_f0_4 * temp_f0_4)));
		temp_f0_6
		    = lbl_8042E018 * temp_f0_5 * (lbl_8042E020 - ((f64)var_f4 * (temp_f0_5 * temp_f0_5)));
		sp10   = (f32)((f64)var_f4
		    * (lbl_8042E018 * temp_f0_6
		        * (lbl_8042E020 - ((f64)var_f4 * (temp_f0_6 * temp_f0_6)))));
		var_f4 = sp10;
	}
	temp_f0_7 = arg1->v.z;
	temp_f0_8 = arg1->v.x;
	temp_f0_9 = arg1->v.y;
	var_f8    = (temp_f0_7 * temp_f0_7) + ((temp_f0_8 * temp_f0_8) + (temp_f0_9 * temp_f0_9));
	if (var_f8 > lbl_8042E008) {
		temp_f0_10 = __frsqrte(var_f8);
		temp_f0_11 = lbl_8042E018 * temp_f0_10
		    * (lbl_8042E020 - ((f64)var_f8 * (temp_f0_10 * temp_f0_10)));
		temp_f0_12 = lbl_8042E018 * temp_f0_11
		    * (lbl_8042E020 - ((f64)var_f8 * (temp_f0_11 * temp_f0_11)));
		spC    = (f32)((f64)var_f8
		    * (lbl_8042E018 * temp_f0_12
		        * (lbl_8042E020 - ((f64)var_f8 * (temp_f0_12 * temp_f0_12)))));
		var_f8 = spC;
	}
	temp_f3    = arg1->v.z;
	temp_f2    = arg0->v.x;
	temp_f1    = arg1->v.x;
	temp_f0_13 = arg1->v.y;
	temp_f7    = (arg0->v.z * temp_f3) + ((temp_f2 * temp_f1) + (arg0->v.y * temp_f0_13));
	if ((f32)__fabs(temp_f7 / (var_f4 * var_f8)) < lbl_8042E028) {
		temp_f9   = arg0->p.x;
		temp_f2_2 = arg0->p.y;
		temp_f4_2 = arg0->p.z;
		temp_f6   = -((temp_f3 * arg1->p.z) + ((temp_f1 * arg1->p.x) + (temp_f0_13 * arg1->p.y)))
		    + ((temp_f3 * temp_f4_2) + ((temp_f1 * temp_f9) + (temp_f0_13 * temp_f2_2)));
		var_f5 = (temp_f3 * temp_f3) + ((temp_f1 * temp_f1) + (temp_f0_13 * temp_f0_13));
		if (arg2 != NULL) {
			temp_f3_2 = -temp_f6 / var_f5;
			arg2->x   = temp_f9 + (temp_f1 * temp_f3_2);
			arg2->y   = temp_f2_2 + (arg1->v.y * temp_f3_2);
			arg2->z   = temp_f4_2 + (arg1->v.z * temp_f3_2);
		}
		temp_f4 = (f32)__fabs(temp_f6);
		if (var_f5 > lbl_8042E008) {
			temp_f0_14 = __frsqrte(var_f5);
			temp_f0_15 = lbl_8042E018 * temp_f0_14
			    * (lbl_8042E020 - ((f64)var_f5 * (temp_f0_14 * temp_f0_14)));
			temp_f0_16 = lbl_8042E018 * temp_f0_15
			    * (lbl_8042E020 - ((f64)var_f5 * (temp_f0_15 * temp_f0_15)));
			sp8    = (f32)((f64)var_f5
			    * (lbl_8042E018 * temp_f0_16
			        * (lbl_8042E020 - ((f64)var_f5 * (temp_f0_16 * temp_f0_16)))));
			var_f5 = sp8;
		}
		return temp_f4 * (lbl_8042E00C / var_f5);
	}
	if (arg2 != NULL) {
		temp_f6_2 = arg0->p.x;
		temp_f3_3
		    = -(-((temp_f3 * arg1->p.z) + ((temp_f1 * arg1->p.x) + (temp_f0_13 * arg1->p.y)))
		          + ((temp_f3 * arg0->p.z) + ((temp_f1 * temp_f6_2) + (temp_f0_13 * arg0->p.y))))
		    / temp_f7;
		arg2->x = temp_f6_2 + (temp_f2 * temp_f3_3);
		arg2->y = arg0->p.y + (arg0->v.y * temp_f3_3);
		arg2->z = arg0->p.z + (arg0->v.z * temp_f3_3);
	}
	return lbl_8042E008;
}

f32 fn_800D605C(NJS_LINE* arg0, NJS_LINE* arg1, RwV3d* arg2, RwV3d* arg3)
{
	NJS_LINE sp58;
	NJS_LINE sp40;
	NJS_LINE sp28;
	volatile f32 sp24;
	volatile f32 sp20;
	volatile f32 sp1C;
	volatile f32 sp18;
	volatile f32 sp14;
	volatile f32 sp10;
	volatile f32 spC;
	volatile f32 sp8;
	f32 temp_f0;
	f32 temp_f0_10;
	f32 temp_f0_14;
	f32 temp_f0_18;
	f32 temp_f0_2;
	f32 temp_f0_3;
	f32 temp_f0_4;
	f32 temp_f0_5;
	f32 temp_f0_6;
	f32 temp_f10;
	f32 temp_f10_2;
	f32 temp_f10_3;
	f32 temp_f11;
	f32 temp_f11_2;
	f32 temp_f12;
	f32 temp_f12_2;
	f32 temp_f13;
	f32 temp_f1;
	f32 temp_f1_10;
	f32 temp_f1_11;
	f32 temp_f1_12;
	f32 temp_f1_16;
	f32 temp_f1_17;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f1_4;
	f32 temp_f1_5;
	f32 temp_f1_6;
	f32 temp_f1_7;
	f32 temp_f1_8;
	f32 temp_f1_9;
	f32 temp_f2;
	f32 temp_f2_2;
	f32 temp_f2_3;
	f32 temp_f2_4;
	f32 temp_f2_5;
	f32 temp_f2_6;
	f32 temp_f3;
	f32 temp_f3_2;
	f32 temp_f3_3;
	f32 temp_f3_4;
	f32 temp_f3_5;
	f32 temp_f3_6;
	f32 temp_f4;
	f32 temp_f4_2;
	f32 temp_f4_3;
	f32 temp_f4_4;
	f32 temp_f4_5;
	f32 temp_f4_6;
	f32 temp_f5;
	f32 temp_f5_2;
	f32 temp_f6;
	f32 temp_f6_2;
	f32 temp_f6_3;
	f32 temp_f6_4;
	f32 temp_f6_5;
	f32 temp_f6_6;
	f32 temp_f7;
	f32 temp_f7_2;
	f32 temp_f7_3;
	f32 temp_f7_4;
	f32 temp_f8;
	f32 temp_f8_2;
	f32 temp_f8_3;
	f32 temp_f8_4;
	f32 temp_f9;
	f32 temp_f9_2;
	f32 temp_f9_3;
	f32 var_f1;
	f32 var_f4;
	f32 var_f4_2;
	f32 var_f4_3;
	f32 var_f7;
	f64 temp_f0_11;
	f64 temp_f0_12;
	f64 temp_f0_13;
	f64 temp_f0_15;
	f64 temp_f0_16;
	f64 temp_f0_17;
	f64 temp_f0_7;
	f64 temp_f0_8;
	f64 temp_f0_9;
	f64 temp_f1_13;
	f64 temp_f1_14;
	f64 temp_f1_15;
	f64 temp_f4_7;
	f64 temp_f4_8;
	f64 temp_f4_9;

	temp_f10 = arg0->v.z;
	temp_f9  = arg1->v.z;
	temp_f3  = arg0->v.x;
	temp_f1  = arg1->v.x;
	temp_f2  = arg0->v.y;
	temp_f0  = arg1->v.y;
	temp_f4  = (temp_f10 * temp_f9) + ((temp_f3 * temp_f1) + (temp_f2 * temp_f0));
	if ((f32)__fabs((temp_f4 * temp_f4)
	        / (((temp_f10 * temp_f10) + ((temp_f3 * temp_f3) + (temp_f2 * temp_f2)))
	            * ((temp_f9 * temp_f9) + ((temp_f1 * temp_f1) + (temp_f0 * temp_f0)))))
	    > lbl_8042E02C) {
		if (arg2 != NULL) {
			arg2->x = arg0->p.x;
			arg2->y = arg0->p.y;
			arg2->z = arg0->p.z;
		}
		temp_f0_2  = arg0->p.x;
		temp_f1_2  = arg0->p.y;
		temp_f6    = arg0->p.z;
		temp_f7    = arg1->v.y;
		temp_f8    = arg1->v.x;
		temp_f9_2  = arg1->v.z;
		temp_f12   = arg1->p.z;
		temp_f10_2 = arg1->p.x;
		temp_f11   = arg1->p.y;
		temp_f4_2
		    = ((temp_f9_2 * (temp_f6 - temp_f12))
		          + ((temp_f8 * (temp_f0_2 - temp_f10_2)) + (temp_f7 * (temp_f1_2 - temp_f11))))
		    / ((temp_f9_2 * temp_f9_2) + ((temp_f8 * temp_f8) + (temp_f7 * temp_f7)));
		if (arg3 != NULL) {
			arg3->x   = temp_f10_2 + (temp_f8 * temp_f4_2);
			arg3->y   = arg1->p.y + (arg1->v.y * temp_f4_2);
			arg3->z   = arg1->p.z + (arg1->v.z * temp_f4_2);
			temp_f2_2 = temp_f6 - arg3->z;
			temp_f0_3 = temp_f0_2 - arg3->x;
			temp_f0_4 = temp_f1_2 - arg3->y;
			var_f1 = (temp_f2_2 * temp_f2_2) + ((temp_f0_3 * temp_f0_3) + (temp_f0_4 * temp_f0_4));
		} else {
			temp_f2_3 = temp_f6 - (temp_f12 + (temp_f9_2 * temp_f4_2));
			temp_f0_5 = temp_f0_2 - (temp_f10_2 + (temp_f8 * temp_f4_2));
			temp_f0_6 = temp_f1_2 - (temp_f11 + (temp_f7 * temp_f4_2));
			var_f1 = (temp_f2_3 * temp_f2_3) + ((temp_f0_5 * temp_f0_5) + (temp_f0_6 * temp_f0_6));
		}
		if (var_f1 < lbl_8042E028) {
			return lbl_8042E008;
		}
		if (var_f1 > lbl_8042E008) {
			temp_f0_7 = __frsqrte(var_f1);
			temp_f0_8 = lbl_8042E018 * temp_f0_7
			    * (lbl_8042E020 - ((f64)var_f1 * (temp_f0_7 * temp_f0_7)));
			temp_f0_9 = lbl_8042E018 * temp_f0_8
			    * (lbl_8042E020 - ((f64)var_f1 * (temp_f0_8 * temp_f0_8)));
			sp10 = (f32)((f64)var_f1
			    * (lbl_8042E018 * temp_f0_9
			        * (lbl_8042E020 - ((f64)var_f1 * (temp_f0_9 * temp_f0_9)))));
			return sp10;
		}
		/* Duplicate return node #31. Try simplifying control flow for better match */
		return var_f1;
	}
	sp58.p.x   = arg0->p.x;
	sp58.p.y   = arg0->p.y;
	sp58.p.z   = arg0->p.z;
	temp_f6_2  = (temp_f2 * temp_f9) - (temp_f10 * temp_f0);
	sp58.v.x   = temp_f6_2;
	temp_f4_3  = (temp_f10 * temp_f1) - (temp_f3 * temp_f9);
	sp58.v.y   = temp_f4_3;
	temp_f0_10 = (temp_f3 * temp_f0) - (temp_f2 * temp_f1);
	sp58.v.z   = temp_f0_10;
	var_f4     = (temp_f0_10 * temp_f0_10) + ((temp_f6_2 * temp_f6_2) + (temp_f4_3 * temp_f4_3));
	if (var_f4 > lbl_8042E008) {
		temp_f0_11 = __frsqrte(var_f4);
		temp_f0_12 = lbl_8042E018 * temp_f0_11
		    * (lbl_8042E020 - ((f64)var_f4 * (temp_f0_11 * temp_f0_11)));
		temp_f0_13 = lbl_8042E018 * temp_f0_12
		    * (lbl_8042E020 - ((f64)var_f4 * (temp_f0_12 * temp_f0_12)));
		sp18   = (f32)((f64)var_f4
		    * (lbl_8042E018 * temp_f0_13
		        * (lbl_8042E020 - ((f64)var_f4 * (temp_f0_13 * temp_f0_13)))));
		var_f4 = sp18;
	}
	temp_f1_3  = lbl_8042E00C / var_f4;
	temp_f8_2  = sp58.v.x * temp_f1_3;
	sp58.v.x   = temp_f8_2;
	temp_f7_2  = sp58.v.y * temp_f1_3;
	sp58.v.y   = temp_f7_2;
	temp_f6_3  = sp58.v.z * temp_f1_3;
	sp58.v.z   = temp_f6_3;
	sp40.p.x   = arg1->p.x;
	sp40.p.y   = arg1->p.y;
	sp40.p.z   = arg1->p.z;
	temp_f3_2  = arg1->v.z;
	temp_f5    = arg1->v.y;
	temp_f4_4  = (temp_f7_2 * temp_f3_2) - (temp_f6_3 * temp_f5);
	sp40.v.x   = temp_f4_4;
	temp_f2_4  = arg1->v.x;
	temp_f3_3  = (temp_f6_3 * temp_f2_4) - (temp_f8_2 * temp_f3_2);
	sp40.v.y   = temp_f3_3;
	temp_f0_14 = (temp_f8_2 * temp_f5) - (temp_f7_2 * temp_f2_4);
	sp40.v.z   = temp_f0_14;
	var_f4_2   = (temp_f0_14 * temp_f0_14) + ((temp_f4_4 * temp_f4_4) + (temp_f3_3 * temp_f3_3));
	if (var_f4_2 > lbl_8042E008) {
		temp_f0_15 = __frsqrte(var_f4_2);
		temp_f0_16 = lbl_8042E018 * temp_f0_15
		    * (lbl_8042E020 - ((f64)var_f4_2 * (temp_f0_15 * temp_f0_15)));
		temp_f0_17 = lbl_8042E018 * temp_f0_16
		    * (lbl_8042E020 - ((f64)var_f4_2 * (temp_f0_16 * temp_f0_16)));
		sp14     = (f32)((f64)var_f4_2
		    * (lbl_8042E018 * temp_f0_17
		        * (lbl_8042E020 - ((f64)var_f4_2 * (temp_f0_17 * temp_f0_17)))));
		var_f4_2 = sp14;
	}
	temp_f1_4 = lbl_8042E00C / var_f4_2;
	sp40.v.x  = sp40.v.x * temp_f1_4;
	sp40.v.y *= temp_f1_4;
	sp40.v.z *= temp_f1_4;
	fn_800D6958(&sp58, &sp40, &sp28);
	temp_f7_3 = arg0->v.x;
	temp_f6_4 = -sp28.v.y;
	temp_f1_5 = arg0->v.y;
	temp_f5_2 = -sp28.v.x;
	temp_f3_4 = (temp_f7_3 * temp_f6_4) - (temp_f1_5 * temp_f5_2);
	if ((f32)__fabs(temp_f3_4) > lbl_8042E028) {
		var_f4_3 = ((temp_f6_4 * (sp28.p.x - arg0->p.x)) - (temp_f5_2 * (sp28.p.y - arg0->p.y)))
		    / temp_f3_4;
	} else {
		temp_f3_5 = -sp28.v.z;
		temp_f2_5 = arg0->v.z;
		temp_f8_3 = (temp_f1_5 * temp_f3_5) - (temp_f2_5 * temp_f6_4);
		if ((f32)__fabs(temp_f8_3) > lbl_8042E028) {
			var_f4_3 = ((temp_f3_5 * (sp28.p.y - arg0->p.y)) - (temp_f6_4 * (sp28.p.z - arg0->p.z)))
			    / temp_f8_3;
		} else {
			var_f4_3 = ((temp_f3_5 * (sp28.p.x - arg0->p.x)) - (temp_f5_2 * (sp28.p.z - arg0->p.z)))
			    / ((temp_f7_3 * temp_f3_5) - (temp_f2_5 * temp_f5_2));
		}
	}
	temp_f0_18 = arg0->p.x + (arg0->v.x * var_f4_3);
	temp_f2_6  = arg0->p.y + (arg0->v.y * var_f4_3);
	temp_f3_6  = arg0->p.z + (arg0->v.z * var_f4_3);
	temp_f8_4  = arg1->v.y;
	temp_f9_3  = arg1->v.x;
	temp_f10_3 = arg1->v.z;
	temp_f13   = arg1->p.z;
	temp_f11_2 = arg1->p.x;
	temp_f12_2 = arg1->p.y;
	temp_f7_4
	    = ((temp_f10_3 * (temp_f3_6 - temp_f13))
	          + ((temp_f9_3 * (temp_f0_18 - temp_f11_2)) + (temp_f8_4 * (temp_f2_6 - temp_f12_2))))
	    / ((temp_f10_3 * temp_f10_3) + ((temp_f9_3 * temp_f9_3) + (temp_f8_4 * temp_f8_4)));
	if (&sp1C != NULL) {
		temp_f4_5 = temp_f11_2 + (temp_f9_3 * temp_f7_4);
		sp1C      = temp_f4_5;
		temp_f6_5 = temp_f12_2 + (temp_f8_4 * temp_f7_4);
		sp20      = temp_f6_5;
		temp_f1_6 = temp_f13 + (temp_f10_3 * temp_f7_4);
		sp24      = temp_f1_6;
		temp_f1_7 = temp_f3_6 - temp_f1_6;
		temp_f1_8 = temp_f0_18 - temp_f4_5;
		temp_f1_9 = temp_f2_6 - temp_f6_5;
		var_f7    = (temp_f1_7 * temp_f1_7) + ((temp_f1_8 * temp_f1_8) + (temp_f1_9 * temp_f1_9));
	} else {
		temp_f1_10 = temp_f3_6 - (temp_f13 + (temp_f10_3 * temp_f7_4));
		temp_f1_11 = temp_f0_18 - (temp_f11_2 + (temp_f9_3 * temp_f7_4));
		temp_f1_12 = temp_f2_6 - (temp_f12_2 + (temp_f8_4 * temp_f7_4));
		var_f7
		    = (temp_f1_10 * temp_f1_10) + ((temp_f1_11 * temp_f1_11) + (temp_f1_12 * temp_f1_12));
	}
	if (!(var_f7 < lbl_8042E028) && (var_f7 > lbl_8042E008)) {
		temp_f1_13 = __frsqrte(var_f7);
		temp_f1_14 = lbl_8042E018 * temp_f1_13
		    * (lbl_8042E020 - ((f64)var_f7 * (temp_f1_13 * temp_f1_13)));
		temp_f1_15 = lbl_8042E018 * temp_f1_14
		    * (lbl_8042E020 - ((f64)var_f7 * (temp_f1_14 * temp_f1_14)));
		spC = (f32)((f64)var_f7
		    * (lbl_8042E018 * temp_f1_15
		        * (lbl_8042E020 - ((f64)var_f7 * (temp_f1_15 * temp_f1_15)))));
	}
	temp_f4_6  = temp_f0_18 - sp1C;
	temp_f6_6  = temp_f2_6 - sp20;
	temp_f1_16 = temp_f3_6 - sp24;
	var_f1     = (temp_f1_16 * temp_f1_16) + ((temp_f4_6 * temp_f4_6) + (temp_f6_6 * temp_f6_6));
	if (var_f1 > lbl_8042E008) {
		temp_f4_7 = __frsqrte(var_f1);
		temp_f4_8
		    = lbl_8042E018 * temp_f4_7 * (lbl_8042E020 - ((f64)var_f1 * (temp_f4_7 * temp_f4_7)));
		temp_f4_9
		    = lbl_8042E018 * temp_f4_8 * (lbl_8042E020 - ((f64)var_f1 * (temp_f4_8 * temp_f4_8)));
		temp_f1_17 = (f32)((f64)var_f1
		    * (lbl_8042E018 * temp_f4_9
		        * (lbl_8042E020 - ((f64)var_f1 * (temp_f4_9 * temp_f4_9)))));
		sp8        = temp_f1_17;
		var_f1     = sp8;
	}
	if (arg2 != NULL) {
		arg2->x = temp_f0_18;
		arg2->y = temp_f2_6;
		arg2->z = temp_f3_6;
	}
	if (arg3 != NULL) {
		arg3->x = sp1C;
		arg3->y = sp20;
		arg3->z = sp24;
	}
	return var_f1;
}

f32 fn_800D67D4(f32 farg0)
{
	if (farg0 < lbl_8042E008) {
		return -(f32)floor(-farg0);
	}
	return (f32)floor((f64)farg0);
}

f32 fn_800D6818(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2)
{
	arg2->x = (arg0->y * arg1->z) - (arg0->z * arg1->y);
	arg2->y = (arg0->z * arg1->x) - (arg0->x * arg1->z);
	arg2->z = (arg0->x * arg1->y) - (arg0->y * arg1->x);
	return fn_801991B4(arg2);
}

f32 fn_800D689C(RwV3d* arg0, RwV3d* arg1, NJS_LINE* arg2)
{

	if (arg2 != NULL) {
		if (((arg0->z * arg1->z) + ((arg0->x * arg1->x) + (arg0->y * arg1->y))) > lbl_8042E02C) {
			arg2->v.x = lbl_8042E008;
			arg2->v.y = lbl_8042E008;
			arg2->v.z = lbl_8042E008;
		} else {
			arg2->v.x = (arg0->y * arg1->z) - (arg1->y * arg0->z);
			arg2->v.y = (arg0->z * arg1->x) - (arg1->z * arg0->x);
			arg2->v.z = (arg0->x * arg1->y) - (arg1->x * arg0->y);
		}
		arg2->p.x = lbl_8042E008;
		arg2->p.y = lbl_8042E008;
		arg2->p.z = lbl_8042E008;
	}
	return lbl_8042E008;
}

f32 fn_800D6958(NJS_LINE* arg0, NJS_LINE* arg1, NJS_LINE* arg2)
{
	volatile f32 sp10;
	volatile f32 spC;
	volatile f32 sp8;
	f32 temp_f0;
	f32 temp_f0_2;
	f32 temp_f0_3;
	f32 temp_f0_4;
	f32 temp_f0_8;
	f32 temp_f10;
	f32 temp_f10_2;
	f32 temp_f11;
	f32 temp_f11_2;
	f32 temp_f12;
	f32 temp_f13;
	f32 temp_f1_10;
	f32 temp_f1_11;
	f32 temp_f1_4;
	f32 temp_f1_5;
	f32 temp_f1_6;
	f32 temp_f25;
	f32 temp_f27;
	f32 temp_f28;
	f32 temp_f29;
	f32 temp_f2;
	f32 temp_f2_2;
	f32 temp_f30;
	f32 temp_f31;
	f32 temp_f3;
	f32 temp_f3_2;
	f32 temp_f4;
	f32 temp_f4_2;
	f32 temp_f5;
	f32 temp_f6;
	f32 temp_f6_2;
	f32 temp_f6_3;
	f32 temp_f7;
	f32 temp_f7_2;
	f32 temp_f7_3;
	f32 temp_f8;
	f32 temp_f8_2;
	f32 temp_f9;
	f32 temp_f9_2;
	f32 temp_f9_3;
	f32 var_f0;
	f32 var_f5;
	f32 var_f8;
	f64 temp_f0_5;
	f64 temp_f0_6;
	f64 temp_f0_7;
	f64 temp_f1;
	f64 temp_f1_2;
	f64 temp_f1_3;
	f64 temp_f1_7;
	f64 temp_f1_8;
	f64 temp_f1_9;

	temp_f0   = arg0->v.z;
	temp_f0_2 = arg0->v.x;
	temp_f0_3 = arg0->v.y;
	var_f0    = (temp_f0 * temp_f0) + ((temp_f0_2 * temp_f0_2) + (temp_f0_3 * temp_f0_3));
	if (var_f0 > lbl_8042E008) {
		temp_f1   = __frsqrte(var_f0);
		temp_f1_2 = lbl_8042E018 * temp_f1 * (lbl_8042E020 - ((f64)var_f0 * (temp_f1 * temp_f1)));
		temp_f1_3
		    = lbl_8042E018 * temp_f1_2 * (lbl_8042E020 - ((f64)var_f0 * (temp_f1_2 * temp_f1_2)));
		temp_f0_4 = (f32)((f64)var_f0
		    * (lbl_8042E018 * temp_f1_3
		        * (lbl_8042E020 - ((f64)var_f0 * (temp_f1_3 * temp_f1_3)))));
		sp10      = temp_f0_4;
		var_f0    = sp10;
	}
	temp_f1_4 = arg1->v.z;
	temp_f1_5 = arg1->v.x;
	temp_f1_6 = arg1->v.y;
	var_f8    = (temp_f1_4 * temp_f1_4) + ((temp_f1_5 * temp_f1_5) + (temp_f1_6 * temp_f1_6));
	if (var_f8 > lbl_8042E008) {
		temp_f1_7 = __frsqrte(var_f8);
		temp_f1_8
		    = lbl_8042E018 * temp_f1_7 * (lbl_8042E020 - ((f64)var_f8 * (temp_f1_7 * temp_f1_7)));
		temp_f1_9
		    = lbl_8042E018 * temp_f1_8 * (lbl_8042E020 - ((f64)var_f8 * (temp_f1_8 * temp_f1_8)));
		spC    = (f32)((f64)var_f8
		    * (lbl_8042E018 * temp_f1_9
		        * (lbl_8042E020 - ((f64)var_f8 * (temp_f1_9 * temp_f1_9)))));
		var_f8 = spC;
	}
	temp_f7 = arg0->v.z;
	temp_f6 = arg1->v.z;
	temp_f3 = arg0->v.y;
	temp_f2 = arg1->v.y;
	if ((f32)__fabs(((temp_f7 * temp_f6) + ((arg0->v.x * arg1->v.x) + (temp_f3 * temp_f2)))
	        / (var_f0 * var_f8))
	    > lbl_8042E02C) {
		if (arg2 != NULL) {
			arg2->p.x = lbl_8042E008;
			arg2->p.y = lbl_8042E008;
			arg2->p.z = lbl_8042E008;
			arg2->v.x = lbl_8042E008;
			arg2->v.y = lbl_8042E008;
			arg2->v.z = lbl_8042E008;
		}
		temp_f7_2 = arg1->v.y;
		temp_f8   = arg1->v.x;
		temp_f9   = arg1->v.z;
		var_f5    = (temp_f9 * temp_f9) + ((temp_f8 * temp_f8) + (temp_f7_2 * temp_f7_2));
		temp_f4   = (f32)__fabs(
		    -((temp_f9 * arg1->p.z) + ((temp_f8 * arg1->p.x) + (temp_f7_2 * arg1->p.y)))
		    + ((temp_f9 * arg0->p.z) + ((temp_f8 * arg0->p.x) + (temp_f7_2 * arg0->p.y))));
		if (var_f5 > lbl_8042E008) {
			temp_f0_5 = __frsqrte(var_f5);
			temp_f0_6 = lbl_8042E018 * temp_f0_5
			    * (lbl_8042E020 - ((f64)var_f5 * (temp_f0_5 * temp_f0_5)));
			temp_f0_7 = lbl_8042E018 * temp_f0_6
			    * (lbl_8042E020 - ((f64)var_f5 * (temp_f0_6 * temp_f0_6)));
			sp8    = (f32)((f64)var_f5
			    * (lbl_8042E018 * temp_f0_7
			        * (lbl_8042E020 - ((f64)var_f5 * (temp_f0_7 * temp_f0_7)))));
			var_f5 = sp8;
		}
		return temp_f4 * (lbl_8042E00C / var_f5);
	}
	if (arg2 != NULL) {
		arg2->v.x  = (temp_f3 * temp_f6) - (temp_f2 * temp_f7);
		arg2->v.y  = (arg0->v.z * arg1->v.x) - (arg1->v.z * arg0->v.x);
		arg2->v.z  = (arg0->v.x * arg1->v.y) - (arg1->v.x * arg0->v.y);
		temp_f7_3  = arg0->v.z;
		temp_f4_2  = arg0->v.x;
		temp_f1_10 = arg0->v.y;
		temp_f30   = (temp_f7_3 * arg0->p.z) + ((temp_f4_2 * arg0->p.x) + (temp_f1_10 * arg0->p.y));
		temp_f0_8  = arg1->v.z;
		temp_f11   = arg1->p.z;
		temp_f8_2  = arg1->v.x;
		temp_f10   = arg1->p.x;
		temp_f3_2  = arg1->v.y;
		temp_f9_2  = arg1->p.y;
		temp_f29   = (temp_f0_8 * temp_f11) + ((temp_f8_2 * temp_f10) + (temp_f3_2 * temp_f9_2));
		temp_f5    = arg2->v.z;
		temp_f2_2  = arg2->v.x;
		temp_f6_2  = arg2->v.y;
		temp_f28   = (temp_f5 * temp_f11) + ((temp_f2_2 * temp_f10) + (temp_f6_2 * temp_f9_2));
		temp_f13   = temp_f7_3 * temp_f6_2;
		temp_f9_3  = temp_f4_2 * temp_f3_2;
		temp_f12   = temp_f1_10 * temp_f0_8;
		temp_f31   = temp_f7_3 * temp_f3_2;
		temp_f10_2 = temp_f1_10 * temp_f8_2;
		temp_f11_2 = temp_f4_2 * temp_f6_2;
		temp_f27   = lbl_8042E00C
		    / (((((temp_f8_2 * temp_f13) + ((temp_f5 * temp_f9_3) + (temp_f2_2 * temp_f12)))
		            - (temp_f2_2 * temp_f31))
		           - (temp_f5 * temp_f10_2))
		        - (temp_f0_8 * temp_f11_2));
		temp_f6_3  = temp_f30 * temp_f6_2;
		temp_f1_11 = temp_f1_10 * temp_f29;
		temp_f25   = temp_f30 * temp_f3_2;
		arg2->p.x  = (((((temp_f29 * temp_f13) + ((temp_f5 * temp_f25) + (temp_f28 * temp_f12)))
		                   - (temp_f28 * temp_f31))
		                  - (temp_f5 * temp_f1_11))
		                 - (temp_f0_8 * temp_f6_3))
		    * temp_f27;
		arg2->p.y
		    = (((((temp_f8_2 * (temp_f7_3 * temp_f28))
		             + ((temp_f5 * (temp_f4_2 * temp_f29)) + (temp_f2_2 * (temp_f30 * temp_f0_8))))
		            - (temp_f2_2 * (temp_f7_3 * temp_f29)))
		           - (temp_f5 * (temp_f30 * temp_f8_2)))
		          - (temp_f0_8 * (temp_f4_2 * temp_f28)))
		    * temp_f27;
		arg2->p.z
		    = (((((temp_f8_2 * temp_f6_3) + ((temp_f28 * temp_f9_3) + (temp_f2_2 * temp_f1_11)))
		            - (temp_f2_2 * temp_f25))
		           - (temp_f28 * temp_f10_2))
		          - (temp_f29 * temp_f11_2))
		    * temp_f27;
	}
	return lbl_8042E008;
}

f32 fn_800D6E0C(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2)
{
	volatile f32 sp8;
	f32 temp_f0;
	f32 temp_f3_2;
	f32 temp_f5;
	f32 temp_f7;
	f32 var_f0;
	f64 temp_f1;
	f64 temp_f1_2;
	f64 temp_f1_3;

	temp_f7 = (arg1->z * arg0->z) + ((arg1->x * arg0->x) + (arg1->y * arg0->y));
	var_f0  = (arg1->z * arg1->z) + ((arg1->x * arg1->x) + (arg1->y * arg1->y));
	if (arg2 != NULL) {
		temp_f3_2 = -temp_f7 / var_f0;
		arg2->x   = arg0->x + (arg1->x * temp_f3_2);
		arg2->y   = arg0->y + (arg1->y * temp_f3_2);
		arg2->z   = arg0->z + (arg1->z * temp_f3_2);
	}
	temp_f5 = (f32)__fabs(temp_f7);
	if (var_f0 > lbl_8042E008) {
		temp_f1   = __frsqrte(var_f0);
		temp_f1_2 = lbl_8042E018 * temp_f1 * (lbl_8042E020 - ((f64)var_f0 * (temp_f1 * temp_f1)));
		temp_f1_3
		    = lbl_8042E018 * temp_f1_2 * (lbl_8042E020 - ((f64)var_f0 * (temp_f1_2 * temp_f1_2)));
		temp_f0 = (f32)((f64)var_f0
		    * (lbl_8042E018 * temp_f1_3
		        * (lbl_8042E020 - ((f64)var_f0 * (temp_f1_3 * temp_f1_3)))));
		sp8     = temp_f0;
		var_f0  = sp8;
	}
	return temp_f5 / var_f0;
}

f32 fn_800D6F0C(RwV3d* arg0, NJS_LINE* arg1, RwV3d* arg2)
{
	volatile f32 sp8;
	f32 temp_f0;
	f32 temp_f3;
	f32 temp_f4_2;
	f32 temp_f5;
	f32 var_f1;
	f64 temp_f1;
	f64 temp_f1_2;
	f64 temp_f1_3;

	temp_f3 = -((arg1->v.z * arg1->p.z) + ((arg1->v.x * arg1->p.x) + (arg1->v.y * arg1->p.y)))
	    + ((arg1->v.z * arg0->z) + ((arg1->v.x * arg0->x) + (arg1->v.y * arg0->y)));
	temp_f0 = (arg1->v.z * arg1->v.z) + ((arg1->v.x * arg1->v.x) + (arg1->v.y * arg1->v.y));
	if (arg2 != NULL) {
		temp_f4_2 = -temp_f3 / temp_f0;
		arg2->x   = arg0->x + (arg1->v.x * temp_f4_2);
		arg2->y   = arg0->y + (arg1->v.y * temp_f4_2);
		arg2->z   = arg0->z + (arg1->v.z * temp_f4_2);
	}
	temp_f5 = (f32)__fabs(temp_f3);
	if (temp_f0 > lbl_8042E008) {
		temp_f1   = __frsqrte(temp_f0);
		temp_f1_2 = lbl_8042E018 * temp_f1 * (lbl_8042E020 - ((f64)temp_f0 * (temp_f1 * temp_f1)));
		temp_f1_3
		    = lbl_8042E018 * temp_f1_2 * (lbl_8042E020 - ((f64)temp_f0 * (temp_f1_2 * temp_f1_2)));
		sp8    = (f32)((f64)temp_f0
		    * (lbl_8042E018 * temp_f1_3
		        * (lbl_8042E020 - ((f64)temp_f0 * (temp_f1_3 * temp_f1_3)))));
		var_f1 = sp8;
	} else {
		var_f1 = temp_f0;
	}
	return temp_f5 * (lbl_8042E00C / var_f1);
}

f32 fn_800D7044(RwV3d* arg0, NJS_LINE* arg1, RwV3d* arg2)
{
	volatile f32 sp8;
	f32 temp_f0;
	f32 temp_f0_2;
	f32 temp_f0_3;
	f32 temp_f0_4;
	f32 temp_f0_5;
	f32 temp_f0_6;
	f32 temp_f10;
	f32 temp_f11;
	f32 temp_f12;
	f32 temp_f3;
	f32 temp_f4;
	f32 temp_f5;
	f32 temp_f6;
	f32 temp_f7;
	f32 temp_f8;
	f32 temp_f9;
	f32 var_f4;
	f64 temp_f0_7;
	f64 temp_f0_8;
	f64 temp_f0_9;

	temp_f4  = arg1->v.y;
	temp_f5  = arg1->v.x;
	temp_f6  = arg1->v.z;
	temp_f12 = arg0->z;
	temp_f11 = arg1->p.z;
	temp_f10 = arg0->x;
	temp_f7  = arg1->p.x;
	temp_f9  = arg0->y;
	temp_f8  = arg1->p.y;
	temp_f3  = ((temp_f6 * (temp_f12 - temp_f11))
	               + ((temp_f5 * (temp_f10 - temp_f7)) + (temp_f4 * (temp_f9 - temp_f8))))
	    / ((temp_f6 * temp_f6) + ((temp_f5 * temp_f5) + (temp_f4 * temp_f4)));
	if (arg2 != NULL) {
		arg2->x   = temp_f7 + (temp_f5 * temp_f3);
		arg2->y   = arg1->p.y + (arg1->v.y * temp_f3);
		arg2->z   = arg1->p.z + (arg1->v.z * temp_f3);
		temp_f0   = arg0->z - arg2->z;
		temp_f0_2 = arg0->x - arg2->x;
		temp_f0_3 = arg0->y - arg2->y;
		var_f4    = (temp_f0 * temp_f0) + ((temp_f0_2 * temp_f0_2) + (temp_f0_3 * temp_f0_3));
	} else {
		temp_f0_4 = temp_f12 - (temp_f11 + (temp_f6 * temp_f3));
		temp_f0_5 = temp_f10 - (temp_f7 + (temp_f5 * temp_f3));
		temp_f0_6 = temp_f9 - (temp_f8 + (temp_f4 * temp_f3));
		var_f4    = (temp_f0_4 * temp_f0_4) + ((temp_f0_5 * temp_f0_5) + (temp_f0_6 * temp_f0_6));
	}
	if (var_f4 < lbl_8042E028) {
		return lbl_8042E008;
	}
	if (var_f4 > lbl_8042E008) {
		temp_f0_7 = __frsqrte(var_f4);
		temp_f0_8
		    = lbl_8042E018 * temp_f0_7 * (lbl_8042E020 - ((f64)var_f4 * (temp_f0_7 * temp_f0_7)));
		temp_f0_9
		    = lbl_8042E018 * temp_f0_8 * (lbl_8042E020 - ((f64)var_f4 * (temp_f0_8 * temp_f0_8)));
		sp8 = (f32)((f64)var_f4
		    * (lbl_8042E018 * temp_f0_9
		        * (lbl_8042E020 - ((f64)var_f4 * (temp_f0_9 * temp_f0_9)))));
		return sp8;
	}
	return var_f4;
}

f32 fn_800D71DC(RwV3d* arg0, RwV3d* arg1)
{
	f32 temp_f0;
	f32 temp_f3;
	f32 temp_f4;

	temp_f3 = arg0->x - arg1->x;
	temp_f4 = arg0->y - arg1->y;
	temp_f0 = arg0->z - arg1->z;
	return (temp_f0 * temp_f0) + ((temp_f3 * temp_f3) + (temp_f4 * temp_f4));
}

f32 fn_800D7218(RwV3d* arg0, RwV3d* arg1)
{
	volatile f32 sp8;
	f32 temp_f0;
	f32 temp_f3;
	f32 temp_f4;
	f32 var_f1;
	f64 temp_f0_2;
	f64 temp_f0_3;
	f64 temp_f0_4;

	temp_f3 = arg0->x - arg1->x;
	temp_f4 = arg0->y - arg1->y;
	temp_f0 = arg0->z - arg1->z;
	var_f1  = (temp_f0 * temp_f0) + ((temp_f3 * temp_f3) + (temp_f4 * temp_f4));
	if (var_f1 > lbl_8042E008) {
		temp_f0_2 = __frsqrte(var_f1);
		temp_f0_3
		    = lbl_8042E018 * temp_f0_2 * (lbl_8042E020 - ((f64)var_f1 * (temp_f0_2 * temp_f0_2)));
		temp_f0_4
		    = lbl_8042E018 * temp_f0_3 * (lbl_8042E020 - ((f64)var_f1 * (temp_f0_3 * temp_f0_3)));
		sp8    = (f32)((f64)var_f1
		    * (lbl_8042E018 * temp_f0_4
		        * (lbl_8042E020 - ((f64)var_f1 * (temp_f0_4 * temp_f0_4)))));
		var_f1 = sp8;
	}
	return var_f1;
}

void fn_800D72C0(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2)
{
	arg2->x = arg0->x - arg1->x;
	arg2->y = arg0->y - arg1->y;
	arg2->z = arg0->z - arg1->z;
}

void fn_800D72F4(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2)
{
	arg2->x = arg0->x + arg1->x;
	arg2->y = arg0->y + arg1->y;
	arg2->z = arg0->z + arg1->z;
}

f32 fn_800D7328(f32 farg0, f32 farg1, f32 farg2)
{
	f32 var_f1;

	var_f1 = farg0;
	if (var_f1 > farg1) {
		var_f1 -= farg2;
		if (var_f1 < farg1) {
			return farg1;
		}
		/* Duplicate return node #7. Try simplifying control flow for better match */
		return var_f1;
	}
	if (var_f1 < farg1) {
		var_f1 += farg2;
		if (var_f1 > farg1) {
			return farg1;
		}
	}
	return var_f1;
}

void fn_800D735C(RwV3d* arg0, RwV3d* arg1, s32* arg2)
{
	volatile f32 spC;
	volatile f32 sp8;
	f32 temp_f0;
	f32 temp_f0_2;
	f32 temp_f0_6;
	f32 temp_f0_7;
	f32 var_f31;
	f32 var_f31_2;
	f64 temp_f0_10;
	f64 temp_f0_3;
	f64 temp_f0_4;
	f64 temp_f0_5;
	f64 temp_f0_8;
	f64 temp_f0_9;

	temp_f0   = arg0->x;
	temp_f0_2 = arg0->z;
	var_f31   = (temp_f0 * temp_f0) + (temp_f0_2 * temp_f0_2);
	if (var_f31 > lbl_8042E008) {
		temp_f0_3 = __frsqrte(var_f31);
		temp_f0_4
		    = lbl_8042E018 * temp_f0_3 * (lbl_8042E020 - ((f64)var_f31 * (temp_f0_3 * temp_f0_3)));
		temp_f0_5
		    = lbl_8042E018 * temp_f0_4 * (lbl_8042E020 - ((f64)var_f31 * (temp_f0_4 * temp_f0_4)));
		spC     = (f32)((f64)var_f31
		    * (lbl_8042E018 * temp_f0_5
		        * (lbl_8042E020 - ((f64)var_f31 * (temp_f0_5 * temp_f0_5)))));
		var_f31 = spC;
	}
	arg2[1] = (s32)(lbl_8042E030 * (f32)atan2((f64)arg0->x, -arg0->z));
	arg2[2] = (s32)(lbl_8042E030 * (f32)atan2(-arg0->y, (f64)var_f31));
	if (arg1 != NULL) {
		temp_f0_6 = arg1->x;
		temp_f0_7 = arg1->z;
		var_f31_2 = (temp_f0_6 * temp_f0_6) + (temp_f0_7 * temp_f0_7);
		if (var_f31_2 > lbl_8042E008) {
			temp_f0_8 = __frsqrte(var_f31_2);
			temp_f0_9 = lbl_8042E018 * temp_f0_8
			    * (lbl_8042E020 - ((f64)var_f31_2 * (temp_f0_8 * temp_f0_8)));
			temp_f0_10 = lbl_8042E018 * temp_f0_9
			    * (lbl_8042E020 - ((f64)var_f31_2 * (temp_f0_9 * temp_f0_9)));
			sp8       = (f32)((f64)var_f31_2
			    * (lbl_8042E018 * temp_f0_10
			        * (lbl_8042E020 - ((f64)var_f31_2 * (temp_f0_10 * temp_f0_10)))));
			var_f31_2 = sp8;
		}
		arg2[1] = (s32)(arg2[1] - (s32)(lbl_8042E030 * (f32)atan2((f64)arg1->x, -arg1->z)));
		arg2[2] = (s32)(arg2[2] - (s32)(lbl_8042E030 * (f32)atan2(-arg1->y, (f64)var_f31_2)));
	}
}

f32 fn_800D7564(f32 farg0, f32 farg1)
{
	if (lbl_8042E008 == farg1) {
		return lbl_8042E008;
	}
	return farg0 - (farg1 * (f32)floor((f64)(farg0 / farg1)));
}

static inline f32 fn_800D75CCSqrt(f32 value, f32 zero)
{
	if (value > zero) {
		f64 estimate = __frsqrte(value);
		estimate     = lbl_8042E018 * estimate * (lbl_8042E020 - estimate * estimate * value);
		estimate     = lbl_8042E018 * estimate * (lbl_8042E020 - estimate * estimate * value);
		estimate     = lbl_8042E018 * estimate * (lbl_8042E020 - estimate * estimate * value);
		volatile f32 result = (f32)(value * estimate);
		return result;
	}
	return value;
}

static inline f32 fn_800D75CCDot(const RwV3d& left, const RwV3d& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

static inline f32 fn_800D75CCDotNormal(const RwV3d& value, f32 normalX, f32 normalY, f32 normalZ)
{
	return normalX * value.x + normalY * value.y + normalZ * value.z;
}

static inline f32 fn_800D75CCProject(const RwV3d& value, f32 normalX, f32 normalY, f32 normalZ,
    f32 numerator, f32 lengthSq, RwV3d* result)
{
	if (result != 0) {
		f32 scale = -numerator / lengthSq;
		result->x = value.x + normalX * scale;
		result->y = value.y + normalY * scale;
		result->z = value.z + normalZ * scale;
	}
	f32 zero = lbl_8042E008;
	return fn_800D75CCSqrt(lengthSq, zero);
}

s32 fn_800D75CC(const RwV3d* first, const RwV3d* second, const RwV3d* planeNormal)
{
	RwV3d projectedFirst;
	RwV3d projectedSecond;
	f32 normalX        = planeNormal->x;
	f32 normalY        = planeNormal->y;
	f32 normalZ        = planeNormal->z;
	f32 initialZero    = lbl_8042E008;
	f32 planeOffset    = -(normalX * initialZero + normalY * initialZero + normalZ * initialZero);
	f32 firstDot       = fn_800D75CCDotNormal(*first, normalX, normalY, normalZ);
	f32 firstNumerator = planeOffset + firstDot;
	f32 lengthSq       = normalX * normalX + normalY * normalY + normalZ * normalZ;
	fn_800D75CCProject(
	    *first, normalX, normalY, normalZ, firstNumerator, lengthSq, &projectedFirst);
	f32 secondNumerator = fn_800D75CCDotNormal(*second, normalX, normalY, normalZ);
	secondNumerator += planeOffset;
	fn_800D75CCProject(
	    *second, normalX, normalY, normalZ, secondNumerator, lengthSq, &projectedSecond);

	if (fn_800D75CCDot(projectedFirst, projectedFirst) <= lbl_8042E034) {
		return -1;
	}
	if (fn_800D75CCDot(projectedSecond, projectedSecond) <= lbl_8042E034) {
		return -1;
	}

	fn_801990E0(&projectedFirst, &projectedFirst);
	fn_801990E0(&projectedSecond, &projectedSecond);

	f32 dot = fn_800D75CCDot(projectedFirst, projectedSecond);
	if (dot <= lbl_8042E038)
		return 0x8000;
	if (dot >= lbl_8042E00C)
		return 0;

	s32 angle = (s32)(lbl_8042E030 * (f32)acos(dot));
	RwV3d cross;
	cross.x = projectedFirst.y * projectedSecond.z - projectedFirst.z * projectedSecond.y;
	cross.y = projectedFirst.z * projectedSecond.x - projectedFirst.x * projectedSecond.z;
	cross.z = projectedFirst.x * projectedSecond.y - projectedFirst.y * projectedSecond.x;
	if (planeNormal != 0) {
		if (lbl_8042E008 > fn_800D75CCDot(*planeNormal, cross)) {
			angle = 0x10000 - angle;
		}
	}
	return angle;
}

static f32 fn_800D7920Dot(const RwV3d& left, const RwV3d& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

s32 fn_800D7920(const RwV3d* first, const RwV3d* second, const RwV3d* orientation)
{
	f32 dot = fn_800D7920Dot(*first, *second);
	if (dot <= lbl_8042E038)
		return 0x8000;
	if (dot >= lbl_8042E00C)
		return 0;

	s32 angle = (s32)(lbl_8042E030 * (f32)acos(dot));
	RwV3d cross;
	cross.x = first->y * second->z - first->z * second->y;
	cross.y = first->z * second->x - first->x * second->z;
	cross.z = first->x * second->y - first->y * second->x;
	if (orientation != 0 && lbl_8042E008 > fn_800D7920Dot(*orientation, cross)) {
		return 0x10000 - angle;
	}
	return angle;
}

u16 fn_800D7A54(u32 first, u32 second)
{
	u16 firstAngle  = (u16)first;
	u16 secondAngle = (u16)second;
	s16 difference  = (s16)(secondAngle - firstAngle);
	s16 result;
	if (difference < 0) {
		result = (s16)-difference;
	} else {
		result = difference;
	}
	return (u16)(s16)result;
}

s16 fn_800D7A80(u32 first, u32 second)
{
	u16 firstAngle  = (u16)first;
	u16 secondAngle = (u16)second;
	return (s16)(secondAngle - firstAngle);
}

u16 fn_800D7A94(u32 first, u32 second, s32 limit)
{
	u16 firstAngle = (u16)first;
	first          = (u16)second;
	s16 difference = (s16)(first - firstAngle);
	if (difference <= limit) {
		if (difference >= -limit)
			return (u16)first;
	}
	s16 result;
	if ((difference & 0x8000) != 0) {
		result = (s16)(firstAngle - limit);
	} else {
		result = (s16)(firstAngle + limit);
	}
	return (u16)(s16)result;
}

f32 fn_800D7AE4(s32 arg0)
{
	return lbl_803A7028[(u16)(arg0 + 0x4000)];
}

f32 fn_800D7B00(u16 arg0)
{
	return lbl_803A7028[arg0];
}
}

extern "C" {
extern const __declspec(section ".sdata2") f32 lbl_8042E008 = 0.0f;
extern const __declspec(section ".sdata2") f32 lbl_8042E00C = 1.0f;
extern const __declspec(section ".sdata2") f32 lbl_8042E010 = 0.1f;
extern const __declspec(section ".sdata2") f32 lbl_8042E014 = 0.01f;
extern const __declspec(section ".sdata2") f64 lbl_8042E018 = 0.5;
extern const __declspec(section ".sdata2") f64 lbl_8042E020 = 3.0;
extern const __declspec(section ".sdata2") f32 lbl_8042E028 = 0.025f;
extern const __declspec(section ".sdata2") f32 lbl_8042E02C = 0.975f;
extern const __declspec(section ".sdata2") f32 lbl_8042E030 = 10430.380859375f;
extern const __declspec(section ".sdata2") f32 lbl_8042E034 = 0.0001f;
extern const __declspec(section ".sdata2") f32 lbl_8042E038 = -1.0f;
}
