// Complete enemy/e_iconman.cpp, including the GC-added mission-failure task.
// PS2 symbolic metadata supplies names/types; GC supplies behavior and ownership.
#include "game/enemy/e_iconman.h"

// Partial external views: only the fields accessed by this unit are exposed.
struct IconActionView {
	u8 unknown[0xc];
	s32 Mode;
};
struct IconModeView {
	s8 flags[0x30];
	s32 words[6];
};
struct IconVoiceView {
	u8 unknown[0x30];
	s32 field30;
	u8 unknown34[8];
	s32 field3c;
	u8 unknown40[0x18];
	s32 field58;
};
struct IconInputView {
	u8 unknown[0x18];
	s32 cleared[6];
};
extern "C" {
extern IconActionView lbl_8029C310;
extern IconModeView* lbl_8042C180;
extern IconVoiceView* lbl_8042C610;
extern IconInputView lbl_8029BBD0;
extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C114;
void fn_80111578(IconVoiceView*, s32);
void fn_80018C4C();
void fn_80019720(IconActionView*);
}
char* CL_TEnemyIconMan = "TEnemyIconMan";
extern "C" {
char* lbl_8042B7AC = "TMissionFailure";
TMissionFailure* lbl_8042C5B8;
}

// External e_icon.cpp contract. GC confirms the first nine virtual slots.
class TEnemyIcon
{
public:
	virtual ~TEnemyIcon();
	virtual void Update();
	virtual void DispOpaq();
	virtual void DispTrans();
	virtual void On(f32, f32);
	virtual void On(f32, f32, s32);
	virtual void Off();
	virtual s32 FrustumTest();
	virtual void ResetParam();
	void SetPos(const RwV3d* pos, const RwV3d* offset)
	{
		mIconFlag |= 4;
		mPos.x = pos->x;
		mPos.y = pos->y;
		mPos.z = pos->z;
		if (offset) {
			mOffset.x = offset->x;
			mOffset.y = offset->y;
			mOffset.z = offset->z;
		}
	}

	RwV3d mPos, mOffset;
	s32 mLife, mMode;
	u32 mIconFlag;
	RpClump* mpClump;
	RpClump* mpClumpBase;
	f32 mScaleX, mScaleY;
};
// These external concrete classes are only allocated here. Unaccessed tails
// retain their GC allocation extent; constructors remain in their owning TU.
class TEnemyIconQuestion : public TEnemyIcon
{
public:
	TEnemyIconQuestion();

private:
	u8 externalState[0x14];
};
class TEnemyIconSleep : public TEnemyIcon
{
public:
	TEnemyIconSleep();

private:
	u8 externalState[0x24];
};
class TEnemyIconEffect : public TEnemyIcon
{
public:
	TEnemyIconEffect();

private:
	u8 externalState[0x14];
};
class TEnemyIconNote : public TEnemyIcon
{
public:
	TEnemyIconNote();

private:
	u8 externalState[0x14];
};
class TEnemyIconCountDown : public TEnemyIcon
{
public:
	TEnemyIconCountDown();

private:
	u8 externalState[0x14];
};
class TEnemyIconHP : public TEnemyIcon
{
public:
	TEnemyIconHP(s32);

private:
	u8 externalState[0x60];
};
class TEnemyIconFreeze : public TEnemyIcon
{
public:
	TEnemyIconFreeze();

private:
	u8 externalState[0x14];
};
class TEnemyIconCross : public TEnemyIcon
{
public:
	TEnemyIconCross();

private:
	u8 externalState[0x14];
};
class TEnemyIconCircle : public TEnemyIcon
{
public:
	TEnemyIconCircle();

private:
	u8 externalState[0x14];
};
class TEnemyIconSearch : public TEnemyIcon
{
public:
	TEnemyIconSearch();

private:
	u8 externalState[0x8];
};
// Database ABI already independently established by the complete database TU.
enum eEnemyDataBase { ENEMY_DB_ICON = 1 };
struct IconDataBaseEntry {
	void* addr;
	s32 filenum;
};
class TEnemyDataBase
{
public:
	TEnemyDataBase();
	s32 Delete(eEnemyDataBase);
	s32 Add(eEnemyDataBase, char*);
	static TEnemyDataBase* mpDataBase;
	static TEnemyDataBase* GetInstance()
	{
		if (!mpDataBase)
			new TEnemyDataBase;
		return mpDataBase;
	}
	IconDataBaseEntry entries[14];
};

inline TMissionFailure::TMissionFailure()
    : TObject(lbl_8042C2A0)
{
	ClassName    = lbl_8042B7AC;
	DispTime     = sizeof(TMissionFailure);
	state        = 0;
	lbl_8042C5B8 = this;
}
void TEnemyIconMan::Initialize()
{
	TEnemyDataBase::GetInstance()->Add(ENEMY_DB_ICON, "en_icon.one");
}
void TEnemyIconMan::Finalize()
{
	TEnemyDataBase::GetInstance()->Delete(ENEMY_DB_ICON);
}
TEnemyIconMan* TEnemyIconMan::Create(eEnemyIcon icon)
{
	return new TEnemyIconMan(icon);
}
void TEnemyIconMan::CreateIconInstance(eEnemyIcon icon)
{
	TEnemyIcon* p = 0;
	switch (icon) {
		case E_ICON_HP:
			p = new TEnemyIconHP(1);
			break;
		case E_ICON_GC_10:
			p = new TEnemyIconHP(0);
			break;
		case E_ICON_SEARCH:
			p = new TEnemyIconSearch;
			break;
		case E_ICON_FREEZE:
			p = new TEnemyIconFreeze;
			break;
		case E_ICON_COUNTDOWN:
			p = new TEnemyIconCountDown;
			break;
		case E_ICON_CIRCLE:
			p = new TEnemyIconCircle;
			break;
		case E_ICON_CROSS:
			p = new TEnemyIconCross;
			break;
		case E_ICON_NOTE:
			p = new TEnemyIconNote;
			break;
		case E_ICON_EFFECT:
			p = new TEnemyIconEffect;
			break;
		case E_ICON_SLEEP:
			p = new TEnemyIconSleep;
			break;
		case E_ICON_QUESTION:
			p = new TEnemyIconQuestion;
			break;
	}
	mpIcon = p;
}
TEnemyIconMan::~TEnemyIconMan()
{
	if (mpIcon) {
		delete mpIcon;
		mpIcon = 0;
	}
}
void TEnemyIconMan::Exec()
{
	if (mpIcon)
		mpIcon->Update();
}
void TEnemyIconMan::Disp()
{
	switch (lbl_8029C310.Mode) {
		case 4:
		case 8:
			return;
		default:
			s32 canDisplay;
			if (lbl_8042C180->flags[0x1f])
				canDisplay = 0;
			else if (lbl_8042C180->flags[0x20])
				canDisplay = 0;
			else
				canDisplay = 1;
			if (canDisplay) {
				if (lbl_8042C180->words[4] < 0 && mpIcon) {
					if (mpIcon->FrustumTest() == 1)
						mpIcon->DispOpaq();
				}
			}
			break;
	}
}
void TEnemyIconMan::SetPos(const RwV3d* pos, const RwV3d* offset)
{
	if (mpIcon)
		mpIcon->SetPos(pos, offset);
}
void TEnemyIconMan::On(f32 a, f32 b)
{
	if (mpIcon) {
		switch (mIconNo) {
			case E_ICON_HP:
				if (a > 0.0f)
					mpIcon->On(a, b);
				break;
			case E_ICON_SEARCH:
				if (lbl_8042C180->flags[0x25] == 1 || lbl_8042C180->flags[0x25] == 4)
					fn_8010AF38();
				mpIcon->On(a, b);
				break;
			default:
				mpIcon->On(a, b);
				break;
		}
	}
}
void TEnemyIconMan::On(f32 a, f32 b, s32 c)
{
	if (mpIcon) {
		switch (mIconNo) {
			case E_ICON_HP:
				if (a > 0.0f)
					mpIcon->On(a, b, c);
				break;
			case E_ICON_SEARCH:
				if (lbl_8042C180->flags[0x25] == 1 || lbl_8042C180->flags[0x25] == 4)
					fn_8010AF38();
				mpIcon->On(a, b, c);
				break;
			default:
				mpIcon->On(a, b, c);
				break;
		}
	}
}
void TEnemyIconMan::Off()
{
	if (mpIcon)
		mpIcon->Off();
}
void TEnemyIconMan::Change(eEnemyIcon icon)
{
	if (mIconNo != icon) {
		if (mpIcon) {
			delete mpIcon;
			mpIcon = 0;
		}
		mIconNo = icon;
		CreateIconInstance(mIconNo);
	}
}
void TEnemyIconMan::Close()
{
	Signal |= 1;
}
s32 TEnemyIconMan::IsOn()
{
	if (mpIcon)
		return mpIcon->mMode == 2 || mpIcon->mMode == 3;
	return 0;
}
inline TEnemyIconMan::TEnemyIconMan(eEnemyIcon icon)
    : TObject(lbl_8042C114)
{
	ClassName = CL_TEnemyIconMan;
	DispTime  = sizeof(TEnemyIconMan);
	mpIcon    = 0;
	mIconNo   = icon;
	CreateIconInstance(mIconNo);
}
extern "C" void fn_8010AF38()
{
	if (!lbl_8042C5B8)
		new TMissionFailure;
}
TMissionFailure::~TMissionFailure()
{
	lbl_8042C5B8 = 0;
}
void TMissionFailure::Exec()
{
	switch (state) {
		case 0:
			if (lbl_8042C610)
				fn_80111578(lbl_8042C610, 0x12b);
			state = 1;
			break;
		case 1:
			lbl_8029BBD0.cleared[0] = 0;
			lbl_8029BBD0.cleared[1] = 0;
			lbl_8029BBD0.cleared[2] = 0;
			lbl_8029BBD0.cleared[3] = 0;
			lbl_8029BBD0.cleared[4] = 0;
			lbl_8029BBD0.cleared[5] = 0;
			fn_80018C4C();
			if (lbl_8042C610) {
				s32 done = lbl_8042C610->field30 == 0 && lbl_8042C610->field3c == 0
				    && lbl_8042C610->field58 == -1;
				if (done)
					state = 2;
			} else
				state = 2;
			break;
		case 2:
			if (lbl_8042C180->flags[0x20] == 0) {
				fn_80019720(&lbl_8029C310);
				Signal |= 1;
			}
			break;
	}
}
