#ifndef GAME_LIGHT_H
#define GAME_LIGHT_H
#include "types.h"

struct RwV3d {
	f32 x, y, z;
};
struct RwRGBAReal {
	f32 red, green, blue, alpha;
};
struct RwFrame;
struct RpLight;
struct RpWorld;
struct RP_LightInfo {
	s8 type;
	RwRGBAReal rgba;
	f32 ang_x, ang_y;
	RwV3d pos;
	f32 Radius, ConeAngle;
};
struct REGLIGHT_STRUCT {
	RwRGBAReal amb_rgba, dir_rgba;
	RwV3d dir_vec;
	s32 dir_ang[2];
};
class RP_Light
{
public:
	s8 lighttype, lightNo;
	u32 setflag;
	RpLight* pLight;
	RpWorld* CurrWorld;
	RP_LightInfo NowInfo;
	RP_Light(s8);
	RP_Light(s8, RP_LightInfo*);
	~RP_Light();
	s32 SetFlag(u32);
	s32 SetColor(RwRGBAReal*);
	s32 SetRadius(f32);
	s32 SetConeAngle(f32);
	s32 SetPosition(RwV3d*);
	s32 SetAngle(f32, f32);
	void Disable();
	void Enable(RpWorld*);
	void DestroyLight();
	RpLight* CreateLight(s8);
	RpLight* CreateLightFromTable(RP_LightInfo*);
};
class CLIGHT
{
public:
	RP_Light* rpLight[8];
	REGLIGHT_STRUCT reglight_struct[19];
	RP_LightInfo splight_struct[4];
	s8 now_num, default_num, current_num;
	s8 player_current[8], player_default[8];
	void EndIgnoreLight(RpWorld*);
	void StartIgnoreLight(RpWorld*);
	void SetLightCurrentPlayer(s8);
	void SetCurrentNumPlayer(s8, s8);
	void ChangeWorld(RpWorld*);
	void DisableAll();
	void Disable(s8);
	void RestoreAll();
	void Restore(s8);
	void Enable(s8, RpWorld*);
	s32 SetRadius(s8, f32);
	s32 SetPosition(s8, RwV3d*);
	s32 SetAngle(s8, f32, f32);
	s32 SetColor(s8, RwRGBAReal*);
	void SetRegTableAngle(s8, f32, f32);
	void SetRegTableColor(s8, RwRGBAReal*);
	void SetLightRegular(s8);
	void SetCurrentNum(s8);
	void DestroyLight(s8);
	s8 CreateSpecialLight(RP_LightInfo*);
	s32 CreateRegularLight();
	void CopyLightData(REGLIGHT_STRUCT*);
	void AssignData(REGLIGHT_STRUCT*);
	void End();
	void Init();
	void InitRegTable();
	void DestroyRegularLight();
	void DestroyAllSPLight();
	s32 LoadLightData(REGLIGHT_STRUCT*, char*);
};
#endif
