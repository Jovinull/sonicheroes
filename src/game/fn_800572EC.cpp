#include "game/octree.h"
#include "game/calc.h"

// Finds the ground and ceiling above and below a point for a collision probe: keeps the previous
// floor and ceiling attributes (+0x0 into +0x4, +0x8 into +0xC), then, with the stage octree
// (lbl_8042C150) loaded, probes along the search direction lbl_802D6350 from the point raised by
// lbl_8042D3D8: the floor (+0x10, lbl_8042D3DC deep) comes from the object octree lbl_8042C154
// (attribute 0x2) or else the stage octree (the polygon's attribute), the ceiling (+0x14,
// lbl_8042D3F8, direction Y lbl_8042D3F4) from the stage octree with its attribute (+0x8) and the
// polygon normal's angles (+0x18, +0x1C, GetAngleXZ). Missing hits give lbl_8042D3E8.
// HYPOTHESIS: the callbacks fn_80056C50 and fn_800574AC filter the polygons; names UNKNOWN.
// NonMatching (31 words): retail numbers the point's floats f5/f4/f3 and the raise f2 (MWCC puts
// the raise in f5), branches over the object probe with bne/b, and keeps the found flag in the
// zero register r5. Tried: the probe inline, if/else and goto shapes, chained zero stores.

struct Probe800572EC {
	u32 floorAttribute;         // 0x0
	u32 previousFloorAttribute; // 0x4
	u32 ceilAttribute;          // 0x8
	u32 previousCeilAttribute;  // 0xC
	f32 floor;                  // 0x10
	f32 ceil;                   // 0x14
	s32 angleX;                 // 0x18
	s32 angleZ;                 // 0x1C
};

extern "C" {
extern OCTREE* lbl_8042C150;
extern OCTREE* lbl_8042C154;
extern RwV3d lbl_802D6350;
extern const f32 lbl_8042D3D8;
extern const f32 lbl_8042D3DC;
extern const f32 lbl_8042D3E8;
extern const f32 lbl_8042D3F0;
extern const f32 lbl_8042D3F4;
extern const f32 lbl_8042D3F8;
s32 fn_80056C50(POLYDATA* poly);
s32 fn_800574AC(POLYDATA* poly);
}

// The floor from the object octree lbl_8042C154, probing from the raised point.
static inline s32 ObjectFloor(Probe800572EC* probe, const RwV3d* position)
{
	RwV3d start;
	RwV3d hit;

	start = *position;
	start.y += lbl_8042D3D8;
	if (lbl_8042C154->DetectAxisYCollisionWithPolygons(&start, lbl_8042D3DC, &hit, fn_80056C50)) {
		probe->floorAttribute |= 0x2;
		probe->floor = hit.y;
		return 1;
	}
	return 0;
}

extern "C" void fn_800572EC(Probe800572EC* probe, const RwV3d* position)
{
	RwV3d point;
	RwV3d hit;
	POLYDATA* poly;
	s32 found;

	probe->previousFloorAttribute = probe->floorAttribute;
	probe->previousCeilAttribute  = probe->ceilAttribute;
	probe->ceilAttribute = probe->floorAttribute = found = 0;
	if (lbl_8042C150 == NULL) {
		probe->ceil = probe->floor = lbl_8042D3E8;
		return;
	}
	point = *position;
	point.y += lbl_8042D3D8;
	lbl_802D6350.x = lbl_802D6350.z = lbl_8042D3F0;
	lbl_802D6350.y                  = lbl_8042D3D8;
	if (lbl_8042C154 != NULL) {
		found = ObjectFloor(probe, position);
	}
	if (!found) {
		poly = lbl_8042C150->DetectAxisYCollisionWithPolygons(
		    &point, lbl_8042D3DC, &hit, fn_800574AC);
		if (poly != NULL) {
			probe->floor          = hit.y;
			probe->floorAttribute = poly->attribute;
		} else {
			probe->floor = lbl_8042D3E8;
		}
	}
	lbl_802D6350.x = lbl_802D6350.z = lbl_8042D3F0;
	lbl_802D6350.y                  = lbl_8042D3F4;
	poly = lbl_8042C150->DetectAxisYCollisionWithPolygons(&point, lbl_8042D3F8, &hit, fn_800574AC);
	if (poly != NULL) {
		probe->ceil          = hit.y;
		probe->ceilAttribute = poly->attribute;
		GetAngleXZ(poly->norm.x, poly->norm.y, poly->norm.z, &probe->angleX, &probe->angleZ);
	} else {
		probe->ceil = lbl_8042D3E8;
	}
}
