#include "types.h"

// BMODEL's own file loaders and their release (ReleaseFiles, LoadFiles and its
// LoadTmbData, LoadAnimData and LoadData: the PS2 build's names, from
// STAGE.BIN), the same in the four stage modules that carry BMODEL. LoadFiles
// opens a file of its own with a 0x4B000-byte work buffer, takes (or loads)
// the texture dictionary, sets up the compressed vertex format (as
// VtxFmtInit does) and loads the tables as BMODEL::LoadFilesEx does; LoadData
// also knows flags 0x800 (compressed geometry) and 0x1000 (fn_800F46B0).
// ReleaseFiles destroys what the tables hold and the dictionary.

struct RpClump;
struct RpAtomic;
struct RtAnimAnimation;
struct RpDMorphAnimation;
struct RpUVAnimAnimation;
struct RwTexDictionary;

struct RtAnimAnimationView {
	u8 unk00[0xC];
	f32 duration; // 0x0C
};

struct BMODEL_ANIMDATA {
	s8 kind; // 0x00
	u8 pad01[0x3];
	void* anim;  // 0x04
	f32 frames;  // 0x08
	s32 updated; // 0x0C
	void** uvb;  // 0x10
	char* name;  // 0x14
}; // 0x18

struct BMODEL_DATA {
	u16 flags; // 0x00
	s8 light;  // 0x02
	u8 pad03;
	s32 world;      // 0x04
	RpClump* clump; // 0x08
	s8 kind;        // 0x0C
	u8 pad0D[0x3];
	void* anim;  // 0x10
	f32 frames;  // 0x14
	s32 updated; // 0x18
	void** uvb;  // 0x1C
	u8 unk20[0x4];
	char* name; // 0x24
}; // 0x28

struct BMODEL_CAMERADATA {
	u8 unk00[0x14];
	char* name; // 0x14
	void* tmb;  // 0x18
}; // 0x1C

class ONEFILE
{
public:
	ONEFILE(char* path, s32 mode);
	~ONEFILE();
	u32 CheckFileID(char* name);
	RwTexDictionary* OneFileLoadTextureDictionay(u32 id, void* buffer);
	RpClump* OneFileLoadClump(u32 id, void* buffer);
	RtAnimAnimation* OneFileLoadHAnimation(u32 id, void* buffer);
	RpDMorphAnimation* OneFileLoadDeltaMorph(u32 id, void* buffer);
	RpUVAnimAnimation* OneFileLoadUVAnim(u32 id, void* buffer);
	void* OneFileLoadCameraTmb(u32 id, void* buffer);

	u8 unk00[0x58];
};

class DAnimClass
{
public:
	f32 GetTotalFrame(RpDMorphAnimation* anim);
};

struct RwEngine {
	u8 unk000[0x134];
	void* (*malloc)(u32 size);  // 0x134
	void (*free)(void* memory); // 0x138
};

typedef struct BModelVtxFmt BModelVtxFmt;

class BMODEL
{
public:
	static void ReleaseFiles(RwTexDictionary** dictionary, BMODEL_DATA* data, BMODEL_ANIMDATA* anim,
	    BMODEL_CAMERADATA* camera);
	static s32 LoadFiles(char* path, char* texture, RwTexDictionary** dictionary, BMODEL_DATA* data,
	    BMODEL_ANIMDATA* anim, BMODEL_CAMERADATA* camera);
};

f32 objRpUVAnimAnimationGetTotalFrame(RpUVAnimAnimation* anim);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* atomic);
RpAtomic* AtomicSetCustomFXTexture(RpAtomic* atomic, void* data);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);
RpAtomic* callbackSetCompressedGeometry(RpAtomic* atomic, void* data);

extern "C" {
extern RwEngine* lbl_8042C9A4;
extern DAnimClass lbl_8042C340;
extern BModelVtxFmt bmodelVtxFmt;
extern s32 bmodelVtxFmtReady;
extern char bmodelAnmFormat[];
extern char bmodelDmaFormat[];
extern char bmodelUvbFormat[];
extern char bmodelCameraEnd[];
extern char bmodelDffFormat[];
int sprintf(char* buffer, const char* format, ...);
int strcmp(const char* a, const char* b);
void fn_801A4C84(RwTexDictionary* dictionary);
void fn_800BE274(RwTexDictionary* dictionary);
void fn_800BE1F4(RwTexDictionary* dictionary);
void fn_801A46D0(RwTexDictionary* dictionary);
void fn_800B8BEC(RpClump* clump, s32 arg);
void fn_800B8ADC(RpClump* clump);
void fn_800BDF30(RpClump* clump);
void fn_8003C640(RpClump* clump);
void fn_800F46B0(RpClump* clump);
void fn_80150958(RpClump* clump);
void fn_8020C2D8(void* anim);
void fn_8013BD74(void* anim);
void fn_8011B7CC(void* anim);
void fn_8015C728(BModelVtxFmt* format);
void fn_8015C6F8(BModelVtxFmt* format, s32 attr, s32 type);
void fn_8015C704(BModelVtxFmt* format, s32 attr, s32 type);
void fn_8015C710(BModelVtxFmt* format, s32 attr, s32 count, s32 frac);
void fn_8015C720(BModelVtxFmt* format, s32 attr);
void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
}

void LoadData(ONEFILE* file, void* buffer, BMODEL_DATA* data);

// The kinds' animation destroyers, shared by both tables.
static inline void bmodelDestroyAnim(s8 kind, void* anim)
{
	switch (kind) {
		case 3:
			break;
		case 1:
			fn_8020C2D8(anim);
			break;
		case 2:
			fn_8013BD74(anim);
			break;
		case 4:
			fn_8011B7CC(anim);
			break;
	}
}

void BMODEL::ReleaseFiles(RwTexDictionary** dictionary, BMODEL_DATA* data, BMODEL_ANIMDATA* anim,
    BMODEL_CAMERADATA* camera)
{
	BMODEL_CAMERADATA* cam;
	BMODEL_DATA* d = data;

	for (; d != NULL && d->kind >= 0; d++) {
		if (d->clump != NULL) {
			if (d->flags & 1) {
				fn_800B8ADC(d->clump);
			}
			fn_80150958(d->clump);
			d->clump = NULL;
		}
		if (d->anim != NULL) {
			switch (d->kind) {
				case 3:
					break;
				case 1:
					fn_8020C2D8(d->anim);
					break;
				case 2:
					fn_8013BD74(d->anim);
					break;
				case 4:
					fn_8011B7CC(d->anim);
					if (d->uvb != NULL) {
						lbl_8042C9A4->free(d->uvb);
						d->uvb = NULL;
					}
					break;
			}
			d->anim = NULL;
		}
	}
	for (; anim != NULL && anim->kind >= 0; anim++) {
		if (anim->anim != NULL) {
			bmodelDestroyAnim(anim->kind, anim->anim);
			anim->anim = NULL;
		}
	}
	for (cam = camera; cam != NULL && strcmp(cam->name, bmodelCameraEnd) != 0; cam++) {
		if (cam->tmb != NULL) {
			lbl_8042C9A4->free(cam->tmb);
			cam->tmb = NULL;
		}
	}
	if (dictionary != NULL && *dictionary != NULL) {
		fn_801A46D0(*dictionary);
		*dictionary = NULL;
	}
}

static inline void bmodelLoadTmbData(ONEFILE* file, void* buffer, BMODEL_CAMERADATA* camera)
{
	void* tmb = file->OneFileLoadCameraTmb(file->CheckFileID(camera->name), buffer);

	if (tmb != NULL) {
		camera->tmb = tmb;
	}
}

static inline void bmodelLoadAnimData(ONEFILE* file, void* buffer, BMODEL_ANIMDATA* anim)
{
	char name[64];

	switch (anim->kind) {
		case 1: {
			RtAnimAnimation* hanim;

			sprintf(name, bmodelAnmFormat, anim->name);
			hanim = file->OneFileLoadHAnimation(file->CheckFileID(name), buffer);
			if (hanim != NULL) {
				anim->frames = ((RtAnimAnimationView*)hanim)->duration;
				anim->anim   = hanim;
				return;
			}
		}
		case 3:
			return;
		case 2: {
			RpDMorphAnimation* morph;

			sprintf(name, bmodelDmaFormat, anim->name);
			morph = file->OneFileLoadDeltaMorph(file->CheckFileID(name), buffer);
			if (morph != NULL) {
				anim->frames = lbl_8042C340.GetTotalFrame(morph);
				anim->anim   = morph;
				return;
			}
			break;
		}
		case 4: {
			RpUVAnimAnimation* uv;

			sprintf(name, bmodelUvbFormat, anim->name);
			uv = file->OneFileLoadUVAnim(file->CheckFileID(name), buffer);
			if (uv != NULL) {
				anim->anim   = uv;
				anim->frames = objRpUVAnimAnimationGetTotalFrame(uv);
			}
			break;
		}
	}
}

s32 BMODEL::LoadFiles(char* path, char* texture, RwTexDictionary** dictionary, BMODEL_DATA* data,
    BMODEL_ANIMDATA* anim, BMODEL_CAMERADATA* camera)
{
	RwTexDictionary* textures = NULL;
	ONEFILE* file             = new ONEFILE(path, 0);
	void* buffer;

	if (file == NULL) {
		return 0;
	}
	buffer = lbl_8042C9A4->malloc(0x4B000);
	if (buffer == NULL) {
		delete file;
		return 0;
	}
	if (dictionary != NULL) {
		if (*dictionary == NULL && texture != NULL) {
			textures    = file->OneFileLoadTextureDictionay(file->CheckFileID(texture), buffer);
			*dictionary = textures;
		} else {
			textures = *dictionary;
		}
	}
	fn_801A4C84(textures);
	if (bmodelVtxFmtReady != 1) {
		fn_8015C728(&bmodelVtxFmt);
		fn_8015C6F8(&bmodelVtxFmt, 3, 6);
		fn_8015C704(&bmodelVtxFmt, 3, 0);
		fn_8015C710(&bmodelVtxFmt, 1, 3, 0xA);
		fn_8015C720(&bmodelVtxFmt, 3);
		bmodelVtxFmtReady = 1;
	}
	if (data != NULL) {
		if (textures != NULL) {
			fn_800BE274(textures);
		}
		for (; data != NULL && data->kind >= 0; data++) {
			LoadData(file, buffer, data);
		}
		if (textures != NULL) {
			fn_800BE1F4(textures);
		}
	}
	if (anim != NULL) {
		BMODEL_ANIMDATA* a;

		for (a = anim; a != NULL && a->kind >= 0; a++) {
			bmodelLoadAnimData(file, buffer, a);
		}
	}
	if (camera != NULL) {
		BMODEL_CAMERADATA* cam;

		for (cam = camera; cam != NULL && strcmp(cam->name, bmodelCameraEnd) != 0; cam++) {
			bmodelLoadTmbData(file, buffer, cam);
		}
	}
	lbl_8042C9A4->free(buffer);
	delete file;
	return 1;
}

void LoadTmbData(ONEFILE* file, void* buffer, BMODEL_CAMERADATA* camera)
{
	bmodelLoadTmbData(file, buffer, camera);
}

void LoadAnimData(ONEFILE* file, void* buffer, BMODEL_ANIMDATA* anim)
{
	bmodelLoadAnimData(file, buffer, anim);
}

void LoadData(ONEFILE* file, void* buffer, BMODEL_DATA* data)
{
	char name[64];

	sprintf(name, bmodelDffFormat, data->name);
	data->clump = file->OneFileLoadClump(file->CheckFileID(name), buffer);
	if (data->clump != NULL) {
		if (data->flags & 1) {
			fn_800B8BEC(data->clump, 0);
		}
		if (data->flags & 4) {
			fn_800BDF30(data->clump);
		}
		if (data->flags & 8) {
			fn_8003C640(data->clump);
		}
		if (data->flags & 0x10) {
			objRpClumpForAllGeometrysToIgnoreLights(data->clump);
		}
		if (data->flags & 0x800) {
			fn_8014FFBC(data->clump, callbackSetCompressedGeometry, NULL);
		}
		if (data->flags & 0x1000) {
			fn_800F46B0(data->clump);
		}
	}
	switch (data->kind) {
		case 1: {
			RtAnimAnimation* hanim;

			sprintf(name, bmodelAnmFormat, data->name);
			hanim = file->OneFileLoadHAnimation(file->CheckFileID(name), buffer);
			if (hanim != NULL) {
				data->frames = ((RtAnimAnimationView*)hanim)->duration;
				data->anim   = hanim;
			}
			break;
		}
		case 3:
			break;
		case 2: {
			RpDMorphAnimation* morph;

			sprintf(name, bmodelDmaFormat, data->name);
			morph = file->OneFileLoadDeltaMorph(file->CheckFileID(name), buffer);
			if (morph != NULL) {
				data->frames = lbl_8042C340.GetTotalFrame(morph);
				data->anim   = morph;
			}
			break;
		}
		case 4: {
			RpUVAnimAnimation* uv;

			sprintf(name, bmodelUvbFormat, data->name);
			uv = file->OneFileLoadUVAnim(file->CheckFileID(name), buffer);
			if (uv != NULL) {
				if (data->clump != NULL && uv != NULL) {
					data->uvb = (void**)lbl_8042C9A4->malloc(0x44);
					if (data->uvb != NULL) {
						*data->uvb = uv;
						AtomicSetCustomFXTexture(objRpClumpGetAtomic(data->clump, NULL), data->uvb);
					}
				}
				data->anim   = uv;
				data->frames = objRpUVAnimAnimationGetTotalFrame(uv);
			}
			break;
		}
	}
}
