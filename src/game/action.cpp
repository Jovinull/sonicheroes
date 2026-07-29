typedef signed char s8;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*RawCallback)();
typedef void (*RawCallback2)(s32, s32);

enum ACTIONMODE {
	ACTIONMODE_0 = 0,
};

struct MainState {
	u8 pad[0x18];
	s8 field18;
	u8 pad19[5];
	s8 field1E;
};

struct TeamObject {
	u8 pad00[59];
	s8 player;
	u8 pad3C[212];
	s8 leaders[1];
};

struct BitFlag {
	u32 bits;

	BitFlag() { }
	BitFlag(u32 value)
	    : bits(value)
	{
	}
	BitFlag(const BitFlag& other)
	    : bits(other.bits)
	{
	}
	inline ~BitFlag() { }
};

struct ActionDispEntry {
	void (*callback)(void*, const BitFlag&);
	s32 index;
	BitFlag option;
};

struct ExecTable {
	s32 team;
	s32 value;
	s32 stage;
	s32 enabled;
};

struct EventManagerBase {
	u8 pad[0x18];
};

struct EventManager : EventManagerBase {
	virtual void method08();
	virtual void method0C();
	virtual void method10();
	virtual void method14();
	virtual void method18();
	virtual void method1C();
	virtual void method20();
	virtual void method24();
	virtual void method28();
	virtual void method2C();
	virtual void method30();
	virtual void method34();
	virtual void method38();
	virtual void method3C();
	virtual void method40();
	virtual void method44();
	virtual void method48();
	virtual void finish();
	virtual void method50();
	virtual void method54();
	virtual void method58();
};

struct EventManagerLate : EventManagerBase {
	virtual void method00();
	virtual void method04();
	virtual void method08();
	virtual void method0C();
	virtual void method10();
	virtual void method14();
	virtual void method18();
	virtual void method1C();
	virtual void method20();
	virtual void method24();
	virtual void method28();
	virtual void method2C();
	virtual void method30();
	virtual void method34();
	virtual void method38();
	virtual void method3C();
	virtual void method40();
	virtual void method44();
	virtual void method48();
	virtual void finish();
	virtual void method50();
	virtual void method54();
	virtual void method58();
};

struct RawTaskBase {
	u8 pad00[0x18];
};

struct RawTask : RawTaskBase {
	virtual void end(s32);
};

struct FadeScreenBase {
	u8 pad00[0x18];
};

struct RwRGBA {
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
};

struct FADESCREEN : FadeScreenBase {
	virtual void method08();
	virtual void method0C();
	virtual void method10();
	virtual void method14();
	virtual void method18();
	virtual void method1C();
	virtual void method20();
	virtual void method24();
	virtual void method28();
	virtual void method2C();
	virtual void method30();
	virtual void method34();
	virtual void method38();
	virtual void method3C();
	virtual void method40();
	virtual void method44();
	u8 pad1C[0xC];
	s32 mode;
	u32 foregroundColor;
	u32 backgroundColor;

	void SetBackgroundColorDefault();
	static void SetBackgroundColor(RwRGBA* color);
	void BlackOut();
	void FadeOut();
	void FlashOut();
	void Disp_Uso();
	void FlashIn();
	void FadeIn();
	void BlackIn();
	void WhiteIn();
};

struct StageNameEntry {
	s32 stage;
	const char* name;
};

struct ACTION {
	u8 pad00[4];
	void* object;
	u8 pad08[4];
	s32 mode;
	s32 nextMode;
	s32 transition;
	s32 processState;
	s32 pauseMode;
	s32 pauseDisabled;
	s32 playerCount;
	s32 stageCount;
	s32 stageNumber;
	void** stageTable;
	struct StageInfo {
		s32 field0;
		s32 stage;
		u8 pad08[4];
		void (*pause)();
		u8 pad10[4];
		void (*restart)();
	}* currentStage;
	u8 pad38[4];
	s32 stageConnect[64];
	s32 stageConnectOriginal[64];
	s32 teams[4];
	s32 pauseChoice;
	s32 execFlag;
	s32 softReset;
	s32 execPending;
	s32 execStarted;
	s32 execPhase;
	s32 execFrames;
	s32 execFramesLeft;
	u32 palFrame;
	void (*execCallback)();
	void (*pauseCallback)();
	s32 goalActive;
	s32 goalState;
	s32 lastLeader;
	void* stageSet;
	s32 countdown;
	s32 specialFlag;
	s32 challengeState;

	s32 IsBonusStageConnect(s32 index);
	s32 IsSpecialStageConnect(s32 index);
	s32 IsSpecialStage();
	s32 IsBonusStage();
	s32 IsSpecialAndBonusStage();
	void InsertStage(s32 stage);
	void eventChecker();
	s32 restartStage();
	void SetPlayMode(s32 playMode, s32 gameRule);
	void SetTeam(s32 player, s32 team);
	void SetStageConnect(s32 stageCount, s32 stage);
	void InitStageAndTeamInfo();
	s32 GetCurrentStageNumber();
	void* GetCurrentStageName();
	void FreezeStage();
	void GiveUpStage();
	void InitRestartStage();
	void BackToBeginningOfStage();
	void RestartStage();
	void ContinueStage();
	void EndPose();
	void StartPose();
	void SetGoalAction(s32 teamNo);
	void StepStage();
	void ExitPauseMode();
	void EnterPauseMode();
	void CheckPauseOff();
	static void dispAlpha(void* world, BitFlag option);
	static void dispPunch(void* world, BitFlag option);
	static void dispOpeq(void* world, BitFlag option);
	inline s32 CheckPauseOn();
	s32 Exec();
	s32 Loop();
	void subEnd();
	void subInit();
	void End();
	void Init();
	void Entry2DFunc(RawCallback callback);
};

extern ACTION Action;
extern MainState* lbl_8042C180;
extern EventManager* lbl_8042C170;
extern u8 lbl_8029C2E4[];
extern u8 lbl_8042C1A4;
extern void* lbl_8042C1F8;
extern void* lbl_8042C298;
extern u8 lbl_8042C308;
extern u8 lbl_8042C304[3];
extern RwRGBA lbl_8042AEB0;
extern RwRGBA lbl_8042AEAC;
extern u8 lbl_80240D0C[];
extern StageNameEntry lbl_80240B10[];
extern RawTask* lbl_80303DC8[];
extern s32 lbl_80303D44[];
extern void* lbl_8042C388;
extern void* lbl_8042C6D0;
extern u8 lbl_803E774C[];
extern u8 lbl_8029BBD0[];
extern u32 lbl_8042C160;
extern u32 lbl_8042C164;
extern u32 lbl_8042C15C;
extern u32 lbl_8042C168;
extern u32 lbl_8042AEA0;
extern s32 lbl_8042C21C;
extern s32 lbl_8042C224;
extern u8 lbl_8042C1C0;
extern void* lbl_8042C1D0;
extern void* lbl_8042C0F8;
extern void* lbl_8042C0FC;
extern void* lbl_8042C100;
extern void* lbl_8042C104;
extern s32 lbl_802408F8[];
extern u8 lbl_803A6690[];
extern void** lbl_8042C9A4;
extern void* lbl_8042C1FC;
extern s32 lbl_8042C200;
extern s32 lbl_8042C710;
extern EventManager* lbl_8042C760;
extern u8 lbl_8042C7E0;
extern void* lbl_8042C148;
extern void* lbl_8042C108;
extern u8 lbl_8029C728[];
extern u8 lbl_8029C5A8[];
extern u8 __vt__8SEQUENCE[];
extern u8 lbl_80240E2C[];
extern u8 lbl_803E73B0[];
extern void* lbl_803E7F88[];
extern float lbl_8042CFDC;
extern float lbl_8042CFE0;
extern u32 lbl_8042CFD8;
extern u8 lbl_8042AE98;
extern "C" s32 CheckSoftReset(s32 mode);
extern "C" void fn_800A74BC(s32 mode);
extern "C" void fn_800CB6EC();
extern "C" void fn_8001F4E8(MainState* state, s32 field, s32 value);
inline void fn_8001F4E8(u32 state, s32 field, s32 value)
{
	fn_8001F4E8((MainState*)state, field, value);
}
extern "C" void fn_80016778(void* task);
extern "C" void fn_80016BBC(void* task);
extern "C" void fn_800215A8(void* object);
extern "C" void fn_8004ED48(void* object);
extern "C" void fn_8005A298(void* object, s32 mode);
inline void fn_8004ED48(u32 object)
{
	fn_8004ED48((void*)object);
}
inline void fn_8005A298(u32 object, s32 mode)
{
	fn_8005A298((void*)object, mode);
}
extern "C" void fn_80066ED8(void* object, s32 mode);
extern "C" void fn_80066D68(void* object, u8 red, u8 green, u8 blue);
extern "C" void fn_800B4684(void* object, s32 mode);
inline void fn_800B4684(u32 object, s32 mode)
{
	fn_800B4684((void*)object, mode);
}
extern "C" void fn_800CB84C();
extern "C" void fn_8001F600();
extern "C" void fn_80066AFC(void* object, s32 stage, s32 value);
inline void fn_80066AFC(u32 object, s32 stage, u32 value)
{
	fn_80066AFC((void*)object, stage, (s32)value);
}
extern "C" void fn_80066EA0(void* object);
extern "C" void fn_8011C6EC();
extern "C" void fn_8011C0C4(void* object);
extern "C" void* fn_80116D2C(void* object);
extern "C" void fn_8009C2D4(void* team);
extern "C" void fn_800A0A4C(s32 teamNo);
extern "C" u32 OSGetTick();
extern "C" void fn_801AD5E0(s32 mode);
extern "C" void fn_8004E6F0(void* object, s32 index);
extern "C" void fn_800422C4(void* object);
extern "C" void fn_80018368(void* object);
extern "C" void ChkController();
extern "C" void EndDemoData();
extern "C" void fn_800B9180();
extern "C" void fn_8005EC14();
extern "C" void fn_800A73B4();
extern "C" void fn_8001DF6C();
extern "C" void fn_80016514(void*);
extern "C" void fn_800CE010();
extern "C" void fn_801125D8(void*);
extern "C" void fn_8020577C();
extern "C" void fn_8016F084();
extern "C" void fn_800A76E4(void*);
extern "C" void fn_800A7820();
extern "C" void fn_8016EF70();
extern "C" void fn_80205624();
extern "C" void fn_8016EE28(float);
extern "C" void fn_8016EE58(float);
extern "C" void* RsPathnameCreate(void*);
extern "C" void fn_8016E054();
extern "C" void RsPathnameDestroy(void*);
extern "C" void fn_8011264C(void*);
extern "C" void fn_800CE0CC();
extern "C" void fn_801125D4(void*);
extern "C" void fn_801126B4(void*);
extern "C" void fn_8001E000();
extern "C" void fn_800A7428();
extern "C" void fn_8005ED88();
extern "C" void fn_800B9408();
extern "C" void fn_80112618(void*);
extern "C" void fn_8012D97C();
extern "C" void fn_800CD138();
extern "C" void fn_8002171C(void*);
extern "C" void fn_80042310(void*, void*);
extern "C" void* fn_80018A34(void*, s32);
extern "C" void fn_8009DFE0(void*, s32, s32, s32, s32, s32, void*);
extern "C" void fn_80066B48(void*, s32, s32);
extern "C" void fn_8004F0F8(s32);
extern "C" void fn_800C731C();
extern "C" void MakeGameKeyData();
extern "C" void fn_8004A05C();
extern "C" void SetAndGetDemoData();
extern "C" void fn_8004AF4C(void* object);
extern "C" s32 repCheck(void* input, s32 bit, s32 repeat, s32 mode);
extern "C" s32 ConvertBit_AD(void* input, s32 bit);
extern "C" void fn_800B52E8(void* object, s32 sound, s32 arg2, s32 arg3);
inline void fn_800B52E8(s32 object, s32 sound, s32 arg2, s32 arg3)
{
	fn_800B52E8((void*)object, sound, arg2, arg3);
}
extern "C" void fn_80194234(s32 index, s32 mode);
extern "C" void fn_80177C50(void* object);
extern "C" void fn_8019CC00(void* world);
inline void fn_8019CC00(u32 world)
{
	fn_8019CC00((void*)world);
}
extern "C" void fn_8015B93C(void* object, void* world);
inline void fn_8015B93C(u32 object, u32 world)
{
	fn_8015B93C((void*)object, (void*)world);
}
extern "C" void fn_8004D568(void* object);
extern "C" void fn_8015B8E8(void* object, void* world);
extern "C" void* fn_8019CC28(void* world);
extern "C" void* fn_8019CC28_noarg();
extern "C" void fn_8019CC00_noarg();
extern "C" void fn_800122B4_noarg();
extern "C" void fn_80177C50_noarg();
extern "C" void fn_800CD6A0(void* object);
extern "C" void fn_800CDE58(void* object, s32 index);
extern "C" void fn_8004DC80(void* object, s32 mode);
extern "C" void RsCameraShowRaster(void* world);
extern "C" void fn_800B7BDC();
extern "C" void fn_800BEEF0();
extern "C" void fn_8019CF28(void* world, void* color, s32 mode);
extern "C" void* fn_800A7658();
extern "C" void fn_8019EE04(void* object);
extern "C" void fn_8004AF04(void* object);
extern "C" void fn_8004EBE0(void* object, s32 index);
extern "C" void fn_8004E7EC(void* object, s32 index);
extern "C" void fn_8001682C(void* task);
extern "C" void fn_8004ACF4(void* object);
extern "C" void fn_8004A6F0(void* object, s32 arg1, s32 index, s32 arg3);
extern "C" s32 fn_8004A5B8(void* object, s32 index, void* filter);
extern "C" void fn_8011253C();
extern "C" void fn_800C4C18();
extern "C" void fn_800B6E64();
extern "C" void fn_80052DD4(void* object, void* world);
extern "C" void fn_8004D678(void* object);
extern "C" void fn_8004D650(void* object);
extern "C" void fn_801AFFB0(s32, s32, s32, s32, s32);
extern "C" void fn_801AF914(s32);
extern "C" void fn_800B8904(void* world);
extern "C" void fn_80016910(void* task);
extern "C" void fn_80159754(void* world);
extern "C" void fn_800169F4(void* task);
extern "C" void fn_80016AD8(void* task);
extern "C" void fn_800B6DC8();
extern u8 lbl_802D5E80[];
extern u8 lbl_803EDBD0[];
extern s8 lbl_80240D00[];
extern ExecTable lbl_802895B8[];
extern "C" void fn_80066474(void* object, s32 mode);
extern "C" void fn_80066454(s8* a, s8* b, s8* c);
extern "C" s32 fn_8012DA08();
extern "C" void* memcpy(void* destination, const void* source, unsigned long size);
extern "C" s32 fn_800166E8(void*);
extern "C" s32 fn_8001D540();
extern "C" void fn_8001D56C(RwRGBA*);
extern "C" s32 fn_8001D718();
extern "C" s32 fn_800421C8(void*, u32);
extern "C" s32 fn_8004B144(void*);
inline s32 fn_8004B144(u32 object)
{
	return fn_8004B144((void*)object);
}
extern "C" s32 fn_8004EF98();
extern "C" s32 fn_80053B9C(void*);
extern "C" s32 fn_8005952C(void*);
extern "C" s32 fn_8005A5EC(void*);
inline s32 fn_8005952C(u32 object)
{
	return fn_8005952C((void*)object);
}
inline s32 fn_8005A5EC(u32 object)
{
	return fn_8005A5EC((void*)object);
}
extern "C" s32 fn_8005B558();
extern "C" s32 fn_8005E8EC();
extern "C" s32 fn_800662BC();
extern "C" s32 fn_80066D4C(void*, void*, void*, void*);
extern "C" s32 fn_80066E80(void*);
extern "C" s32 fn_8009C618(RawTask*);
extern "C" s32 fn_8009C704(s32, s32);
extern "C" void fn_8009250C(RawTask*);
extern "C" void fn_8009D2E0(RawTask*);
extern "C" s32 fn_800A7338();
extern "C" u32 fn_800A7648();
extern "C" s32 fn_800B113C();
extern "C" s32 fn_800B44A0(void*);
extern "C" s32 fn_800B48B8(void*);
extern "C" s32 fn_800B603C(void*);
inline s32 fn_800B44A0(u32 object)
{
	return fn_800B44A0((void*)object);
}
inline s32 fn_800B48B8(u32 object)
{
	return fn_800B48B8((void*)object);
}
inline s32 fn_800B603C(u32 object)
{
	return fn_800B603C((void*)object);
}
extern "C" s32 fn_800B7B30();
extern "C" s32 fn_800BF5D8();
extern "C" s32 fn_800C59C4();
extern "C" s32 fn_800C6F28();
extern "C" void fn_800CDE58(void*, s32);
extern "C" void VIWaitForRetrace();
extern "C" void ChkController();
extern "C" s32 fn_800CB750();
extern "C" s32 fn_800CB95C();
extern "C" s32 fn_800CC7E8();
extern "C" s32 fn_800CD05C();
extern "C" s32 fn_80110A4C();
extern "C" s32 fn_801169A4(s32, u32, s32);
extern "C" s32 fn_80116B84(void*);
extern "C" s32 fn_8012C3E8();
extern "C" s32 fn_8012DA84();
extern "C" s32 fn_8012DAA0();
extern "C" s32 fn_80130484();
extern "C" s32 fn_8013057C();
extern "C" s32 fn_801306BC();
extern "C" s32 fn_80138414(void*, s32);
extern "C" s32 fn_801388C4(void*, s32);
extern "C" s32 fn_80196D00();
extern "C" s32 fn_801C3C04(u32, void*);

#define DAT_802408f8 lbl_802408F8[0]
#define DAT_802408fc lbl_802408F8[1]
#define DAT_8029bbe8 (*(s32*)(lbl_8029BBD0 + 0x18))
#define DAT_8029bbec (*(s32*)(lbl_8029BBD0 + 0x1C))
#define DAT_8029bbf0 (*(s32*)(lbl_8029BBD0 + 0x20))
#define DAT_8029bbf4 (*(s32*)(lbl_8029BBD0 + 0x24))
#define DAT_8029bbf8 (*(s32*)(lbl_8029BBD0 + 0x28))
#define DAT_8029bbfc (*(s32*)(lbl_8029BBD0 + 0x2C))
#define DAT_8029bc20 (*(u32*)(lbl_8029BBD0 + 0x50))
#define DAT_8029c2e4 lbl_8029C2E4
#define DAT_8029c330 (*(s32*)((u8*)&Action + 0x20))
#define DAT_8029c344 ((u8*)Action.currentStage)
#define DAT_802d5e80 lbl_802D5E80
#define DAT_80303d44 lbl_80303D44[0]
#define DAT_80303dc8 (*(s32*)lbl_80303DC8)
#define DAT_803e774c lbl_803E774C

s32 GetTheLastLeader()
{
	if (Action.mode != 12 && lbl_8042C180->field1E == 0)
		return -1;
	return Action.lastLeader;
}

s32 SetPauseDisable()
{
	Action.pauseDisabled = 0;
	return 0;
}

s32 SetPauseEnable()
{
	Action.pauseDisabled = 1;
	return 1;
}

s32 CheckActionPause()
{
	return Action.mode == 6;
}

ACTIONMODE GetActionMode()
{
	return (ACTIONMODE)Action.mode;
}

void CheckActionSoftReset()
{
	if (CheckSoftReset(3) != 0)
		fn_800A74BC(0);
}

void RestoreStageConnect(ACTION* action)
{
	action->stageConnect[0] = action->stageConnect[action->stageCount];
	for (s32 i = 0; i < 64; ++i) {
		if (action->stageConnectOriginal[i] == 0)
			break;
		action->stageConnect[i + 1] = action->stageConnectOriginal[i];
	}
	action->stageCount = 0;
}

void SaveStageConnect(ACTION* action)
{
	memcpy(action->stageConnectOriginal, action->stageConnect, 0x100);
}

s32 ACTION::IsBonusStageConnect(s32 index)
{
	s32 stage = Action.stageConnect[index];
	if (stage >= 29 && stage <= 35)
		return 1;
	return 0;
}

s32 ACTION::IsSpecialStageConnect(s32 index)
{
	s32 stage = Action.stageConnect[index];
	if (stage >= 52 && stage <= 61)
		return 1;
	return 0;
}

s32 ACTION::IsSpecialStage()
{
	if (currentStage != 0) {
		s32 stage = Action.currentStage->stage;
		if (stage >= 80 && stage <= 89)
			return 1;
	}
	return 0;
}

s32 ACTION::IsBonusStage()
{
	if (currentStage != 0) {
		s32 stage = Action.currentStage->stage;
		if (stage >= 40 && stage <= 49)
			return 1;
	}
	return 0;
}

s32 ACTION::IsSpecialAndBonusStage()
{
	if (currentStage != 0) {
		s32 stage = Action.currentStage->stage;
		if (stage >= 40 && stage <= 49)
			return 1;
		if (stage >= 80 && stage <= 89)
			return 1;
	}
	return 0;
}

void ACTION::InsertStage(s32 stage)
{
	for (s32 i = 63; i > stageCount + 1; --i)
		stageConnect[i] = stageConnect[i - 1];
	stageConnect[stageCount + 1] = stage;
}

void ACTION::eventChecker()
{
	if (Action.mode == 8)
		return;

	if (Action.IsSpecialAndBonusStage() && lbl_8042C180->field1E == 0) {
		((EventManagerLate*)lbl_8042C170)->finish();
		Action.mode = 8;
		fn_800CB6EC();
	} else {
		((EventManagerLate*)lbl_8042C170)->finish();
		Action.mode                  = 8;
		*(s32*)((u8*)&Action + 0x14) = 3;
		fn_800CB6EC();
		fn_8001F4E8(lbl_8042C180, 38, 1);
	}
}

s32 ACTION::restartStage()
{
	fn_80016778(lbl_8029C2E4);
	processState = 5;
	fn_80016BBC(lbl_8029C2E4);
	fn_800215A8(&lbl_8042C1A4);
	fn_8004ED48(lbl_8042C1F8);
	fn_8005A298(lbl_8042C298, 0);
	fn_80066ED8(&lbl_8042C308, 2);

	processState = 2;
	fn_80016BBC(lbl_8029C2E4);
	fn_800215A8(&lbl_8042C1A4);
	fn_80016BBC(lbl_8029C2E4);
	fn_800215A8(&lbl_8042C1A4);

	if (currentStage->restart != 0)
		currentStage->restart();

	processState = 0;
	fn_8001F4E8(lbl_8042C180, 26, 1);
	fn_8001F4E8(lbl_8042C180, 27, 1);
	fn_8001F4E8(lbl_8042C180, 33, 0);
	fn_8001F4E8(lbl_8042C180, 34, 0);
	fn_8001F4E8(lbl_8042C180, 35, 0);
	fn_8001F4E8(lbl_8042C180, 38, 1);
	*(s32*)((u8*)lbl_8042C180 + 0x30) = 0;
	*(s32*)((u8*)lbl_8042C180 + 0x34) = 0;

	if (stageNumber == 23)
		fn_80066D68(lbl_8042C304, lbl_8042C304[0], lbl_8042C304[1], lbl_8042C304[2]);

	if (lbl_8042C180->field1E == 0 && lbl_8042C180->field18 == 0
	    && lbl_80303D44[*(s8*)(*(u8**)lbl_80303DC8 + 56)] < 0) {
		*(s32*)((u8*)this + 0x14) = 3;
		return 0;
	}

	challengeState = 0;
	return 1;
}

void ACTION::SetPlayMode(s32 playMode, s32 gameRule)
{
	switch (playMode) {
		case 0:
			fn_8001F4E8(lbl_8042C180, 30, 0);
			break;
		case 1:
			fn_8001F4E8(lbl_8042C180, 30, 1);
			break;
		case 2:
			fn_8001F4E8(lbl_8042C180, 30, 2);
			break;
	}

	switch (gameRule) {
		case 0:
			fn_8001F4E8(lbl_8042C180, 36, 0);
			break;
		case 1:
			fn_8001F4E8(lbl_8042C180, 36, 1);
			break;
		case 2:
			fn_8001F4E8(lbl_8042C180, 36, 2);
			break;
		case 3:
			fn_8001F4E8(lbl_8042C180, 36, 3);
			break;
		case 4:
			fn_8001F4E8(lbl_8042C180, 36, 4);
			break;
		case 5:
			fn_8001F4E8(lbl_8042C180, 36, 5);
			break;
		case 6:
			fn_8001F4E8(lbl_8042C180, 36, 6);
			break;
		case 7:
			fn_8001F4E8(lbl_8042C180, 36, 7);
			break;
		case 8:
			fn_8001F4E8(lbl_8042C180, 36, 8);
			break;
	}
}

void ACTION::SetTeam(s32 player, s32 team)
{
	if (team >= 4)
		return;
	if (player >= 4)
		return;
	teams[player] = team;
}

void ACTION::SetStageConnect(s32 stageCount, s32 stage)
{
	if (stageCount >= 64)
		return;
	if (stage >= 62)
		return;
	stageConnect[stageCount] = stage;
}

void ACTION::InitStageAndTeamInfo()
{
	for (s32 i = 0; i < 64; ++i)
		SetStageConnect(i, 0);
	for (s32 i = 0; i < 4; ++i)
		SetTeam(i, -1);
}

u8* GetBGColor()
{
	return (u8*)&lbl_8042AEB0;
}

void EnableDistantWorldAlpha()
{
	*(void (**)())lbl_80240D0C = (void (*)())ACTION::dispAlpha;
}

void DisableDistantWorldAlpha()
{
	*(unsigned int*)(lbl_80240D0C + 8) &= ~0x10;
}

s32 ACTION::GetCurrentStageNumber()
{
	if (currentStage != 0)
		return currentStage->stage;
	return -1;
}

void* ACTION::GetCurrentStageName()
{
	if (currentStage != 0)
		return *(void**)currentStage;
	return 0;
}

void ACTION::FreezeStage()
{
	mode       = 7;
	transition = 0;
	fn_800B4684(lbl_8042C388, 1);
	fn_800CB84C();
	fn_8001F600();
	fn_8001F4E8(lbl_8042C180, 26, 0);
	fn_8001F4E8(lbl_8042C180, 27, 0);
}

void ACTION::GiveUpStage()
{
	if (mode == 8)
		return;

	if (IsSpecialAndBonusStage() && lbl_8042C180->field1E == 0) {
		((EventManagerLate*)lbl_8042C170)->finish();
		mode = 8;
		fn_800CB6EC();
	} else {
		((EventManagerLate*)lbl_8042C170)->finish();
		mode       = 8;
		transition = 3;
		fn_800CB6EC();
		fn_8001F4E8(lbl_8042C180, 38, 1);
	}
}

void ACTION::InitRestartStage()
{
	((EventManagerLate*)lbl_8042C170)->finish();
	mode       = 8;
	transition = 2;
	fn_800CB6EC();
	fn_80066AFC(object, *(s8*)(*(u8**)lbl_80303DC8 + 56), -1);
}

void ACTION::BackToBeginningOfStage()
{
	((EventManagerLate*)lbl_8042C170)->method54();
	mode       = 8;
	transition = 4;
	fn_80066EA0(&lbl_8042C308);
	if (lbl_8042C6D0 == 0)
		fn_8011C6EC();
	if (lbl_8042C6D0 != 0)
		fn_8011C0C4(lbl_8042C6D0);
}

void ACTION::RestartStage()
{
	((EventManagerLate*)lbl_8042C170)->finish();
	mode       = 8;
	transition = 1;
	fn_800CB6EC();
	challengeState = 0;
}

void ACTION::ContinueStage()
{
	fn_8001F4E8(lbl_8042C180, 27, 1);
	fn_8001F4E8(lbl_8042C180, 26, 1);
	fn_8001F4E8(lbl_8042C180, 33, 0);
	Action.pauseDisabled = 1;
}

void ACTION::EndPose()
{
	fn_8001F4E8(lbl_8042C180, 27, 0);
	fn_8001F4E8(lbl_8042C180, 26, 0);
	fn_8001F4E8(lbl_8042C180, 33, 1);
	Action.pauseDisabled = 0;
}

void ACTION::StartPose()
{
	if (lbl_8042C180->field1E == 0) {
		s32 score;
		s32 team     = teams[0];
		score        = lbl_80303D44[0];
		s32* scores  = (s32*)((u8*)fn_80116D2C(lbl_803E774C) + 60);
		scores[team] = score;
	}
}

void ACTION::SetGoalAction(s32 teamNo)
{
	switch (mode) {
		case 5:
		case 7:
			break;
		default:
			return;
	}

	mode       = 12;
	goalActive = 1;
	goalState  = 0;

	TeamObject* team = ((TeamObject**)lbl_80303DC8)[teamNo];
	if (team != 0 && stageNumber != 26 && (unsigned int)(stageNumber - 27) > 1) {
		lastLeader = team->leaders[team->player];
		fn_8009C2D4(team);
	} else {
		lastLeader = -1;
		fn_800A0A4C(teamNo);
	}

	fn_8001F4E8(lbl_8042C180, 27, 0);
	fn_8001F4E8(lbl_8042C180, 26, 0);
	fn_8001F4E8(lbl_8042C180, 33, 1);
	fn_8001F4E8(lbl_8042C180, 34, 1);
	Action.pauseDisabled = 0;
	fn_800CB6EC();

	*(s32*)(lbl_8029BBD0 + 24) = 0;
	*(s32*)(lbl_8029BBD0 + 28) = 0;
	*(s32*)(lbl_8029BBD0 + 32) = 0;
	*(s32*)(lbl_8029BBD0 + 36) = 0;
	*(s32*)(lbl_8029BBD0 + 40) = 0;
	*(s32*)(lbl_8029BBD0 + 44) = 0;

	if (lbl_8042C180->field1E == 0) {
		s32 score         = lbl_80303D44[0];
		s32 teamIndex     = teams[0];
		s32* scores       = (s32*)((u8*)fn_80116D2C(lbl_803E774C) + 60);
		scores[teamIndex] = score;
	}
}

void ACTION::StepStage()
{
	((EventManagerLate*)lbl_8042C170)->finish();
	mode = 8;
	fn_800CB6EC();
}

static inline u32 GetMilliseconds()
{
	return OSGetTick() / ((*(u32*)0x800000F8 >> 2) / 1000);
}

void ACTION::ExitPauseMode()
{
	s32 frames;
	if (lbl_8042C180->field1E != 0 && *(s8*)((u8*)lbl_8042C180 + 36) == 0) {
		if (lbl_8042C160 + lbl_8042C164 < 16)
			frames = 1;
		else
			frames = 2;
		lbl_8042C15C = GetMilliseconds();
	} else {
		frames = 1;
	}

	fn_801AD5E0(1);
	do {
		for (s32 i = lbl_8042C21C; i <= lbl_8042C224; ++i)
			fn_8004E6F0(lbl_8042C1F8, i);

		fn_800422C4(&lbl_8042C1C0);
		fn_80018368(lbl_8042C0F8);
		fn_80018368(lbl_8042C0FC);
		fn_80018368(lbl_8042C100);
		fn_80018368(lbl_8042C104);

		if (--frames <= 0)
			break;

		lbl_8042C15C = GetMilliseconds();
		ChkController();
		MakeGameKeyData();
		fn_8004A05C();
		SetAndGetDemoData();
		fn_8004AF4C(lbl_8042C1D0);
		if (currentStage->pause != 0)
			currentStage->pause();
	} while (1);

	u32 now      = GetMilliseconds();
	lbl_8042C164 = now - lbl_8042C15C;
	lbl_8042C15C = now;
}

static inline void* GetPauseInput(s32 player)
{
	return lbl_8029BBD0 + lbl_802408F8[player] * 76 + 72;
}

struct PauseControllerRecord {
	u8 padding[72];
	u32 buttons;
};

static inline ExecTable& GetExecTable()
{
	return *lbl_802895B8;
}

struct ActionExecCursor {
	ExecTable* entry;
};

static inline u32 GetPauseButtons(s32 player)
{
	return *(u32*)(lbl_8029BBD0 + 80 + lbl_802408F8[player] * 76);
}
void ACTION::EnterPauseMode()
{
	if ((playerCount == 1
	        && (repCheck(GetPauseInput(0), 4, 12, 1) || ConvertBit_AD(GetPauseInput(0), 4)))
	    || (playerCount == 2
	        && (repCheck(GetPauseInput(1), 4, 12, 1) || ConvertBit_AD(GetPauseInput(1), 4)))) {
		if (pauseChoice < 2) {
			++pauseChoice;
			if (lbl_8042C180->field1E == 0 && (lbl_80303D44[0] <= 0 || IsSpecialAndBonusStage())) {
				if (pauseChoice == 1)
					pauseChoice = 2;
			}
			if (lbl_8042C388 != 0)
				fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
		}
		return;
	}

	if ((playerCount == 1
	        && (repCheck(GetPauseInput(0), 8, 12, 1) || ConvertBit_AD(GetPauseInput(0), 8)))
	    || (playerCount == 2
	        && (repCheck(GetPauseInput(1), 8, 12, 1) || ConvertBit_AD(GetPauseInput(1), 8)))) {
		if (pauseChoice != 0) {
			--pauseChoice;
			if (lbl_8042C180->field1E == 0 && (lbl_80303D44[0] <= 0 || IsSpecialAndBonusStage())) {
				if (pauseChoice == 1)
					pauseChoice = 0;
			}
			if (lbl_8042C388 != 0)
				fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
		}
	}
}

void ACTION::CheckPauseOff()
{
	lbl_8042C15C = GetMilliseconds();
	if (lbl_8042C1F8 == 0)
		return;

	if (*(void**)((u8*)lbl_8042C1D0 + 29264) != 0) {
		fn_80194234(8, 1);
		if (*lbl_8042C9A4 != 0)
			fn_80177C50(lbl_8042C9A4);
		fn_8019CC00(*(void**)((u8*)lbl_8042C1F8 + 40));
		fn_8015B93C(*(void**)((u8*)lbl_8042C1D0 + 29264), *(void**)((u8*)lbl_8042C1F8 + 40));
	}

	if (*(s8*)((u8*)lbl_8042C180 + 9) != 0) {
		if (*(void**)((u8*)lbl_8042C1D0 + 29264) != 0) {
			fn_8004D568(lbl_8042C1F8);
			fn_8015B8E8(*(void**)((u8*)lbl_8042C1D0 + 29264), *(void**)((u8*)lbl_8042C1F8 + 40));
			fn_8019CC28(*(void**)((u8*)lbl_8042C1F8 + 40));
			fn_80194234(6, 1);
			fn_80194234(8, 0);
			if (pauseCallback != 0)
				pauseCallback();
		}
		fn_800CD6A0(lbl_803A6690);
		fn_800CDE58(lbl_803A6690, 35);
		if (*(void**)((u8*)lbl_8042C1D0 + 29264) != 0) {
			fn_80194234(8, 1);
			if (*lbl_8042C9A4 != 0)
				fn_80177C50(lbl_8042C9A4);
			fn_8019CC00(*(void**)((u8*)lbl_8042C1F8 + 40));
			fn_8015B93C(*(void**)((u8*)lbl_8042C1D0 + 29264), *(void**)((u8*)lbl_8042C1F8 + 40));
		}
		fn_800CDE58(lbl_803A6690, 28);
		fn_800CDE58(lbl_803A6690, 29);
		fn_800CDE58(lbl_803A6690, 30);
		fn_800CDE58(lbl_803A6690, 31);
		fn_800CDE58(lbl_803A6690, 33);
	}

	fn_8004DC80(lbl_8042C1F8, 1);
	if (*(s32*)((u8*)lbl_8042C180 + 48) > 2)
		RsCameraShowRaster(*(void**)((u8*)lbl_8042C1F8 + 40));
	fn_800B7BDC();
	fn_800BEEF0();
	fn_8019CF28(*(void**)((u8*)lbl_8042C1F8 + 40), &lbl_8042AEB0, 3);
	fn_8004DC80(lbl_8042C1F8, 1);
	fn_8015B8E8(*(void**)((u8*)lbl_8042C1D0 + 29264), *(void**)((u8*)lbl_8042C1F8 + 40));
	fn_8019EE04(*(void**)((u8*)fn_800A7658() + 4));
	fn_8019CC28(*(void**)((u8*)lbl_8042C1F8 + 40));
	((EventManagerLate*)lbl_8042C170)->method24();
	fn_8019CC00(*(void**)((u8*)lbl_8042C1F8 + 40));
	fn_8015B93C(*(void**)((u8*)lbl_8042C1D0 + 29264), *(void**)((u8*)lbl_8042C1F8 + 40));
	fn_8004AF04(lbl_8042C1D0);

	s32 objectIndex;
	objectIndex = lbl_8042C21C;
	for (; objectIndex <= lbl_8042C224; ++objectIndex) {
		fn_8004EBE0(lbl_8042C1F8, objectIndex);
		fn_8004E7EC(lbl_8042C1F8, objectIndex);
		fn_8001682C(lbl_8029C2E4);
		fn_8004ACF4(lbl_8042C1D0);

		for (u32 i = 0; i < 24; ++i) {
			ActionDispEntry& entry = ((ActionDispEntry*)lbl_80240D0C)[i];
			if (*(s8*)((u8*)lbl_8042C180 + 7) != 0)
				fn_8004A6F0(lbl_8042C1D0, 0, entry.index, 0);

			if (*(s32*)(*(u8**)((u8*)lbl_8042C1D0 + 29264 + entry.index * 4) + 36) > 0
			    || (s32)(entry.option.bits & 2) != 0) {
				if (*(s8*)((u8*)lbl_8042C180 + 32) != 0) {
					switch (entry.index) {
						case 2:
						case 8:
						case 21: {
							BitFlag option;
							BitFlag argument = entry.option;
							option           = argument;
							entry.callback(
							    *(void**)((u8*)lbl_8042C1D0 + 29264 + entry.index * 4), option);
						} break;
					}
				} else {
					BitFlag option;
					BitFlag argument = entry.option;
					option           = argument;
					entry.callback(*(void**)((u8*)lbl_8042C1D0 + 29264 + entry.index * 4), option);
				}
			}

			if (*(s8*)((u8*)lbl_8042C180 + 32) == 0) {
				BitFlag option;
				BitFlag argument(entry.option.bits & ~2U);
				option = argument;
				entry.callback(*(void**)((u8*)lbl_8042C1D0 + 29364 + entry.index * 260), option);
			}

			if (*(s8*)((u8*)lbl_8042C180 + 32) == 0) {
				for (s32 j = 1; j < 65; ++j) {
					if (fn_8004A5B8(lbl_8042C1D0, j, lbl_8042C1FC) != 0) {
						BitFlag option;
						BitFlag argument(entry.option.bits & ~2U);
						option = argument;
						entry.callback(
						    *(void**)((u8*)lbl_8042C1D0 + 29364 + entry.index * 260 + j * 4),
						    option);
					}
				}
			}
		}
	}

	fn_8004EBE0(lbl_8042C1F8, -1);
	fn_8019EE04(*(void**)((u8*)fn_800A7658() + 4));
	fn_8019CC28(*(void**)((u8*)lbl_8042C1F8 + 40));
	((EventManagerLate*)lbl_8042C170)->method28();
	fn_8019CC00(*(void**)((u8*)lbl_8042C1F8 + 40));
	fn_8011253C();

	if (*(void**)((u8*)lbl_8042C1D0 + 29264) != 0) {
		fn_8004D568(lbl_8042C1F8);
		fn_8015B8E8(*(void**)((u8*)lbl_8042C1D0 + 29264), *(void**)((u8*)lbl_8042C1F8 + 40));
		fn_8019CC28(*(void**)((u8*)lbl_8042C1F8 + 40));
		fn_80194234(6, 1);
		fn_80194234(8, 0);
		if (pauseCallback != 0)
			pauseCallback();
	}
	fn_800C4C18();
	lbl_8042C160 = GetMilliseconds() - lbl_8042C15C;
}

void ACTION::dispAlpha(void* world, BitFlag option)
{
	if (world == 0)
		return;

	s32 flags = *(s32*)((u8*)world + 8);
	fn_800B6E64();
	fn_8015B8E8(world, *(void**)((u8*)lbl_8042C1F8 + 40));

	if ((option.bits & 1) != 0) {
		*(s32*)((u8*)world + 8) = flags | 0x30;
		fn_80052DD4(lbl_802D5E80, world);
	} else {
		*(s32*)((u8*)world + 8) = flags & ~0x30;
		fn_80052DD4(lbl_802D5E80, 0);
	}

	if ((option.bits & 8) != 0)
		fn_8004DC80(lbl_8042C1F8, 1);
	else
		fn_8004DC80(lbl_8042C1F8, 0);

	void* result = fn_8019CC28(*(void**)((u8*)lbl_8042C1F8 + 40));
	if (result != 0) {
		if ((option.bits & 16) != 0)
			fn_8004D678(lbl_8042C1F8);
		else
			fn_8004D650(lbl_8042C1F8);

		fn_80194234(6, 1);
		fn_80194234(8, 0);
		fn_80194234(9, 6);
		if ((option.bits & 64) != 0) {
			fn_80194234(10, 5);
			fn_80194234(11, 2);
		} else {
			fn_80194234(10, 5);
			fn_80194234(11, 6);
		}
		fn_801AFFB0(7, 0, 0, 7, 0);
		fn_801AF914(1);
		if ((option.bits & 4) != 0)
			fn_80194234(20, 1);
		else
			fn_80194234(20, 2);
		if ((option.bits & 32) != 0)
			fn_800B8904(world);
		if ((option.bits & 2) != 0)
			fn_80016910(lbl_8029C2E4);
		fn_80159754(world);
		fn_8004D650(lbl_8042C1F8);
		fn_8019CC00(result);
	}

	fn_8015B93C(world, *(void**)((u8*)lbl_8042C1F8 + 40));
}

void ACTION::dispPunch(void* world, BitFlag option)
{
	if (world == 0)
		return;

	s32 flags = *(s32*)((u8*)world + 8);
	fn_800B6E64();
	fn_8015B8E8(world, *(void**)((u8*)lbl_8042C1F8 + 40));

	if ((option.bits & 1) != 0) {
		*(s32*)((u8*)world + 8) = flags | 0x30;
		fn_80052DD4(lbl_802D5E80, world);
	} else {
		*(s32*)((u8*)world + 8) = flags & ~0x30;
		fn_80052DD4(lbl_802D5E80, 0);
	}

	if ((option.bits & 8) != 0)
		fn_8004DC80(lbl_8042C1F8, 1);
	else
		fn_8004DC80(lbl_8042C1F8, 0);

	void* result = fn_8019CC28(*(void**)((u8*)lbl_8042C1F8 + 40));
	if (result != 0) {
		if ((option.bits & 16) != 0)
			fn_8004D678(lbl_8042C1F8);
		else
			fn_8004D650(lbl_8042C1F8);

		fn_80194234(8, 1);
		fn_80194234(6, 1);
		fn_80194234(9, 2);
		if ((option.bits & 64) != 0) {
			fn_80194234(10, 5);
			fn_80194234(11, 2);
		} else {
			fn_80194234(10, 5);
			fn_80194234(11, 6);
		}
		fn_801AFFB0(4, 200, 0, 7, lbl_803EDBD0[85]);
		fn_801AF914(0);
		if ((option.bits & 4) != 0)
			fn_80194234(20, 1);
		else
			fn_80194234(20, 2);
		if ((option.bits & 32) != 0)
			fn_800B8904(world);
		if ((option.bits & 2) != 0)
			fn_800169F4(lbl_8029C2E4);
		fn_80159754(world);
		fn_8004D650(lbl_8042C1F8);
		fn_8019CC00(result);
	}

	fn_8015B93C(world, *(void**)((u8*)lbl_8042C1F8 + 40));
}

void ACTION::dispOpeq(void* world, BitFlag option)
{
	if (world == 0)
		return;

	s32 flags = *(s32*)((u8*)world + 8);
	fn_800B6DC8();
	fn_8015B8E8(world, *(void**)((u8*)lbl_8042C1F8 + 40));

	if ((option.bits & 1) != 0) {
		*(s32*)((u8*)world + 8) = flags | 0x30;
		fn_80052DD4(lbl_802D5E80, world);
	} else {
		*(s32*)((u8*)world + 8) = flags & ~0x30;
		fn_80052DD4(lbl_802D5E80, 0);
	}

	if ((option.bits & 8) != 0)
		fn_8004DC80(lbl_8042C1F8, 1);
	else
		fn_8004DC80(lbl_8042C1F8, 0);

	void* result = fn_8019CC28(*(void**)((u8*)lbl_8042C1F8 + 40));
	if (result != 0) {
		if ((option.bits & 16) != 0)
			fn_8004D678(lbl_8042C1F8);
		else
			fn_8004D650(lbl_8042C1F8);

		fn_80194234(6, 1);
		fn_80194234(8, 1);
		fn_80194234(9, 2);
		if ((option.bits & 64) != 0) {
			fn_80194234(10, 5);
			fn_80194234(11, 2);
		} else {
			fn_80194234(10, 5);
			fn_80194234(11, 6);
		}
		if ((option.bits & 4) != 0)
			fn_80194234(20, 1);
		else
			fn_80194234(20, 2);
		if ((option.bits & 32) != 0)
			fn_800B8904(world);
		if ((option.bits & 2) != 0)
			fn_80016AD8(lbl_8029C2E4);
		fn_80159754(world);
		fn_8004D650(lbl_8042C1F8);
		fn_8019CC00(result);
	}

	fn_8015B93C(world, *(void**)((u8*)lbl_8042C1F8 + 40));
}

inline s32 ACTION::CheckPauseOn()
{
	if ((pauseDisabled == 1 && *(s32*)((u8*)lbl_8042C180 + 64) < 0
	        && ((GetPauseButtons(0) & 0x1000) != 0
	            || (lbl_8042C180->field1E != 0 && (GetPauseButtons(1) & 0x1000) != 0)))
	    || pauseMode == 1) {
		if ((GetPauseButtons(0) & 0x1000) != 0 || pauseMode == 1)
			return 1;
		return 2;
	}
	return 0;
}

s32 ACTION::Exec()
{
	void** execMethods;
	s8* resultCPtr;
	s8* resultBPtr;
	s32 pauseStatus;
	pauseStatus = 0;

	if (*(s8*)((u8*)lbl_8042C180 + 17) == 2) {
		++palFrame;
		s32 displayCount = lbl_8042C224 - lbl_8042C21C;
		if (palFrame >= 5)
			palFrame = 0;
		s8* frameTable = lbl_80240D00 + displayCount * 5;
		execFrames     = frameTable[palFrame];
		if (lbl_8042C180->field1E != 0) {
			if (execFrames > 1)
				fn_801AD5E0(2);
			else
				fn_801AD5E0(1);
		} else {
			fn_801AD5E0(1);
		}
	} else if (lbl_8042C180->field1E != 0) {
		execFrames = lbl_8042C224 - lbl_8042C21C + 1;
		if (execFrames > 1)
			fn_801AD5E0(2);
		else
			fn_801AD5E0(1);
	} else {
		execFrames = 1;
		fn_801AD5E0(1);
	}
	execFramesLeft = execFrames;

	s8 resultC;
	s8 resultB;
	s8 resultA;
	execMethods = lbl_803E7F88;
	resultCPtr  = &resultC;
	resultBPtr  = &resultB;

exec_frame:
	s32 i;
	for (i = lbl_8042C21C; i <= lbl_8042C224; ++i)
		fn_8004E6F0(lbl_8042C1F8, i);

	if (execPending != 0 && execStarted == 0) {
		if (execPhase == 2) {
			ActionExecCursor cursor = { &GetExecTable() };
			s32 value               = -1;
			execStarted             = 1;
			while (cursor.entry->value >= 0) {
				if (cursor.entry->stage == stageNumber && cursor.entry->team == teams[0]) {
					value = cursor.entry->value;
					break;
				}
				++cursor.entry;
			}
			if (value >= 0) {
				s32 object = ((s32 (*)(s32))execMethods[2])(value);
				if (object != 0 && cursor.entry->enabled != 0) {
					object = ((s32 (*)(s32))execMethods[4])(object);
					((void (*)(s32))execMethods[3])(object);
				}
			} else
				goto exec_start_done;
		}
		++execPhase;
	}
exec_start_done:

	fn_800422C4(&lbl_8042C1C0);
	fn_80016BBC(lbl_8029C2E4);
	if (*(s8*)((u8*)lbl_8042C180 + 31) != 0)
		++*(s32*)((u8*)lbl_8042C180 + 52);
	else
		++*(s32*)((u8*)lbl_8042C180 + 48);
	++*(s32*)((u8*)lbl_8042C180 + 44);

#pragma opt_propagation off
	if (mode == 5 && *(s32*)((u8*)lbl_8042C180 + 64) < 0 && *(s8*)((u8*)lbl_8042C180 + 32) == 0
	    && *(s8*)((u8*)lbl_8042C180 + 31) == 0 && *(s8*)((u8*)lbl_8042C180 + 33) == 0
	    && challengeState == 0) {
		if (execCallback != 0) {
			fn_80066474(&object, -1);
			fn_80066454(&resultA, resultBPtr, resultCPtr);
			if (resultA == 0 && resultB == 0 && resultC == 0)
				execCallback();
		} else {
			fn_80066474(&object, 1);
		}
	}
#pragma opt_propagation reset

	--execFramesLeft;
	fn_800215A8(&lbl_8042C1A4);
	if (execFramesLeft <= 0)
		goto final_pause_check;
	if (execFramesLeft != execFrames - 1)
		goto exec_frame;

	lbl_8042C15C = GetMilliseconds();
	ChkController();
	s32 returnedStatus = CheckPauseOn();
	if (returnedStatus != 0)
		pauseStatus = returnedStatus;
	MakeGameKeyData();
	fn_8004A05C();
	SetAndGetDemoData();
	fn_8004AF4C(lbl_8042C1D0);
	if (currentStage->pause != 0)
		currentStage->pause();
	goto exec_frame;

final_pause_check:
	if (pauseDisabled != 1)
		goto check_for_forced_pause;
	if (*(s32*)((u8*)lbl_8042C180 + 64) >= 0)
		goto check_for_forced_pause;
	u8* pauseButtonBase = lbl_8029BBD0 + 80;
	if ((*(u32*)(pauseButtonBase + lbl_802408F8[0] * 76) & 0x1000) != 0)
		goto pause_requested;
	if (lbl_8042C180->field1E != 0
	    && (*(u32*)(pauseButtonBase + lbl_802408F8[1] * 76) & 0x1000) != 0)
		goto pause_requested;

check_for_forced_pause:
	if (pauseMode != 1)
		goto no_pause_requested;

pause_requested:
	PauseControllerRecord* pauseInput
	    = &((PauseControllerRecord*)(lbl_8029BBD0 + 8))[lbl_802408F8[0]];
	if ((pauseInput->buttons & 0x1000) != 0 || pauseMode == 1)
		returnedStatus = 1;
	else
		returnedStatus = 2;
	goto pause_status_ready;

no_pause_requested:
	returnedStatus = 0;
pause_status_ready:
	if (returnedStatus != 0)
		pauseStatus = returnedStatus;
	u32 now      = GetMilliseconds();
	lbl_8042C164 = now - lbl_8042C15C;
	lbl_8042C15C = now;
	if (fn_8012DA08() == 0)
		pauseStatus = 0;
	return pauseStatus;
}

#pragma opt_propagation off
static inline void ResetLoopRawTasks(s32& outCount, s32 mode)
{
	s32 count = outCount;
	do {
		RawTask* task = lbl_80303DC8[count];
		if (task != 0)
			fn_8009C704((s32)task, mode);
		count++;
	} while (count < 4);
	outCount = count;
}

#pragma opt_propagation reset

#pragma opt_lifetimes off
s32 ACTION::Loop()
{
	s8 cVar1;
	s32 bVar2;
	u32 uVar3;
	s32 iVar4;
	s32 iVar5;
	RawCallback pcVar6;
	struct {
		s32 count;
		RawTask** entry;
	} iterator;
	u8* const param_1 = (u8*)this;

	MakeGameKeyData();
	fn_8004A05C();
	SetAndGetDemoData();
	switch (*(u32*)(param_1 + 0xc)) {
		case 1:
			stageCount  = 0;
			stageNumber = stageConnect[stageCount];
			subEnd();
			currentStage = (StageInfo*)stageTable[stageNumber];
			mode         = 2;
			break;
		case 0xb:
			fn_800C6F28();
			fn_800CD05C();
			fn_800421C8((u8*)&lbl_8042C1C0, (u32)stageSet);
			{
				DAT_8029c330   = (s32)(stageSet = (void*)(iterator.count = 0));
				iterator.entry = (RawTask**)lbl_80303DC8;
				do {
					RawTask* current = *iterator.entry;
					if (current != 0)
						current->end(1);
					iterator.entry++;
					iterator.count++;
				} while (iterator.count < 4);
			}
			fn_8004EF98();
			if (softReset != 0) {
				return 3;
			}
			if (*(s32*)(param_1 + 0x14) == 3) {
				return 2;
			}
			if (stageConnect[stageCount] > 0) {
				iVar5           = 0;
				u8* destination = param_1;
				do {
					*(s32*)(destination + 0x3c) = stageConnect[stageCount];
					destination += 4;
					iVar5++;
					stageCount++;
				} while (stageConnect[stageCount] > 0);
				stageConnect[iVar5] = 0;
				fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x31, 2);
			}
			return 1;
		case 2:
			subInit();
			if (IsSpecialAndBonusStage())
				mode = 3;
			else
				mode = 4;
			cVar1 = lbl_8042C180->field18;
			if (cVar1 == 3)
				break;
			if (cVar1 >= 3)
				goto checkUpperMode;
			if (cVar1 >= 1)
				goto setMode16;
			break;
		checkUpperMode:
			if (cVar1 >= 5)
				break;
		setMode16:
			mode = 16;
			break;
		case 3:
			uVar3 = fn_800A7648();
			fn_8019CF28((void*)uVar3, (u8*)&lbl_8042AEB0, 3);
			iVar4 = fn_800A7648();
			fn_8019EE04(*(void**)(iVar4 + 4));
			fn_800A7648();
			fn_8019CC28_noarg();
			fn_80194234(8, 0);
			fn_80194234(6, 0);
			fn_80194234(7, 2);
			fn_80194234(9, 2);
			fn_80194234(0xc, 1);
			fn_80194234(0x14, 1);
			iVar4 = fn_8012DAA0();
			if (iVar4 != 0) {
				lbl_8042C760->method0C();
				lbl_8042C760->method28();
			}
			fn_800A7648();
			fn_8019CC00_noarg();
			if (2 < *(s32*)(*(s32*)((u8*)&lbl_8042C180) + 0x30)) {
				fn_800A7648();
				fn_800122B4_noarg();
			}
			iVar4 = fn_8012DA84();
			if (iVar4 != 0) {
				*(u32*)(param_1 + 0xc) = 4;
			}
			break;
		case 10:
			fn_800B113C();
			fn_8005E8EC();
			{
				s32 count = 0;
				do {
					RawTask* task = lbl_80303DC8[count];
					if (task != 0)
						fn_8009C618(task);
					count++;
				} while (count < 4);
			}
			pcVar6 = *(RawCallback*)(*(s32*)(param_1 + 0x34) + 0x10);
			if (pcVar6 != (RawCallback)0x0) {
				(*pcVar6)();
			}
			fn_8005B558();
			fn_800B7B30();
			fn_80053B9C(&DAT_802d5e80);
			fn_800C59C4();
			if (*(void**)((u8*)lbl_8042C1D0 + 0x7250) != 0) {
				fn_80194234(8, 1);
				if (*lbl_8042C9A4 != 0) {
					fn_80177C50_noarg();
				}
				fn_8019CC00(*(u32*)(*(s32*)((u8*)&lbl_8042C1F8) + 0x28));
				fn_8015B93C(*(u32*)(*(s32*)((u8*)&lbl_8042C1D0) + 0x7250),
				    *(u32*)(*(s32*)((u8*)&lbl_8042C1F8) + 0x28));
			}
			fn_80016BBC(&DAT_8029c2e4);
			fn_8004B144(*(u32*)((u8*)&lbl_8042C1D0));
			fn_800BF5D8();
			fn_800B603C((u32)lbl_8042C388);
			fn_8001D540();
			fn_80110A4C();
			fn_800A7338();
			fn_800662BC();
			fn_801AD5E0(1);
			fn_80196D00();
			fn_80016BBC(&DAT_8029c2e4);
			if (*(s32*)(param_1 + 0x14) != 3) {
				if (*(char*)(*(s32*)((u8*)&lbl_8042C180) + 0x27) != '\0') {
					fn_801388C4(&lbl_8042C7E0, stageConnect[stageCount]);
				}
				if (*(char*)(*(s32*)((u8*)&lbl_8042C180) + 0x28) == '\x02') {
					iterator.count = lbl_80303D44[0];
					iVar4          = (s32)fn_80116D2C(&DAT_803e774c);
					fn_801169A4(iVar4 + 0x6f8, iterator.count, 1);
				}
				fn_80116B84(&DAT_803e774c);
				stageCount++;
				{
					s32 stage;
					if ((stageCount < 64) && ((stage = stageConnect[stageCount]) > 0)) {
						const char* name;
						s32 index = 0;
						do {
							if (stage == lbl_80240B10[index].stage) {
								name = lbl_80240B10[index].name;
								break;
							}
							index++;
						} while (1);
						iVar4 = fn_801C3C04((u32)stageSet, (void*)name);
						if ((iVar4 != 0)
						    || (iVar4 = fn_80138414(&lbl_8042C7E0, stageConnect[stageCount]),
						        iVar4 != 0))
							goto LAB_8001b690;
						stageNumber  = stageConnect[stageCount];
						currentStage = (StageInfo*)stageTable[stageNumber];
						nextMode     = 2;
					} else {
					LAB_8001b690:
						currentStage    = 0;
						stageConnect[0] = 0;
						nextMode        = 11;
					}
				}
				cVar1 = *(char*)(*(s32*)((u8*)&lbl_8042C180) + 0x1e);
				switch (cVar1) {
					case 1:
					case 2:
						mode = nextMode;
						goto case10Done;
				}
				if (*(char*)(*(s32*)((u8*)&lbl_8042C180) + 0x28) == '\x02') {
					mode = nextMode;
				} else {
					*(u32*)(param_1 + 0xc) = 0xd;
				}
			} else {
				if (IsSpecialAndBonusStage()) {
					iVar4 = *(s32*)((u8*)&lbl_8042C180);
					if (*(char*)(iVar4 + 0x27) != '\0')
						goto specialTransition;
					if (*(char*)(iVar4 + 0x28) != '\x02')
						goto regularTransition;
				specialTransition:
					if (*(char*)(iVar4 + 0x28) == '\x02') {
						iterator.count = lbl_80303D44[0];
						iVar4          = (s32)fn_80116D2C(&DAT_803e774c);
						fn_801169A4(iVar4 + 0x6f8, iterator.count, 0);
					}
					fn_80116B84(&DAT_803e774c);
					if (*(char*)(*(s32*)((u8*)&lbl_8042C180) + 0x27) != '\0') {
						fn_801388C4(&lbl_8042C7E0, stageConnect[stageCount]);
					}
					*(u32*)(param_1 + 0xc)  = 0xd;
					*(u32*)(param_1 + 0x10) = 0xb;
					goto transitionReady;
				}
			regularTransition:
				if (*(char*)(*(s32*)((u8*)&lbl_8042C180) + 0x28) == '\x02') {
					if (*(char*)(*(s32*)((u8*)&lbl_8042C180) + 0x28) != '\x02')
						goto regularTransitionCleanup;
					iterator.count = lbl_80303D44[0];
					iVar4          = (s32)fn_80116D2C(&DAT_803e774c);
					fn_801169A4(iVar4 + 0x6f8, iterator.count, 0);
				regularTransitionCleanup:
					fn_80116B84(&DAT_803e774c);
					*(u32*)(param_1 + 0xc)  = 0xd;
					*(u32*)(param_1 + 0x10) = 0xb;
				} else {
					*(u32*)(param_1 + 0xc)  = 0xb;
					*(u32*)(param_1 + 0x10) = 0xb;
				}
			transitionReady:
				*(u32*)(param_1 + 0x34) = 0;
			}
		case10Done:
			break;
		case 4:
			if (*(char*)(*(s32*)((u8*)&lbl_8042C180) + 0x18) == '\x02') {
				if (*(s32*)(*(s32*)((u8*)&lbl_8042C170) + 0x28) == 0) {
					DAT_8029bbe8            = 1;
					DAT_8029bbec            = 1;
					DAT_8029bbf0            = 1;
					DAT_8029bbf4            = 1;
					DAT_8029bbf8            = 1;
					DAT_8029bbfc            = 1;
					DAT_8029c330            = 1;
					*(u32*)(param_1 + 0xc)  = 5;
					*(u32*)(param_1 + 0x14) = 0;
				}
			} else if (*(s32*)(*(s32*)((u8*)&lbl_8042C170) + 0x28) == 0) {
				DAT_8029bbe8            = 1;
				DAT_8029bbec            = 1;
				DAT_8029bbf0            = 1;
				DAT_8029bbf4            = 1;
				DAT_8029bbf8            = 1;
				DAT_8029bbfc            = 1;
				DAT_8029c330            = 1;
				*(u32*)(param_1 + 0xc)  = 5;
				*(u32*)(param_1 + 0x14) = 0;
			}
			fn_8004AF4C(*(void**)((u8*)&lbl_8042C1D0));
			pcVar6 = *(RawCallback*)(*(s32*)(param_1 + 0x34) + 0xc);
			if (pcVar6 != (RawCallback)0x0) {
				(*pcVar6)();
			}
			Exec();
			CheckPauseOff();
			break;
		case 8:
			DAT_8029bbe8 = 0;
			DAT_8029bbec = 0;
			DAT_8029bbf0 = 0;
			DAT_8029bbf4 = 0;
			DAT_8029bbf8 = 0;
			DAT_8029bbfc = 0;
			if (*(s32*)(*(s32*)((u8*)&lbl_8042C170) + 0x28) == 0) {
				if ((*(s32*)(param_1 + 0x28c) == 0)
				    && (*(char*)(*(s32*)((u8*)&lbl_8042C180) + 0x18) == '\x02')) {
					*(u32*)(param_1 + 0x14) = 3;
				} else {
					*(u32*)(param_1 + 0x28c) = 0;
				}
				switch (transition) {
					case 1:
						fn_80016778(&DAT_8029c2e4);
						*(u32*)(param_1 + 0x18) = 4;
						fn_80016BBC(&DAT_8029c2e4);
						fn_800215A8((u8*)&lbl_8042C1A4);
						fn_8004ED48(*(u32*)((u8*)&lbl_8042C1F8));
						fn_8005A5EC(*(u32*)((u8*)&lbl_8042C298));
						fn_80066ED8((u8*)&lbl_8042C308, 3);
						*(u32*)(param_1 + 0x18) = 1;
						fn_80016BBC(&DAT_8029c2e4);
						fn_800215A8((u8*)&lbl_8042C1A4);
						fn_80016BBC(&DAT_8029c2e4);
						fn_800215A8((u8*)&lbl_8042C1A4);
						pcVar6 = *(RawCallback*)(*(s32*)(param_1 + 0x34) + 0x14);
						if (pcVar6 != (RawCallback)0x0) {
							(*pcVar6)();
						}
						*(u32*)(param_1 + 0x18) = 0;
						fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x1a, 1);
						fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x1b, 1);
						fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x21, 0);
						fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x22, 0);
						fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x23, 0);
						fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x26, 1);
						fn_80066E80((u8*)&lbl_8042C308);
						if ((*(char*)(*(s32*)((u8*)&lbl_8042C180) + 0x1e) == '\0')
						    && ((int)(&DAT_80303d44)[*(s8*)(*(u8**)lbl_80303DC8 + 0x38)] < 0)) {
							*(u32*)(param_1 + 0x14)                          = 3;
							*(u32*)((u8*)fn_80116D2C(&DAT_803e774c) + 0x6f8) = 0;
							*(u32*)((u8*)fn_80116D2C(&DAT_803e774c) + 0x6fc) = 0;
							bVar2                                            = 0;
						} else {
							bVar2 = 1;
						}
						if (bVar2) {
							{
								s32 count = 0;
								do {
									RawTask* task = lbl_80303DC8[count];
									if (task != 0)
										fn_8009C704((s32)task, 0);
									count++;
								} while (count < 4);
							}
							*(u32*)(param_1 + 0xc) = 4;
							lbl_8042C170->method50();
							fn_800CB95C();
							fn_800CC7E8();
						}

						break;
					case 2:
						iVar4 = restartStage();
						if (iVar4 != 0) {
							{
								s32 count = 0;
								do {
									RawTask* task = lbl_80303DC8[count];
									if (task != 0)
										fn_8009C704((s32)task, 1);
									count++;
								} while (count < 4);
							}
							*(u32*)(param_1 + 0xc) = 4;
							lbl_8042C170->method50();
							fn_800B48B8((u32)lbl_8042C388);
							fn_800CB95C();
							fn_800CC7E8();
							lbl_8042C170->method50();
						}

						break;
					case 4:
						fn_80016778(&DAT_8029c2e4);
						fn_8004ED48(*(u32*)((u8*)&lbl_8042C1F8));
						fn_8005A298(*(u32*)((u8*)&lbl_8042C298), 1);
						fn_80016BBC(&DAT_8029c2e4);
						*(u32*)(param_1 + 0x18) = 2;
						fn_800215A8((u8*)&lbl_8042C1A4);
						fn_80016BBC(&DAT_8029c2e4);
						fn_800215A8((u8*)&lbl_8042C1A4);
						pcVar6 = *(RawCallback*)(*(s32*)(param_1 + 0x34) + 0x14);
						if (pcVar6 != (RawCallback)0x0) {
							(*pcVar6)();
						}
						*(u32*)(param_1 + 0x18) = 0;
						fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x1a, 1);
						fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x1b, 1);
						fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x21, 0);
						fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x22, 0);
						fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x23, 0);
						iVar4 = 0;
						ResetLoopRawTasks(iVar4, 2);
						*(u32*)(param_1 + 0xc) = 4;
						lbl_8042C170->method58();

						break;
					default:
						*(u32*)(param_1 + 0x18) = 3;
						fn_80016778(&DAT_8029c2e4);
						*(u32*)(param_1 + 0xc) = 10;
						fn_8005952C(*(u32*)((u8*)&lbl_8042C298));
						fn_80016BBC(&DAT_8029c2e4);
						fn_800215A8((u8*)&lbl_8042C1A4);
						*(u32*)(param_1 + 0x18) = 3;

						break;
				}
			}
			fn_8004AF4C(*(void**)((u8*)&lbl_8042C1D0));
			pcVar6 = *(RawCallback*)(*(s32*)(param_1 + 0x34) + 0xc);
			if (pcVar6 != (RawCallback)0x0) {
				(*pcVar6)();
			}
			Exec();
			CheckPauseOff();
			break;
		case 5:
			*(u32*)(param_1 + 0x250) = 1;
			fn_8004AF4C(*(void**)((u8*)&lbl_8042C1D0));
			pcVar6 = *(RawCallback*)(*(s32*)(param_1 + 0x34) + 0xc);
			if (pcVar6 != (RawCallback)0x0) {
				(*pcVar6)();
			}
			iVar4 = Exec();
			CheckPauseOff();
			if (iVar4 != 0) {
				MainState* mainState;
				*(s32*)(param_1 + 0x24) = iVar4;
				mainState               = lbl_8042C180;
				cVar1                   = mainState->field18;
				if (cVar1 == '\x02') {
					if (*(s32*)(param_1 + 0xc) != 8) {
						if ((IsSpecialAndBonusStage()) && (mainState->field1E == 0)) {
							lbl_8042C170->method54();
							*(u32*)(param_1 + 0xc) = 8;
							fn_800CB6EC();
						} else {
							lbl_8042C170->method54();
							*(u32*)(param_1 + 0xc)  = 8;
							*(u32*)(param_1 + 0x14) = 3;
							fn_800CB6EC();
							fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x26, 1);
						}
					}
				} else {
					if (cVar1 == '\0') {
						fn_800166E8(&DAT_8029c2e4);
					}
					*(u32*)(param_1 + 0xc)  = 6;
					*(u32*)(param_1 + 0x1c) = 0;
					fn_800B4684((u32)lbl_8042C388, 1);
					*(u32*)((u8*)&lbl_8042C200) = 0;
					fn_800CB84C();
					fn_8001F600();
					*(u32*)(param_1 + 0x24c) = 0;
					if (lbl_8042C388 != 0) {
						fn_800B52E8((s32)lbl_8042C388, 0xe00a, 0, 0);
					}
				}
			}
			break;
		case 0xc:
			fn_8004AF4C(*(void**)((u8*)&lbl_8042C1D0));
			pcVar6 = *(RawCallback*)(*(s32*)(param_1 + 0x34) + 0xc);
			if (pcVar6 != (RawCallback)0x0) {
				(*pcVar6)();
			}
			Exec();
			iVar4 = *(s32*)(param_1 + 0x278);
			switch (iVar4) {
				case 1: {
					s32 stage;
					s32 timeout;

					*(s32*)(param_1 + 0x27c) = *(s32*)(param_1 + 0x27c) + 1;
					stage                    = *(s32*)(param_1 + 0x2c);
					if (stage == 0x1a)
						goto shortGoalDelay;
					if (stage == 0x1b)
						goto shortGoalDelay;
					if (stage != 0x1c)
						goto longGoalDelay;
				shortGoalDelay:
					timeout = 0x96;
					goto goalDelayReady;
				longGoalDelay:
					timeout = 300;
				goalDelayReady:
					if (*(s32*)(param_1 + 0x27c) <= timeout)
						goto goalDone;
					if ((stage != 0x18) || (*(s32*)((u8*)&lbl_8042C710) == 0)) {
						*(u32*)(param_1 + 0x278) = 2;
						*(u32*)(param_1 + 0x27c) = 0;
						if (*(char*)(*(s32*)((u8*)&lbl_8042C180) + 0x1e) == '\0') {
							if (*(s32*)(param_1 + 0x2c) != 0x17) {
								fn_8012C3E8();
								goto goalDone;
							}
							fn_80066D4C((u8*)&lbl_8042C304, (u8*)&lbl_8042C304,
							    (u8*)&lbl_8042C304 + 1, (u8*)&lbl_8042C304 + 2);
							lbl_8042C170->method54();
							*(u32*)(param_1 + 0xc) = 8;
							fn_800CB6EC();
						}
					}
				} break;
				case 2:
					break;
			}
		goalDone:
			CheckPauseOff();
			break;
		case 6:
			EnterPauseMode();
			CheckPauseOff();
			if (((*(s32*)(param_1 + 0x24) == 1)
			        && (((&DAT_8029bc20)[DAT_802408f8 * 0x13] & 0x1000) != 0))
			    || ((*(s32*)(param_1 + 0x24) == 2
			        && (((&DAT_8029bc20)[DAT_802408fc * 0x13] & 0x1000) != 0)))) {
				bVar2 = 1;
			} else {
				bVar2 = 0;
			}
			if (bVar2) {
				iVar4 = *(s32*)(param_1 + 0x24c);
				switch (iVar4) {
					case 0:
						fn_80016778(&DAT_8029c2e4);
						*(u32*)((u8*)&lbl_8042C200) = 1;
						*(u32*)(param_1 + 0xc)      = 5;
						fn_800B44A0((u32)lbl_8042C388);
						fn_800CB750();
						if (lbl_8042C388 != 0) {
							fn_800B52E8((s32)lbl_8042C388, 0xe00a, 0, 0);
						}
						break;
					case 1:
						lbl_8042C170->method54();
						*(u32*)(param_1 + 0xc)  = 8;
						*(u32*)(param_1 + 0x14) = 2;
						fn_800CB6EC();
						fn_80066AFC(*(u32*)(param_1 + 4), (int)*(s8*)(*(u8**)lbl_80303DC8 + 0x38),
						    0xffffffff);
						if (lbl_8042C388 != 0) {
							fn_800B52E8((s32)lbl_8042C388, 0xe008, 0, 0);
						}
						break;
					case 2:
						if (*(s32*)(param_1 + 0xc) != 8) {
							if ((IsSpecialAndBonusStage()) && (lbl_8042C180->field1E == 0)) {
								lbl_8042C170->method54();
								*(u32*)(param_1 + 0xc) = 8;
								fn_800CB6EC();
							} else {
								lbl_8042C170->method54();
								*(u32*)(param_1 + 0xc)  = 8;
								*(u32*)(param_1 + 0x14) = 3;
								fn_800CB6EC();
								fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x26, 1);
							}
						}
						if (lbl_8042C388 != 0) {
							fn_800B52E8((s32)lbl_8042C388, 0xe008, 0, 0);
						}
						break;
					default:
						break;
				}
				*(u32*)(param_1 + 0x24) = 0;
			}
			break;
		case 0x11:
			CheckPauseOff();
			break;
		case 7:
			ExitPauseMode();
			CheckPauseOff();
			break;
		case 0xd:
			fn_801306BC();
			*(u32*)(param_1 + 0xc) = 0xe;
			break;
		case 0xe:
			iVar4 = fn_80130484();
			if (iVar4 == 0) {
				*(u32*)(param_1 + 0xc) = 0xf;
			}
			break;
		case 0xf:
			fn_8013057C();
			*(u32*)(param_1 + 0xc) = *(u32*)(param_1 + 0x10);
			break;
		case 0x10:
			if (*(s32*)(param_1 + 0x288) != 0) {
				fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x17, 0);
				fn_8004AF4C(*(void**)((u8*)&lbl_8042C1D0));
				pcVar6 = *(RawCallback*)(*(s32*)(param_1 + 0x34) + 0xc);
				if (pcVar6 != (RawCallback)0x0) {
					(*pcVar6)();
				}
				Exec();
				CheckPauseOff();
				fn_8001F4E8(*(u32*)((u8*)&lbl_8042C180), 0x17, 1);
				*(s32*)(param_1 + 0x288) = *(s32*)(param_1 + 0x288) + -1;
			} else {
				if (*(s32*)(param_1 + 0x288) != 0)
					break;
				lbl_8042C170->method54();
				*(u32*)(param_1 + 0xc)  = 8;
				*(u32*)(param_1 + 0x14) = 2;
				fn_800CB6EC();
				fn_80066AFC(
				    *(u32*)(param_1 + 4), (int)*(char*)(*(s32*)lbl_80303DC8 + 0x38), 0xffffffff);
			}
			break;
	}
	*(u32*)(param_1 + 0x250) = 0;
	if ((*(s32*)(param_1 + 0x254) != 0) || (iVar4 = CheckSoftReset(3), iVar4 == 0))
		goto LAB_8001c460;
	iVar4 = *(s32*)(param_1 + 0xc);
	switch (iVar4) {
		case 5:
		case 6:
		case 0xc:
		case 0xe:
			fn_800A74BC(0);
	}
LAB_8001c460:
	fn_8001D718();
	return 0;
}
#pragma opt_lifetimes reset

#pragma opt_propagation off
static inline s32 ReadSavedTeamRank(s32* ranks, s32 team)
{
	return ranks[team];
}

static inline void WriteSavedTeamRank(s32* ranks, s32 team, s32 value)
{
	ranks[team] = value;
}

static inline const char* FindStageName(s32 stage)
{
	s32 index             = 0;
	StageNameEntry* entry = lbl_80240B10;
	do {
		if (stage == entry->stage)
			return lbl_80240B10[index].name;
		entry++;
		index++;
	} while (1);
}

#pragma opt_propagation reset

#pragma opt_common_subs off
#pragma opt_propagation off
static inline void InitRawTaskLoopNoCSE(s32& count, RawTask**& base, RawTask**& entry)
{
	count = 0;
	base  = (RawTask**)lbl_80303DC8;
	entry = base;
}

static inline void InitFirstStageTasks(s32& outCount, RawTask**& outBase, RawTask**& outEntry)
{
	RawTask** base;
	RawTask** entry;
	outCount = 0;
	base     = (RawTask**)lbl_80303DC8;
	entry    = base;
	do {
		RawTask* task = *entry;
		if (task != 0)
			fn_8009250C(task);
		entry++;
		outCount++;
	} while (outCount < 4);
	outBase  = base;
	outEntry = entry;
}

static inline void InitSecondStageTasks(RawTask**& outEntry, RawTask**& outBase, s32& outCount)
{
	s32 count = 0;
	RawTask** entry;
	RawTask** base = (RawTask**)lbl_80303DC8;
	entry          = base;
	do {
		RawTask* task = *entry;
		if (task != 0)
			fn_8009D2E0(task);
		entry++;
		count++;
	} while (count < 4);
	outCount = count;
	outBase  = base;
	outEntry = entry;
}

#pragma opt_propagation reset
#pragma opt_common_subs reset

void ACTION::subEnd()
{
	switch (stageNumber) {
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
		case 58:
		case 59:
		case 60:
		case 61: {
			fn_8001F4E8(lbl_8042C180, 36, 0);
			EventManager* fade        = lbl_8042C170;
			*(u32*)((u8*)fade + 0x2C) = 0xFFFFFFFF;
			*(u32*)((u8*)fade + 0x30) = 0xFFFFFFFF;
			RwRGBA color              = *(RwRGBA*)&lbl_8042CFD8;
			fn_8001D56C(&color);
			break;
		}
		case 17:
		case 20:
		case 40:
		case 41:
		case 42:
			fn_8001F4E8(lbl_8042C180, 36, 6);
			{
				EventManager* fade        = lbl_8042C170;
				*(u32*)((u8*)fade + 0x2C) = 0xFF000000;
				*(u32*)((u8*)fade + 0x30) = 0xFF000000;
			}
			fn_8001D540();
			break;
		case 43:
		case 44:
		case 45:
			fn_8001F4E8(lbl_8042C180, 36, 3);
			{
				EventManager* fade        = lbl_8042C170;
				*(u32*)((u8*)fade + 0x2C) = 0xFF000000;
				*(u32*)((u8*)fade + 0x30) = 0xFF000000;
			}
			fn_8001D540();
			break;
		case 46:
		case 47:
		case 48:
			fn_8001F4E8(lbl_8042C180, 36, 1);
			{
				EventManager* fade        = lbl_8042C170;
				*(u32*)((u8*)fade + 0x2C) = 0xFF000000;
				*(u32*)((u8*)fade + 0x30) = 0xFF000000;
			}
			fn_8001D540();
			break;
		case 16:
		case 18:
		case 19:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 36:
		case 37:
		case 38:
		case 39:
		case 49:
		case 50:
		case 51:
		default:
			fn_8001F4E8(lbl_8042C180, 36, 0);
			{
				EventManager* fade        = lbl_8042C170;
				*(u32*)((u8*)fade + 0x2C) = 0xFF000000;
				*(u32*)((u8*)fade + 0x30) = 0xFF000000;
			}
			fn_8001D540();
			break;
	}

	fn_8001F4E8(lbl_8042C180, 37, 0);
	if (stageNumber == 23) {
		lbl_8042C304[0]            = 0;
		lbl_8042C304[1]            = 0;
		lbl_8042C304[2]            = 0;
		*(s32*)((u8*)this + 0x23C) = 2;
	} else if (stageNumber == 24) {
		*(s32*)((u8*)this + 0x23C) = 0;
	}

	fn_801126B4(lbl_803E73B0);
	*(s32*)(lbl_8029BBD0 + 0x18) = 0;
	*(s32*)(lbl_8029BBD0 + 0x1C) = 0;
	*(s32*)(lbl_8029BBD0 + 0x20) = 0;
	*(s32*)(lbl_8029BBD0 + 0x24) = 0;
	*(s32*)(lbl_8029BBD0 + 0x28) = 0;
	*(s32*)(lbl_8029BBD0 + 0x2C) = 0;
	*(s32*)((u8*)&Action + 0x20) = 0;
	fn_8012D97C();
	fn_800CD138();
	fn_8002171C(&lbl_8042C1A4);

	const char* stageName        = FindStageName(stageConnect[0]);
	*(void**)((u8*)this + 0x284) = (void*)stageName;
	fn_80042310(&lbl_8042C1C0, *(void**)((u8*)this + 0x284));

	s32 player;
	s32 activeTeams;
	activeTeams = 0;
	player      = 0;
	do {
		if (*(s32*)((u8*)this + 0x23C + player * 4) != -1) {
			if (lbl_80303DC8[player] == 0) {
				if (lbl_8042C180->field1E == 0) {
					void* task = fn_80018A34(lbl_8042C148, 0x280);
					if (task != 0)
						fn_8009DFE0(task, 1, player, *(s32*)((u8*)this + 0x23C + player * 4),
						    player, 0, lbl_8042C108);
				} else {
					u32 buttons = *(u32*)(lbl_8029BBD0 + lbl_802408F8[player] * 0x4C + 0x48);
					if ((buttons & 0x100) != 0 && (buttons & 0x800) != 0) {
						void* task = fn_80018A34(lbl_8042C148, 0x280);
						if (task != 0)
							fn_8009DFE0(task, 1, player, *(s32*)((u8*)this + 0x23C + player * 4),
							    player, 1, lbl_8042C108);
					} else {
						void* task = fn_80018A34(lbl_8042C148, 0x280);
						if (task != 0)
							fn_8009DFE0(task, 1, player, *(s32*)((u8*)this + 0x23C + player * 4),
							    player, 0, lbl_8042C108);
					}
				}
			}
			activeTeams++;
			if (player == 0) {
				s32 team = *(s32*)((u8*)this + 0x23C + player * 4);
				if (*(s8*)((u8*)lbl_8042C180 + 0x28) == 2) {
					u8* save = (u8*)fn_80116D2C(lbl_803E774C);
					if (*(s32*)(save + 0x6FC) <= 0)
						*(s32*)((u8*)fn_80116D2C(lbl_803E774C) + 0x6FC) = 3;
					save = (u8*)fn_80116D2C(lbl_803E774C);
					fn_80066B48(object, 0, *(s32*)(save + 0x6FC));
				} else {
					s32* ranks = (s32*)((u8*)fn_80116D2C(lbl_803E774C) + 0x3C);
					if (ReadSavedTeamRank(ranks, team) <= 3) {
						ranks = (s32*)((u8*)fn_80116D2C(lbl_803E774C) + 0x3C);
						WriteSavedTeamRank(ranks, team, 3);
					}
					ranks = (s32*)((u8*)fn_80116D2C(lbl_803E774C) + 0x3C);
					fn_80066B48(object, 0, ReadSavedTeamRank(ranks, team));
				}
				*(s8*)((u8*)fn_80116D2C(lbl_803E774C) + 0x24) = (s8)team;
			}
		}
		player++;
	} while (player < 4);

	if (*(s8*)((u8*)lbl_8042C180 + 0x24) == 6)
		activeTeams = 1;
	if (activeTeams == 2)
		fn_8001F4E8(lbl_8042C180, 41, 0);
	fn_8004F0F8(activeTeams);
	fn_80066ED8(&lbl_8042C308, 2);
	*(s32*)((u8*)lbl_8042C180 + 0x30) = 0;
	*(s32*)((u8*)lbl_8042C180 + 0x34) = 0;
	if (*(s8*)((u8*)lbl_8042C180 + 0x27) != 0)
		*(void**)((u8*)this + 0x258) = ((void* (*)())lbl_803E7F88[0])();
	fn_80112618(lbl_803E73B0);
	fn_800C731C();
	*(s32*)((u8*)this + 0x274) = 0;
}

void ACTION::End()
{
	EndDemoData();
	if (*(s32*)((u8*)this + 0x258) != 0) {
		((RawCallback)lbl_803E7F88[1])();
		*(s32*)((u8*)this + 0x258) = 0;
	}
	fn_800B9180();
	fn_8005EC14();
	fn_800A73B4();
	fn_8001DF6C();
	mode = 1;
	fn_80016514(lbl_8029C2E4);
	fn_800CE010();
	fn_801125D8(lbl_803E73B0);
	fn_8020577C();
	fn_8016F084();
	fn_800A76E4(this);
	fn_80196D00();
	processState = 0;
	fn_8001F4E8(lbl_8042C180, 31, 0);
	fn_8001F4E8(lbl_8042C180, 32, 0);
}

void ACTION::Init()
{
	fn_800A7820();
	fn_800A7658();
	fn_8016EF70();
	fn_80205624();
	fn_8016EE28(lbl_8042CFDC);
	fn_8016EE58(lbl_8042CFE0);
	void* state = RsPathnameCreate(&lbl_8042AE98);
	fn_8016E054();
	RsPathnameDestroy(state);
	fn_8011264C(lbl_803E73B0);
	fn_800CE0CC();
	softReset                  = 0;
	*(s32*)((u8*)this + 0x250) = 0;
	*(s32*)((u8*)this + 0x26C) = 0;
	fn_801125D4(lbl_803E73B0);
	fn_801126B4(lbl_803E73B0);
	mode        = 1;
	pauseMode   = 0;
	playerCount = 0;
	fn_8001E000();
	fn_800A7428();
	fn_8005ED88();
	fn_800B9408();
	fn_80066ED8(&lbl_8042C308, 2);
	fn_80112618(lbl_803E73B0);
}

void __sinit_action_cpp()
{
	u8* action               = (u8*)&Action;
	*(void**)(action + 4)    = action + 0x294;
	*(void**)(action + 8)    = action + 0x295;
	*(void* volatile*)action = __vt__8SEQUENCE;
	*(void* volatile*)action = lbl_80240E2C;
	memcpy(lbl_8029C5A8, lbl_80240D0C, 0x120);
	*(s32*)((u8*)&Action + 0x284) = 0;
}

void FADESCREEN::SetBackgroundColorDefault()
{
	lbl_8042AEB0 = lbl_8042AEAC;
}

void FADESCREEN::SetBackgroundColor(RwRGBA* color)
{
	lbl_8042AEB0 = *color;
}

void FADESCREEN::BlackOut()
{
	method44();
	foregroundColor = 0xFF000000;
}

void FADESCREEN::FadeOut()
{
	mode            = 3;
	foregroundColor = (foregroundColor & 0x00FFFFFF) | 0xFF000000;
}

void FADESCREEN::FlashOut()
{
	method44();
	foregroundColor = 0xFFFFFFFF;
}

void FADESCREEN::Disp_Uso() { }

void FADESCREEN::FlashIn()
{
	method40();
	backgroundColor = 0xFFFFFFFF;
}

void FADESCREEN::FadeIn()
{
	mode            = 2;
	foregroundColor = foregroundColor & 0x00FFFFFF;
}

void FADESCREEN::BlackIn()
{
	method40();
	backgroundColor = 0xFF000000;
}

void FADESCREEN::WhiteIn()
{
	method40();
	backgroundColor = 0xFFFFFFFF;
}

void syncInitSync()
{
	lbl_8042C168 = lbl_8042AEA0;
}

void syncWaitVSync()
{
	fn_800CDE58(lbl_803A6690, 32);
	VIWaitForRetrace();
	ChkController();
	lbl_8042C168 = lbl_8042AEA0;
}

void ACTION::Entry2DFunc(RawCallback callback)
{
	*(RawCallback*)(lbl_8029C728 + 0x10) = callback;
}
extern "C" void fn_801C28D0(u32);
extern "C" void fn_800C5BDC();
extern "C" void fn_800CCEB0();
extern "C" void fn_80066320();
extern "C" void fn_800A7374();
extern "C" void fn_80110B04();
extern "C" void fn_800B60C0(void*);
extern "C" void fn_8004ECBC(void*, u32, s32);
extern "C" void fn_800BF794();
extern "C" s32 fn_8004B308(void*, u32);
extern "C" s32 fn_8004B9D4(void*, u32);
extern "C" void RsErrorMessage(void*);
extern "C" void fn_80053D58(void*);
extern "C" void fn_8005B5B8(void*, u32);
extern "C" void fn_8009250C(RawTask*);
extern "C" void fn_8009D2E0(RawTask*);
extern "C" void InitDemoData(s32, s32);
extern "C" s32 LoadDemoData(u32);
extern "C" s32 GetStartFlame();
extern "C" void fn_8001AB48(ACTION*);
extern "C" void fn_801125D0(void*);
// existing lbl_8042C1D0
extern u8 lbl_80240EAC[];
// existing lbl_8042C148
extern void* lbl_8042C108;
extern RawCallback lbl_8042C274;

#pragma opt_propagation off
static inline void RunLoadedDemoFrames(ACTION* action)
{
	s32 saved;
	s32 flame;
	s32 frame;
	if (*(s8*)((u8*)lbl_8042C180 + 0x18) != 0) {
		saved = *(s8*)((u8*)lbl_8042C180 + 0x17);
		fn_8001F4E8(lbl_8042C180, 23, 0);
		if (*(s8*)((u8*)lbl_8042C180 + 0x18) == 1 || *(s8*)((u8*)lbl_8042C180 + 0x18) == 2) {
			for (flame = 0; flame < GetStartFlame(); ++flame) {
				SetAndGetDemoData();
				*(s32*)((u8*)action + 0x250) = 1;
				fn_8004AF4C(lbl_8042C1D0);
				if (action->currentStage->pause != 0)
					action->currentStage->pause();
				fn_8001AB48(action);
				for (frame = lbl_8042C21C; frame <= lbl_8042C224; ++frame) {
					fn_8004EBE0(lbl_8042C1F8, frame);
					fn_8004E6F0(lbl_8042C1F8, frame);
				}
			}
		}
		fn_8001F4E8(lbl_8042C180, 23, saved);
	}
}
#pragma opt_propagation reset

void ACTION::subInit()
{
	u32 stageObject;
	s32 i;
	u8* playerAction;
	RawTask** taskBase;
	s32 j;
	RawTask** taskEntry;
	s32 firstCount;

	if (stageNumber <= 1 || stageNumber >= 62)
		fn_800A74BC(0);
	fn_801126B4(lbl_803E73B0);
	fn_8012D97C();
	*(s32*)((u8*)this + 0x250) = 0;
	*(s32*)((u8*)this + 0x24)  = 0;
	*(s32*)((u8*)this + 0x18)  = 0;
	*(s32*)((u8*)this + 0x26C) = 0;
	*(s32*)((u8*)this + 0x25C) = 0;
	*(s32*)((u8*)this + 0x260) = 0;
	fn_8001F4E8(lbl_8042C180, 33, 0);
	fn_8001F4E8(lbl_8042C180, 34, 0);
	fn_8001F4E8(lbl_8042C180, 35, 0);
	fn_8001F4E8(lbl_8042C180, 38, 1);

	switch (stageNumber) {
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
		case 58:
		case 59:
		case 60:
		case 61: {
			fn_8001F4E8(lbl_8042C180, 36, 0);
			EventManager* fade        = lbl_8042C170;
			*(s32*)((u8*)fade + 0x2C) = -1;
			*(s32*)((u8*)fade + 0x30) = -1;
			RwRGBA color              = *(RwRGBA*)&lbl_8042CFD8;
			fn_8001D56C(&color);
			break;
		}
		case 17:
		case 20:
		case 40:
		case 41:
		case 42:
			fn_8001F4E8(lbl_8042C180, 36, 6);
			{
				EventManager* fade        = lbl_8042C170;
				*(s32*)((u8*)fade + 0x2C) = 0xFF000000;
				*(s32*)((u8*)fade + 0x30) = 0xFF000000;
			}
			fn_8001D540();
			break;
		case 43:
		case 44:
		case 45:
			fn_8001F4E8(lbl_8042C180, 36, 3);
			{
				EventManager* fade        = lbl_8042C170;
				*(s32*)((u8*)fade + 0x2C) = 0xFF000000;
				*(s32*)((u8*)fade + 0x30) = 0xFF000000;
			}
			fn_8001D540();
			break;
		case 46:
		case 47:
		case 48:
			fn_8001F4E8(lbl_8042C180, 36, 1);
			{
				EventManager* fade        = lbl_8042C170;
				*(s32*)((u8*)fade + 0x2C) = 0xFF000000;
				*(s32*)((u8*)fade + 0x30) = 0xFF000000;
			}
			fn_8001D540();
			break;
		case 16:
		case 18:
		case 19:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 36:
		case 37:
		case 38:
		case 39:
		case 49:
		case 50:
		case 51:
		default:
			fn_8001F4E8(lbl_8042C180, 36, 0);
			{
				EventManager* fade        = lbl_8042C170;
				*(s32*)((u8*)fade + 0x2C) = 0xFF000000;
				*(s32*)((u8*)fade + 0x30) = 0xFF000000;
			}
			fn_8001D540();
			break;
	}
	fn_8001F4E8(lbl_8042C180, 37, 0);

	s32 stage = stageNumber;
	switch (stage) {
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 36:
			if (*(s8*)((u8*)lbl_8042C180 + 0x1E) == 0) {
				switch (teams[0]) {
					case 0:
						if (*(s8*)((u8*)lbl_8042C180 + 0x28) == 1)
							fn_8001F4E8(lbl_8042C180, 37, 3);
						else
							fn_8001F4E8(lbl_8042C180, 37, 0);
						break;
					case 1:
						if (*(s8*)((u8*)lbl_8042C180 + 0x28) == 1)
							fn_8001F4E8(lbl_8042C180, 36, 5);
						else
							fn_8001F4E8(lbl_8042C180, 36, 0);
						fn_8001F4E8(lbl_8042C180, 37, 0);
						break;
					case 2:
						if (*(s8*)((u8*)lbl_8042C180 + 0x28) == 1)
							fn_8001F4E8(lbl_8042C180, 36, 3);
						else
							fn_8001F4E8(lbl_8042C180, 36, 0);
						fn_8001F4E8(lbl_8042C180, 37, 0);
						break;
					case 3:
						switch (stageNumber) {
							case 2:
							case 5:
							case 7:
							case 9:
							case 11:
							case 13:
							case 15:
								fn_8001F4E8(lbl_8042C180, 36, 8);
								fn_8001F4E8(lbl_8042C180, 37, 0);
								break;
							case 6:
								fn_8001F4E8(lbl_8042C180, 36, 3);
								fn_8001F4E8(lbl_8042C180, 37, 0);
								break;
							case 8:
							case 36:
								fn_8001F4E8(lbl_8042C180, 36, 0);
								if (*(s8*)((u8*)lbl_8042C180 + 0x28) == 1)
									fn_8001F4E8(lbl_8042C180, 37, 3);
								else
									fn_8001F4E8(lbl_8042C180, 37, 0);
								break;
							case 10:
								fn_8001F4E8(lbl_8042C180, 36, 0);
								if (*(s8*)((u8*)lbl_8042C180 + 0x28) == 1)
									fn_8001F4E8(lbl_8042C180, 37, 5);
								else
									fn_8001F4E8(lbl_8042C180, 37, 2);
								break;
							case 3:
							case 12:
								fn_8001F4E8(lbl_8042C180, 36, 8);
								if (*(s8*)((u8*)lbl_8042C180 + 0x28) == 1)
									fn_8001F4E8(lbl_8042C180, 37, 1);
								else
									fn_8001F4E8(lbl_8042C180, 37, 0);
								break;
							case 14:
								fn_8001F4E8(lbl_8042C180, 36, 0);
								if (*(s8*)((u8*)lbl_8042C180 + 0x28) == 1)
									fn_8001F4E8(lbl_8042C180, 37, 4);
								else
									fn_8001F4E8(lbl_8042C180, 37, 1);
								break;
							case 4:
								fn_8001F4E8(lbl_8042C180, 36, 4);
								if (*(s8*)((u8*)lbl_8042C180 + 0x28) == 1)
									fn_8001F4E8(lbl_8042C180, 37, 3);
								else
									fn_8001F4E8(lbl_8042C180, 37, 0);
								break;
							default:
								fn_8001F4E8(lbl_8042C180, 36, 0);
								fn_8001F4E8(lbl_8042C180, 37, 0);
								break;
						}
						break;
				}
			}
			break;
		default:
			break;
	}

	fn_80066ED8(&lbl_8042C308, 2);
	*(s32*)((u8*)lbl_8042C180 + 0x30) = 0;
	*(s32*)((u8*)lbl_8042C180 + 0x34) = 0;
	fn_801C28D0(0xDEAD0CAB);
	*(s32*)(lbl_8029BBD0 + 0x18) = 0;
	*(s32*)(lbl_8029BBD0 + 0x1C) = 0;
	*(s32*)(lbl_8029BBD0 + 0x20) = 0;
	*(s32*)(lbl_8029BBD0 + 0x24) = 0;
	*(s32*)(lbl_8029BBD0 + 0x28) = 0;
	*(s32*)(lbl_8029BBD0 + 0x2C) = 0;
	fn_8001F4E8(lbl_8042C180, 26, 1);
	fn_8001F4E8(lbl_8042C180, 27, 1);
	fn_800C5BDC();
	fn_800CCEB0();
	fn_80066320();
	fn_800A7374();
	fn_80110B04();
	fn_800B60C0(lbl_8042C388);

	stageObject = currentStage != 0 ? *(u32*)currentStage : 0;
	fn_8004ECBC(lbl_8042C1F8, stageObject, 0);
	fn_8004ED48(lbl_8042C1F8);
	memcpy(lbl_80240D0C, lbl_8029C5A8, 0x120);
	fn_800BF794();
	stageObject = currentStage != 0 ? *(u32*)currentStage : 0;
	if (fn_8004B308(lbl_8042C1D0, stageObject) == 0) {
		RsErrorMessage(lbl_80240EAC);
		for (;;) {
		}
	}

	if (*(void**)((u8*)lbl_8042C1D0 + 0x7250) != 0) {
		fn_8004D568(lbl_8042C1F8);
		fn_8015B8E8(*(void**)((u8*)lbl_8042C1D0 + 0x7250), *(void**)((u8*)lbl_8042C1F8 + 0x28));
		fn_8019CC28(*(void**)((u8*)lbl_8042C1F8 + 0x28));
		fn_80194234(6, 1);
		fn_80194234(8, 0);
		RawCallback movieCallback = *(RawCallback*)((u8*)&Action + 0x274);
		if (movieCallback != 0)
			movieCallback();
	}
	stageObject = currentStage != 0 ? *(u32*)currentStage : 0;
	if (fn_8004B9D4(lbl_8042C1D0, stageObject) == 0) {
		RsErrorMessage(lbl_80240EAC);
		for (;;) {
		}
	}
	fn_80053D58(lbl_802D5E80);
	stageObject = currentStage != 0 ? *(u32*)currentStage : 0;
	fn_8005B5B8(*(void**)((u8*)this + 0x38), stageObject);
	RawCallback callback = *(RawCallback*)((u8*)currentStage + 8);
	if (callback != 0)
		callback();

	InitFirstStageTasks(firstCount, taskBase, taskEntry);

	j            = 0;
	playerAction = (u8*)this;
	do {
		if (*(s32*)(playerAction + 0x23C) != -1 && *taskBase == 0) {
			if (*(s8*)((u8*)lbl_8042C180 + 0x1E) == 0) {
				void* task = fn_80018A34(lbl_8042C148, 0x280);
				if (task != 0)
					fn_8009DFE0(task, 1, j, *(s32*)(playerAction + 0x23C), j, 0, lbl_8042C108);
			} else {
				u32 buttons = *(u32*)(lbl_8029BBD0 + lbl_802408F8[j] * 0x4C + 0x48);
				if ((buttons & 0x100) != 0 && (buttons & 0x800) != 0) {
					void* task = fn_80018A34(lbl_8042C148, 0x280);
					if (task != 0)
						fn_8009DFE0(task, 1, j, *(s32*)(playerAction + 0x23C), j, 1, lbl_8042C108);
				} else {
					void* task = fn_80018A34(lbl_8042C148, 0x280);
					if (task != 0)
						fn_8009DFE0(task, 1, j, *(s32*)(playerAction + 0x23C), j, 0, lbl_8042C108);
				}
			}
		}
		playerAction += 4;
		taskBase++;
		j++;
	} while (j < 4);

	i = 0;
	do {
		RawTask* task = lbl_80303DC8[i];
		if (task != 0)
			fn_8009D2E0(task);
		i++;
	} while (i < 4);

	if (*(s8*)((u8*)lbl_8042C180 + 0x18) != 0)
		InitDemoData(1, 0xE10);
	s8 demo = *(s8*)((u8*)lbl_8042C180 + 0x18);
	if (demo == 3)
		goto subInitDemoDone;
	if (demo >= 3)
		goto subInitHighDemo;
	if (demo >= 1)
		goto subInitActiveDemo;
	goto subInitDemoDone;
subInitHighDemo:
	if (demo >= 5)
		goto subInitDemoDone;
	fn_8001F4E8(lbl_8042C180, 24, 1);
subInitActiveDemo:
	fn_8001F4E8(lbl_8042C180, 0, 0);
	stageObject = currentStage != 0 ? *(u32*)currentStage : 0;
	if (LoadDemoData(stageObject) != 0) {
		i = 0;
		do {
			RawTask* task = lbl_80303DC8[i];
			if (task != 0)
				fn_8009C704((s32)task, 0);
			i++;
		} while (i < 4);
		*(s32*)((u8*)this + 0x288) = 1;
		*(s32*)((u8*)this + 0x28C) = 1;
		RunLoadedDemoFrames(this);
	}
subInitDemoDone:
	switch (stageNumber) {
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
			lbl_8042C170->method48();
			break;
		default:
			lbl_8042C170->method50();
			break;
	}
	*(s32*)((u8*)this + 0x18)  = 0;
	*(s32*)((u8*)this + 0x290) = 0;
	fn_80112618(lbl_803E73B0);
	fn_801125D0(lbl_803E73B0);
}

__declspec(section ".ctors") void (*const actionCtorEntry)() = __sinit_action_cpp;
