#ifndef GAME_RW_ENGINE_H
#define GAME_RW_ENGINE_H

#include "game/object.h"

// RenderWare engine globals as seen by the core units around 0x80190000-0x801A4000.
// Field roles are HYPOTHESIS (RenderWare RwGlobals shape) backed by the GameCube accesses noted
// below; symbols stay fn_ addresses.

struct RwFreeList;

// Driver standard function (HYPOTHESIS: RwStandardFunc): returns nonzero on success.
typedef s32 (*RwStandardFunc)(void* out, void* inOut, s32 numIn);

// Indices into RwEngineGlobals::stdFunc (HYPOTHESIS: RwStandardFunc enumeration order; the raster
// lock entries are corroborated by their callers' arguments and flag updates).
enum RwStandardFuncIndex {
	rwSTANDARDRASTERLOCK          = 15, // 0x84
	rwSTANDARDRASTERUNLOCK        = 16, // 0x88
	rwSTANDARDRASTERLOCKPALETTE   = 23, // 0xA4
	rwSTANDARDRASTERUNLOCKPALETTE = 24, // 0xA8
	rwSTANDARDNUMOFSTANDARD       = 29
};

// Module bookkeeping (HYPOTHESIS: RwModuleInfo): offset of a module's globals inside the engine
// block and the number of open engine instances.
struct RwModuleInfo {
	s32 globalsOffset;
	s32 numInstances;
};

// Engine globals block (HYPOTHESIS: RwGlobals behind RwEngineInstance). Modules keep their own
// globals at a registered offset inside it.
struct RwEngineGlobals {
	u8 pad0[0x30];
	// Device 2D immediate-mode entry points.
	s32 (*im2DRenderPrimitive)(s32 primType, void* vertices, s32 numVertices); // 0x30
	s32 (*im2DRenderIndexedPrimitive)(
	    s32 primType, void* vertices, s32 numVertices, u16* indices, s32 numIndices); // 0x34
	u8 pad38[0x48 - 0x38];
	RwStandardFunc stdFunc[rwSTANDARDNUMOFSTANDARD]; // 0x48
	RwLinkList dirtyFrameList;                       // 0xBC
	u8 padC4[0x120 - 0xC4];
	u32 (*rwstrlen)(const char* string); // 0x120
	u8 pad124[0x134 - 0x124];
	void* (*rwmalloc)(u32 size); // 0x134
	void (*rwfree)(void* block); // 0x138
	u8 pad13C[0x144 - 0x13C];
	void* (*freeListAlloc)(RwFreeList* freeList);            // 0x144
	void (*freeListFree)(RwFreeList* freeList, void* entry); // 0x148
};

extern "C" {
extern RwEngineGlobals* lbl_8042C9A4;
}

#endif
