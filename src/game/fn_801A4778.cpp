// Calls callback(texture, data) for every texture of the dictionary, stopping early when it
// returns null (HYPOTHESIS: RwTexDictionaryForAllTextures). The next link is read before the call
// so the callback may remove the texture. Returns the dictionary.
#include "game/rw_engine.h"

typedef RwTexture* (*RwTextureCallBack801A4778)(RwTexture* texture, void* data);

extern "C" {
RwTexDictionary* fn_801A4778(RwTexDictionary* dict, RwTextureCallBack801A4778 callback, void* data)
{
	RwLLLink* next;
	RwLLLink* cur       = dict->texturesInDict.link.next;
	const RwLLLink* end = &dict->texturesInDict.link;
	while (cur != end) {
		RwTexture* texture = (RwTexture*)((u8*)cur - 0x8); // lInDictionary
		next               = cur->next;
		if (callback(texture, data) == 0) {
			break;
		}
		cur = next;
	}
	return dict;
}
}
