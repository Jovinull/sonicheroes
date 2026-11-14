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
	u8* cpPixels;    // 0x14
	RwRGBA* palette; // 0x18
};

#define RW_IMAGE_ALLOCATED       0x1
#define RW_IMAGE_GAMMA_CORRECTED 0x2

// RwRaster::cFlags, privateFlags and cFormat bits (HYPOTHESIS: RenderWare names).
#define RW_RASTER_DONT_ALLOCATE        0x80 // cFlags
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
	rwSTANDARDRASTERCREATE          = 4,  // 0x58
	rwSTANDARDRASTERDESTROY         = 5,  // 0x5C
	rwSTANDARDIMAGEGETRASTER        = 6,  // 0x60
	rwSTANDARDRASTERSETIMAGE        = 7,  // 0x64
	rwSTANDARDTEXTURESETRASTER      = 8,  // 0x68
	rwSTANDARDIMAGEFINDRASTERFORMAT = 9,  // 0x6C
	rwSTANDARDCAMERAENDUPDATE       = 10, // 0x70
	rwSTANDARDRASTERSUBRASTER       = 12, // 0x78
	rwSTANDARDRASTERLOCK            = 15, // 0x84
	rwSTANDARDRASTERUNLOCK          = 16, // 0x88
	rwSTANDARDRASTERSHOWRASTER      = 20, // 0x98
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
// Error code meaning "no error pending"; codes with the top bit set carry no plugin ID.
#define RW_ERROR_NONE ((s32)0x80000000)

// Device system requests (HYPOTHESIS: RwCoreDeviceSystemFn order).
#define RW_DEVICE_SYSTEM_GET_MODE_INFO 6
#define RW_DEVICE_SYSTEM_GET_MODE      10

// Plugin callbacks (HYPOTHESIS: RwPluginObjectConstructor/Destructor/Copy): object, offset and
// size of the plugin's data inside the object.
typedef void* (*RwPluginObjectConstructor)(void* object, s32 offset, s32 size);
typedef void* (*RwPluginObjectDestructor)(void* object, s32 offset, s32 size);
typedef void* (*RwPluginObjectCopy)(void* dst, const void* src, s32 offset, s32 size);

struct RwPluginRegistry;

// One registered plugin (HYPOTHESIS: RwPluginRegEntry); stream and rights callbacks are untyped.
struct RwPluginRegEntry {
	s32 offset;
	s32 size;
	u32 pluginID;
	void* readCB;
	void* writeCB;
	void* getSizeCB;
	void* alwaysCB;
	void* rightsCB;
	RwPluginObjectConstructor constructCB; // 0x20
	RwPluginObjectDestructor destructCB;   // 0x24
	RwPluginObjectCopy copyCB;             // 0x28
	void* errStrCB;
	RwPluginRegEntry* nextRegEntry; // 0x30
	RwPluginRegEntry* prevRegEntry; // 0x34
	RwPluginRegistry* parentRegistry;
};

// Plugin registry of one object type (HYPOTHESIS: RwPluginRegistry, 0x18 bytes).
struct RwPluginRegistry {
	s32 sizeOfStruct;
	s32 origSizeOfStruct;
	s32 maxSizeOfStruct;
	s32 staticAlloc;
	RwPluginRegEntry* firstRegEntry; // 0x10
	RwPluginRegEntry* lastRegEntry;  // 0x14
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
	u8 padC4[0xFC - 0xC4];
	char* (*rwstrncpy)(char* dst, const char* src, u32 size); // 0xFC
	u8 pad100[0x120 - 0x100];
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
// Error module bookkeeping (HYPOTHESIS: errorModule).
extern RwModuleInfo lbl_8042C950;
// HYPOTHESIS: _rwerror (variadic; builds an error code) and RwErrorSet.
s32 fn_8019408C(s32 code, ...);
RwError* fn_80193FE8(RwError* error);
// HYPOTHESIS: _rwPluginRegistryInitObject (null when a constructor fails),
// _rwPluginRegistryDeInitObject and _rwPluginRegistryCopyObject; each returns the registry.
RwPluginRegistry* fn_80198D5C(RwPluginRegistry* registry, void* object);
RwPluginRegistry* fn_80198E04(RwPluginRegistry* registry, void* object);
RwPluginRegistry* fn_80198E70(RwPluginRegistry* registry, void* dst, const void* src);
}

// Image module bookkeeping (HYPOTHESIS: imageModule) and plugin registry (imageTKList); the image
// free list is the first field of the image module globals.
extern "C" {
extern RwModuleInfo lbl_8042C9B0;
extern RwPluginRegistry lbl_80290610;
}
#define RW_IMAGE_FREE_LIST (*(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C9B0.globalsOffset))

// Raster module bookkeeping (HYPOTHESIS: rasterModule) and plugin registry (rasterTKList); the
// raster free list sits at +0x60 in the raster module globals.
extern "C" {
extern RwModuleInfo lbl_8042C9B8;
extern RwPluginRegistry lbl_80290628;
}
#define RW_RASTER_FREE_LIST (*(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C9B8.globalsOffset + 0x60))

// Texture module bookkeeping (HYPOTHESIS: textureModule); its globals start with the list of all
// texture dictionaries and hold the texture free list at +0x8, the dictionary free list at +0xC
// and the current dictionary at +0x10.
extern "C" {
extern RwModuleInfo lbl_8042C9C4;
}
#define RW_TEXTURE_GLOBALS          ((u8*)lbl_8042C9A4 + lbl_8042C9C4.globalsOffset)
#define RW_TEX_DICTIONARY_LIST      (*(RwLinkList*)RW_TEXTURE_GLOBALS)
#define RW_TEXTURE_FREE_LIST        (*(RwFreeList**)(RW_TEXTURE_GLOBALS + 0x8))
#define RW_TEX_DICTIONARY_FREE_LIST (*(RwFreeList**)(RW_TEXTURE_GLOBALS + 0xC))
#define RW_CURRENT_TEX_DICTIONARY   (*(RwTexDictionary**)(RW_TEXTURE_GLOBALS + 0x10))

// Last error of the current engine instance (HYPOTHESIS: RWERRORGLOBAL(errError)).
#define RW_LAST_ERROR (*(RwError*)((u8*)lbl_8042C9A4 + lbl_8042C950.globalsOffset))

#define RW_MATRIX_TYPE_ORTHONORMAL  0x3
#define RW_MATRIX_INTERNAL_IDENTITY 0x20000

// Loads the identity into the matrix and flags it as identity/orthonormal
// (HYPOTHESIS: RwMatrixSetIdentityMacro). one and zero name the calling unit's .sdata2 constants
// 1.0f and 0.0f; each RenderWare unit has its own pair, and the retail code reloads them after the
// matrix stores, so they are declared non-const and read once per assignment chain.
#define RW_MATRIX_SET_IDENTITY(m, one, zero)                                                       \
	do {                                                                                           \
		(m)->right.x = (m)->up.y = (m)->at.z = (one);                                              \
		(m)->right.y = (m)->right.z = (m)->up.x = (zero);                                          \
		(m)->up.z = (m)->at.x = (m)->at.y = (zero);                                                \
		(m)->pos.x = (m)->pos.y = (m)->pos.z = (zero);                                             \
		(m)->flags |= RW_MATRIX_INTERNAL_IDENTITY | RW_MATRIX_TYPE_ORTHONORMAL;                    \
	} while (0)

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
