// Reads a 2D shape from a stream (HYPOTHESIS: Rt2dShapeStreamRead): reads the 8-byte header,
// creates the shape (reference count 1) with a 0xC-byte node array sized for the node count, and
// for each node reads its flags; nodes with flag 0x4 read their value, then a path (chunk 0x1A1,
// fn_80171620/fn_80171978/fn_80171D84) and a brush (chunk 0x1A2, fn_80169E28/fn_8016A930), other
// nodes get neither. Finally the shape's bounds are computed (fn_80174B0C). Returns the shape, or
// null when a read fails. Names are inferred from this function only.
#include "game/rw_engine.h"

#define RT2D_CHUNK_PATH    0x1A1
#define RT2D_CHUNK_BRUSH   0x1A2
#define RT2D_NODE_HAS_PATH 0x4

struct Node80174EFC {
	s32 value;   // 0x0
	void* path;  // 0x4
	void* brush; // 0x8
};

struct Shape80174EFC {
	RwSList* nodes; // 0x0
	s32 refCount;   // 0x4
	void* bounds;   // 0x8
};

struct ShapeHeader80174EFC {
	s32 version;  // 0x0
	s32 numNodes; // 0x4
};

extern "C" {
// HYPOTHESIS: RwStreamRead, RwMemNative32, RwStreamReadInt32, RwStreamFindChunk and the SList
// helpers.
u32 fn_801979AC(void* stream, void* buffer, u32 length);
void* fn_80193270(void* mem, u32 size);
void* fn_80193884(void* stream, void* ints, u32 numBytes);
s32 fn_80192F38(void* stream, u32 type, u32* length, u32* version);
RwSList* fn_80194318(s32 entrySize);
void* fn_80194510(RwSList* sList, s32 count);
void* fn_8019460C(RwSList* sList);
void* fn_80171620(void);
void fn_80171978(void* path);
void fn_80171D84(void* path, void* stream);
void* fn_80169E28(void);
void fn_8016A930(void* brush, void* stream);
void* fn_80174B0C(Shape80174EFC* shape);

Shape80174EFC* fn_80174EFC(void* stream)
{
	ShapeHeader80174EFC header;
	u32 flags;
	u32 size;
	u32 version;
	Shape80174EFC* shape;
	s32 reserve;
	Node80174EFC* node;
	s32 i;

	if (fn_801979AC(stream, &header, sizeof(header)) != sizeof(header)) {
		return 0;
	}
	fn_80193270(&header, sizeof(header));
	reserve         = header.numNodes;
	shape           = (Shape80174EFC*)lbl_8042C9A4->rwmalloc(sizeof(Shape80174EFC));
	shape->refCount = 1;
	shape->nodes    = fn_80194318(sizeof(Node80174EFC));
	shape->bounds   = 0;
	if (reserve != 0) {
		fn_80194510(shape->nodes, reserve);
	}
	node = (Node80174EFC*)fn_8019460C(shape->nodes);
	for (i = 0; i < header.numNodes; i++) {
		if (fn_801979AC(stream, &flags, sizeof(flags)) != sizeof(flags)) {
			return 0;
		}
		fn_80193270(&flags, sizeof(flags));
		if (flags & RT2D_NODE_HAS_PATH) {
			fn_80193884(stream, &node->value, sizeof(s32));
			if (!fn_80192F38(stream, RT2D_CHUNK_PATH, &size, &version)) {
				return 0;
			}
			node->path = fn_80171620();
			fn_80171978(node->path);
			fn_80171D84(node->path, stream);
			if (!fn_80192F38(stream, RT2D_CHUNK_BRUSH, &size, &version)) {
				return 0;
			}
			node->brush = fn_80169E28();
			fn_8016A930(node->brush, stream);
		} else {
			node->path  = 0;
			node->brush = 0;
		}
		node++;
	}
	shape->bounds = fn_80174B0C(shape);
	return shape;
}
}
