#include "types.h"

// The blink helpers of the common stage object base (propBase here; the
// class has no PS2 name), the same in the six stage modules that carry it.
// The object keeps a hit timer per player; while one runs, it blinks with
// the given period (flag 0x2000 while hidden), unless the game is in stop
// state 1 or the object is destroyed (flag 0x10). propBaseBlinkColor blinks
// a value between two colors near the end of the hit time instead.
// propBaseTimersDown counts the timers down, and propBaseTeamReady tells
// whether fn_80020BD8 accepts mode 0xF for the player.

class PARAM_SCORE
{
public:
	s32 isFlag(u32 flag) { return (flags & flag) != 0; }
	void onFlag(u32 flag) { flags |= flag; }
	void offFlag(u32 flag) { *(volatile u32*)&flags &= ~flag; }

	u32 flags; // 0x00
};

static inline s32 propHasFlag(u32 flags, u32 flag)
{
	return (flags & flag) != 0;
}

typedef struct GameInfo {
	u8 unk00[0x1F];
	s8 paused; // 0x1F
	s8 stop;   // 0x20
	u8 unk21[0xF];
	s32 frame;      // 0x30
	s32 pauseFrame; // 0x34
} GameInfo;

typedef struct PropBase {
	u8 unk000[0xB0];
	PARAM_SCORE param; // 0x0B0
	u8 unk0B4[0x18];
	s16 hitTime;   // 0x0CC
	s16 timers[8]; // 0x0CE
} PropBase;

extern "C" GameInfo* lbl_8042C180;
extern "C" u8 lbl_8042C1A4[];

extern "C" void fn_80021824(void* list);
extern "C" s32 fn_80020BD8(s32 player, s32 mode);

extern "C" s32 propBaseBlink(PropBase* object, s16 period)
{
	u32 flags;
	s16 longest;
	s32 frame;
	u8 i;

	if (lbl_8042C180->stop == 1) {
		object->param.offFlag(0x2000);
		return 0;
	}
	flags = object->param.flags;
	if (propHasFlag(flags, 0x10) == 1) {
		object->param.offFlag(0x2000);
		return 0;
	}
	longest = -1;
	for (i = 0; i < 8; i++) {
		if (longest < object->timers[i]) {
			longest = object->timers[i];
		}
	}
	if (lbl_8042C180->paused != 0) {
		frame = lbl_8042C180->pauseFrame;
	} else {
		frame = lbl_8042C180->frame;
	}
	if (longest > 0) {
		if (frame % (period * 2) > period) {
			if ((flags & 0x2000) == 0) {
				object->param.onFlag(0x2000);
			}
			return 1;
		}
		if ((flags & 0x2000) != 0) {
			object->param.offFlag(0x2000);
		}
		return 0;
	}
	if ((flags & 0x2000) != 0) {
		object->param.offFlag(0x2000);
	}
	return 0;
}

extern "C" u8 propBaseBlinkColor(PropBase* object, s16 period, u8* color, u8 normal, u8 blink)
{
	s16 longest = -1;
	u8 i;

	for (i = 0; i < 8; i++) {
		if (longest < object->timers[i]) {
			longest = object->timers[i];
		}
	}
	if (longest > object->hitTime - period * 5 && longest > 0) {
		if (lbl_8042C180->frame % (period * 2) > period) {
			*color = blink;
		} else {
			*color = normal;
		}
	} else if ((s8)*color != (s8)normal) {
		*color = normal;
	}
	return *color;
}

extern "C" s32 propBaseTeamReady(PropBase* object, s32 player)
{
	fn_80021824(lbl_8042C1A4);
	return fn_80020BD8(player, 0xF) != 0;
}

extern "C" void propBaseTimersDown(PropBase* object)
{
	s32 i;

	for (i = 0; i < 8; i++) {
		if (object->timers[i] > 0) {
			object->timers[i]--;
		}
	}
}
