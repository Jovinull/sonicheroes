#include "types.h"

// TObjEnemyCapture::Exec (captureExec here; the PS2 build's class name), the
// same in the seven stage modules that carry the capture. It runs while the
// game is neither paused nor in its two other stop states (and is shown
// unless paused), forgets its held player on stop state 1, follows its
// collision, runs the enemy steps and the damage check, searches and catches
// a player (as captureSearchCatch does), updates its motion, runs its mode
// (phase 1), lets a held player go once the team's follower is set (as
// captureFreePlayerCheck does), poses itself, spins its parts while shown (as
// captureSpinParts does), places its last part, and moves its collision with
// it when fn_80017800 allows.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct RwFrame RwFrame;
typedef struct RwMatrix RwMatrix;

namespace nSearchPlayer
{
s32 GetTeamNoFromPlayerNum(s32 player);
s32 GetNearestPlayerNum(const RwV3d* pos, f32 distance);
}

class C_COLLI
{
public:
	void Entry();

	u8 unk00[0x10];
	void* data; // 0x10
	u8 unk14[0x4C];
	RwV3d pos;  // 0x60
	sAngle ang; // 0x6C
	u8 unk78[0x4];
	RwV3d prev; // 0x7C
}; // 0x88

class CaptureMotion
{
public:
	virtual ~CaptureMotion();
	virtual void Update(void* owner);
};

typedef struct CapturePart {
	u8 unk00[0x4];
	RwFrame* frame; // 0x04
} CapturePart;

typedef struct CaptureTeam {
	u8 unk000[0x14E];
	s16 follower; // 0x14E
	u8 unk150[0x4];
	s32 state; // 0x154
} CaptureTeam;

typedef struct CapturePlayer CapturePlayer;

struct CaptureBase {
	u8 unk000[0x18];
};

// TObjEnemy's virtual functions up to its mode function (slot 0x50).
class Capture : public CaptureBase
{
public:
	virtual ~Capture();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char* message);
	virtual void Render();
	virtual void Virtual2C();
	virtual void Virtual30();
	virtual void Virtual34();
	virtual void CheckDamage2();
	virtual void DestroyMyself();
	virtual void Explosion();
	virtual void InitMode();
	virtual void ExecMode();
	virtual void ExitMode();
	virtual void Mode(s32 kind, s32 phase);

	u8 unk01C[0xC];
	C_COLLI colli; // 0x028
	u8 unk0B0[0x90];
	RwV3d pos;  // 0x140
	sAngle ang; // 0x14C
	u8 unk158[0x44];
	s32 kind; // 0x19C
	u8 unk1A0[0xA0];
	CaptureMotion* motion; // 0x240
	u8 unk244[0x24];
	void* anchors[3]; // 0x268
	s32 found;        // 0x274
	s32 player;       // 0x278
	u8 unk27C[0x4];
	s32 caught; // 0x280
	s32 angle;  // 0x284
	f32 pulse;  // 0x288
	s32 spin;   // 0x28C
	u8 unk290[0x48];
	CapturePart* parts[5]; // 0x2D8
	void* lastAnchor;      // 0x2EC
	u8 unk2F0[0x280];
	s32 catchKind; // 0x570
	s32 active;    // 0x574
	s32 shown;     // 0x578
};

extern "C" u8* lbl_8042C180;
extern "C" CapturePlayer* lbl_802AD070[];
extern "C" CaptureTeam* lbl_80303DC8[];
extern "C" const RwV3d AxisY;
extern "C" const f32 captureSearchDrop;
extern "C" const f32 captureSearchRange;
extern "C" const f32 captureHalfTurn;
extern "C" const f32 captureHalf;

extern "C" void fn_800A5B34(Capture* object);
extern "C" void fn_800A3D94(Capture* object);
extern "C" void fn_800A3D48(Capture* object);
extern "C" s32 fn_80017800(Capture* object);
extern "C" void captureUpdateFrame(Capture* object);
extern "C" s32 fn_800AB25C(s32 player);
extern "C" s32 fn_800AB2E0(CapturePlayer* body);
extern "C" s32 fn_80089204(CapturePlayer* body);
extern "C" void fn_80043F28(CapturePlayer* body);
extern "C" void fn_800E1208(s32 player, s32 mode, s32 arg);
extern "C" RwMatrix* fn_8019E8EC(void* anchor);
extern "C" void fn_8019ECCC(RwFrame* frame, RwMatrix* matrix, s32 combine);
extern "C" void fn_8019ED68(RwFrame* frame, const RwV3d* axis, f32 angle, s32 combine);
extern "C" f32 fn_800D7B00(s32 angle);

// captureCatchPlayer (rel/capture_catch_player.cpp), inlined.
static inline s32 captureCatch(Capture* object)
{
	s32 found = object->found;

	if (found != -1) {
		CapturePlayer* body = lbl_802AD070[found];

		if (body != NULL && fn_800AB2E0(body) != 0) {
			if (fn_80089204(body) != 0) {
				object->catchKind = 1;
			} else {
				object->catchKind = 2;
				fn_80043F28(body);
			}
			fn_800E1208(object->found, 0x17, 0);
			object->player = object->found;
			return 1;
		}
		object->catchKind = 0;
	}
	return 0;
}

// captureSearchCatch (rel/capture_search_catch.cpp), inlined.
static inline s32 captureSearch(Capture* object)
{
	if (object->player != -1) {
		return 0;
	}
	switch (object->kind) {
		case 2:
		case 6:
		case 9:
		case 0x2C:
			break;
		default:
			return 0;
	}

	RwV3d at = object->pos;

	at.y -= captureSearchDrop;
	object->found = nSearchPlayer::GetNearestPlayerNum(&at, captureSearchRange);
	if (object->found != -1 && fn_800AB25C(object->found) == 1) {
		return captureCatch(object);
	}
	return 0;
}

// captureFreePlayerCheck (rel/capture_free_player_check.cpp), inlined.
static inline void captureFreeCheck(Capture* object)
{
	if (object->player != -1) {
		s32 team = nSearchPlayer::GetTeamNoFromPlayerNum(object->player);

		if (team != -1) {
			CaptureTeam* info = lbl_80303DC8[team];

			if (info != NULL) {
				s32 follower;

				if (info->state != 9) {
					follower = -1;
				} else {
					follower = info->follower;
				}
				if (follower != -1 && object->player != -1) {
					fn_800E1208(object->player, 0xF, 0);
					object->player = -1;
				}
			}
		}
	}
}

// captureSpinParts (rel/capture_spin_parts.cpp), inlined.
static inline void captureSpin(Capture* object)
{
	if (object->spin != 0) {
		CapturePart* part = object->parts[0];

		if (part != NULL && object->anchors[2] != NULL) {
			RwFrame* frame = part->frame;

			fn_8019ECCC(frame, fn_8019E8EC(object->anchors[2]), 0);
		}
		part = object->parts[1];
		if (part != NULL && object->anchors[0] != NULL) {
			RwFrame* frame = part->frame;

			fn_8019ED68(frame, &AxisY, captureHalfTurn, 0);
			fn_8019ECCC(frame, fn_8019E8EC(object->anchors[0]), 2);
		}
		part = object->parts[2];
		if (part != NULL && object->anchors[1] != NULL) {
			RwFrame* frame = part->frame;

			fn_8019ED68(frame, &AxisY, captureHalfTurn, 0);
			fn_8019ECCC(frame, fn_8019E8EC(object->anchors[1]), 2);
		}
		object->angle += 0x1000;
		{
			f32 sine = fn_800D7B00(object->angle);

			object->pulse = captureHalf + captureHalf * sine;
		}
	}
}

extern "C" void captureExec(Capture* object)
{
	s32 active;

	if ((s8)lbl_8042C180[0x1F] != 0) {
		active = 0;
	} else if ((s8)lbl_8042C180[0x20] != 0) {
		active = 0;
	} else if ((s8)lbl_8042C180[0x21] != 0) {
		active = 0;
	} else {
		active = 1;
	}
	object->active = active;
	object->shown  = (s8)lbl_8042C180[0x1F] != 0 ? 0 : 1;
	if ((s8)lbl_8042C180[0x21] == 1) {
		object->player = -1;
	}
	if (object->colli.data != NULL) {
		object->pos.x = object->colli.pos.x;
		object->pos.y = object->colli.pos.y;
		object->pos.z = object->colli.pos.z;
	}
	fn_800A5B34(object);
	object->CheckDamage2();
	fn_800A3D94(object);
	if (object->active != 0) {
		object->caught = captureSearch(object);
	}
	if (object->motion != NULL) {
		object->motion->Update(object);
	}
	object->Mode(object->kind, 1);
	captureFreeCheck(object);
	captureUpdateFrame(object);
	fn_800A3D48(object);
	if (object->shown != 0) {
		captureSpin(object);
	}
	if (object->lastAnchor != NULL) {
		CapturePart* part = object->parts[4];

		if (part != NULL) {
			RwFrame* frame = part->frame;

			fn_8019ECCC(frame, fn_8019E8EC(object->lastAnchor), 0);
		}
	}
	if (fn_80017800(object) != 0 && object->colli.data != NULL) {
		object->colli.prev.x = object->colli.pos.x;
		object->colli.prev.y = object->colli.pos.y;
		object->colli.prev.z = object->colli.pos.z;
		object->colli.pos.x  = object->pos.x;
		object->colli.pos.y  = object->pos.y;
		object->colli.pos.z  = object->pos.z;
		object->colli.ang.x  = object->ang.x;
		object->colli.ang.y  = object->ang.y;
		object->colli.ang.z  = object->ang.z;
		object->colli.Entry();
	}
}
