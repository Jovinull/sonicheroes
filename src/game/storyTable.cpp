#include "game/storyTable.h"

// Complete C++ storyTable.cpp reconstruction. The metadata helpers expand in
// several retail callers under the single whole-unit deferred mode. Definitions
// use the compiler's deferred emission order; original source line order is unknown.
// Four GC-only operations retain raw address names rather than invented identities.
// See docs/story-table-unit-evidence.md for the owned inventory and compiler trials.
extern "C" {
extern void* lbl_8042C180;
extern u8 lbl_8029C310[];
extern u8 MoviePlaySub[];
extern u8 lbl_803E774C[];
extern u8 seqVars__13TQuestSeqCtrl[];
void SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(void*, s32, s32);
void fn_8001938C(void*);
void fn_8001934C(void*, s32, s32);
void fn_800191F8(void*, s32, s32);
void fn_8001936C(void*, s32, s32);
s32 CheckSequenceVars__13TQuestSeqCtrlFi(s32);
void SetSequenceVars__13TQuestSeqCtrlFi(s32);
void* fn_80116D2C(void*);
s32 fn_801380B8(STORYMANAGE*);
s32 EventNumber2MovieNumber__10MOVIE_PLAYFi(void*, s32);
s32 MovieNumber2EventNumber__10MOVIE_PLAYFi(void*);
void* memcpy(void*, const void*, unsigned long);
}

extern "C" void fn_80018EFC(void*, s32);
STORYMANAGE StoryManage;
static STORY_TABLE storyTable_Sonic[27] = {
	{ 0, static_cast<SEQ_TYPE>(1), 0 },
	{ 1, static_cast<SEQ_TYPE>(0), 2 },
	{ 2, static_cast<SEQ_TYPE>(0), 3 },
	{ 3, static_cast<SEQ_TYPE>(0), 16 },
	{ 4, static_cast<SEQ_TYPE>(0), 4 },
	{ 5, static_cast<SEQ_TYPE>(0), 5 },
	{ 6, static_cast<SEQ_TYPE>(1), 4 },
	{ 7, static_cast<SEQ_TYPE>(0), 17 },
	{ 8, static_cast<SEQ_TYPE>(0), 6 },
	{ 9, static_cast<SEQ_TYPE>(0), 7 },
	{ 10, static_cast<SEQ_TYPE>(0), 18 },
	{ 11, static_cast<SEQ_TYPE>(0), 8 },
	{ 12, static_cast<SEQ_TYPE>(0), 9 },
	{ 13, static_cast<SEQ_TYPE>(0), 19 },
	{ 14, static_cast<SEQ_TYPE>(1), 9 },
	{ 15, static_cast<SEQ_TYPE>(0), 10 },
	{ 16, static_cast<SEQ_TYPE>(0), 11 },
	{ 17, static_cast<SEQ_TYPE>(1), 12 },
	{ 18, static_cast<SEQ_TYPE>(0), 20 },
	{ 19, static_cast<SEQ_TYPE>(0), 12 },
	{ 20, static_cast<SEQ_TYPE>(0), 13 },
	{ 21, static_cast<SEQ_TYPE>(0), 21 },
	{ 22, static_cast<SEQ_TYPE>(0), 14 },
	{ 23, static_cast<SEQ_TYPE>(0), 15 },
	{ 24, static_cast<SEQ_TYPE>(0), 22 },
	{ 25, static_cast<SEQ_TYPE>(1), 17 },
	{ 26, static_cast<SEQ_TYPE>(2), 0 },
};
static STORY_TABLE storyTable_Dark[27] = {
	{ 27, static_cast<SEQ_TYPE>(1), 100 },
	{ 28, static_cast<SEQ_TYPE>(0), 2 },
	{ 29, static_cast<SEQ_TYPE>(0), 3 },
	{ 30, static_cast<SEQ_TYPE>(0), 16 },
	{ 31, static_cast<SEQ_TYPE>(0), 4 },
	{ 32, static_cast<SEQ_TYPE>(0), 5 },
	{ 33, static_cast<SEQ_TYPE>(1), 104 },
	{ 34, static_cast<SEQ_TYPE>(0), 17 },
	{ 35, static_cast<SEQ_TYPE>(0), 6 },
	{ 36, static_cast<SEQ_TYPE>(0), 7 },
	{ 37, static_cast<SEQ_TYPE>(0), 18 },
	{ 38, static_cast<SEQ_TYPE>(0), 8 },
	{ 39, static_cast<SEQ_TYPE>(0), 9 },
	{ 40, static_cast<SEQ_TYPE>(0), 19 },
	{ 41, static_cast<SEQ_TYPE>(1), 109 },
	{ 42, static_cast<SEQ_TYPE>(0), 10 },
	{ 43, static_cast<SEQ_TYPE>(0), 11 },
	{ 44, static_cast<SEQ_TYPE>(1), 12 },
	{ 45, static_cast<SEQ_TYPE>(0), 20 },
	{ 46, static_cast<SEQ_TYPE>(0), 12 },
	{ 47, static_cast<SEQ_TYPE>(0), 13 },
	{ 48, static_cast<SEQ_TYPE>(0), 21 },
	{ 49, static_cast<SEQ_TYPE>(0), 14 },
	{ 50, static_cast<SEQ_TYPE>(0), 15 },
	{ 51, static_cast<SEQ_TYPE>(0), 22 },
	{ 52, static_cast<SEQ_TYPE>(1), 117 },
	{ 53, static_cast<SEQ_TYPE>(2), 0 },
};
static STORY_TABLE storyTable_Roses[28] = {
	{ 54, static_cast<SEQ_TYPE>(1), 200 },
	{ 55, static_cast<SEQ_TYPE>(0), 25 },
	{ 56, static_cast<SEQ_TYPE>(0), 2 },
	{ 57, static_cast<SEQ_TYPE>(0), 3 },
	{ 58, static_cast<SEQ_TYPE>(0), 16 },
	{ 59, static_cast<SEQ_TYPE>(0), 4 },
	{ 60, static_cast<SEQ_TYPE>(0), 5 },
	{ 61, static_cast<SEQ_TYPE>(1), 4 },
	{ 62, static_cast<SEQ_TYPE>(0), 17 },
	{ 63, static_cast<SEQ_TYPE>(0), 6 },
	{ 64, static_cast<SEQ_TYPE>(0), 7 },
	{ 65, static_cast<SEQ_TYPE>(0), 18 },
	{ 66, static_cast<SEQ_TYPE>(0), 8 },
	{ 67, static_cast<SEQ_TYPE>(0), 9 },
	{ 68, static_cast<SEQ_TYPE>(0), 19 },
	{ 69, static_cast<SEQ_TYPE>(1), 209 },
	{ 70, static_cast<SEQ_TYPE>(0), 10 },
	{ 71, static_cast<SEQ_TYPE>(0), 11 },
	{ 72, static_cast<SEQ_TYPE>(1), 212 },
	{ 73, static_cast<SEQ_TYPE>(0), 20 },
	{ 74, static_cast<SEQ_TYPE>(0), 12 },
	{ 75, static_cast<SEQ_TYPE>(0), 13 },
	{ 76, static_cast<SEQ_TYPE>(0), 21 },
	{ 77, static_cast<SEQ_TYPE>(0), 14 },
	{ 78, static_cast<SEQ_TYPE>(0), 15 },
	{ 79, static_cast<SEQ_TYPE>(0), 22 },
	{ 80, static_cast<SEQ_TYPE>(1), 217 },
	{ 81, static_cast<SEQ_TYPE>(2), 0 },
};
static STORY_TABLE storyTable_Chaotix[27] = {
	{ 82, static_cast<SEQ_TYPE>(1), 300 },
	{ 83, static_cast<SEQ_TYPE>(0), 2 },
	{ 84, static_cast<SEQ_TYPE>(0), 3 },
	{ 85, static_cast<SEQ_TYPE>(0), 16 },
	{ 86, static_cast<SEQ_TYPE>(0), 4 },
	{ 87, static_cast<SEQ_TYPE>(0), 5 },
	{ 88, static_cast<SEQ_TYPE>(1), 104 },
	{ 89, static_cast<SEQ_TYPE>(0), 17 },
	{ 90, static_cast<SEQ_TYPE>(0), 6 },
	{ 91, static_cast<SEQ_TYPE>(0), 7 },
	{ 92, static_cast<SEQ_TYPE>(0), 18 },
	{ 93, static_cast<SEQ_TYPE>(0), 36 },
	{ 94, static_cast<SEQ_TYPE>(0), 9 },
	{ 95, static_cast<SEQ_TYPE>(0), 19 },
	{ 96, static_cast<SEQ_TYPE>(1), 309 },
	{ 97, static_cast<SEQ_TYPE>(0), 10 },
	{ 98, static_cast<SEQ_TYPE>(0), 11 },
	{ 99, static_cast<SEQ_TYPE>(1), 212 },
	{ 100, static_cast<SEQ_TYPE>(0), 20 },
	{ 101, static_cast<SEQ_TYPE>(0), 12 },
	{ 102, static_cast<SEQ_TYPE>(0), 13 },
	{ 103, static_cast<SEQ_TYPE>(0), 21 },
	{ 104, static_cast<SEQ_TYPE>(0), 14 },
	{ 105, static_cast<SEQ_TYPE>(0), 15 },
	{ 106, static_cast<SEQ_TYPE>(0), 22 },
	{ 107, static_cast<SEQ_TYPE>(1), 317 },
	{ 108, static_cast<SEQ_TYPE>(2), 0 },
};
static STORY_TABLE storyTable_Last[8] = {
	{ 109, static_cast<SEQ_TYPE>(1), 400 },
	{ 110, static_cast<SEQ_TYPE>(1), 401 },
	{ 111, static_cast<SEQ_TYPE>(1), 402 },
	{ 112, static_cast<SEQ_TYPE>(0), 23 },
	{ 113, static_cast<SEQ_TYPE>(1), 403 },
	{ 114, static_cast<SEQ_TYPE>(0), 24 },
	{ 115, static_cast<SEQ_TYPE>(1), 404 },
	{ 116, static_cast<SEQ_TYPE>(2), 0 },
};
static ACTIONSTAGE_NUMBER mustExitBeforePlay[3]
    = { ACTIONSTAGE_OCEAN_01, BOSSSTAGE_VSCHARA1ST_21, BOSSSTAGE_TEAMBATTLE2_24 };
struct BONUSSTAGE_TBL {
	ACTIONSTAGE_NUMBER baseStage, oppStage;
};
static BONUSSTAGE_TBL bonusStageTable[15]
    = { { static_cast<ACTIONSTAGE_NUMBER>(2), static_cast<ACTIONSTAGE_NUMBER>(29) },
	      { static_cast<ACTIONSTAGE_NUMBER>(3), static_cast<ACTIONSTAGE_NUMBER>(52) },
	      { static_cast<ACTIONSTAGE_NUMBER>(4), static_cast<ACTIONSTAGE_NUMBER>(30) },
	      { static_cast<ACTIONSTAGE_NUMBER>(5), static_cast<ACTIONSTAGE_NUMBER>(53) },
	      { static_cast<ACTIONSTAGE_NUMBER>(6), static_cast<ACTIONSTAGE_NUMBER>(31) },
	      { static_cast<ACTIONSTAGE_NUMBER>(7), static_cast<ACTIONSTAGE_NUMBER>(54) },
	      { static_cast<ACTIONSTAGE_NUMBER>(8), static_cast<ACTIONSTAGE_NUMBER>(32) },
	      { static_cast<ACTIONSTAGE_NUMBER>(9), static_cast<ACTIONSTAGE_NUMBER>(55) },
	      { static_cast<ACTIONSTAGE_NUMBER>(10), static_cast<ACTIONSTAGE_NUMBER>(33) },
	      { static_cast<ACTIONSTAGE_NUMBER>(11), static_cast<ACTIONSTAGE_NUMBER>(56) },
	      { static_cast<ACTIONSTAGE_NUMBER>(12), static_cast<ACTIONSTAGE_NUMBER>(34) },
	      { static_cast<ACTIONSTAGE_NUMBER>(13), static_cast<ACTIONSTAGE_NUMBER>(57) },
	      { static_cast<ACTIONSTAGE_NUMBER>(14), static_cast<ACTIONSTAGE_NUMBER>(35) },
	      { static_cast<ACTIONSTAGE_NUMBER>(15), static_cast<ACTIONSTAGE_NUMBER>(58) },
	      { static_cast<ACTIONSTAGE_NUMBER>(36), static_cast<ACTIONSTAGE_NUMBER>(32) } };
STORY_INFO STORYMANAGE::storyInfo[5] = {
	{ storyTable_Sonic, 27 },
	{ storyTable_Dark, 27 },
	{ storyTable_Roses, 28 },
	{ storyTable_Chaotix, 27 },
	{ storyTable_Last, 8 },
};

s32 STORYMANAGE::SetStory(STORY_TYPE team)
{
	STORYMANAGE* cursor = this;
	s32 id;
	s32 offset;
	s32 sequence;
	s32 i;
	STORY_TABLE* entry;
	STORY_INFO* table;
	STORY_TABLE* current;

	fn_8001938C(lbl_8029C310);
	switch (team) {
		case 0:
			fn_8001934C(lbl_8029C310, 0, 0);
			break;
		case 1:
			fn_8001934C(lbl_8029C310, 0, 1);
			break;
		case 2:
			fn_8001934C(lbl_8029C310, 0, 2);
			break;
		case 3:
			fn_8001934C(lbl_8029C310, 0, 3);
			break;
		case 4:
			fn_8001934C(lbl_8029C310, 0, 2);
			break;
	}

	cursor->currentStory = team;
	if (team != 4) {
		sequence        = getCurrentSeq(team);
		cursor->seqStep = sequence;
	} else {
		cursor->seqStep = 0;
	}
	if (cursor->seqStep < 0)
		return 0;

	SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 39, 1);
	SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 38, 1);
	for (s32 channel = 1; channel < 4; channel++)
		fn_8001934C(lbl_8029C310, channel, -1);
	fn_800191F8(lbl_8029C310, 0, 0);

	table = &STORYMANAGE::storyInfo[cursor->currentStory];
	entry = table->storyTable;
	id    = entry[cursor->seqStep].seqFlag;
	i     = 0;
	while (id != entry->seqFlag) {
		entry++;
		i++;
		if (i >= table->ele)
			goto done;
	}
	sequence = 0;
	offset   = i * 12;
	do {
		current = (STORY_TABLE*)((u8*)table->storyTable + offset);
		if (current->type == 0) {
			fn_8001936C(lbl_8029C310, sequence, current->data);
			sequence++;
		}
		offset += 12;
		i++;
	} while (i < table->ele);
done:
	return 1;
}

extern "C" void fn_80138A9C(STORYMANAGE* cursor)
{
	s32 id;
	s32 sequence;
	s32 i;
	STORY_TABLE* entry;
	s32 offset;
	STORY_INFO* table;
	STORY_TABLE* current;
	s32 channel;

	cursor->seqStep = 0;
	SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 39, 1);
	SetModeSwitch__10MODESWITCHF15MODESWITCH_ENUMi(lbl_8042C180, 38, 1);
	fn_8001938C(lbl_8029C310);
	switch (cursor->currentStory) {
		case 0:
			fn_8001934C(lbl_8029C310, 0, 0);
			break;
		case 1:
			fn_8001934C(lbl_8029C310, 0, 1);
			break;
		case 2:
			fn_8001934C(lbl_8029C310, 0, 2);
			break;
		case 3:
			fn_8001934C(lbl_8029C310, 0, 3);
			break;
		case 4:
			fn_8001934C(lbl_8029C310, 0, 2);
			break;
	}
	for (channel = 1; channel < 4; channel++)
		fn_8001934C(lbl_8029C310, channel, -1);
	fn_800191F8(lbl_8029C310, 0, 0);

	table = &STORYMANAGE::storyInfo[cursor->currentStory];
	entry = table->storyTable;
	id    = entry[cursor->seqStep].seqFlag;
	i     = 0;
	while (id != entry->seqFlag) {
		entry++;
		i++;
		if (i >= table->ele)
			return;
	}
	sequence = 0;
	offset   = i * 12;
	do {
		current = (STORY_TABLE*)((u8*)table->storyTable + offset);
		if (current->type == 0) {
			fn_8001936C(lbl_8029C310, sequence, current->data);
			sequence++;
		}
		offset += 12;
		i++;
	} while (i < table->ele);
}

s32 STORYMANAGE::CheckStoryProgress(STORY_TYPE team, s32 count)
{
	STORYMANAGE* cursor = this;
	s32 index           = getCurrentSeq(team);
	s32 result;

	if (count != 0) {
		index = cursor->seqStep + count - 1;
	} else {
		index = getCurrentSeq(team);
	}

	if (index >= 0) {
		result = index * 100 / (STORYMANAGE::storyInfo[team].ele - 1);
		if (result > 100)
			return 100;
		return result;
	}
	return 100;
}

inline s32 STORYMANAGE::getCurrentSeq(STORY_TYPE team)
{
	int i;
	STORY_INFO* table = &STORYMANAGE::storyInfo[team];
	for (i = 0; i < table->ele; i++) {
		if (CheckSequenceVars__13TQuestSeqCtrlFi(table->storyTable[i].seqFlag) == 0)
			return i;
	}
	return -1;
}

SEQ_STAUS STORYMANAGE::StepStageSeq(ACTIONSTAGE_NUMBER value)
{
	STORYMANAGE* cursor  = this;
	STORY_TABLE* entries = STORYMANAGE::storyInfo[cursor->currentStory].storyTable;
	s32 index            = cursor->seqStep;
	if (entries[index].type == 0 && value == entries[index].data) {
		SetSequenceVars__13TQuestSeqCtrlFi(entries[index].seqFlag);
		memcpy((u8*)fn_80116D2C(lbl_803E774C) + 1441, seqVars__13TQuestSeqCtrl, 128);
		cursor->seqStep++;
		fn_801380B8(cursor);
		return static_cast<SEQ_STAUS>(
		    cursor->seqStep >= STORYMANAGE::storyInfo[cursor->currentStory].ele);
	}
	return SEQ_STAUS_NOHIT;
}

SEQ_STAUS STORYMANAGE::StepMovieSeq()
{
	STORYMANAGE* cursor  = this;
	s32 teamOffset       = cursor->currentStory * 8;
	STORY_INFO* tables   = STORYMANAGE::storyInfo;
	STORY_TABLE* entries = (*(STORY_INFO*)((u8*)tables + teamOffset)).storyTable;
	s32 index            = cursor->seqStep;
	if (entries[index].type == 1) {
		if (MovieNumber2EventNumber__10MOVIE_PLAYFi(MoviePlaySub)
		    != (*(STORY_INFO*)((u8*)tables + teamOffset)).storyTable[cursor->seqStep].data)
			goto not_matching;
		{
			STORY_TABLE* entries = (*(STORY_INFO*)((u8*)tables + teamOffset)).storyTable;
			s32 index            = cursor->seqStep;
			SetSequenceVars__13TQuestSeqCtrlFi(entries[index].seqFlag);
			memcpy((u8*)fn_80116D2C(lbl_803E774C) + 1441, seqVars__13TQuestSeqCtrl, 128);
			cursor->seqStep++;
			fn_801380B8(cursor);
			return static_cast<SEQ_STAUS>(
			    cursor->seqStep >= STORYMANAGE::storyInfo[cursor->currentStory].ele);
		}
	}
not_matching:
	return SEQ_STAUS_NOHIT;
}

extern "C" s32 fn_80138704(STORYMANAGE* cursor)
{
	STORY_TABLE* entries = STORYMANAGE::storyInfo[cursor->currentStory].storyTable;
	s32 index            = cursor->seqStep;
	if (entries[index].type == 2) {
		SetSequenceVars__13TQuestSeqCtrlFi(entries[index].seqFlag);
		memcpy((u8*)fn_80116D2C(lbl_803E774C) + 1441, seqVars__13TQuestSeqCtrl, 128);
		cursor->seqStep++;
		fn_801380B8(cursor);
		return static_cast<SEQ_STAUS>(
		    cursor->seqStep >= STORYMANAGE::storyInfo[cursor->currentStory].ele);
	}
	return SEQ_STAUS_NOHIT;
}

SEQ_TYPE STORYMANAGE::CheckCurrentSeqType()
{
	STORYMANAGE* cursor = this;
	if (cursor->seqStep >= STORYMANAGE::storyInfo[cursor->currentStory].ele)
		return static_cast<SEQ_TYPE>(-1);
	return STORYMANAGE::storyInfo[cursor->currentStory].storyTable[cursor->seqStep].type;
}

s32 STORYMANAGE::CurrentMovieNumber()
{
	STORYMANAGE* cursor = this;
	STORY_TABLE* entry  = &STORYMANAGE::storyInfo[cursor->currentStory].storyTable[cursor->seqStep];
	if (entry->type == 1)
		return EventNumber2MovieNumber__10MOVIE_PLAYFi(MoviePlaySub, entry->data);
	return -1;
}

s32 STORYMANAGE::WarpSeqStep(ACTIONSTAGE_NUMBER stage)
{
	STORY_INFO* info = &storyInfo[currentStory];
	s32 previous     = -1;
	s32 flag         = 1;
	seqStep          = 0;
	while (info->storyTable[seqStep].type != SEQ_STAGE || stage != info->storyTable[seqStep].data) {
		if (flag != 0 && info->storyTable[seqStep].type != SEQ_STAGE) {
			previous = seqStep;
			flag     = 0;
		}
		if (info->storyTable[seqStep].type == SEQ_STAGE) {
			previous = -1;
			flag     = 1;
		}
		++seqStep;
		if (seqStep >= info->ele)
			return 0;
	}
	if (previous >= 0)
		seqStep = previous;
	SetActionStageConnect(info->storyTable[seqStep].seqFlag);
	return 1;
}

inline s32 STORYMANAGE::SetActionStageConnect(s32 seqFlag)
{
	STORY_INFO* _info  = &storyInfo[currentStory];
	s32 _step          = 0;
	STORY_TABLE* entry = _info->storyTable;
	while (seqFlag != entry->seqFlag) {
		++entry;
		++_step;
		if (_step >= _info->ele)
			return 0;
	}
	s32 _stageCount = 0;
	do {
		if (_info->storyTable[_step].type == SEQ_STAGE) {
			fn_8001936C(lbl_8029C310, _stageCount, _info->storyTable[_step].data);
			++_stageCount;
		}
		++_step;
	} while (_step < _info->ele);
	return 1;
}

s32 STORYMANAGE::SetBonusStage(ACTIONSTAGE_NUMBER stage)
{
	s32 i;
	ACTIONSTAGE_NUMBER bonus = ACTIONSTAGE_END;
	for (i = 0; i < 15; ++i)
		if (stage == bonusStageTable[i].baseStage) {
			bonus = bonusStageTable[i].oppStage;
			break;
		}
	if (bonus == 0)
		return 0;
	fn_80018EFC(lbl_8029C310, bonus);
	return 1;
}

s32 STORYMANAGE::MustExit(ACTIONSTAGE_NUMBER stage)
{
	for (s32 i = 0; i < 3; ++i)
		if (stage == mustExitBeforePlay[i])
			return 1;
	return 0;
}

extern "C" s32 fn_801383F0(STORYMANAGE* self)
{
	if (static_cast<s8*>(lbl_8042C180)[0x27] != 0)
		return self->currentStory;
	return -1;
}

extern "C" s32 fn_801380B8(STORYMANAGE* self)
{
	u8* save   = static_cast<u8*>(fn_80116D2C(lbl_803E774C));
	save[0x1E] = static_cast<u8>(self->CheckStoryProgress(STORY_TYPE_SONIC, 0));
	save[0x1F] = static_cast<u8>(self->CheckStoryProgress(STORY_TYPE_DARK, 0));
	save[0x20] = static_cast<u8>(self->CheckStoryProgress(STORY_TYPE_ROSES, 0));
	save[0x21] = static_cast<u8>(self->CheckStoryProgress(STORY_TYPE_CHAOTIX, 0));
	return 1;
}
