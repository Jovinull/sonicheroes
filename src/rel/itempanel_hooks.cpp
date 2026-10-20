#include "types.h"

// endObjItempanel and initObjItempanel (the PS2 build's names), the item
// panel's unload and load hooks, which the item box's own hooks call: the four
// panel objects are killed and forgotten, and the thirteen panel icons
// (o_ring ... o_fgage) are looked up in the stage's texture dictionary.

typedef struct RwTexture RwTexture;
typedef struct RwTexDictionary RwTexDictionary;

typedef struct ItempanelObject {
	u8 unk00[0x4];
	u16 signal; // 0x04, 1: kill
} ItempanelObject;

typedef struct ItempanelTexture {
	RwTexture* texture; // 0x00
	const char* name;   // 0x04
} ItempanelTexture;

extern "C" ItempanelObject* itempanelObjects[4];
extern "C" ItempanelTexture itempanelTextures[13];

RwTexDictionary* objRwTexDictionaryGetPointer();
extern "C" RwTexture* fn_801A4BBC(RwTexDictionary* dict, const char* name);

void endObjItempanel()
{
	for (int i = 0; i < 4; i++) {
		if (itempanelObjects[i] != NULL) {
			itempanelObjects[i]->signal |= 1;
		}
		itempanelObjects[i] = NULL;
	}
	for (long i = 0; i < 13; i++) {
		itempanelTextures[i].texture = NULL;
	}
}

void initObjItempanel()
{
	for (int i = 0; i < 4; i++) {
		itempanelObjects[i] = NULL;
	}
	RwTexDictionary* dict = objRwTexDictionaryGetPointer();

	for (int i = 0; i < 13; i++) {
		if (itempanelTextures[i].name != NULL) {
			itempanelTextures[i].texture = fn_801A4BBC(dict, itempanelTextures[i].name);
		}
	}
}
