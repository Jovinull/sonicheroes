#ifndef GAME_MEMORYCARD_CRYPT_H
#define GAME_MEMORYCARD_CRYPT_H

#include "types.h"

// Save-data digest and cipher used by the memory card code.
//
// Class, method and namespace names are CORROBORATED by the PS2 symbol table (TMD5, TDes,
// nMemoryCardUtil and SAVEDATA, with matching argument lists); the GameCube bodies are the
// evidence for the field layouts. Field names are inferred.

// MD5 context (HYPOTHESIS: the RSA reference MD5_CTX with the bit count first).
class TMD5
{
public:
	TMD5();
	~TMD5();
	void Begin();
	void Update(const void* data, unsigned int size);
	void End(void* digest);

private:
	void Transform(unsigned int* state, unsigned int* block);

	u32 mCount[2];    // 0x00: message length in bits, low word first
	u32 mState[4];    // 0x08: chaining values A, B, C, D
	u8 mBuffer[0x40]; // 0x18: pending input block
};

// DES cipher. The whole 0x300-byte state is cleared by the constructor and the destructor; its
// internal layout (key schedule) is UNKNOWN.
class TDes
{
public:
	TDes();
	~TDes();
	void Crypt(const char* in, char* out, int mode);
	void MakeKey(const char* key);

private:
	u8 mWork[0x300];
};

// Save block as stored on the memory card: an MD5 digest of the body followed by the body. Only
// the sizes are known here (the PS2 class also has methods such as GetAudioHash).
struct SAVEDATA {
	u8 digest[0x10]; // 0x000
	u8 body[0x6F8];  // 0x010
};

namespace nMemoryCardUtil
{
// Returns nonzero when the stored digest matches the body.
int CheckMD5(SAVEDATA* data);
// Stores the body's digest in front of it.
void MakeMD5(SAVEDATA* data);
// Runs the whole block through DES in 8-byte blocks; mode selects the direction.
void Crypt(SAVEDATA* data, int mode);
} // namespace nMemoryCardUtil

#endif
