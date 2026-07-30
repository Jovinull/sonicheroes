#include "types.h"

struct RwStream;
struct RwTexDictionary;

extern "C" {
RwStream* fn_80041FF4(char* path);
s32 fn_80192F38(RwStream* stream, u32 type, u32* length, u32* version);
RwTexDictionary* fn_8019B744(RwStream* stream);
s32 fn_80197ED8(RwStream* stream, void* data);
}

static inline RwTexDictionary* texLoadTexDictionaryMemory(RwStream* stream)
{
	RwTexDictionary* dictionary = 0;

	if (stream != 0 && fn_80192F38(stream, 0x16, 0, 0))
		dictionary = fn_8019B744(stream);

	return dictionary;
}

RwTexDictionary* texLoadTexDictionaryFile(char* path)
{
	RwTexDictionary* dictionary = 0;
	RwStream* stream            = fn_80041FF4(path);

	if (stream != 0) {
		dictionary = texLoadTexDictionaryMemory(stream);
		fn_80197ED8(stream, 0);
	}

	return dictionary;
}
