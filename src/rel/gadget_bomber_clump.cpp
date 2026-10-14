#include "types.h"

// TEnemyGadgetBomber::DestroyClump and CloneClump (the PS2 build's names): the
// bomber destroys its motion manager, body and bomb, and clones them again
// from its two static models, with a motion manager on the body using the
// bomber's motions (not playing).

#include "src/rel/searcher.inc"

typedef struct GadgetBomber {
	TEnemyGadget base;
	TObjEnemy* enemy; // 0x38
	u8 unk3C[0x4];
	ENEMYMTNMAN* motion; // 0x40
	RpClump* bomb;       // 0x44
} GadgetBomber;

class TEnemyGadgetBomber
{
public:
	static RpClump* pClumpStatic[2];
};

extern "C" ENEMY_MOTION bomberMotions[];

extern "C" void fn_80150958(RpClump* clump);
extern "C" RpClump* fn_80150588(RpClump* clump);

extern "C" void DestroyClump__18TEnemyGadgetBomberFv(GadgetBomber* gadget)
{
	if (gadget->motion != NULL) {
		delete gadget->motion;
		gadget->motion = NULL;
	}
	if (gadget->base.pClump != NULL) {
		fn_80150958(gadget->base.pClump);
		gadget->base.pClump = NULL;
	}
	if (gadget->bomb != NULL) {
		fn_80150958(gadget->bomb);
		gadget->bomb = NULL;
	}
}

extern "C" void CloneClump__18TEnemyGadgetBomberFv(GadgetBomber* gadget)
{
	DestroyClump__18TEnemyGadgetBomberFv(gadget);
	gadget->base.pClump     = fn_80150588(TEnemyGadgetBomber::pClumpStatic[0]);
	gadget->bomb            = fn_80150588(TEnemyGadgetBomber::pClumpStatic[1]);
	gadget->motion          = new ENEMYMTNMAN;
	gadget->motion->clump   = gadget->base.pClump;
	gadget->motion->motions = bomberMotions;
	gadget->motion->active  = 0;
}
