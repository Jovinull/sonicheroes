#include "types.h"
#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "__gx.h"

// GX display-list playback, 0x801F73B0 to 0x801F7420.
// Transcribed from the Apr 2003 Dolphin SDK GXDisplayList.c (release build, no
// debugger). This build links only GXCallDisplayList: the game never records
// display lists, so GXBeginDisplayList / GXEndDisplayList (and their FIFO
// statics DisplayListFifo / OldCPUFifo / __savedGXdata) are unreferenced and
// stripped, leaving the single function below.

void GXCallDisplayList(void* list, u32 nbytes)
{
	CHECK_GXBEGIN(254, "GXCallDisplayList");
	ASSERTMSGLINE(
	    255, !__GXData->inDispList, "GXCallDisplayList: display list already in progress");
	ASSERTMSGLINE(256, (nbytes & 0x1F) == 0, "GXCallDisplayList: nbytes is not 32 byte aligned");
	ASSERTMSGLINE(257, ((u32)list & 0x1F) == 0, "GXCallDisplayList: list is not 32 byte aligned");

	if (__GXData->dirtyState != 0) {
		__GXSetDirtyState();
	}

#if DEBUG
	__GXShadowDispList(list, nbytes);
#endif

	if (*(u32*)&__GXData->vNumNot == 0) { // checks both vNum and bpSent
		__GXSendFlushPrim();
	}

	GX_WRITE_U8(GX_CMD_CALL_DL);
	GX_WRITE_U32(list);
	GX_WRITE_U32(nbytes);
}
