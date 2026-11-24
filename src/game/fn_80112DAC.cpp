// Installs the callbacks fn_80112BB0 / fn_801127FC (lbl_8042C0D8 / lbl_8042C0DC) and loads the
// language archive: releases the texture held at lbl_802636A0 (fn_801A46D0), creates the ONEFILE
// at lbl_802636A0+4 on first use and points it at the in-memory archive of the current language
// (lbl_80288B28[language], byte 0x13 of the game state lbl_8042C180; language 1 without a game
// state). The roles of the callbacks and of the archive are UNKNOWN.
#include "game/one.h"

struct LangFile80112DAC {
	void* data; // 0x0
	s32 size;   // 0x4
};

struct State80112DAC {
	void* texture; // 0x0
	ONEFILE* one;  // 0x4
	u8 pad8[0x20 - 0x8];
};

struct GameState80112DAC {
	u8 pad0[0x13];
	s8 language; // 0x13
};

extern "C" {
extern void* lbl_8042C0D8;
extern void* lbl_8042C0DC;
extern GameState80112DAC* lbl_8042C180;
extern State80112DAC lbl_802636A0;
extern LangFile80112DAC lbl_80288B28[];
void fn_80112BB0(void);
void fn_801127FC(void);
void fn_801A46D0(void* p);
}

static inline void LoadLanguageFile80112DAC(s32 language)
{
	if (lbl_802636A0.texture != NULL) {
		fn_801A46D0(lbl_802636A0.texture);
		lbl_802636A0.texture = NULL;
	}
	if (lbl_802636A0.one == NULL) {
		lbl_802636A0.one = new ONEFILE(NULL, 0);
	}
	lbl_802636A0.one->SetOneFile(lbl_80288B28[language].data, lbl_80288B28[language].size, 0);
}

extern "C" void fn_80112DAC(void)
{
	lbl_8042C0D8 = (void*)fn_80112BB0;
	lbl_8042C0DC = (void*)fn_801127FC;
	if (lbl_8042C180 != NULL) {
		LoadLanguageFile80112DAC(lbl_8042C180->language);
	} else {
		LoadLanguageFile80112DAC(1);
	}
}
