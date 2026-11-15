// Polls the create step of a memory card task (HYPOTHESIS; names inferred): when the task is not
// busy elsewhere (fn_801276A8) and the card is not busy, an error goes to fn_80127760. On success,
// operation 2 fills the file's banner and icon description from the save description at 0x2C
// (comment and icon addresses, banner format, one icon format and speed per icon frame, the end
// speed after the last one and the animation mode) and reports message 0xD; operation 5 continues
// with fn_80127884 and any other one goes to step 2 (fn_80127808).
#include "types.h"

// The parts of the SDK CARDStat used here (dolphin/card.h only builds as C).
struct CARDStat80126C88 {
	u8 pad0[0x2E];
	u8 bannerFormat; // 0x2E
	u8 pad2F;
	u32 iconAddr;    // 0x30
	u16 iconFormat;  // 0x34
	u16 iconSpeed;   // 0x36
	u32 commentAddr; // 0x38
};

#define CARD_STAT_BANNER_MASK 0x03
#define CARD_STAT_ANIM_MASK   0x04
#define CARD_STAT_ICON_MASK   0x03
#define CARD_STAT_SPEED_MASK  0x03
#define CARD_STAT_SPEED_END   0

// SDK macro forms (CARDSetBannerFormat, CARDSetIconAnim, CARDSetIconFormat, CARDSetIconSpeed).
#define CARDSetBannerFormat(stat, f)                                                               \
	((stat)->bannerFormat = (u8)(((stat)->bannerFormat & ~CARD_STAT_BANNER_MASK) | (f)))
#define CARDSetIconAnim(stat, f)                                                                   \
	((stat)->bannerFormat = (u8)(((stat)->bannerFormat & ~CARD_STAT_ANIM_MASK) | (f)))
#define CARDSetIconFormat(stat, n, f)                                                              \
	((stat)->iconFormat                                                                            \
	    = (u16)(((stat)->iconFormat & ~(CARD_STAT_ICON_MASK << (2 * (n)))) | ((f) << (2 * (n)))))
#define CARDSetIconSpeed(stat, n, f)                                                               \
	((stat)->iconSpeed                                                                             \
	    = (u16)(((stat)->iconSpeed & ~(CARD_STAT_SPEED_MASK << (2 * (n)))) | ((f) << (2 * (n)))))

#define CARD_RESULT_READY 0
#define CARD_RESULT_BUSY  (-1)

struct CardFile80126C88 {
	u8 pad0[0x3C];
	CARDStat80126C88 stat; // 0x3C
};

struct SaveInfo80126C88 {
	u8 pad0[0x18];
	u32 commentAddress; // 0x18
	u32 iconAddress;    // 0x1C
	u8 pad20[0x24 - 0x20];
	s32 numIcons; // 0x24
};

struct CardTask80126C88 {
	CardFile80126C88* file; // 0x0
	s32 channel;            // 0x4
	u8 pad8[0x18 - 0x8];
	s32 operation; // 0x18
	s32 step;      // 0x1C
	u8 pad20[0x2C - 0x20];
	SaveInfo80126C88* save; // 0x2C
};

extern "C" {
s32 CARDGetResultCode(s32 channel);
s32 fn_801276A8(CardTask80126C88* task);
void fn_80127760(CardTask80126C88* task, s32 result);
void fn_80127808(CardTask80126C88* task);
void fn_80127884(CardTask80126C88* task);
void fn_80127904(CardTask80126C88* task, s32 message);
// HYPOTHESIS: the banner format, icon speed, icon format and animation mode of a save.
s32 fn_801265B4(SaveInfo80126C88* save);
s32 fn_80126560(SaveInfo80126C88* save);
s32 fn_80126598(void);
s32 fn_8012653C(SaveInfo80126C88* save);

void fn_80126C88(CardTask80126C88* task)
{
	s32 result;

	if (fn_801276A8(task) != 0) {
		return;
	}
	result = CARDGetResultCode(task->channel);
	if (result == CARD_RESULT_BUSY) {
		return;
	}
	if (result == CARD_RESULT_READY) {
		if (task->operation == 2) {
			CARDStat80126C88* stat = &task->file->stat;
			s32 speed;
			s32 i;

			stat->commentAddr = task->save->commentAddress;
			CARDSetBannerFormat(stat, fn_801265B4(task->save));
			stat->iconAddr = task->save->iconAddress;
			speed          = fn_80126560(task->save);
			for (i = 0; i < task->save->numIcons; i++) {
				CARDSetIconFormat(stat, i, fn_80126598());
				CARDSetIconSpeed(stat, i, speed);
			}
			CARDSetIconSpeed(stat, task->save->numIcons, CARD_STAT_SPEED_END);
			CARDSetIconAnim(stat, fn_8012653C(task->save));
			fn_80127904(task, 0xD);
		} else if (task->operation == 5) {
			fn_80127884(task);
		} else {
			task->step = 2;
			fn_80127808(task);
		}
	} else {
		fn_80127760(task, result);
	}
}
}
