// CRI ADX header decoding (adx_dcd): the ADX header, its extension blocks
// (version, cutoff, delay, loop, AINF), the footer and the ADPCM prediction
// coefficients.
//
// .text 0x80212800-0x80213014 (10 functions), .rodata 0x8023DF98-0x8023DFD8
// ("(c)CRI" and GetCoefficient's float constants). ADX_DecodeInfoExVer is
// also inlined into ExIdly/ExLoop/Ainf. MKD adx_dcd.o has the same ten
// functions. Needs GC/1.3.2r: plain 1.3.2 pools GetCoefficient's constants
// behind a base register, which the DOL does not do.
#include "types.h"

unsigned long strlen(const char* s);
void* memcpy(void* dst, const void* src, unsigned long n);
double cos(double x);
double __frsqrte(double x);

typedef struct ADX_HDR {
	unsigned short magic;      // 0x00
	short cpy_ofst;            // 0x02
	unsigned char encoding;    // 0x04
	unsigned char blklen;      // 0x05
	unsigned char nbits;       // 0x06
	unsigned char nch;         // 0x07
	unsigned char sfreq[4];    // 0x08
	unsigned char nsmpl[4];    // 0x0C
	unsigned short cutoff;     // 0x10
	unsigned char ver;         // 0x12
	unsigned char rev;         // 0x13
	unsigned char reserved[4]; // 0x14
	unsigned short dly[4];     // 0x18
} ADX_HDR;

static inline float adx_sqrtf(float x)
{
	volatile float y;

	if (x > 0.0f) {
		double guess = __frsqrte((double)x);
		guess        = 0.5 * guess * (3.0 - guess * guess * x);
		guess        = 0.5 * guess * (3.0 - guess * guess * x);
		guess        = 0.5 * guess * (3.0 - guess * guess * x);
		y            = (float)(x * guess);
		return y;
	}
	return x;
}

void ADX_GetCoefficient(int cutoff, int sfreq, short* k0, short* k1)
{
	float z;
	float a;
	float b;
	float c;
	float d;

	z   = cos(6.2831855f * (float)cutoff / (float)sfreq);
	a   = adx_sqrtf(2.0f) - z;
	b   = adx_sqrtf(2.0f) - 1.0f;
	c   = adx_sqrtf((a + b) * (a - b));
	d   = (a - c) / b;
	*k0 = 4096.0f * (2.0f * d);
	*k1 = 4096.0f * (-d * d);
}

int ADX_ScanInfoCode(signed char* ibuf, int ibuflen, short* dlen)
{
	int pos;
	int found = 0x7FFFFFFF;
	short* p  = (short*)ibuf;

	for (pos = 0; pos < ibuflen - 1; pos += 2, p++) {
		if (*p == -32768) {
			found = pos < found ? pos : found;
			break;
		}
	}
	if (found != 0x7FFFFFFF) {
		*dlen = found;
		return 0;
	}
	*dlen = 0;
	return -1;
}

int ADX_DecodeInfo(signed char* ibuf, int ibuflen, short* dlen, signed char* enc,
    signed char* nbits, signed char* blklen, signed char* nch, int* sfreq, int* nsmpl, int* blksmpl)
{
	unsigned char* h = (unsigned char*)ibuf;

	if (ibuflen < 0x10) {
		return -1;
	}
	if ((unsigned short)((h[0] << 8) | h[1]) != 0x8000) {
		return -2;
	}
	*dlen   = ((h[2] << 8) | h[3]) + 4;
	*enc    = h[4];
	*blklen = h[5];
	*nbits  = h[6];
	*nch    = h[7];
	*sfreq  = (h[8] << 24) | (h[9] << 16) | (h[10] << 8) | h[11];
	*nsmpl  = (h[12] << 24) | (h[13] << 16) | (h[14] << 8) | h[15];
	if (*nbits == 0) {
		*blksmpl = 0;
	} else {
		*blksmpl = (*blklen - 2) * 8 / *nbits;
	}
	return 0;
}

int ADX_DecodeInfoExADPCM2(signed char* ibuf, int ibuflen, short* cutoff)
{
	ADX_HDR* hdr = (ADX_HDR*)ibuf;

	if (ibuflen < 0x12) {
		return -1;
	}
	if (hdr->magic != 0x8000) {
		return -2;
	}
	if (hdr->cpy_ofst < 0xE) {
		return -1;
	}
	*cutoff = hdr->cutoff;
	return 0;
}

int ADX_DecodeInfoExVer(signed char* ibuf, int ibuflen, unsigned char* ver, unsigned char* rev)
{
	ADX_HDR* hdr = (ADX_HDR*)ibuf;

	if (ibuflen < 0x14) {
		return -1;
	}
	if (hdr->magic != 0x8000) {
		return -2;
	}
	if (hdr->cpy_ofst < 0x10) {
		return -1;
	}
	*ver = hdr->ver;
	*rev = hdr->rev;
	return 0;
}

int ADX_DecodeInfoExIdly(signed char* ibuf, int ibuflen, short* dlyl, short* dlyr)
{
	ADX_HDR* hdr = (ADX_HDR*)ibuf;
	unsigned char ver;
	unsigned char rev;

	if (ADX_DecodeInfoExVer(ibuf, ibuflen, &ver, &rev) != 0) {
		return -1;
	}
	if (ver >= 4) {
		if (ibuflen < 0x20) {
			return -1;
		}
		if (hdr->magic != 0x8000) {
			return -2;
		}
		if (hdr->cpy_ofst < 0x1C) {
			return -1;
		}
		dlyl[0] = hdr->dly[0];
		dlyr[0] = hdr->dly[1];
		dlyl[1] = hdr->dly[2];
		dlyr[1] = hdr->dly[3];
	} else {
		dlyl[0] = dlyr[0] = dlyl[1] = dlyr[1] = 0;
	}
	return 0;
}

int ADX_DecodeInfoExLoop(signed char* ibuf, int ibuflen, int* lpins, short* nlp, short* lptype,
    int* lpsp, int* lpso, int* lpep, int* lpeo)
{
	ADX_HDR* hdr = (ADX_HDR*)ibuf;
	unsigned char ver;
	unsigned char rev;
	int ret;
	int len;
	int ofst;

	*nlp = 0;
	ret  = ADX_DecodeInfoExVer(ibuf, ibuflen, &ver, &rev);
	if (ret != 0) {
		return ret;
	}
	len = ver == 4 ? 0x3C : 0x30;
	if (ibuflen < len) {
		return -1;
	}
	if (hdr->magic != 0x8000) {
		return -2;
	}
	if (hdr->cpy_ofst < len - 4) {
		return -1;
	}
	ofst   = ver == 4 ? 0x20 : 0x14;
	*lpins = *(short*)(ibuf + ofst);
	ofst += (int)ibuf;
	ibuf = (signed char*)ofst;
	*nlp = *(short*)(ibuf + 2);
	if (*nlp != 1) {
		return -2;
	}
	*lptype = *(short*)(ibuf + 6);
	*lpsp   = *(int*)(ibuf + 8);
	*lpso   = *(int*)(ibuf + 0xC);
	*lpep   = *(int*)(ibuf + 0x10);
	*lpeo   = *(int*)(ibuf + 0x14);
	return 0;
}

int ADX_DecodeInfoAinf(
    signed char* ibuf, int ibuflen, int* ainflen, unsigned char* ainf, short* defvol, short* defpan)
{
	ADX_HDR* hdr = (ADX_HDR*)ibuf;
	unsigned char ver;
	unsigned char rev;
	int ret;
	int len;
	int ofst;

	*ainflen = 0;
	ret      = ADX_DecodeInfoExVer(ibuf, ibuflen, &ver, &rev);
	if (ret != 0) {
		return ret;
	}
	len = ver == 4 ? 0x48 : 0x3C;
	if (ibuflen < len) {
		return -1;
	}
	if (hdr->magic != 0x8000) {
		return -2;
	}
	if (hdr->cpy_ofst < len - 4) {
		return -1;
	}
	ofst = ver == 4 ? 0x20 : 0x14;
	if (((*(unsigned char*)(4 + ofst + (int)ibuf) << 24)
	        | (*(unsigned char*)(5 + ofst + (int)ibuf) << 16)
	        | (*(unsigned char*)(6 + ofst + (int)ibuf) << 8)
	        | *(unsigned char*)(7 + ofst + (int)ibuf))
	    != 0x41494E46) { // "AINF"
		return -2;
	}
	*ainflen = *(int*)(8 + ofst + (int)ibuf);
	memcpy(ainf, (void*)(0xC + ofst + (int)ibuf), 16);
	*defvol   = *(short*)(0x1C + ofst + (int)ibuf);
	defpan[0] = *(short*)(0x20 + ofst + (int)ibuf);
	defpan[1] = *(short*)(0x22 + ofst + (int)ibuf);
	return 0;
}

int ADX_DecodeFooter(signed char* ibuf, int ibuflen, short* dlen)
{
	if (ibuflen < 0x10) {
		return -1;
	}
	if (*(unsigned short*)ibuf != 0x8001) {
		return -2;
	}
	*dlen = *(short*)(ibuf + 2) + 4;
	return 0;
}

int ADX_CalcHdrInfoLen(int ver, int hdrlen, int ofst, unsigned int align)
{
	if (ver == 0) {
		return align * ((0x1B + hdrlen + strlen("(c)CRI") + ofst + align) / align) - ofst;
	}
	return align * ((0x33 + hdrlen + strlen("(c)CRI") + ofst + align) / align) - ofst;
}
