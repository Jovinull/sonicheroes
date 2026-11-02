#include "types.h"

// TObjLightColli::Exec (lightCollisionExec here), the same in the thirteen
// stage modules that share the engine core. Out of range or told to die, the
// collision asks to be killed. On an edit it takes the placement's light and
// kind again. Then, by kind: kinds 0 and 2 keep each player's flag set while
// the player's body touches it; kind 1 (a switch) turns its light on for a
// player that touches it, off in every other switch, and on for the player's
// two teammates when the player leads the team; kind 3 turns it off the same
// way. Kind 3 clears its first teammate's flag twice: the second teammate
// asked for is never used.

typedef struct LightCollisionParams {
	s8 light; // 0x00
	s8 kind;  // 0x01
} LightCollisionParams;

typedef struct Frame {
	u8 unk00[0x2C];
	LightCollisionParams* params; // 0x2C
} Frame;

typedef struct Motion {
	Frame* frame;  // 0x00
	void** vtable; // 0x04
} Motion;

typedef struct LightCollision {
	u8 unk00[0x4];
	u16 signal; // 0x04
	u8 unk06[0x22];
	Motion motion; // 0x28
	s8 lights[8];  // 0x30
	s8 light;      // 0x38
	s8 kind;       // 0x39
	u8 pad3A[0x2];
	struct LightCollision* next; // 0x3C
} LightCollision;

typedef struct Team {
	u8 unk000[0x3A];
	s8 leader; // 0x3A
	u8 unk03B[0xD5];
	s8 members[3]; // 0x110
} Team;

extern "C" LightCollision* lightCollisionHead;

extern "C" s32 CheckRangeOut__10TObjSetObjFv(Motion* motion);
extern "C" s32 CheckMustKill__10TObjSetObjFv(Motion* motion);
extern "C" s32 OnEdit__10TObjSetObjFv(Motion* motion);
extern "C" s32 CheckCollisionedPlayerBody__14TObjLightColliFi(LightCollision* object, s32 player);
extern "C" Team* fn_800924E4(s32 player);
extern "C" s32 fn_800927D0(Team* team, s32 member);

// TObjLightColliMaster::SetAllSwitchLightOff (rel/light_collision_master.cpp),
// inlined.
static inline void lightCollisionSwitchOff(s32 no)
{
	LightCollision* colli;

	for (colli = lightCollisionHead; colli != NULL; colli = colli->next) {
		if (colli->kind == 1 && colli->lights[no] == 1) {
			colli->lights[no] = 0;
		}
	}
}

static inline void lightCollisionTurnOn(LightCollision* object, s32 no)
{
	lightCollisionSwitchOff(no);
	object->lights[no] = 1;
}

static inline void lightCollisionTurnOff(LightCollision* object, s32 no)
{
	object->lights[no] = 0;
	lightCollisionSwitchOff(no);
}

// A team leader's teammates follow the leader's light.
static inline void lightCollisionTeamOn(LightCollision* object, s8 player)
{
	Team* team = fn_800924E4(player);

	if (team != NULL && player == team->members[team->leader]) {
		object->lights[team->members[fn_800927D0(team, 1)]] = 1;
		object->lights[team->members[fn_800927D0(team, 2)]] = 1;
	}
}

static inline void lightCollisionTeamOff(LightCollision* object, s8 player)
{
	Team* team = fn_800924E4(player);

	if (team != NULL && player == team->members[team->leader]) {
		s32 member = team->members[fn_800927D0(team, 1)];

		object->lights[member] = 0;
		fn_800927D0(team, 2);
		object->lights[member] = 0;
	}
}

extern "C" void lightCollisionExec(LightCollision* object)
{
	LightCollisionParams* params = object->motion.frame->params;

	if (CheckRangeOut__10TObjSetObjFv(&object->motion) != 0
	    || CheckMustKill__10TObjSetObjFv(&object->motion) != 0) {
		object->signal |= 1;
		return;
	}
	if (OnEdit__10TObjSetObjFv(&object->motion) != 0) {
		object->light = params->light;
		object->kind  = params->kind;
	}

	switch (params->kind) {
		case 0:
		case 2: {
			u8 i;

			for (i = 0; i < 8; i++) {
				if (object->lights[i] == 1) {
					s32 off = 0;

					if (CheckCollisionedPlayerBody__14TObjLightColliFi(object, i) == 0) {
						off = 1;
					}
					if (off == 1) {
						object->lights[i] = 0;
					}
				} else if (CheckCollisionedPlayerBody__14TObjLightColliFi(object, i) != 0) {
					object->lights[i] = 1;
				}
			}
			break;
		}
		case 1: {
			s8 i;

			for (i = 0; i < 8; i++) {
				if (CheckCollisionedPlayerBody__14TObjLightColliFi(object, i) != 0) {
					lightCollisionTurnOn(object, i);
					{
						Team* team = fn_800924E4((s8)i);

						if (team != NULL && (s8)i == team->members[team->leader]) {
							s32 index;

							index                                = fn_800927D0(team, 1);
							object->lights[team->members[index]] = 1;
							index                                = fn_800927D0(team, 2);
							object->lights[team->members[index]] = 1;
						}
					}
				}
			}
			break;
		}
		case 3: {
			s8 i;

			for (i = 0; i < 8; i++) {
				if (CheckCollisionedPlayerBody__14TObjLightColliFi(object, i) != 0) {
					lightCollisionTurnOff(object, i);
					{
						Team* team = fn_800924E4((s8)i);

						if (team != NULL && (s8)i == team->members[team->leader]) {
							s32 index;
							s8* light;

							index                                            = fn_800927D0(team, 1);
							*(light = &object->lights[team->members[index]]) = 0;
							fn_800927D0(team, 2);
							*light = 0;
						}
					}
				}
			}
			break;
		}
	}
}
