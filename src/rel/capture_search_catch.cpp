#include "types.h"

// The capture enemy's search (captureSearchCatch here), the same in the seven
// stage modules that carry the capture: an enemy of kind 2, 6, 9 or 0x2C that
// holds nobody looks for the nearest player within its search range of a
// point below it, and catches it (as captureCatchPlayer does, inlined) when
// fn_800AB25C gives 1. Returns whether a player was caught.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

namespace nSearchPlayer
{
s32 GetNearestPlayerNum(const RwV3d* pos, f32 distance);
}

typedef struct Capture {
	u8 unk000[0x140];
	RwV3d pos; // 0x140
	u8 unk14C[0x50];
	s32 kind; // 0x19C
	u8 unk1A0[0xD4];
	s32 found;  // 0x274
	s32 player; // 0x278
	u8 unk27C[0x2F4];
	s32 catchKind; // 0x570
} Capture;

typedef struct CapturePlayer CapturePlayer;

extern "C" CapturePlayer* lbl_802AD070[];
extern "C" const f32 captureSearchDrop;
extern "C" const f32 captureSearchRange;

extern "C" s32 fn_800AB25C(s32 player);
extern "C" s32 fn_800AB2E0(CapturePlayer* body);
extern "C" s32 fn_80089204(CapturePlayer* body);
extern "C" void fn_80043F28(CapturePlayer* body);
extern "C" void fn_800E1208(s32 player, s32 mode, s32 arg);

// captureCatchPlayer (rel/capture_catch_player.cpp), inlined.
static inline s32 captureCatch(Capture* object)
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

extern "C" s32 captureSearchCatch(Capture* object)
{
	if (object->player != -1) {
		return 0;
	}
	switch (object->kind) {
		case 2:
		case 6:
		case 9:
		case 0x2C:
			break;
		default:
			return 0;
	}

	RwV3d at = object->pos;

	at.y -= captureSearchDrop;
	object->found = nSearchPlayer::GetNearestPlayerNum(&at, captureSearchRange);
	if (object->found != -1 && fn_800AB25C(object->found) == 1) {
		return captureCatch(object);
	}
	return 0;
}
