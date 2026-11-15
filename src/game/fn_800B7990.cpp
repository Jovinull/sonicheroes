// Fills three tables of four 0x24-byte vertices (lbl_80304020, lbl_803040B0, lbl_80304140): each
// vertex gets the shared vector of lbl_80253B14 at +0xC and the pair of floats of its own table
// (lbl_80253AB4, lbl_80253AD4, lbl_80253AF4) at +0x1C. HYPOTHESIS: these are immediate-mode
// vertices (RwIm3DVertex is 0x24 bytes with u/v at +0x1C/+0x20) of three textured quads; the role
// of the +0xC vector is UNKNOWN.
#include "types.h"

struct Vec800B7990 {
	f32 x;
	f32 y;
	f32 z;
};

struct UV800B7990 {
	f32 u;
	f32 v;
};

struct Vertex800B7990 {
	u8 pad0[0xC];
	Vec800B7990 unknownC; // 0xC
	u8 pad18[4];
	UV800B7990 uv; // 0x1C
};

extern "C" {
extern Vertex800B7990 lbl_80304020[4];
extern Vertex800B7990 lbl_803040B0[4];
extern Vertex800B7990 lbl_80304140[4];
extern const UV800B7990 lbl_80253AB4[4];
extern const UV800B7990 lbl_80253AD4[4];
extern const UV800B7990 lbl_80253AF4[4];
extern const Vec800B7990 lbl_80253B14[4];

void fn_800B7990(void)
{
	int i;

	for (i = 0; i < 4; i++) {
		lbl_80304020[i].uv       = lbl_80253AB4[i];
		lbl_80304020[i].unknownC = lbl_80253B14[i];
		lbl_803040B0[i].uv       = lbl_80253AD4[i];
		lbl_803040B0[i].unknownC = lbl_80253B14[i];
		lbl_80304140[i].uv       = lbl_80253AF4[i];
		lbl_80304140[i].unknownC = lbl_80253B14[i];
	}
}
}
