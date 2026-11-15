// fn_800E59D0's test (without its counter reset) plus a second one: a collision polygon with flag
// 0x8000 (+0x18) is rejected, the point lbl_803E7068 must lie on the normal's side of the
// polygon's plane (as in fn_800E59D0), and the offset from the foot of that point to a second
// point (lbl_803E7074) must not run along the normalized direction lbl_803E705C (dot product above
// lbl_8042E254). HYPOTHESIS: a swept-sphere facing test; the roles are UNKNOWN.
#include "game/misc.h"

struct Poly800E55EC {
	u16 vertex; // 0x0
	u8 pad2[0xC - 0x2];
	RwV3d normal; // 0xC
	u32 flags;    // 0x18
};

struct Data800E55EC {
	u8 pad0[0x8];
	RwV3d* vertices; // 0x8
	u8 padC[0x188 - 0xC];
	s32 unknown188; // 0x188
};

extern "C" {
extern Data800E55EC* lbl_8042C150;
extern RwV3d lbl_803E7068;
extern RwV3d lbl_803E7074;
extern RwV3d lbl_803E705C;
extern const f32 lbl_8042E278;
extern const f32 lbl_8042E254;
f32 fn_801990E0(RwV3d* out, const RwV3d* in);
}

extern "C" s32 fn_800E55EC(Poly800E55EC* poly)
{
	NJS_LINE plane;
	RwV3d foot;
	RwV3d offset;

	if (poly->flags & 0x8000) {
		return 0;
	}
	RwV3d* vertex = &lbl_8042C150->vertices[poly->vertex];
	// The vertex is read before the normal is copied (plain struct assignments reorder the loads).
	f32 x     = vertex->x;
	f32 y     = vertex->y;
	f32 z     = vertex->z;
	plane.v.x = poly->normal.x;
	plane.v.y = poly->normal.y;
	plane.v.z = poly->normal.z;
	plane.p.x = x;
	plane.p.y = y;
	plane.p.z = z;
	DistanceP2PL(&lbl_803E7068, &plane, &foot);
	offset.x = lbl_803E7068.x - foot.x;
	offset.y = lbl_803E7068.y - foot.y;
	offset.z = lbl_803E7068.z - foot.z;
	if (offset.z * offset.z + (offset.x * offset.x + offset.y * offset.y) > lbl_8042E278) {
		fn_801990E0(&offset, &offset);
		if (offset.z * poly->normal.z + (offset.x * poly->normal.x + offset.y * poly->normal.y)
		    < lbl_8042E254) {
			return 0;
		}
	}
	f32 dx = lbl_803E7074.x - foot.x;
	f32 dy = lbl_803E7074.y - foot.y;
	f32 dz = lbl_803E7074.z - foot.z;
	RwV3d direction;
	fn_801990E0(&direction, &lbl_803E705C);
	if (dz * direction.z + (dx * direction.x + dy * direction.y) > lbl_8042E254) {
		return 0;
	}
	return 1;
}
