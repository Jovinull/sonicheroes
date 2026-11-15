// Reads a mesh header from a stream (HYPOTHESIS: RenderWare RpMeshRead / the bin-mesh reader, the
// inverse of fn_80155C6C): reads the flags, mesh count and total index count, allocates the header
// with its meshes and, unless the owner (a type 7 or 8 object) holds native data (flag
// 0x01000000), room for 16-bit indices, stamps it with the next mesh serial number of the module
// (lbl_8042C900), then reads each mesh's index count and material index (fn_80154F00) and its
// indices, narrowed from 32 bits in blocks of up to 256. Returns the header, or null when the
// allocation or a read fails.
// NonMatching: the unrolled index copy keeps a copy of the block count for its remainder loop (one
// extra move) and the loop registers differ (74 words). Tried while, for and counter-copy forms of
// the copy loop and an index loop (which unrolls differently).
#include "game/rw_engine.h"

#define RW_OBJECT_TYPE_WORLD    7 // HYPOTHESIS
#define RW_OBJECT_TYPE_GEOMETRY 8 // HYPOTHESIS
#define RW_OBJECT_NATIVE        0x01000000
#define MESH_INDEX_BLOCK        256
#define MESH_ALLOC_STRIDE       0x10 // per-mesh allocation (UNKNOWN: larger than the 12-byte mesh)

struct Mesh80155E70 {
	u16* indices;   // 0x0
	u32 numIndices; // 0x4
	void* material; // 0x8
};

struct MeshHeader80155E70 {
	u32 flags;           // 0x0
	u16 numMeshes;       // 0x4
	u16 serialNum;       // 0x6
	u32 totalIndices;    // 0x8
	u32 firstMeshOffset; // 0xC
};

struct Object80155E70 {
	u8 type; // 0x0
	u8 pad1[0x8 - 0x1];
	u32 flags; // 0x8
};

struct BinMeshHeader80155E70 {
	u32 flags;
	u32 numMeshes;
	u32 totalIndices;
};

struct BinMesh80155E70 {
	u32 numIndices;
	s32 matIndex;
};

extern "C" {
// Mesh module bookkeeping; its globals hold the next mesh serial number (HYPOTHESIS).
extern RwModuleInfo lbl_8042C900;

// HYPOTHESIS: RwStreamReadInt32 and _rpMaterialListGetMaterial.
void* fn_80193884(void* stream, void* ints, u32 numBytes);
void* fn_80154F00(const void* matList, s32 index);

#define MESH_NEXT_SERIAL (*(s16*)((u8*)lbl_8042C9A4 + lbl_8042C900.globalsOffset))

MeshHeader80155E70* fn_80155E70(void* stream, const Object80155E70* object, const void* matList)
{
	BinMeshHeader80155E70 binHeader;
	BinMesh80155E70 binMesh;
	u32 indices[MESH_INDEX_BLOCK];
	MeshHeader80155E70* header;
	u32 size;

	if (fn_80193884(stream, &binHeader, sizeof(binHeader)) == 0) {
		return 0;
	}

	size = binHeader.numMeshes * MESH_ALLOC_STRIDE + sizeof(MeshHeader80155E70);
	if ((object->type == RW_OBJECT_TYPE_GEOMETRY && !(object->flags & RW_OBJECT_NATIVE))
	    || (object->type == RW_OBJECT_TYPE_WORLD && !(object->flags & RW_OBJECT_NATIVE))) {
		size += binHeader.totalIndices * sizeof(u16);
	}

	header = (MeshHeader80155E70*)lbl_8042C9A4->rwmalloc(size);
	if (header != 0) {
		Mesh80155E70* mesh = (Mesh80155E70*)(header + 1);
		u16* dst           = (u16*)(mesh + binHeader.numMeshes);
		u32 type           = object->type;
		u32 numMeshes;

		header->flags           = binHeader.flags;
		header->numMeshes       = binHeader.numMeshes;
		header->serialNum       = MESH_NEXT_SERIAL;
		header->totalIndices    = binHeader.totalIndices;
		header->firstMeshOffset = 0;
		MESH_NEXT_SERIAL++;

		numMeshes = header->numMeshes;
		while (numMeshes--) {
			if (fn_80193884(stream, &binMesh, sizeof(binMesh)) == 0) {
				return 0;
			}
			mesh->numIndices = binMesh.numIndices;
			mesh->material   = fn_80154F00(matList, binMesh.matIndex);
			mesh->indices    = dst;

			if ((type == RW_OBJECT_TYPE_GEOMETRY && !(object->flags & RW_OBJECT_NATIVE))
			    || (type == RW_OBJECT_TYPE_WORLD && !(object->flags & RW_OBJECT_NATIVE))) {
				u32 remaining = mesh->numIndices;
				while (remaining != 0) {
					u32* src  = indices;
					u32 count = MESH_INDEX_BLOCK;
					if (remaining < MESH_INDEX_BLOCK) {
						count = remaining;
					}
					if (fn_80193884(stream, src, count * sizeof(u32)) == 0) {
						return 0;
					}
					remaining -= count;
					while (count--) {
						*dst++ = *src++;
					}
				}
			}
			mesh++;
		}
	}
	return header;
}
}
