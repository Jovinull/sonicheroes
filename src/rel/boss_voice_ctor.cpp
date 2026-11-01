#include "types.h"

// TObjBossVoice's two constructors (the PS2 build's names), the same in the six
// stage modules that carry the boss voices. The first queues a voice to play
// after a delay through a timer; the second plays it at once, unless the voice
// is a team's (flag 4 in the voice table) and that team (or the first, for a
// voice of no team) is not in state 3, in which case the object asks to be
// killed straight away. Nothing in the modules calls them; they are kept with
// force_active.

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
extern "C" BossVoiceEntry bossVoiceTable[];
extern "C" const f32 bossVoiceNoDelay;
extern "C" void* bossVoiceVtable[];
extern "C" BossVoiceTeam* lbl_80303DC8[];

extern "C" void __ct__7TObjectFP7TObject(TObject* object, TObject* parent);

extern "C" BossVoice* __ct__13TObjBossVoiceFP7TObjectiPffi(
    BossVoice* object, TObject* parent, s32 voice, f32* timer, f32 delay, s32 team)
{
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
	return object;
}

extern "C" BossVoice* __ct__13TObjBossVoiceFP7TObjectiii(
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
				return object;
			}
		} else if (lbl_80303DC8[0] != NULL && lbl_80303DC8[0]->state != 3) {
			object->base.signal |= 1;
			return object;
		}
	}
	object->unk29 = 0;
	object->timer = NULL;
	object->delay = bossVoiceNoDelay;
	object->unk2A = 0;
	return object;
}
