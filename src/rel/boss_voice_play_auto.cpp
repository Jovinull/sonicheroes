#include "types.h"

// bossVoicePlayAuto (our name), in the six stage modules that carry the boss
// voices: as bossVoicePlay (rel/boss_voice_play.cpp), under the stage's event
// object when there is one and under the root object otherwise. Each branch
// builds the voice in its own pointer, which the retail then copies.

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

typedef struct BossVoiceEntry {
	u8 unk00[0x8];
	u32 flags; // 0x08
	u8 unk0C[0x4];
} BossVoiceEntry;

typedef struct BossVoiceTeam {
	u8 unk00[0x34];
	s32 state; // 0x34
} BossVoiceTeam;

extern "C" const char* CL_TObjBossVoice;
extern "C" void* bossVoiceVtable[];

extern "C" void __ct__7TObjectFP7TObject(TObject* object, TObject* parent);

extern "C" BossVoiceEntry bossVoiceTable[];
extern "C" const f32 bossVoiceNoDelay;
extern "C" BossVoiceTeam* lbl_80303DC8[];
extern "C" void* lbl_8042C148;
extern "C" TObject* lbl_8042C2A0;
extern "C" TObject* lbl_8042C110;
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" s32 fn_80017800(void* object);

static inline void bossVoiceInitNow(
    BossVoice* object, TObject* parent, s32 voice, s32 arg, s32 team)
{
	__ct__7TObjectFP7TObject(&object->base, parent);
	object->base.vtable    = bossVoiceVtable;
	object->base.className = CL_TObjBossVoice;
	object->base.dispTime  = 0x40;
	object->waiting        = 0;
	object->voice          = voice;
	object->unk30          = arg;
	object->team           = team;
	if (((BossVoiceEntry*)((u8*)bossVoiceTable + (object->voice << 4)))->flags & 4) {
		if (object->team >= 0) {
			if (lbl_80303DC8[object->team] != NULL && lbl_80303DC8[object->team]->state != 3) {
				object->base.signal |= 1;
				return;
			}
		} else if (lbl_80303DC8[0] != NULL && lbl_80303DC8[0]->state != 3) {
			object->base.signal |= 1;
			return;
		}
	}
	object->unk29 = 0;
	object->timer = NULL;
	object->delay = bossVoiceNoDelay;
	object->unk2A = 0;
	return;
}

extern "C" BossVoice* bossVoicePlayAuto(s32 voice, s32 arg, s32 team)
{
	BossVoice* object;

	if (lbl_8042C2A0 != NULL) {
		BossVoice* made = (BossVoice*)Malloc__9THeapCtrlFUi(lbl_8042C148, 0x40);

		if (made != NULL) {
			bossVoiceInitNow(made, lbl_8042C2A0, voice, arg, team);
		}
		object = made;
	} else {
		BossVoice* made = (BossVoice*)Malloc__9THeapCtrlFUi(lbl_8042C148, 0x40);

		if (made != NULL) {
			bossVoiceInitNow(made, lbl_8042C110, voice, arg, team);
		}
		object = made;
	}
	if (object == NULL) {
		return NULL;
	}
	if (fn_80017800(object) == 0) {
		return NULL;
	}
	return object;
}
