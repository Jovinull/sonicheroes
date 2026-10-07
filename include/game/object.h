#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "game/pathctrl.h"
#include "game/plugin/materialcolorchange.h"

struct RwObject {
	u8 type, subType, flags, privateFlags;
	void* parent;
};
struct RwLLLink {
	RwLLLink *next, *prev;
};
struct RwLinkList {
	RwLLLink link;
};
struct RwMatrix {
	RwV3d right;
	u32 flags;
	RwV3d up;
	u32 pad1;
	RwV3d at;
	u32 pad2;
	RwV3d pos;
	u32 pad3;
};
struct RwFrame {
	RwObject object;
	RwLLLink inDirtyListLink;
	RwMatrix modelling, ltm;
	RwLinkList objectList;
	RwFrame *child, *next, *root;
};
struct RwObjectHasFrame {
	RwObject object;
	RwLLLink lFrame;
	void* sync;
};
struct RwSphere {
	RwV3d center;
	f32 radius;
};
struct RwSurfaceProperties {
	f32 ambient, specular, diffuse;
};
struct RwRGBAReal {
	f32 red, green, blue, alpha;
};
struct RwTexCoords {
	f32 u, v;
};
struct RwTexDictionary;
enum RwTextureFilterMode {
	rwFILTERNAFILTERMODE,
	rwFILTERNEAREST,
	rwFILTERLINEAR,
	rwFILTERMIPNEAREST,
	rwFILTERMIPLINEAR,
	rwFILTERLINEARMIPNEAREST,
	rwFILTERLINEARMIPLINEAR
};
struct RwRaster {
	RwRaster* parent;
	u8 *cpPixels, *palette;
	s32 width, height, depth, stride;
	s16 nOffsetX, nOffsetY;
	u8 cType, cFlags, privateFlags, cFormat;
	u8* originalPixels;
	s32 originalWidth, originalHeight, originalStride;
};
struct RwTexture {
	RwRaster* raster;
	RwTexDictionary* dict;
	RwLLLink lInDictionary;
	char name[32], mask[32];
	u32 filterAddressing;
	s32 refCount;
};
struct RwTexDictionary {
	RwObject object;
	RwLinkList texturesInDict;
	RwLLLink lInInstance;
};
struct RpMaterial {
	RwTexture* texture;
	RwRGBA color;
	void* pipeline;
	RwSurfaceProperties surfaceProps;
	s16 refCount, pad;
};
struct RpMaterialList {
	RpMaterial** materials;
	s32 numMaterials, space;
};
struct RpGeometry {
	RwObject object;
	u32 flags;
	u16 lockedSinceLastInst;
	s16 refCount;
	s32 numTriangles, numVertices, numMorphTargets, numTexCoordSets;
	RpMaterialList matList;
	void* triangles;
	RwRGBA* preLitLum;
	RwTexCoords* texCoords[8];
	void* mesh;
	void* repEntry;
	void* morphTarget;
};
struct RpClump;
struct RpInterpolator {
	s32 flags;
	s16 startMorphTarget, endMorphTarget;
	f32 time, recipTime, position;
};
struct RpAtomic {
	RwObjectHasFrame object;
	void* repEntry;
	RpGeometry* geometry;
	RwSphere boundingSphere, worldBoundingSphere;
	RpClump* clump;
	RwLLLink inClumpLink;
	RpAtomic* (*renderCallBack)(RpAtomic*);
	RpInterpolator interpolator;
	u16 renderFrame, pad;
	RwLinkList llWorldSectorsInAtomic;
	void* pipeline;
};
struct RpClump {
	RwObject object;
	RwLinkList atomicList, lightList, cameraList;
	RwLLLink inWorldLink;
	RpClump* (*callback)(RpClump*, void*);
};
struct RpHAnimNodeInfo {
	s32 nodeID, nodeIndex, flags;
	RwFrame* pFrame;
};
struct RpHAnimHierarchy {
	s32 flags, numNodes;
	RwMatrix* pMatrixArray;
	void* pMatrixArrayUnaligned;
	RpHAnimNodeInfo* pNodeInfo;
	RwFrame* parentFrame;
	RpHAnimHierarchy* parentHierarchy;
	s32 rootParentOffset;
	void* currentAnim;
};
struct RtAnimAnimation {
	void* interpInfo;
	s32 numFrames, flags;
	f32 duration;
	void* pFrames;
	void* customData;
};
struct RpUVAnimAnimation {
	RtAnimAnimation* pAnim;
	void* instance;
	s32 type;
};
struct UVFXInfo {
	RpUVAnimAnimation* uvAnim;
	RwMatrix uvMatrix;
};
struct OBJ_SearchMaterials {
	RpMaterial* (*callback)(RpMaterial*, void*);
	char* pTextureName;
	void* pData;
};
struct OBJ_CLUMPANIM {
	char filename[64];
	void* ptr;
};

struct sRealAngle3 {
	f32 x, y, z;
};
class OBJ_MoveOnGround
{
public:
	static RwV3d vMove;
	enum BOUND_MODE { POINT, EASY, REAL };
	u16 cCheck, flagMOG;
	BOUND_MODE bound_mode;
	RwV3d posCenter;
	sRealAngle3 angGround;
	RwV3d spdObject;
	f32 radObject, bound_coef;
	u32 lattr_Ignore;
	void CheckGroundCollision(u32);
	void CheckCollisionSub();
	void CheckCollisionSub_MoveToPoly(RwV3d*, RwV3d*, RwV3d*);
	OBJ_MoveOnGround();
};
class OBJ_ReplacePlayer
{
public:
	s32 objSetPlayerHandlingPosition(s32, u8, RwV3d*, sAngle*);
	s32 objSetPlayerPosition(s32, u8, RwV3d*, sAngle*);
};
void objCalculateVelocityAsCannonBall(RwV3d*);
void objCalculateVelocityAsCannonBall(RwV3d*, RwV3d*);
#endif
