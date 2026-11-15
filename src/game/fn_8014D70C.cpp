// Clones a spline (HYPOTHESIS: RpSplineClone): allocates the header with its inline control
// points, copies the type, control point count, flags and control points, and duplicates the
// derived point table (count - 2 entries for open splines, count - 3 for closed ones; other types
// raise error 1 of plugin 0x102 and get none). Allocation failures raise error 0x80000013 of plugin
// 0x102 with the size. Returns the clone, or null.
// NonMatching: retail keeps the derived point count and its byte size in separate saved registers
// (r30/r29, four saved in all) while this source lets them share one, so the frame and every later
// register differ (93 words, two instructions). A size local, declaration orders and plain
// expressions give the same allocation.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

#define RP_SPLINE_OBJECT_TYPE 0xC
#define RP_SPLINE_TYPE_OPEN   1
#define RP_SPLINE_TYPE_CLOSED 2
#define PLUGIN_ID_SPLINE      0x102

struct Spline8014D70C {
	u8 type; // 0x0
	u8 pad1[0x8 - 0x1];
	s32 numCtrlPoints; // 0x8
	s32 splineType;    // 0xC
	s32 flags10;       // 0x10
	RwV3d* points;     // 0x14: derived point table
	u8 pad18[0x38 - 0x18];
	RwV3d ctrlPoints[1]; // 0x38
};

static inline void RecordError8014D70C(s32 code)
{
	RwError error;
	error.pluginID  = PLUGIN_ID_SPLINE;
	error.errorCode = fn_8019408C(code);
	fn_80193FE8(&error);
}

static inline void RecordNoMemory8014D70C(u32 size)
{
	RwError error;
	error.pluginID  = PLUGIN_ID_SPLINE;
	error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
	fn_80193FE8(&error);
}

extern "C" {
Spline8014D70C* fn_8014D70C(Spline8014D70C* spline)
{
	Spline8014D70C* clone;
	s32 numPoints;

	clone = (Spline8014D70C*)lbl_8042C9A4->rwmalloc(
	    (spline->numCtrlPoints - 1) * sizeof(RwV3d) + sizeof(Spline8014D70C));
	if (clone != 0) {
		clone->type = RP_SPLINE_OBJECT_TYPE;
		switch (spline->splineType) {
			case RP_SPLINE_TYPE_OPEN:
				numPoints = spline->numCtrlPoints - 2;
				break;
			case RP_SPLINE_TYPE_CLOSED:
				numPoints = spline->numCtrlPoints - 3;
				break;
			default:
				RecordError8014D70C(1);
				numPoints = 0;
				break;
		}
		clone->numCtrlPoints = spline->numCtrlPoints;
		clone->splineType    = spline->splineType;
		clone->flags10       = spline->flags10;
		memcpy(clone->ctrlPoints, spline->ctrlPoints, spline->numCtrlPoints * sizeof(RwV3d));
		clone->points = (RwV3d*)lbl_8042C9A4->rwmalloc(numPoints * sizeof(RwV3d));
		if (clone->points != 0) {
			memcpy(clone->points, spline->points, numPoints * sizeof(RwV3d));
			return clone;
		}
		RecordNoMemory8014D70C(numPoints * sizeof(RwV3d));
		return 0;
	} else {
		RecordNoMemory8014D70C(
		    (spline->numCtrlPoints - 1) * sizeof(RwV3d) + sizeof(Spline8014D70C));
		return 0;
	}
}
}
