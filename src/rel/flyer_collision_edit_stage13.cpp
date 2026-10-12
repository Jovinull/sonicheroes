// TObjFlyerCollision's EditOnChange in stage13D, which is built from another
// revision of rel/flyer_collision_edit.cpp: the clamped kind is stored through
// the parameter block's unsigned byte, without the sign extension the other
// modules have. The kind is held between the module's two byte limits and the
// word at 0x14 between its two word limits, the kind names the editor's first
// field, and the volume's extent takes the placement's position. The limits go
// through a clamp that returns a reference, which is where the original's
// branch over a branch comes from. The class is in game/obj_flyer_collision.h.

#include "game/obj_flyer_collision.h"

extern "C" s8 flyerColKindMin;
extern "C" s8 flyerColKindMax;
extern "C" const s32 flyerColUnk14Min;
extern "C" const s32 flyerColUnk14Max;
extern "C" const char* flyerColKindNames[];
extern "C" const char* flyerColObjectFieldNames[];

template <typename T>
static inline const T& flyerColClamp(const T& value, const T& low, const T& high)
{
	return value < low ? low : (value > high ? high : value);
}

void TObjFlyerCollision::EditOnChange(SETDATA_PARAM* data)
{
	FlyerColParam* param = (FlyerColParam*)data->setBuffer;
	s8* kind             = (s8*)&param->kind;

	param->kind                 = flyerColClamp(*kind, flyerColKindMin, flyerColKindMax);
	param->unk14                = flyerColClamp(param->unk14, flyerColUnk14Min, flyerColUnk14Max);
	flyerColObjectFieldNames[0] = flyerColKindNames[*kind];
	param->extent               = data->pos;
}
