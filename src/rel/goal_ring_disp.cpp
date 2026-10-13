#include "types.h"

// TObjGoalring::Disp (the PS2 build's name): with the game not paused and the
// plain ring shown, once the ring has grown above zero it draws the effect
// model with light set 0x10 and the regular light: scaled by the ring's size
// (its height kept), placed at the ring, its inner frames turned about Y and
// Z by the ring's spins, its atomics given full alpha (goalRingBind).

#include "src/rel/goal_ring_class.inc"

struct RwFrame;
struct RpAtomic;

class CLIGHT
{
public:
	u8 unk000[0x4BE];
	s8 regular; // 0x4BE

	void SetCurrentNum(s8 num);
	void SetLightRegular(s8 num);
};

struct GoalringClump {
	u8 pad00[0x4];
	RwFrame* frame; // 0x04
};

extern "C" CLIGHT lbl_802D5E80;
extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 goalRingZero[1];
extern "C" const f32 goalRingEffectHeight[1];

extern "C" RpAtomic* goalRingBind(RpAtomic* atomic, void* data);
extern "C" void fn_8014FF2C(RpClump* clump);
extern "C" void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
extern "C" void fn_8019EB94(RwFrame* frame, const RwV3d* translation, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, const RwV3d* scale, s32 combine);
extern "C" void fn_8019ED68(RwFrame* frame, const RwV3d* axis, f32 angle, s32 combine);
RwFrame* objRwFrameGetChildFrame(RwFrame* frame, RwFrame* after);

void TObjGoalring::Disp()
{
	if (lbl_8042C180[0x20] == 0 && !goalRingHasTwoRings()) {
		RwFrame* frame;
		RwV3d scale;
		u8 alpha;

		if (unkD8 <= goalRingZero[0]) {
			return;
		}
		lbl_802D5E80.SetCurrentNum(0x10);
		lbl_802D5E80.SetLightRegular(lbl_802D5E80.regular);
		frame   = ((GoalringClump*)effect)->frame;
		scale.y = goalRingEffectHeight[0];
		scale.x = scale.z = goalRingEffectHeight[0] * unkD8;
		fn_8019EC30(frame, &scale, 0);
		fn_8019EB94(frame, &pos, 2);
		frame = objRwFrameGetChildFrame(frame, NULL);
		fn_8019ED68(frame, &AxisY, unkE0, 0);
		frame = objRwFrameGetChildFrame(frame, NULL);
		fn_8019ED68(frame, &AxisZ, unkE8, 0);
		fn_8019ED68(frame, &AxisY, unkE4 - unkE0, 2);
		alpha = 0xFF;
		fn_8014FFBC(effect, goalRingBind, &alpha);
		fn_8014FF2C(effect);
	}
}
