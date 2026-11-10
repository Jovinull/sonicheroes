#ifndef GAME_RTANIM_H
#define GAME_RTANIM_H
#include "types.h"

// GameCube RenderWare animation prefix used by enemy resource consumers.
struct RtAnimInterpolatorInfo {
	s32 typeID;
};
struct RtAnimAnimation {
	RtAnimInterpolatorInfo* interpInfo;
	s32 numFrames;
	s32 flags;
	f32 duration;
	void* pFrames;
	void* customData;
};

#endif
