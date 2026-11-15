// Starts event 0x1004 of a controller unless it is already busy (+0x3 > 0): allocates the event
// (fn_800B55E4), sets its code 0x85, clears two bytes and gives it the value of lbl_80253810 for
// the controller's alternating index (+0x4), which then flips between 0 and 1; the controller
// state becomes 2. Returns 1, or 0 when busy or when no event could be allocated. The roles are
// UNKNOWN.
#include "types.h"

struct Event800B4984 {
	u8 pad0[4];
	s8 value; // 0x4
	u8 pad5[2];
	s8 unknown7; // 0x7
	s8 unknown8; // 0x8
	u8 pad9[3];
	s32 code; // 0xC
};

struct Ctrl800B4984 {
	u8 pad0[3];
	s8 state; // 0x3
	s8 index; // 0x4
};

extern "C" {
extern s8 lbl_80253810[];
Event800B4984* fn_800B55E4(Ctrl800B4984* ctrl, s32 id, s32 a, s32 b);

s32 fn_800B4984(Ctrl800B4984* ctrl)
{
	Event800B4984* event;
	s8 next;

	if (ctrl->state > 0) {
		return 0;
	}
	event = fn_800B55E4(ctrl, 0x1004, 0, 0);
	if (event == NULL) {
		return 0;
	}
	event->code     = 0x85;
	event->unknown7 = event->unknown8 = next = 0;
	event->value                             = lbl_80253810[ctrl->index];
	if (ctrl->index == 0) {
		next = 1;
	}
	ctrl->index = (s32)next; // the retail code sign-extends the byte again before the store
	ctrl->state = 2;
	return 1;
}
}
