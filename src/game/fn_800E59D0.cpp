// Whether a collision polygon faces the point lbl_803E7068: clears the counter +0x188 of the
// collision data (lbl_8042C150), rejects a polygon with flag 0x8000 (+0x18), and finds the foot of
// the point on the polygon's plane (its first vertex, from the data's vertex table +0x8, and its
// normal +0xC). A point off the plane (squared distance above lbl_8042E278) must lie on the
// normal's side (the normalized offset's dot product with the normal at least lbl_8042E254).
// HYPOTHESIS: the roles are UNKNOWN.
#include "game/misc.h"

struct Poly800E59D0 {
	u16 vertex; // 0x0
	u8 pad2[0xC - 0x2];
	RwV3d normal; // 0xC
	u32 flags;    // 0x18
};

struct Data800E59D0 {
	u8 pad0[0x8];
	RwV3d* vertices; // 0x8
	u8 padC[0x188 - 0xC];
	s32 unknown188; // 0x188
};

extern "C" {
extern Data800E59D0* lbl_8042C150;
extern RwV3d lbl_803E7068;
extern const f32 lbl_8042E278;
extern const f32 lbl_8042E254;
f32 fn_801990E0(RwV3d* out, const RwV3d* in);
}

extern "C" s32 fn_800E59D0(Poly800E59D0* poly)
{
	NJS_LINE plane;
	RwV3d foot;
	RwV3d offset;

	lbl_8042C150->unknown188 = 0;
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
	return 1;
}
