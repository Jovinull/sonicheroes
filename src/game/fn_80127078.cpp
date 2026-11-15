// Polls the status step of a memory card task (HYPOTHESIS; names inferred): when the task is not
// busy elsewhere (fn_801276A8), reads the card result (CARDGetResultCode once the status flag
// 0x4 is set, otherwise CARDGetStatus of the task's file). A busy card waits; an error goes to
// fn_80127760. On success sets the status flag and, by operation (0x18): operation 2 reports
// message 0xB, operations 4 and 5 go to step 8 for a file without data (0x6C of the file record
// is -1) or report 0xA (4) or 0xB (5), and every other operation goes to step 2 (fn_80127808).
#include "types.h"

#define CARD_RESULT_READY 0
#define CARD_RESULT_BUSY  (-1)
#define CARD_TASK_STATUS  0x4

struct CardFile80127078 {
	u8 pad0[0x38];
	s32 fileNo;      // 0x38
	u8 status[0x30]; // 0x3C: CARDStat
	u32 value6C;     // 0x6C
};

struct CardTask80127078 {
	CardFile80127078* file; // 0x0
	s32 channel;            // 0x4
	u8 pad8[0x18 - 0x8];
	s32 operation; // 0x18
	s32 step;      // 0x1C
	u32 flags;     // 0x20
};

extern "C" {
s32 CARDGetResultCode(s32 channel);
s32 CARDGetStatus(s32 channel, s32 fileNo, void* stat);
s32 fn_801276A8(CardTask80127078* task);
void fn_80127760(CardTask80127078* task, s32 result);
void fn_80127808(CardTask80127078* task);
void fn_80127904(CardTask80127078* task, s32 message);

void fn_80127078(CardTask80127078* task)
{
	s32 result;

	if (fn_801276A8(task) != 0) {
		return;
	}
	if (task->flags & CARD_TASK_STATUS) {
		result = CARDGetResultCode(task->channel);
	} else {
		result = CARDGetStatus(task->channel, task->file->fileNo, task->file->status);
	}
	if (result == CARD_RESULT_BUSY) {
		return;
	}
	if (result == CARD_RESULT_READY) {
		task->flags |= CARD_TASK_STATUS;
		switch (task->operation) {
			case 0:
			case 1:
			case 3:
			case 6:
			default:
				task->step = 2;
				fn_80127808(task);
				break;
			case 2:
				fn_80127904(task, 0xB);
				break;
			case 4:
			case 5:
				if (task->file->value6C == 0xFFFFFFFF) {
					task->step = 8;
					fn_80127808(task);
				} else if (task->operation == 4) {
					fn_80127904(task, 0xA);
				} else {
					fn_80127904(task, 0xB);
				}
				break;
		}
	} else {
		fn_80127760(task, result);
	}
}
}
