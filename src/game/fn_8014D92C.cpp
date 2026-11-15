// Creates a spline (HYPOTHESIS: RpSplineCreate): allocates the header with room for the control
// points (count + 2 for open splines, count + 3 for closed ones; other types raise error 1 of
// plugin 0x102), initialises it, derives the control points from the given points (fn_8014B5E4)
// and keeps a copy of the given points. Allocation failures raise error 0x80000013 of plugin
// 0x102 with the size. Returns the spline, or null. Layout as in fn_8014D70C.
// NonMatching: retail keeps the size of the point copy in the type's saved register (r30) where
// this source reuses the header size's (r27), 5 words. Expression and scope variants do not help.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

#define RP_SPLINE_OBJECT_TYPE 0xC
#define RP_SPLINE_TYPE_OPEN   1
#define RP_SPLINE_TYPE_CLOSED 2
#define PLUGIN_ID_SPLINE      0x102

struct Spline8014D92C {
	u8 type; // 0x0
	u8 pad1[0x8 - 0x1];
	s32 numCtrlPoints; // 0x8
	s32 splineType;    // 0xC
	s32 flags10;       // 0x10
	RwV3d* points;     // 0x14: copy of the given points
	u8 flags18;        // 0x18
	u8 pad19[0x38 - 0x19];
	RwV3d ctrlPoints[1]; // 0x38
};

static inline void RecordError8014D92C(s32 code)
{
	RwError error;
	error.pluginID  = PLUGIN_ID_SPLINE;
	error.errorCode = fn_8019408C(code);
	fn_80193FE8(&error);
}

static inline void RecordNoMemory8014D92C(u32 size)
{
	RwError error;
	error.pluginID  = PLUGIN_ID_SPLINE;
	error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
	fn_80193FE8(&error);
}

extern "C" {
// HYPOTHESIS: derives the spline control points from the given points.
void* fn_8014B5E4(Spline8014D92C* spline, const RwV3d* points);

Spline8014D92C* fn_8014D92C(s32 numPoints, s32 type, const RwV3d* points)
{
	Spline8014D92C* spline;

	switch (type) {
		case RP_SPLINE_TYPE_OPEN: {
			u32 size = (numPoints + 1) * sizeof(RwV3d) + sizeof(Spline8014D92C);
			spline   = (Spline8014D92C*)lbl_8042C9A4->rwmalloc(size);
			if (spline == 0) {
				RecordNoMemory8014D92C(size);
				return 0;
			}
			spline->numCtrlPoints = numPoints + 2;
			break;
		}
		case RP_SPLINE_TYPE_CLOSED: {
			u32 size = (numPoints + 2) * sizeof(RwV3d) + sizeof(Spline8014D92C);
			spline   = (Spline8014D92C*)lbl_8042C9A4->rwmalloc(size);
			if (spline == 0) {
				RecordNoMemory8014D92C(size);
				return 0;
			}
			spline->numCtrlPoints = numPoints + 3;
			break;
		}
		default:
			RecordError8014D92C(1);
			return 0;
	}
	spline->flags10    = 0;
	spline->flags18    = 0;
	spline->splineType = type;
	spline->type       = RP_SPLINE_OBJECT_TYPE;
	if (fn_8014B5E4(spline, points) == 0) {
		lbl_8042C9A4->rwfree(spline);
		return 0;
	}
	spline->type = RP_SPLINE_OBJECT_TYPE;
	{
		u32 size = numPoints * sizeof(RwV3d);
		if ((spline->points = (RwV3d*)lbl_8042C9A4->rwmalloc(size)) == 0) {
			lbl_8042C9A4->rwfree(spline);
			RecordNoMemory8014D92C(size);
			return 0;
		}
		memcpy(spline->points, points, size);
	}
	return spline;
}
}
