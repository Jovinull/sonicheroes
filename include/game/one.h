#ifndef GAME_ONE_H
#define GAME_ONE_H
#include "types.h"

struct RwMemory {
	u8* start;
	u32 length;
};
struct ONE_FILEINFO {
	char filename[256][64];
};
struct NJS_MOTION;
struct Rt2dMaestro;
struct RpUVAnimAnimation;
struct RtAnimAnimation;
struct RpWorld;
struct RpDMorphAnimation;
struct RpSpline;
struct RpClump;
struct RwTexDictionary;

class ONEFILE
{
public:
	char fname[64];
	void* exBuffer;
	ONE_FILEINFO* oneFileInfo;
	s32 showError;
	s32 flagBW;
	RwMemory memInfo;

	ONEFILE(char* filename, s32 flag);
	~ONEFILE();
	s32 LoadOneFile(char* filename);
	s32 SetOneFile(void* buffer, s32 size, s32 releaseFlag);
	s32 ReleaseOneFile();
	s32 Exist() { return fname[0]; }
	s32 CheckFileID(char* filename);
	char* CheckFileName(s32 id);
	u32 OpenData(u32 id, void* buffer);
	NJS_MOTION* OneFileLoadCameraTmb(u32 id, void* buffer);
	Rt2dMaestro* OneFileLoadMaestro(u32 id, void* buffer);
	RpUVAnimAnimation* OneFileLoadUVAnim(u32 id, void* buffer);
	RtAnimAnimation* OneFileLoadHAnimation(u32 id, void* buffer);
	RpWorld* OneFileLoadWorld(u32 id, void* buffer);
	RpDMorphAnimation* OneFileLoadDeltaMorph(u32 id, void* buffer);
	RpSpline* OneFileLoadSpline(u32 id, void* buffer);
	RpClump* OneFileLoadClump(u32 id, void* buffer);
	RwTexDictionary* OneFileLoadTextureDictionay(u32 id, void* buffer);
	Rt2dMaestro* LoadMaestroEx(u32 id, char* oneFilename);
	NJS_MOTION* LoadCameraTmbEx(u32 id, char* oneFilename);
	RpUVAnimAnimation* LoadUVAnimationEx(u32 id, char* oneFilename);
	RtAnimAnimation* LoadHAnimationEx(u32 id, char* oneFilename);
	RpDMorphAnimation* LoadDeltaMorphEx(u32 id, char* oneFilename);
	RpSpline* LoadSplineEx(u32 id, char* oneFilename);
	RpClump* LoadClumpEx(u32 id, char* oneFilename);
};

// Original names unavailable for these two GameCube-specific operations.
extern "C" void fn_800BA7F8(ONEFILE*, void*, u32);
extern "C" u32 fn_800BC370(ONEFILE*, u32, void*, u32*);
#endif
