#include "game/matrix.h"

#pragma opt_common_subs off

struct CollisionActor {
	u8 pad0[0x60];
	RwV3d position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
};

struct CollisionInfo {
	u8 pad0[4];
	u32 flags;
	RwV3d position;
	f32 extentX;
	f32 extentY;
	f32 extentZ;
	u8 pad20[8];
	s32 angle;
};

struct CollisionWork {
	RwV3d points[10];
	RwMatrixTag matrix208;
	RwMatrixTag matrix248;
	RwMatrixTag matrix288;
	RwMatrixTag matrix2C8;
};

extern "C" {
extern const f32 lbl_8042D048;
extern const f32 lbl_8042D074;

f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
void fn_8003B7C8(s32, void*, void*, void*, void*);
void fn_8003B97C(s32, void*, void*, void*, void*);
RwMatrixTag* fn_80195790(RwMatrixTag*, const RwV3d*, f32, f32, s32);
RwMatrixTag* fn_80196050(RwMatrixTag*, const RwV3d*, s32);
RwMatrixTag* fn_80195B5C(RwMatrixTag*, const RwMatrixTag*);
RwV3d* fn_8019941C(RwV3d*, const RwV3d*, s32, const RwMatrixTag*);
f64 __fabs(f64);
}

extern "C" void fn_80029088(
    s32 arg0, CollisionActor* arg1, CollisionInfo* arg2, CollisionActor* arg3, CollisionInfo* arg4)
{
	CollisionWork collision;
	RwV3d sp154[5];
	RwV3d sp118[5];
	RwV3d spDC[5];
	RwV3d spA0[5];
	RwMatrixTag sp60;
	RwMatrixTag sp20;
	RwV3d sp14;
	RwV3d sp8;
	register RwMatrixTag* matrix2C8Ptr;
	register RwV3d* secondPoints;
	register RwMatrixTag* matrix248Ptr;
	register RwV3d* secondOutput;
	f32 temp_f31;
	f32 temp_f30;
	f32 temp_f29;
	f32 temp_f28;
	f32 temp_f1;
	f32 temp_f2;
	f32 temp_f3;
	f32 temp_f27;
	u32 temp_r3;
	u32 temp_r3_2;

	if ((arg2->flags & 0x20) != 0) {
		sp14.x = arg2->position.x;
		sp14.y = arg2->position.y;
		sp14.z = arg2->position.z;
	} else {
		fn_80196050(&sp60, &arg1->position, 0);
		temp_r3 = arg2->flags;
		if ((temp_r3 & 0x8000) == 0) {
			if ((temp_r3 & 0x200) != 0) {
				temp_f27 = fn_800D7B00(arg1->angleY);
				fn_80195790(&sp60, &AxisY, lbl_8042D074 - fn_800D7AE4(arg1->angleY), temp_f27, 1);
				temp_f27 = fn_800D7B00(arg1->angleZ);
				fn_80195790(&sp60, &AxisZ, lbl_8042D074 - fn_800D7AE4(arg1->angleZ), temp_f27, 1);
				temp_f27 = fn_800D7B00(arg1->angleX);
				fn_80195790(&sp60, &AxisX, lbl_8042D074 - fn_800D7AE4(arg1->angleX), temp_f27, 1);
			} else {
				temp_f27 = fn_800D7B00(arg1->angleZ);
				fn_80195790(&sp60, &AxisZ, lbl_8042D074 - fn_800D7AE4(arg1->angleZ), temp_f27, 1);
				temp_f27 = fn_800D7B00(arg1->angleX);
				fn_80195790(&sp60, &AxisX, lbl_8042D074 - fn_800D7AE4(arg1->angleX), temp_f27, 1);
				temp_f27 = fn_800D7B00(arg1->angleY);
				fn_80195790(&sp60, &AxisY, lbl_8042D074 - fn_800D7AE4(arg1->angleY), temp_f27, 1);
			}
		}
		fn_8019941C(&sp14, &arg2->position, 1, &sp60);
	}

	if ((arg4->flags & 0x20) != 0) {
		sp8.x = arg4->position.x;
		sp8.y = arg4->position.y;
		sp8.z = arg4->position.z;
	} else {
		fn_80196050(&sp20, &arg3->position, 0);
		temp_r3_2 = arg4->flags;
		if ((temp_r3_2 & 0x8000) == 0) {
			if ((temp_r3_2 & 0x200) != 0) {
				temp_f27 = fn_800D7B00(arg3->angleY);
				fn_80195790(&sp20, &AxisY, lbl_8042D074 - fn_800D7AE4(arg3->angleY), temp_f27, 1);
				temp_f27 = fn_800D7B00(arg3->angleZ);
				fn_80195790(&sp20, &AxisZ, lbl_8042D074 - fn_800D7AE4(arg3->angleZ), temp_f27, 1);
				temp_f27 = fn_800D7B00(arg3->angleX);
				fn_80195790(&sp20, &AxisX, lbl_8042D074 - fn_800D7AE4(arg3->angleX), temp_f27, 1);
			} else {
				temp_f27 = fn_800D7B00(arg3->angleZ);
				fn_80195790(&sp20, &AxisZ, lbl_8042D074 - fn_800D7AE4(arg3->angleZ), temp_f27, 1);
				temp_f27 = fn_800D7B00(arg3->angleX);
				fn_80195790(&sp20, &AxisX, lbl_8042D074 - fn_800D7AE4(arg3->angleX), temp_f27, 1);
				temp_f27 = fn_800D7B00(arg3->angleY);
				fn_80195790(&sp20, &AxisY, lbl_8042D074 - fn_800D7AE4(arg3->angleY), temp_f27, 1);
			}
		}
		fn_8019941C(&sp8, &arg4->position, 1, &sp20);
	}

	temp_f31 = arg2->extentX;
	temp_f30 = arg4->extentX;
	temp_f2  = arg2->extentY;
	temp_f3  = arg4->extentY;
	temp_f29 = arg2->extentZ;
	temp_f28 = arg4->extentZ;
	if (!((f32)__fabs(sp14.y - sp8.y) > (temp_f2 + temp_f3))) {
		temp_r3 = arg2->flags;
		if (((temp_r3 & 0x20) != 0) || ((temp_r3 & 0x8000) != 0)) {
			temp_f27 = fn_800D7B00(arg2->angle);
			fn_80195790(
			    &collision.matrix288, &AxisY, lbl_8042D074 - fn_800D7AE4(arg2->angle), temp_f27, 0);
		} else {
			temp_f27 = fn_800D7B00(arg2->angle + arg1->angleY);
			fn_80195790(&collision.matrix288, &AxisY,
			    lbl_8042D074 - fn_800D7AE4(arg2->angle + arg1->angleY), temp_f27, 0);
		}
		fn_80196050(&collision.matrix288, &sp14, 2);
		fn_80195B5C(&collision.matrix208, &collision.matrix288);
		temp_r3_2 = arg4->flags;
		if (((temp_r3_2 & 0x20) != 0) || ((temp_r3_2 & 0x8000) != 0)) {
			temp_f27 = fn_800D7B00(arg4->angle);
			fn_80195790(
			    &collision.matrix2C8, &AxisY, lbl_8042D074 - fn_800D7AE4(arg4->angle), temp_f27, 0);
		} else {
			temp_f27 = fn_800D7B00(arg4->angle + arg3->angleY);
			fn_80195790(&collision.matrix2C8, &AxisY,
			    lbl_8042D074 - fn_800D7AE4(arg4->angle + arg3->angleY), temp_f27, 0);
		}
		matrix2C8Ptr = &collision.matrix2C8;
		fn_80196050(matrix2C8Ptr, &sp8, 2);
		matrix248Ptr = &collision.matrix248;
		fn_80195B5C(matrix248Ptr, matrix2C8Ptr);

		collision.points[0].x = lbl_8042D048;
		collision.points[0].y = lbl_8042D048;
		collision.points[0].z = lbl_8042D048;
		collision.points[1].x = temp_f31;
		collision.points[1].y = lbl_8042D048;
		collision.points[1].z = temp_f29;
		collision.points[2].x = temp_f31;
		collision.points[2].y = lbl_8042D048;
		temp_f1               = -temp_f29;
		collision.points[2].z = temp_f1;
		temp_f2               = -temp_f31;
		collision.points[3].x = temp_f2;
		collision.points[3].y = lbl_8042D048;
		collision.points[3].z = temp_f29;
		collision.points[4].x = temp_f2;
		collision.points[4].y = lbl_8042D048;
		collision.points[4].z = temp_f1;

		secondPoints      = &collision.points[5];
		secondPoints[0].x = lbl_8042D048;
		secondPoints[0].y = lbl_8042D048;
		secondPoints[0].z = lbl_8042D048;
		secondPoints[1].x = temp_f31;
		secondPoints[1].y = lbl_8042D048;
		secondPoints[1].z = temp_f29;
		secondPoints[2].x = temp_f31;
		secondPoints[2].y = lbl_8042D048;
		secondPoints[2].z = temp_f1;
		secondPoints[3].x = temp_f2;
		secondPoints[3].y = lbl_8042D048;
		secondPoints[3].z = temp_f29;
		secondPoints[4].x = temp_f2;
		secondPoints[4].y = lbl_8042D048;
		secondPoints[4].z = temp_f1;

		fn_8019941C(sp118, collision.points, 5, &collision.matrix288);
		secondOutput = sp154;
		secondOutput = fn_8019941C(secondOutput, secondPoints, 5, matrix2C8Ptr);
		fn_8019941C(spA0, sp118, 5, matrix248Ptr);
		fn_8019941C(spDC, secondOutput, 5, &collision.matrix208);

		if (((f32)__fabs(spA0[0].x) < temp_f30 && (f32)__fabs(spA0[0].z) < temp_f28)
		    || ((f32)__fabs(spA0[1].x) < temp_f30 && (f32)__fabs(spA0[1].z) < temp_f28)
		    || ((f32)__fabs(spA0[2].x) < temp_f30 && (f32)__fabs(spA0[2].z) < temp_f28)
		    || ((f32)__fabs(spA0[3].x) < temp_f30 && (f32)__fabs(spA0[3].z) < temp_f28)
		    || ((f32)__fabs(spA0[4].x) < temp_f30 && (f32)__fabs(spA0[4].z) < temp_f28)
		    || ((f32)__fabs(spDC[0].x) < temp_f31 && (f32)__fabs(spDC[0].z) < temp_f29)
		    || ((f32)__fabs(spDC[1].x) < temp_f31 && (f32)__fabs(spDC[1].z) < temp_f29)
		    || ((f32)__fabs(spDC[2].x) < temp_f31 && (f32)__fabs(spDC[2].z) < temp_f29)
		    || ((f32)__fabs(spDC[3].x) < temp_f31 && (f32)__fabs(spDC[3].z) < temp_f29)
		    || ((f32)__fabs(spDC[4].x) < temp_f31 && (f32)__fabs(spDC[4].z) < temp_f29)) {
			fn_8003B7C8(arg0, arg1, arg2, arg3, arg4);
			fn_8003B97C(arg0, arg1, arg2, arg3, arg4);
		}
	}
}
