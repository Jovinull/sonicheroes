#include "types.h"

// TObjLightColli::CheckCollisionedPlayerBody (the PS2 build's name), the same
// in the thirteen stage modules that share the engine core: whether player
// `player`'s body is inside the collision. The placement's size is read by
// shape: a sphere (shape 0, the size's length), a box (shape 1, its x) or a
// cylinder (shape 2, the length of its x and y). A body further than that plus
// its radius is out; a box is then in; a sphere and a cylinder take the body
// into the collision's frame (its position and angles) and check it against
// the size along each axis, the cylinder's height by the body's height and
// its radius on the ground plane.

typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;

typedef struct RwMatrixTag RwMatrixTag;

typedef struct LightCollisionParams {
	s8 light;   // 0x00
	s8 kind;    // 0x01
	s8 shape;   // 0x02
	u8 pad03;   // 0x03
	RwV3d size; // 0x04
} LightCollisionParams;

typedef struct SetData {
	RwV3d pos; // 0x00
	s32 angX;  // 0x0C
	s32 angY;  // 0x10
	s32 angZ;  // 0x14
	u8 unk18[0x14];
	LightCollisionParams* params; // 0x2C
} SetData;

typedef struct LightCollision {
	u8 unk00[0x28];
	SetData* setdata; // 0x28
} LightCollision;

typedef struct PlayerBody {
	u8 unk00[0x8];
	RwV3d pos;  // 0x08
	f32 radius; // 0x14
	f32 height; // 0x18
} PlayerBody;

typedef struct PlayerWork {
	u8 unk00[0x38];
	PlayerBody* body; // 0x38
} PlayerWork;

extern "C" PlayerWork* lbl_802AD070[];
extern RwMatrixTag* pCurrentMatrix;
extern "C" const f32 lightCollisionNoSize[1];
extern "C" const double lightCollisionHalf;
extern "C" const double lightCollisionThree;

double __frsqrte(double x);
f32 DistanceP2P(const RwV3d* a, const RwV3d* b);
void PushMatrixEx();
void PopMatrixEx();
void UnitMatrix(RwMatrixTag* matrix);
void RotateX(RwMatrixTag* matrix, int angle);
void RotateY(RwMatrixTag* matrix, int angle);
void RotateZ(RwMatrixTag* matrix, int angle);
void njInvertMatrix(RwMatrixTag* matrix);
void CalcPoint(const RwMatrixTag* matrix, const RwV3d* in, RwV3d* out);
extern "C" f32 fn_801991B4(RwV3d* v);
extern "C" void fn_80196050(RwMatrixTag* matrix, const RwV3d* translation, s32 combine);

// MSL's sqrtf, as rel/cage_class.inc has it.
static inline f32 lightCollisionSqrtf(f32 x)
{
	volatile f32 y;

	if (x > lightCollisionNoSize[0]) {
		double guess = __frsqrte((double)x);
		double half  = lightCollisionHalf;
		double three;
		guess = half * guess * ((three = lightCollisionThree) - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		y     = (f32)(x * guess);
		return y;
	}
	return x;
}

extern "C" s32 CheckCollisionedPlayerBody__14TObjLightColliFi(LightCollision* object, s32 player)
{
	PlayerBody* body;
	SetData* setdata             = object->setdata;
	LightCollisionParams* params = setdata->params;
	RwV3d size;
	PlayerWork* work;
	f32 reach;

	size.x = params->size.x;
	size.y = params->size.y;
	size.z = params->size.z;
	work   = lbl_802AD070[player];
	if (work == NULL) {
		return 0;
	}
	body = work->body;
	if (body == NULL) {
		return 0;
	}

	switch (params->shape) {
		case 0:
			reach = fn_801991B4(&size);
			break;
		case 1:
			reach = size.x;
			break;
		case 2:
			reach = lightCollisionSqrtf(size.x * size.x + size.y * size.y);
			break;
		default:
			return 0;
	}
	if (DistanceP2P(&body->pos, &setdata->pos) > reach + body->radius) {
		return 0;
	}

	switch (params->shape) {
		case 0: {
			RwV3d local;
			RwV3d pos = body->pos;

			PushMatrixEx();
			UnitMatrix(NULL);
			fn_80196050(pCurrentMatrix, &setdata->pos, 1);
			RotateY(NULL, setdata->angY);
			RotateZ(NULL, setdata->angZ);
			njInvertMatrix(NULL);
			CalcPoint(NULL, &pos, &local);
			PopMatrixEx();
			if (local.x > size.x + body->radius || local.x < -size.x - body->radius
			    || local.y > size.y + body->radius || local.y < -size.y - body->radius
			    || local.z > size.z + body->radius || local.z < -size.z - body->radius) {
				return 0;
			}
			break;
		}
		case 1:
			break;
		case 2: {
			RwV3d local;
			RwV3d pos = body->pos;

			PushMatrixEx();
			UnitMatrix(NULL);
			fn_80196050(pCurrentMatrix, &setdata->pos, 1);
			RotateY(NULL, setdata->angY);
			RotateX(NULL, setdata->angX);
			RotateZ(NULL, setdata->angZ);
			njInvertMatrix(NULL);
			CalcPoint(NULL, &pos, &local);
			PopMatrixEx();
			if (local.y > size.y + body->height || local.y < -size.y - body->height) {
				return 0;
			}
			if (body->radius + lightCollisionSqrtf(local.x * local.x + local.z * local.z)
			    > size.x) {
				return 0;
			}
			break;
		}
		default:
			return 0;
	}
	return 1;
}
