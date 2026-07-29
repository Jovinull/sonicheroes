typedef signed char s8;
typedef signed int s32;
typedef unsigned char u8;

enum ACTIONMODE {
	ACTIONMODE_0 = 0,
};

struct MainState {
	u8 pad[0x18];
	s8 field18;
	u8 pad19[5];
	s8 field1E;
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
};

struct ACTION {
	u8 pad00[0x0C];
	s32 mode;
	u8 pad10[0x10];
	s32 pauseDisabled;
	u8 pad24[4];
	s32 stageCount;
	s32 stageNumber;
	u8 pad30[4];
	struct StageInfo {
		s32 field0;
		s32 stage;
		u8 pad08[0x0C];
		void (*restart)();
	}* currentStage;
	u8 pad38[4];
	s32 stageConnect[64];
	s32 stageConnectOriginal[64];
	u8 pad23C[0x44];
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
};

extern ACTION Action;
extern MainState* lbl_8042C180;
extern EventManager* lbl_8042C170;
extern u8 lbl_8029C2E4[];
extern u8 lbl_8042C1A4[];
extern void* lbl_8042C1F8;
extern void* lbl_8042C298;
extern u8 lbl_8042C308[];
extern u8 lbl_8042C304[3];
extern void* lbl_80303DC8;
extern s32 lbl_80303D44[];
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

#if 0
s32 ACTION::restartStage()
{
	fn_80016778(lbl_8029C2E4);
	pauseDisabled = 5;
	fn_80016BBC(lbl_8029C2E4);
	fn_800215A8(lbl_8042C1A4);
	fn_8004ED48(lbl_8042C1F8);
	fn_8005A298(lbl_8042C298, 0);
	fn_80066ED8(lbl_8042C308, 2);

	pauseDisabled = 2;
	fn_80016BBC(lbl_8029C2E4);
	fn_800215A8(lbl_8042C1A4);
	fn_80016BBC(lbl_8029C2E4);
	fn_800215A8(lbl_8042C1A4);

	if (currentStage->restart != 0)
		currentStage->restart();

	pauseDisabled = 0;
	fn_8001F4E8(lbl_8042C180, 26, 1);
	fn_8001F4E8(lbl_8042C180, 27, 1);
	fn_8001F4E8(lbl_8042C180, 33, 0);
	fn_8001F4E8(lbl_8042C180, 34, 0);
	fn_8001F4E8(lbl_8042C180, 35, 0);
	fn_8001F4E8(lbl_8042C180, 38, 1);
	*(s32*)((u8*)lbl_8042C180 + 0x30) = 0;
	*(s32*)((u8*)lbl_8042C180 + 0x34) = 0;

	if (stageNumber == 23)
		fn_80066D68(lbl_8042C308, lbl_8042C304[0], lbl_8042C304[1], lbl_8042C304[2]);

	if (lbl_8042C180->field1E != 0 && lbl_8042C180->field18 != 0
	    && lbl_80303D44[*(s8*)((u8*)lbl_80303DC8 + 56)] > 0) {
		*(s32*)((u8*)this + 0x14) = 3;
		return 0;
	}

	challengeState = 0;
	return 1;
}
#endif
