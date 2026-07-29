#include "types.h"

struct VoiceEntry {
	int id;
	int type;
	int value;
};

struct VoiceTable {
	VoiceEntry* entries;
	int count;
};

struct VoiceCursor {
	int team;
	int index;
};

extern "C" {
extern void* lbl_8042C180;
extern u8 lbl_8029C310[];
extern u8 lbl_803EC340[];
extern u8 lbl_803E774C[];
extern u8 lbl_803E75E8[];
extern VoiceEntry lbl_8028C448[];
extern VoiceEntry lbl_8028C58C[];
extern VoiceEntry lbl_8028C6D0[];
extern VoiceEntry lbl_8028C820[];

VoiceEntry lbl_8028C964[8] = {
	{ 109, 1, 400 },
	{ 110, 1, 401 },
	{ 111, 1, 402 },
	{ 112, 0, 23 },
	{ 113, 1, 403 },
	{ 114, 0, 24 },
	{ 115, 1, 404 },
	{ 116, 2, 0 },
};
u32 lbl_8028C9C4[3]  = { 2, 17, 20 };
u32 lbl_8028C9D0[30] = {
	2,
	29,
	3,
	52,
	4,
	30,
	5,
	53,
	6,
	31,
	7,
	54,
	8,
	32,
	9,
	55,
	10,
	33,
	11,
	56,
	12,
	34,
	13,
	57,
	14,
	35,
	15,
	58,
	36,
	32,
};
VoiceTable lbl_8028CA48[5] = {
	{ lbl_8028C448, 27 },
	{ lbl_8028C58C, 27 },
	{ lbl_8028C6D0, 28 },
	{ lbl_8028C820, 27 },
	{ lbl_8028C964, 8 },
};

void fn_8001F4E8(void*, s32, s32);
void fn_8001938C(void*);
void fn_8001934C(void*, s32, s32);
void fn_800191F8(void*, s32, s32);
void fn_8001936C(void*, s32, s32);
s32 fn_801143E0(s32);
void fn_8011445C(s32);
void* fn_80116D2C(void*);
void fn_801380B8(VoiceCursor*);
s32 fn_801390A4(void*, s32);
s32 fn_801390D8(void*);
void* memcpy(void*, const void*, unsigned long);
}

#pragma opt_propagation off
extern "C" s32 fn_80138664(VoiceCursor* cursor)
{
	VoiceEntry* entry = &lbl_8028CA48[cursor->team].entries[cursor->index];
	if (entry->type == 1)
		return fn_801390A4(lbl_803EC340, entry->value);
	return -1;
}

extern "C" s32 fn_801386C4(VoiceCursor* cursor)
{
	if (cursor->index >= lbl_8028CA48[cursor->team].count)
		return -1;
	return lbl_8028CA48[cursor->team].entries[cursor->index].type;
}

extern "C" s32 fn_80138704(VoiceCursor* cursor)
{
	VoiceEntry* entries = lbl_8028CA48[cursor->team].entries;
	s32 index           = cursor->index;
	if (entries[index].type == 2) {
		fn_8011445C(entries[index].id);
		memcpy((u8*)fn_80116D2C(lbl_803E774C) + 1441, lbl_803E75E8, 128);
		cursor->index++;
		fn_801380B8(cursor);
#pragma cplusplus off
		return cursor->index >= lbl_8028CA48[cursor->team].count;
#pragma cplusplus on
	}
	return 2;
}

extern "C" s32 fn_801387C8(VoiceCursor* cursor)
{
	s32 teamOffset      = cursor->team * 8;
	VoiceTable* tables  = lbl_8028CA48;
	VoiceEntry* entries = (*(VoiceTable*)((u8*)tables + teamOffset)).entries;
	s32 index           = cursor->index;
	if (entries[index].type == 1) {
		if (fn_801390D8(lbl_803EC340)
		    != (*(VoiceTable*)((u8*)tables + teamOffset)).entries[cursor->index].value)
			goto not_matching;
		{
			VoiceEntry* entries = (*(VoiceTable*)((u8*)tables + teamOffset)).entries;
			s32 index           = cursor->index;
			fn_8011445C(entries[index].id);
			memcpy((u8*)fn_80116D2C(lbl_803E774C) + 1441, lbl_803E75E8, 128);
			cursor->index++;
			fn_801380B8(cursor);
#pragma cplusplus off
			return cursor->index >= lbl_8028CA48[cursor->team].count;
#pragma cplusplus on
		}
	}
not_matching:
	return 2;
}

extern "C" s32 fn_801388C4(VoiceCursor* cursor, s32 value)
{
	VoiceEntry* entries = lbl_8028CA48[cursor->team].entries;
	s32 index           = cursor->index;
	if (entries[index].type == 0 && value == entries[index].value) {
		fn_8011445C(entries[index].id);
		memcpy((u8*)fn_80116D2C(lbl_803E774C) + 1441, lbl_803E75E8, 128);
		cursor->index++;
		fn_801380B8(cursor);
#pragma cplusplus off
		return cursor->index >= lbl_8028CA48[cursor->team].count;
#pragma cplusplus on
	}
	return 2;
}

#pragma opt_propagation on
inline int FindAvailableVoice(int team)
{
	int i;
	VoiceTable* table = &lbl_8028CA48[team];
	for (i = 0; i < table->count; i++) {
		if (fn_801143E0(table->entries[i].id) == 0)
			return i;
	}
	return -1;
}

extern "C" s32 fn_80138994(VoiceCursor* cursor, s32 team, s32 count)
{
	s32 index = FindAvailableVoice(team);
	s32 result;

	if (count != 0) {
		index = cursor->index + count - 1;
	} else {
		index = FindAvailableVoice(team);
	}

	if (index >= 0) {
		result = index * 100 / (lbl_8028CA48[team].count - 1);
		if (result > 100)
			result = 100;
		return result;
	}
	return 100;
}
#pragma opt_propagation off

extern "C" void fn_80138A9C(VoiceCursor* cursor)
{
	s32 id;
	s32 sequence;
	s32 i;
	VoiceEntry* entry;
	s32 offset;
	VoiceTable* table;
	VoiceEntry* current;
	s32 channel;

	cursor->index = 0;
	fn_8001F4E8(lbl_8042C180, 39, 1);
	fn_8001F4E8(lbl_8042C180, 38, 1);
	fn_8001938C(lbl_8029C310);
	switch (cursor->team) {
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

	table = &lbl_8028CA48[cursor->team];
	entry = table->entries;
	id    = entry[cursor->index].id;
	i     = 0;
	while (id != entry->id) {
		entry++;
		i++;
		if (i >= table->count)
			return;
	}
	sequence = 0;
	offset   = i * 12;
	do {
		current = (VoiceEntry*)((u8*)table->entries + offset);
		if (current->type == 0) {
			fn_8001936C(lbl_8029C310, sequence, current->value);
			sequence++;
		}
		offset += 12;
		i++;
	} while (i < table->count);
}

#pragma opt_propagation on
extern "C" s32 fn_80138C78(VoiceCursor* cursor, int team)
{
	s32 id;
	s32 offset;
	s32 sequence;
	s32 i;
	VoiceEntry* entry;
	VoiceTable* table;
	VoiceEntry* current;

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

	cursor->team = team;
	if (team != 4) {
		sequence      = FindAvailableVoice(team);
		cursor->index = sequence;
	} else {
		cursor->index = 0;
	}
	if (cursor->index < 0)
		return 0;

	fn_8001F4E8(lbl_8042C180, 39, 1);
	fn_8001F4E8(lbl_8042C180, 38, 1);
	for (team = 1; team < 4; team++)
		fn_8001934C(lbl_8029C310, team, -1);
	fn_800191F8(lbl_8029C310, 0, 0);

	table = &lbl_8028CA48[cursor->team];
	entry = table->entries;
	id    = entry[cursor->index].id;
	i     = 0;
	while (id != entry->id) {
		entry++;
		i++;
		if (i >= table->count)
			goto done;
	}
	sequence = 0;
	offset   = i * 12;
	do {
		current = (VoiceEntry*)((u8*)table->entries + offset);
		if (current->type == 0) {
			fn_8001936C(lbl_8029C310, sequence, current->value);
			sequence++;
		}
		offset += 12;
		i++;
	} while (i < table->count);
done:
	return 1;
}
#pragma opt_propagation off
