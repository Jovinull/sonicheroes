// Loads the texture dictionary of the current stage and language unless the object's mode (0x98)
// is 1: builds the path from one of two prefixes (chosen by fn_8019FE1C), the stage's name (the
// 51-entry stage table lbl_8028AA80, first entry as fallback), a variant suffix for stages 2-15
// and 0x24 (lbl_8028ACB4 by lbl_8029C310+0x23C), a mode suffix when the mode is 0 and the game
// state's byte 0x1E is clear, the language suffix and the extension lbl_8042BB64, then loads it
// (fn_801A157C, HYPOTHESIS: a texture dictionary read) into 0x38 through RsPathnameCreate.
// The table, suffix and field roles are inferred.
// NonMatching (1 word): retail sets the lookup index with its own li r6, 0, where MWCC here
// copies the name's zero (mr r6, r4). Tried: declaration orders, for-init forms, pointer and index
// loop shapes, -opt nopropagation and opt_* pragmas.
#include "types.h"

struct StageName8012E248 {
	s32 stage;
	const char* name;
};

struct Game8012E248 {
	u8 pad0[0x2C];
	s32 stage; // 0x2C
	u8 pad30[0x23C - 0x30];
	s32 f23C; // 0x23C
};

struct GameState8012E248 {
	u8 pad0[0x13];
	s8 language; // 0x13
	u8 pad14[0x1E - 0x14];
	s8 f1E; // 0x1E
	u8 pad1F[0x28 - 0x1F];
	s8 f28; // 0x28
};

struct Obj8012E248 {
	u8 pad0[0x38];
	void* textures; // 0x38
	u8 pad3C[0x98 - 0x3C];
	s32 f98; // 0x98
};

extern "C" {
extern StageName8012E248 lbl_8028AA80[51];
extern Game8012E248 lbl_8029C310;
extern GameState8012E248* lbl_8042C180;
extern const char* lbl_8028ACB4[];
extern const char* lbl_8028ACC4[];
extern const char* lbl_8028ACD0[];
extern char lbl_8028AD38[];
extern char lbl_8028AD54[];
extern char lbl_8042BB64[7];
char* strcpy(char* dst, const char* src);
char* strcat(char* dst, const char* src);
void* fn_8019FE1C(void);
void* fn_801A157C(char* path);
char* RsPathnameCreate(const char* path);
void RsPathnameDestroy(char* path);
}

static inline const char* GetStageName8012E248()
{
	const char* name         = NULL;
	s32 i                    = 0;
	StageName8012E248* entry = lbl_8028AA80;
	for (; i < 51; entry++, i++) {
		if (entry->stage == lbl_8029C310.stage) {
			name = lbl_8028AA80[i].name;
			break;
		}
	}
	if (name == NULL) {
		name = lbl_8028AA80[0].name;
	}
	return name;
}

extern "C" void fn_8012E248(Obj8012E248* o)
{
	char path[0x40];

	switch (o->f98) {
		case 1:
			return;
	}
	if (fn_8019FE1C() != NULL) {
		strcpy(path, lbl_8028AD38);
	} else {
		strcpy(path, lbl_8028AD54);
	}
	strcat(path, GetStageName8012E248());
	switch (lbl_8029C310.stage) {
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
			strcat(path, lbl_8028ACB4[lbl_8029C310.f23C]);
			break;
	}
	if (o->f98 == 0 && lbl_8042C180->f1E == 0) {
		strcat(path, lbl_8028ACC4[lbl_8042C180->f28]);
	}
	strcat(path, lbl_8028ACD0[lbl_8042C180->language]);
	strcat(path, lbl_8042BB64);
	char* full  = RsPathnameCreate(path);
	o->textures = fn_801A157C(full);
	RsPathnameDestroy(full);
}
