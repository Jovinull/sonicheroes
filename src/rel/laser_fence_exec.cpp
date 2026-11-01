#include "types.h"

// TObjLaserfence::Exec (the PS2 build's name, by its place in the PS2 order;
// laserFenceExec here), the same in the thirteen stage modules that share the
// engine core. Out of range or due to be killed, the fence asks to be killed.
// On an edit it takes its placement again (kind, size and the count, or the
// group or enemy set its kind waits on). Otherwise, while the debug display is
// off, its centre follows the turned fence (out to its radius for kind 3), and
// by state: off (3) and on (2) fences switch after a count of frames (kind 1),
// when their switch group is complete (kind 2) or their enemies are gone
// (kind 4), with a sound; a sweeping fence (4) swings its radius on a sine
// and resizes its collision. Any fence not off keeps its collision with it.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

struct RwMatrixTag {
	RwV3d right; // 0x00
	u32 flags;   // 0x0C
	RwV3d up;    // 0x10
	u32 pad1C;   // 0x1C
	RwV3d at;    // 0x20
	u32 pad2C;   // 0x2C
	RwV3d pos;   // 0x30
	u32 pad3C;   // 0x3C
};

typedef struct LaserFenceParam {
	s32 kind;   // 0x00
	f32 width;  // 0x04
	f32 height; // 0x08
	u32 count;  // 0x0C
} LaserFenceParam;

typedef struct LaserFenceSet {
	RwV3d pos;  // 0x00
	sAngle ang; // 0x0C
	u8 unk18[0x14];
	LaserFenceParam* param; // 0x2C
} LaserFenceSet;

typedef struct LaserFenceInfo {
	u8 unk00;
	u8 form; // 0x01
	u8 unk02[0x6];
	f32 a; // 0x08
	u8 unk0C[0x8];
	f32 b; // 0x14
	f32 c; // 0x18
} LaserFenceInfo;

typedef struct LaserFence {
	u8 unk00[0x4];
	u16 signal; // 0x04
	u8 unk06[0x22];
	LaserFenceSet* set; // 0x28 (TObjSetObj)
	u8 unk2C[0x4];
	u8 colli[0x10];       // 0x30 (C_COLLI)
	LaserFenceInfo* info; // 0x40
	u8 unk44[0x4C];
	RwV3d colliPos;  // 0x90
	sAngle colliAng; // 0x9C
	u8 unkA8[0x4];
	RwV3d colliPrePos; // 0xAC
	s32 kind;          // 0xB8
	s32 state;         // 0xBC
	RwV3d pos;         // 0xC0
	sAngle ang;        // 0xCC
	f32 width;         // 0xD8
	f32 height;        // 0xDC
	f32 radius;        // 0xE0
	RwV3d center;      // 0xE4
	u32 count;         // 0xF0
	u32 timer;         // 0xF4
} LaserFence;

extern "C" u8* lbl_8042C180;
extern "C" void* lbl_8042C388;
extern RwMatrixTag* pCurrentMatrix;
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 laserFenceOne[1];
extern "C" const f32 laserFenceHalf[1];
extern "C" const f32 laserFenceMinEdit[1];
extern "C" const f32 laserFenceMinSize[1];
extern "C" const f32 laserFenceFlip;

extern "C" s32 CheckRangeOut__10TObjSetObjFv(void* setObj);
extern "C" s32 CheckMustKill__10TObjSetObjFv(void* setObj);
extern "C" s32 OnEdit__10TObjSetObjFv(void* setObj);
extern "C" void Entry__7C_COLLIFv(void* colli);
extern "C" void CalcRange__7C_COLLIFv(void* colli);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, const RwV3d* translation, s32 combine);
extern "C" void fn_800B5118(void* sound, s32 id, RwV3d* pos, s32 a, s32 b);
extern "C" void fn_800B4A38(void* sound, s32 id, RwV3d* pos, void* owner, s32 a, s32 b, s32 c);
extern "C" s32 objGroupAllSet(u8 group);
extern "C" s32 IsAnnihilated__19nEnemyCommunicationFUc(u8 group);

static inline RwV3d* laserFenceMatrixPos(RwMatrixTag* matrix)
{
	return matrix == NULL ? &pCurrentMatrix->pos : &matrix->pos;
}

static inline void laserFenceSound(LaserFence* object, s32 id)
{
	if (lbl_8042C388 != NULL) {
		fn_800B5118(lbl_8042C388, id, &object->center, 0, 0);
	}
}

extern "C" void laserFenceExec(LaserFence* object)
{
	if (CheckRangeOut__10TObjSetObjFv(&object->set)
	    || CheckMustKill__10TObjSetObjFv(&object->set)) {
		object->signal |= 1;
		return;
	}
	if (OnEdit__10TObjSetObjFv(&object->set)) {
		LaserFenceParam* param = object->set->param;

		object->pos  = object->set->pos;
		object->ang  = object->set->ang;
		object->kind = param->kind;
		switch (object->kind) {
			case 1:
			case 3:
				object->count = param->count;
				object->timer = 0;
				break;
			case 2:
			case 4:
				*(u8*)&object->count = param->count;
				break;
		}
		object->height = param->height;
		object->width  = param->width;
		object->center = object->pos;
		return;
	}
	if ((s8)lbl_8042C180[5] == 0) {
		RwMatrixTag matrix;

		fn_80195790(&matrix, &AxisX, laserFenceFlip, laserFenceMinEdit[0], 0);
		fn_80195790(&matrix, &AxisY, laserFenceOne[0] - fn_800D7AE4(object->ang.y),
		    fn_800D7B00(object->ang.y), 2);
		fn_80195790(&matrix, &AxisX, laserFenceOne[0] - fn_800D7AE4(object->ang.x),
		    fn_800D7B00(object->ang.x), 2);
		fn_80195790(&matrix, &AxisZ, laserFenceOne[0] - fn_800D7AE4(object->ang.z),
		    fn_800D7B00(object->ang.z), 2);
		fn_80196050(&matrix, &object->pos, 2);
		if (object->kind == 3) {
			RwV3d offset;

			offset.x = object->radius;
			offset.y = offset.z = laserFenceMinEdit[0];
			fn_80196050(&matrix, &offset, 1);
		}
		{
			RwV3d* at = laserFenceMatrixPos(&matrix);

			object->center.x = at->x;
			object->center.y = at->y;
			object->center.z = at->z;
		}
		switch (object->state) {
			case 1:
				break;
			case 3:
				if (object->kind == 1) {
					if (object->timer++ > object->count) {
						object->timer = 0;
						object->state = 2;
						laserFenceSound(object, 0x1031);
					}
				} else if (object->kind == 2) {
					if (!objGroupAllSet(*(u8*)&object->count)) {
						object->state = 2;
						laserFenceSound(object, 0x1031);
					}
				} else if (object->kind == 4) {
					if (!IsAnnihilated__19nEnemyCommunicationFUc(*(u8*)&object->count)) {
						object->state = 2;
						laserFenceSound(object, 0x1031);
					}
				}
				break;
			case 2:
				if (object->kind == 1) {
					if (object->timer++ > object->count) {
						object->timer = 0;
						object->state = 3;
						laserFenceSound(object, 0x1032);
					}
				} else if (object->kind == 2) {
					if (objGroupAllSet(*(u8*)&object->count)) {
						object->state = 3;
						laserFenceSound(object, 0x1032);
					}
				} else if (object->kind == 4) {
					if (IsAnnihilated__19nEnemyCommunicationFUc(*(u8*)&object->count)) {
						object->state = 3;
						laserFenceSound(object, 0x1032);
					}
				}
				break;
			case 4:
				if ((s8)lbl_8042C180[0x1F] == 0) {
					object->radius
					    = laserFenceHalf[0] * (object->height * fn_800D7B00(object->timer));
					object->timer += object->count;
					if (object->info != NULL) {
						if (object->state == 4) {
							object->info->a = object->radius;
							object->info->b = laserFenceMinSize[0];
							object->info->c = laserFenceHalf[0] * object->width;
							if (object->info->c < laserFenceMinSize[0]) {
								object->info->c = laserFenceMinSize[0];
							}
						} else {
							const f32* limit;

							object->info->b = laserFenceHalf[0] * object->height;
							if (object->info->b < *(limit = laserFenceMinSize)) {
								object->info->b = *limit;
							}
							object->info->c = laserFenceHalf[0] * object->width;
							if (object->info->c < *(limit = laserFenceMinSize)) {
								object->info->c = *limit;
							}
						}
						if (object->ang.x == 0 && object->ang.z == 0) {
							object->info->form = 4;
						} else {
							object->info->form = 7;
						}
						CalcRange__7C_COLLIFv(object->colli);
					}
					if (lbl_8042C388 != NULL) {
						fn_800B4A38(lbl_8042C388, 0x1030, &object->center, object, 3, 0x30, 2);
					}
				}
				break;
		}
	}
	if (object->state != 3) {
		object->colliPrePos = object->colliPos;
		object->colliPos    = object->pos;
		object->colliAng    = object->ang;
		Entry__7C_COLLIFv(object->colli);
	}
}
