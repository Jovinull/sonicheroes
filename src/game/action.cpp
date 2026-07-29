typedef signed char s8;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned int u32;

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
	~BitFlag() { }
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
};

struct ACTION {
	u8 pad00[4];
	void* object;
	u8 pad08[4];
	s32 mode;
	u8 pad10[4];
	s32 transition;
	s32 processState;
	s32 pauseMode;
	s32 pauseDisabled;
	s32 playerCount;
	s32 stageCount;
	s32 stageNumber;
	u8 pad30[4];
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
	u8 pad250[8];
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
	u8 pad284[0x0C];
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
extern u8 lbl_8042AEB0;
extern u8 lbl_80240D0C[];
extern u8 lbl_80303DC8[];
extern s32 lbl_80303D44[];
extern void* lbl_8042C388;
extern void* lbl_8042C6D0;
extern u8 lbl_803E774C[];
extern u8 lbl_8029BBD0[];
extern u32 lbl_8042C160;
extern u32 lbl_8042C164;
extern u32 lbl_8042C15C;
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
extern "C" s32 CheckSoftReset(s32 mode);
extern "C" void fn_800A74BC(s32 mode);
extern "C" void fn_800CB6EC();
extern "C" void fn_8001F4E8(MainState* state, s32 field, s32 value);
extern "C" void fn_80016778(void* task);
extern "C" void fn_80016BBC(void* task);
extern "C" void fn_800215A8(void* object);
extern "C" void fn_8004ED48(void* object);
extern "C" void fn_8005A298(void* object, s32 mode);
extern "C" void fn_80066ED8(void* object, s32 mode);
extern "C" void fn_80066D68(void* object, u8 red, u8 green, u8 blue);
extern "C" void fn_800B4684(void* object, s32 mode);
extern "C" void fn_800CB84C();
extern "C" void fn_8001F600();
extern "C" void fn_80066AFC(void* object, s32 stage, s32 value);
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
extern "C" void MakeGameKeyData();
extern "C" void fn_8004A05C();
extern "C" void SetAndGetDemoData();
extern "C" void fn_8004AF4C(void* object);
extern "C" s32 repCheck(void* input, s32 bit, s32 repeat, s32 mode);
extern "C" s32 ConvertBit_AD(void* input, s32 bit);
extern "C" void fn_800B52E8(void* object, s32 sound, s32 arg2, s32 arg3);
extern "C" void fn_80194234(s32 index, s32 mode);
extern "C" void fn_80177C50(void* object);
extern "C" void fn_8019CC00(void* world);
extern "C" void fn_8015B93C(void* object, void* world);
extern "C" void fn_8004D568(void* object);
extern "C" void fn_8015B8E8(void* object, void* world);
extern "C" void* fn_8019CC28(void* world);
extern "C" void fn_800CD6A0(void* object);
extern "C" void fn_800CDE58(void* object, s32 index);
extern "C" void fn_8004DC80(void* object, s32 mode);
extern "C" void fn_800122B4(void* world);
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
extern void* lbl_803E7F88[];
extern "C" void fn_80066474(void* object, s32 mode);
extern "C" void fn_80066454(s8* a, s8* b, s8* c);
extern "C" s32 fn_8012DA08();
extern "C" void* memcpy(void* destination, const void* source, unsigned long size);

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
		lbl_8042C170->finish();
		Action.mode = 8;
		fn_800CB6EC();
	} else {
		lbl_8042C170->finish();
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
	return &lbl_8042AEB0;
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
		lbl_8042C170->finish();
		mode = 8;
		fn_800CB6EC();
	} else {
		lbl_8042C170->finish();
		mode       = 8;
		transition = 3;
		fn_800CB6EC();
		fn_8001F4E8(lbl_8042C180, 38, 1);
	}
}

void ACTION::InitRestartStage()
{
	lbl_8042C170->finish();
	mode       = 8;
	transition = 2;
	fn_800CB6EC();
	fn_80066AFC(object, *(s8*)(*(u8**)lbl_80303DC8 + 56), -1);
}

void ACTION::BackToBeginningOfStage()
{
	lbl_8042C170->method54();
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
	lbl_8042C170->finish();
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
	lbl_8042C170->finish();
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
		fn_800122B4(*(void**)((u8*)lbl_8042C1F8 + 40));
	fn_800B7BDC();
	fn_800BEEF0();
	fn_8019CF28(*(void**)((u8*)lbl_8042C1F8 + 40), &lbl_8042AEB0, 3);
	fn_8004DC80(lbl_8042C1F8, 1);
	fn_8015B8E8(*(void**)((u8*)lbl_8042C1D0 + 29264), *(void**)((u8*)lbl_8042C1F8 + 40));
	fn_8019EE04(*(void**)((u8*)fn_800A7658() + 4));
	fn_8019CC28(*(void**)((u8*)lbl_8042C1F8 + 40));
	lbl_8042C170->method24();
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
	lbl_8042C170->method28();
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

#pragma opt_common_subs off
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
#pragma opt_common_subs reset

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
