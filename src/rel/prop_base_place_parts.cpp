#include "types.h"

// The common stage object base's part placement (propBasePlaceParts here; the
// class has no PS2 name), the same in the six stage modules that carry it:
// each active collision part (flag 0x20) takes its layout's offset turned by
// the object's place and angles, and the layout's own angles on top of the
// object's (or the object's angles alone).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

struct RwMatrixTag;

typedef struct PropPart {
	u8 unk00[0x4];
	u32 flags; // 0x04
	RwV3d pos; // 0x08
	u8 unk14[0x10];
	sAngle ang; // 0x24
} PropPart;     // 0x30

typedef struct PropBase {
	u8 unk000[0x32];
	u16 parts; // 0x032
	u8 unk034[0x4];
	PropPart* part; // 0x038
	u8 unk03C[0x78];
	RwV3d pos;  // 0x0B4
	sAngle ang; // 0x0C0
} PropBase;

extern RwMatrixTag* pCurrentMatrix;

void PushUnitMatrix();
void PopMatrixEx();
void RotateX(RwMatrixTag* matrix, s32 angle);
void RotateY(RwMatrixTag* matrix, s32 angle);
void RotateZ(RwMatrixTag* matrix, s32 angle);
void CalcPoint(const RwMatrixTag* matrix, const RwV3d* point, RwV3d* out);
void GetRotYXZ(RwMatrixTag* matrix, s32* x, s32* y, s32* z);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);

extern "C" void propBasePlaceParts(PropBase* object, PropPart* layout)
{
	PropPart* to;
	RwV3d pos;
	sAngle ang;
	u8 i;
	PropPart* from;

	from = layout;
	to   = object->part;

	if (object->parts != 0) {
		for (i = 0; i < object->parts; i++) {
			if (from == NULL || to == NULL) {
				from++;
				to++;
			} else if ((to->flags & 0x20) == 0) {
				from++;
				to++;
			} else {
				pos.x = from->pos.x;
				pos.y = from->pos.y;
				pos.z = from->pos.z;
				PushUnitMatrix();
				fn_80196050(pCurrentMatrix, &object->pos, 1);
				RotateZ(NULL, object->ang.z);
				RotateX(NULL, object->ang.x);
				RotateY(NULL, object->ang.y);
				CalcPoint(NULL, &pos, &pos);
				// (the volatile read keeps the retail's second load of the angle)
				if (*(volatile s32*)&from->ang.z != 0 || from->ang.x != 0 || from->ang.y != 0) {
					RotateZ(NULL, from->ang.z);
					RotateX(NULL, from->ang.x);
					RotateY(NULL, from->ang.y);
					GetRotYXZ(pCurrentMatrix, &ang.x, &ang.y, &ang.z);
				} else {
					ang.x = object->ang.x;
					ang.y = object->ang.y;
					ang.z = object->ang.z;
				}
				PopMatrixEx();
				to->pos.x = pos.x;
				to->pos.y = pos.y;
				to->pos.z = pos.z;
				to->ang.x = ang.x;
				to->ang.y = ang.y;
				to->ang.z = ang.z;
				to++;
				from++;
			}
		}
	}
}
