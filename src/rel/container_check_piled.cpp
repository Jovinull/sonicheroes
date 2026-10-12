// TObjContainer::CheckPiled (the PS2 build's name): whether the crate rests on
// another one. It goes through what its collision touches as kind 1 and, for
// the first hitter the crate is above by no more than 21, sets the crate's
// ground height to 20 above that hitter's and answers 1; otherwise 0. Exec
// inlines it; this copy has no caller and is kept with force_active. The class
// is in game/obj_container.h.

#include "game/obj_container.h"

struct ContainerPile {
	u8 pad00[0x64];
	f32 y; // 0x64
};

struct ContainerPileHit {
	u8 pad00[0x4];
	ContainerPile* hitter; // 0x04
};

extern "C" const f32 containerZero[1];
extern "C" const f32 containerPileReach[1];
extern "C" const f32 containerPileHeight[1];
extern "C" void fn_80021824(C_COLLI& colli);
extern "C" ContainerPileHit* fn_80020BD8(C_COLLI& colli, s32 kind);

static inline ContainerPile* containerPile(ContainerPileHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

s32 TObjContainer::CheckPiled()
{
	ContainerPile* pile;

	fn_80021824(*this);
	while ((pile = containerPile(fn_80020BD8(*this, 1))) != NULL) {
		f32 above = pos.y - pile->y;
		if (above <= containerPileReach[0] && above > containerZero[0]) {
			height = containerPileHeight[0] + pile->y;
			return 1;
		}
	}
	return 0;
}
