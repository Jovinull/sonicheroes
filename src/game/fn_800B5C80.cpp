#include "types.h"

// Resets the sound manager's sequencer channels (HYPOTHESIS: stopping every sequenced sound):
// runs fn_800B48B8 and fn_8020AC50, then on each of the 16 MIDI channels of the eight voices of
// lbl_80303FE0 sends controller 0x3E = 0 when the sound mode switch 0x12 of lbl_8042C180 is 2
// (sequencer voices only), controller 0xA (pan) = 0x40 (fn_8020AAD4 on the other voices) and the
// event 0x79 (reset all controllers is controller 0x79; here it is the status byte, as retail
// passes it). The 0x2B channel records at +0x8 (0x38 bytes each; see fn_800B2110) are then
// cleared: record i > 0 takes id i, +0x1/+0x2 become -1, the floats lbl_8042DCE8 (0.0f) and the
// rest 0. The roles of the record fields are UNKNOWN.
// NonMatching (18 words, registers only): retail keeps the channel counter in r30 and the walked
// voice-table pointer in r28; MWCC swaps them (as in fn_800B5EBC). Declaration orders, while
// loops, a scoped channel, a reused counter and an explicit table pointer did not fix it.

struct Channel800B5C80 {
	s8 id;         // 0x0
	s8 unknown1;   // 0x1
	s8 unknown2;   // 0x2
	u8 unknown3;   // 0x3
	u8 unknown4;   // 0x4
	u8 unknown5;   // 0x5
	u8 unknown6;   // 0x6
	u8 unknown7;   // 0x7
	u8 unknown8;   // 0x8
	u8 unknown9;   // 0x9
	s32 unknownC;  // 0xC
	s16 unknown10; // 0x10
	s16 unknown12; // 0x12
	s16 unknown14; // 0x14
	s16 unknown16; // 0x16
	s16 unknown18; // 0x18
	s32 unknown1C; // 0x1C
	f32 unknown20; // 0x20
	f32 unknown24; // 0x24
	f32 unknown28; // 0x28
	f32 unknown2C; // 0x2C
	f32 unknown30; // 0x30
	s32 unknown34; // 0x34
};

struct Sound800B5C80 {
	u8 pad0[0x8];
	Channel800B5C80 channels[0x2B]; // 0x8
};

struct ModeSwitch800B5C80 {
	u8 pad0[0x12];
	s8 sound; // 0x12 (mode switch 0x12, see fn_800B41A0)
};

extern "C" {
extern ModeSwitch800B5C80* lbl_8042C180;
extern void* lbl_80303FE0[8];
extern const f32 lbl_8042DCE8; // 0.0f
void fn_800B48B8(Sound800B5C80* sound);
void fn_8020AC50(void);
int fn_8020AF5C(void* slot, u8* event, u8 status, ...);
int fn_8020AEA4(void* slot, u8* event, u8 unknown);
int fn_8020AAD4(void* slot, s32 unknown1, s32 unknown2);
}

// Sends one MIDI event to a voice (as in fn_800B2110).
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

extern "C" void fn_800B5C80(Sound800B5C80* sound)
{
	s8 voice;
	s8 channel;
	s8 i;
	u8 event[4];

	fn_800B48B8(sound);
	fn_8020AC50();
	for (voice = 0; voice < 8; voice++) {
		for (channel = 0; channel < 0x10; channel++) {
			if (lbl_8042C180 != NULL && lbl_8042C180->sound == 2) {
				if (voice < 3) {
					Send(voice, channel | 0xB0, 0x3E, 0);
				}
				Center(voice, channel);
			} else {
				Center(voice, channel);
			}
			fn_8020AF5C(lbl_80303FE0[voice], event, 0x79, 0);
			fn_8020AEA4(lbl_80303FE0[voice], event, 0);
		}
	}
	for (i = 0; i < 0x2B; i++) {
		Channel800B5C80* record = &sound->channels[i];
		if (i > 0) {
			record->id = i;
		}
		record->unknown1  = -1;
		record->unknown2  = -1;
		record->unknown3  = 0;
		record->unknown4  = 0;
		record->unknown6  = 0;
		record->unknown5  = 0;
		record->unknown7  = 0;
		record->unknown8  = 0;
		record->unknown9  = 0;
		record->unknownC  = 0;
		record->unknown10 = 0;
		record->unknown12 = 0;
		record->unknown14 = 0;
		record->unknown16 = 0;
		record->unknown18 = 0;
		record->unknown1C = 0;
		record->unknown28 = lbl_8042DCE8;
		record->unknown24 = lbl_8042DCE8;
		record->unknown20 = lbl_8042DCE8;
		record->unknown2C = lbl_8042DCE8;
		record->unknown30 = lbl_8042DCE8;
		record->unknown34 = 0;
	}
}
