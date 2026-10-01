#include "types.h"
#include <dolphin/ax.h>

#include "__ax.h"

// AX.c of the Dolphin SDK AX audio library, 0x801E1EA4 to 0x801E1F48.
// Boundaries: every function was matched by instruction shape against the
// reference compiled with GC/1.2.5n, in the library's link order.
// Reference: doldecomp/dolsdk2004 src/ax/AX.c (public reconstruction of the
// Dolphin SDK); this DOL carries the 2003 release build "<< Dolphin SDK - AX ... Jul 29 2003 16:15:36 >>".
// Compiled with GC/1.2.5n like the other SDK units. The original linker
// smart-stripped the functions nothing in the game calls; they are still
// defined here, as in the SDK source, and the linker drops them again.
//
// The AX library's two data-only units are deliberately not reproduced:
// DSPCode.c (axDspSlave, the 0x1EC0-byte DSP microcode at 0x80294D00, and
// axDspSlaveLength in .sdata) is original Nintendo DSP code, and AXComp.c
// (__AXCompressorTable, 0x1A40 bytes at 0x802932C0) is a large SDK table.
// Both stay in the extracted, unowned splits and link from there; AXOut.c
// and AXCL.c refer to them by name.

const char* __AXVersion = "<< Dolphin SDK - AX\trelease build: Jul 29 2003 16:15:36 (0x2301) >>";

void AXInit(void)
{
	AXInitEx(0);
}

void AXInitEx(u32 outputBufferMode)
{
#ifdef DEBUG
	OSReport("Initializing AX\n");
#endif
	OSRegisterVersion(__AXVersion);

	__AXAllocInit();
	__AXVPBInit();
	__AXSPBInit();
	__AXAuxInit();
	__AXClInit();
	__AXOutInit(outputBufferMode);
}

void AXQuit(void)
{
#ifdef DEBUG
	OSReport("Shutting down AX\n");
#endif
	__AXAllocQuit();
	__AXVPBQuit();
	__AXSPBQuit();
	__AXAuxQuit();
	__AXClQuit();
	__AXOutQuit();
}
