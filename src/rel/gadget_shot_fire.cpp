#include "types.h"

// TEnemyGadgetShot::Fire, StandBy and NoAction (the PS2 build's names), the
// shot gadget's modes:
// - NoAction pitches back to rest;
// - StandBy pitches toward the target (held between 0 and 0x2000);
// - Fire shoots a ground shot at the searcher's shot speed along its pitch and
//   the searcher's angles, from its muzzle frame, keeps the shot's number and
//   ends the attack.
// Built with deferred inlining like the rest of the gadgets' file, so the
// functions are defined last to first.

#include "src/rel/searcher.inc"

namespace nVariable
{

template <class T> inline const T& Limit(const T& value, const T& min, const T& max)
{
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

} // namespace nVariable

typedef struct RwMatrixTag {
	RwV3d right;
	u32 flags;
	RwV3d up;
	u32 pad1;
	RwV3d at;
	u32 pad2;
	RwV3d pos;
	u32 pad3;
} RwMatrixTag;

class ENEMY_SHOT
{
public:
	static int Create(u16& id, int kind, RwV3d* vel, RwV3d* pos);
};

typedef struct GadgetShot {
	TEnemyGadget base;
	Searcher* enemy; // 0x38
	u8 unk3C[0x4];
	s32 pitch; // 0x40
	s32 shot;  // 0x44, the shot's number, -1 for none
} GadgetShot;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const RwV3d shotVelocity;
extern "C" const RwV3d shotMuzzle;
extern "C" const f32 gadgetOne;
extern "C" const s32 gadgetMinAim;
extern "C" const s32 gadgetMaxAim;

s32 AdjustAngle(s32 angle, s32 aim, s32 speed);
RwFrame* objRwFrameGetFrame(RwFrame* frame, int index);
extern "C" RwMatrixTag* fn_8019E8EC(RwFrame* frame);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019941C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
extern "C" void fn_8019947C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
extern "C" sAngle GetTargetAngle__17TObjEnemySearcherFv(Searcher* searcher);

extern "C" void NoAction__16TEnemyGadgetShotFv(GadgetShot* gadget)
{
	gadget->pitch = AdjustAngle(gadget->pitch, 0, 0x150);
}

extern "C" void StandBy__16TEnemyGadgetShotFv(GadgetShot* gadget)
{
	if (gadget->enemy != NULL) {
		sAngle angle = GetTargetAngle__17TObjEnemySearcherFv(gadget->enemy);

		angle.x       = nVariable::Limit(angle.x, gadgetMinAim, gadgetMaxAim);
		gadget->pitch = AdjustAngle(gadget->pitch, angle.x, 0x150);
	}
}

extern "C" void Fire__16TEnemyGadgetShotFv(GadgetShot* gadget)
{
	Searcher* searcher = gadget->enemy;

	if (searcher != NULL) {
		RwMatrixTag matrix;
		RwV3d vel = shotVelocity;

		vel.z = -searcher->shotSpeed;
		fn_80195790(&matrix, &AxisX, gadgetOne - fn_800D7AE4(-gadget->pitch),
		    fn_800D7B00(-gadget->pitch), 0);
		fn_80195790(&matrix, &AxisY, gadgetOne - fn_800D7AE4(searcher->ang.y + 0x8000),
		    fn_800D7B00(searcher->ang.y + 0x8000), 2);
		fn_80195790(&matrix, &AxisX, gadgetOne - fn_800D7AE4(searcher->ang.x),
		    fn_800D7B00(searcher->ang.x), 2);
		fn_80195790(&matrix, &AxisZ, gadgetOne - fn_800D7AE4(searcher->ang.z),
		    fn_800D7B00(searcher->ang.z), 2);
		fn_8019947C(&vel, &vel, 1, &matrix);
		RwV3d pos      = shotMuzzle;
		RwFrame* frame = gadget->base.pClump->frame;

		if (frame != NULL && (frame = objRwFrameGetFrame(frame, 2)) != NULL) {
			u16 id;

			matrix = *fn_8019E8EC(frame);
			fn_8019941C(&pos, &pos, 1, &matrix);
			if (ENEMY_SHOT::Create(id, 1, &vel, &pos) == 1) {
				gadget->shot = id;
			}
		}
	}
	gadget->base.gmode = TEnemyGadget::E_GM_POSTATTACK;
}
