// Updates an Adler-32 checksum with len bytes of buf (HYPOTHESIS: zlib adler32), reducing modulo
// 65521 at least every 5552 bytes. A null buffer returns the initial value 1.
#include "types.h"

#define ADLER_BASE 65521UL
#define ADLER_NMAX 5552

#define DO1(buf, i)                                                                                \
	{                                                                                              \
		s1 += buf[i];                                                                              \
		s2 += s1;                                                                                  \
	}
#define DO2(buf, i)                                                                                \
	DO1(buf, i);                                                                                   \
	DO1(buf, i + 1);
#define DO4(buf, i)                                                                                \
	DO2(buf, i);                                                                                   \
	DO2(buf, i + 2);
#define DO8(buf, i)                                                                                \
	DO4(buf, i);                                                                                   \
	DO4(buf, i + 4);
#define DO16(buf)                                                                                  \
	DO8(buf, 0);                                                                                   \
	DO8(buf, 8);

extern "C" {
unsigned long fn_80178738(unsigned long adler, const unsigned char* buf, unsigned int len)
{
	unsigned long s1 = adler & 0xFFFF;
	unsigned long s2 = (adler >> 16) & 0xFFFF;
	int k;
	if (buf == 0) {
		return 1L;
	}
	while (len > 0) {
		k = len < ADLER_NMAX ? len : ADLER_NMAX;
		len -= k;
		while (k >= 16) {
			DO16(buf);
			buf += 16;
			k -= 16;
		}
		if (k != 0) {
			do {
				s1 += *buf++;
				s2 += s1;
			} while (--k);
		}
		s1 %= ADLER_BASE;
		s2 %= ADLER_BASE;
	}
	return (s2 << 16) | s1;
}
}
