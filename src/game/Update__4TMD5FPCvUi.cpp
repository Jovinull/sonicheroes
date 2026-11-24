#include "game/memorycard_crypt.h"

// TMD5::Update(const void*, unsigned int): the byte-at-a-time update of the RSA reference MD5
// (the 1990 md5.c MD5Update): adds the length in bits to the count, copies the input into the
// block buffer and transforms every full 64-byte block, packed little-endian into 16 words.
// TMD5::End (not split yet) inlines this function.
void TMD5::Update(const void* data, unsigned int size)
{
	unsigned int in[16];
	int mdi;
	unsigned int i, ii;
	const u8* input;

	mdi   = (int)((mCount[0] >> 3) & 0x3F);
	input = (const u8*)data;
	if ((mCount[0] + ((u32)size << 3)) < mCount[0]) {
		mCount[1]++;
	}
	mCount[0] += (u32)size << 3;
	mCount[1] += (u32)size >> 29;

	while (size--) {
		mBuffer[mdi++] = *input++;
		if (mdi == 0x40) {
			for (i = 0, ii = 0; i < 16; i++, ii += 4) {
				in[i] = (((u32)mBuffer[ii + 3]) << 24) | (((u32)mBuffer[ii + 2]) << 16)
				    | (((u32)mBuffer[ii + 1]) << 8) | ((u32)mBuffer[ii]);
			}
			Transform(mState, in);
			mdi = 0;
		}
	}
}
