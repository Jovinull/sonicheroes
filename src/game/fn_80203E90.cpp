// Reads the descriptor table of an fn_802038AC object from a stream (HYPOTHESIS): reads the
// descriptor count, creates the 0x3C-byte descriptor array at +0x8 when missing, and for each new
// descriptor (type 2, ids -1) creates its group table (fn_80205354), reads it (fn_80205128), its
// two ids, a chunk header, initialises its key-frame block from the node of its index
// (fn_8020219C with fn_8020472C) and reads its key-frame list (fn_80200934). Finally the first
// descriptor is fetched. Returns the object, or null on failure. Names follow fn_80203A6C.
#include "game/object_802038AC.h"

struct Descriptor80203E90 {
	s32 type;        // 0x0
	u8 cursor[0x1C]; // 0x4: key-frame list read by fn_80200934
	u8 block[0x10];  // 0x20
	void* groups;    // 0x30
	s32 id34;        // 0x34
	s32 id38;        // 0x38
};

struct ChunkHeaderInfo80203E90 {
	u32 type;
	u32 length;
	u32 version;
	u32 buildNum;
	s32 isComplex;
};

extern "C" {
// HYPOTHESIS: RwStreamReadInt32, RwStreamReadChunkHeaderInfo and the SList helpers.
void* fn_80193884(void* stream, void* ints, u32 numBytes);
void* fn_80193968(void* stream, ChunkHeaderInfo80203E90* info);
RwSList* fn_80194318(s32 entrySize);
void* fn_80194510(RwSList* sList, s32 count);
void* fn_8019472C(RwSList* sList, s32 index);
void* fn_80205354(void);
void* fn_80205128(Object802038AC* object, void* groups, void* stream);
void* fn_8020472C(Object802038AC* object, s32 id);
void* fn_8020219C(void* block, void* node);
// The third argument is passed but not used by fn_80200934.
void* fn_80200934(void* list, void* stream, void* block);
}

// Creates the descriptor's group table. Returns the descriptor, or null.
static inline Descriptor80203E90* InitDescriptor80203E90(Descriptor80203E90* descriptor)
{
	descriptor->type = 2;
	descriptor->id34 = -1;
	descriptor->id38 = -1;
	if ((descriptor->groups = fn_80205354()) == 0) {
		return 0;
	}
	return descriptor;
}

extern "C" {
Object802038AC* fn_80203E90(Object802038AC* object, void* stream)
{
	s32 count;

	if (fn_80193884(stream, &count, sizeof(count)) == 0) {
		return 0;
	}
	if (count > 0) {
		s32 i;
		Descriptor80203E90* descriptor;
		if (object->part8 == 0) {
			object->part8 = fn_80194318(sizeof(Descriptor80203E90));
		}
		if (object->part8 != 0) {
			descriptor = (Descriptor80203E90*)fn_80194510((RwSList*)object->part8, count);
			if (descriptor == 0) {
				return 0;
			}
			for (i = 0; i < count; i++) {
				ChunkHeaderInfo80203E90 info;
				void* node;
				if (InitDescriptor80203E90(descriptor) == 0) {
					return 0;
				}
				if (fn_80205128(object, descriptor->groups, stream) == 0) {
					return 0;
				}
				if (fn_80193884(stream, &descriptor->id34, sizeof(s32)) == 0) {
					return 0;
				}
				if (fn_80193884(stream, &descriptor->id38, sizeof(s32)) == 0) {
					return 0;
				}
				if (fn_80193968(stream, &info) == 0) {
					return 0;
				}
				node = fn_8020472C(object, i);
				if (fn_8020219C(descriptor->block, node) == 0) {
					return 0;
				}
				if (fn_80200934(descriptor->cursor, stream, descriptor->block) == 0) {
					return 0;
				}
				descriptor++;
			}
			fn_8019472C((RwSList*)object->part8, 0);
		} else {
			return 0;
		}
	}
	return object;
}
}
