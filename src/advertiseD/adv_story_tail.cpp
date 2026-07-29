#include "types.h"

// Two TAdvStoryTitle methods linked after the advertiseD REL-generated
// _unresolved/_epilog/_prolog unit.

extern "C" {

#pragma force_active on

struct Title {
	/* 0x00 */ void* name;
	/* 0x04 */ u8 pad_04[0x18 - 0x04];
	/* 0x18 */ void* vtable;
	/* 0x1C */ u8 pad_1C[0x1E - 0x1C];
	/* 0x1E */ u16 unk_1E;
	/* 0x20 */ u8 pad_20[0x28 - 0x20];
	/* 0x28 */ void* window;
	/* 0x2C */ f32 timer;
	/* 0x30 */ u8 pad_30[0x34 - 0x30];
	/* 0x34 */ s32 flag_34;
};

// 0x88C4 - clear the title fade flag.
void fn_1_88C4(Title* self)
{
	self->flag_34 = 0;
}

// 0x88D0 - set the title fade flag and seed the timer from a tick count.
void fn_1_88D0(Title* self, s32 ticks)
{
	self->flag_34 = 1;
	self->timer   = (f32)ticks;
}

#pragma force_active reset
}
