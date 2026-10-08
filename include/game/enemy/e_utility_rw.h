#ifndef GAME_ENEMY_E_UTILITY_RW_H
#define GAME_ENEMY_E_UTILITY_RW_H
#include "types.h"
struct RwFrame;
namespace nRenderWare
{
RwFrame* SearchFrameFromFrameID(RwFrame* pFrameParent, s32 FrameID);
}
#endif
