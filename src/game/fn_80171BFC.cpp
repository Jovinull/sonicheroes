// Reads the body of a 2D path from a stream (HYPOTHESIS: the Rt2d path stream reader): resets the
// path (fn_80171278), makes it its own parent, takes the segment count, closed and flat flags and
// inset from the header, reads the 0x18-byte segments (converted to native byte order), then,
// when the header says a sub-path follows (flag 0x4), reads it from its 0x1A1 chunk (fn_80171E0C)
// and makes this path the parent of the whole sub-path chain. Returns the path, or null on failure.
// The empty per-segment loop is kept as retail compiles it.
#include "game/rw_engine.h"

#define RT2D_CHUNK_PATH        0x1A1
#define RT2D_PATH_CLOSED       0x1
#define RT2D_PATH_FLAT         0x2
#define RT2D_PATH_HAS_SUB_PATH 0x4
#define RT2D_PATH_SEGMENT_SIZE 0x18

struct PathHeader80171BFC {
	u8 pad0[0x4];
	s32 numSegments; // 0x4
	u32 flags;       // 0x8
	f32 inset;       // 0xC
};

struct Path80171BFC {
	void* segments;       // 0x0
	s32 numSegments;      // 0x4
	s32 closed;           // 0x8
	s32 flat;             // 0xC
	f32 inset;            // 0x10
	Path80171BFC* next;   // 0x14
	Path80171BFC* parent; // 0x18
};

extern "C" {
void fn_80171278(Path80171BFC* path);
Path80171BFC* fn_80171E0C(void* stream);
// HYPOTHESIS: RwStreamRead, the float byte-swap (RwMemFloat32ToReal-style) and RwStreamFindChunk.
u32 fn_801979AC(void* stream, void* buffer, u32 length);
void fn_80193174(void* buffer, u32 size);
s32 fn_80192F38(void* stream, u32 type, u32* length, u32* version);

Path80171BFC* fn_80171BFC(Path80171BFC* path, PathHeader80171BFC* header, void* stream)
{
	void* segments;
	s32 i;

	fn_80171278(path);
	path->parent      = path;
	path->numSegments = header->numSegments;
	path->closed      = header->flags & RT2D_PATH_CLOSED;
	path->flat        = (header->flags & RT2D_PATH_FLAT) >> 1;
	path->inset       = header->inset;

	segments = lbl_8042C9A4->rwmalloc(path->numSegments * RT2D_PATH_SEGMENT_SIZE);
	if (segments == 0) {
		return 0;
	}
	if (path->numSegments != 0) {
		if (path->numSegments * RT2D_PATH_SEGMENT_SIZE
		    != fn_801979AC(stream, segments, path->numSegments * RT2D_PATH_SEGMENT_SIZE)) {
			return 0;
		}
		fn_80193174(segments, path->numSegments * RT2D_PATH_SEGMENT_SIZE);
	}
	for (i = 0; i < header->numSegments; i++) {
	}
	path->segments = segments;

	if (header->flags & RT2D_PATH_HAS_SUB_PATH) {
		if (fn_80192F38(stream, RT2D_CHUNK_PATH, 0, 0)) {
			path->next = fn_80171E0C(stream);
		} else {
			return 0;
		}
	}
	{
		Path80171BFC* sub;
		for (sub = path->next; sub != 0; sub = sub->next) {
			sub->parent = path;
		}
	}
	return path;
}
}
