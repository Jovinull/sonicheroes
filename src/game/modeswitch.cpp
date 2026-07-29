#include "types.h"

// The PS2 beta symbols identify this translation unit as modeswitch.cpp and
// name the class MODESWITCH. The correlated GameCube constructor, destructor,
// and setter form one contiguous text and exception-metadata range. The two
// adjacent initializer arrays and singleton are private data owned by the same
// unit.
//
// The retail setter deliberately accepts four more byte indices than the
// values-array layout would suggest, so the byte and word views overlap. This
// is also why flags has the PS2-era 0x28-byte shape while the constructor
// copies the full 0x2C-byte retail initializer.
enum MODESWITCH_ENUM { };

struct MODESWITCH {
	s8 flags[0x28];
	s32 values[6];

	MODESWITCH();
	~MODESWITCH();
	void SetModeSwitch(MODESWITCH_ENUM, int);
};

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
	memcpy(flags, lbl_802412C0, 0x2C);
	memcpy((u8*)this + 0x2C, lbl_802412EC, 0x18);

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
		values[index - 0x2C] = value;
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
