#ifndef GAME_RW_ENGINE_H
#define GAME_RW_ENGINE_H

#include "game/object.h"

// RenderWare engine globals as seen by the core units around 0x80190000-0x801A4000.
// Field roles are HYPOTHESIS (RenderWare RwGlobals shape) backed by the GameCube accesses noted
// below; symbols stay fn_ addresses.

struct RwFreeList;
struct RwCamera;

// Image header (HYPOTHESIS: RwImage); later fields are not used by the reconstructed units yet.
struct RwImage {
	s32 flags; // RW_IMAGE_* bits
	s32 width;
	s32 height;
	s32 depth;
	s32 stride;
	u8* cpPixels;  // 0x14
	void* palette; // 0x18
};

#define RW_IMAGE_ALLOCATED       0x1
#define RW_IMAGE_GAMMA_CORRECTED 0x2

// RwRaster::privateFlags and cFormat bits (HYPOTHESIS: RenderWare names).
#define RW_RASTER_GAMMA_CORRECTED      0x01
#define RW_RASTER_PALETTE_LOCKED_READ  0x08
#define RW_RASTER_PALETTE_LOCKED_WRITE 0x10
#define RW_RASTER_FORMAT_MIPMAP        0x8000 // in the (cFormat << 8) raster format

// Driver standard function (HYPOTHESIS: RwStandardFunc): returns nonzero on success.
typedef s32 (*RwStandardFunc)(void* out, void* inOut, s32 numIn);

// Indices into RwEngineGlobals::stdFunc (HYPOTHESIS: RwStandardFunc enumeration order; each entry
// is corroborated by its caller's arguments and flag updates, and the 29-entry table ends exactly
// at the dirty-frame list).
enum RwStandardFuncIndex {
	rwSTANDARDCAMERABEGINUPDATE     = 1,  // 0x4C
	rwSTANDARDRGBTOPIXEL            = 2,  // 0x50
	rwSTANDARDPIXELTORGB            = 3,  // 0x54
	rwSTANDARDIMAGEGETRASTER        = 6,  // 0x60
	rwSTANDARDRASTERSETIMAGE        = 7,  // 0x64
	rwSTANDARDTEXTURESETRASTER      = 8,  // 0x68
	rwSTANDARDIMAGEFINDRASTERFORMAT = 9,  // 0x6C
	rwSTANDARDCAMERAENDUPDATE       = 10, // 0x70
	rwSTANDARDRASTERLOCK            = 15, // 0x84
	rwSTANDARDRASTERUNLOCK          = 16, // 0x88
	rwSTANDARDCAMERACLEAR           = 21, // 0x9C
	rwSTANDARDRASTERLOCKPALETTE     = 23, // 0xA4
	rwSTANDARDRASTERUNLOCKPALETTE   = 24, // 0xA8
	rwSTANDARDRASTERGETMIPLEVELS    = 28, // 0xB8
	rwSTANDARDNUMOFSTANDARD         = 29
};

// Error record (HYPOTHESIS: RwError) and the plugin ID used by core errors.
struct RwError {
	s32 pluginID;
	s32 errorCode;
};

#define RW_ID_CORE_PLUGIN 1

// Device system requests (HYPOTHESIS: RwCoreDeviceSystemFn order).
#define RW_DEVICE_SYSTEM_GET_MODE_INFO 6
#define RW_DEVICE_SYSTEM_GET_MODE      10

// Module bookkeeping (HYPOTHESIS: RwModuleInfo): offset of a module's globals inside the engine
// block and the number of open engine instances.
struct RwModuleInfo {
	s32 globalsOffset;
	s32 numInstances;
};

// Engine globals block (HYPOTHESIS: RwGlobals behind RwEngineInstance). Modules keep their own
// globals at a registered offset inside it.
struct RwEngineGlobals {
	RwCamera* curCamera; // 0x0, camera between begin/end update
	u8 pad4[0x14 - 0x4];
	// Device system entry point (HYPOTHESIS: RwDevice::fpSystem).
	s32 (*system)(s32 request, void* out, void* inOut, s32 numIn); // 0x14
	u8 pad18[0x20 - 0x18];
	// Device render-state entry points.
	s32 (*renderStateSet)(s32 state, void* value); // 0x20
	s32 (*renderStateGet)(s32 state, void* value); // 0x24
	u8 pad28[0x30 - 0x28];
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
// HYPOTHESIS: _rwerror (variadic; builds an error code) and RwErrorSet.
s32 fn_8019408C(s32 code, ...);
RwError* fn_80193FE8(RwError* error);
}

// Forwards a request to the device system entry point and records core error 0x18 for the request
// when it fails (HYPOTHESIS: _rwDeviceSystemRequest, inlined). Returns the entry point's status.
static inline s32 RwDeviceSystemRequest(s32 request, void* out, void* inOut, s32 numIn)
{
	s32 ok = lbl_8042C9A4->system(request, out, inOut, numIn);
	if (!ok) {
		RwError error;
		error.pluginID  = RW_ID_CORE_PLUGIN;
		error.errorCode = fn_8019408C(0x18, request);
		fn_80193FE8(&error);
	}
	return ok;
}

#endif
