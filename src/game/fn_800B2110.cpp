#include "types.h"

// Silences one sound voice channel (HYPOTHESIS: stopping a sequenced sound): the id (+0x0) names
// a voice of lbl_80303FE0 and a MIDI channel (high and low nibble; ids above 0x26 are voices
// id - 0x23 on channel 0). On the three sequencer voices it sends control changes (status 0xB0):
// controller 0x3E to 0 when the sound mode switch 0x12 of lbl_8042C180 is 2 (surround-like), then
// controller 0xA (pan) to 0x40, and finally a note off (status 0x80, note 0x30); the other voices
// take fn_8020AAD4 and fn_8020AADC instead. The channel's state (+0x4, +0x5, +0xC..+0x34) is
// then cleared. The event layout is from fn_8020AF5C; the roles of the state are UNKNOWN.

struct Channel800B2110 {
	s8 id; // 0x0
	u8 pad1[0x4 - 0x1];
	u8 unknown4; // 0x4
	u8 unknown5; // 0x5
	u8 pad6[0xC - 0x6];
	s32 unknownC; // 0xC
	u8 pad10[0x12 - 0x10];
	s16 unknown12; // 0x12
	u8 pad14[0x16 - 0x14];
	s16 unknown16; // 0x16
	s16 unknown18; // 0x18
	u8 pad1A[0x1C - 0x1A];
	s32 unknown1C; // 0x1C
	u8 pad20[0x34 - 0x20];
	s32 unknown34; // 0x34
};

struct ModeSwitch800B2110 {
	u8 pad0[0x12];
	s8 sound; // 0x12 (mode switch 0x12, see fn_800B41A0)
};

extern "C" {
extern ModeSwitch800B2110* lbl_8042C180;
extern void* lbl_80303FE0[8];
int fn_8020AF5C(void* slot, u8* event, u8 status, ...);
int fn_8020AEA4(void* slot, u8* event, u8 unknown);
int fn_8020AAD4(void* slot, s32 unknown1, s32 unknown2);
int fn_8020AADC(void* slot);
}

// Sends one MIDI event to a voice (the note off in fn_800B2110 is written out with its own
// buffer, the retail stack layout).
static inline void Send(s8 voice, u8 status, s32 data1, s32 data2)
{
	u8 event[4];

	fn_8020AF5C(lbl_80303FE0[voice], event, status, data1, data2);
	fn_8020AEA4(lbl_80303FE0[voice], event, 0);
}

static inline void Center(s8 voice, s8 channel)
{
	if (voice >= 3) {
		fn_8020AAD4(lbl_80303FE0[voice], 0, 0);
	} else {
		Send(voice, channel | 0xB0, 0xA, 0x40);
	}
}

extern "C" void fn_800B2110(Channel800B2110* sound)
{
	s8 voice;
	s8 channel;
	u8 event[4];

	if (sound->id > 0x26) {
		voice   = sound->id - 0x23;
		channel = 0;
	} else {
		voice   = sound->id >> 4;
		channel = sound->id & 0xF;
	}
	if (lbl_8042C180 != NULL && lbl_8042C180->sound == 2) {
		if (voice < 3) {
			Send(voice, channel | 0xB0, 0x3E, 0);
		}
		Center(voice, channel);
	} else {
		Center(voice, channel);
	}
	sound->unknown4 = 0;
	sound->unknown5 = 0;
	if (voice >= 3) {
		fn_8020AADC(lbl_80303FE0[voice]);
	} else {
		fn_8020AF5C(lbl_80303FE0[voice], event, channel | 0x80, 0x30, 0);
		fn_8020AEA4(lbl_80303FE0[voice], event, 0);
	}
	sound->unknown1C = 0;
	sound->unknown18 = 0;
	sound->unknown12 = 0;
	sound->unknownC  = 0;
	sound->unknown16 = 0;
	sound->unknown34 = 0;
}
