#include "types.h"

#define AIFF_U16(p)    ((p)[0] | ((p)[1] << 8))
#define AIFF_LE16(p)   (((p)[1] << 8) | (p)[0])
#define AIFF_U32(p)    ((unsigned int)((p)[0] | ((p)[1] << 8) | ((p)[2] << 16) | ((p)[3] << 24)))
#define AIFF_SWAP32(x) (((x) >> 24) | (((x) >> 8) & 0xFF00) | (((x) << 8) & 0xFF0000) | ((x) << 24))
#define AIFF_SWAP16(x) ((((x) >> 8) & 0xFF) | (((x) & 0xFF) << 8))

static inline unsigned int AIFF_GetU32f(unsigned char* p)
{
	return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
}
static inline unsigned int AIFF_Swap32f(unsigned int x)
{
	return (x >> 24) | ((x >> 8) & 0xFF00) | ((x << 8) & 0xFF0000) | (x << 24);
}

extern "C" {

unsigned char* AIFF_GetInfo(unsigned char* p, unsigned int* rate, unsigned int* ch,
    unsigned int* bits, unsigned int* frames)
{
	unsigned char* q = p + 0xC;
	int found_comm   = 0;
	int found_ssnd;
	unsigned char* ret;
	unsigned char* end;
	unsigned int tag;
	unsigned int size;
	unsigned int aiff;
	unsigned int id;
	unsigned int sz;
	unsigned short exp;
	unsigned short mant;
	unsigned int v1;
	unsigned int v2;
	unsigned int *ac, *ab, *af;
	unsigned int raw_ofst;

	tag        = AIFF_U32(p);
	size       = AIFF_U32(p + 4);
	size       = AIFF_SWAP32(size);
	aiff       = AIFF_U32(p + 8);
	found_ssnd = 0;
	ret        = 0;
	if (tag != 0x4D524F46) {
		return 0;
	}
	if (aiff != 0x46464941) {
		return 0;
	}
	end = q + size - 4;

	while (q < end) {
		id = AIFF_GetU32f(q);
		sz = AIFF_Swap32f(AIFF_GetU32f(q + 4));

		q += 8;
		ac = ch;
		ab = bits;
		af = frames;
		switch (id) {
			case 0x4D4D4F43:
				if (found_comm) {
					break;
				}
				if ((int)sz < 0x12) {
					return 0;
				}
				found_comm = 1;
				v1         = (q)[1];
				v1 <<= 8;
				v1 &= 0xFFFF00;
				*ch     = v1 | ((q)[0] & 0xFF);
				*ch     = ((((*ac) >> 8) & 0xFF) | (((*ch) & 0xFF) << 8));
				*frames = AIFF_U32(q + 2);
				*frames = ((((*frames) >> 24) | (((*frames) >> 8) & 0xFF00))
				              | (((*frames) << 8) & 0xFF0000))
				    | ((*af) << 24);
				v2 = (q + 6)[1];
				v2 <<= 8;
				v2 &= 0xFFFF00;
				*bits = v2 | ((q + 6)[0] & 0xFF);
				*bits = ((((*ab) >> 8) & 0xFF) | (((*bits) & 0xFF) << 8));
				exp   = AIFF_U16(q + 8);
				exp   = AIFF_SWAP16(exp);
				mant  = AIFF_U16(q + 10);
				mant  = AIFF_SWAP16(mant);
				*rate = mant >> (0x400E - exp);
				q += 0x12;
				if (found_ssnd) {
					return ret;
				}
				break;
			case 0x444E5353:
				if (found_ssnd) {
					break;
				}
				found_ssnd = 1;
				{
					raw_ofst = AIFF_U32(q);
					raw_ofst = AIFF_SWAP32(raw_ofst);
					q += 4;
					ret = q + raw_ofst;
				}
				if (found_comm) {
					return ret;
				}
				break;
			default:
				q += (sz + 1) & ~1;
				break;
		}
	}
	return ret;
}
}
