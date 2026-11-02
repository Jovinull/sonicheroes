#include "types.h"

// TObjEnemyCapture's destructor (captureDtor here; the PS2 build's class
// name), the same in the seven stage modules that carry the capture: it
// forgets its held player (as captureDropPlayer does), kills its paralysis,
// closes both icons, deletes its motion, releases its parts (as
// captureReleaseParts does), then runs the motion holder's and TObjEnemy's
// destructors and frees itself when asked.

typedef struct CapturePlayer {
	u8 unk000[0x6F0];
	s16 state; // 0x6F0
} CapturePlayer;

typedef struct CaptureParalysis {
	u8 unk00[0x4];
	u16 signal; // 0x04
} CaptureParalysis;

class TEnemyIconMan
{
public:
	void Close();
};

class CaptureMotion
{
public:
	virtual ~CaptureMotion();
};

typedef struct HAnimClass {
	CaptureMotion* motion; // 0x00
} HAnimClass;

typedef struct Capture {
	u8 unk000[0x18];
	void** vtable; // 0x018
	u8 unk01C[0x98];
	void** vtable2; // 0x0B4
	u8 unk0B8[0x30];
	void* body; // 0x0E8
	u8 unk0EC[0x154];
	HAnimClass anim;             // 0x240
	CaptureParalysis* paralysis; // 0x244
	u8 unk248[0x30];
	s32 player; // 0x278
	u8 unk27C[0x5C];
	void* parts[5]; // 0x2D8
	u8 unk2EC[0x4];
	TEnemyIconMan* lifeIcon;   // 0x2F0
	TEnemyIconMan* searchIcon; // 0x2F4
} Capture;

extern "C" void* __vt__16TObjEnemyCapture[];
extern "C" CapturePlayer* lbl_802AD070[];
extern "C" void* lbl_8042C148;

extern "C" void fn_80043DEC(void);
extern "C" void fn_80150958(void* part);
extern "C" void __dt__10HAnimClassFv(HAnimClass* anim, s32 flags);
extern "C" void fn_800A7088(Capture* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" Capture* captureDtor(Capture* object, s16 flags)
{
	if (object != NULL) {
		object->vtable  = __vt__16TObjEnemyCapture;
		object->vtable2 = __vt__16TObjEnemyCapture + 11;
		{
			s32 player = object->player;

			if (player != -1) {
				CapturePlayer* body = lbl_802AD070[player];

				if (body != NULL) {
					if (body->state == 0x26) {
						fn_80043DEC();
					}
					object->player = -1;
				}
			}
		}
		if (object->paralysis != NULL) {
			object->paralysis->signal |= 1;
			object->paralysis = NULL;
		}
		if (object->lifeIcon != NULL) {
			object->lifeIcon->Close();
			object->lifeIcon = NULL;
		}
		if (object->searchIcon != NULL) {
			object->searchIcon->Close();
			object->searchIcon = NULL;
		}
		if (object->anim.motion != NULL) {
			delete object->anim.motion;
			object->anim.motion = NULL;
		}
		if (object->parts[4] != NULL) {
			fn_80150958(object->parts[4]);
			object->parts[4] = NULL;
		}
		if (object->parts[3] != NULL) {
			fn_80150958(object->parts[3]);
			object->parts[3] = NULL;
		}
		if (object->parts[2] != NULL) {
			fn_80150958(object->parts[2]);
			object->parts[2] = NULL;
		}
		if (object->parts[1] != NULL) {
			fn_80150958(object->parts[1]);
			object->parts[1] = NULL;
		}
		if (object->parts[0] != NULL) {
			fn_80150958(object->parts[0]);
			object->parts[0] = NULL;
		}
		if (object->body != NULL) {
			fn_80150958(object->body);
			object->body = NULL;
		}
		__dt__10HAnimClassFv(&object->anim, 0);
		fn_800A7088(object, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
