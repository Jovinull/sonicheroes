#include "types.h"

// TObjLightColliMaster::Exec (lightCollisionManagerExec here), the same in the
// thirteen stage modules that share the engine core. With no light collision
// left the master asks to be killed. Otherwise it picks, for each of the
// eight players, the light the player's collisions call for, walking the list
// from its head: a collision the player touches takes the slot when none is
// set yet (a kind-2 collision keeping the player's current light), or when it
// is not kind 1 and either names the light already in the player's slot or
// the slot was set by a kind-1 collision. Then each player whose pick is unset
// or is its current light goes back to it with a free slot, and the others
// switch to the pick, which the slot remembers.

typedef struct LightColli {
	u8 unk00[0x30];
	s8 touched[8]; // 0x30
	s8 light;      // 0x38
	s8 kind;       // 0x39
	u8 unk3A[0x2];
	struct LightColli* next; // 0x3C
} LightColli;

typedef struct LightSlot {
	s8 light;
	s8 unk1;
} LightSlot;

typedef struct LightMaster {
	u8 unk0[0x4];
	u16 signal; // 0x4
} LightMaster;

class CLIGHT
{
public:
	u8 unk000[0x4BF];
	s8 current[8]; // 0x4BF
	s8 players[8]; // 0x4C7

	void SetCurrentNumPlayer(s8 player, s8 num);
};

extern "C" CLIGHT lbl_802D5E80;
extern "C" LightColli* lightCollisionHead;
extern "C" LightSlot lightCollisionSlots[8];

extern "C" void lightCollisionManagerExec(LightMaster* object)
{
	LightColli* top = lightCollisionHead;
	LightColli* colli;
	s8 light[8];
	s8 kind[8];
	s8 i;

	if (top == NULL) {
		object->signal |= 1;
		return;
	}

	colli = top;
	if (colli == NULL) {
		light[0] = -1;
		light[1] = -1;
		light[2] = -1;
		light[3] = -1;
		light[4] = -1;
		light[5] = -1;
		light[6] = -1;
		light[7] = -1;
	} else {
		while (colli != NULL) {
			for (i = 0; i < 8; i++) {
				if (colli == top) {
					light[i] = -1;
					kind[i]  = -1;
				}
				if (colli->touched[i] == 1) {
					if (light[i] < 0) {
						if (colli->kind == 2) {
							light[i] = lbl_802D5E80.players[i];
						} else {
							light[i] = colli->light;
						}
						kind[i] = colli->kind;
					} else if (colli->kind != 1) {
						if (colli->light == lightCollisionSlots[i].light || kind[i] == 1) {
							light[i] = colli->light;
							kind[i]  = colli->kind;
						}
					}
				}
			}
			colli = colli->next;
		}
	}

	for (i = 0; i < 8; i++) {
		if (light[i] < 0 || light[i] == lbl_802D5E80.players[i]) {
			if (lbl_802D5E80.current[i] != lbl_802D5E80.players[i]) {
				lbl_802D5E80.SetCurrentNumPlayer(i, lbl_802D5E80.players[i]);
			}
			lightCollisionSlots[i].light = -1;
		} else {
			if (light[i] != lbl_802D5E80.current[i]) {
				lbl_802D5E80.SetCurrentNumPlayer(i, light[i]);
			}
			lightCollisionSlots[i].light = light[i];
		}
	}
}
