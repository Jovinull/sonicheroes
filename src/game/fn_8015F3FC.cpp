// Builds remapped index rows (HYPOTHESIS: a vertex-welding step of the GameCube geometry
// instancing): allocates one block holding numRows row pointers followed by numRows rows of
// numCols u16 indices, then for each row maps every source index through its remap table (an
// entry of -1 keeps the index) and subtracts how many lower indices are remapped, compacting the
// index space. Returns the row pointer table, or null when it cannot be allocated. Names are
// inferred from this function only.
// NonMatching: instruction stream matches; retail keeps the row counter in the saved register of
// the table size (r25), the index in r12, and copies numRows before numCols in the prologue
// (19 words). Declaration orders and reusing the first loop's counter do not reproduce it.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

// Per-row remap table (8-byte records; the table pointer is the first word).
struct Remap8015F3FC {
	s32* table; // 0x0
	u8 pad4[0x4];
};

extern "C" {
u16** fn_8015F3FC(Remap8015F3FC* remaps, u16** source, u32 numRows, u32 numCols)
{
	u32 rowBytes   = numCols * sizeof(u16);
	u32 tableBytes = numRows * sizeof(u16*);
	u16** rows     = (u16**)lbl_8042C9A4->rwmalloc(tableBytes + numRows * rowBytes);
	u32 offset;
	u32 i;

	if (rows == 0) {
		return 0;
	}
	memset(rows, 0, tableBytes);
	offset = tableBytes;
	for (i = 0; i < numRows; i++) {
		rows[i] = (u16*)((u8*)rows + offset);
		offset += rowBytes;
	}
	{
		u16 lower;
		u32 removed;
		s32* table;
		u16* src;
		u16* dst;
		Remap8015F3FC* remap;
		u16** in;
		u16** out;
		u16 index;
		u32 row;
		u32 col;

		remap = remaps;
		in    = source;
		out   = rows;
		for (row = 0; row < numRows; row++) {
			table = remap->table;
			src   = *in;
			dst   = *out;
			for (col = 0; col < numCols; col++) {
				s32 mapped;
				index  = *src;
				mapped = table[index];
				if (mapped != -1) {
					index = mapped;
				}
				removed = 0;
				for (lower = 0; lower < index; lower++) {
					if (table[lower] != -1) {
						removed++;
					}
				}
				src++;
				*dst = index - removed;
				dst++;
			}
			remap++;
			in++;
			out++;
		}
	}
	return rows;
}
}
