// Returns how the chunk chunkName is to be handled according to the user chunk list (HYPOTHESIS:
// libpng png_handle_as_unknown): the list holds 5-byte entries (4-byte name, handling byte) and is
// searched from the end; 0 when the name is not listed or there is no list.
#include "types.h"

// Fields used here (HYPOTHESIS: png_struct layout).
struct Png8017C500 {
	unsigned char pad0[0x190];
	int numChunkList;         // 0x190
	unsigned char* chunkList; // 0x194
};

extern "C" {
s32 memcmp(const void* lhs, const void* rhs, u32 count);

int fn_8017C500(Png8017C500* png, const unsigned char* chunkName)
{
	int i;
	unsigned char* p;
	if ((png == 0 && chunkName == 0) || png->numChunkList <= 0) {
		return 0;
	}
	p = png->chunkList + png->numChunkList * 5 - 5;
	for (i = png->numChunkList; i; i--, p -= 5) {
		if (!memcmp(chunkName, p, 4)) {
			return (int)*(p + 4);
		}
	}
	return 0;
}
}
