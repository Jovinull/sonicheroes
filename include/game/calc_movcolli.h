#ifndef GAME_CALC_MOVCOLLI_H
#define GAME_CALC_MOVCOLLI_H
#include "game/rw_types.h"
enum ENUM_CL_MOVING { CL_MOVING_NONE = 0, CL_MOVING_COLLISION = 1, CL_MOVING_INTERSECTION = 2 };
ENUM_CL_MOVING clDetectMS2T(const RwV3d* sphere_pos, f32 sphere_rad, const RwV3d* sphere_vec,
    RwV3d* tri_vertex, RwV3d* ans_vec, RwV3d* coli_pos, s16* pOn_Edge);
ENUM_CL_MOVING clDetectMS2LS_(const RwV3d* sphere_pos, f32 sphere_rad, const RwV3d* sphere_vec,
    const RwV3d* detect_vec, const RwV3d* safe_vec, RwV3d* ans_vec, RwV3d* coli_pos);
ENUM_CL_MOVING clDetectMS2P_(const RwV3d* sphere_pos, f32 sphere_rad, const RwV3d* sphere_vec,
    const RwV3d* safe_vec, RwV3d* ans_vec);
#endif
