#include "game/memorycard_crypt.h"
#include "MSL_C/string.h"

// TMD5::~TMD5(): clears the bit count, the chaining values and the input buffer.

TMD5::~TMD5()
{
	memset(mCount, 0, sizeof(mCount));
	memset(mState, 0, sizeof(mState));
	memset(mBuffer, 0, sizeof(mBuffer));
}
