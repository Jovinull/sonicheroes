#include "types.h"

// TEnemyGadgetLaser::Update, DestroyClump and CloneClump (the PS2 build's
// names): the laser keeps its body on the searcher's jet frame; while the game
// runs it steps its charge sparks when readying (pre-attack), else its
// collision is cleared; its six parts and three beams are destroyed and cloned
// from its nine static models (pClumpStatic).

#include "src/rel/searcher.inc"

typedef struct RwMatrixTag RwMatrixTag;

class C_COLLI
{
public:
	void ClearInfo();
};

typedef struct GadgetLaser {
	TEnemyGadget base;
	u8 colli[0x88];  // 0x38, a C_COLLI
	Searcher* enemy; // 0xC0
	u8 unkC4[0x34];
	RpClump* parts[6]; // 0xF8
	RpClump* beams[3]; // 0x110
} GadgetLaser;

typedef struct GameState {
	u8 unk00[0x1F];
	s8 paused;  // 0x1F
	s8 stopped; // 0x20
	s8 ending;  // 0x21
} GameState;

class TEnemyGadgetLaser
{
public:
	static RpClump* pClumpStatic[9];
};

extern "C" GameState* lbl_8042C180;

extern "C" RwMatrixTag* fn_8019E8EC(RwFrame* frame);
extern "C" void fn_8019ECCC(RwFrame* frame, RwMatrixTag* matrix, s32 combine);
extern "C" void fn_80150958(RpClump* clump);
extern "C" RpClump* fn_80150588(RpClump* clump);
extern "C" void UpdataSparkFrame__17TEnemyGadgetLaserFv(GadgetLaser* gadget);

static inline int searcherGameRuns()
{
	if (lbl_8042C180->paused) {
		return 0;
	}
	if (lbl_8042C180->stopped) {
		return 0;
	}
	if (lbl_8042C180->ending) {
		return 0;
	}
	return 1;
}

extern "C" void Update__17TEnemyGadgetLaserFv(GadgetLaser* gadget)
{
	RwFrame* frame = gadget->base.pClump->frame;

	if (frame != NULL) {
		RwMatrixTag* matrix = fn_8019E8EC(gadget->enemy->jetFrame);

		if (matrix != NULL) {
			fn_8019ECCC(frame, matrix, 0);
		}
	}
	if (!searcherGameRuns()) {
		((C_COLLI*)gadget->colli)->ClearInfo();
	} else {
		switch (gadget->base.gmode) {
			case TEnemyGadget::E_GM_STANDBY:
				break;
			case TEnemyGadget::E_GM_PREATTACK:
				UpdataSparkFrame__17TEnemyGadgetLaserFv(gadget);
				break;
			case TEnemyGadget::E_GM_ATTACK:
			case TEnemyGadget::E_GM_POSTATTACK:
				break;
		}
	}
}

extern "C" void DestroyClump__17TEnemyGadgetLaserFv(GadgetLaser* gadget)
{
	int i;

	for (i = 2; i >= 0; i--) {
		if (gadget->beams[i] != NULL) {
			fn_80150958(gadget->beams[i]);
			gadget->beams[i] = NULL;
		}
	}
	for (i = 5; i >= 0; i--) {
		if (gadget->parts[i] != NULL) {
			fn_80150958(gadget->parts[i]);
			gadget->parts[i] = NULL;
		}
	}
}

extern "C" void CloneClump__17TEnemyGadgetLaserFv(GadgetLaser* gadget)
{
	DestroyClump__17TEnemyGadgetLaserFv(gadget);
	gadget->parts[0] = fn_80150588(TEnemyGadgetLaser::pClumpStatic[3]);
	gadget->parts[1] = fn_80150588(TEnemyGadgetLaser::pClumpStatic[4]);
	gadget->parts[2] = fn_80150588(TEnemyGadgetLaser::pClumpStatic[5]);
	gadget->parts[3] = fn_80150588(TEnemyGadgetLaser::pClumpStatic[6]);
	gadget->parts[4] = fn_80150588(TEnemyGadgetLaser::pClumpStatic[7]);
	gadget->parts[5] = fn_80150588(TEnemyGadgetLaser::pClumpStatic[8]);
	gadget->beams[0] = fn_80150588(TEnemyGadgetLaser::pClumpStatic[0]);
	gadget->beams[1] = fn_80150588(TEnemyGadgetLaser::pClumpStatic[1]);
	gadget->beams[2] = fn_80150588(TEnemyGadgetLaser::pClumpStatic[2]);
}
