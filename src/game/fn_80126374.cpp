#include "game/memorycard_crypt.h"
#include "MSL_C/string.h"

// nMemoryCardUtil: digest and encryption of the save block. The three functions are one
// translation unit (contiguous code and exception tables); the file name is not known.
//
// Built with -bool off: CheckMD5 keeps the comparison result as an int without the byte
// truncation C++ bool adds.

extern "C" s32 memcmp(const void* lhs, const void* rhs, u32 size);

// DES key of the save block (8 bytes in .sdata2, owned by a unit that is not split yet).
extern "C" const char lbl_8042ECB0[8];

int nMemoryCardUtil::CheckMD5(SAVEDATA* data)
{
	u8 digest[0x10];
	TMD5 md5;
	md5.Begin();
	md5.Update(data->body, sizeof(data->body));
	md5.End(digest);
	int ok = memcmp(digest, data->digest, sizeof(digest)) == 0;
	memset(digest, 0, sizeof(digest));
	return ok;
}

void nMemoryCardUtil::MakeMD5(SAVEDATA* data)
{
	TMD5 md5;
	md5.Begin();
	md5.Update(data->body, sizeof(data->body));
	md5.End(data->digest);
}

void nMemoryCardUtil::Crypt(SAVEDATA* data, int mode)
{
	if (data != NULL) {
		char in[8];
		char out[8];
		TDes des;
		int remain = sizeof(SAVEDATA);
		des.MakeKey(lbl_8042ECB0);
		char* p = (char*)data;
		do {
			memset(in, 0, sizeof(in));
			memcpy(in, p, sizeof(in));
			des.Crypt(in, out, mode);
			memcpy(p, out, sizeof(out));
			remain -= sizeof(out);
			p += sizeof(out);
		} while (remain != 0);
		memset(in, 0, sizeof(in));
		memset(out, 0, sizeof(out));
	}
}
