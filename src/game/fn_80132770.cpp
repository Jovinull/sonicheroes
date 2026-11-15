// Prepares a loaded path file in place (HYPOTHESIS; names inferred): converts the header to native
// byte order ("iiss") and turns its data offset into a pointer; the low nibble of the header flags
// selects the body: type 3 is a path of three arrays (two of 16-byte and one of 8-byte entries),
// type 4 a path of four arrays (two of each). Converts the body, relocates its array offsets
// against the file and converts every array entry.
#include "types.h"

struct Entry16x80132770 {
	s32 v[4];
};

struct Entry8x80132770 {
	s32 v[2];
};

struct Header80132770 {
	u8* body;  // 0x0
	s32 unk4;  // 0x4
	s16 unk8;  // 0x8
	u16 flags; // 0xA
};

// Type 3 body.
struct PathA80132770 {
	Entry16x80132770* points;  // 0x0
	Entry16x80132770* normals; // 0x4
	Entry8x80132770* params;   // 0x8
	u32 count;                 // 0xC
};

// Type 4 body.
struct PathB80132770 {
	Entry16x80132770* points;  // 0x0
	Entry16x80132770* normals; // 0x4
	Entry8x80132770* params;   // 0x8
	Entry8x80132770* extra;    // 0xC
	u32 count;                 // 0x10
	u8 pad14[0x20 - 0x14];
};

void ConvertAnyParameter(u8* data, const char* format, s32 count);

extern "C" void fn_80132770(Header80132770* header)
{
	PathA80132770* pathA;
	PathB80132770* pathB;
	u32 i;

	ConvertAnyParameter((u8*)header, "iiss", 1);
	header->body = header->body + (u32)header;
	pathA        = 0;
	pathB        = 0;
	if ((header->flags & 0xF) == 3) {
		pathA = (PathA80132770*)header->body;
	} else if ((header->flags & 0xF) == 4) {
		pathB = (PathB80132770*)header->body;
	}
	if (pathA != 0) {
		ConvertAnyParameter((u8*)pathA, "iiiiii", 1);
	} else {
		ConvertAnyParameter((u8*)pathB, "iiiiiiii", 1);
	}
	if (pathA != 0) {
		pathA->points  = (Entry16x80132770*)((u32)header + (u32)pathA->points);
		pathA->normals = (Entry16x80132770*)((u32)header + (u32)pathA->normals);
		pathA->params  = (Entry8x80132770*)((u32)header + (u32)pathA->params);
	} else {
		pathB->points  = (Entry16x80132770*)((u32)header + (u32)pathB->points);
		pathB->normals = (Entry16x80132770*)((u32)header + (u32)pathB->normals);
		pathB->params  = (Entry8x80132770*)((u32)header + (u32)pathB->params);
		pathB->extra   = (Entry8x80132770*)((u32)header + (u32)pathB->extra);
	}
	if (pathA != 0) {
		Entry16x80132770* point  = pathA->points;
		Entry16x80132770* normal = pathA->normals;
		Entry8x80132770* param   = pathA->params;

		for (i = 0; i < pathA->count; i++) {
			ConvertAnyParameter((u8*)point, "iiii", 1);
			ConvertAnyParameter((u8*)normal, "iiii", 1);
			ConvertAnyParameter((u8*)param, "ii", 1);
			point++;
			normal++;
			param++;
		}
	} else {
		Entry16x80132770* point  = pathB->points;
		Entry16x80132770* normal = pathB->normals;
		Entry8x80132770* param   = pathB->params;
		Entry8x80132770* extra   = pathB->extra;

		for (i = 0; i < pathB->count; i++) {
			ConvertAnyParameter((u8*)point, "iiii", 1);
			ConvertAnyParameter((u8*)normal, "iiii", 1);
			ConvertAnyParameter((u8*)param, "ii", 1);
			ConvertAnyParameter((u8*)extra, "ii", 1);
			point++;
			normal++;
			param++;
			extra++;
		}
	}
}
