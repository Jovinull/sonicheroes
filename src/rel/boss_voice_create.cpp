#include "types.h"

// Two helpers after TObjBossVoice's constructors (bossVoiceInterrupt and
// bossVoiceCreate here), the same in the six stage modules that carry the boss
// voices. bossVoiceInterrupt cuts the message being shown and stops the voice
// playing (fn_800CB15C). bossVoiceCreate makes a delayed voice (the first
// constructor, inlined) and answers it, or nothing when it could not be made
// or has already died.

typedef struct TObject {
	const char* className; // 0x00
	u16 signal;            // 0x04
	u8 unk06[0x12];
	void** vtable; // 0x18
	u8 unk1C[0x2];
	u16 dispTime; // 0x1E
	u8 unk20[0x8];
} TObject;

typedef struct BossVoice {
	TObject base; // 0x00
	u8 waiting;   // 0x28
	u8 unk29;     // 0x29
	u8 unk2A;     // 0x2A
	u8 pad2B;
	s32 voice;  // 0x2C
	s32 unk30;  // 0x30
	s32 team;   // 0x34
	f32* timer; // 0x38
	f32 delay;  // 0x3C
} BossVoice;

extern "C" const char* CL_TObjBossVoice;
extern "C" void* bossVoiceVtable[];

extern "C" void __ct__7TObjectFP7TObject(TObject* object, TObject* parent);

extern "C" void* lbl_8042C148;
extern "C" void* lbl_8042C610;
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" s32 fn_80017800(void* object);
extern "C" void fn_80110C7C(void* message);
extern "C" void fn_800CB15C(void);

extern "C" void bossVoiceInterrupt(void)
{
	if (lbl_8042C610 != NULL) {
		fn_80110C7C(lbl_8042C610);
	}
	fn_800CB15C();
}

extern "C" BossVoice* bossVoiceCreate(TObject* parent, s32 voice, f32* timer, f32 delay, s32 team)
{
	BossVoice* object = (BossVoice*)Malloc__9THeapCtrlFUi(lbl_8042C148, 0x40);

	if (object != NULL) {
		__ct__7TObjectFP7TObject(&object->base, parent);
		object->base.vtable    = bossVoiceVtable;
		object->base.className = CL_TObjBossVoice;
		object->base.dispTime  = 0x40;
		object->waiting        = 1;
		object->voice          = voice;
		object->unk30          = 0;
		object->team           = team;
		object->timer          = timer;
		object->delay          = delay;
		object->unk29          = 0;
		object->unk2A          = 0;
	}
	if (object == NULL) {
		return NULL;
	}
	if (fn_80017800(object) == 0) {
		return NULL;
	}
	return object;
}
