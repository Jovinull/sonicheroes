// Fetches triangle i of an indexed triangle strip (HYPOTHESIS): reads the three vertex indices
// (u16, stride bytes apart), skipping the degenerate joints of a stitched strip and swapping the
// last two on odd triangles to keep the winding, then points the triangle at the position
// (3 * size each), normal (9 * size) and texture coordinate (2 * size) data of its vertices.
// Field names are inferred from this function only.
// The u16-index twin of fn_80143AE4.
// NonMatching: same joint-block register difference as fn_80143AE4, and the u16 reads through the
// helper also shift the index registers (75 words differ).
#include "types.h"

struct Triangle80143C3C {
	u8* positions[3]; // 0x0
	u8* normal;       // 0xC: normal data of the first vertex
	u8* uvs[3];       // 0x10
	u8 positionSize;  // 0x1C
	u8 normalSize;    // 0x1D
	u8 uvSize;        // 0x1E
};

// Reads the u16 index at a byte offset.
static inline u16 Index80143C3C(const u8* indices, s32 offset)
{
	return *(const u16*)(indices + offset);
}

extern "C" {
void fn_80143C3C(Triangle80143C3C* triangle, const u8* indices, s32 stride, u8* positions,
    u8* normals, u8* uvs, s32 i)
{
	u32 a = Index80143C3C(indices, stride * i);
	u16 b;
	u16 c;

	if (i < 2) {
		if (i == 0) {
			b = Index80143C3C(indices, stride);
			c = Index80143C3C(indices, stride * 2);
		} else {
			c = Index80143C3C(indices, 0);
			b = Index80143C3C(indices, stride * 2);
		}
	} else {
		b = Index80143C3C(indices, stride * (i - 2));
		c = Index80143C3C(indices, stride * (i - 1));
		if (b == c) {
			c = Index80143C3C(indices, stride * (i + 1));
			if (a == c) {
				i++;
				b = Index80143C3C(indices, stride * (i + 1));
				if (a == b) {
					i++;
					b = Index80143C3C(indices, stride * (i + 1));
				}
				c = Index80143C3C(indices, stride * (i + 2));
			}
		}
		if (i & 1) {
			u16 swap = c;
			c        = b;
			b        = swap;
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
