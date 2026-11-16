// CRI ADX: reads a Sun AU (.snd) header: checks the magic, then returns the header length, data size,
// encoding, sample rate and channel count (big-endian fields read byte by byte and swapped) through the
// output pointers. The data size at +8 is read before the encoding at +0xC, each read followed by its
// swap; reading the encoding first gives a different register assignment (VERIFIED by objdiff).
// Original file: CRI's adx_bau.c (HYPOTHESIS, from the CRI file layout used by other CRI units).
#include "types.h"

#define LE32(p) ((u32)(p)[0] | ((u32)(p)[1] << 8) | ((u32)(p)[2] << 16) | ((u32)(p)[3] << 24))
#define BSWAP32(x)                                                                                 \
	(((x) >> 24) | (((x) >> 8) & 0x0000FF00) | (((x) << 8) & 0x00FF0000) | ((x) << 24))

extern "C" {

u8* AU_GetInfo(u8* p, s32 size, s32* rate, s32* chan, s32* block, s32* nsmp, s32* fmt)
{
	u32 magic;
	u32 hdr;
	u32 enc;
	u32 dlen;

	magic = LE32(p);
	if (magic != 0x0064732E && magic != 0x646E732E) {
		return 0;
	}
	hdr = LE32(p + 4);
	hdr = BSWAP32(hdr);
	if ((s32)hdr > size) {
		return 0;
	}
	dlen = LE32(p + 8);
	dlen = BSWAP32(dlen);
	enc  = LE32(p + 0xC);
	enc  = BSWAP32(enc);
	switch (enc) {
		case 1:
			*fmt   = 2;
			*block = 8;
			break;
		case 2:
			*fmt   = 1;
			*block = 8;
			break;
		case 3:
			*fmt   = 0;
			*block = 0x10;
			break;
		default:
			return 0;
	}
	*rate = (s32)LE32(p + 0x10);
	*rate = (s32)(((u32)*rate >> 24) | (((u32)*rate >> 8) & 0x0000FF00)
	    | (((u32)*rate << 8) & 0x00FF0000) | ((u32)*rate << 24));
	*chan = (s32)LE32(p + 0x14);
	*chan = (s32)(((u32)*chan >> 24) | (((u32)*chan >> 8) & 0x0000FF00)
	    | (((u32)*chan << 8) & 0x00FF0000) | ((u32)*chan << 24));
	if (*fmt == 2) {
		*nsmp = (s32)dlen / *chan;
	} else if (*fmt == 1) {
		*nsmp = (s32)dlen / *chan;
	} else if (*fmt == 0) {
		*nsmp = ((s32)dlen / 2) / *chan;
	} else {
		*nsmp = 0x7FFF0000;
	}
	return p + hdr;
}
}
