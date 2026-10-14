#include "game/effect/eff_bomb.h"
#include "game/object.h"

// ENEMY_SHIELD::SetShieldStatusForDisp (the PS2 build's name): a kind 0 shield
// shows one piece per hit it has left (up to six), by switching each atomic's
// render flag through enemyShieldAtomicStatus (ours) with a bit mask.

#include "src/rel/enemy_shield.inc"

struct ShieldAtomic {
	u8 type;    // 0x00
	u8 subType; // 0x01
	u8 flags;   // 0x02
};

extern "C" RpClump* fn_8014FFBC(
    RpClump* clump, ShieldAtomic* (*callback)(ShieldAtomic*, void*), void* data);
extern "C" ShieldAtomic* enemyShieldAtomicStatus(ShieldAtomic* atomic, void* data);

void ENEMY_SHIELD::SetShieldStatusForDisp(RpClump* clump)
{
	int mask;

	switch (kind) {
		case ENEMY_SHIELD_KIND_0:
			if (hits >= 6) {
				mask = 0x3F;
			} else if (hits >= 5) {
				mask = 0x1F;
			} else if (hits >= 4) {
				mask = 0xF;
			} else if (hits >= 3) {
				mask = 7;
			} else if (hits >= 2) {
				mask = 3;
			} else {
				mask = 1;
			}
			break;
		case ENEMY_SHIELD_KIND_1:
		case ENEMY_SHIELD_KIND_2:
			return;
	}
	fn_8014FFBC(clump, enemyShieldAtomicStatus, &mask);
}

extern "C" ShieldAtomic* enemyShieldAtomicStatus(ShieldAtomic* atomic, void* data)
{
	int* mask = (int*)data;

	if (*mask & 1) {
		atomic->flags |= 4;
	} else {
		atomic->flags &= ~4;
	}
	*mask >>= 1;
	return atomic;
}
