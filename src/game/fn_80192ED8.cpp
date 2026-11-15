#include "types.h"

extern "C" {
void fn_80193174(u32* buffer, u32 size); /* byte-swaps size/4 words in place */
void* fn_80197B48(void* stream, const void* buffer, u32 size);

void* fn_80192ED8(void* stream, u32 type, u32 size, u32 version, u32 buildNum)
{
	u32 header[3];
	u32 ver = version - 0x30000;

	header[0] = type;
	header[1] = size;
	header[2] = ((ver << 14) & 0xFFC00000) | ((version << 16) & 0x003F0000) | (buildNum & 0xFFFF);
	fn_80193174(header, 0xC);
	return fn_80197B48(stream, header, 0xC);
}
}
