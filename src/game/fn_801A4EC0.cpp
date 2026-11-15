// Closes the texture module (HYPOTHESIS: _rwTextureClose): frees the module's scratch buffer
// (+0x24, size at +0x28), destroys the default texture dictionary lbl_8042C9C0 when it is still in
// the dictionary list (clearing it as the current dictionary, destroying its textures until one
// refuses, running the dictionary plugin destructors and returning it to its free list), destroys
// the texture and dictionary free lists and drops the instance count. Returns the instance.
// NonMatching: instruction stream matches; retail keeps the module globals in r3 and the list
// cursor in r4 (swapped here) and computes the texture-list terminator before loading its head
// (11 words). Declaration permutations get no closer.
#include "game/rw_engine.h"

struct TextureGlobals801A4EC0 {
	RwLinkList dictionaries;      // 0x0
	RwFreeList* textureFreeList;  // 0x8
	RwFreeList* dictFreeList;     // 0xC
	RwTexDictionary* currentDict; // 0x10
	u8 pad14[0x24 - 0x14];
	void* scratch;   // 0x24
	u16 scratchSize; // 0x28
};

#define TEXTURE_GLOBALS_801A4EC0      ((TextureGlobals801A4EC0*)RW_TEXTURE_GLOBALS)
#define TEXTURE_SCRATCH_801A4EC0      (*(void**)(RW_TEXTURE_GLOBALS + 0x24))
#define TEXTURE_SCRATCH_SIZE_801A4EC0 (*(u16*)(RW_TEXTURE_GLOBALS + 0x28))

extern "C" {
// Default texture dictionary and the dictionary plugin registry (HYPOTHESIS: texDictTKList).
extern RwTexDictionary* lbl_8042C9C0;
extern RwPluginRegistry lbl_80290658;
// HYPOTHESIS: the texture-destroy callback used when a dictionary is destroyed.
RwTexture* fn_801A491C(RwTexture* texture, void* data);

void* fn_801A4EC0(void* instance)
{
	RwLLLink* texLink;
	RwLLLink* cur;
	RwLLLink* next;
	RwTexDictionary* dict;
	RwLLLink* end;

	if (TEXTURE_SCRATCH_801A4EC0 != 0) {
		lbl_8042C9A4->rwfree(TEXTURE_SCRATCH_801A4EC0);
		TEXTURE_SCRATCH_801A4EC0      = 0;
		TEXTURE_SCRATCH_SIZE_801A4EC0 = 0;
	}
	{
		TextureGlobals801A4EC0* globals = TEXTURE_GLOBALS_801A4EC0;
		if (globals->textureFreeList != 0 && globals->dictFreeList != 0) {
			cur  = globals->dictionaries.link.next;
			dict = lbl_8042C9C0;
			while (cur != &globals->dictionaries.link) {
				RwTexDictionary* entry = (RwTexDictionary*)((u8*)cur - 0x10);
				cur                    = cur->next;
				if (entry == dict) {
					if (globals->currentDict == dict) {
						globals->currentDict = 0;
					}
					end     = &dict->texturesInDict.link;
					texLink = dict->texturesInDict.link.next;
					while (texLink != end) {
						next = texLink->next;
						if (fn_801A491C((RwTexture*)((u8*)texLink - 8), 0) == 0) {
							break;
						}
						texLink = next;
					}
					fn_80198E04(&lbl_80290658, dict);
					RwLLLinkRemove(&dict->lInInstance);
					lbl_8042C9A4->freeListFree(RW_TEX_DICTIONARY_FREE_LIST, dict);
					lbl_8042C9C0 = 0;
					break;
				}
			}
		}
	}
	if (RW_TEXTURE_FREE_LIST != 0) {
		RwFreeListDestroy(RW_TEXTURE_FREE_LIST);
		RW_TEXTURE_FREE_LIST = 0;
	}
	if (RW_TEX_DICTIONARY_FREE_LIST != 0) {
		RwFreeListDestroy(RW_TEX_DICTIONARY_FREE_LIST);
		RW_TEX_DICTIONARY_FREE_LIST = 0;
	}
	lbl_8042C9C4.numInstances--;
	return instance;
}
}
