#include "types.h"

typedef struct RinoColTask RinoColTask;
struct RinoColTask {
	u8 unk00[0x28];
	u16 classId; // 0x28
	u8 unk2A[0x6];
	s32* work; // 0x30
	u8 unk34[0x4];
	RinoColTask* next; // 0x38
};

typedef struct RinoColTaskLists {
	u8 unk00[0x30];
	RinoColTask* lists[1]; // 0x30
} RinoColTaskLists;

extern "C" {
extern u8 lbl_8029C310[];
extern RinoColTaskLists* lbl_8042C298;
s32 fn_16_9FBC(void*);
RinoColTask* fn_16_33DC(RinoColTaskLists*, s32);

s32 fn_16_3D790(void)
{
	RinoColTask* task;
	s32* work;

	if (fn_16_9FBC(lbl_8029C310) != 9) {
		return 0;
	}
	for (task = fn_16_33DC(lbl_8042C298, 0); task != NULL; task = task->next) {
		if (task->classId == 0x743) {
			work = task->work;
			if (work == NULL) {
				return 0;
			}
			return *work;
		}
	}
	return 0;
}
}
