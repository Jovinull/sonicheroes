// Draws a ribbon trail (HYPOTHESIS; names inferred): with more than two points, saves and sets the
// blend, z-test, raster, vertex-alpha and cull render states, rebuilds the segment vertices
// (fn_80103D48) and renders count - 1 segments of the 32-entry ring at 0x438 starting at the head
// (0x2A), each as a 12-vertex triangle strip through the 3D immediate mode, then restores the
// states.
#include "types.h"

#define TRAIL_SEGMENT_COUNT 32

struct Segment80103BC8 {
	u8 vertices[0x1B0]; // 12 immediate-mode vertices of 0x24 bytes
};

struct Trail80103BC8 {
	u8 pad0[0x2A];
	s16 head;  // 0x2A
	s16 count; // 0x2C
	u8 pad2E[0x438 - 0x2E];
	Segment80103BC8 segments[TRAIL_SEGMENT_COUNT]; // 0x438
};

extern "C" {
// HYPOTHESIS: RwRenderStateGet/Set, RwIm3DTransform, RwIm3DRenderPrimitive and RwIm3DEnd.
s32 fn_80194294(s32 state, void* value);
s32 fn_80194234(s32 state, void* value);
void* fn_801B2934(void* vertices, u32 numVertices, void* ltm, u32 flags);
s32 fn_801B2C00(s32 primType);
s32 fn_801B2A14(void);
void fn_80103D48(Trail80103BC8* trail);

void fn_80103BC8(Trail80103BC8* trail)
{
	void* srcBlend;
	void* destBlend;
	void* zTest;
	void* vertexAlpha;
	void* cull;
	s32 i;
	Segment80103BC8* segment;

	if (trail->count > 2) {
		fn_80194294(10, &srcBlend);
		fn_80194294(11, &destBlend);
		fn_80194294(20, &zTest);
		fn_80194294(12, &vertexAlpha);
		fn_80194294(14, &cull);
		fn_80194234(10, (void*)5);
		fn_80194234(11, (void*)2);
		fn_80194234(20, (void*)1);
		fn_80194234(1, (void*)0);
		fn_80194234(12, (void*)1);
		fn_80194234(14, (void*)0);
		fn_80103D48(trail);
		segment = &trail->segments[trail->head];
		for (i = 0; i < trail->count - 1; i++) {
			if (fn_801B2934(segment, 12, 0, 0x18) != 0) {
				fn_801B2C00(4);
			}
			if (segment >= &trail->segments[TRAIL_SEGMENT_COUNT - 1]) {
				segment = &trail->segments[0];
			} else {
				segment++;
			}
		}
		fn_801B2A14();
		fn_80194234(14, cull);
		fn_80194234(12, vertexAlpha);
		fn_80194234(20, zTest);
		fn_80194234(10, srcBlend);
		fn_80194234(11, destBlend);
	}
}
}
