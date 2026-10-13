#include "types.h"

// TObjEnemySearcher::CloneClump (the PS2 build's name): destroys what it had
// (DestroyClump, inline), then clones its body (the plain or the textured
// model), its gadget's model and the gadget for its kind (1 needle, 2 shot,
// 3 machine gun, 4 laser, 5 bomber, 6 search light; the bomber has no model),
// the four lit and dark clumps (put in the world, hidden), the parts when the
// stage has them, and a motion manager.

#include "src/rel/searcher.inc"

#include "src/rel/searcher_destroy_clump.inc"

class TObjEnemySearcher;

class TEnemyGadgetNeedle : public TEnemyGadget
{
public:
	TEnemyGadgetNeedle(TObjEnemySearcher* owner);
	u8 unk38[0xC];
};

class TEnemyGadgetShot : public TEnemyGadget
{
public:
	TEnemyGadgetShot(TObjEnemySearcher* owner);
	u8 unk38[0x10];
};

class TEnemyGadgetMGun : public TEnemyGadget
{
public:
	TEnemyGadgetMGun(TObjEnemySearcher* owner);
	u8 unk38[0x18];
};

class TEnemyGadgetLaser : public TEnemyGadget
{
public:
	TEnemyGadgetLaser(TObjEnemySearcher* owner);
	u8 unk38[0x23C];
};

class TEnemyGadgetBomber : public TEnemyGadget
{
public:
	TEnemyGadgetBomber(TObjEnemySearcher* owner);
	u8 unk38[0x28];
};

class TEnemyGadgetSearchLight : public TEnemyGadget
{
public:
	TEnemyGadgetSearchLight(TObjEnemySearcher* owner);
	u8 unk38[0x18];
};

extern "C" RpClump* searcherModels[];

void objRpClumpForAllAtomicsToHide(RpClump* clump);
extern "C" RpClump* fn_80150588(RpClump* clump);
extern "C" void fn_8015BB08(RpWorld* world, RpClump* clump);

extern "C" void CloneClump__17TObjEnemySearcherFv(Searcher* searcher)
{
	TObjEnemySearcher* owner = (TObjEnemySearcher*)searcher;
	s32 i;

	DestroyClump__17TObjEnemySearcherFv(searcher);
	searcher->clump     = searcher->plainTexture == 0 ? fn_80150588(searcherModels[0])
	                                                  : fn_80150588(searcherModels[1]);
	searcher->bodyClump = NULL;
	searcher->gadget    = NULL;
	switch (searcher->kind) {
		case 0:
			break;
		case 1:
			searcher->bodyClump = fn_80150588(searcherModels[7]);
			break;
		case 2:
			searcher->bodyClump = fn_80150588(searcherModels[3]);
			break;
		case 3:
			searcher->bodyClump = fn_80150588(searcherModels[4]);
			break;
		case 4:
			searcher->bodyClump = fn_80150588(searcherModels[5]);
			break;
		case 5:
			break;
		case 6:
			searcher->bodyClump = fn_80150588(searcherModels[2]);
			break;
	}
	switch (searcher->kind) {
		case 0:
			break;
		case 1:
			searcher->gadget = new TEnemyGadgetNeedle(owner);
			searcher->gadget->SetClump(searcher->bodyClump);
			break;
		case 2:
			searcher->gadget = new TEnemyGadgetShot(owner);
			searcher->gadget->SetClump(searcher->bodyClump);
			break;
		case 3:
			searcher->gadget = new TEnemyGadgetMGun(owner);
			searcher->gadget->SetClump(searcher->bodyClump);
			break;
		case 4:
			searcher->gadget = new TEnemyGadgetLaser(owner);
			searcher->gadget->SetClump(searcher->bodyClump);
			break;
		case 5:
			searcher->gadget = new TEnemyGadgetBomber(owner);
			break;
		case 6:
			searcher->gadget = new TEnemyGadgetSearchLight(owner);
			searcher->gadget->SetClump(searcher->bodyClump);
			break;
	}
	searcher->clumps[0] = fn_80150588(searcherModels[10]);
	searcher->clumps[1] = fn_80150588(searcherModels[11]);
	searcher->clumps[2] = fn_80150588(searcherModels[8]);
	searcher->clumps[3] = fn_80150588(searcherModels[9]);
	for (i = 0; i < 4; i++) {
		fn_8015BB08(lbl_8042C1D0->world, searcher->clumps[i]);
		objRpClumpForAllAtomicsToHide(searcher->clumps[i]);
	}
	if (searcherModels[12] != NULL) {
		searcher->partsClump = fn_80150588(searcherModels[12]);
	}
	searcher->motion = new ENEMYMTNMAN;
}
