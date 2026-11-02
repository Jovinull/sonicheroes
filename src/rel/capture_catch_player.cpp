#include "types.h"

// The capture enemy's catch (captureCatchPlayer here), the same in the seven
// stage modules that carry the capture: a found player that fn_800AB2E0
// accepts is caught (kind 1 when fn_80089204 says so, otherwise kind 2 after
// fn_80043F28), put in mode 0x17 and held. Kind 0 when it was not taken.
// Returns whether the player was caught.

typedef struct Capture {
	u8 unk000[0x274];
	s32 found;  // 0x274
	s32 player; // 0x278
	u8 unk27C[0x2F4];
	s32 catchKind; // 0x570
} Capture;

typedef struct CapturePlayer CapturePlayer;

extern "C" CapturePlayer* lbl_802AD070[];

extern "C" s32 fn_800AB2E0(CapturePlayer* body);
extern "C" s32 fn_80089204(CapturePlayer* body);
extern "C" void fn_80043F28(CapturePlayer* body);
extern "C" void fn_800E1208(s32 player, s32 mode, s32 arg);

extern "C" s32 captureCatchPlayer(Capture* object)
{
	s32 found = object->found;

	if (found != -1) {
		CapturePlayer* body = lbl_802AD070[found];

		if (body != NULL && fn_800AB2E0(body) != 0) {
			if (fn_80089204(body) != 0) {
				object->catchKind = 1;
			} else {
				object->catchKind = 2;
				fn_80043F28(body);
			}
			fn_800E1208(object->found, 0x17, 0);
			object->player = object->found;
			return 1;
		}
		object->catchKind = 0;
	}
	return 0;
}
