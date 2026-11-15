// Builds the GX vertex layout of a world into the shared descriptor at lbl_803EC8D8 (HYPOTHESIS:
// the world twin of fn_80164E6C; names inferred): uses the world's vertex format (plugin slot
// lbl_8042C934, or the default from fn_8015C590) and flags, and takes the vertex count of each
// attribute from its own entry of a stream array, indexing it with 8 bits below 255 vertices and
// with 16 bits otherwise. Returns the descriptor.
extern "C" {
#include "dolphin/gx.h"
}
#include "types.h"

#define WORLD_NORMALS  0x10
#define WORLD_PRELIT   0x8
#define WORLD_TEXTURED 0x84

struct VertexFormat8016623C {
	u8 posType;    // 0x0
	u8 normalType; // 0x1
	u8 texType[8]; // 0x2
	u8 colorType;  // 0xA
	u8 padB;       // 0xB
	u8 posFrac;    // 0xC
	u8 hasNbt;     // 0xD
	u8 texFrac[8]; // 0xE
};

struct World8016623C {
	u8 pad0[0x8];
	u32 flags; // 0x8
	u8 padC[0x20 - 0xC];
	s32 numTexCoordSets; // 0x20
};

// One vertex stream per GX attribute, in attribute order (HYPOTHESIS).
struct AttrStream8016623C {
	void* data;      // 0x0 (UNKNOWN)
	u32 numVertices; // 0x4
};

struct VertexDesc8016623C;

extern "C" {
extern s32 lbl_8042C934; // Plugin offset of the vertex format pointer (HYPOTHESIS)
extern VertexDesc8016623C lbl_803EC8D8;

VertexFormat8016623C* fn_8015C590(void);
void fn_80169508(VertexDesc8016623C* desc);
void fn_80169534(VertexDesc8016623C* desc, s32 value);
void fn_8016953C(VertexDesc8016623C* desc, s32 attr, s32 compCount, s32 compType, s32 frac);
void fn_80169820(VertexDesc8016623C* desc, s32 attr, GXAttrType type);
void fn_80169D58(VertexDesc8016623C* desc, u8 numAttributes);

VertexDesc8016623C* fn_8016623C(World8016623C* world, AttrStream8016623C* streams)
{
	VertexFormat8016623C* format;
	s32 numAttributes = 0;
	s32 i;

	format = *(VertexFormat8016623C**)((u8*)world + lbl_8042C934);
	if (format == 0) {
		format = fn_8015C590();
	}

	fn_80169508(&lbl_803EC8D8);
	fn_80169534(&lbl_803EC8D8, 0);
	fn_8016953C(&lbl_803EC8D8, GX_VA_POS, GX_POS_XYZ, format->posType, format->posFrac);
	fn_80169820(&lbl_803EC8D8, GX_VA_POS,
	    streams[numAttributes].numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
	numAttributes++;

	if (world->flags & WORLD_NORMALS) {
		if (format->hasNbt) {
			fn_8016953C(&lbl_803EC8D8, GX_VA_NBT, GX_NRM_NBT, format->normalType, 0);
			fn_80169820(&lbl_803EC8D8, GX_VA_NBT,
			    streams[numAttributes].numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
		} else {
			fn_8016953C(&lbl_803EC8D8, GX_VA_NRM, GX_NRM_XYZ, format->normalType, 0);
			fn_80169820(&lbl_803EC8D8, GX_VA_NRM,
			    streams[numAttributes].numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
		}
		numAttributes++;
	}

	if (world->flags & WORLD_PRELIT) {
		fn_8016953C(&lbl_803EC8D8, GX_VA_CLR0,
		    format->colorType > GX_RGBX8 ? GX_CLR_RGBA : GX_CLR_RGB, format->colorType, 0);
		fn_80169820(&lbl_803EC8D8, GX_VA_CLR0,
		    streams[numAttributes].numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
		numAttributes++;
	}

	if (world->flags & WORLD_TEXTURED) {
		for (i = 0; i < world->numTexCoordSets; i++) {
			fn_8016953C(
			    &lbl_803EC8D8, GX_VA_TEX0 + i, GX_TEX_ST, format->texType[i], format->texFrac[i]);
			fn_80169820(&lbl_803EC8D8, GX_VA_TEX0 + i,
			    streams[numAttributes].numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
			numAttributes++;
		}
	}

	fn_80169D58(&lbl_803EC8D8, numAttributes);
	return &lbl_803EC8D8;
}
}
