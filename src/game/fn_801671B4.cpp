// Counts the strips a run of triangles (count u16 indices, read as a sliding strip window) breaks
// into and the indices those strips need (HYPOTHESIS: strip statistics for a strip builder).
// Degenerate triangles end the current strip; with joining enabled a strip that would restart on
// an odd triangle starts two triangles long, and a degenerate triangle followed by a valid one on
// an odd position only extends the strip. Adds to *numStrips and *numIndices (both cleared first).
// NonMatching: retail stores the two zero counters from r9 and only then sets the loop index (also
// r9); this source uses r10 for the zero and sets the index between the stores (4 words differ).
// Statement order, chained assignments, signed counters and compilers 1.3/2.0 do not change it.
#include "types.h"

// Closes the current strip of run triangles: run + 2 indices, one more strip. Returns the new run.
static inline u32 EndStrip801671B4(u32 run, u32* numStrips, u32* numIndices)
{
	*numIndices += run + 2;
	(*numStrips)++;
	return 0;
}

// A strip window is a triangle when its three indices differ.
#define IS_TRIANGLE_801671B4(a, b, c) ((a) != (b) && (a) != (c) && (b) != (c))

extern "C" {
void fn_801671B4(const u16* indices, u32 count, u32* numStrips, u32* numIndices, s32 join)
{
	u32 run;
	u32 i;

	*numStrips  = 0;
	*numIndices = 0;
	run         = 0;
	for (i = 0; i < count - 2; indices++, i++) {
		if (IS_TRIANGLE_801671B4(indices[0], indices[1], indices[2])) {
			if (run == 0 && (i & 1) && join) {
				run = 2;
			} else {
				run++;
			}
		} else if (run != 0) {
			if (join && i < count - 3) {
				if (IS_TRIANGLE_801671B4(indices[1], indices[2], indices[3])) {
					if (!((i + 1) & 1)) {
						run = EndStrip801671B4(run, numStrips, numIndices);
					} else {
						run++;
					}
				} else {
					run = EndStrip801671B4(run, numStrips, numIndices);
				}
			} else {
				run = EndStrip801671B4(run, numStrips, numIndices);
			}
		}
	}
	if (run != 0) {
		EndStrip801671B4(run, numStrips, numIndices);
	}
}
}
