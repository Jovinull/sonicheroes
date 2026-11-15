// Appends a source path to a destination path (HYPOTHESIS): refreshes the cached squared length at
// 0x398 of lbl_803EC968 (fn_8016ED64), then walks the source points (a raw array, or a growable
// array when the count is -1). A type-2 point starts a curve: its previous point, itself and the
// next two points are handed to fn_80170490 with the setting at 0x3A0 and the walk skips the two
// control points; any other point is copied to a new point of the destination. A closed source
// path closes the destination (fn_80170204). Names are inferred from this function and
// fn_8016FE54. Returns the destination.
// NonMatching: retail copies the control points and the plain points as integer words (lwz/stw
// pairs); C++ compiles these float struct copies to lfs/stfs. Compiling the same source as C
// gives the word copies (28 words then differ: the 0x398 store order and two loop registers),
// which with fn_8016EAB4's matrix stack suggests this block (lbl_803EC968) is the RenderWare
// Rt2d toolkit, a C library; moving it to a reviewed C boundary is left for review.
#include "game/rw_engine.h"

struct V2d80170854 {
	f32 x;
	f32 y;
};

// Path point (layout as in fn_8016FE54).
struct Point80170854 {
	s32 type;           // 0x0: 2 starts a curve
	V2d80170854 pos;    // 0x4
	V2d80170854 normal; // 0xC
	f32 length;         // 0x14
};

struct Path80170854 {
	RwSList* points; // 0x0
};

// Source path: points is a raw array, or an RwSList when count is -1.
struct PathSource80170854 {
	void* points; // 0x0
	s32 count;    // 0x4
	s32 closed;   // 0x8
};

struct Block80170854 {
	u8 pad0[0x398];
	f32 lengthSquared; // 0x398
	u8 pad39C[0x3A0 - 0x39C];
	s32 curveSetting; // 0x3A0, UNKNOWN
};

extern "C" {
extern Block80170854 lbl_803EC968;
f32 fn_8016ED64(void);
// HYPOTHESIS: _rwSListGetArray, _rwSListGetNumEntries and _rwSListGetNewEntry.
void* fn_8019460C(RwSList* sList);
s32 fn_8019469C(RwSList* sList);
void* fn_80194430(RwSList* sList);
void fn_80170490(Path80170854* path, V2d80170854* controls, s32 setting);
void fn_80170204(Path80170854* path);

Path80170854* fn_80170854(Path80170854* path, PathSource80170854* source)
{
	s32 count;
	Point80170854* point;
	s32 i;

	lbl_803EC968.lengthSquared = fn_8016ED64();
	if (source->count == -1) {
		point = (Point80170854*)fn_8019460C((RwSList*)source->points);
	} else {
		point = (Point80170854*)source->points;
	}
	count = source->count;
	if (count == -1) {
		count = fn_8019469C((RwSList*)source->points);
	}

	for (i = 0; i < count; i++) {
		if (point->type == 2) {
			V2d80170854 controls[4];
			controls[0] = point[-1].pos;
			controls[1] = point[0].pos;
			controls[2] = point[1].pos;
			controls[3] = point[2].pos;
			fn_80170490(path, controls, lbl_803EC968.curveSetting);
			i += 2;
			point += 2;
		} else {
			*(Point80170854*)fn_80194430(path->points) = *point;
		}
		point++;
	}

	if (source->closed != 0) {
		fn_80170204(path);
	}
	return path;
}
}
