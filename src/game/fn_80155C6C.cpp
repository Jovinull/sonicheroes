// Writes a mesh header to a stream (HYPOTHESIS: RenderWare RpMeshWrite / the bin-mesh writer):
// writes the flags, mesh count and total index count as 32-bit words, then for each mesh its index
// count and material index (fn_80155040, clamped to 0 when the material is not in the list) and,
// unless the owner (a type 7 or 8 object) holds native data (flag 0x01000000), its indices
// widened to 32 bits in blocks of up to 256. Returns the stream, or null when a write fails.
#include "types.h"

#define RW_OBJECT_TYPE_WORLD    7 // HYPOTHESIS
#define RW_OBJECT_TYPE_GEOMETRY 8 // HYPOTHESIS
#define RW_OBJECT_NATIVE        0x01000000
#define MESH_INDEX_BLOCK        256

struct Mesh80155C6C {
	u16* indices;   // 0x0
	u32 numIndices; // 0x4
	void* material; // 0x8
};

struct MeshHeader80155C6C {
	u32 flags;           // 0x0
	u16 numMeshes;       // 0x4
	u16 serialNum;       // 0x6
	u32 totalIndices;    // 0x8
	u32 firstMeshOffset; // 0xC
};

struct Object80155C6C {
	u8 type; // 0x0
	u8 pad1[0x8 - 0x1];
	u32 flags; // 0x8
};

struct BinMeshHeader80155C6C {
	u32 flags;
	u32 numMeshes;
	u32 totalIndices;
};

struct BinMesh80155C6C {
	u32 numIndices;
	s32 matIndex;
};

extern "C" {
// HYPOTHESIS: RwStreamWriteInt32 and _rpMaterialListFindMaterialIndex.
void* fn_80193474(void* stream, const void* ints, u32 numBytes);
s32 fn_80155040(const void* matList, const void* material);

void* fn_80155C6C(const MeshHeader80155C6C* header, const Object80155C6C* object, void* stream,
    const void* matList)
{
	u32 count;
	u32 type;
	u32 numMeshes;
	const Mesh80155C6C* mesh;
	u32 remaining;
	const u16* src;
	u32 i;
	BinMeshHeader80155C6C binHeader;
	BinMesh80155C6C binMesh;
	u32 indices[MESH_INDEX_BLOCK];

	binHeader.flags        = header->flags;
	binHeader.numMeshes    = header->numMeshes;
	binHeader.totalIndices = header->totalIndices;
	if (fn_80193474(stream, &binHeader, sizeof(binHeader)) == 0) {
		return 0;
	}

	numMeshes = header->numMeshes;
	mesh      = (const Mesh80155C6C*)(header + 1);
	type      = object->type;
	while (numMeshes--) {
		binMesh.numIndices = mesh->numIndices;
		binMesh.matIndex   = fn_80155040(matList, mesh->material);
		if (binMesh.matIndex < 0) {
			binMesh.matIndex = 0;
		}
		if (fn_80193474(stream, &binMesh, sizeof(binMesh)) == 0) {
			return 0;
		}

		if ((type == RW_OBJECT_TYPE_GEOMETRY && !(object->flags & RW_OBJECT_NATIVE))
		    || (type == RW_OBJECT_TYPE_WORLD && !(object->flags & RW_OBJECT_NATIVE))) {
			u32 remaining  = mesh->numIndices;
			const u16* src = mesh->indices;
			while (remaining != 0) {
				count = MESH_INDEX_BLOCK;
				if (remaining < MESH_INDEX_BLOCK) {
					count = remaining;
				}
				for (i = 0; i < count; i++) {
					indices[i] = *src++;
				}
				if (fn_80193474(stream, indices, count * sizeof(u32)) == 0) {
					return 0;
				}
				remaining -= count;
			}
		}
		mesh++;
	}
	return stream;
}
}
