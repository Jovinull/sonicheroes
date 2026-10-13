#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// As in game/gparam.h (which clashes with eff_bomb.h's RwV3d).
class PARAM_VICTORY
{
public:
	static s8 num[4];
	void addVictory(s32, s32);
	void setVictory(s32, s32);
};

// TObjGoalring (the PS2 build's class): the goal ring, either the plain ring
// or, on mission and versus stages, the two-part ring (front and back).

// PARAM_VICTORY is an empty base: it sits at 0xB8, where addVictory gets its
// `this`.
class TObjGoalring : public TObject, public TObjSetObj, public C_COLLI, public PARAM_VICTORY
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
	RpClump* effect;   // 0xFC

	TObjGoalring(TObject* parent);
	// Exec comes first so that it is the key function: no unit of ours emits
	// the vtable, which stays in each module's data.
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual ~TObjGoalring();
	virtual void EditOnChange(SETDATA_PARAM* param);
	u8 CheckDispBackRing();
	void CheckAndSetPlayerReached();
	// The collision base without the null test a pointer conversion makes.
	C_COLLI& Colli() { return *this; }
}; // 0x100

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

extern "C" s8* lbl_8042C180;
extern "C" GoalringTeam* lbl_80303DC8[];
extern "C" GoalringStage lbl_8029C310;
extern "C" s32 stageMissionFlags[];

// Whether the stage shows the two-part ring: team kind 3 on a mission the
// stage's table flags, or team kinds 1 and 2 with the game's byte 0x28 set
// (CheckDispBackRing, inlined).
static inline bool goalRingTwoRings()
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

// The members test it as an s32, as the retail does.
static inline s32 goalRingHasTwoRings()
{
	return goalRingTwoRings();
}
