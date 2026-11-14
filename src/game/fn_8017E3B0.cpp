// Frees a read structure and its info structures (HYPOTHESIS: libpng png_destroy_read_struct):
// releases the reader state (fn_8017E4B4, HYPOTHESIS: png_read_destroy), the data of each info
// structure (fn_8017C024, HYPOTHESIS: png_free_data with mask 0x4000 and all entries), then
// frees the info structures and the read structure with the structure's free function and memory
// pointer (fn_8017CD58, HYPOTHESIS: png_destroy_struct_2), clearing the caller's pointers. Null
// handles are skipped.
#include "types.h"

// Fields used here (HYPOTHESIS: png_struct layout).
struct PngStruct8017E3B0 {
	u8 pad0[0x1A8];
	void* memPtr; // 0x1A8
	u8 pad1AC[0x4];
	void* freeFn; // 0x1B0
};

#define PNG_FREE_ALL 0x4000

extern "C" {
void fn_8017E4B4(PngStruct8017E3B0* png, void* info, void* endInfo);
void fn_8017C024(PngStruct8017E3B0* png, void* info, u32 mask, s32 num);
void fn_8017CD58(void* structure, void* freeFn, void* memPtr);

void fn_8017E3B0(PngStruct8017E3B0** pngPtr, void** infoPtr, void** endInfoPtr)
{
	PngStruct8017E3B0* png = 0;
	void* info             = 0;
	void* endInfo          = 0;
	void* freeFn;
	void* memPtr;

	if (pngPtr) {
		png = *pngPtr;
	}
	if (infoPtr) {
		info = *infoPtr;
	}
	if (endInfoPtr) {
		endInfo = *endInfoPtr;
	}

	freeFn = png->freeFn;
	memPtr = png->memPtr;
	fn_8017E4B4(png, info, endInfo);

	if (info) {
		fn_8017C024(png, info, PNG_FREE_ALL, -1);
		fn_8017CD58(info, freeFn, memPtr);
		*infoPtr = 0;
	}
	if (endInfo) {
		fn_8017C024(png, endInfo, PNG_FREE_ALL, -1);
		fn_8017CD58(endInfo, freeFn, memPtr);
		*endInfoPtr = 0;
	}
	if (png) {
		fn_8017CD58(png, freeFn, memPtr);
		*pngPtr = 0;
	}
}
}
