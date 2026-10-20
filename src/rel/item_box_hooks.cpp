#include "types.h"

// The item box's unload and load hooks (itemBoxUnload and itemBoxLoad here):
// loading looks up the box's three glow textures, the thirteen item icons and
// the three sign textures in the stage's texture dictionary, reads the box
// model and finds its icon, glow and sign materials (the first texture name
// the model has), then loads the item panel; unloading forgets them all and
// ends the item panel.

typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;
typedef struct RwTexture RwTexture;
typedef struct RwTexDictionary RwTexDictionary;

typedef struct ItemBoxIcon {
	RwTexture* texture; // 0x00
	char* name;         // 0x04
	s32 unk08;          // 0x08
} ItemBoxIcon;          // 0x0C

extern "C" RpClump* itemBoxModel;
extern "C" RpMaterial* itemBoxMaterial;
extern "C" RpMaterial* itemBoxGlowMaterial;
extern "C" RpMaterial* itemBoxSignMaterial;
extern "C" RwTexture* itemBoxTexture0;
extern "C" RwTexture* itemBoxTexture1;
extern "C" RwTexture* itemBoxTexture2;
extern "C" char* itemBoxTextureNames[];
extern "C" ItemBoxIcon itemBoxIcons[13];
extern "C" RwTexture* itemBoxSignTextures[3];
extern "C" char itemBoxSignName0[];
extern "C" char itemBoxSignName1[];
extern "C" char itemBoxSignName2[];
extern "C" char itemBoxModelFile[];

RwTexDictionary* objRwTexDictionaryGetPointer();
RpClump* objPointerReadFromClumpAnim(char* file);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* texture);
void endObjItempanel();
void initObjItempanel();
extern "C" RwTexture* fn_801A4BBC(RwTexDictionary* dict, const char* name);

extern "C" void itemBoxUnload(void)
{
	itemBoxModel        = NULL;
	itemBoxMaterial     = NULL;
	itemBoxSignMaterial = NULL;
	for (long i = 0; i < 13; i++) {
		itemBoxIcons[i].texture = NULL;
	}
	for (long i = 0; i < 3; i++) {
		itemBoxSignTextures[i] = NULL;
	}
	endObjItempanel();
}

extern "C" void itemBoxLoad(void)
{
	RwTexDictionary* dict = objRwTexDictionaryGetPointer();

	itemBoxTexture0 = fn_801A4BBC(dict, itemBoxTextureNames[0]);
	itemBoxTexture1 = fn_801A4BBC(dict, itemBoxTextureNames[1]);
	itemBoxTexture2 = fn_801A4BBC(dict, itemBoxTextureNames[2]);
	for (long i = 0; i < 13; i++) {
		if (itemBoxIcons[i].name != NULL) {
			itemBoxIcons[i].texture = fn_801A4BBC(dict, itemBoxIcons[i].name);
		}
	}
	itemBoxSignTextures[0] = fn_801A4BBC(dict, itemBoxSignName0);
	itemBoxSignTextures[1] = fn_801A4BBC(dict, itemBoxSignName1);
	itemBoxSignTextures[2] = fn_801A4BBC(dict, itemBoxSignName2);
	itemBoxModel           = objPointerReadFromClumpAnim(itemBoxModelFile);
	if (itemBoxModel != NULL) {
		ItemBoxIcon* icon = itemBoxIcons;

		itemBoxMaterial = NULL;
		while (itemBoxMaterial == NULL) {
			itemBoxMaterial
			    = objRpClumpGetMaterialWithSpecificTexture(itemBoxModel, NULL, icon->name);
			icon++;
		}
		itemBoxGlowMaterial = NULL;
		for (long i = 0; itemBoxGlowMaterial == NULL; i++) {
			itemBoxGlowMaterial = objRpClumpGetMaterialWithSpecificTexture(
			    itemBoxModel, NULL, itemBoxTextureNames[i]);
		}
		itemBoxSignMaterial
		    = objRpClumpGetMaterialWithSpecificTexture(itemBoxModel, NULL, itemBoxSignName0);
		if (itemBoxSignMaterial == NULL) {
			itemBoxSignMaterial
			    = objRpClumpGetMaterialWithSpecificTexture(itemBoxModel, NULL, itemBoxSignName1);
		}
	}
	initObjItempanel();
}
