#include "game/object.h"

// Loads the shared resources of an effect (HYPOTHESIS: the effect's set-up routine): looks up
// the eight textures of the table lbl_80259C78 (entries without a name are skipped) in the
// current texture dictionary (fn_801A4BBC), and reads the clumps lbl_8042C4C0, lbl_8042C4C4,
// lbl_8042C4C8, lbl_8042C4CC and lbl_8042C4D0 once (objPointerReadFromClumpAnim), keeping the
// material of each (the first three by the texture name lbl_80259C18) and making them ignore
// the lights and modulate the material colour. The UV animation lbl_8042C4E8 is read every time
// and, when present, set as the custom FX texture (lbl_803E7080) of the first three clumps. The
// names of the resources are UNKNOWN.

struct Texture800F7038 {
	void* texture; // 0x0
	char* name;    // 0x4
};

extern "C" {
extern Texture800F7038 lbl_80259C78[8];
extern char lbl_80259C18[];
extern char lbl_80259D48[];
extern char lbl_80259D5C[];
extern char lbl_80259D70[];
extern char lbl_80259D84[];
extern char lbl_80259D94[];
extern char lbl_80259DA8[];
extern RpClump* lbl_8042C4C0;
extern RpClump* lbl_8042C4C4;
extern RpClump* lbl_8042C4C8;
extern RpClump* lbl_8042C4CC;
extern RpClump* lbl_8042C4D0;
extern RpMaterial* lbl_8042C4D4;
extern RpMaterial* lbl_8042C4D8;
extern RpMaterial* lbl_8042C4DC;
extern RpMaterial* lbl_8042C4E0;
extern RpMaterial* lbl_8042C4E4;
extern RpUVAnimAnimation* lbl_8042C4E8;
extern UVFXInfo lbl_803E7080;
void* fn_801A4BBC(void* dictionary, char* name);
}

void* objRwTexDictionaryGetPointer();
void* objPointerReadFromClumpAnim(char* name);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);
void objRpClumpForAllGeometrysToModulateMaterialColor(RpClump* clump);
void SetClumpCustomFXTexture(RpClump* clump, UVFXInfo* info);

extern "C" void fn_800F7038(void)
{
	void* dictionary = objRwTexDictionaryGetPointer();

	for (u32 i = 0; i < 8; i++) {
		if (lbl_80259C78[i].name != NULL) {
			lbl_80259C78[i].texture = fn_801A4BBC(dictionary, lbl_80259C78[i].name);
		}
	}
	if (lbl_8042C4C0 == NULL) {
		lbl_8042C4C0 = (RpClump*)objPointerReadFromClumpAnim(lbl_80259D48);
		if (lbl_8042C4C0 != NULL) {
			lbl_8042C4D4
			    = objRpClumpGetMaterialWithSpecificTexture(lbl_8042C4C0, NULL, lbl_80259C18);
			objRpClumpForAllGeometrysToIgnoreLights(lbl_8042C4C0);
			objRpClumpForAllGeometrysToModulateMaterialColor(lbl_8042C4C0);
		}
	}
	if (lbl_8042C4C4 == NULL) {
		lbl_8042C4C4 = (RpClump*)objPointerReadFromClumpAnim(lbl_80259D5C);
		if (lbl_8042C4C4 != NULL) {
			lbl_8042C4D8
			    = objRpClumpGetMaterialWithSpecificTexture(lbl_8042C4C4, NULL, lbl_80259C18);
			objRpClumpForAllGeometrysToIgnoreLights(lbl_8042C4C4);
			objRpClumpForAllGeometrysToModulateMaterialColor(lbl_8042C4C4);
		}
	}
	if (lbl_8042C4C8 == NULL) {
		lbl_8042C4C8 = (RpClump*)objPointerReadFromClumpAnim(lbl_80259D70);
		if (lbl_8042C4C8 != NULL) {
			lbl_8042C4DC
			    = objRpClumpGetMaterialWithSpecificTexture(lbl_8042C4C8, NULL, lbl_80259C18);
			objRpClumpForAllGeometrysToIgnoreLights(lbl_8042C4C8);
			objRpClumpForAllGeometrysToModulateMaterialColor(lbl_8042C4C8);
		}
	}
	lbl_8042C4E8 = (RpUVAnimAnimation*)objPointerReadFromClumpAnim(lbl_80259D84);
	if (lbl_8042C4E8 != NULL) {
		lbl_803E7080.uvAnim = lbl_8042C4E8;
		SetClumpCustomFXTexture(lbl_8042C4C0, &lbl_803E7080);
		SetClumpCustomFXTexture(lbl_8042C4C4, &lbl_803E7080);
		SetClumpCustomFXTexture(lbl_8042C4C8, &lbl_803E7080);
	}
	if (lbl_8042C4CC == NULL) {
		lbl_8042C4CC = (RpClump*)objPointerReadFromClumpAnim(lbl_80259D94);
		if (lbl_8042C4CC != NULL) {
			lbl_8042C4E0 = objRpClumpGetMaterialWithSpecificTexture(lbl_8042C4CC, NULL, NULL);
			objRpClumpForAllGeometrysToIgnoreLights(lbl_8042C4CC);
			objRpClumpForAllGeometrysToModulateMaterialColor(lbl_8042C4CC);
		}
	}
	if (lbl_8042C4D0 == NULL) {
		lbl_8042C4D0 = (RpClump*)objPointerReadFromClumpAnim(lbl_80259DA8);
		if (lbl_8042C4D0 != NULL) {
			lbl_8042C4E4 = objRpClumpGetMaterialWithSpecificTexture(lbl_8042C4D0, NULL, NULL);
			objRpClumpForAllGeometrysToIgnoreLights(lbl_8042C4D0);
			objRpClumpForAllGeometrysToModulateMaterialColor(lbl_8042C4D0);
		}
	}
}
