// Opens the engine (HYPOTHESIS: RenderWare RwEngineOpen). Requires the initialised state and open
// parameters (errors 0x80000001 and 0x80000016) and a device (fn_801AD0A0). Moves the engine
// globals from the static block lbl_803ED4E0 into a heap instance sized by the engine plugin
// registry (lbl_802904E0), registers the device's entry points and memory functions, opens the
// device with the parameters and fetches its standard functions (each device failure raises error
// 0x18 with the request); on success counts the open (lbl_8042C9A0) and marks the engine opened,
// otherwise moves the globals back into the static block and frees the instance. Returns whether
// the engine was opened.
// NonMatching: in C++ the comparison results are bool and get an extra byte mask, while retail
// keeps the plain int of C (a C-mode probe reproduces those words); retail also reloads the
// engine instance pointer right after storing the new block, as other RenderWare open routines do
// (fn_801971B0). One instruction differs, the rest shifts.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

#define RW_ENGINE_STATUS_OPENED    2
#define RW_DEVICE_SYSTEM_OPEN      0
#define RW_DEVICE_SYSTEM_REGISTER  4
#define RW_DEVICE_SYSTEM_STANDARDS 11
#define RW_ERROR_DEVICE            0x18
#define RW_ERROR_ENGINE_STATE      ((s32)0x80000001)
#define RW_ERROR_NULL_POINTER      ((s32)0x80000016)
#define RW_ENGINE_GLOBALS_SIZE     0x158

// Device handle (HYPOTHESIS: RwDevice; only the system entry point is used here).
struct RwDevice8019D86C {
	f32 gammaCorrection;                                           // 0x0
	s32 (*system)(s32 request, void* out, void* inOut, s32 numIn); // 0x4
};

extern "C" {
// Static engine globals used before the engine is opened (HYPOTHESIS: staticGlobals).
extern RwEngineGlobals lbl_803ED4E0;
// Engine plugin registry; its struct size is the engine instance size (HYPOTHESIS: engineTKList).
extern RwPluginRegistry lbl_802904E0;
// Number of engine opens (HYPOTHESIS: engineInstancesOpened).
extern s32 lbl_8042C9A0;
// HYPOTHESIS: _rwDeviceGetHandle.
RwDevice8019D86C* fn_801AD0A0(void);

static inline void RecordError8019D86C(s32 code, s32 arg)
{
	RwError error;
	error.pluginID  = RW_ID_CORE_PLUGIN;
	error.errorCode = fn_8019408C(code, arg);
	fn_80193FE8(&error);
}

s32 fn_8019D86C(void* params)
{
	s32 result;

	if (lbl_8042C9A4 == 0) {
		lbl_8042C9A4 = &lbl_803ED4E0;
	}

	result = lbl_8042C9A4->engineStatus == RW_ENGINE_STATUS_INITED;
	if (result) {
		result = params != 0;
		if (result) {
			RwDevice8019D86C* device = fn_801AD0A0();
			result                   = device != 0;
			if (result) {
				RwEngineGlobals* instance;

				lbl_8042C9A4 = (RwEngineGlobals*)lbl_8042C9A4->rwmalloc(lbl_802904E0.sizeOfStruct);
				instance     = lbl_8042C9A4;
				if (instance != 0) {
					s32 opened;

					memcpy(instance, &lbl_803ED4E0, RW_ENGINE_GLOBALS_SIZE);
					if (!device->system(RW_DEVICE_SYSTEM_REGISTER, (u8*)lbl_8042C9A4 + 0x10,
					        &lbl_8042C9A4->rwmalloc, 0)) {
						RecordError8019D86C(RW_ERROR_DEVICE, RW_DEVICE_SYSTEM_REGISTER);
					}
					opened = device->system(RW_DEVICE_SYSTEM_OPEN, 0, params, 0);
					if (!opened) {
						RecordError8019D86C(RW_ERROR_DEVICE, RW_DEVICE_SYSTEM_OPEN);
					}
					if (opened) {
						if (!device->system(RW_DEVICE_SYSTEM_STANDARDS, lbl_8042C9A4->stdFunc, 0,
						        rwSTANDARDNUMOFSTANDARD)) {
							RecordError8019D86C(RW_ERROR_DEVICE, RW_DEVICE_SYSTEM_STANDARDS);
						}
						lbl_8042C9A0++;
						result = 1;
					} else {
						lbl_8042C9A4 = &lbl_803ED4E0;
						memcpy(lbl_8042C9A4, instance, RW_ENGINE_GLOBALS_SIZE);
						lbl_8042C9A4->rwfree(instance);
						result = 0;
					}
				} else {
					RecordError8019D86C(RW_ERROR_NO_MEMORY, lbl_802904E0.sizeOfStruct);
					result = 0;
				}
				if (result) {
					lbl_8042C9A4->engineStatus = RW_ENGINE_STATUS_OPENED;
				}
			}
		} else {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(RW_ERROR_NULL_POINTER);
			fn_80193FE8(&error);
		}
	} else {
		RwError error;
		error.pluginID  = RW_ID_CORE_PLUGIN;
		error.errorCode = fn_8019408C(RW_ERROR_ENGINE_STATE);
		fn_80193FE8(&error);
	}
	return result;
}
}
