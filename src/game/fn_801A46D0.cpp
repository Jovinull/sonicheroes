// Destroys a texture dictionary (HYPOTHESIS: RwTexDictionaryDestroy): stops it being the current
// dictionary, drops every texture in it through fn_801A491C, runs the dictionary plugin
// destructors, unlinks it from the engine instance's dictionary list and returns it to the
// dictionary free list. Always returns 1.
#include "game/rw_engine.h"

typedef RwTexture* (*RwTextureCallBack801A46D0)(RwTexture* texture, void* data);

extern "C" {
// Texture dictionary plugin registry (HYPOTHESIS: texDictTKList).
extern RwPluginRegistry lbl_80290658;
// HYPOTHESIS: RwTexDictionaryForAllTextures and RwTextureDestroy (used as the callback).
RwTexDictionary* fn_801A4778(RwTexDictionary* dict, RwTextureCallBack801A46D0 callback, void* data);
s32 fn_801A491C(RwTexture* texture);

s32 fn_801A46D0(RwTexDictionary* dict)
{
	if (RW_CURRENT_TEX_DICTIONARY == dict) {
		RW_CURRENT_TEX_DICTIONARY = 0;
	}
	fn_801A4778(dict, (RwTextureCallBack801A46D0)fn_801A491C, 0);
	fn_80198E04(&lbl_80290658, dict);
	dict->lInInstance.prev->next = dict->lInInstance.next;
	dict->lInInstance.next->prev = dict->lInInstance.prev;
	lbl_8042C9A4->freeListFree(RW_TEX_DICTIONARY_FREE_LIST, dict);
	return 1;
}
}
