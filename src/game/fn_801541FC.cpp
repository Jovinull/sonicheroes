// Reads a light from a stream (HYPOTHESIS: RpLightStreamRead): finds the struct chunk, accepts
// library versions 0x31000 to 0x35000 (otherwise error 0x80000004 of plugin 2), reads the 0x18-byte
// light record (zero-filled first, converted to native byte order), creates a light of the
// recorded type and applies the radius, colour and cone (older files store the cone as a tangent,
// converted to -cos), flags the light as chroma-free when its colour is grey, copies the flags and
// reads the light plugin data. Returns the light, or null on failure.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

// Light record as stored in the stream (HYPOTHESIS: _rpLight).
struct RpLightBinary801541FC {
	f32 radius;        // 0x0
	f32 red;           // 0x4
	f32 green;         // 0x8
	f32 blue;          // 0xC
	f32 minusCosAngle; // 0x10: cone tangent before version 0x30300
	u32 typeAndFlags;  // 0x14: type in bits 16-23, flags in the low byte
};

// RpLight fields used here (HYPOTHESIS: RpLight layout).
struct RpLight801541FC {
	RwObject object; // 0x0
	u8 pad8[0x14 - 0x8];
	f32 radius;        // 0x14
	f32 red;           // 0x18
	f32 green;         // 0x1C
	f32 blue;          // 0x20
	f32 alpha;         // 0x24
	f32 minusCosAngle; // 0x28
};

#define RW_ID_STRUCT               1
#define RW_ERROR_BAD_VERSION       ((s32)0x80000004)
#define RW_STREAM_VERSION_OLDEST   0x31000
#define RW_STREAM_VERSION_NEWEST   0x35000
#define RW_STREAM_VERSION_CONE_COS 0x30300
#define RP_LIGHT_PRIVATE_NO_CHROMA 1
#define PLUGIN_ID_WORLD            2

extern "C" {
// Light plugin registry (HYPOTHESIS: lightTKList).
extern RwPluginRegistry lbl_8028D278;
extern f32 lbl_8042F34C; // 1.0f
// HYPOTHESIS: RwStreamFindChunk, RwStreamRead, RwMemNative32, RpLightCreate, RwSqrt and
// _rwPluginRegistryReadDataChunks.
s32 fn_80192F38(void* stream, u32 type, u32* length, u32* version);
u32 fn_801979AC(void* stream, void* buffer, u32 length);
void* fn_80193270(void* mem, u32 size);
RpLight801541FC* fn_80154414(s32 type);
f32 fn_801991F4(f32 value);
const RwPluginRegistry* fn_8019836C(const RwPluginRegistry* registry, void* stream, void* object);

RpLight801541FC* fn_801541FC(void* stream)
{
	u32 size;
	u32 version;
	RpLightBinary801541FC binary;
	RpLight801541FC* light;

	if (!fn_80192F38(stream, RW_ID_STRUCT, &size, &version)) {
		return 0;
	}
	if (version >= RW_STREAM_VERSION_OLDEST && version <= RW_STREAM_VERSION_NEWEST) {
		memset(&binary, 0, sizeof(binary));
		if (size != fn_801979AC(stream, &binary, size)) {
			return 0;
		}
		fn_80193270(&binary, sizeof(binary));

		light = fn_80154414((binary.typeAndFlags >> 16) & 0xFF);
		if (light == 0) {
			return 0;
		}
		light->radius = binary.radius;
		light->red    = binary.red;
		light->green  = binary.green;
		light->blue   = binary.blue;
		if (version < RW_STREAM_VERSION_CONE_COS) {
			light->minusCosAngle = -fn_801991F4(
			    lbl_8042F34C / (lbl_8042F34C + binary.minusCosAngle * binary.minusCosAngle));
		} else {
			light->minusCosAngle = binary.minusCosAngle;
		}
		if (light->red == light->green && light->red == light->blue) {
			light->object.privateFlags = RP_LIGHT_PRIVATE_NO_CHROMA;
		} else {
			light->object.privateFlags = 0;
		}
		light->object.flags = binary.typeAndFlags;
		if (fn_8019836C(&lbl_8028D278, stream, light) == 0) {
			return 0;
		}
		return light;
	} else {
		RwError error;
		error.pluginID  = PLUGIN_ID_WORLD;
		error.errorCode = fn_8019408C(RW_ERROR_BAD_VERSION);
		fn_80193FE8(&error);
		return 0;
	}
}
}
