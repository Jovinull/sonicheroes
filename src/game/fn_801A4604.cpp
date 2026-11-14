// Creates an empty texture dictionary (HYPOTHESIS: RwTexDictionaryCreate): takes one from the
// dictionary free list, initializes its object header (type 6), links it at the head of the engine
// instance's dictionary list, empties its texture list and runs the dictionary plugin constructors.
// Returns the dictionary, or null when allocation fails.
#include "game/rw_engine.h"

#define RW_TEX_DICTIONARY_TYPE 6

extern "C" {
// Texture dictionary plugin registry (HYPOTHESIS: texDictTKList).
extern RwPluginRegistry lbl_80290658;

RwTexDictionary* fn_801A4604(void)
{
	RwTexDictionary* dict
	    = (RwTexDictionary*)lbl_8042C9A4->freeListAlloc(RW_TEX_DICTIONARY_FREE_LIST);
	if (dict == 0) {
		return 0;
	}
	dict->object.type                      = RW_TEX_DICTIONARY_TYPE;
	dict->object.subType                   = 0;
	dict->object.flags                     = 0;
	dict->object.privateFlags              = 0;
	dict->object.parent                    = 0;
	dict->lInInstance.next                 = RW_TEX_DICTIONARY_LIST.link.next;
	dict->lInInstance.prev                 = &RW_TEX_DICTIONARY_LIST.link;
	RW_TEX_DICTIONARY_LIST.link.next->prev = &dict->lInInstance;
	RW_TEX_DICTIONARY_LIST.link.next       = &dict->lInInstance;
	dict->texturesInDict.link.next         = &dict->texturesInDict.link;
	dict->texturesInDict.link.prev         = &dict->texturesInDict.link;
	fn_80198D5C(&lbl_80290658, dict);
	return dict;
}
}
