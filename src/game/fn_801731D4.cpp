// Reads an object from a stream: a 0x2C-byte header through fn_801979AC (HYPOTHESIS:
// RwStreamRead), converted in place by fn_80193270, then the chunk with ID 0xD through fn_80192F38
// (HYPOTHESIS: RwStreamFindChunk) and a string into +0xC through fn_80193DA4. The header's words 1-2
// go to +0x0/+0x4 and its eight words 3-10 to +0x8C; the type word at +0x8 becomes 6. Names are
// UNKNOWN. Returns the object, or null when the stream is short or the chunk is missing.
#include "types.h"

struct Block801731D4 {
	unsigned int w[8];
};

struct Header801731D4 {
	unsigned int f0;
	unsigned int f4;
	unsigned int f8;
	Block801731D4 block; // 0xC
};

struct Object801731D4 {
	unsigned int f0;     // 0x0
	unsigned int f4;     // 0x4
	unsigned int type;   // 0x8
	char name[0x80];     // 0xC
	Block801731D4 block; // 0x8C
};

extern "C" {
unsigned int fn_801979AC(void* stream, void* buffer, unsigned int length);
void fn_80193270(void* buffer, unsigned int length);
int fn_80192F38(void* stream, unsigned int type, unsigned int* length, unsigned int* version);
void* fn_80193DA4(void* stream, char* string);

Object801731D4* fn_801731D4(Object801731D4* object, void* stream)
{
	Header801731D4 header;
	if (fn_801979AC(stream, &header, sizeof(header)) != sizeof(header)) {
		return 0;
	}
	fn_80193270(&header, sizeof(header));
	if (fn_80192F38(stream, 0xD, 0, 0) == 0) {
		return 0;
	}
	fn_80193DA4(stream, object->name);
	object->f0    = header.f4;
	object->f4    = header.f8;
	object->block = header.block;
	object->type  = 6;
	return object;
}
}
