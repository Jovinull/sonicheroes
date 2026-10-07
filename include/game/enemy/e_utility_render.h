#ifndef GAME_ENEMY_E_UTILITY_RENDER_H
#define GAME_ENEMY_E_UTILITY_RENDER_H
#include "types.h"
namespace nRender
{
void FogDisable();
void FogEnable();
void DisableLight(s32 world_num);
void EnableLight(s32 world_num);
void SetLightNum(u32 lightnum);
void SetRenderStateForBlendAdd();
void LoadRenderState();
void SaveRenderState();
}
#endif
