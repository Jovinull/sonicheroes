#include "types.h"

// TObjHintColli::DispExec (the PS2 build's name), the same in the thirteen
// stage modules that share the engine core: while the hint is shown, a busy
// hint message marks the team's slot in the game table as having seen a hint,
// and when the team's row has flag 0x100 the message is advanced
// (fn_80110C7C).

typedef struct HintColliTeam {
	u8 unk000[0x14C];
	s8 slot; // 0x14C
} HintColliTeam;

typedef struct HintColli {
	u8 unk000[0xF0];
	s32 team; // 0xF0
	u8 unk0F4[0x4];
	s32 shown; // 0xF8
} HintColli;

class HintMessage
{
public:
	inline u8 IsIdle()
	{
		u8 idle = 0;

		if (unk30 == 0 && unk3C == 0 && unk58 == -1) {
			idle = 1;
		}
		return idle;
	}

	u8 unk00[0x30];
	s32 unk30; // 0x30
	u8 unk34[0x8];
	s32 unk3C; // 0x3C
	u8 unk40[0x18];
	s32 unk58; // 0x58
};

typedef struct HintTableRow {
	u32 flags; // 0x00
	u8 unk04[0x48];
} HintTableRow; // 0x4C

typedef struct HintTable {
	u8 unk00[0x30];
	s32 seen[4]; // 0x30
	u8 unk40[0x10];
	HintTableRow rows[1]; // 0x50
} HintTable;

extern "C" HintColliTeam* lbl_80303DC8[];
extern "C" HintMessage* lbl_8042C610;
extern "C" HintTable lbl_8029BBD0;
extern "C" s32 lbl_802408F8[];
extern "C" void fn_80110C7C(HintMessage* message);

extern "C" void DispExec__13TObjHintColliFv(HintColli* object)
{
	if (object->shown == 1) {
		HintColliTeam* team  = lbl_80303DC8[object->team];
		HintMessage* message = lbl_8042C610;

		if (!message->IsIdle()) {
			lbl_8029BBD0.seen[team->slot] = 1;
		}
		if (lbl_8029BBD0.rows[lbl_802408F8[team->slot]].flags & 0x100) {
			fn_80110C7C(message);
		}
	}
}
