#include "types.h"
#include <dolphin/axfx.h>

#include "__axfx.h"

// axfx.c of the Dolphin SDK AXFX effects library, 0x801E791C to 0x801E7978.
// Boundaries: every function was matched by instruction shape against the
// reference compiled with GC/1.2.5n, in the library's link order.
// Reference: doldecomp/dolsdk2004 src/axfx/axfx.c (public reconstruction of the
// Dolphin SDK); this DOL carries the 2003 release build (no version string of its own; it links between AX and MIX).
// Compiled with GC/1.2.5n like the other SDK units. The original linker
// smart-stripped the functions nothing in the game calls; they are still
// defined here, as in the SDK source, and the linker drops them again.
//
// Built with -fp_contract off, like the rest of AXFX.

static void* __AXFXAllocFunction(u32 bytes)
{
	return OSAlloc(bytes);
}

static void __AXFXFreeFunction(void* p)
{
	OSFree(p);
}

void* (*__AXFXAlloc)(u32) = __AXFXAllocFunction;
void (*__AXFXFree)(void*) = __AXFXFreeFunction;

void AXFXSetHooks(void* (*alloc)(u32), void (*free)(void*))
{

	__AXFXAlloc = alloc;
	__AXFXFree  = free;
}
