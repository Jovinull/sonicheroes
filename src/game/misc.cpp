// Complete GameCube misc.cpp candidate, 0x800D5844--0x800D7B18.
// NonMatching. Initial GameCube control flow recovered with m2c 708d2d2.
#include "game/misc.h"
#include "Runtime.PPCEABI.H/__va_arg.h"
// Word-copy view preserves the observed 12-byte vector copy.
struct VectorCopyWords {
	u32 words[3];
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
}

static inline f32 MiscSqrt(f32 value, f32 zero)
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

void ClosePositionToCamera(RwV3d* arg0, f32 farg0)
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

void DisplayRpSpline(RpSpline* arg0) { }

void RelativeCalcPoint(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2, sAngle* arg3)
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

s32 AdjustPoint(RwV3d* arg0, const RwV3d* arg1, f32 farg0)
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

void njPrintColor(u32 arg0)
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

void njPrint2(s32 position, const char* format, ...)
{
	__va_list args;
	char buffer[64];
	__builtin_va_info(args);
	vsprintf(buffer, format, args);
	RsCameraSize(lbl_8042C0F0, buffer, position >> 16, (u16)position, 5);
}

void njPrint(s32 position, const char* format, ...)
{
	__va_list args;
	char buffer[64];
	__builtin_va_info(args);
	vsprintf(buffer, format, args);
	RsCameraSize(lbl_8042C0F0, buffer, position >> 16, (u16)position + 6, 5);
}

f32 DistanceL2PL(const NJS_LINE* line, const NJS_LINE* plane, RwV3d* nearestPoint)
{
	volatile f32 roundedLineLength;
	volatile f32 roundedPlaneLength;
	volatile f32 roundedNormalLength;
	f32 pointY;
	f32 projectionScale;
	f32 intersectionRate;
	f32 absoluteOffset;
	f32 pointZ;
	f32 signedOffset;
	f32 directionDotNormal;
	f32 pointX;
	f32 lineLength;
	f32 normalMagnitude;
	f32 planeLength;
	lineLength = (line->v.z * line->v.z) + ((line->v.x * line->v.x) + (line->v.y * line->v.y));
	if (lineLength > lbl_8042E008) {
		f64 estimate = __frsqrte(lineLength);
		estimate
		    = lbl_8042E018 * estimate * (lbl_8042E020 - (f64)lineLength * (estimate * estimate));
		estimate
		    = lbl_8042E018 * estimate * (lbl_8042E020 - (f64)lineLength * (estimate * estimate));
		estimate
		    = lbl_8042E018 * estimate * (lbl_8042E020 - (f64)lineLength * (estimate * estimate));
		roundedLineLength = (f32)((f64)lineLength * estimate);
		lineLength        = roundedLineLength;
	}
	planeLength
	    = (plane->v.z * plane->v.z) + ((plane->v.x * plane->v.x) + (plane->v.y * plane->v.y));
	if (planeLength > lbl_8042E008) {
		f64 estimate = __frsqrte(planeLength);
		estimate
		    = lbl_8042E018 * estimate * (lbl_8042E020 - (f64)planeLength * (estimate * estimate));
		estimate
		    = lbl_8042E018 * estimate * (lbl_8042E020 - (f64)planeLength * (estimate * estimate));
		estimate
		    = lbl_8042E018 * estimate * (lbl_8042E020 - (f64)planeLength * (estimate * estimate));
		roundedPlaneLength = (f32)((f64)planeLength * estimate);
		planeLength        = roundedPlaneLength;
	}
	directionDotNormal
	    = (line->v.z * plane->v.z) + ((line->v.x * plane->v.x) + (line->v.y * plane->v.y));
	if ((f32)__fabs(directionDotNormal / (lineLength * planeLength)) < lbl_8042E028) {
		pointX = line->p.x;
		pointY = line->p.y;
		pointZ = line->p.z;
		signedOffset
		    = -((plane->v.z * plane->p.z) + ((plane->v.x * plane->p.x) + (plane->v.y * plane->p.y)))
		    + ((plane->v.z * pointZ) + ((plane->v.x * pointX) + (plane->v.y * pointY)));
		normalMagnitude
		    = (plane->v.z * plane->v.z) + ((plane->v.x * plane->v.x) + (plane->v.y * plane->v.y));
		if (nearestPoint != NULL) {
			projectionScale = -signedOffset / normalMagnitude;
			nearestPoint->x = pointX + (plane->v.x * projectionScale);
			nearestPoint->y = pointY + (plane->v.y * projectionScale);
			nearestPoint->z = pointZ + (plane->v.z * projectionScale);
		}
		absoluteOffset = (f32)__fabs(signedOffset);
		if (normalMagnitude > lbl_8042E008) {
			f64 estimate = __frsqrte(normalMagnitude);
			estimate     = lbl_8042E018 * estimate
			    * (lbl_8042E020 - (f64)normalMagnitude * (estimate * estimate));
			estimate = lbl_8042E018 * estimate
			    * (lbl_8042E020 - (f64)normalMagnitude * (estimate * estimate));
			estimate = lbl_8042E018 * estimate
			    * (lbl_8042E020 - (f64)normalMagnitude * (estimate * estimate));
			roundedNormalLength = (f32)((f64)normalMagnitude * estimate);
			normalMagnitude     = roundedNormalLength;
		}
		return absoluteOffset * (lbl_8042E00C / normalMagnitude);
	}
	if (nearestPoint != NULL) {
		intersectionRate = -(-((plane->v.z * plane->p.z)
		                         + ((plane->v.x * plane->p.x) + (plane->v.y * plane->p.y)))
		                       + ((plane->v.z * line->p.z)
		                           + ((plane->v.x * line->p.x) + (plane->v.y * line->p.y))))
		    / directionDotNormal;
		nearestPoint->x = line->p.x + (line->v.x * intersectionRate);
		nearestPoint->y = line->p.y + (line->v.y * intersectionRate);
		nearestPoint->z = line->p.z + (line->v.z * intersectionRate);
	}
	return lbl_8042E008;
}

f32 DistanceL2L(const NJS_LINE* l1, const NJS_LINE* l2, RwV3d* p1, RwV3d* p2)
{
	RwV3d p;
	RwV3d tp1;
	NJS_LINE pl1;
	NJS_LINE pl2;
	NJS_LINE tl;
	volatile RwV3d tp2;
	volatile f32 sp18;
	volatile f32 sp14;
	volatile f32 sp10;
	volatile f32 spC;
	volatile f32 sp8;
	f32 temp_f0_2;
	f32 temp_f1_16;
	f32 temp_f1_17;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f1_4;
	f32 temp_f1_5;
	f32 temp_f1_6;
	f32 temp_f2_5;
	f32 temp_f3_4;
	f32 temp_f4;
	f32 temp_f4_2;
	f32 temp_f4_5;
	f32 temp_f4_6;
	f32 temp_f6;
	f32 temp_f6_5;
	f32 temp_f6_6;
	f32 temp_f7_3;
	f32 temp_f7_4;
	f32 temp_f8_3;
	f32 var_f1;
	f32 var_f4;
	f32 var_f4_2;
	f32 u;
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
	temp_f4 = (l1->v.z * l2->v.z) + ((l1->v.x * l2->v.x) + (l1->v.y * l2->v.y));
	if ((f32)__fabs((temp_f4 * temp_f4)
	        / (((l1->v.z * l1->v.z) + ((l1->v.x * l1->v.x) + (l1->v.y * l1->v.y)))
	            * ((l2->v.z * l2->v.z) + ((l2->v.x * l2->v.x) + (l2->v.y * l2->v.y)))))
	    > lbl_8042E02C) {
		if (p1 != NULL) {
			p1->x = l1->p.x;
			p1->y = l1->p.y;
			p1->z = l1->p.z;
		}
		temp_f0_2 = l1->p.x;
		temp_f1_2 = l1->p.y;
		temp_f6   = l1->p.z;
		temp_f4_2 = ((l2->v.z * (temp_f6 - l2->p.z))
		                + ((l2->v.x * (temp_f0_2 - l2->p.x)) + (l2->v.y * (temp_f1_2 - l2->p.y))))
		    / ((l2->v.z * l2->v.z) + ((l2->v.x * l2->v.x) + (l2->v.y * l2->v.y)));
		if (p2 != NULL) {
			p2->x = l2->p.x + (l2->v.x * temp_f4_2);
			p2->y = l2->p.y + (l2->v.y * temp_f4_2);
			p2->z = l2->p.z + (l2->v.z * temp_f4_2);

			var_f1 = ((temp_f6 - p2->z) * (temp_f6 - p2->z))
			    + (((temp_f0_2 - p2->x) * (temp_f0_2 - p2->x))
			        + ((temp_f1_2 - p2->y) * (temp_f1_2 - p2->y)));
		} else {

			var_f1 = ((temp_f6 - (l2->p.z + (l2->v.z * temp_f4_2)))
			             * (temp_f6 - (l2->p.z + (l2->v.z * temp_f4_2))))
			    + (((temp_f0_2 - (l2->p.x + (l2->v.x * temp_f4_2)))
			           * (temp_f0_2 - (l2->p.x + (l2->v.x * temp_f4_2))))
			        + ((temp_f1_2 - (l2->p.y + (l2->v.y * temp_f4_2)))
			            * (temp_f1_2 - (l2->p.y + (l2->v.y * temp_f4_2)))));
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
			sp10   = (f32)((f64)var_f1
			    * (lbl_8042E018 * temp_f0_9
			        * (lbl_8042E020 - ((f64)var_f1 * (temp_f0_9 * temp_f0_9)))));
			var_f1 = sp10;
		}
		return var_f1;
	}
	pl1.p.x = l1->p.x;
	pl1.p.y = l1->p.y;
	pl1.p.z = l1->p.z;
	pl1.v.x = (l1->v.y * l2->v.z) - (l1->v.z * l2->v.y);
	pl1.v.y = (l1->v.z * l2->v.x) - (l1->v.x * l2->v.z);
	pl1.v.z = (l1->v.x * l2->v.y) - (l1->v.y * l2->v.x);
	var_f4  = (pl1.v.z * pl1.v.z) + ((pl1.v.x * pl1.v.x) + (pl1.v.y * pl1.v.y));
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
	temp_f1_3 = lbl_8042E00C / var_f4;
	pl1.v.x   = pl1.v.x * temp_f1_3;
	pl1.v.y   = pl1.v.y * temp_f1_3;
	pl1.v.z   = pl1.v.z * temp_f1_3;
	pl2.p.x   = l2->p.x;
	pl2.p.y   = l2->p.y;
	pl2.p.z   = l2->p.z;
	pl2.v.x   = (pl1.v.y * l2->v.z) - (pl1.v.z * l2->v.y);
	pl2.v.y   = (pl1.v.z * l2->v.x) - (pl1.v.x * l2->v.z);
	pl2.v.z   = (pl1.v.x * l2->v.y) - (pl1.v.y * l2->v.x);
	var_f4_2  = (pl2.v.z * pl2.v.z) + ((pl2.v.x * pl2.v.x) + (pl2.v.y * pl2.v.y));
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
	pl2.v.x   = pl2.v.x * temp_f1_4;
	pl2.v.y *= temp_f1_4;
	pl2.v.z *= temp_f1_4;
	DistancePL2PL(&pl1, &pl2, &tl);
	temp_f7_3 = l1->v.x;
	p.y       = -tl.v.y;
	temp_f1_5 = l1->v.y;
	p.x       = -tl.v.x;
	temp_f3_4 = (temp_f7_3 * p.y) - (temp_f1_5 * p.x);
	if ((f32)__fabs(temp_f3_4) > lbl_8042E028) {
		u = ((p.y * (tl.p.x - l1->p.x)) - (p.x * (tl.p.y - l1->p.y))) / temp_f3_4;
	} else {
		p.z       = -tl.v.z;
		temp_f2_5 = l1->v.z;
		temp_f8_3 = (temp_f1_5 * p.z) - (temp_f2_5 * p.y);
		if ((f32)__fabs(temp_f8_3) > lbl_8042E028) {
			u = ((p.z * (tl.p.y - l1->p.y)) - (p.y * (tl.p.z - l1->p.z))) / temp_f8_3;
		} else {
			u = ((p.z * (tl.p.x - l1->p.x)) - (p.x * (tl.p.z - l1->p.z)))
			    / ((temp_f7_3 * p.z) - (temp_f2_5 * p.x));
		}
	}
	tp1.x     = l1->p.x + (l1->v.x * u);
	tp1.y     = l1->p.y + (l1->v.y * u);
	tp1.z     = l1->p.z + (l1->v.z * u);
	temp_f7_4 = ((l2->v.z * (tp1.z - l2->p.z))
	                + ((l2->v.x * (tp1.x - l2->p.x)) + (l2->v.y * (tp1.y - l2->p.y))))
	    / ((l2->v.z * l2->v.z) + ((l2->v.x * l2->v.x) + (l2->v.y * l2->v.y)));
	if (&tp2 != NULL) {
		temp_f4_5 = l2->p.x + (l2->v.x * temp_f7_4);
		tp2.x     = temp_f4_5;
		temp_f6_5 = l2->p.y + (l2->v.y * temp_f7_4);
		tp2.y     = temp_f6_5;
		temp_f1_6 = l2->p.z + (l2->v.z * temp_f7_4);
		tp2.z     = temp_f1_6;

		var_f7 = ((tp1.z - temp_f1_6) * (tp1.z - temp_f1_6))
		    + (((tp1.x - temp_f4_5) * (tp1.x - temp_f4_5))
		        + ((tp1.y - temp_f6_5) * (tp1.y - temp_f6_5)));
	} else {

		var_f7 = ((tp1.z - (l2->p.z + (l2->v.z * temp_f7_4)))
		             * (tp1.z - (l2->p.z + (l2->v.z * temp_f7_4))))
		    + (((tp1.x - (l2->p.x + (l2->v.x * temp_f7_4)))
		           * (tp1.x - (l2->p.x + (l2->v.x * temp_f7_4))))
		        + ((tp1.y - (l2->p.y + (l2->v.y * temp_f7_4)))
		            * (tp1.y - (l2->p.y + (l2->v.y * temp_f7_4)))));
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
	temp_f4_6  = tp1.x - tp2.x;
	temp_f6_6  = tp1.y - tp2.y;
	temp_f1_16 = tp1.z - tp2.z;
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
	if (p1 != NULL) {
		p1->x = tp1.x;
		p1->y = tp1.y;
		p1->z = tp1.z;
	}
	if (p2 != NULL) {
		p2->x = tp2.x;
		p2->y = tp2.y;
		p2->z = tp2.z;
	}
	return var_f1;
}

f32 RoundOff(f32 farg0)
{
	if (farg0 < lbl_8042E008) {
		return -(f32)floor(-farg0);
	}
	return (f32)floor((f64)farg0);
}

f32 CrossProduct(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2)
{
	arg2->x = (arg0->y * arg1->z) - (arg0->z * arg1->y);
	arg2->y = (arg0->z * arg1->x) - (arg0->x * arg1->z);
	arg2->z = (arg0->x * arg1->y) - (arg0->y * arg1->x);
	return fn_801991B4(arg2);
}

f32 DistancePL2PL(const RwV3d* arg0, const RwV3d* arg1, NJS_LINE* arg2)
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

f32 DistancePL2PL(const NJS_LINE* pl1, const NJS_LINE* pl2, NJS_LINE* l)
{
	RwV3d p;
	f32 d1, d2, d3, oodet;
	volatile f32 sp10;
	volatile f32 spC;
	volatile f32 sp8;
	f32 temp_f0_4;
	f32 temp_f4;
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
	var_f0 = (pl1->v.z * pl1->v.z) + ((pl1->v.x * pl1->v.x) + (pl1->v.y * pl1->v.y));
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
	var_f8 = (pl2->v.z * pl2->v.z) + ((pl2->v.x * pl2->v.x) + (pl2->v.y * pl2->v.y));
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
	if ((f32)__fabs(((pl1->v.z * pl2->v.z) + ((pl1->v.x * pl2->v.x) + (pl1->v.y * pl2->v.y)))
	        / (var_f0 * var_f8))
	    > lbl_8042E02C) {
		if (l != NULL) {
			l->p.x = lbl_8042E008;
			l->p.y = lbl_8042E008;
			l->p.z = lbl_8042E008;
			l->v.x = lbl_8042E008;
			l->v.y = lbl_8042E008;
			l->v.z = lbl_8042E008;
		}

		temp_f4
		    = (f32)__fabs(-((pl2->v.z * pl2->p.z) + ((pl2->v.x * pl2->p.x) + (pl2->v.y * pl2->p.y)))
		        + ((pl2->v.z * pl1->p.z) + ((pl2->v.x * pl1->p.x) + (pl2->v.y * pl1->p.y))));
		var_f5 = (pl2->v.z * pl2->v.z) + ((pl2->v.x * pl2->v.x) + (pl2->v.y * pl2->v.y));
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
	if (l != NULL) {
		l->v.x = (pl1->v.y * pl2->v.z) - (pl2->v.y * pl1->v.z);
		l->v.y = (pl1->v.z * pl2->v.x) - (pl2->v.z * pl1->v.x);
		l->v.z = (pl1->v.x * pl2->v.y) - (pl2->v.x * pl1->v.y);
		d1     = (pl1->v.z * pl1->p.z) + ((pl1->v.x * pl1->p.x) + (pl1->v.y * pl1->p.y));
		d2     = (pl2->v.z * pl2->p.z) + ((pl2->v.x * pl2->p.x) + (pl2->v.y * pl2->p.y));
		d3     = (l->v.z * pl2->p.z) + ((l->v.x * pl2->p.x) + (l->v.y * pl2->p.y));

		oodet = lbl_8042E00C
		    / (((((pl2->v.x * (pl1->v.z * l->v.y))
		             + ((l->v.z * (pl1->v.x * pl2->v.y)) + (l->v.x * (pl1->v.y * pl2->v.z))))
		            - (l->v.x * (pl1->v.z * pl2->v.y)))
		           - (l->v.z * (pl1->v.y * pl2->v.x)))
		        - (pl2->v.z * (pl1->v.x * l->v.y)));
		p.z    = (((((pl2->v.x * (d1 * l->v.y))
		                + ((d3 * (pl1->v.x * pl2->v.y)) + (l->v.x * (pl1->v.y * d2))))
		               - (l->v.x * (d1 * pl2->v.y)))
		              - (d3 * (pl1->v.y * pl2->v.x)))
		    - (d2 * (pl1->v.x * l->v.y)));
		p.x    = (((((d2 * (pl1->v.z * l->v.y))
		                + ((l->v.z * (d1 * pl2->v.y)) + (d3 * (pl1->v.y * pl2->v.z))))
		               - (d3 * (pl1->v.z * pl2->v.y)))
		              - (l->v.z * (pl1->v.y * d2)))
		    - (pl2->v.z * (d1 * l->v.y)));
		p.y    = (((((pl2->v.x * (pl1->v.z * d3))
		                + ((l->v.z * (pl1->v.x * d2)) + (l->v.x * (d1 * pl2->v.z))))
		               - (l->v.x * (pl1->v.z * d2)))
		              - (l->v.z * (d1 * pl2->v.x)))
		    - (pl2->v.z * (pl1->v.x * d3)));
		l->p.x = p.x * oodet;
		l->p.y = p.y * oodet;
		l->p.z = p.z * oodet;
	}
	return lbl_8042E008;
}

f32 DistanceP2PL(const RwV3d* arg0, const RwV3d* arg1, RwV3d* arg2)
{
	f32 temp_f3_2;
	f32 temp_f5;
	f32 temp_f7;
	f32 var_f0;

	temp_f7 = (arg1->z * arg0->z) + ((arg1->x * arg0->x) + (arg1->y * arg0->y));
	var_f0  = (arg1->z * arg1->z) + ((arg1->x * arg1->x) + (arg1->y * arg1->y));
	if (arg2 != NULL) {
		temp_f3_2 = -temp_f7 / var_f0;
		arg2->x   = arg0->x + (arg1->x * temp_f3_2);
		arg2->y   = arg0->y + (arg1->y * temp_f3_2);
		arg2->z   = arg0->z + (arg1->z * temp_f3_2);
	}
	f64 absolute = __fabs(temp_f7);
	temp_f5      = (f32)absolute;
	return temp_f5 / MiscSqrt(var_f0, lbl_8042E008);
}

f32 DistanceP2PL(const RwV3d* arg0, const NJS_LINE* arg1, RwV3d* arg2)
{
	f32 temp_f0;
	f32 temp_f3;
	f32 temp_f4_2;
	f32 temp_f5;

	temp_f3 = -((arg1->v.z * arg1->p.z) + ((arg1->v.x * arg1->p.x) + (arg1->v.y * arg1->p.y)))
	    + ((arg1->v.z * arg0->z) + ((arg1->v.x * arg0->x) + (arg1->v.y * arg0->y)));
	temp_f0 = (arg1->v.z * arg1->v.z) + ((arg1->v.x * arg1->v.x) + (arg1->v.y * arg1->v.y));
	if (arg2 != NULL) {
		temp_f4_2 = -temp_f3 / temp_f0;
		arg2->x   = arg0->x + (arg1->v.x * temp_f4_2);
		arg2->y   = arg0->y + (arg1->v.y * temp_f4_2);
		arg2->z   = arg0->z + (arg1->v.z * temp_f4_2);
	}
	f64 absolute = __fabs(temp_f3);
	temp_f5      = (f32)absolute;
	return temp_f5 * (lbl_8042E00C / MiscSqrt(temp_f0, lbl_8042E008));
}

f32 DistanceP2L(const RwV3d* arg0, const NJS_LINE* arg1, RwV3d* arg2)
{
	f32 temp_f3;
	f32 var_f4;

	temp_f3 = ((arg1->v.z * (arg0->z - arg1->p.z))
	              + ((arg1->v.x * (arg0->x - arg1->p.x)) + (arg1->v.y * (arg0->y - arg1->p.y))))
	    / ((arg1->v.z * arg1->v.z) + ((arg1->v.x * arg1->v.x) + (arg1->v.y * arg1->v.y)));
	if (arg2 != NULL) {
		arg2->x = arg1->p.x + (arg1->v.x * temp_f3);
		arg2->y = arg1->p.y + (arg1->v.y * temp_f3);
		arg2->z = arg1->p.z + (arg1->v.z * temp_f3);
		var_f4  = ((arg0->z - arg2->z) * (arg0->z - arg2->z))
		    + (((arg0->x - arg2->x) * (arg0->x - arg2->x))
		        + ((arg0->y - arg2->y) * (arg0->y - arg2->y)));
	} else {
		var_f4 = ((arg0->z - (arg1->p.z + (arg1->v.z * temp_f3)))
		             * (arg0->z - (arg1->p.z + (arg1->v.z * temp_f3))))
		    + (((arg0->x - (arg1->p.x + (arg1->v.x * temp_f3)))
		           * (arg0->x - (arg1->p.x + (arg1->v.x * temp_f3))))
		        + ((arg0->y - (arg1->p.y + (arg1->v.y * temp_f3)))
		            * (arg0->y - (arg1->p.y + (arg1->v.y * temp_f3)))));
	}
	if (var_f4 < lbl_8042E028) {
		return lbl_8042E008;
	}
	return MiscSqrt(var_f4, lbl_8042E008);
}

f32 Distance2P2P(const RwV3d* arg0, const RwV3d* arg1)
{
	f32 temp_f0;
	f32 temp_f3;
	f32 temp_f4;

	temp_f3 = arg0->x - arg1->x;
	temp_f4 = arg0->y - arg1->y;
	temp_f0 = arg0->z - arg1->z;
	return (temp_f0 * temp_f0) + ((temp_f3 * temp_f3) + (temp_f4 * temp_f4));
}

f32 DistanceP2P(const RwV3d* arg0, const RwV3d* arg1)
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

void SubVectorReturnToVector(const RwV3d* arg0, const RwV3d* arg1, RwV3d* arg2)
{
	arg2->x = arg0->x - arg1->x;
	arg2->y = arg0->y - arg1->y;
	arg2->z = arg0->z - arg1->z;
}

void AddVectorReturnToVector(const RwV3d* arg0, const RwV3d* arg1, RwV3d* arg2)
{
	arg2->x = arg0->x + arg1->x;
	arg2->y = arg0->y + arg1->y;
	arg2->z = arg0->z + arg1->z;
}

f32 AdjustFloat(f32 farg0, f32 farg1, f32 farg2)
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

void GetZYAngleForTheTargetPoint(const RwV3d* arg0, const RwV3d* arg1, s32* arg2)
{
	volatile f32 spC;
	volatile f32 sp8;
	f32 var_f31;
	f32 var_f31_2;
	f64 temp_f0_10;
	f64 temp_f0_3;
	f64 temp_f0_4;
	f64 temp_f0_5;
	f64 temp_f0_8;
	f64 temp_f0_9;
	var_f31 = (arg0->x * arg0->x) + (arg0->z * arg0->z);
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
		var_f31_2 = (arg1->x * arg1->x) + (arg1->z * arg1->z);
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

f32 GetFloatMod(f32 farg0, f32 farg1)
{
	if (lbl_8042E008 == farg1) {
		return lbl_8042E008;
	}
	return farg0 - (farg1 * (f32)floor((f64)(farg0 / farg1)));
}

static inline f32 fn_800D75CCDot(const RwV3d& left, const RwV3d& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

s32 VectorAngleOnPlane(RwV3d* v1, RwV3d* v2, RwV3d* vn)
{
	NJS_LINE pl;
	RwV3d v1s;
	RwV3d v2s;
	pl.v   = *vn;
	pl.p.x = pl.p.y = pl.p.z = lbl_8042E008;
	DistanceP2PL(v1, &pl, &v1s);
	DistanceP2PL(v2, &pl, &v2s);

	if (fn_800D75CCDot(v1s, v1s) <= lbl_8042E034) {
		return -1;
	}
	if (fn_800D75CCDot(v2s, v2s) <= lbl_8042E034) {
		return -1;
	}

	fn_801990E0(&v1s, &v1s);
	fn_801990E0(&v2s, &v2s);

	f32 dot = fn_800D75CCDot(v1s, v2s);
	if (dot <= lbl_8042E038)
		return 0x8000;
	if (dot >= lbl_8042E00C)
		return 0;

	s32 angle = (s32)(lbl_8042E030 * (f32)acos(dot));
	RwV3d cross;
	cross.x = v1s.y * v2s.z - v1s.z * v2s.y;
	cross.y = v1s.z * v2s.x - v1s.x * v2s.z;
	cross.z = v1s.x * v2s.y - v1s.y * v2s.x;
	if (vn != 0) {
		if (lbl_8042E008 > fn_800D75CCDot(*vn, cross)) {
			angle = 0x10000 - angle;
		}
	}
	return angle;
}

static f32 fn_800D7920Dot(const RwV3d& left, const RwV3d& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

s32 VectorAngle(RwV3d* first, RwV3d* second, RwV3d* orientation)
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

u16 DiffAngle(s32 first, s32 second)
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

s16 SubAngle(s32 first, s32 second)
{
	u16 firstAngle  = (u16)first;
	u16 secondAngle = (u16)second;
	return (s16)(secondAngle - firstAngle);
}

u16 AdjustAngle(s32 first, s32 second, s32 limit)
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
