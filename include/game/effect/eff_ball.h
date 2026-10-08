#ifndef GAME_EFFECT_EFF_BALL_H
#define GAME_EFFECT_EFF_BALL_H
#include "game/pathctrl.h"
struct RpClump;
struct RpUVAnimAnimation;
struct RwRGBA {
	u8 red, green, blue, alpha;
};
struct sRealAngle3 {
	f32 x, y, z;
};
class EffBall
{
public:
	void RenderEffBall(s32);
	void SetEffBallMaterialColor(const RwRGBA*);
	void ResetEffBallClump();
	~EffBall();
	EffBall();
	static void SetOriginalEffBallUVAnimPointer(s32, RpUVAnimAnimation*);
	static void SetOriginalEffBallClumpPointer(s32, RpClump*);
	static RpClump* pClump[6];
	static RpUVAnimAnimation* pUVAnim[6];
	RwRGBA rgba;
	RpClump* pClumpInstance[6];
};
s32 SetEffBallAnglesByDifferenceOfPlayersPositions(s32, sRealAngle3*);
s32 SetEffBallAnglesByDifferenceOfPlayersPositions(s32, sAngle*);
void EndEffBall();
void InitEffBall();
#endif
