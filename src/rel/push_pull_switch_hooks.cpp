#include "game/setObj.h"
#include "MSL_C/string.h"

// The four hooks rel/push_pull_switch_register.cpp puts in the push-pull
// switch's editor record, in the thirteen stage modules that share it.
//
// The reset clears the 0x14-byte work block the placement keeps for the
// switch. The load finds the switch's six textures in the stage's texture
// dictionary, reads its model and the model's first atomic, and then keeps two
// materials: for each, the first of the texture names that a material of the
// model uses, the second search going on from the first material. The unload
// only forgets the model and the materials (the stage resource manager owns
// them). The factory allocates 0xFC bytes and hands them to the module's
// constructor (left as assembly and named pushPullSwitchCtor here).

typedef struct RwTexDictionary RwTexDictionary;
typedef struct RwTexture RwTexture;
typedef struct RpMaterial RpMaterial;
typedef struct RpClump RpClump;
typedef struct RpAtomic RpAtomic;

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" char* pushPullSwitchTextureNames[6];
extern "C" char pushPullSwitchModelName[];
extern "C" RwTexture* pushPullSwitchTexture0;
extern "C" RwTexture* pushPullSwitchTexture1;
extern "C" RwTexture* pushPullSwitchTexture2;
extern "C" RwTexture* pushPullSwitchTexture3;
extern "C" RwTexture* pushPullSwitchTexture4;
extern "C" RwTexture* pushPullSwitchTexture5;
extern "C" RpClump* pushPullSwitchModel;
extern "C" RpAtomic* pushPullSwitchAtomic;
extern "C" RpMaterial* pushPullSwitchMaterials[2];

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* pushPullSwitchCtor(void* object, void* owner);
extern "C" RwTexture* fn_801A4BBC(RwTexDictionary* dictionary, char* name);
RwTexDictionary* objRwTexDictionaryGetPointer();
RpClump* objPointerReadFromClumpAnim(char* name);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* atomic);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);

extern "C" void pushPullSwitchReset(SETOBJ_PARAM* param)
{
	if (param->originalWork != NULL) {
		memset(param->originalWork, 0, 0x14);
	}
}

extern "C" void pushPullSwitchUnload(void)
{
	pushPullSwitchModel        = NULL;
	pushPullSwitchMaterials[0] = NULL;
	pushPullSwitchMaterials[1] = NULL;
}

extern "C" void pushPullSwitchLoad(void)
{
	RwTexDictionary* dictionary = objRwTexDictionaryGetPointer();
	int i;
	RpMaterial* previous;
	int j;

	pushPullSwitchTexture0 = fn_801A4BBC(dictionary, pushPullSwitchTextureNames[0]);
	pushPullSwitchTexture1 = fn_801A4BBC(dictionary, pushPullSwitchTextureNames[1]);
	pushPullSwitchTexture2 = fn_801A4BBC(dictionary, pushPullSwitchTextureNames[2]);
	pushPullSwitchTexture3 = fn_801A4BBC(dictionary, pushPullSwitchTextureNames[3]);
	pushPullSwitchTexture4 = fn_801A4BBC(dictionary, pushPullSwitchTextureNames[4]);
	pushPullSwitchTexture5 = fn_801A4BBC(dictionary, pushPullSwitchTextureNames[5]);
	pushPullSwitchModel    = objPointerReadFromClumpAnim(pushPullSwitchModelName);
	pushPullSwitchAtomic   = objRpClumpGetAtomic(pushPullSwitchModel, NULL);

	previous = NULL;
	for (i = 0; i < 2; i++) {
		pushPullSwitchMaterials[i] = NULL;
		for (j = 0; pushPullSwitchMaterials[i] == NULL; j++) {
			pushPullSwitchMaterials[i] = objRpClumpGetMaterialWithSpecificTexture(
			    pushPullSwitchModel, previous, pushPullSwitchTextureNames[j]);
		}
		previous = pushPullSwitchMaterials[i];
	}
}

extern "C" void pushPullSwitchCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		pushPullSwitchCtor(memory, lbl_8042C110);
	}
}
