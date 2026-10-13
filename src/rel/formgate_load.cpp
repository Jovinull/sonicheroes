#include "types.h"

// The load hook rel/formgate_register.cpp puts in the formation gate's editor
// record, in the thirteen stage modules that share it. It finds the gate's
// nine textures in the stage's texture dictionary and reads its model: the
// first material that uses one of the textures, then three more, each the next
// one after the last that uses one of the textures from the seventh on. It
// reads the shade and the beam (with the beam's material), and gives the beam
// its scrolling texture when both are there. Last it keeps the positions of
// the model's three markers (the children of its first child frame).
//
// Built without common subexpressions: with them MWCC keeps the address of the
// seventh name from the texture loads for the second search, and keeps the
// names' address across the two searches, where the retail computes each again.

typedef struct RwTexDictionary RwTexDictionary;
typedef struct RwTexture RwTexture;
typedef struct RpMaterial RpMaterial;
typedef struct RpAtomic RpAtomic;

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwMatrix {
	RwV3d right; // 0x00
	u32 flags;   // 0x0C
	RwV3d up;    // 0x10
	u32 pad1;    // 0x1C
	RwV3d at;    // 0x20
	u32 pad2;    // 0x2C
	RwV3d pos;   // 0x30
	u32 pad3;    // 0x3C
} RwMatrix;

typedef struct RwFrame {
	u8 pad00[0x10];
	RwMatrix modelling; // 0x10
} RwFrame;

typedef struct RpClump {
	u8 pad00[0x4];
	RwFrame* frame; // 0x04
} RpClump;

extern "C" char* formgateObjectTextureNames[9];
extern "C" char formgateObjectModelName[];
extern "C" char formgateObjectShadeName[];
extern "C" char formgateObjectBeamName[];
extern "C" char formgateObjectBeamTexture[];
extern "C" char formgateObjectBeamUVName[];
extern "C" RwTexture* formgateObjectTexture0;
extern "C" RwTexture* formgateObjectTexture1;
extern "C" RwTexture* formgateObjectTexture2;
extern "C" RwTexture* formgateObjectTexture3;
extern "C" RwTexture* formgateObjectTexture4;
extern "C" RwTexture* formgateObjectTexture5;
extern "C" RwTexture* formgateObjectTexture6;
extern "C" RwTexture* formgateObjectTexture7;
extern "C" RwTexture* formgateObjectTexture8;
extern "C" RpClump* formgateObjectModel;
extern "C" RpMaterial* formgateObjectMaterial;
extern "C" RpMaterial* formgateObjectMaterials[3];
extern "C" RpClump* formgateObjectShade;
extern "C" RpMaterial* formgateObjectShadeMaterial;
extern "C" RpClump* formgateObjectBeam;
extern "C" RpMaterial* formgateObjectBeamMaterial;
extern "C" RpClump* formgateObjectBeamUV;
extern "C" RpClump* formgateObjectBeamFX;
extern "C" RwV3d formgateObjectPositions[3];
extern RwMatrix* pCurrentMatrix;

extern "C" RwTexture* fn_801A4BBC(RwTexDictionary* dictionary, char* name);
RwTexDictionary* objRwTexDictionaryGetPointer();
RpClump* objPointerReadFromClumpAnim(char* name);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(
    RpClump* clump, RpMaterial* material, char* name);
RpAtomic* objRpClumpGetAtomicWithTexture(RpClump* clump, RpAtomic* after, char* texture);
void AtomicSetCustomFXTexture(RpAtomic* atomic, void* fx);
RwFrame* objRwFrameGetChildFrame(RwFrame* frame, RwFrame* after);

#pragma opt_common_subs off
extern "C" void formgateObjectLoad(void)
{
	RwTexDictionary* dictionary = objRwTexDictionaryGetPointer();
	RwFrame* root;
	RwFrame* child;
	RwMatrix* matrix;

	formgateObjectTexture0 = fn_801A4BBC(dictionary, formgateObjectTextureNames[0]);
	formgateObjectTexture1 = fn_801A4BBC(dictionary, formgateObjectTextureNames[1]);
	formgateObjectTexture2 = fn_801A4BBC(dictionary, formgateObjectTextureNames[2]);
	formgateObjectTexture3 = fn_801A4BBC(dictionary, formgateObjectTextureNames[3]);
	formgateObjectTexture4 = fn_801A4BBC(dictionary, formgateObjectTextureNames[4]);
	formgateObjectTexture5 = fn_801A4BBC(dictionary, formgateObjectTextureNames[5]);
	formgateObjectTexture6 = fn_801A4BBC(dictionary, formgateObjectTextureNames[6]);
	formgateObjectTexture7 = fn_801A4BBC(dictionary, formgateObjectTextureNames[7]);
	formgateObjectTexture8 = fn_801A4BBC(dictionary, formgateObjectTextureNames[8]);

	formgateObjectModel = objPointerReadFromClumpAnim(formgateObjectModelName);
	if (formgateObjectModel != NULL) {
		RpMaterial* last;
		int i;
		int j;

		formgateObjectMaterial = NULL;
		for (j = 0; formgateObjectMaterial == NULL; j++) {
			formgateObjectMaterial = objRpClumpGetMaterialWithSpecificTexture(
			    formgateObjectModel, NULL, formgateObjectTextureNames[j]);
		}
		last = NULL;
		for (i = 0; i < 3; i++) {
			formgateObjectMaterials[i] = NULL;
			for (j = 6; formgateObjectMaterials[i] == NULL; j++) {
				formgateObjectMaterials[i] = objRpClumpGetMaterialWithSpecificTexture(
				    formgateObjectModel, last, formgateObjectTextureNames[j]);
			}
			last = formgateObjectMaterials[i];
		}
	}

	formgateObjectShade = objPointerReadFromClumpAnim(formgateObjectShadeName);
	formgateObjectShadeMaterial
	    = objRpClumpGetMaterialWithSpecificTexture(formgateObjectShade, NULL, NULL);
	formgateObjectBeam         = objPointerReadFromClumpAnim(formgateObjectBeamName);
	formgateObjectBeamMaterial = objRpClumpGetMaterialWithSpecificTexture(
	    formgateObjectBeam, NULL, formgateObjectBeamTexture);
	formgateObjectBeamUV = objPointerReadFromClumpAnim(formgateObjectBeamUVName);
	if (formgateObjectBeamUV != NULL && formgateObjectBeamMaterial != NULL) {
		formgateObjectBeamFX = formgateObjectBeamUV;
		AtomicSetCustomFXTexture(
		    objRpClumpGetAtomicWithTexture(formgateObjectBeam, NULL, formgateObjectBeamTexture),
		    &formgateObjectBeamFX);
	}

	root                       = objRwFrameGetChildFrame(formgateObjectModel->frame, NULL);
	child                      = objRwFrameGetChildFrame(root, NULL);
	matrix                     = &child->modelling;
	formgateObjectPositions[0] = *(matrix == NULL ? &pCurrentMatrix->pos : &matrix->pos);
	child                      = objRwFrameGetChildFrame(root, child);
	matrix                     = &child->modelling;
	formgateObjectPositions[1] = *(matrix == NULL ? &pCurrentMatrix->pos : &matrix->pos);
	child                      = objRwFrameGetChildFrame(root, child);
	matrix                     = &child->modelling;
	formgateObjectPositions[2] = *(matrix == NULL ? &pCurrentMatrix->pos : &matrix->pos);
}
#pragma opt_common_subs reset
