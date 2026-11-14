#ifndef GAME_GEOMETRY_PLUGIN_105_H
#define GAME_GEOMETRY_PLUGIN_105_H

#include "types.h"

// Geometry plugin 0x105, registered by fn_8014A90C through fn_80152FDC (HYPOTHESIS:
// RpGeometryRegisterPlugin); its constructor is fn_8014A37C. Field names are inferred from the
// copy (fn_8014A03C) and stream write (fn_8014A0E0) callbacks only.

// 0x14-byte entry; the link points at another entry of the same array.
struct GeometryPlugin105Entry {
	u32 id;                       // 0x0
	s16 a;                        // 0x4
	s16 b;                        // 0x6
	f32 value;                    // 0x8
	u8 padC[0x4];                 // 0xC
	GeometryPlugin105Entry* link; // 0x10
};

// Plugin data inside a geometry.
struct GeometryPlugin105Data {
	s32 count;                       // 0x0
	void* callback;                  // 0x4
	GeometryPlugin105Entry* entries; // 0x8
};

extern "C" {
// Offset of the plugin data inside a geometry.
extern s32 lbl_8042C86C;
}

#define GEOMETRY_PLUGIN_105_DATA(geometry)                                                         \
	((GeometryPlugin105Data*)((u8*)(geometry) + lbl_8042C86C))

#endif
