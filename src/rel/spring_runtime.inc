#include "types.h"

struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
};

struct SpringMember {
	f32 height;
	s16 kind;
	u8 unk6[2];
	f32 width;
};

struct SpringFrame {
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	u8 unk18[0x12];
	u8 group;
	u8 unk2B;
	SpringMember* member;
};

struct ModelRef {
	u8 unk0[4];
	void* model;
};

union ModelPointer {
	void* value;
	u8* bytes;
	u32* words;
};

struct SpringRuntime {
	u8 unk0[4];
	u16 flags;
	u8 unk6[0x22];
	SpringFrame* frame;
	u8 unk2C[4];
	u8 collision[0x60];
	Vec3 lastPosition;
	s32 lastAngleX;
	s32 lastAngleY;
	s32 lastAngleZ;
	u8 unkA8[4];
	Vec3 previousPosition;
	s32 state;
	s8 hits[8];
	s16 kind;
	u8 unkC6[2];
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	s32 phase;
	f32 amplitude;
	f32 scaleY;
	f32 scaleXZ;
	f32 height;
	f32 width;
	ModelRef* modelRef;
};

struct World {
	u8 unk0[0x7274];
	void* scene;
};

extern "C" const Vec3 lbl_80239978;
extern "C" const Vec3 lbl_80239984;
extern "C" const Vec3 lbl_80239990;
extern "C" World* lbl_8042C1D0;

extern "C" s32 fn_8003BC38(void* collision);
extern "C" s32 fn_8005B8BC(void* motion);
extern "C" s32 fn_8005B8D8(void* motion);
extern "C" s32 fn_8005B9F0(void* motion);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void fn_8015BB08(void* scene, ModelRef* model);
extern "C" void fn_80195790(void* matrix, const Vec3* axis, f32 cosine, f32 sine, s32 mode);
extern "C" void fn_8019EB94(void* model, const Vec3* position, s32 mode);
extern "C" void fn_8019EC30(void* model, const Vec3* scale, s32 mode);
extern "C" s32 objGroupAllSet(u8 group);
extern "C" void springLaunch(SpringRuntime* object);

#define SCALE_VECTOR(out, in, scalar)                                                              \
	do {                                                                                           \
		(out)->x = (in)->x * (scalar);                                                             \
		(out)->y = (in)->y * (scalar);                                                             \
		(out)->z = (in)->z * (scalar);                                                             \
	} while (0)

#define ADD_VECTOR(out, lhs, rhs)                                                                  \
	do {                                                                                           \
		(out)->x = (lhs)->x + (rhs)->x;                                                            \
		(out)->y = (lhs)->y + (rhs)->y;                                                            \
		(out)->z = (lhs)->z + (rhs)->z;                                                            \
	} while (0)

#define SET_SPRING_TRANSFORM()                                                                     \
	SCALE_VECTOR(&scale, &lbl_80239984, object->scaleY);                                           \
	SCALE_VECTOR(&add, &lbl_80239978, object->scaleXZ);                                            \
	ADD_VECTOR(&scale, &scale, &add);                                                              \
	SCALE_VECTOR(&add, &lbl_80239990, object->scaleXZ);                                            \
	ADD_VECTOR(&scale, &scale, &add);                                                              \
	fn_8019EC30(model, &scale, 0);                                                                 \
	sine = fn_800D7B00(object->angleY);                                                            \
	fn_80195790(matrix.bytes + 0x10, &lbl_80239984, 1.0f - fn_800D7AE4(object->angleY), sine, 2);  \
	sine = fn_800D7B00(object->angleX);                                                            \
	fn_80195790(matrix.words + 4, &lbl_80239978, 1.0f - fn_800D7AE4(object->angleX), sine, 2);     \
	sine = fn_800D7B00(object->angleZ);                                                            \
	fn_80195790(                                                                                   \
	    (u8*)matrix.value + 0x10, &lbl_80239990, 1.0f - fn_800D7AE4(object->angleZ), sine, 2);     \
	fn_8019EB94(model, &object->position, 2)

#pragma opt_common_subs on
extern "C" void springTransform(SpringRuntime* object)
{
	f32 sine;
	Vec3 scale;
	Vec3 add;
	void* model = object->modelRef->model;
	ModelPointer matrix;
	matrix.value = model;
	SET_SPRING_TRANSFORM();
}

extern "C" void Exec__11SpringClassFv(SpringRuntime* object)
{
	register SpringMember* member = object->frame->member;

	if (fn_8005B9F0(&object->frame) || fn_8005B8BC(&object->frame)) {
		object->flags |= 1;
		return;
	}

	if (fn_8005B8D8(&object->frame)) {
		object->position   = object->frame->position;
		SpringFrame* frame = object->frame;
		object->angleX     = frame->angleX;
		object->angleY     = frame->angleY;
		object->angleZ     = frame->angleZ;
		object->height     = member->height;
		object->kind       = member->kind;
		object->width      = member->width;

		Vec3 scale;
		Vec3 add;
		void* model = object->modelRef->model;
		ModelPointer matrix;
		matrix.value = model;
		f32 sine;
		SET_SPRING_TRANSFORM();
		return;
	}

	if (object->state == 3) {
		if (objGroupAllSet(object->frame->group)) {
			object->state = 1;
			fn_8015BB08(lbl_8042C1D0->scene, object->modelRef);
		} else {
			return;
		}
	}

	springLaunch(object);
	if (object->state == 2) {
		object->phase += 0x800;
		object->amplitude = 0.987f * object->amplitude;
		f64 amplitude     = __fabs(object->amplitude);
		if ((f32)amplitude <= 0.001f) {
			f32 scale         = 1.0f;
			object->amplitude = scale;
			object->scaleXZ   = scale;
			object->scaleY    = scale;
			object->state     = 1;
		} else {
			object->scaleY  = 1.0f + object->amplitude * fn_800D7B00(object->phase);
			object->scaleXZ = 1.0f - object->amplitude * fn_800D7B00(object->phase);
		}
	}

	Vec3 scale;
	Vec3 add;
	void* model = object->modelRef->model;
	ModelPointer matrix;
	matrix.value = model;
	f32 sine;
	SET_SPRING_TRANSFORM();

	if (object->hits[0] > 0)
		object->hits[0]--;
	if (object->hits[1] > 0)
		object->hits[1]--;
	if (object->hits[2] > 0)
		object->hits[2]--;
	if (object->hits[3] > 0)
		object->hits[3]--;
	if (object->hits[4] > 0)
		object->hits[4]--;
	if (object->hits[5] > 0)
		object->hits[5]--;
	if (object->hits[6] > 0)
		object->hits[6]--;
	if (object->hits[7] > 0)
		object->hits[7]--;

	object->previousPosition = object->lastPosition;
	object->lastPosition     = object->position;
	object->lastAngleX       = object->angleX;
	object->lastAngleY       = object->angleY;
	object->lastAngleZ       = object->angleZ;
	fn_8003BC38(object->collision);
}

#pragma opt_common_subs reset
