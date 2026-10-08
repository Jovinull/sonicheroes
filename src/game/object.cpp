// Complete object.cpp: 79 surviving GameCube bodies.
// Ten scan-pointer register fields in six instructions require the documented
// tools/fix_object_registers.py step; the remaining source bodies and layout match.
#include "game/object.h"
#include "game/expasm.h"
struct ResourceEntry {
	char name[0x40];
	void* object;
};

struct ResourceRequest {
	char name[0x40];
	void* data;
	u32 size;
	u32 slot;
	void* dictionary;
};

extern "C" {
char* strchr(const char*, s32);
s32 strncmp(const char*, const char*, u32);
char* strcpy(char*, const char*);
void* memset(void*, s32, u32);
s32 sprintf(char*, const char*, ...);
void Exec__22TObjSetDamageCollisionFv(void);
void EndEffTornado__Fv(void);
void InitEffTornado__Fv(void);
void startObjSetDamageCollision__Fv(void);
s32 strcmp(const char*, const char*);
void fn_80150958(void*);
void fn_8020C2D8(void*);
void fn_8011B7CC(void*);
void* fn_80012994(u32);
void fn_800126C8(void*);
void fn_800D0624(void*, void*, u32);
void fn_801A4C84(void*);
void* fn_80198000(s32, s32, void*);
s32 fn_80192F38(void*, s32, s32, s32);
void* fn_80150B88(void*);
void fn_80197ED8(void*, s32);
void fn_800D075C(void*);
void* fn_801471DC(void);
void fn_801471C8(void*);
void fn_8014705C(void*);
void fn_801A46D0(void*);
void* texLoadTexDictionaryFile__FPc(char*);
void* fn_80041FF4(char*);
void* fn_80146EA8(void*);
void* __nw__FUl(u32);
void* CheckFileName__7ONEFILEFi(void*, u32);
void fn_80112718(void);
void* fn_800BC370(void*, u32, void*, void*);
void* OneFileLoadClump__7ONEFILEFUiPv(void*, u32, void*);
void* OneFileLoadHAnimation__7ONEFILEFUiPv(void*, u32, void*);
void* OneFileLoadUVAnim__7ONEFILEFUiPv(void*, u32, void*);
void __dt__7ONEFILEFv(void*, s32);
void fn_8015C728(void*);
void fn_8015C6F8(void*, s32, s32);
void fn_8015C704(void*, s32, s32);
void fn_8015C710(void*, s32, s32, s32);
void fn_8015C720(void*, s32);

void EndEffBrim__Fv(void);
void EndPlayerBarrier__Fv(void);
void fn_8010C0C0(void);
void fn_8010AD10(void);
void fn_801043EC(void);
void EndEffDush__Fv(void);
void fn_800FAB00(void);
void fn_800F6FDC(void);
void EndEffRocketAxel__Fv(void);
void EndEffMuteki__Fv(void);
void EndEffBall__Fv(void);
void EndEffBomb__Fv(void);
void InitEffBomb__Fv(void);
void InitEffBall__Fv(void);
void InitEffMuteki__Fv(void);
void InitEffRocketAxel__Fv(void);
void fn_800F7038(void);
void fn_800FAB54(void);
void InitEffDush__Fv(void);
void fn_80104410(void);
void fn_8010AD48(void);
void fn_8010C108(void);
void InitPlayerBarrier__Fv(void);
void InitEffBrim__Fv(void);

#pragma force_active on
char lbl_80243418[]                     = "OBJ_BOBSLEIGH.DFF";
char lbl_8024342C[]                     = "OBJ_BBS_LAUNCHER.DFF";
char lbl_80243444[]                     = "OBJ_BOBSTOP.DFF";
char lbl_80243454[]                     = "OBJ_ROLLDOOR.DFF";
char lbl_80243468[]                     = "OBJ_SWB.DFF";
char lbl_80243474[]                     = "OBJ_TARGET.DFF";
char lbl_80243484[]                     = "OBJ_WEIGHT.DFF";
char lbl_80243494[]                     = "OBJ_WEIGHT_BROKEN.DFF";
char lbl_802434AC[]                     = "EF_RDOOR.DFF";
__declspec(export) char* lbl_802434BC[] = { lbl_80243418, lbl_8024342C, lbl_80243444, lbl_80243454,
	lbl_80243468, lbl_80243474, lbl_80243484, lbl_80243494, lbl_802434AC };
char lbl_802434E0[]                     = "OBJ_DSHR.DFF";
char lbl_802434F0[]                     = "OBJ_DUSHP.DFF";
char lbl_80243500[]                     = "EFF_BOB_ON.DFF";
char lbl_80243510[]                     = "EF_FIBALL.DFF";
char lbl_80243520[]                     = "EF_FCHG_BEAM.DFF";
char lbl_80243534[]                     = "EF_FLOWARP.DFF";
char lbl_80243544[]                     = "OBJ_JBOARD.DFF";
__declspec(export) char* lbl_80243554[] = { lbl_802434E0, lbl_802434F0, lbl_80243500, lbl_80243510,
	lbl_80243520, lbl_80243534, lbl_80243544 };
extern char lbl_802435A0[];
extern char lbl_802435BC[];
extern char lbl_802435C8[];

char lbl_8042B228[] = "DFF";
char lbl_8042B22C[] = "ANM";
char lbl_8042B230[] = "UVB";

ResourceEntry lbl_802FF5E0[0x100];
u8 lbl_803039E0[0x18];
ResourceRequest lbl_803039F8[10];
void* lbl_8042C2A8;
#pragma force_active reset
}

class ONEFILE
{
	u8 body[0x58];

public:
	ONEFILE(char*, s32);
};
void* operator new(unsigned long);

static RpGeometry* pCurrentGeometry;
static RpMaterial* pSkipMaterial;
static RpAtomic *pSkipAtomic, *pobjAtomic;
static char* pobjTextureName;
static RpGeometry* pSearchGeometry;
static RwFrame* pSkipFrame;
static s32 order_Frame;
static RwFrame* pSerchingFrame;
static u8 idBoneToHide;
static s32 pCurrentMaterialNum;
static OBJ_MoveOnGround* pCurrentMOG;
RwV3d OBJ_MoveOnGround::vMove;
// Rendering/material portion of object.cpp. Included into the complete TU.
#include "game/object.h"
extern "C" {
extern u8 lbl_803039E0[0x18];
extern void* lbl_8042C208;
extern u8 lbl_802D5E80[];
RpAtomic* fn_801491A8(RpAtomic*);
RpMaterial* fn_80149274(RpMaterial*, s32);
RpMaterial* fn_80149D7C(RpMaterial*, RwMatrix*, RwMatrix*);
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpGeometry* fn_801527A4(RpGeometry*, RpMaterial* (*)(RpMaterial*, void*), void*);
void fn_8011B78C(RpUVAnimAnimation*, RwMatrix*);
RwMatrix* fn_8019565C(RwMatrix*);
RpAtomic* fn_8014F1B0(RpAtomic*);
RwMatrix* fn_8019E8EC(RwFrame*);
void SubVectorReturnToVector__FPC5RwV3dPC5RwV3dP5RwV3d(RwV3d*, void*, RwV3d*);
void fn_8014F854(RpAtomic*);
void* __nwa__FUl(u32);
void __dla__FPv(void*);
void fn_8015C878(RpGeometry*, void*);
void fn_800B8804(RpAtomic*);
void SetCurrentNum__6CLIGHTFSc(void*, s8);
void SetLightRegular__6CLIGHTFSc(void*, u8);
RpGeometry* fn_80152828(RpGeometry*, s32);
RpGeometry* fn_80152880(RpGeometry*);
void* fn_80226468(RpGeometry*);
u8* fn_80226578(void*);
RwFrame* fn_8019EB10(RwFrame*, RwFrame* (*)(RwFrame*, void*), void*);
RpUVAnimAnimation* fn_8011B874(RwStream*);
void fn_8011BC20(RpUVAnimAnimation*);
RpUVAnimAnimation* fn_8011B654(RwStream*);
}
static RpMaterial* MaterialSetEffect(RpMaterial*, void*);
static RpMaterial* SetUVAnimData(RpMaterial*, void*);
RpAtomic* AtomicSetCustomFXTexture(RpAtomic*, void*);
static RpMaterial* MaterialSetCustomFXTexture(RpMaterial*, void*);
static RpAtomic* objCallbackRpAtomicToSetRenderCallbackToCheckFromCamera(RpAtomic*, void*);
static RpAtomic* objCallbackRpAtomicCheckFromCamera(RpAtomic*);
static RpAtomic* objRpAtomicCallBackRenderNearCamera(RpAtomic*, void*);
static inline RpAtomic* objRpAtomicCallBackRenderNearCamera(RpAtomic*, f32, void*);
static RpMaterial* objRpMaterialResetFlagsAndColor(RpMaterial*, void*);
static RpMaterial* objRpMaterialSaveFlagsAndColor(RpMaterial*, void*);
s32 objRpAtomicCheckFromCamera(RpAtomic*, f32);
static RpAtomic* objCallbackRpAtomicToSetRenderCallbackToOptimizeShadow(RpAtomic*, void*);
static RpAtomic* objCallbackRpAtomicRenderToOptimizeShadow(RpAtomic*);
static RpAtomic* objCallbackRpAtomicToSetRenderCallbackToUseLight(RpAtomic*, void*);
static RpAtomic* objCallbackRpAtomicRenderToUseLight(RpAtomic*);
static RpAtomic* objCallbackRpAtomicToAffectAlphaToColor(RpAtomic*, void*);
static RpAtomic* objRpAtomicCallbackSetAtomicFlagToHide2(RpAtomic*, void*);
static RpAtomic* objRpAtomicCallbackSetAtomicFlagToHide(RpAtomic*, void*);
static RpAtomic* objRpAtomicCallbackSetAtomicFlagToRender(RpAtomic*, void*);
static RpAtomic* objRpAtomicCallbackSetGeometryFlagToModulateMaterialColor(RpAtomic*, void*);
static RpAtomic* objRpAtomicCallbackSetGeometryFlagToIgnoreLights(RpAtomic*, void*);
static RpAtomic* objRpAtomicForAllMaterialsToChangeMaterialColor(RpAtomic*, void*);
void objRpAtomicForAllMaterialsToChangeMaterialColor(RpAtomic*, RwRGBAReal*);
static RpMaterial* objRpMaterialCallbackToChangeMaterialColor(RpMaterial*, void*);
s32 objRwFrameSerchChildFrame(RwFrame*, RwFrame*);

// Movement fragment. External ABI views below are restricted to GC-observed fields.
struct POLYDATA {
	u16 vertexIndexNo[3], neighbor[3];
	RwV3d norm;
	u32 attribute;
	u16 groupIndexNo;
	u8 dummy[2];
};
struct ColliPolyLinearListNode {
	u16 no;
	s16 on_edge;
	RwV3d ansVec, coliPos, pushVec;
	ColliPolyLinearListNode *prevNode, *nextNode;
};
struct ColliPolyLinearList {
	s32 numNode;
	ColliPolyLinearListNode *topNode, *bottomNode;
};
struct ObjectOctreeView {
	void* nodeData;
	POLYDATA* polygonData;
};
struct ObjectTaskView {
	s16 mode, modeLast, smode, flag;
	u16 wtimer;
	sAngle ang;
	RwV3d pos, scl;
};
struct ObjectPlayerWorkView {
	s8 playerno, characterno;
};
struct ObjectPlayerAngleView {
	u8 unknown_000[0x644];
	sAngle angle_644;
};
extern "C" {
extern ObjectOctreeView* lbl_8042C150;
extern ObjectTaskView* lbl_802AD090[8];
extern ObjectPlayerWorkView* lbl_802AD0D0[8];
extern ObjectPlayerAngleView* lbl_802AD070[8];
extern RwV3d AxisX, AxisY, AxisZ;
extern u8 lbl_8042C1BC;
s32 fn_8003E244(void*, s32, u8, RwV3d*, sAngle*);
ColliPolyLinearList* DetectSphereCollisionWithPolygons__6OCTREEFP5RwV3dfPFP8POLYDATA_i(
    ObjectOctreeView*, RwV3d*, f32, s32 (*)(POLYDATA*));
ColliPolyLinearList*
DetectMovingSphereCollisionWithPolygons__6OCTREEFP5RwV3dfP5RwV3dP14ENUM_CL_MOVINGPFP8POLYDATA_i(
    ObjectOctreeView*, RwV3d*, f32, RwV3d*, s32*, s32 (*)(POLYDATA*));
void OmitSameSurfacePolygons__6OCTREEFP19ColliPolyLinearList(
    ObjectOctreeView*, ColliPolyLinearList*);
void __dt__19ColliPolyLinearListFv(ColliPolyLinearList*, s32);
f32 DistanceP2PL__FPC5RwV3dPC5RwV3dP5RwV3d(RwV3d*, RwV3d*, RwV3d*);
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
RwMatrix* fn_80195790(RwMatrix*, const RwV3d*, f32, f32, s32);
RwV3d* fn_8019947C(RwV3d*, const RwV3d*, s32, const RwMatrix*);
f32 fn_801990E0(RwV3d*, const RwV3d*);
f32 fn_801991B4(const RwV3d*);
f64 atan2(f64, f64);
f64 asin(f64);
f64 __fabs(f64);
}
// Root should emit these at whole-TU original definition order.

static s32 objCallbackCheckCollisionMoving(POLYDATA*);

#include "game/object.h"
extern "C" {
RwFrame* fn_8019EB10(RwFrame*, RwFrame* (*)(RwFrame*, void*), void*);
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpGeometry* fn_801527A4(RpGeometry*, RpMaterial* (*)(RpMaterial*, void*), void*);
RwTexDictionary* fn_801A4778(RwTexDictionary*, RwTexture* (*)(RwTexture*, void*), void*);
void fn_801B27EC(RwTexture*, f32*, s32*, s32*, s32*);
s32 fn_801A1844(RwRaster*);
void fn_801B2620(RwTexture*, f32, s32, s32, s32);
s32 strcmp(const char*, const char*);
void* fn_80146BC8(RpMaterial*, s32);
u32 fn_801468B4(void*);
RwTexture* fn_80146990(void*, u32);
s32 fn_80149480(RpMaterial*);
RwTexture* fn_80149810(RpMaterial*);
RwTexture* fn_80149A6C(RpMaterial*);
RwTexture* fn_80149CE0(RpMaterial*);
}
// Defined once with the complete unit's storage inventory.
static RwFrame* objCallbackSerchFrame(RwFrame*, void*);
static RwFrame* objCallbackRwFrameGetChildFrame(RwFrame*, void*);
static RwFrame* objCallbackGetFrame(RwFrame*, void*);
static RwTexture* objCallbackChangeTextureFilterMode(RwTexture*, void*);
static RpAtomic* objRpClumpGetAtomicWithGeometry(RpAtomic*, void*);
static RpAtomic* objCallbackGetAtomicWithTexture(RpAtomic*, void*);
static RpMaterial* objCheckTextureRpMaterialCallback(RpMaterial*, void*);
static RpAtomic* objCallbackGetAtomic(RpAtomic*, void*);
static RpMaterial* objCallBackGetRpMaterialWithTexture(RpMaterial*, void*);
static RpAtomic* objRpAtomicForAllMaterialsWithSpecificTexture(RpAtomic*, void*);
static RpMaterial* objCheckCallbackForSpecificMaterialWithTexture(RpMaterial*, void*);

struct ResourceLoopState {
	ResourceEntry* entry;

	ResourceLoopState()
	    : entry(lbl_802FF5E0)
	{
	}
};
static RpAtomic* AtomicSetMaterialEffect(RpAtomic* atomic, void* data);
static RpMaterial* MaterialSetEffect(RpMaterial* material, void*);
void SetClumpCustomFXTexture(RpClump* clump, UVFXInfo* info);
RpAtomic* SetAtomicCustomFXData(RpAtomic* atomic, void* data);
static RpMaterial* SetUVAnimData(RpMaterial* material, void* data);
RpAtomic* AtomicSetCustomFXTexture(RpAtomic* atomic, void* data);
static RpMaterial* MaterialSetCustomFXTexture(RpMaterial* material, void* data);
f32 objRpUVAnimAnimationGetTotalFrame(RpUVAnimAnimation* animation);
// GC additionally advances position; PS2 metadata exposes only velocity.
void objCalculateVelocityAsCannonBall(RwV3d* velocity, RwV3d* position);
void objCalculateVelocityAsCannonBall(RwV3d* pVec);
static s32 objCallbackCheckCollisionMoving(POLYDATA* pData);
void objRpAtomicToSetRenderCallbackToCheckFromCamera(RpAtomic* atomic, f32 distance);
void objRpClumpForAllAtomicsToSetRenderCallbackToCheckFromCamera(RpClump* clump, f32 distance);
static RpAtomic* objCallbackRpAtomicToSetRenderCallbackToCheckFromCamera(
    RpAtomic* atomic, void* data);
static RpAtomic* objCallbackRpAtomicCheckFromCamera(RpAtomic* atomic);
void objRpClumpForAllAtomicsRenderNearCamera(RpClump* clump);
static RpAtomic* objRpAtomicCallBackRenderNearCamera(RpAtomic* atomic, void*);
void objRpAtomicRenderNearCamera(RpAtomic* atomic);
void objRpAtomicRenderNearCamera(RpAtomic* atomic, f32 distance, void* callback);
static inline RpAtomic* objRpAtomicCallBackRenderNearCamera(
    RpAtomic* atomic, f32 distance, void* callback);
static RpMaterial* objRpMaterialResetFlagsAndColor(RpMaterial* material, void* data);
static RpMaterial* objRpMaterialSaveFlagsAndColor(RpMaterial* material, void* data);
s32 objRpAtomicCheckFromCamera(RpAtomic* atomic, f32 distance);
static RpAtomic* objRpAtomicCallbackSetCompressedGeometry(RpAtomic* atomic, void*);
void objRpClumpForAllAtomicsToSetRenderCallbackToOptimizeShadow(RpClump* clump);
static RpAtomic* objCallbackRpAtomicToSetRenderCallbackToOptimizeShadow(RpAtomic* atomic, void*);
static RpAtomic* objCallbackRpAtomicRenderToOptimizeShadow(RpAtomic* atomic);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump* clump, u32 light);
static RpAtomic* objCallbackRpAtomicToSetRenderCallbackToUseLight(RpAtomic* atomic, void* data);
static RpAtomic* objCallbackRpAtomicRenderToUseLight(RpAtomic* atomic);
void objRpClumpForAllGeometriesToAffectAlphaToColor(RpClump* clump);
static RpAtomic* objCallbackRpAtomicToAffectAlphaToColor(RpAtomic* atomic, void*);
void objRpClumpForTheAtomicsToHide(RpClump* clump, RwFrame* frame, u32 bone);
static RpAtomic* objRpAtomicCallbackSetAtomicFlagToHide2(RpAtomic* atomic, void* data);
void objRpClumpForAllAtomicsToHide(RpClump* clump);
static RpAtomic* objRpAtomicCallbackSetAtomicFlagToHide(RpAtomic* atomic, void*);
void objRpClumpForAllAtomicsToRender(RpClump* clump);
static RpAtomic* objRpAtomicCallbackSetAtomicFlagToRender(RpAtomic* atomic, void*);
s32 objRpHAnimHierarchyFindFrameFromBoneID(RpHAnimHierarchy* hierarchy, s32 id);
void objRpClumpForAllGeometrysToModulateMaterialColor(RpClump* clump);
static RpAtomic* objRpAtomicCallbackSetGeometryFlagToModulateMaterialColor(RpAtomic* atomic, void*);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);
static RpAtomic* objRpAtomicCallbackSetGeometryFlagToIgnoreLights(RpAtomic* atomic, void*);
void objRpAtomicForAllMaterialsToChangeMaterialColor(RpAtomic* atomic, RwRGBAReal* color);
void objRpClumpForAllMaterialsToChangeMaterialColor(RpClump* clump, RwRGBAReal* color);
static RpAtomic* objRpAtomicForAllMaterialsToChangeMaterialColor(RpAtomic* atomic, void* color);
static RpMaterial* objRpMaterialCallbackToChangeMaterialColor(RpMaterial* material, void* data);
RpUVAnimAnimation* objRpUVAnimAnimationStreamRead(RwStream* stream);
s32 objRpAtomicChangeUV(RpAtomic* atomic, RwTexCoords* offset);
s32 objRwFrameSerchChildFrame(RwFrame* frame, RwFrame* target);
static RwFrame* objCallbackSerchFrame(RwFrame* frame, void* data);
RwFrame* objRwFrameGetFrame(RwFrame* frame, s32 order);
static RwFrame* objCallbackRwFrameGetChildFrame(RwFrame* frame, void* data);
RwFrame* objRwFrameGetChildFrame(RwFrame* frame, RwFrame* skip);
static RwFrame* objCallbackGetFrame(RwFrame* frame, void* data);
s32 objChangeTextureFilterMode(RwTexDictionary* dictionary, RwTextureFilterMode mode);
static RwTexture* objCallbackChangeTextureFilterMode(RwTexture* texture, void* data);
RpAtomic* objRpClumpGetAtomicWithGeometry(RpClump* clump, RpAtomic* skip, RpGeometry* geometry);
static RpAtomic* objRpClumpGetAtomicWithGeometry(RpAtomic* atomic, void* data);
RpAtomic* objRpClumpGetAtomicWithTexture(RpClump* clump, RpAtomic* skip, char* name);
static RpAtomic* objCallbackGetAtomicWithTexture(RpAtomic* atomic, void* data);
static RpMaterial* objCheckTextureRpMaterialCallback(RpMaterial* material, void* data);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* skip);
static RpAtomic* objCallbackGetAtomic(RpAtomic* atomic, void* data);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture(RpClump* clump, RpMaterial* skip, char* name);
static RpMaterial* objCallBackGetRpMaterialWithTexture(RpMaterial* material, void* data);
void objRpClumpForAllMaterialsWithSpecificTexture(RpClump* clump, OBJ_SearchMaterials* search);
static RpAtomic* objRpAtomicForAllMaterialsWithSpecificTexture(RpAtomic* atomic, void* data);
static RpMaterial* objCheckCallbackForSpecificMaterialWithTexture(RpMaterial* material, void* data);
static inline s32 findResourceRequest(char* name);
void objReleaseClumpAnimStoredInARAMFromMainRAM(void);
static inline s32 findResourceEntry(char* name);
void* objPointerReadFromClumpAnim(char* name);
RwTexDictionary* objRwTexDictionaryGetPointer(void);
void objReleaseCommonObjectTextures(void);
void objLoadCommonObjectTextures(void);
static const RwRGBAReal nearCameraColor = { -1.0f, -1.0f, -1.0f, 0.25f };
s32 OBJ_ReplacePlayer::objSetPlayerPosition(s32 pno, u8 frame, RwV3d* pos, sAngle* ang)
{
	if (pno >= 8)
		return 0;
	ObjectTaskView* ptwp = lbl_802AD090[pno];
	if (!ptwp)
		return 0;
	if (frame == 0) {
		if (ang)
			ptwp->ang = *ang;
		if (pos)
			ptwp->pos = *pos;
	}
	return fn_8003E244(&lbl_8042C1BC, pno, frame, pos, ang);
}

s32 OBJ_ReplacePlayer::objSetPlayerHandlingPosition(s32 pno, u8 frame, RwV3d* pos, sAngle* ang)
{
	ObjectTaskView* ptwp = lbl_802AD090[pno];
	if (!ptwp)
		return 0;
	if (frame == 0) {
		if (ang)
			ptwp->ang = *ang;
		if (pos) {
			static f32 lengthByHands[12]
			    = { 8.5f, 9.0f, 6.4f, 9.0f, 19.0f, 8.5f, 9.0f, 25.0f, 6.3f, 8.5f, 22.0f, 6.2f };
			RwV3d offset_Temp;
			RwMatrix mat_Temp;
			s32 cno       = lbl_802AD0D0[pno]->characterno;
			offset_Temp.x = 0.0f;
			offset_Temp.y = -lengthByHands[cno];
			offset_Temp.z = 0.0f;
			f32 sn        = fn_800D7B00(-0x4000 - ptwp->ang.y);
			fn_80195790(&mat_Temp, &AxisY, 1.0f - fn_800D7AE4(-0x4000 - ptwp->ang.y), sn, 0);
			s32 angz;
			s32 angx = lbl_802AD070[pno]->angle_644.x;
			angz     = -lbl_802AD070[pno]->angle_644.z;
			sn       = fn_800D7B00(angz);
			fn_80195790(&mat_Temp, &AxisZ, 1.0f - fn_800D7AE4(angz), sn, 1);
			sn = fn_800D7B00(-angx);
			fn_80195790(&mat_Temp, &AxisX, 1.0f - fn_800D7AE4(-angx), sn, 1);
			sn = fn_800D7B00(ptwp->ang.x);
			fn_80195790(&mat_Temp, &AxisX, 1.0f - fn_800D7AE4(ptwp->ang.x), sn, 2);
			sn = fn_800D7B00(ptwp->ang.z);
			fn_80195790(&mat_Temp, &AxisZ, 1.0f - fn_800D7AE4(ptwp->ang.z), sn, 2);
			fn_8019947C(&offset_Temp, &offset_Temp, 1, &mat_Temp);
			ptwp->pos.x = pos->x + offset_Temp.x;
			ptwp->pos.y = pos->y + offset_Temp.y;
			ptwp->pos.z = pos->z + offset_Temp.z;
		}
	}
	return fn_8003E244(&lbl_8042C1BC, pno, frame, pos, ang);
}

void objLoadCommonObjectTextures(void)
{
	fn_8015C728(lbl_803039E0);
	fn_8015C6F8(lbl_803039E0, 3, 6);
	fn_8015C704(lbl_803039E0, 1, 0);
	fn_8015C710(lbl_803039E0, 1, 3, 10);
	fn_8015C720(lbl_803039E0, 3);
	if (lbl_8042C2A8 == NULL) {
		char path[0x20];
		sprintf(path, lbl_802435A0);
		lbl_8042C2A8 = texLoadTexDictionaryFile__FPc(path);
		if (lbl_8042C2A8 == NULL)
			return;
		fn_801A4778((RwTexDictionary*)lbl_8042C2A8, objCallbackChangeTextureFilterMode, (void*)6);
	}
	void* workspace;
	u32 i;
	{
		void* material;
		void* materialData = NULL;
		material           = fn_80041FF4(lbl_802435BC);
		if (material != NULL) {
			if (fn_80192F38(material, 0x21, 0, 0) != 0)
				materialData = fn_80146EA8(material);
			fn_80197ED8(material, 0);
		}
		if (materialData != NULL)
			fn_801471C8(materialData);
	}
	ONEFILE* archive = new ONEFILE(lbl_802435C8, 0);
	if (archive != NULL) {
		fn_801A4C84(lbl_8042C2A8);
		workspace                = fn_80012994(0x25800);
		ResourceRequest* request = lbl_803039F8;
		for (u32 i = 0; i < 10; i++)
			request[i].data = NULL;
		request = lbl_803039F8;
		for (i = 0; i < 0x100; i++) {
			char* source = (char*)CheckFileName__7ONEFILEFi(archive, i);
			if (source == NULL) {
				memset(&lbl_802FF5E0[i], 0, 0x40);
				lbl_802FF5E0[i].object = NULL;
				continue;
			}
			strcpy(lbl_802FF5E0[i].name, source);
			char* extension = strchr(lbl_802FF5E0[i].name, '.');
			if (extension == NULL)
				continue;
			fn_80112718();
			if (strncmp(extension + 1, lbl_8042B228, 3) == 0) {
				s32 special = FALSE;
				for (u32 j = 0; j < 9; j++)
					if (strcmp(lbl_802FF5E0[i].name, lbl_802434BC[j]) == 0) {
						special = TRUE;
						break;
					}
				if (special) {
					lbl_802FF5E0[i].object = NULL;
					request->data          = fn_800BC370(archive, i, workspace, &request->size);
					request->slot          = i;
					strcpy(request->name, lbl_802FF5E0[i].name);
					lbl_802FF5E0[i].name[0] = 0;
					request->dictionary     = lbl_8042C2A8;
					request++;
				} else {
					lbl_802FF5E0[i].object = OneFileLoadClump__7ONEFILEFUiPv(archive, i, workspace);
					for (u32 j = 0; j < 7; j++)
						if (strcmp(lbl_802FF5E0[i].name, lbl_80243554[j]) == 0) {
							fn_8014FFBC(
							    (RpClump*)lbl_802FF5E0[i].object, AtomicSetMaterialEffect, 0);
							break;
						}
				}
				if (lbl_802FF5E0[i].object != NULL)
					fn_8014FFBC((RpClump*)lbl_802FF5E0[i].object,
					    objRpAtomicCallbackSetCompressedGeometry, 0);
			} else if (strncmp(extension + 1, lbl_8042B22C, 3) == 0)
				lbl_802FF5E0[i].object
				    = OneFileLoadHAnimation__7ONEFILEFUiPv(archive, i, workspace);
			else if (strncmp(extension + 1, lbl_8042B230, 3) == 0)
				lbl_802FF5E0[i].object = OneFileLoadUVAnim__7ONEFILEFUiPv(archive, i, workspace);
			else
				lbl_802FF5E0[i].object = NULL;
		}
		if (workspace != NULL)
			fn_800126C8(workspace);
		__dt__7ONEFILEFv(archive, 1);
	} else
		memset(lbl_802FF5E0, 0, 0x4400);
	InitEffTornado__Fv();
	InitEffBomb__Fv();
	InitEffBall__Fv();
	InitEffMuteki__Fv();
	InitEffRocketAxel__Fv();
	fn_800F7038();
	fn_800FAB54();
	InitEffDush__Fv();
	fn_80104410();
	fn_8010AD48();
	fn_8010C108();
	InitPlayerBarrier__Fv();
	InitEffBrim__Fv();
	startObjSetDamageCollision__Fv();
}

void objReleaseCommonObjectTextures(void)
{
	Exec__22TObjSetDamageCollisionFv();
	EndEffBrim__Fv();
	EndPlayerBarrier__Fv();
	fn_8010C0C0();
	fn_8010AD10();
	fn_801043EC();
	EndEffDush__Fv();
	fn_800FAB00();
	fn_800F6FDC();
	EndEffRocketAxel__Fv();
	EndEffMuteki__Fv();
	EndEffBall__Fv();
	EndEffBomb__Fv();
	EndEffTornado__Fv();
	for (s32 i = 0; i < 0x100; i++) {
		char* extension = strchr(lbl_802FF5E0[i].name, '.');
		if (extension != NULL) {
			if (strncmp(extension + 1, lbl_8042B228, 3) == 0)
				fn_80150958(lbl_802FF5E0[i].object);
			else if (strncmp(extension + 1, lbl_8042B22C, 3) == 0)
				fn_8020C2D8(lbl_802FF5E0[i].object);
			else if (strncmp(extension + 1, lbl_8042B230, 3) == 0)
				fn_8011B7CC(lbl_802FF5E0[i].object);
			lbl_802FF5E0[i].object = NULL;
		}
	}
	for (u32 i = 0; i < 10; i++)
		if (lbl_803039F8[i].data != NULL)
			fn_800D075C(lbl_803039F8[i].data);
	void* object = fn_801471DC();
	if (object != NULL) {
		fn_801471C8(NULL);
		fn_8014705C(object);
	}
	if (lbl_8042C2A8 != NULL) {
		fn_801A46D0(lbl_8042C2A8);
		lbl_8042C2A8 = NULL;
	}
}

RwTexDictionary* objRwTexDictionaryGetPointer(void)
{
	return (RwTexDictionary*)lbl_8042C2A8;
}

void* objPointerReadFromClumpAnim(char* name)
{
	void* result = NULL;
	s32 i        = findResourceEntry(name);
	if (i != -1) {
		result = lbl_802FF5E0[i].object;
		goto done;
	}

	i = findResourceRequest(name);
	if (i != -1) {
		ResourceRequest* request = &lbl_803039F8[i];
		name                     = (char*)request->data;
		void** objectBase        = &lbl_802FF5E0[0].object;
		void* loaded;
		if (*(void**)((u8*)objectBase + request->slot * sizeof(ResourceEntry)) != NULL) {
			loaded = *(void**)((u8*)objectBase + request->slot * sizeof(ResourceEntry));
		} else if (name != NULL) {
			void* input;
			void* expanded = fn_80012994(0x19000);
			input          = fn_80012994(request->size);
			fn_800D0624(input, name, request->size);
			s32 expandedSize = Expand2(input, expanded);
			struct {
				void* start;
				u32 length;
			} streamArgs;
			streamArgs.length = expandedSize;
			streamArgs.start  = expanded;
			fn_801A4C84(request->dictionary);
			void* stream = fn_80198000(3, 1, &streamArgs);
			if (fn_80192F38(stream, 0x10, 0, 0) != 0)
				*(void**)((u8*)objectBase + request->slot * sizeof(ResourceEntry))
				    = fn_80150B88(stream);
			fn_80197ED8(stream, 0);
			fn_800126C8(input);
			fn_800126C8(expanded);
			strcpy(lbl_802FF5E0[request->slot].name, request->name);
			if (*(void**)((u8*)objectBase + request->slot * sizeof(ResourceEntry)) != NULL)
				fn_8014FFBC(*(RpClump**)((u8*)objectBase + request->slot * sizeof(ResourceEntry)),
				    objRpAtomicCallbackSetCompressedGeometry, 0);
			loaded = *(void**)((u8*)objectBase + request->slot * sizeof(ResourceEntry));
		} else {
			loaded = NULL;
		}
		result = loaded;
	}
done:
	return result;
}

static inline s32 findResourceEntry(char* name)
{
	ResourceEntry* entry;
	s32 i = 0;
	entry = lbl_802FF5E0;
	while (i < 0x100) {
		if (strcmp(entry->name, name) == 0)
			return i;
		entry++;
		i++;
	}
	return -1;
}

void objReleaseClumpAnimStoredInARAMFromMainRAM(void)
{
	s32 i = 0;
	ResourceLoopState state;
	do {
		u32 found = findResourceRequest(state.entry->name);
		if ((s32)found != -1) {
			char* extension = strchr(state.entry->name, '.');
			if (extension != NULL) {
				if (strncmp(extension + 1, lbl_8042B228, 3) == 0)
					fn_80150958(state.entry->object);
				else if (strncmp(extension + 1, lbl_8042B22C, 3) == 0)
					fn_8020C2D8(state.entry->object);
				else if (strncmp(extension + 1, lbl_8042B230, 3) == 0)
					fn_8011B7CC(state.entry->object);
				state.entry->object  = NULL;
				state.entry->name[0] = 0;
			}
		}
		state.entry++;
		i++;
	} while (i < 0x100);
}

static inline s32 findResourceRequest(char* name)
{
	ResourceRequest* request;
	u32 i   = 0;
	request = lbl_803039F8;
	while (i < 10) {
		if (strcmp(request->name, name) == 0)
			return i;
		request++;
		i++;
	}
	return -1;
}

static RpMaterial* objCheckCallbackForSpecificMaterialWithTexture(RpMaterial* material, void* data)
{
	OBJ_SearchMaterials* search = (OBJ_SearchMaterials*)data;
	if (!search)
		return material;
	RwTexture* texture = material->texture;
	if (!search->pTextureName) {
		if (!texture) {
			pCurrentGeometry->flags |= 0x40;
			if (search->callback)
				search->callback(material, search);
		}
	} else if (texture && strcmp(search->pTextureName, texture->name) == 0) {
		pCurrentGeometry->flags |= 0x40;
		if (search->callback)
			search->callback(material, search);
	} else {
		void* animation = fn_80146BC8(material, 6);
		if (animation) {
			pCurrentGeometry->flags |= 0x40;
			u32 count = fn_801468B4(animation);
			for (u32 i = 0; i < count; ++i) {
				if (strcmp(search->pTextureName, fn_80146990(animation, i)->name) == 0
				    && search->callback)
					search->callback(material, search);
			}
		} else if (texture) {
			s32 effect               = fn_80149480(material);
			RwTexture* effectTexture = NULL;
			switch (effect) {
				case 1:
					effectTexture = fn_80149810(material);
					break;
				case 2:
					effectTexture = fn_80149A6C(material);
					break;
				case 4:
					effectTexture = fn_80149CE0(material);
					break;
			}
			if (effectTexture && strcmp(search->pTextureName, effectTexture->name) == 0) {
				pCurrentGeometry->flags |= 0x40;
				if (search->callback)
					search->callback(material, search);
			}
		}
	}
	return material;
}

static RpAtomic* objRpAtomicForAllMaterialsWithSpecificTexture(RpAtomic* atomic, void* data)
{
	pCurrentGeometry = atomic->geometry;
	fn_801527A4(pCurrentGeometry, objCheckCallbackForSpecificMaterialWithTexture, data);
	pCurrentGeometry->flags |= 0x40;
	return atomic;
}

void objRpClumpForAllMaterialsWithSpecificTexture(RpClump* clump, OBJ_SearchMaterials* search)
{
	fn_8014FFBC(clump, objRpAtomicForAllMaterialsWithSpecificTexture, search);
}

static RpMaterial* objCallBackGetRpMaterialWithTexture(RpMaterial* material, void* data)
{
	if (!data)
		return material;
	OBJ_SearchMaterials* search = (OBJ_SearchMaterials*)data;
	RwTexture* texture          = material->texture;
	RpMaterial** found          = (RpMaterial**)search->pData;
	if (!search->pTextureName) {
		if (!texture) {
			if (!pSkipMaterial) {
				*found        = material;
				pSkipMaterial = material;
			} else if (pSkipMaterial == material)
				pSkipMaterial = NULL;
		}
	} else if (texture && strcmp(search->pTextureName, texture->name) == 0) {
		if (!pSkipMaterial) {
			*found        = material;
			pSkipMaterial = material;
		} else if (pSkipMaterial == material)
			pSkipMaterial = NULL;
	} else {
		void* animation = fn_80146BC8(material, 6);
		if (animation) {
			u32 count = fn_801468B4(animation);
			for (u32 i = 0; i < count; ++i) {
				if (strcmp(search->pTextureName, fn_80146990(animation, i)->name) == 0) {
					if (!pSkipMaterial) {
						*found        = material;
						pSkipMaterial = material;
					} else if (pSkipMaterial == material)
						pSkipMaterial = NULL;
				}
			}
		} else if (texture) {
			s32 effect               = fn_80149480(material);
			RwTexture* effectTexture = NULL;
			switch (effect) {
				case 1:
					effectTexture = fn_80149810(material);
					break;
				case 2:
					effectTexture = fn_80149A6C(material);
					break;
				case 4:
					effectTexture = fn_80149CE0(material);
					break;
			}
			if (effectTexture && strcmp(search->pTextureName, effectTexture->name) == 0) {
				if (!pSkipMaterial) {
					*found        = material;
					pSkipMaterial = material;
				} else if (pSkipMaterial == material)
					pSkipMaterial = NULL;
			}
		}
	}
	return material;
}

RpMaterial* objRpClumpGetMaterialWithSpecificTexture(RpClump* clump, RpMaterial* skip, char* name)
{
	RpMaterial* found = NULL;
	OBJ_SearchMaterials search;
	search.callback     = objCallBackGetRpMaterialWithTexture;
	search.pTextureName = name;
	search.pData        = &found;
	pSkipMaterial       = skip;
	fn_8014FFBC(clump, objRpAtomicForAllMaterialsWithSpecificTexture, &search);
	return found;
}

static RpAtomic* objCallbackGetAtomic(RpAtomic* atomic, void* data)
{
	RpAtomic** found = (RpAtomic**)data;
	if (!*found) {
		if (pSkipAtomic == atomic)
			pSkipAtomic = NULL;
		else if (!pSkipAtomic) {
			*found      = atomic;
			pSkipAtomic = atomic;
		}
	}
	return atomic;
}

RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* skip)
{
	RpAtomic* found = NULL;
	pSkipAtomic     = skip;
	if (clump)
		fn_8014FFBC(clump, objCallbackGetAtomic, &found);
	return found;
}

static RpMaterial* objCheckTextureRpMaterialCallback(RpMaterial* material, void* data)
{
	RpAtomic** found = (RpAtomic**)data;
	if (!material->texture && !pobjTextureName) {
		*found      = pobjAtomic;
		pSkipAtomic = pobjAtomic;
	} else if (pobjTextureName && material->texture
	    && strcmp(pobjTextureName, material->texture->name) == 0) {
		*found      = pobjAtomic;
		pSkipAtomic = pobjAtomic;
	} else {
		void* animation = fn_80146BC8(material, 6);
		if (animation) {
			u32 count = fn_801468B4(animation);
			for (u32 i = 0; i < count; ++i) {
				if (strcmp(pobjTextureName, fn_80146990(animation, i)->name) == 0) {
					*found      = pobjAtomic;
					pSkipAtomic = pobjAtomic;
				}
			}
		}
	}
	return material;
}

static RpAtomic* objCallbackGetAtomicWithTexture(RpAtomic* atomic, void* data)
{
	RpAtomic** found = (RpAtomic**)data;
	if (!*found) {
		if (pSkipAtomic == atomic)
			pSkipAtomic = NULL;
		else if (!pSkipAtomic) {
			pCurrentGeometry = atomic->geometry;
			pobjAtomic       = atomic;
			fn_801527A4(pCurrentGeometry, objCheckTextureRpMaterialCallback, data);
		}
	}
	return atomic;
}

RpAtomic* objRpClumpGetAtomicWithTexture(RpClump* clump, RpAtomic* skip, char* name)
{
	RpAtomic* found = NULL;
	pSkipAtomic     = skip;
	pobjTextureName = name;
	fn_8014FFBC(clump, objCallbackGetAtomicWithTexture, &found);
	return found;
}

static RpAtomic* objRpClumpGetAtomicWithGeometry(RpAtomic* atomic, void* data)
{
	RpAtomic** found = (RpAtomic**)data;
	if (!*found) {
		if (pSkipAtomic == atomic)
			pSkipAtomic = NULL;
		else if (!pSkipAtomic && atomic->geometry == pSearchGeometry) {
			*found = atomic;
			return NULL;
		}
	}
	return atomic;
}

RpAtomic* objRpClumpGetAtomicWithGeometry(RpClump* clump, RpAtomic* skip, RpGeometry* geometry)
{
	RpAtomic* found = NULL;
	pSkipAtomic     = skip;
	pSearchGeometry = geometry;
	fn_8014FFBC(clump, objRpClumpGetAtomicWithGeometry, &found);
	return found;
}

static RwTexture* objCallbackChangeTextureFilterMode(RwTexture* texture, void* data)
{
	f32 bias;
	s32 edge, clamp, anisotropy;
	s32 mode = (s32)data;
	fn_801B27EC(texture, &bias, &edge, &clamp, &anisotropy);
	RwRaster* raster = texture->raster;
	if (fn_801A1844(raster) > 1) {
		texture->filterAddressing = (texture->filterAddressing & ~255) | (mode & 255);
		s32 format                = raster->cFormat << 8;
		if (format & 0x6000)
			fn_801B2620(texture, bias, edge, 1, 0);
		else if (format & 0x9000)
			fn_801B2620(texture, bias, 0, 0, 0);
	} else {
		if (mode == 6)
			texture->filterAddressing = (texture->filterAddressing & ~255) | 2;
		else
			texture->filterAddressing = (texture->filterAddressing & ~255) | 1;
		fn_801B2620(texture, bias, edge, 1, 0);
	}
	return texture;
}

s32 objChangeTextureFilterMode(RwTexDictionary* dictionary, RwTextureFilterMode mode)
{
	fn_801A4778(dictionary, objCallbackChangeTextureFilterMode, (void*)mode);
	return 1;
}

static RwFrame* objCallbackGetFrame(RwFrame* frame, void* data)
{
	RwFrame** found = (RwFrame**)data;
	if (!*found) {
		if (pSkipFrame == frame)
			pSkipFrame = NULL;
		else if (!pSkipFrame) {
			*found     = frame;
			pSkipFrame = frame;
		}
	}
	return frame;
}

RwFrame* objRwFrameGetChildFrame(RwFrame* frame, RwFrame* skip)
{
	RwFrame* found = NULL;
	pSkipFrame     = skip;
	fn_8019EB10(frame, objCallbackGetFrame, &found);
	return found;
}

static RwFrame* objCallbackRwFrameGetChildFrame(RwFrame* frame, void* data)
{
	RwFrame** found = (RwFrame**)data;
	if (!*found) {
		if (order_Frame == 0) {
			*found      = frame;
			order_Frame = -1;
		} else if (order_Frame > 0) {
			--order_Frame;
			fn_8019EB10(frame, objCallbackRwFrameGetChildFrame, data);
		}
	}
	return frame;
}

RwFrame* objRwFrameGetFrame(RwFrame* frame, s32 order)
{
	RwFrame* found = NULL;
	order_Frame    = order;
	fn_8019EB10(frame, objCallbackRwFrameGetChildFrame, &found);
	return found;
}

static RwFrame* objCallbackSerchFrame(RwFrame* frame, void* data)
{
	s32* found = (s32*)data;
	if (!*found) {
		if (pSerchingFrame == frame)
			*found = 1;
		else if (frame->child)
			fn_8019EB10(frame, objCallbackSerchFrame, data);
	}
	return frame;
}

s32 objRwFrameSerchChildFrame(RwFrame* frame, RwFrame* target)
{
	s32 found      = 0;
	pSerchingFrame = target;
	fn_8019EB10(frame, objCallbackSerchFrame, &found);
	return found;
}

s32 objRpAtomicChangeUV(RpAtomic* atomic, RwTexCoords* offset)
{
	RpGeometry* geometry = atomic->geometry;
	RwTexCoords* uv      = geometry->texCoords[0];
	if (!uv)
		return 0;
	fn_80152828(geometry, 0x10);
	s32 count = geometry->numVertices;
	s32 i;
	for (i = 0; i < count; ++i) {
		uv->u += offset->u;
		uv->v += offset->v;
		++uv;
	}
	fn_80152880(geometry);
	return 1;
}

RpUVAnimAnimation* objRpUVAnimAnimationStreamRead(RwStream* stream)
{
	fn_8011BC20(fn_8011B874(stream));
	return fn_8011B654(stream);
}

static RpMaterial* objRpMaterialCallbackToChangeMaterialColor(RpMaterial* material, void* data)
{
	if (!data)
		return material;
	RwRGBA color      = material->color;
	RwRGBAReal* input = (RwRGBAReal*)data;
	if (input->alpha >= 0.0f)
		color.alpha = (u8)(255.0f * input->alpha);
	if (input->red >= 0.0f)
		color.red = (u8)(255.0f * input->red);
	if (input->green >= 0.0f)
		color.green = (u8)(255.0f * input->green);
	if (input->blue >= 0.0f)
		color.blue = (u8)(255.0f * input->blue);
	material->color = color;
	return material;
}

static RpAtomic* objRpAtomicForAllMaterialsToChangeMaterialColor(RpAtomic* atomic, void* color)
{
	objRpAtomicForAllMaterialsToChangeMaterialColor(atomic, (RwRGBAReal*)color);
	return atomic;
}

void objRpClumpForAllMaterialsToChangeMaterialColor(RpClump* clump, RwRGBAReal* color)
{
	fn_8014FFBC(clump, objRpAtomicForAllMaterialsToChangeMaterialColor, color);
}

void objRpAtomicForAllMaterialsToChangeMaterialColor(RpAtomic* atomic, RwRGBAReal* color)
{
	RpGeometry* geometry = atomic->geometry;
	fn_801527A4(geometry, objRpMaterialCallbackToChangeMaterialColor, color);
	geometry->flags |= 0x40;
}

static RpAtomic* objRpAtomicCallbackSetGeometryFlagToIgnoreLights(RpAtomic* atomic, void*)
{
	atomic->geometry->flags &= ~0x20;
	return atomic;
}

void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump)
{
	fn_8014FFBC(clump, objRpAtomicCallbackSetGeometryFlagToIgnoreLights, NULL);
}

static RpAtomic* objRpAtomicCallbackSetGeometryFlagToModulateMaterialColor(RpAtomic* atomic, void*)
{
	atomic->geometry->flags |= 0x40;
	return atomic;
}

void objRpClumpForAllGeometrysToModulateMaterialColor(RpClump* clump)
{
	fn_8014FFBC(clump, objRpAtomicCallbackSetGeometryFlagToModulateMaterialColor, NULL);
}

s32 objRpHAnimHierarchyFindFrameFromBoneID(RpHAnimHierarchy* hierarchy, s32 id)
{
	if (!hierarchy)
		return -1;
	s32 i;
	s32 found = -1;
	for (i = 0; i < hierarchy->numNodes; ++i)
		if (id == hierarchy->pNodeInfo[i].nodeID)
			found = i;
	return found;
}

static RpAtomic* objRpAtomicCallbackSetAtomicFlagToRender(RpAtomic* atomic, void*)
{
	atomic->object.object.flags |= 4;
	return atomic;
}

void objRpClumpForAllAtomicsToRender(RpClump* clump)
{
	fn_8014FFBC(clump, objRpAtomicCallbackSetAtomicFlagToRender, NULL);
}

static RpAtomic* objRpAtomicCallbackSetAtomicFlagToHide(RpAtomic* atomic, void*)
{
	atomic->object.object.flags &= ~4;
	return atomic;
}

void objRpClumpForAllAtomicsToHide(RpClump* clump)
{
	fn_8014FFBC(clump, objRpAtomicCallbackSetAtomicFlagToHide, NULL);
}

static RpAtomic* objRpAtomicCallbackSetAtomicFlagToHide2(RpAtomic* atomic, void* data)
{
	RwFrame* target      = (RwFrame*)data;
	RwFrame* frame       = (RwFrame*)atomic->object.object.parent;
	RpGeometry* geometry = atomic->geometry;
	void* skin           = fn_80226468(geometry);
	if (skin) {
		u8* indices = fn_80226578(skin);
		s32 count   = geometry->numVertices;
		if (indices)
			for (s32 i = 0; i <= count; ++i) {
				if (*indices++ == idBoneToHide || *indices++ == idBoneToHide
				    || *indices++ == idBoneToHide || *indices++ == idBoneToHide) {
					atomic->object.object.flags &= ~4;
					break;
				}
			}
	} else if (target == frame || objRwFrameSerchChildFrame(target, frame)) {
		atomic->object.object.flags &= ~4;
	}
	return atomic;
}

void objRpClumpForTheAtomicsToHide(RpClump* clump, RwFrame* frame, u32 bone)
{
	idBoneToHide = (u8)bone;
	fn_8014FFBC(clump, objRpAtomicCallbackSetAtomicFlagToHide2, frame);
}

static RpAtomic* objCallbackRpAtomicToAffectAlphaToColor(RpAtomic* atomic, void*)
{
	RwRGBA* color;
	s32 count;
	RpGeometry* geometry = atomic->geometry;
	count                = geometry->numVertices;
	color                = geometry->preLitLum;
	fn_80152828(geometry, 8);
	while (count-- > 0) {
		u32 alpha = color->alpha;
		if (alpha < 255) {
			color->red   = (u8)((color->red * alpha) >> 8);
			color->green = (u8)((color->green * alpha) >> 8);
			color->blue  = (u8)((color->blue * alpha) >> 8);
			color->alpha = 255;
		}
		++color;
	}
	fn_80152880(geometry);
	return atomic;
}

void objRpClumpForAllGeometriesToAffectAlphaToColor(RpClump* clump)
{
	fn_8014FFBC(clump, objCallbackRpAtomicToAffectAlphaToColor, NULL);
}

static RpAtomic* objCallbackRpAtomicRenderToUseLight(RpAtomic* atomic)
{
	OBJ_CUSTOMRENDER* cr = RpAtomicMCCGetCustomRenderCallBack(atomic);
	SetCurrentNum__6CLIGHTFSc(lbl_802D5E80, (s8)(s32)cr->pData);
	SetLightRegular__6CLIGHTFSc(lbl_802D5E80, lbl_802D5E80[0x4be]);
	cr->callback(atomic);
	return atomic;
}

static RpAtomic* objCallbackRpAtomicToSetRenderCallbackToUseLight(RpAtomic* atomic, void* data)
{
	OBJ_CUSTOMRENDER cr;
	cr.callback = atomic->renderCallBack;
	if (cr.callback == objCallbackRpAtomicRenderToUseLight)
		return atomic;
	cr.pData = data;
	RpAtomicMCCSetCustomRenderCallBack(atomic, &cr);
	atomic->renderCallBack = objCallbackRpAtomicRenderToUseLight;
	if (!atomic->renderCallBack)
		atomic->renderCallBack = fn_8014F1B0;
	return atomic;
}

void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump* clump, u32 light)
{
	fn_8014FFBC(clump, objCallbackRpAtomicToSetRenderCallbackToUseLight, (void*)light);
}

static RpAtomic* objCallbackRpAtomicRenderToOptimizeShadow(RpAtomic* atomic)
{
	OBJ_CUSTOMRENDER* cr = RpAtomicMCCGetCustomRenderCallBack(atomic);
	fn_800B8804(atomic);
	cr->callback(atomic);
	return atomic;
}

static RpAtomic* objCallbackRpAtomicToSetRenderCallbackToOptimizeShadow(RpAtomic* atomic, void*)
{
	OBJ_CUSTOMRENDER cr;
	cr.callback = atomic->renderCallBack;
	if (cr.callback == objCallbackRpAtomicRenderToOptimizeShadow)
		return atomic;
	RpAtomicMCCSetCustomRenderCallBack(atomic, &cr);
	atomic->renderCallBack = objCallbackRpAtomicRenderToOptimizeShadow;
	if (!atomic->renderCallBack)
		atomic->renderCallBack = fn_8014F1B0;
	return atomic;
}

void objRpClumpForAllAtomicsToSetRenderCallbackToOptimizeShadow(RpClump* clump)
{
	fn_8014FFBC(clump, objCallbackRpAtomicToSetRenderCallbackToOptimizeShadow, NULL);
}

static RpAtomic* objRpAtomicCallbackSetCompressedGeometry(RpAtomic* atomic, void*)
{
	fn_8015C878(atomic->geometry, lbl_803039E0);
	return atomic;
}

s32 objRpAtomicCheckFromCamera(RpAtomic* atomic, f32 distance)
{
	RwV3d vector;
	SubVectorReturnToVector__FPC5RwV3dPC5RwV3dP5RwV3d(
	    &fn_8019E8EC((RwFrame*)atomic->object.object.parent)->pos, lbl_8042C208, &vector);
	if (0.0f == distance) {
		if (atomic->interpolator.flags & 2)
			fn_8014F854(atomic);
		distance = 5.0f + atomic->boundingSphere.radius;
	}
	if (vector.z * vector.z + (vector.x * vector.x + vector.y * vector.y) < distance * distance)
		return 1;
	return 0;
}

static RpMaterial* objRpMaterialSaveFlagsAndColor(RpMaterial* material, void* data)
{
	u8 alpha                    = material->color.alpha;
	u8* colors                  = (u8*)data;
	colors[pCurrentMaterialNum] = alpha;
	++pCurrentMaterialNum;
	return material;
}

static RpMaterial* objRpMaterialResetFlagsAndColor(RpMaterial* material, void* data)
{
	RwRGBA color    = material->color;
	u8* colors      = (u8*)data;
	color.alpha     = colors[pCurrentMaterialNum];
	material->color = color;
	++pCurrentMaterialNum;
	return material;
}

static inline RpAtomic* objRpAtomicCallBackRenderNearCamera(
    RpAtomic* atomic, f32 distance, void* callback)
{
	RpGeometry* geometry = atomic->geometry;
	if (objRpAtomicCheckFromCamera(atomic, distance) && (atomic->object.object.flags & 4)) {
		void* savedAlpha    = __nwa__FUl(geometry->matList.numMaterials);
		RwRGBAReal color    = nearCameraColor;
		u32 flags           = geometry->flags;
		pCurrentMaterialNum = 0;
		fn_801527A4(geometry, objRpMaterialSaveFlagsAndColor, savedAlpha);
		objRpAtomicForAllMaterialsToChangeMaterialColor(atomic, &color);
		((RpAtomic * (*)(RpAtomic*)) callback)(atomic);
		pCurrentMaterialNum = 0;
		fn_801527A4(geometry, objRpMaterialResetFlagsAndColor, savedAlpha);
		__dla__FPv(savedAlpha);
		geometry->flags = flags;
	}
	return atomic;
}

void objRpAtomicRenderNearCamera(RpAtomic* atomic, f32 distance, void* callback)
{
	objRpAtomicCallBackRenderNearCamera(atomic, distance, callback);
}

void objRpAtomicRenderNearCamera(RpAtomic* atomic)
{
	void* savedAlpha;
	RpGeometry* geometry;
	OBJ_CUSTOMRENDER* cr = RpAtomicMCCGetCustomRenderCallBack(atomic);
	void* callback       = (void*)cr->callback;
	u32 flags;
	geometry     = atomic->geometry;
	f32 distance = (f32)(s32)cr->pData;
	if (objRpAtomicCheckFromCamera(atomic, distance) && (atomic->object.object.flags & 4)) {
		savedAlpha          = __nwa__FUl(geometry->matList.numMaterials);
		RwRGBAReal color    = nearCameraColor;
		flags               = geometry->flags;
		pCurrentMaterialNum = 0;
		fn_801527A4(geometry, objRpMaterialSaveFlagsAndColor, savedAlpha);
		RpGeometry* colorGeometry = atomic->geometry;
		fn_801527A4(colorGeometry, objRpMaterialCallbackToChangeMaterialColor, &color);
		colorGeometry->flags |= 0x40;
		((RpAtomic * (*)(RpAtomic*)) callback)(atomic);
		pCurrentMaterialNum = 0;
		fn_801527A4(geometry, objRpMaterialResetFlagsAndColor, savedAlpha);
		__dla__FPv(savedAlpha);
		geometry->flags = flags;
	}
}

static RpAtomic* objRpAtomicCallBackRenderNearCamera(RpAtomic* atomic, void*)
{
	void* savedAlpha;
	RpGeometry* geometry;
	OBJ_CUSTOMRENDER* cr = RpAtomicMCCGetCustomRenderCallBack(atomic);
	void* callback       = (void*)cr->callback;
	u32 flags;
	geometry     = atomic->geometry;
	f32 distance = (f32)(s32)cr->pData;
	if (objRpAtomicCheckFromCamera(atomic, distance) && (atomic->object.object.flags & 4)) {
		savedAlpha          = __nwa__FUl(geometry->matList.numMaterials);
		RwRGBAReal color    = nearCameraColor;
		flags               = geometry->flags;
		pCurrentMaterialNum = 0;
		fn_801527A4(geometry, objRpMaterialSaveFlagsAndColor, savedAlpha);
		RpGeometry* colorGeometry = atomic->geometry;
		fn_801527A4(colorGeometry, objRpMaterialCallbackToChangeMaterialColor, &color);
		colorGeometry->flags |= 0x40;
		((RpAtomic * (*)(RpAtomic*)) callback)(atomic);
		pCurrentMaterialNum = 0;
		fn_801527A4(geometry, objRpMaterialResetFlagsAndColor, savedAlpha);
		__dla__FPv(savedAlpha);
		geometry->flags = flags;
	}
	return atomic;
}

void objRpClumpForAllAtomicsRenderNearCamera(RpClump* clump)
{
	fn_8014FFBC(clump, objRpAtomicCallBackRenderNearCamera, NULL);
}

static RpAtomic* objCallbackRpAtomicCheckFromCamera(RpAtomic* atomic)
{
	OBJ_CUSTOMRENDER* cr = RpAtomicMCCGetCustomRenderCallBack(atomic);
	if (objRpAtomicCheckFromCamera(atomic, (f32)(s32)cr->pData) == 1)
		return atomic;
	cr->callback(atomic);
	return atomic;
}

static RpAtomic* objCallbackRpAtomicToSetRenderCallbackToCheckFromCamera(
    RpAtomic* atomic, void* data)
{
	OBJ_CUSTOMRENDER cr;
	cr.callback = atomic->renderCallBack;
	if (cr.callback == objCallbackRpAtomicCheckFromCamera)
		return atomic;
	cr.pData = data;
	RpAtomicMCCSetCustomRenderCallBack(atomic, &cr);
	atomic->renderCallBack = objCallbackRpAtomicCheckFromCamera;
	if (!atomic->renderCallBack)
		atomic->renderCallBack = fn_8014F1B0;
	return atomic;
}

void objRpClumpForAllAtomicsToSetRenderCallbackToCheckFromCamera(RpClump* clump, f32 distance)
{
	fn_8014FFBC(
	    clump, objCallbackRpAtomicToSetRenderCallbackToCheckFromCamera, (void*)(s32)distance);
}

void objRpAtomicToSetRenderCallbackToCheckFromCamera(RpAtomic* atomic, f32 distance)
{
	OBJ_CUSTOMRENDER cr;
	s32 value   = (s32)distance;
	cr.callback = atomic->renderCallBack;
	if (cr.callback != objCallbackRpAtomicCheckFromCamera) {
		cr.pData = (void*)value;
		RpAtomicMCCSetCustomRenderCallBack(atomic, &cr);
		atomic->renderCallBack = objCallbackRpAtomicCheckFromCamera;
		if (!atomic->renderCallBack)
			atomic->renderCallBack = fn_8014F1B0;
	}
}

OBJ_MoveOnGround::OBJ_MoveOnGround()
{
	posCenter.x = posCenter.y = posCenter.z = 0.0f;
	angGround.x                             = 0.0f;
	angGround.y                             = 0.0f;
	angGround.x                             = 0.0f;
	spdObject.x = spdObject.y = spdObject.z = 0.0f;
	cCheck                                  = 1;
	radObject                               = 10.0f;
	bound_mode                              = REAL;
	bound_coef                              = 0.75f;
	flagMOG &= ~0xf00;
	flagMOG &= ~0xf;
	lattr_Ignore = 0;
}

static s32 objCallbackCheckCollisionMoving(POLYDATA* pData)
{
	if (pData->attribute & pCurrentMOG->lattr_Ignore)
		return 0;
	return !(pData->norm.z * OBJ_MoveOnGround::vMove.z
	        + (pData->norm.x * OBJ_MoveOnGround::vMove.x
	            + pData->norm.y * OBJ_MoveOnGround::vMove.y)
	    >= 0.0f);
}

void OBJ_MoveOnGround::CheckCollisionSub_MoveToPoly(RwV3d* pPos, RwV3d* pVec, RwV3d* pNorm)
{
	RwV3d vV;
	if (vMove.z * vMove.z + (vMove.x * vMove.x + vMove.y * vMove.y) >= 0.01f)
		fn_801990E0(&vV, &vMove);
	else {
		vV.x = vV.y = vV.z = 0.0f;
		vMove.x = vMove.y = vMove.z = 0.0f;
	}
	vMove.x -= pVec->x;
	vMove.y -= pVec->y;
	vMove.z -= pVec->z;
	if (vV.z * pNorm->z + (vV.x * pNorm->x + vV.y * pNorm->y) < 0.1f) {
		spdObject.x *= bound_coef;
		spdObject.y *= bound_coef;
		spdObject.z *= bound_coef;
		vMove.x *= bound_coef;
		vMove.y *= bound_coef;
		vMove.z *= bound_coef;
	}
	if (spdObject.z * spdObject.z + (spdObject.x * spdObject.x + spdObject.y * spdObject.y) < 0.01f)
		spdObject.x = spdObject.y = spdObject.z = 0.0f;
	switch (bound_mode) {
		case REAL: {
			RwV3d vAdd;
			vAdd.x    = pNorm->x;
			vAdd.y    = pNorm->y;
			vAdd.z    = pNorm->z;
			f32 scale = 2.0f * DistanceP2PL__FPC5RwV3dPC5RwV3dP5RwV3d(&spdObject, pNorm, 0);
			vAdd.x *= scale;
			vAdd.y *= scale;
			vAdd.z *= scale;
			spdObject.x += vAdd.x;
			spdObject.y += vAdd.y;
			spdObject.z += vAdd.z;
			vAdd.x = pNorm->x;
			vAdd.y = pNorm->y;
			vAdd.z = pNorm->z;
			scale  = 2.0f * DistanceP2PL__FPC5RwV3dPC5RwV3dP5RwV3d(&vMove, pNorm, 0);
			vAdd.x *= scale;
			vAdd.y *= scale;
			vAdd.z *= scale;
			vMove.x += vAdd.x;
			vMove.y += vAdd.y;
			vMove.z += vAdd.z;
			break;
		}
		case EASY:
			if ((f32)__fabs(pNorm->x) > 0.5f) {
				spdObject.x = -spdObject.x;
				vMove.x     = -vMove.x;
			}
			if ((f32)__fabs(pNorm->y) > 0.5f) {
				spdObject.y = -spdObject.y;
				vMove.y     = -vMove.y;
			}
			if ((f32)__fabs(pNorm->z) > 0.5f) {
				spdObject.z = -spdObject.z;
				vMove.z     = -vMove.z;
			}
			break;
		case POINT:
			spdObject.x = -1.0f * spdObject.x;
			spdObject.y = -1.0f * spdObject.y;
			spdObject.z = -1.0f * spdObject.z;
			vMove.x     = -1.0f * vMove.x;
			vMove.y     = -1.0f * vMove.y;
			vMove.z     = -1.0f * vMove.z;
			break;
	}
	posCenter.x = pPos->x + pVec->x;
	posCenter.y = pPos->y + pVec->y;
	posCenter.z = pPos->z + pVec->z;
	f32 angle   = (f32)atan2(pNorm->x, pNorm->y);
	angGround.z = 0.0054931640625f * -(s32)(10430.381f * angle);
	angle       = (f32)asin(pNorm->z);
	angGround.x = 0.0054931640625f * (s32)(10430.381f * angle);
}

void OBJ_MoveOnGround::CheckCollisionSub()
{
	ColliPolyLinearList* pList;
	s32 stat;
	s32 numPoly;
	RwV3d vTrans, vecN, vecC;
	ColliPolyLinearListNode* pTempList;
	if (!lbl_8042C150)
		pList = 0;
	else if (0.0f == vMove.z * vMove.z + (vMove.x * vMove.x + vMove.y * vMove.y)) {
		pList = DetectSphereCollisionWithPolygons__6OCTREEFP5RwV3dfPFP8POLYDATA_i(
		    lbl_8042C150, &posCenter, radObject, 0);
		if (pList) {
			stat = 2;
			OmitSameSurfacePolygons__6OCTREEFP19ColliPolyLinearList(lbl_8042C150, pList);
		}
	} else
		pList
		    = DetectMovingSphereCollisionWithPolygons__6OCTREEFP5RwV3dfP5RwV3dP14ENUM_CL_MOVINGPFP8POLYDATA_i(
		        lbl_8042C150, &posCenter, radObject, &vMove, &stat,
		        objCallbackCheckCollisionMoving);
	if (!pList) {
		posCenter.x += vMove.x;
		posCenter.y += vMove.y;
		posCenter.z += vMove.z;
		vMove.x = vMove.y = vMove.z = 0.0f;
		return;
	}
	switch (stat) {
		case 1: {
			POLYDATA* pPoly;
			pPoly     = &lbl_8042C150->polygonData[pList->topNode->no];
			pTempList = pList->topNode;
			vTrans.x  = pTempList->ansVec.x;
			vTrans.y  = pTempList->ansVec.y;
			vTrans.z  = pTempList->ansVec.z;
			if (flagMOG & 0x100)
				flagMOG |= 1;
			if ((flagMOG & 0x200) && pPoly->norm.y > 0.5f)
				flagMOG |= 2;
			if ((flagMOG & 0x800) && pPoly->norm.y < -0.5f)
				flagMOG |= 8;
			if ((flagMOG & 0x400) && (f32)__fabs(pPoly->norm.y) <= 0.5f)
				flagMOG |= 4;
			CheckCollisionSub_MoveToPoly(&posCenter, &vTrans, &pPoly->norm);
			break;
		}
		case 2: {
			POLYDATA* pPoly;
			pTempList = pList->topNode;
			pPoly     = &lbl_8042C150->polygonData[pTempList->no];
			vecC.x    = pTempList->pushVec.x;
			vecC.y    = pTempList->pushVec.y;
			vecC.z    = pTempList->pushVec.z;
			vecN.x    = pPoly->norm.x;
			vecN.y    = pPoly->norm.y;
			vecN.z    = pPoly->norm.z;
			numPoly   = pList->numNode;
			for (s32 i = 1; i < numPoly; ++i) {
				vecC.x += pTempList->pushVec.x;
				vecC.y += pTempList->pushVec.y;
				vecC.z += pTempList->pushVec.z;
				POLYDATA* pPoly = &lbl_8042C150->polygonData[pTempList->no];
				vecN.x += pPoly->norm.x;
				vecN.y += pPoly->norm.y;
				vecN.z += pPoly->norm.z;
				pTempList = pTempList->nextNode;
				if (flagMOG & 0x100)
					flagMOG |= 1;
				if ((flagMOG & 0x200) && pPoly->norm.y > 0.5f)
					flagMOG |= 2;
				if ((flagMOG & 0x800) && pPoly->norm.y < -0.5f)
					flagMOG |= 8;
				if ((flagMOG & 0x400) && (f32)__fabs(pPoly->norm.y) <= 0.5f)
					flagMOG |= 4;
			}
			f32 scale = 1.0f / numPoly;
			vecC.x *= scale;
			vecC.y *= scale;
			vecC.z *= scale;
			if (vecN.z * vecN.z + (vecN.x * vecN.x + vecN.y * vecN.y) >= 0.01f)
				fn_801990E0(&vecN, &vecN);
			else {
				pPoly  = &lbl_8042C150->polygonData[pList->topNode->no];
				vecN.x = pPoly->norm.x;
				vecN.y = pPoly->norm.y;
				vecN.z = pPoly->norm.z;
			}
			CheckCollisionSub_MoveToPoly(&posCenter, &vecC, &vecN);
			break;
		}
	}
	__dt__19ColliPolyLinearListFv(pList, 1);
}

void OBJ_MoveOnGround::CheckGroundCollision(u32 flagRequest)
{
	pCurrentMOG = this;
	vMove       = spdObject;
	flagMOG &= ~0xf;
	flagMOG |= flagRequest & 0xf00;
	u32 i = 0;
	do {
		CheckCollisionSub();
	} while (i++ <= cCheck && 0.0f != fn_801991B4(&vMove));
	flagMOG &= ~0xf00;
}

void objCalculateVelocityAsCannonBall(RwV3d* pVec)
{
	pVec->y -= 0.1f;
	if (pVec->y < -5.0f)
		pVec->y = -5.0f;
}

// GC additionally advances position; PS2 metadata exposes only velocity.
void objCalculateVelocityAsCannonBall(RwV3d* velocity, RwV3d* position)
{
	velocity->y -= 0.1f;
	if (velocity->y < -5.0f)
		velocity->y = -5.0f;
	position->x += velocity->x;
	position->y += velocity->y;
	position->z += velocity->z;
}

f32 objRpUVAnimAnimationGetTotalFrame(RpUVAnimAnimation* animation)
{
	if (!animation || !animation->pAnim)
		return -1.0f;
	return animation->pAnim->duration;
}

static RpMaterial* MaterialSetCustomFXTexture(RpMaterial* material, void* data)
{
	UVFXInfo* info = (UVFXInfo*)data;
	fn_80149274(material, 5);
	fn_80149D7C(material, &info->uvMatrix, &info->uvMatrix);
	return material;
}

RpAtomic* AtomicSetCustomFXTexture(RpAtomic* atomic, void* data)
{
	RpGeometry* geometry = atomic->geometry;
	fn_801491A8(atomic);
	if (geometry)
		fn_801527A4(geometry, MaterialSetCustomFXTexture, data);
	return atomic;
}

static RpMaterial* SetUVAnimData(RpMaterial* material, void* data)
{
	UVFXInfo* info = (UVFXInfo*)data;
	fn_8011B78C(info->uvAnim, &info->uvMatrix);
	fn_8019565C(&info->uvMatrix);
	return material;
}

RpAtomic* SetAtomicCustomFXData(RpAtomic* atomic, void* data)
{
	fn_801527A4(atomic->geometry, SetUVAnimData, data);
	return atomic;
}

void SetClumpCustomFXTexture(RpClump* clump, UVFXInfo* info)
{
	fn_8014FFBC(clump, AtomicSetCustomFXTexture, info);
}

static RpMaterial* MaterialSetEffect(RpMaterial* material, void*)
{
	fn_80149274(material, 5);
	return material;
}

static RpAtomic* AtomicSetMaterialEffect(RpAtomic* atomic, void* data)
{
	RpGeometry* geometry = atomic->geometry;
	fn_801491A8(atomic);
	if (geometry)
		fn_801527A4(geometry, MaterialSetEffect, data);
	return atomic;
}
extern "C" {
__declspec(export) char lbl_802435A0[] = "./textures/obj_common.txd";
__declspec(export) char lbl_802435BC[] = "mte_gcn.mtd";
__declspec(export) char lbl_802435C8[] = "comobj.one";
}
