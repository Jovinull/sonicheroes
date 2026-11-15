// Fetches triangle i of an indexed triangle strip (HYPOTHESIS): reads the three vertex indices
// (u8, stride bytes apart), skipping the degenerate joints of a stitched strip and swapping the
// last two on odd triangles to keep the winding, then points the triangle at the position
// (3 * size each), normal (9 * size) and texture coordinate (2 * size) data of its vertices.
// Field names are inferred from this function only.
// NonMatching: retail keeps the lookahead index in its own register and moves it into place
// (b = c, c = next) when the joint is not doubled; this form reuses c for the lookahead, so the
// register use of the joint block differs (23 words). The explicit-lookahead form with every
// u8/u32 typing of the indices stays at 40 words or more.
#include "types.h"

struct Triangle80143AE4 {
	u8* positions[3]; // 0x0
	u8* normal;       // 0xC: normal data of the first vertex
	u8* uvs[3];       // 0x10
	u8 positionSize;  // 0x1C
	u8 normalSize;    // 0x1D
	u8 uvSize;        // 0x1E
};

extern "C" {
void fn_80143AE4(Triangle80143AE4* triangle, const u8* indices, s32 stride, u8* positions,
    u8* normals, u8* uvs, s32 i)
{
	u32 a = indices[stride * i];
	u8 b;
	u8 c;

	if (i < 2) {
		if (i == 0) {
			b = indices[stride];
			c = indices[stride * 2];
		} else {
			c = indices[0];
			b = indices[stride * 2];
		}
	} else {
		b = indices[stride * (i - 2)];
		c = indices[stride * (i - 1)];
		if (b == c) {
			c = indices[stride * (i + 1)];
			if (a == c) {
				i++;
				b = indices[stride * (i + 1)];
				if (a == b) {
					i++;
					b = indices[stride * (i + 1)];
				}
				c = indices[stride * (i + 2)];
			}
		}
		if (i & 1) {
			u8 swap = c;
			c       = b;
			b       = swap;
		}
	}

	triangle->positions[0] = positions + a * (triangle->positionSize * 3);
	triangle->positions[1] = positions + b * (triangle->positionSize * 3);
	triangle->positions[2] = positions + c * (triangle->positionSize * 3);
	triangle->normal       = normals + a * (triangle->normalSize * 9);
	triangle->uvs[0]       = uvs + a * (triangle->uvSize * 2);
	triangle->uvs[1]       = uvs + b * (triangle->uvSize * 2);
	triangle->uvs[2]       = uvs + c * (triangle->uvSize * 2);
}
}
