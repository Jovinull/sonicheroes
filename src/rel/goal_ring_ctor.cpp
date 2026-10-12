#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// TObjGoalring's constructor (the PS2 build's TObjGoalring::__ct). It takes the
// placement's position and angles, starts in state 1 with its scales set, and
// makes either the two-part ring (front, registered with the world, and back)
// or the plain ring, lit by the placement's light bits, then the effect model,
// and gives the collision its shape with flag 0x40.
//
// A real constructor over bases with destructors. The light bits are read
// before each clump, as the volatile reads keep them (as in
// rel/tri_spring_ctor.cpp); the collision is set up through a reference, so
// there is no null test on the base pointer.

class TObjGoalring : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 state;         // 0xB8
	RwV3d pos;         // 0xBC
	sAngle ang;        // 0xC8
	s32 unkD4;         // 0xD4
	f32 unkD8;         // 0xD8
	f32 unkDC;         // 0xDC
	f32 unkE0;         // 0xE0
	f32 unkE4;         // 0xE4
	f32 unkE8;         // 0xE8
	RpClump* ring;     // 0xEC
	RpClump* ring2;    // 0xF0
	RpClump* ringBack; // 0xF4
	u8 padF8[0x4];
	RpClump* effect; // 0xFC

	TObjGoalring(TObject* parent);
	// Exec comes first so that it is the key function (see rel/goal_ring_dtor.cpp).
	virtual void Exec();
	virtual ~TObjGoalring();
};

struct GoalringTeam {
	u8 pad00[0x34];
	s32 kind; // 0x34
};

struct GoalringMission {
	u8 pad00[0x4];
	s32 index; // 0x04
};

struct GoalringStage {
	u8 pad00[0x34];
	GoalringMission* mission; // 0x34
};

extern "C" u8* lbl_8042C1D0;
extern "C" s8* lbl_8042C180;
extern "C" GoalringTeam* lbl_80303DC8[];
extern "C" GoalringStage lbl_8029C310;
extern "C" s32 stageMissionFlags[];
extern "C" char* CL_TObjGoalring;
extern "C" RpClump* goalRingModel;
extern "C" RpClump* goalRingModel2;
extern "C" RpClump* goalRingBackModel;
extern "C" RpClump* goalRingEffectModel;
extern "C" CCL_INFO goalRingCclInfo;
extern "C" const f32 goalRingStartScale[1];
extern "C" const f32 goalRingZero[1];

extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, s32 count, s32 kind);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump* clump, u32 light);

// Whether the stage shows the two-part ring: team kind 3 on a mission the
// stage's table flags, or team kinds 1 and 2 with the game's byte 0x28 set.
// The answer goes through an s32, as the retail tests it.
static inline s32 goalRingHasTwoRings()
{
	s32 kind = lbl_80303DC8[0]->kind;
	bool two = kind == 3;
	if (two) {
		two = stageMissionFlags[lbl_8029C310.mission->index] == 1;
	}
	if (!two) {
		two = kind == 1;
		if (!two) {
			two = kind == 2;
		}
		if (two) {
			two = lbl_8042C180[0x28] == 1;
		}
	}
	return two;
}

TObjGoalring::TObjGoalring(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjGoalring;
	DispTime  = 0x100;
	pos       = ObjParam->setData.pos;
	ang       = ObjParam->setData.ang;
	unkD4     = 0;
	unkD8     = goalRingStartScale[0];
	unkDC     = goalRingZero[0];
	unkE0     = goalRingZero[0];
	unkE4     = goalRingZero[0];
	unkE8     = goalRingZero[0];
	state     = 1;
	if (goalRingHasTwoRings()) {
		ring  = NULL;
		ring2 = fn_80150588(goalRingModel2);
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), ring2);
		u32 lightFront = *(volatile u32*)&ObjParam->setData.condition.Flag;
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
		    ring2, ((lightFront & 0x1C0000) >> 18) + 4);
		ringBack      = fn_80150588(goalRingBackModel);
		u32 lightBack = *(volatile u32*)&ObjParam->setData.condition.Flag;
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
		    ringBack, ((lightBack & 0x1C0000) >> 18) + 4);
	} else {
		ring = fn_80150588(goalRingModel);
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), ring);
		u32 light = *(volatile u32*)&ObjParam->setData.condition.Flag;
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(ring, ((light & 0x1C0000) >> 18) + 4);
		ring2    = NULL;
		ringBack = NULL;
	}
	effect         = fn_80150588(goalRingEffectModel);
	C_COLLI& colli = *this;
	fn_8003BF04(&colli, &goalRingCclInfo, 1, 5);
	flag |= 0x40;
}
