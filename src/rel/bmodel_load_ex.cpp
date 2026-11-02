#include "types.h"

// BMODEL's loaders from the stage's one file (LoadFilesEx and its
// LoadTmbDataEx, LoadAnimDataEx and LoadDataEx: the PS2 build's names, from
// STAGE.BIN), the same in the four stage modules that carry BMODEL.
// LoadFilesEx loads the one file under the stage's texture dictionary, then
// each BMODEL_DATA entry's clump and animation (LoadDataEx), each
// BMODEL_ANIMDATA's hierarchy, delta morph or UV animation (kind 1, 2 or 4;
// kind 3 has none), and each BMODEL_CAMERADATA's camera, up to the tables'
// ends. The clump flags ask for fn_800B8BEC (1), fn_800BDF30 (4),
// fn_8003C640 (8) and for ignoring lights (0x10). A clump's UV animation is
// also set as its first atomic's custom texture effect.

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
	void LoadOneFile(char* path);
	u32 CheckFileID(char* name);
	RpClump* LoadClumpEx(u32 id, char* path);
	RtAnimAnimation* LoadHAnimationEx(u32 id, char* path);
	RpDMorphAnimation* LoadDeltaMorphEx(u32 id, char* path);
	RpUVAnimAnimation* LoadUVAnimationEx(u32 id, char* path);
	void* LoadCameraTmbEx(u32 id, char* path);
};

class DAnimClass
{
public:
	f32 GetTotalFrame(RpDMorphAnimation* anim);
};

struct StageFiles {
	u8 unk000[0xA50];
	ONEFILE* file; // 0xA50
};

struct GameWorld {
	u8 unk0000[0x8C18];
	RwTexDictionary* dictionary; // 0x8C18
};

struct RwEngine {
	u8 unk000[0x134];
	void* (*malloc)(u32 size); // 0x134
};

class BMODEL
{
public:
	static s32 LoadFilesEx(BMODEL_DATA* data, BMODEL_ANIMDATA* anim, BMODEL_CAMERADATA* camera);
};

f32 objRpUVAnimAnimationGetTotalFrame(RpUVAnimAnimation* anim);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* atomic);
RpAtomic* AtomicSetCustomFXTexture(RpAtomic* atomic, void* data);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);

extern "C" {
extern StageFiles* lbl_8042C298;
extern GameWorld* lbl_8042C1D0;
extern RwEngine* lbl_8042C9A4;
extern DAnimClass lbl_8042C340;
extern char lbl_802FF5A0[];
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
void fn_800B8BEC(RpClump* clump, s32 arg);
void fn_800BDF30(RpClump* clump);
void fn_8003C640(RpClump* clump);
}

void LoadDataEx(BMODEL_DATA* data);

static inline void bmodelLoadTmbDataEx(BMODEL_CAMERADATA* camera)
{
	void* tmb = lbl_8042C298->file->LoadCameraTmbEx(
	    lbl_8042C298->file->CheckFileID(camera->name), lbl_802FF5A0);

	if (tmb != NULL) {
		camera->tmb = tmb;
	}
}

static inline void bmodelLoadAnimDataEx(BMODEL_ANIMDATA* anim)
{
	char name[64];

	switch (anim->kind) {
		case 1: {
			RtAnimAnimation* hanim;

			sprintf(name, bmodelAnmFormat, anim->name);
			hanim = lbl_8042C298->file->LoadHAnimationEx(
			    lbl_8042C298->file->CheckFileID(name), lbl_802FF5A0);
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
			morph = lbl_8042C298->file->LoadDeltaMorphEx(
			    lbl_8042C298->file->CheckFileID(name), lbl_802FF5A0);
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
			uv = lbl_8042C298->file->LoadUVAnimationEx(
			    lbl_8042C298->file->CheckFileID(name), lbl_802FF5A0);
			if (uv != NULL) {
				anim->anim   = uv;
				anim->frames = objRpUVAnimAnimationGetTotalFrame(uv);
			}
			break;
		}
	}
}

s32 BMODEL::LoadFilesEx(BMODEL_DATA* data, BMODEL_ANIMDATA* anim, BMODEL_CAMERADATA* camera)
{
	BMODEL_ANIMDATA* a = anim;
	BMODEL_DATA* entry;

	fn_801A4C84(lbl_8042C1D0->dictionary);
	lbl_8042C298->file->LoadOneFile(lbl_802FF5A0);
	entry = data;
	fn_800BE274(lbl_8042C1D0->dictionary);
	for (; entry != NULL && entry->kind >= 0; entry++) {
		LoadDataEx(entry);
	}
	fn_800BE1F4(lbl_8042C1D0->dictionary);
	if (a != NULL) {
		for (; a != NULL && a->kind >= 0; a++) {
			bmodelLoadAnimDataEx(a);
		}
	}
	if (camera != NULL) {
		BMODEL_CAMERADATA* cam;

		for (cam = camera; cam != NULL && strcmp(cam->name, bmodelCameraEnd) != 0; cam++) {
			bmodelLoadTmbDataEx(cam);
		}
	}
	return 1;
}

void LoadTmbDataEx(BMODEL_CAMERADATA* camera)
{
	bmodelLoadTmbDataEx(camera);
}

void LoadAnimDataEx(BMODEL_ANIMDATA* anim)
{
	bmodelLoadAnimDataEx(anim);
}

void LoadDataEx(BMODEL_DATA* data)
{
	char name[64];

	sprintf(name, bmodelDffFormat, data->name);
	data->clump
	    = lbl_8042C298->file->LoadClumpEx(lbl_8042C298->file->CheckFileID(name), lbl_802FF5A0);
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
	}
	switch (data->kind) {
		case 1: {
			RtAnimAnimation* hanim;

			sprintf(name, bmodelAnmFormat, data->name);
			hanim = lbl_8042C298->file->LoadHAnimationEx(
			    lbl_8042C298->file->CheckFileID(name), lbl_802FF5A0);
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
			morph = lbl_8042C298->file->LoadDeltaMorphEx(
			    lbl_8042C298->file->CheckFileID(name), lbl_802FF5A0);
			if (morph != NULL) {
				data->frames = lbl_8042C340.GetTotalFrame(morph);
				data->anim   = morph;
			}
			break;
		}
		case 4: {
			RpUVAnimAnimation* uv;

			sprintf(name, bmodelUvbFormat, data->name);
			uv = lbl_8042C298->file->LoadUVAnimationEx(
			    lbl_8042C298->file->CheckFileID(name), lbl_802FF5A0);
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
