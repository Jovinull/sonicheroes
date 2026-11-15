// Measures the distance from a point to a segment (HYPOTHESIS; names inferred): builds the line
// through the segment start and end, takes the nearest point on it (DistanceP2L) and, when that
// point lies within the segment (no farther from its midpoint than half the segment, using the
// half factor lbl_8042EF58), stores the fraction along the segment and the nearest point and
// returns the distance; otherwise returns lbl_8042EF5C. Built with the game-unit flags and
// -fp_contract off.
#include "game/misc.h"

extern "C" {
extern f32 lbl_8042EF58; // 0.5f
extern f32 lbl_8042EF5C;
// HYPOTHESIS: RwV3dLength.
f32 fn_801991B4(const RwV3d* vector);

f32 fn_801333C4(
    const RwV3d* start, const RwV3d* end, const RwV3d* point, f32* fraction, RwV3d* nearest)
{
	NJS_LINE line;
	RwV3d onLine;
	RwV3d offset;
	RwV3d half;
	RwV3d fromMiddle;
	f32 distance;

	line.p.x = start->x;
	line.p.y = start->y;
	line.p.z = start->z;
	line.v.x = end->x - start->x;
	line.v.y = end->y - start->y;
	line.v.z = end->z - start->z;
	distance = DistanceP2L(point, &line, &onLine);

	half.x       = lbl_8042EF58 * line.v.x;
	half.y       = lbl_8042EF58 * line.v.y;
	half.z       = lbl_8042EF58 * line.v.z;
	fromMiddle.x = onLine.x - (start->x + half.x);
	fromMiddle.y = onLine.y - (start->y + half.y);
	fromMiddle.z = onLine.z - (start->z + half.z);
	if (half.z * half.z + (half.x * half.x + half.y * half.y) >= fromMiddle.z * fromMiddle.z
	        + (fromMiddle.x * fromMiddle.x + fromMiddle.y * fromMiddle.y)) {
		f32 length = fn_801991B4(&line.v);
		offset.x   = onLine.x - start->x;
		offset.y   = onLine.y - start->y;
		offset.z   = onLine.z - start->z;
		*fraction  = fn_801991B4(&offset) / length;
		*nearest   = onLine;
		return distance;
	}
	return lbl_8042EF5C;
}
}
