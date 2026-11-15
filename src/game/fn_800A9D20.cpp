#include "types.h"

// Ends a game session (the game task object): runs fn_80112DAC, releases the camera (+0x3C:
// fn_80177C50, fn_8019CC00), marks the task (+0x4 = 1), deletes the task +0x68, clears +0x28/+0x2C
// and, when there is a stage object (+0x30), calls its release hook (+0x14) and updates the
// session flags (+0x58: 0x30 set; with 0x100 the end-of-stage cleanup runs for 0x10 or 0x20
// unless 0x40 is set, which instead becomes 0x10, and 0x100 is cleared) before fn_80196D00. It then
// loads lbl_80253158 into lbl_8042C1C0 (fn_800421C8) and, in play modes 0 and 1 (lbl_8042C180
// +0x38), resets the mode switches 0x28 and 0x30 (5 for type 5 when flag 24 is set, else 2).
// HYPOTHESIS: the roles are UNKNOWN.

// A TObject (vtable pointer at +0x18, virtual destructor first). Nothing here is defined, so no
// vtable is emitted.
class TObject800A9D20
{
public:
	u8 pad0[0x18];
	virtual ~TObject800A9D20();
};

struct Stage800A9D20 {
	u8 pad0[0x14];
	void (*release)(Stage800A9D20* self); // 0x14
};

struct Game800A9D20 {
	u8 pad0[0x4];
	s32 ended; // 0x4
	u8 pad8[0x28 - 0x8];
	void* unknown28;      // 0x28
	void* unknown2C;      // 0x2C
	Stage800A9D20* stage; // 0x30
	u8 pad34[0x3C - 0x34];
	void* camera; // 0x3C
	u8 pad40[0x58 - 0x40];
	u32 flags; // 0x58
	u8 pad5C[0x68 - 0x5C];
	TObject800A9D20* task; // 0x68
};

// The play-mode switches (see fn_800B41A0); the switch numbers used here are UNKNOWN.
enum MODESWITCH_ENUM { MODESWITCH_ENUM_0 };

class MODESWITCH
{
public:
	void SetModeSwitch(MODESWITCH_ENUM which, int value);

	s8 flags[0x38]; // 0x0
	s32 mode;       // 0x38
	s32 type;       // 0x3C
};

extern "C" {
extern MODESWITCH* lbl_8042C180;
extern void* lbl_8042C1C0;
extern char lbl_80253158[];
extern u8 lbl_8029C2E4[];
void fn_80112DAC(void);
void fn_80177C50(void);
void fn_8019CC00(void* camera);
void fn_8012ECE0(void);
void fn_80110C18(void);
void fn_80016BBC(void* object);
void fn_800CC280(void);
void fn_800CD05C(void);
void fn_80196D00(void);
void fn_800421C8(void** out, char* name);
}

void RemoveLangMessage();

extern "C" void fn_800A9D20(Game800A9D20* game)
{
	fn_80112DAC();
	if (game->camera != NULL) {
		fn_80177C50();
		fn_8019CC00(game->camera);
		game->camera = NULL;
	}
	game->ended = 1;
	if (game->task != NULL) {
		delete game->task;
	}
	game->task      = NULL;
	game->unknown28 = NULL;
	game->unknown2C = NULL;
	if (game->stage != NULL) {
		game->stage->release(game->stage);
		game->flags |= 0x30;
		u32 flags = game->flags;
		if (flags & 0x100) {
			if (!(flags & 0x40)) {
				if ((flags & 0x10) || (flags & 0x20)) {
					fn_8012ECE0();
					fn_80110C18();
					fn_80016BBC(lbl_8029C2E4);
					RemoveLangMessage();
					fn_800CC280();
					fn_800CD05C();
				}
			} else {
				game->flags = flags | 0x10;
				game->flags &= ~0x40;
			}
			game->flags &= ~0x100;
		}
		fn_80196D00();
		game->stage = NULL;
	}
	fn_800421C8(&lbl_8042C1C0, lbl_80253158);
	switch (lbl_8042C180->mode) {
		case 0:
		case 1:
			if (lbl_8042C180->flags[0x18] != 0) {
				lbl_8042C180->SetModeSwitch((MODESWITCH_ENUM)0x28, 0);
				if (lbl_8042C180->type == 5) {
					lbl_8042C180->SetModeSwitch((MODESWITCH_ENUM)0x30, 5);
				} else {
					lbl_8042C180->SetModeSwitch((MODESWITCH_ENUM)0x30, 2);
				}
			} else {
				lbl_8042C180->SetModeSwitch((MODESWITCH_ENUM)0x30, 2);
			}
			break;
	}
}
