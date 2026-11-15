// Render callback of a player's atomics (its custom render data holds the player number and the
// original callback; RpAtomicMCCGetCustomRenderCallBack): in team phase 9 (+0x154 of the team
// record +0x258) it uses light setup 0x12 of the light manager lbl_802D5E80, otherwise the
// player's own lights. With two or more teams (lbl_8042C204), a player of another team farther
// than 800 (squared 640000) from the current team's block (lbl_8042C208) is not drawn. Returns the
// atomic. HYPOTHESIS: the field roles.
#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct RpAtomic;

struct OBJ_CUSTOMRENDER {
	void* pData;                           // 0x0 (the player number)
	RpAtomic* (*callback)(RpAtomic* atom); // 0x4
};

class CLIGHT
{
public:
	void SetLightCurrentPlayer(s8 player);
	void SetLightRegular(s8 index);
	void SetCurrentNum(s8 num);
};

struct Team8003C7F0 {
	u8 pad0[0x154];
	s32 phase; // 0x154
};

struct Ctrl8003C7F0 {
	u8 pad0[0x258];
	Team8003C7F0* team; // 0x258
	s8 teamNumber;      // 0x25C
};

struct State8003C7F0 {
	u8 pad0[0x18];
	RwV3d position; // 0x18
};

f32 Distance2P2P(const RwV3d* a, const RwV3d* b);

extern "C" {
extern u8 lbl_802D5E80[]; // the CLIGHT object
extern Ctrl8003C7F0* lbl_802AD0D0[8];
extern State8003C7F0* lbl_802AD090[8];
extern s32 lbl_8042C204;
extern s32 lbl_8042C1FC;
extern RwV3d* lbl_8042C208;
extern f32 lbl_8042D0E0; // 640000.0f
OBJ_CUSTOMRENDER* RpAtomicMCCGetCustomRenderCallBack(RpAtomic* atomic);

RpAtomic* fn_8003C7F0(RpAtomic* atomic)
{
	OBJ_CUSTOMRENDER* cr = RpAtomicMCCGetCustomRenderCallBack(atomic);
	s32 player           = (s32)cr->pData;
	Ctrl8003C7F0* ctrl   = lbl_802AD0D0[player];

	if (ctrl != NULL && ctrl->team->phase == 9) {
		((CLIGHT*)lbl_802D5E80)->SetCurrentNum(0x12);
		((CLIGHT*)lbl_802D5E80)->SetLightRegular(((s8*)lbl_802D5E80)[0x4BE]);
	} else {
		((CLIGHT*)lbl_802D5E80)->SetLightCurrentPlayer(player);
	}
	if (lbl_8042C204 >= 2 && ctrl->teamNumber != lbl_8042C1FC
	    && Distance2P2P(lbl_8042C208, &lbl_802AD090[player]->position) > lbl_8042D0E0) {
		return atomic;
	}
	cr->callback(atomic);
	return atomic;
}
}
