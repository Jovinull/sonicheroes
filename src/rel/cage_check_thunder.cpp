#include "types.h"

// TObjCage::CheckThunderShoot (the PS2 build's name; cageCheckThunderShoot
// here): it goes through what hit the cage's collision as kind 0xF (a thunder
// shot) and keeps the player behind the last one (fn_80041B64 of the hitter's
// type); when there was one, the cage goes to state 3.

typedef struct CageHitter {
	u8 pad000[0x78];
	s32 type; // 0x78
} CageHitter;

typedef struct CageHit {
	u8 pad00[0x4];
	CageHitter* hitter; // 0x04
} CageHit;

typedef struct Cage {
	u8 base[0x30];  // 0x00
	u8 colli[0x10]; // 0x30
	u8 unk40[0xB0]; // 0x40
	s32 state;      // 0xF0
} Cage;

extern "C" u8 lbl_8042C1A4[];
extern "C" void fn_80021824(void* world);
extern "C" CageHit* fn_80020BD8(void* colli, s32 kind);
extern "C" s32 fn_80041B64(s32 type);

static inline CageHitter* cageThunderHitter(CageHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

extern "C" void cageCheckThunderShoot(Cage* object)
{
	s32 shooter = -1;
	CageHitter* hitter;

	fn_80021824(lbl_8042C1A4);
	while ((hitter = cageThunderHitter(fn_80020BD8(object->colli, 0xF))) != NULL) {
		shooter = fn_80041B64(hitter->type);
	}
	if (shooter != -1) {
		object->state = 3;
	}
}
