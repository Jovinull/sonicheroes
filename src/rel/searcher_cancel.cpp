#include "types.h"

// TObjEnemySearcher (the PS2 build's names, but for the first, which the PS2
// build lacks): searcherPlaySound plays the searcher's sound 0x4000 where it
// is (what rel/searcher_sound_limit.cpp does for each searcher it collects);
// Cancel cancels the gadget's attack; AddItemBox drops an item box where the
// searcher was destroyed.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RpClump RpClump;

struct TEnemyGadgetBase {
	u8 unk00[0x18];
};

// TEnemyGadget's vtable as in game/enemy/e_gadget.h up to slot 0x40, the PS2
// build's Cancel (DelClump there, inline, which would put a copy here; its
// object check pins that name)
class TEnemyGadget : public TEnemyGadgetBase
{
public:
	virtual ~TEnemyGadget();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char* message);
	virtual void Render();
	virtual void SetClump(RpClump* clump);
	virtual void Update();
	virtual void DispOpaq();
	virtual void DispTrans();
	virtual s32 ReqGadgetMode(s32 mode);
	virtual void Cancel();
};

typedef struct Searcher {
	u8 unk000[0x140];
	RwV3d pos; // 0x140
	u8 unk14C[0x11C];
	TEnemyGadget* gadget; // 0x268
} Searcher;

namespace nItemBox
{
void CreateItemBox(RwV3d* pos);
}

extern "C" void* lbl_8042C388;

extern "C" void fn_800B4A38(void* sound, s32 id, void* position, void* owner, s32 a, s32 b, s32 c);

extern "C" void searcherPlaySound(Searcher* searcher)
{
	if (lbl_8042C388 != NULL) {
		fn_800B4A38(lbl_8042C388, 0x4000, &searcher->pos, searcher, 3, 0, 2);
	}
}

extern "C" void Cancel__17TObjEnemySearcherFv(Searcher* searcher)
{
	if (searcher->gadget != NULL) {
		searcher->gadget->Cancel();
	}
}

extern "C" void AddItemBox__17TObjEnemySearcherFP5RwV3d(Searcher* searcher, RwV3d* pos)
{
	nItemBox::CreateItemBox(pos);
}
