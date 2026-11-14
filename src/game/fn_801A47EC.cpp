// Calls callback(dict, data) for every texture dictionary of the engine instance, stopping early
// when it returns null (HYPOTHESIS: RwTexDictionaryForAllTexDictionaries). Always returns 1.
#include "game/rw_engine.h"

typedef RwTexDictionary* (*RwTexDictionaryCallBack801A47EC)(RwTexDictionary* dict, void* data);

extern "C" {
s32 fn_801A47EC(RwTexDictionaryCallBack801A47EC callback, void* data)
{
	RwLinkList* list = &RW_TEX_DICTIONARY_LIST;
	RwLLLink* cur    = list->link.next;
	while (cur != &list->link) {
		RwLLLink* next        = cur->next;
		RwTexDictionary* dict = (RwTexDictionary*)((u8*)cur - 0x10); // lInInstance
		if (callback(dict, data) == 0) {
			break;
		}
		cur = next;
	}
	return 1;
}
}
