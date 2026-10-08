// Complete C++ enemy/e_summon.cpp. Metadata supplies class and method names;
// GC establishes layout, behavior and the three emitted function bodies.
#include "game/enemy/e_summon.h"
#include "game/setObj.h"

char* CL_TEnemySummon = "TEnemySummon";
// Accessed prefixes only; the remaining external class layouts are opaque.
enum ACTIONMODE_TURN {
	ACTIONMODE_TURN_NONE,
	ACTIONMODE_TURN_CONTINUE,
	ACTIONMODE_TURN_RESTART,
	ACTIONMODE_TURN_GIVEUP,
	ACTIONMODE_TURN_MAX
};
struct SummonActionView {
	u8 unknown[0x18];
	ACTIONMODE_TURN restartFlag;
};
struct SummonModeView {
	u8 unknown[0x1f];
	s8 flag1f, flag20, flag21;
};
struct SummonSetGenView {
	u8 unknown[0x30];
	SETOBJ_PARAM* listTop[256];
};
struct SoundControl;
extern "C" {
extern SummonActionView lbl_8029C310;
extern SummonModeView* lbl_8042C180;
extern SummonSetGenView* lbl_8042C298;
extern TObject* lbl_8042C10C;
extern u16 e_start_uid_tbl[];
extern SoundControl* lbl_8042C388;
void fn_800FDC1C(u32, u32);
void fn_800FDD40(u32);
void fn_800FDE58(u32);
void fn_800B52E8(SoundControl*, s32, s32, s32);
}
// Local predicate names are reconstruction labels, not metadata claims.
static inline s32 SummonIsRestarting()
{
	ACTIONMODE_TURN restartFlag = lbl_8029C310.restartFlag;
	return (restartFlag == ACTIONMODE_TURN_CONTINUE || restartFlag == ACTIONMODE_TURN_RESTART)
	    || restartFlag == ACTIONMODE_TURN_GIVEUP;
}
static inline s32 SummonCanAdvance()
{
	if (lbl_8042C180->flag1f)
		return 0;
	if (lbl_8042C180->flag20)
		return 0;
	if (lbl_8042C180->flag21)
		return 0;
	return 1;
}
inline s32 TEnemySummon::SummonEnemy()
{
	SETOBJ_PARAM* plist = lbl_8042C298->listTop[mCommunicationId];
	if (!plist)
		return 0;
	while (plist) {
		for (s32 idx = 0; e_start_uid_tbl[idx]; ++idx) {
			if (plist->setData.uniqueId == e_start_uid_tbl[idx]) {
				plist->setData.condition.Flag &= ~0x02000000;
				break;
			}
		}
		plist = plist->next;
	}
	// This helper's result is discarded; its original success value is unknown.
	return 0;
}
inline s32 TEnemySummon::CreateSummonPtcl()
{
	fn_800FDC1C(mCommunicationId, 0x20);
	// The inlined call discards this result; the original value is unknown.
	return 0;
}
void TEnemySummon::Exec()
{
	if (SummonIsRestarting()) {
		fn_800FDD40(mCommunicationId);
		Signal |= 1;
		return;
	}
	if (!SummonCanAdvance())
		return;
	switch (mMode) {
		case 0:
			SummonEnemy();
			mMode  = 1;
			mTimer = 80;
			break;
		case 1:
			if (mTimer == 80) {
				CreateSummonPtcl();
				fn_800FDE58(mCommunicationId);
			}
			if (--mTimer < 0) {
				fn_800FDD40(mCommunicationId);
				if (lbl_8042C388)
					fn_800B52E8(lbl_8042C388, 0x405e, 0, 0);
				mMode = 2;
			}
			break;
		case 2:
			Signal |= 1;
			break;
	}
}
TEnemySummon::~TEnemySummon() { }
inline TEnemySummon::TEnemySummon(TObject* ptp, u8 communicationId)
    : TObject(ptp)
{
	ClassName        = CL_TEnemySummon;
	DispTime         = sizeof(TEnemySummon);
	mMode            = 0;
	mTimer           = 80;
	mCommunicationId = communicationId;
}
void TEnemySummon::Create(u8 communicationId)
{
	new TEnemySummon(lbl_8042C10C, communicationId);
}
