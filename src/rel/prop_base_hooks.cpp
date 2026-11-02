#include "types.h"

// Small hooks of a common stage object base (propBase here; the class has no
// PS2 name), the same in the six stage modules that carry it: a TObject with
// its collision at 0x28 and a score parameter at 0xB0 whose first word holds
// the object's flags. The hooks turn the collision on or off together with
// flag 0x800 (off) or 0x20 (hit), check for a player in state 0x53, set the
// four sounds, score a destroyed object and wake a player.

class PARAM_SCORE
{
public:
	void addPlayerScore(s32 player, s32 score);
	s32 isFlag(u32 flag) { return (flags & flag) != 0; }

	u32 flags; // 0x00
};

typedef struct PropPlayer {
	s16 state;  // 0x00
	s16 state2; // 0x02
} PropPlayer;

typedef struct PropContact {
	u8 unk00[0x78];
	s32 who; // 0x78
} PropContact;

typedef struct PropBase {
	u8 unk000[0x2E];
	s16 timer; // 0x02E
	u16 colli; // 0x030
	u8 unk032[0x7E];
	PARAM_SCORE param; // 0x0B0
	u8 unk0B4[0x2C];
	s32 score; // 0x0E0
	u8 unk0E4[0x4];
	s16 sounds[4]; // 0x0E8
	u8 unk0F0[0x4];
	f32 life; // 0x0F4
} PropBase;

extern "C" PropPlayer* lbl_802AD090[];
extern "C" void* lbl_802AD070[];
extern "C" const f32 propBaseZero;

extern "C" s32 fn_80041B64(s32 who);
extern "C" void fn_800AB42C(void* body);

extern "C" void propBaseOn(PropBase* object)
{
	object->colli |= 0x40;
	object->param.flags &= ~0x800;
}

extern "C" void propBaseOff(PropBase* object)
{
	object->colli &= ~0x40;
	object->param.flags |= 0x800;
}

extern "C" void propBaseClearHit(PropBase* object)
{
	object->colli |= 0x40;
	object->param.flags &= ~0x20;
}

extern "C" void propBaseSetHit(PropBase* object)
{
	object->colli &= ~0x40;
	object->param.flags |= 0x20;
}

// Clears the hit once no player is in state 0x53 any more.
extern "C" s32 propBaseCheckRelease(PropBase* object)
{
	u8 i;

	if (object->param.isFlag(0x800) == 1) {
		return 0;
	}
	for (i = 0; i < 8; i++) {
		PropPlayer* player = lbl_802AD090[i];

		if (player != NULL && (player->state == 0x53 || player->state2 == 0x53)) {
			return 0;
		}
	}
	object->colli |= 0x40;
	object->param.flags &= ~0x20;
	return 1;
}

// Sets the hit when the touching player is in state 0x53.
extern "C" s32 propBaseCheckHit(PropBase* object, PropContact* contact)
{
	PropPlayer* player;

	if (object->param.isFlag(0x800) == 1) {
		return 0;
	}
	player = lbl_802AD090[fn_80041B64(contact->who)];
	if (player != NULL && (player->state == 0x53 || player->state2 == 0x53)) {
		object->colli &= ~0x40;
		object->param.flags |= 0x20;
		return 1;
	}
	return 0;
}

extern "C" void propBaseSetSounds(PropBase* object)
{
	object->sounds[0] = 0x4056;
	object->sounds[1] = 0x4057;
	object->sounds[2] = 0x4058;
	object->sounds[3] = 0x4059;
}

// Once out of life the object is destroyed and the player scores it.
extern "C" void propBaseScore(PropBase* object, s32 player)
{
	if (object->life <= propBaseZero) {
		object->timer = 0;
		object->param.flags |= 0x10;
		object->param.addPlayerScore(player, object->score);
	}
}

extern "C" void propBaseWakePlayer(PropBase* object, s32 player)
{
	if (lbl_802AD070[player] != NULL) {
		fn_800AB42C(lbl_802AD070[player]);
	}
}
