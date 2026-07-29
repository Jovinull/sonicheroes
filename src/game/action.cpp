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
	u8 pad1C[4];
	s32 pauseDisabled;
	u8 pad24[4];
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
	u8 pad24C[0x2C];
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
extern "C" void fn_8001A518();
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
	*(void (**)())lbl_80240D0C = (void (*)())fn_8001A518;
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
