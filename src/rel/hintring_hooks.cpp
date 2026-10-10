#include "types.h"

// The four hooks rel/hintring_register.cpp puts in the hint ring's editor
// record, in the thirteen stage modules that share it: the empty reset, the
// unload that forgets what the load read, the load, and the factory.
//
// The load reads the ring's clump (keeping its first atomic and its first
// material when there is one) and finds the ring's texture in the stage's
// texture dictionary, which the register's two resource records also point at
// (it is what rel/hintring_register.cpp calls hintringObjectModel). The factory
// allocates 0x84 bytes and hands them to the module's constructor (left as
// assembly and named hintringObjectCtor here).

typedef struct RwTexDictionary RwTexDictionary;
typedef struct RwTexture RwTexture;
typedef struct RpClump RpClump;
typedef struct RpAtomic RpAtomic;
typedef struct RpMaterial RpMaterial;

typedef struct ObjectResource {
	u8 unk00[0xC]; // 0x00
	void* model;   // 0x0C
	u8 unk10[0x8]; // 0x10
} ObjectResource;  // 0x18

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" char hintringObjectClumpName[];
extern "C" char hintringObjectTextureName[];
extern "C" RpClump* hintringObjectClump;
extern "C" RpAtomic* hintringObjectAtomic;
extern "C" RpMaterial* hintringObjectMaterial;
extern "C" void* hintringObjectModel;
extern "C" ObjectResource hintringObjectResourceA;
extern "C" ObjectResource hintringObjectResourceB;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* hintringObjectCtor(void* object, void* owner);
extern "C" RwTexture* fn_8005FA0C(RwTexDictionary* dictionary, char* name);
RwTexDictionary* objRwTexDictionaryGetPointer();
RpClump* objPointerReadFromClumpAnim(char* name);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* atomic);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);

extern "C" void hintringObjectReset(void) { }

extern "C" void hintringObjectUnload(void)
{
	hintringObjectClump           = NULL;
	hintringObjectAtomic          = NULL;
	hintringObjectMaterial        = NULL;
	hintringObjectModel           = NULL;
	hintringObjectResourceA.model = NULL;
	hintringObjectResourceB.model = NULL;
}

extern "C" void hintringObjectLoad(void)
{
	hintringObjectClump = objPointerReadFromClumpAnim(hintringObjectClumpName);
	if (hintringObjectClump != NULL) {
		hintringObjectAtomic = objRpClumpGetAtomic(hintringObjectClump, NULL);
		hintringObjectMaterial
		    = objRpClumpGetMaterialWithSpecificTexture(hintringObjectClump, NULL, NULL);
	}
	hintringObjectModel = fn_8005FA0C(objRwTexDictionaryGetPointer(), hintringObjectTextureName);
	hintringObjectResourceA.model = hintringObjectModel;
	hintringObjectResourceB.model = hintringObjectModel;
}

extern "C" void hintringObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x84);

	if (memory != NULL) {
		hintringObjectCtor(memory, lbl_8042C110);
	}
}
