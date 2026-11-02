#include "types.h"

// The move step of the object each searcher builds into its +0x2F0 field
// (searcherGroundMove here, run first by searcherGroundExec), the same in the
// thirteen stage modules that share the engine core. While its collision volume
// is active it notes whether any player it touches has not died. Then it casts
// a line of the volume's length from its start, turned by its angles, against
// the octree; the length becomes the distance to the first polygon hit (at
// least searcherGroundUnkF4), and the volume's sphere is placed along that
// line, scaled to it.

typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;

typedef struct RwMatrix {
	u8 data[0x40];
} RwMatrix;

typedef struct CollisionInfo {
	u8 unk00[0x8];
	RwV3d offset; // 0x08
	u8 unk14[0x4];
	f32 radius; // 0x18
	u8 unk1C[0xC];
	s32 angleY; // 0x28
	s32 angleX; // 0x2C
} CollisionInfo;

typedef struct Hitter {
	u8 unk00[0x78];
	s32 type; // 0x78
} Hitter;

typedef struct Hit {
	u8 unk00[0x4];
	Hitter* hitter; // 0x04
} Hit;

typedef struct SearcherGround {
	u8 unk00[0x60];
	u8 volume[0x8];  // 0x60
	u16 volumeFlags; // 0x68
	u8 pad6A[0x2];
	f32 volumeRadius;    // 0x6C
	CollisionInfo* info; // 0x70
	u8 unk74[0x4C];
	RwV3d start; // 0xC0
	u8 unkCC[0x1C];
	f32 angleY;  // 0xE8
	f32 angleX;  // 0xEC
	s32 touched; // 0xF0
	f32 length;  // 0xF4
	RwV3d end;   // 0xF8
} SearcherGround;

struct POLYDATA;

class OCTREE
{
public:
	void* DetectLineCollisionWithPolygons(
	    const RwV3d* start, const RwV3d* end, RwV3d* hit, s32 (*filter)(POLYDATA*));
};

f32 DistanceP2P(const RwV3d* a, const RwV3d* b);

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" u8 lbl_8042C1A4[];
extern "C" void* lbl_802AD070[];
extern "C" OCTREE* lbl_8042C150;
extern "C" const f32 searcherGroundUnkE8;
extern "C" const f32 searcherGroundUnkF4;
extern "C" const f32 searcherGroundYaw;
extern "C" const f32 searcherGroundRadiusScale;
extern "C" const f32 searcherGroundDegreesToAngle;

extern "C" void fn_80021824(void* world);
extern "C" Hit* fn_800211A8(void* volume);
extern "C" s32 fn_80041B64(s32 type);
extern "C" s32 fn_800AB32C(void* player);
extern "C" void fn_80195A74(RwMatrix* matrix, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_8019947C(RwV3d* out, const RwV3d* in, s32 count, const RwMatrix* matrix);

static inline Hitter* searcherGroundHitter(Hit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

extern "C" void searcherGroundMove(SearcherGround* object)
{
	Hitter* hitter;
	CollisionInfo* info;
	s32 no;
	RwV3d dir;
	RwV3d hit;
	RwMatrix matrix;
	RwMatrix rotation;
	f32 length;

	if (object->info == NULL) {
		return;
	}
	if (object->volumeFlags & 1) {
		object->touched = 0;
		fn_80021824(lbl_8042C1A4);
		while ((hitter = searcherGroundHitter(fn_800211A8(object->volume))) != NULL) {
			no = fn_80041B64(hitter->type);
			if (no != -1 && lbl_802AD070[no] != NULL && fn_800AB32C(lbl_802AD070[no]) == 0) {
				object->touched = 1;
			}
		}
	} else {
		object->touched = 0;
	}

	length = searcherGroundUnkE8;
	dir.x  = length;
	dir.y  = length;
	dir.z  = -object->volumeRadius;
	fn_80195A74(&matrix, &AxisX, -object->angleX, 0);
	fn_80195A74(&matrix, &AxisY, searcherGroundYaw + object->angleY, 2);
	fn_8019947C(&object->end, &dir, 1, &matrix);
	if (lbl_8042C150->DetectLineCollisionWithPolygons(&object->start, &object->end, &hit, NULL)
	    != NULL) {
		length = DistanceP2P(&object->start, &hit);
	}
	if (length < searcherGroundUnkF4) {
		// volatile is a reconstruction aid: the retail reloads the minimum
		// rather than reusing the value it just compared against.
		length = *(volatile const f32*)&searcherGroundUnkF4;
	}
	object->length = length;

	info           = object->info;
	info->radius   = searcherGroundRadiusScale * object->length;
	info->angleX   = (s32)(searcherGroundDegreesToAngle * object->angleX) - 0x4000;
	info->angleY   = (s32)(searcherGroundDegreesToAngle * object->angleY) + 0x4000;
	info->offset.x = searcherGroundUnkE8;
	info->offset.y = searcherGroundUnkE8;
	info->offset.z = info->radius;
	fn_80195A74(&rotation, &AxisX, object->angleX, 0);
	fn_80195A74(&rotation, &AxisY, object->angleY, 2);
	fn_8019947C(&info->offset, &info->offset, 1, &rotation);
}
