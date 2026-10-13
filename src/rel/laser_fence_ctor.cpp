#include "types.h"

// The laser fence's constructor (laserFenceCtor here), called by the factory
// in the module's laser fence hooks.
//
// It takes the placement's position, angle and parameters: the kind, the width
// and height, and a value kept whole for kinds 1 and 3 and as a byte for kinds
// 2 and 4. The kind picks the first state (1 for kind 0, 4 for kind 3, 3 for
// the others). Outside the editor it gives the collision its shape: half the
// width and height (kind 3 keeps its radius and only takes half the width),
// at least 5 each, and a flat check for a fence that is not tilted.
//
// The limit 5.0 is a pooled constant of the TU (a named extern here): read
// through a pointer taken inside the comparison, it loads after the size and
// lands in f0, as the retail's literal does.

typedef struct LaserFenceVec {
	f32 x, y, z;
} LaserFenceVec;

typedef struct LaserFenceAngle {
	s32 x, y, z;
} LaserFenceAngle;

typedef struct LaserFenceParams {
	s32 kind;   // 0x00
	f32 width;  // 0x04
	f32 height; // 0x08
	s32 value;  // 0x0C
} LaserFenceParams;

typedef struct LaserFenceFrame {
	LaserFenceVec pos;        // 0x00
	LaserFenceAngle ang;      // 0x0C
	u8 unk18[0x14];           // 0x18
	LaserFenceParams* params; // 0x2C
} LaserFenceFrame;

typedef struct LaserFenceShape {
	u8 unk00;    // 0x00
	u8 kind;     // 0x01
	u8 unk02[6]; // 0x02
	f32 radius;  // 0x08
	u8 unk0C[8]; // 0x0C
	f32 height;  // 0x14
	f32 width;   // 0x18
} LaserFenceShape;

typedef struct LaserFenceTask {
	const char* className; // 0x00
	u16 signal;            // 0x04
	u16 tag;               // 0x06
	u8 unk08[0x10];        // 0x08
	void** vtable;         // 0x18
	s16 unk1C;             // 0x1C
	s16 objectSize;        // 0x1E
	u8 unk20[0x8];         // 0x20
} LaserFenceTask;          // 0x28

typedef struct LaserFenceMotion {
	LaserFenceFrame* frame; // 0x00
	void** vtable;          // 0x04
} LaserFenceMotion;         // 0x08

typedef struct LaserFence {
	LaserFenceTask base;     // 0x00
	LaserFenceMotion motion; // 0x28
	u8 colli[0x10];          // 0x30
	LaserFenceShape* shape;  // 0x40
	u8 colli44[0x74];        // 0x44
	s32 kind;                // 0xB8
	s32 state;               // 0xBC
	LaserFenceVec pos;       // 0xC0
	LaserFenceAngle ang;     // 0xCC
	f32 width;               // 0xD8
	f32 height;              // 0xDC
	f32 radius;              // 0xE0
	LaserFenceVec start;     // 0xE4
	union {
		s32 value;
		u8 byte;
	} value;   // 0xF0
	s32 unkF4; // 0xF4
} LaserFence;  // 0xF8

extern "C" void* laserFenceVtable[];
extern "C" const char* laserFenceClassName;
extern "C" u8 laserFenceCclInfo[];
extern "C" const f32 laserFenceMinSize[1];
extern "C" const f32 laserFenceHalf[1];

extern "C" void __ct__7TObjectFP7TObject(LaserFenceTask* object, void* owner);
extern "C" void __ct__10TObjSetObjFv(LaserFenceMotion* motion);
extern "C" void __ct__7C_COLLIFv(void* colli);
extern "C" s32 OnEdit__10TObjSetObjFv(LaserFenceMotion* motion);
extern "C" void Init__7C_COLLIFP8CCL_INFOiUc(void* colli, void* info, s32 count, u8 kind);
extern "C" void CalcRange__7C_COLLIFv(void* colli);

extern "C" LaserFence* laserFenceCtor(LaserFence* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	__ct__10TObjSetObjFv(&object->motion);
	__ct__7C_COLLIFv(object->colli);
	object->base.vtable      = laserFenceVtable;
	object->motion.vtable    = laserFenceVtable + 0xB;
	object->base.className   = laserFenceClassName;
	object->base.objectSize  = 0xF8;
	LaserFenceParams* params = object->motion.frame->params;
	object->pos              = object->motion.frame->pos;
	object->ang              = object->motion.frame->ang;
	object->kind             = params->kind;

	switch (object->kind) {
		case 1:
		case 3:
			object->value.value = params->value;
			object->unkF4       = 0;
			break;
		case 2:
		case 4:
			object->value.byte = params->value;
			break;
	}
	object->height = params->height;
	object->width  = params->width;
	object->start  = object->pos;

	switch (object->kind) {
		case 0:
			object->state = 1;
			break;
		case 1:
			object->state = 3;
			break;
		case 2:
			object->state = 3;
			break;
		case 3:
			object->state = 4;
			break;
		case 4:
			object->state = 3;
			break;
	}

	if (OnEdit__10TObjSetObjFv(&object->motion) == 0) {
		Init__7C_COLLIFP8CCL_INFOiUc(object->colli, laserFenceCclInfo, 1, 4);
		if (object->shape != NULL) {
			if (object->state == 4) {
				object->shape->radius = object->radius;
				object->shape->height = laserFenceMinSize[0];
				object->shape->width  = laserFenceHalf[0] * object->width;
				if (object->shape->width < laserFenceMinSize[0]) {
					object->shape->width = laserFenceMinSize[0];
				}
			} else {
				const f32* limit;
				object->shape->height = laserFenceHalf[0] * object->height;
				if (object->shape->height < *(limit = laserFenceMinSize)) {
					object->shape->height = *limit;
				}
				object->shape->width = laserFenceHalf[0] * object->width;
				if (object->shape->width < *(limit = laserFenceMinSize)) {
					object->shape->width = *limit;
				}
			}
			if (object->ang.x == 0 && object->ang.z == 0) {
				object->shape->kind = 4;
			} else {
				object->shape->kind = 7;
			}
			CalcRange__7C_COLLIFv(object->colli);
		}
	}
	return object;
}
