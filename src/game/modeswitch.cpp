#include "types.h"

// The PS2 beta symbols identify this translation unit as modeswitch.cpp and
// name the class MODESWITCH. The correlated GameCube constructor, destructor,
// and setter form one contiguous text and exception-metadata range. The two
// adjacent initializer arrays and singleton are private data owned by the same
// unit.
//
// The GameCube constructor copies 0x2C flag bytes followed by six words, so
// this class is 0x44 bytes. The PS2 metadata's 0x28-byte flags describe a
// different platform layout and must not determine the GameCube object size.
// The retail setter also accepts the boundary index 0x2C, addressing the final
// four flag bytes as a word; its guard/index behavior is preserved below.
enum MODESWITCH_ENUM { };

struct MODESWITCH {
	s8 flags[0x2C];
	s32 values[6];

	MODESWITCH();
	~MODESWITCH();
	void SetModeSwitch(MODESWITCH_ENUM, int);
};

typedef char ModeSwitchSizeCheck[(sizeof(MODESWITCH) == 0x44) ? 1 : -1];

extern "C" {
extern MODESWITCH* lbl_8042C180[2];
extern s8 lbl_802412C0[0x2C];
extern s32 lbl_802412EC[7];

void fn_8011273C(s32);
void* memcpy(void*, const void*, u32);
}

#pragma force_active on

MODESWITCH::MODESWITCH()
{
	memcpy(flags, lbl_802412C0, sizeof(flags));
	memcpy(values, lbl_802412EC, sizeof(values));

	if (lbl_8042C180[0] == NULL) {
		lbl_8042C180[0] = this;
	}
}

MODESWITCH::~MODESWITCH()
{
	if (lbl_8042C180[0] == this) {
		lbl_8042C180[0] = NULL;
	}
}

void MODESWITCH::SetModeSwitch(MODESWITCH_ENUM index, int value)
{
	if (index < 0) {
		return;
	}

	if (index < 0x2C) {
		flags[index] = value;
		if (index == 0x13) {
			fn_8011273C(value);
		}
	} else if (index < 0x33) {
		values[index - 0x2D] = value;
	}
}

// These must remain writable. With deferred C++ emission, const arrays move to
// .rodata instead of the original writable .data section.
extern "C" s8 lbl_802412C0[0x2C] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1,
	1,
	0,
	1,
	0,
	1,
	1,
	1,
	1,
	1,
	0,
	0,
	1,
	1,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1,
	0,
	0,
	0,
	-1,
	0,
};

extern "C" s32 lbl_802412EC[7] = {
	0,
	0,
	0,
	0,
	0,
	-1,
	0,
};

extern "C" {
MODESWITCH* lbl_8042C180[2];
}
