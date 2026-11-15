// Builds the GX vertex layout of a geometry into the shared descriptor at lbl_803EC8B8
// (HYPOTHESIS: a GameCube instancing helper; names inferred): uses the geometry's vertex format
// (plugin slot lbl_8042C930, or the default from fn_8015C590), always adds the position, then a
// normal or NBT set (flag 0x10), the colour (flag 0x8, RGBA when the colour type is above RGBX8)
// and one texture coordinate per set (flags 0x84), each indexed with 8 bits under 255 vertices
// and 16 bits otherwise, and stores the attribute count. Returns the descriptor.
extern "C" {
#include "dolphin/gx.h"
}
#include "types.h"

#define GEOMETRY_NORMALS  0x10
#define GEOMETRY_PRELIT   0x8
#define GEOMETRY_TEXTURED 0x84

struct VertexFormat801657CC {
	u8 posType;    // 0x0
	u8 normalType; // 0x1
	u8 texType[8]; // 0x2
	u8 colorType;  // 0xA
	u8 padB;       // 0xB
	u8 posFrac;    // 0xC
	u8 hasNbt;     // 0xD
	u8 texFrac[8]; // 0xE
};

struct Geometry801657CC {
	u8 pad0[0x8];
	u32 flags; // 0x8
	u8 padC[0x14 - 0xC];
	u32 numVertices; // 0x14
	u8 pad18[0x1C - 0x18];
	s32 numTexCoordSets; // 0x1C
};

struct VertexDesc801657CC;

extern "C" {
extern s32 lbl_8042C930; // Plugin offset of the vertex format pointer (HYPOTHESIS)
extern VertexDesc801657CC lbl_803EC8B8;

VertexFormat801657CC* fn_8015C590(void);
void fn_80169508(VertexDesc801657CC* desc);
void fn_80169534(VertexDesc801657CC* desc, s32 value);
void fn_8016953C(VertexDesc801657CC* desc, s32 attr, s32 compCount, s32 compType, s32 frac);
void fn_80169820(VertexDesc801657CC* desc, s32 attr, GXAttrType type);
void fn_80169D58(VertexDesc801657CC* desc, u8 numAttributes);

VertexDesc801657CC* fn_801657CC(Geometry801657CC* geometry)
{
	VertexFormat801657CC* format;
	u32 numVertices = geometry->numVertices;
	s32 numAttributes;
	s32 i;

	format = *(VertexFormat801657CC**)((u8*)geometry + lbl_8042C930);
	if (format == 0) {
		format = fn_8015C590();
	}

	fn_80169508(&lbl_803EC8B8);
	fn_80169534(&lbl_803EC8B8, 0);
	fn_8016953C(&lbl_803EC8B8, GX_VA_POS, GX_POS_XYZ, format->posType, format->posFrac);
	fn_80169820(&lbl_803EC8B8, GX_VA_POS, numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
	numAttributes = 1;

	if (geometry->flags & GEOMETRY_NORMALS) {
		if (format->hasNbt) {
			fn_8016953C(&lbl_803EC8B8, GX_VA_NBT, GX_NRM_NBT, format->normalType, 0);
			fn_80169820(&lbl_803EC8B8, GX_VA_NBT, numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
		} else {
			fn_8016953C(&lbl_803EC8B8, GX_VA_NRM, GX_NRM_XYZ, format->normalType, 0);
			fn_80169820(&lbl_803EC8B8, GX_VA_NRM, numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
		}
		numAttributes = 2;
	}

	if (geometry->flags & GEOMETRY_PRELIT) {
		fn_8016953C(&lbl_803EC8B8, GX_VA_CLR0,
		    format->colorType > GX_RGBX8 ? GX_CLR_RGBA : GX_CLR_RGB, format->colorType, 0);
		fn_80169820(&lbl_803EC8B8, GX_VA_CLR0, numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
		numAttributes++;
	}

	if (geometry->flags & GEOMETRY_TEXTURED) {
		for (i = 0; i < geometry->numTexCoordSets; i++) {
			fn_8016953C(
			    &lbl_803EC8B8, GX_VA_TEX0 + i, GX_TEX_ST, format->texType[i], format->texFrac[i]);
			fn_80169820(
			    &lbl_803EC8B8, GX_VA_TEX0 + i, numVertices >= 0xFF ? GX_INDEX16 : GX_INDEX8);
			numAttributes++;
		}
	}

	fn_80169D58(&lbl_803EC8B8, numAttributes);
	return &lbl_803EC8B8;
}
}
