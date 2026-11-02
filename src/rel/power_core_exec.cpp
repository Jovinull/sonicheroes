#include "types.h"

// TEnemyPowerCore::Exec (the PS2 build's name), the same in the bonus stages
// (31D-33D). It asks to be killed while the game stands still. Otherwise a
// new core aims 50 above its place (state 1), rises ever slower to it until
// its time runs out (state 2) and then sinks to the ground; a touch (as
// CheckHitCollision does) in either state scores it (state 3): the toucher's
// team gets 100 points of its type (0, 2 or 1 by the core's type) when
// fn_80090790 says so, 500 otherwise, and the core asks to be killed. Its
// models and collision follow it.

#include "src/rel/power_core_class.inc"

class PARAM_SCORE
{
public:
	void addScore(s32 team, s32 kind, s32 score);
};

typedef struct TeamInfo TeamInfo;

struct PowerCoreHitter {
	u8 unk00[0x78];
	s32 player; // 0x78
};

struct PowerCoreHit {
	u8 unk00[0x4];
	PowerCoreHitter* hitter; // 0x04
};

struct RpClumpView {
	u8 unk00[0x4];
	struct RwFrame* frame; // 0x04
};

extern "C" u8 lbl_8042C1A4[];
extern "C" TeamInfo* lbl_80303DC8[];
extern "C" const sAngleView powerCoreNoAngle;
extern "C" const f32 powerCoreAim;
extern "C" const f32 powerCoreSlow;
extern "C" const f32 powerCoreSink;

extern "C" void fn_80021824(void* list);
extern "C" PowerCoreHit* fn_800211A8(C_COLLI* colli);
extern "C" s32 fn_800418A8(s32 player);
extern "C" s32 fn_80090790(TeamInfo* team, s32 kind, s32 arg);
extern "C" void fn_8019EB94(struct RwFrame* frame, RwV3d* translation, s32 combine);
extern "C" s32 fn_80017800(TEnemyPowerCore* object);

// TEnemyPowerCore::CheckHitCollision (rel/power_core_check_hit.cpp), inlined.
static inline s32 powerCoreCheckHit(TEnemyPowerCore* object)
{
	if (object->flags & 1) {
		PowerCoreHit* hit;
		PowerCoreHitter* hitter;

		fn_80021824(lbl_8042C1A4);
		hit = fn_800211A8(&static_cast<C_COLLI&>(*object));
		if (hit != NULL) {
			hitter = hit->hitter;
		} else {
			hitter = NULL;
		}
		if (hitter != NULL) {
			object->unkDC = hitter->player;
			return 1;
		}
	}
	return 0;
}

static inline void powerCoreScore(TEnemyPowerCore* object, s32 team, s32 kind)
{
	if (fn_80090790(lbl_80303DC8[team], kind, 1) != 0) {
		((PARAM_SCORE*)&object->params)->addScore(team, kind, 100);
	} else {
		((PARAM_SCORE*)&object->params)->addScore(team, kind, 500);
	}
}

extern "C" void Exec__15TEnemyPowerCoreFv(TEnemyPowerCore* object)
{
	if (powerCoreGameStopped()) {
		object->signal |= 1;
		return;
	}
	switch (object->unkE8) {
		case 0:
			object->params.unk18 = powerCoreAim + object->params.pos.y;
			object->unkE8        = 1;
			break;
		case 1:
			object->params.range.unk10 *= powerCoreSlow;
			object->params.pos.y += object->params.range.unk10;
			if (object->params.pos.y > object->params.unk18) {
				object->params.pos.y = object->params.unk18;
			}
			if (powerCoreCheckHit(object) != 0) {
				object->unkE8 = 3;
			}
			if (--object->unkE4 < 0) {
				object->unkE8 = 2;
			}
			break;
		case 2:
			object->params.pos.y -= powerCoreSink;
			if (object->params.pos.y < object->params.ground) {
				object->params.pos.y = object->params.ground;
			}
			if (powerCoreCheckHit(object) != 0) {
				object->unkE8 = 3;
			}
			break;
		case 3:
			if (object->unkDC != 0) {
				s32 team = fn_800418A8(object->unkDC);

				if (team != -1) {
					switch (object->params.type) {
						case 0:
							powerCoreScore(object, team, 0);
							break;
						case 1:
							powerCoreScore(object, team, 2);
							break;
						case 2:
							powerCoreScore(object, team, 1);
							break;
					}
				}
			}
			object->signal |= 1;
			break;
	}
	if (object->body != NULL) {
		fn_8019EB94(((RpClumpView*)object->body)->frame, &object->params.pos, 0);
	}
	if (object->shine != NULL) {
		fn_8019EB94(((RpClumpView*)object->shine)->frame, &object->params.pos, 0);
	}
	if (fn_80017800(object) != 0) {
		sAngleView ang = powerCoreNoAngle;

		object->prev.x = object->pos.x;
		object->prev.y = object->pos.y;
		object->prev.z = object->pos.z;
		object->pos.x  = object->params.pos.x;
		object->pos.y  = object->params.pos.y;
		object->pos.z  = object->params.pos.z;
		object->ang    = ang;
		object->Entry();
	}
}
