// Builds the GX vertex layout of a geometry into the shared descriptor at lbl_803EC8B8, like
// fn_801657CC, but takes the vertex count of each attribute from its own entry of a stream array
// (HYPOTHESIS: per-attribute vertex streams of a split or skinned geometry; names inferred): each
// attribute is indexed with 8 bits when its stream holds fewer than 255 vertices and with 16 bits
// otherwise. Returns the descriptor.
extern "C" {
#include "dolphin/gx.h"
}
#include "types.h"

#define GEOMETRY_NORMALS  0x10
#define GEOMETRY_PRELIT   0x8
#define GEOMETRY_TEXTURED 0x84

struct VertexFormat80164E6C {
	u8 posType;    // 0x0
	u8 normalType; // 0x1
	u8 texType[8]; // 0x2
	u8 colorType;  // 0xA
	u8 padB;       // 0xB
	u8 posFrac;    // 0xC
	u8 hasNbt;     // 0xD
	u8 texFrac[8]; // 0xE
};

struct Geometry80164E6C {
	u8 pad0[0x8];
	u32 flags; // 0x8
	u8 padC[0x14 - 0xC];
	u32 numVertices; // 0x14
	u8 pad18[0x1C - 0x18];
	s32 numTexCoordSets; // 0x1C
};

// One vertex stream per GX attribute, in attribute order (HYPOTHESIS).
struct AttrStream80164E6C {
	void* data;      // 0x0 (UNKNOWN)
	u32 numVertices; // 0x4
};

struct VertexDesc80164E6C;

extern "C" {
extern s32 lbl_8042C930; // Plugin offset of the vertex format pointer (HYPOTHESIS)
extern VertexDesc80164E6C lbl_803EC8B8;

VertexFormat80164E6C* fn_8015C590(void);
void fn_80169508(VertexDesc80164E6C* desc);
void fn_80169534(VertexDesc80164E6C* desc, s32 value);
void fn_8016953C(VertexDesc80164E6C* desc, s32 attr, s32 compCount, s32 compType, s32 frac);
void fn_80169820(VertexDesc80164E6C* desc, s32 attr, GXAttrType type);
void fn_80169D58(VertexDesc80164E6C* desc, u8 numAttributes);

VertexDesc80164E6C* fn_80164E6C(Geometry80164E6C* geometry, AttrStream80164E6C* streams)
{
	VertexFormat80164E6C* format;
	s32 numAttributes = 0;
	s32 i;

	format = *(VertexFormat80164E6C**)((u8*)geometry + lbl_8042C930);
	if (format == 0) {
		format = fn_8015C590();
	}

	fn_80169508(&lbl_803EC8B8);
	fn_80169534(&lbl_803EC8B8, 0);
	fn_8016953C(&lbl_803EC8B8, GX_VA_POS, GX_POS_XYZ, format->posType, format->posFrac);
	fn_80169820(&lbl_803EC8B8, GX_VA_POS,
	    streams[numAttributes].numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
	numAttributes++;

	if (geometry->flags & GEOMETRY_NORMALS) {
		if (format->hasNbt) {
			fn_8016953C(&lbl_803EC8B8, GX_VA_NBT, GX_NRM_NBT, format->normalType, 0);
			fn_80169820(&lbl_803EC8B8, GX_VA_NBT,
			    streams[numAttributes].numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
		} else {
			fn_8016953C(&lbl_803EC8B8, GX_VA_NRM, GX_NRM_XYZ, format->normalType, 0);
			fn_80169820(&lbl_803EC8B8, GX_VA_NRM,
			    streams[numAttributes].numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
		}
		numAttributes++;
	}

	if (geometry->flags & GEOMETRY_PRELIT) {
		fn_8016953C(&lbl_803EC8B8, GX_VA_CLR0,
		    format->colorType > GX_RGBX8 ? GX_CLR_RGBA : GX_CLR_RGB, format->colorType, 0);
		fn_80169820(&lbl_803EC8B8, GX_VA_CLR0,
		    streams[numAttributes].numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
		numAttributes++;
	}

	if (geometry->flags & GEOMETRY_TEXTURED) {
		for (i = 0; i < geometry->numTexCoordSets; i++) {
			fn_8016953C(
			    &lbl_803EC8B8, GX_VA_TEX0 + i, GX_TEX_ST, format->texType[i], format->texFrac[i]);
			fn_80169820(&lbl_803EC8B8, GX_VA_TEX0 + i,
			    streams[numAttributes].numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
			numAttributes++;
		}
	}

	fn_80169D58(&lbl_803EC8B8, numAttributes);
	return &lbl_803EC8B8;
}
}
