#include "game/memorycard_crypt.h"

// TMD5::Begin(): zeroes the 64-bit bit count and loads the four standard MD5 chaining constants.

void TMD5::Begin()
{
	mCount[0] = 0;
	mCount[1] = 0;
	mState[0] = 0x67452301;
	mState[1] = 0xEFCDAB89;
	mState[2] = 0x98BADCFE;
	mState[3] = 0x10325476;
}
