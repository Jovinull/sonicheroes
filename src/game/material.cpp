#include "game/material.h"
#include "game/pathctrl.h"

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

static s32 sMaterialCounter;
static RpGeometry* pCurrentGeometry;
extern "C" {
RpGeometry* fn_801527A4(RpGeometry*, RpMaterial* (*)(RpMaterial*, void*), void*);
s32 fn_801A491C(RwTexture*);
RpMaterial* fn_8015498C(RpMaterial*, RwTexture*);
RpAtomic* fn_801491A8(RpAtomic*);
RpAtomic* fn_8011AA84(RpAtomic*);
}
static RpAtomic* AtomicCountMaterials(RpAtomic*, void*);
static RpAtomic* AtomicDecMaterialTextureRefs(RpAtomic*, void*);
static RpMaterial* DecMaterialTextureRefs(RpMaterial*, void*);
static RpAtomic* AtomicGetMaterialColors(RpAtomic*, void*);
static RpMaterial* GetMaterialColors(RpMaterial*, void*);
static RpAtomic* AtomicGetMaterialTexturePtrs(RpAtomic*, void*);
static RpMaterial* GetMaterialTexturePtrs(RpMaterial*, void*);
static RpAtomic* AtomicSetMaterialDefaultTextures(RpAtomic*, void*);
static RpMaterial* SetMaterialDefaultTextures(RpMaterial*, void*);
static RpAtomic* AtomicSetMaterialNoTextures(RpAtomic*, void*);
static RpMaterial* SetMaterialNoTextures(RpMaterial*, void*);
static RpAtomic* AtomicSetMaterialDefaultColors(RpAtomic*, void*);
static RpMaterial* SetMaterialDefaultColors(RpMaterial*, void*);
static RpAtomic* AtomicMulMaterialColors(RpAtomic*, void*);
static RpMaterial* MulMaterialColors(RpMaterial*, void*);
static RpAtomic* AtomicSetMaterialColors(RpAtomic*, void*);
static RpMaterial* SetMaterialColors(RpMaterial*, void*);
static RpAtomic* AtomicEnableMatFX(RpAtomic*, void*);
static RpAtomic* AtomicDisableMatFX(RpAtomic*, void*);

extern "C" {
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpGeometry* fn_801527A4(RpGeometry*, RpMaterial* (*)(RpMaterial*, void*), void*);
RpAtomic* fn_801491A8(RpAtomic*);
RpAtomic* fn_8011AA84(RpAtomic*);
}
struct MaterialRwMemoryFunctions {
	void* (*malloc)(u32);
	void (*free)(void*);
};
struct MaterialRwGlobals {
	u8 prefix[0x134];
	MaterialRwMemoryFunctions memoryFuncs;
};
extern "C" MaterialRwGlobals* lbl_8042C9A4;

static RpAtomic* AtomicDisableMatFX(RpAtomic* pCurrentAtomic, void* pData)
{
	fn_8011AA84(pCurrentAtomic);
	return pCurrentAtomic;
}

static RpAtomic* AtomicEnableMatFX(RpAtomic* pCurrentAtomic, void* pData)
{
	fn_801491A8(pCurrentAtomic);
	return pCurrentAtomic;
}

static RpMaterial* SetMaterialColors(RpMaterial* pCurrentMaterial, void* pData)
{
	RwRGBA* rgba                  = (RwRGBA*)pData;
	pCurrentMaterial->color.red   = rgba->red;
	pCurrentMaterial->color.green = rgba->green;
	pCurrentMaterial->color.blue  = rgba->blue;
	pCurrentMaterial->color.alpha = rgba->alpha;
	return pCurrentMaterial;
}

static RpAtomic* AtomicSetMaterialColors(RpAtomic* pCurrentAtomic, void* pData)
{
	pCurrentGeometry = pCurrentAtomic->geometry;
	fn_801527A4(pCurrentGeometry, SetMaterialColors, pData);
	return pCurrentAtomic;
}

static RpMaterial* MulMaterialColors(RpMaterial* pCurrentMaterial, void* pData)
{
	RwRGBA rgba                   = pCurrentMaterial->color;
	rgba.red                      = (u8)(rgba.red * ((f32*)pData)[0]);
	rgba.green                    = (u8)(rgba.green * ((f32*)pData)[1]);
	rgba.blue                     = (u8)(rgba.blue * ((f32*)pData)[2]);
	rgba.alpha                    = (u8)(rgba.alpha * ((f32*)pData)[3]);
	pCurrentMaterial->color.red   = rgba.red;
	pCurrentMaterial->color.green = rgba.green;
	pCurrentMaterial->color.blue  = rgba.blue;
	pCurrentMaterial->color.alpha = rgba.alpha;
	return pCurrentMaterial;
}

static RpAtomic* AtomicMulMaterialColors(RpAtomic* pCurrentAtomic, void* pData)
{
	pCurrentGeometry = pCurrentAtomic->geometry;
	fn_801527A4(pCurrentGeometry, MulMaterialColors, pData);
	return pCurrentAtomic;
}

static RpMaterial* SetMaterialDefaultColors(RpMaterial* pCurrentMaterial, void* pData)
{
	RwRGBA* rgba                  = &((RwRGBA*)pData)[sMaterialCounter++];
	pCurrentMaterial->color.red   = rgba->red;
	pCurrentMaterial->color.green = rgba->green;
	pCurrentMaterial->color.blue  = rgba->blue;
	pCurrentMaterial->color.alpha = rgba->alpha;
	return pCurrentMaterial;
}

static RpAtomic* AtomicSetMaterialDefaultColors(RpAtomic* pCurrentAtomic, void* pData)
{
	pCurrentGeometry = pCurrentAtomic->geometry;
	fn_801527A4(pCurrentGeometry, SetMaterialDefaultColors, pData);
	return pCurrentAtomic;
}

static RpMaterial* SetMaterialNoTextures(RpMaterial* pCurrentMaterial, void* pData)
{
	fn_8015498C(pCurrentMaterial, NULL);
	return pCurrentMaterial;
}

static RpAtomic* AtomicSetMaterialNoTextures(RpAtomic* pCurrentAtomic, void* pData)
{
	pCurrentGeometry = pCurrentAtomic->geometry;
	fn_801527A4(pCurrentGeometry, SetMaterialNoTextures, pData);
	return pCurrentAtomic;
}

static RpMaterial* SetMaterialDefaultTextures(RpMaterial* pCurrentMaterial, void* pData)
{
	fn_8015498C(pCurrentMaterial, ((RwTexture**)pData)[sMaterialCounter++]);
	return pCurrentMaterial;
}

static RpAtomic* AtomicSetMaterialDefaultTextures(RpAtomic* pCurrentAtomic, void* pData)
{
	pCurrentGeometry = pCurrentAtomic->geometry;
	fn_801527A4(pCurrentGeometry, SetMaterialDefaultTextures, pData);
	return pCurrentAtomic;
}

static RpMaterial* GetMaterialTexturePtrs(RpMaterial* pCurrentMaterial, void* pData)
{
	RwTexture** texPtr = &((RwTexture**)pData)[sMaterialCounter++];
	*texPtr            = pCurrentMaterial->texture;
	if (*texPtr != NULL)
		++(*texPtr)->refCount;
	return pCurrentMaterial;
}

static RpAtomic* AtomicGetMaterialTexturePtrs(RpAtomic* pCurrentAtomic, void* pData)
{
	pCurrentGeometry = pCurrentAtomic->geometry;
	pCurrentGeometry->flags |= 0x40;
	fn_801527A4(pCurrentGeometry, GetMaterialTexturePtrs, pData);
	return pCurrentAtomic;
}

static RpMaterial* GetMaterialColors(RpMaterial* pCurrentMaterial, void* pData)
{
	RwRGBA* rgba = &((RwRGBA*)pData)[sMaterialCounter++];
	rgba->red    = pCurrentMaterial->color.red;
	rgba->green  = pCurrentMaterial->color.green;
	rgba->blue   = pCurrentMaterial->color.blue;
	rgba->alpha  = pCurrentMaterial->color.alpha;
	return pCurrentMaterial;
}

static RpAtomic* AtomicGetMaterialColors(RpAtomic* pCurrentAtomic, void* pData)
{
	pCurrentGeometry = pCurrentAtomic->geometry;
	fn_801527A4(pCurrentGeometry, GetMaterialColors, pData);
	return pCurrentAtomic;
}

static RpMaterial* DecMaterialTextureRefs(RpMaterial* pCurrentMaterial, void* pData)
{
	RwTexture* texPtr = pCurrentMaterial->texture;
	if (texPtr != NULL)
		fn_801A491C(texPtr);
	return pCurrentMaterial;
}

static RpAtomic* AtomicDecMaterialTextureRefs(RpAtomic* pCurrentAtomic, void* pData)
{
	pCurrentGeometry = pCurrentAtomic->geometry;
	fn_801527A4(pCurrentGeometry, DecMaterialTextureRefs, pData);
	return pCurrentAtomic;
}

static RpAtomic* AtomicCountMaterials(RpAtomic* pCurrentAtomic, void* pData)
{
	*(s32*)pData += pCurrentAtomic->geometry->matList.numMaterials;
	return pCurrentAtomic;
}

DealMaterial::DealMaterial(RpClump* _clump)
{
	clump         = _clump;
	atomic        = 0;
	num_materials = 0;
	fn_8014FFBC(clump, AtomicCountMaterials, &num_materials);
	colors = (RwRGBA*)lbl_8042C9A4->memoryFuncs.malloc(num_materials * sizeof(RwRGBA));
	texture_ptrs
	    = (RwTexture**)lbl_8042C9A4->memoryFuncs.malloc(num_materials * sizeof(RwTexture*));
	sMaterialCounter = 0;
	fn_8014FFBC(clump, AtomicGetMaterialColors, colors);
	sMaterialCounter = 0;
	fn_8014FFBC(clump, AtomicGetMaterialTexturePtrs, texture_ptrs);
}

DealMaterial::DealMaterial(RpAtomic* _atomic)
{
	clump         = 0;
	atomic        = _atomic;
	num_materials = 0;
	AtomicCountMaterials(_atomic, &num_materials);
	colors = (RwRGBA*)lbl_8042C9A4->memoryFuncs.malloc(num_materials * sizeof(RwRGBA));
	texture_ptrs
	    = (RwTexture**)lbl_8042C9A4->memoryFuncs.malloc(num_materials * sizeof(RwTexture*));
	sMaterialCounter = 0;
	AtomicGetMaterialColors(_atomic, colors);
	sMaterialCounter = 0;
	AtomicGetMaterialTexturePtrs(_atomic, texture_ptrs);
}

DealMaterial::~DealMaterial()
{
	DefaultColor();
	DefaultTexture();
	lbl_8042C9A4->memoryFuncs.free(colors);
	lbl_8042C9A4->memoryFuncs.free(texture_ptrs);
	if (clump)
		fn_8014FFBC(clump, AtomicDecMaterialTextureRefs, 0);
	else
		AtomicDecMaterialTextureRefs(atomic, 0);
}

void DealMaterial::NoTexture()
{
	if (clump)
		fn_8014FFBC(clump, AtomicSetMaterialNoTextures, 0);
	else
		AtomicSetMaterialNoTextures(atomic, 0);
}

void DealMaterial::DefaultTexture()
{
	sMaterialCounter = 0;
	if (clump)
		fn_8014FFBC(clump, AtomicSetMaterialDefaultTextures, texture_ptrs);
	else
		AtomicSetMaterialDefaultTextures(atomic, texture_ptrs);
}

void DealMaterial::SetColor(RwRGBA* color)
{
	if (clump)
		fn_8014FFBC(clump, AtomicSetMaterialColors, color);
	else
		AtomicSetMaterialColors(atomic, color);
}

void DealMaterial::MulColor(f32* color)
{
	sMaterialCounter = 0;
	if (clump)
		fn_8014FFBC(clump, AtomicMulMaterialColors, color);
	else
		AtomicMulMaterialColors(atomic, color);
}

void DealMaterial::DefaultColor()
{
	sMaterialCounter = 0;
	if (clump)
		fn_8014FFBC(clump, AtomicSetMaterialDefaultColors, colors);
	else
		AtomicSetMaterialDefaultColors(atomic, colors);
}

void DealMaterial::DisableMatFX()
{
	if (clump)
		fn_8014FFBC(clump, AtomicDisableMatFX, 0);
	else
		fn_8011AA84(atomic);
}

void DealMaterial::EnableMatFX()
{
	if (clump)
		fn_8014FFBC(clump, AtomicEnableMatFX, 0);
	else
		fn_801491A8(atomic);
}
