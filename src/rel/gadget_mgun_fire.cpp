#include "types.h"

// TEnemyGadgetMGun::Fire, SetUpFire, StandBy and NoAction (the PS2 build's
// names), the machine gun's gadget modes:
// - NoAction turns the gun back to rest and stops it;
// - StandBy turns toward the target (yaw held between 0 and 0x2000), levels
//   the pitch and takes the searcher's attack angle as its aim, stopping;
// - SetUpFire pitches to that aim, then attacks and runs the gun;
// - Fire points the gun from its muzzle frame along the searcher's angle
//   turned by its yaw and pitch, 20 ahead, and pitches back to the opposite
//   angle, stopping the gun there.
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
	RwV3d pos; // 0x30
	u32 pad3;
} RwMatrixTag;

class TMachineGun
{
public:
	void SetPosition(const RwV3d* pos);
	void SetAimPosition(const RwV3d* pos);
	void Stop();
	void Run();
};

typedef struct GadgetMGun {
	TEnemyGadget base;
	TObjEnemy* enemy;  // 0x38, the searcher
	TMachineGun* mgun; // 0x3C
	u8 unk40[0x4];
	s32 yaw;      // 0x44
	s32 pitch;    // 0x48
	s32 aimPitch; // 0x4C
} GadgetMGun;

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d mgunMuzzle;
extern "C" const RwV3d mgunAimDir;
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
extern "C" sAngle GetTargetAngle__17TObjEnemySearcherFv(Searcher* searcher);
extern "C" s32 GetMachineGunAttackAngle__17TObjEnemySearcherFv(Searcher* searcher);

extern "C" void NoAction__16TEnemyGadgetMGunFv(GadgetMGun* gadget)
{
	gadget->yaw   = AdjustAngle(gadget->yaw, 0, 0x150);
	gadget->pitch = AdjustAngle(gadget->pitch, 0, 0x150);
	if (gadget->mgun != NULL) {
		gadget->mgun->Stop();
	}
}

extern "C" void StandBy__16TEnemyGadgetMGunFv(GadgetMGun* gadget)
{
	if (gadget->enemy != NULL) {
		sAngle angle = GetTargetAngle__17TObjEnemySearcherFv((Searcher*)gadget->enemy);

		angle.x       = nVariable::Limit(angle.x, gadgetMinAim, gadgetMaxAim);
		gadget->yaw   = AdjustAngle(gadget->yaw, angle.x, 0x150);
		gadget->pitch = AdjustAngle(gadget->pitch, 0, 0x150);
		gadget->aimPitch
		    = GetMachineGunAttackAngle__17TObjEnemySearcherFv((Searcher*)gadget->enemy);
	}
	if (gadget->mgun != NULL) {
		gadget->mgun->Stop();
	}
}

extern "C" void SetUpFire__16TEnemyGadgetMGunFv(GadgetMGun* gadget)
{
	gadget->pitch = AdjustAngle(gadget->pitch, gadget->aimPitch, 0x150);
	if (gadget->pitch == gadget->aimPitch) {
		gadget->base.gmode = TEnemyGadget::E_GM_ATTACK;
		if (gadget->mgun != NULL) {
			gadget->mgun->Run();
		}
	}
}

extern "C" void Fire__16TEnemyGadgetMGunFv(GadgetMGun* gadget)
{
	if (gadget->enemy != NULL && gadget->mgun != NULL) {
		RwMatrixTag matrix;
		RwV3d muzzle   = mgunMuzzle;
		RwFrame* frame = gadget->base.pClump->frame;

		if (frame != NULL && (frame = objRwFrameGetFrame(frame, 2)) != NULL) {
			muzzle = fn_8019E8EC(frame)->pos;
		}
		sAngle angle = ((Searcher*)gadget->base.pOwner)->ang;

		angle.x += gadget->yaw;
		angle.y += gadget->pitch;
		RwV3d aim = mgunAimDir;

		fn_80195790(&matrix, &AxisX, gadgetOne - fn_800D7AE4(angle.x), fn_800D7B00(angle.x), 0);
		fn_80195790(&matrix, &AxisY, gadgetOne - fn_800D7AE4(angle.y), fn_800D7B00(angle.y), 2);
		fn_8019941C(&aim, &aim, 1, &matrix);
		aim.x += muzzle.x;
		aim.y += muzzle.y;
		aim.z += muzzle.z;
		gadget->mgun->SetPosition(&muzzle);
		gadget->mgun->SetAimPosition(&aim);
	}
	s32 target = (u16)-gadget->aimPitch;

	gadget->pitch = AdjustAngle(gadget->pitch, target, 0x80);
	if (gadget->pitch == target && gadget->mgun != NULL) {
		gadget->mgun->Stop();
	}
}
