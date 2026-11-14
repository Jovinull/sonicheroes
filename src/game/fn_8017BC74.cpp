// Updates a CRC-32 with len bytes of buf using the 256-entry table lbl_8023C3F8 (HYPOTHESIS: zlib
// crc32, eight bytes per step). A null buffer returns 0.
// Built with GC/2.0 (configure.py): GC/1.3.2 forms the 0xFFFFFFFF xors with xoris/xori pairs
// instead of a loaded -1 (6 words differ). HYPOTHESIS: this zlib copy is part of the RenderWare
// toolkit and was built with GC/2.x like the other RenderWare units (see fn_8019D0CC).
#include "types.h"

extern "C" {
// HYPOTHESIS: zlib crc_table (.rodata of the original unit).
extern const unsigned long lbl_8023C3F8[256];
}

#define DO1(buf) crc = lbl_8023C3F8[((int)crc ^ (*buf++)) & 0xFF] ^ (crc >> 8);
#define DO2(buf)                                                                                   \
	DO1(buf);                                                                                      \
	DO1(buf);
#define DO4(buf)                                                                                   \
	DO2(buf);                                                                                      \
	DO2(buf);
#define DO8(buf)                                                                                   \
	DO4(buf);                                                                                      \
	DO4(buf);

extern "C" {
unsigned long fn_8017BC74(unsigned long crc, const unsigned char* buf, unsigned int len)
{
	if (buf == 0) {
		return 0L;
	}
	crc = crc ^ 0xFFFFFFFFL;
	while (len >= 8) {
		DO8(buf);
		len -= 8;
	}
	if (len) {
		do {
			DO1(buf);
		} while (--len);
	}
	return crc ^ 0xFFFFFFFFL;
}
}
