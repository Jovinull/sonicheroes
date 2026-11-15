// Opens the raster module (HYPOTHESIS: _rwRasterOpen): records the globals offset, sets up the
// dummy raster (a zero-sized raster that owns no pixels) as the only entry of the raster context
// stack and creates the raster free list. Returns the instance, or null when the free list cannot
// be created. NonMatching: retail stores the offset and then re-reads lbl_8042C9B8 before the
// memset, while this source reuses the offset register, so every later word shifts by one. Forcing
// the re-read with a volatile access leaves only a two-register swap (r0/r3) and is not used. Tried
// compilers 1.2.5n to 2.6.
#include "game/rw_engine.h"

// Raster module globals (HYPOTHESIS: rwRasterGlobals; the 0x28-0x64 layout is used by this
// function and the free list at +0x60 by fn_801A19D4).
struct RwRasterGlobals801A1B84 {
	RwRaster* rasterStack[10];  // 0x0: raster context stack
	s32 rasterSP;               // 0x28: stack pointer
	RwRaster dummyRaster;       // 0x2C
	RwFreeList* rasterFreeList; // 0x60
};

#define RASTER_GLOBALS ((RwRasterGlobals801A1B84*)((u8*)lbl_8042C9A4 + lbl_8042C9B8.globalsOffset))

extern "C" {
void* memset(void* dst, int value, unsigned long n);
// HYPOTHESIS: RwFreeListCreate(entrySize, entriesPerBlock, alignment, numBlocksToPreallocate,
// inPlaceSpace).
RwFreeList* fn_801966CC(
    s32 entrySize, s32 entriesPerBlock, s32 alignment, s32 numBlocks, void* inPlace);

// Raster free list tuning and its in-place header (HYPOTHESIS).
extern s32 lbl_8042BE38;
extern s32 lbl_8042BE3C;
extern u8 lbl_803ED6A8[];

void* fn_801A1B84(void* instance, s32 offset, s32 size)
{
	lbl_8042C9B8.globalsOffset = offset;

	memset(&RASTER_GLOBALS->dummyRaster, 0, sizeof(RwRaster));
	RASTER_GLOBALS->dummyRaster.width    = 0;
	RASTER_GLOBALS->dummyRaster.height   = 0;
	RASTER_GLOBALS->dummyRaster.depth    = 0;
	RASTER_GLOBALS->dummyRaster.cFlags   = RW_RASTER_DONT_ALLOCATE;
	RASTER_GLOBALS->dummyRaster.cpPixels = 0;
	RASTER_GLOBALS->dummyRaster.palette  = 0;
	RASTER_GLOBALS->dummyRaster.cType    = 0;
	RASTER_GLOBALS->rasterSP             = 0;
	RASTER_GLOBALS->rasterStack[0]       = &RASTER_GLOBALS->dummyRaster;

	RASTER_GLOBALS->rasterFreeList
	    = fn_801966CC(lbl_80290628.sizeOfStruct, lbl_8042BE38, 4, lbl_8042BE3C, lbl_803ED6A8);
	if (RASTER_GLOBALS->rasterFreeList == 0) {
		return 0;
	}
	lbl_8042C9B8.numInstances++;
	return instance;
}
}
