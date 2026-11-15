// Sets up the GX vertex descriptors, formats and arrays for an instanced mesh (HYPOTHESIS: the
// GameCube instancing pipeline's vertex setup): positions always, then normals (NBT when the
// format asks for it) for flag 0x10, colours for flag 0x8, and texture coordinates for every
// remaining stream when flag 0x80 or 0x4 is set, each stream giving its descriptor type, data and
// stride. A null format uses the default lbl_803EC6A0. Names are inferred from this function.
// NonMatching: retail does not fold the normal stream index (stream = 1) into constant offsets:
// it shifts it and re-adds the arrays base before each access, five instructions more than this
// source (103 words). C mode folds it the same way.
extern "C" {
#include "dolphin/gx.h"
}
#include "types.h"

// Vertex component formats.
struct VtxFormat8015C3A4 {
	u8 posType;    // 0x0
	u8 normalType; // 0x1
	u8 texType[8]; // 0x2
	u8 colorType;  // 0xA
	u8 padB;
	u8 posFrac;    // 0xC
	u8 useNbt;     // 0xD
	u8 texFrac[8]; // 0xE
};

struct VtxStream8015C3A4 {
	void* data; // 0x0
	u8 pad4;
	u8 stride;   // 0x5
	u8 descType; // 0x6
	u8 pad7;
};

struct VtxArrays8015C3A4 {
	u8 pad0[0x8];
	u32 numStreams;               // 0x8
	VtxStream8015C3A4 streams[1]; // 0xC
};

struct Instance8015C3A4 {
	u8* resEntry; // 0x0: arrays follow the 0x18-byte header
	u8 pad4[0x4];
	u32 flags; // 0x8
};

#define INSTANCE_8015C3A4_NORMALS  0x10
#define INSTANCE_8015C3A4_COLORS   0x8
#define INSTANCE_8015C3A4_TEXTURED 0x84

extern "C" {
extern VtxFormat8015C3A4 lbl_803EC6A0;

void fn_8015C3A4(VtxFormat8015C3A4* format, Instance8015C3A4* instance)
{
	VtxArrays8015C3A4* arrays;
	u32 stream;

	if (format == 0) {
		format = &lbl_803EC6A0;
	}
	arrays = (VtxArrays8015C3A4*)(instance->resEntry + 0x18);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, (GXAttrType)arrays->streams[0].descType);
	GXSetVtxAttrFmt(
	    GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, (GXCompType)format->posType, format->posFrac);
	GXSetArray(GX_VA_POS, arrays->streams[0].data, arrays->streams[0].stride);
	stream = 1;
	if (instance->flags & INSTANCE_8015C3A4_NORMALS) {
		if (format->useNbt) {
			GXSetVtxDesc(GX_VA_NBT, (GXAttrType)arrays->streams[stream].descType);
			GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NBT, GX_NRM_NBT, (GXCompType)format->normalType, 0);
			GXSetArray(GX_VA_NBT, arrays->streams[stream].data, arrays->streams[stream].stride);
			stream = 2;
		} else {
			GXSetVtxDesc(GX_VA_NRM, (GXAttrType)arrays->streams[stream].descType);
			GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, (GXCompType)format->normalType, 0);
			GXSetArray(GX_VA_NRM, arrays->streams[stream].data, arrays->streams[stream].stride);
			stream = 2;
		}
	}
	if (instance->flags & INSTANCE_8015C3A4_COLORS) {
		GXSetVtxDesc(GX_VA_CLR0, (GXAttrType)arrays->streams[stream].descType);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, (GXCompCnt)(format->colorType > 2),
		    (GXCompType)format->colorType, 0);
		GXSetArray(GX_VA_CLR0, arrays->streams[stream].data, arrays->streams[stream].stride);
		stream++;
	}
	if (instance->flags & INSTANCE_8015C3A4_TEXTURED) {
		VtxStream8015C3A4* tex = &arrays->streams[stream];
		s32 attr               = GX_VA_TEX0;
		for (; stream < arrays->numStreams; stream++) {
			GXSetVtxDesc((GXAttr)attr, (GXAttrType)tex->descType);
			GXSetVtxAttrFmt(GX_VTXFMT0, (GXAttr)attr, GX_TEX_ST,
			    (GXCompType)format->texType[attr - GX_VA_TEX0], format->texFrac[attr - GX_VA_TEX0]);
			GXSetArray((GXAttr)attr, tex->data, tex->stride);
			tex++;
			attr++;
		}
	}
}
}
