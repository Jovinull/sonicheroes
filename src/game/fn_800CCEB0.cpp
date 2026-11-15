#include "types.h"

// Stops and resets every ADX stream: the two music streams of lbl_8042B624 (ADXT_Stop, unpaused,
// their name table's entries reset with ADXT_ResetEntry and the table deleted, the state, mode and
// flags cleared, both volumes -90 (+0x34/+0x38), +0x3C = -1 and the two 0x20-byte areas +0x50 and
// +0x70 cleared) and the two effect streams of lbl_8042B634 (stopped, ids -1, volume -50); each
// stream's output volume is then reapplied. HYPOTHESIS: the field names (see fn_800CADD8 and
// fn_800CAFCC) are UNKNOWN beyond the ADXT handle.
// NonMatching (9 words, registers only): in both loops retail keeps the table pointer in r31 and
// the counter below it; MWCC swaps them. The two loops as inlines and the declaration order of
// the first one fix the rest; pointer walks, array bounds and counter forms did not help.

struct StreamNames800CCEB0 {
	s8 unknown0; // 0x0
	s8 unknown1; // 0x1
	u8 pad2[0x8 - 0x2];
	void* adxt; // 0x8

	~StreamNames800CCEB0() { }
};

struct Stream800CCEB0 {
	u8 pad0[0x29];
	s8 state;     // 0x29
	s8 mode;      // 0x2A
	u8 flags;     // 0x2B
	s8 unknown2C; // 0x2C
	u8 pad2D[0x30 - 0x2D];
	s32 unknown30; // 0x30
	s32 volume34;  // 0x34
	s32 volume;    // 0x38
	s32 unknown3C; // 0x3C
	s32 unknown40; // 0x40
	void* adxt;    // 0x44
	u8 pad48[0x4C - 0x48];
	StreamNames800CCEB0* names; // 0x4C
	u8 area50[0x20];            // 0x50
	u8 area70[0x20];            // 0x70
};

struct Effect800CCEB0 {
	u8 pad0[0x29];
	s8 state;      // 0x29
	s8 id;         // 0x2A
	u8 flags;      // 0x2B
	s32 unknown2C; // 0x2C
	s32 unknown30; // 0x30
	s32 unknown34; // 0x34
	s32 volume;    // 0x38
	void* adxt;    // 0x3C
};

extern "C" {
extern Stream800CCEB0* lbl_8042B624[2];
extern Effect800CCEB0* lbl_8042B634[2];
void* memset(void* dst, int c, unsigned long n);
void ADXT_Stop(void* adxt);
void ADXT_Pause(void* adxt, s32 pause);
void ADXT_ResetEntry(void* adxt);
void ADXT_SetOutVol(void* adxt, s32 volume);
}

static inline void StopStreams()
{
	StreamNames800CCEB0* names;
	Stream800CCEB0* stream;
	s32 i;

	for (i = 0; i < 2; i++) {
		stream = lbl_8042B624[i];
		if (stream == NULL) {
			continue;
		}
		ADXT_Stop(stream->adxt);
		ADXT_Pause(stream->adxt, 0);
		names = stream->names;
		if (names != NULL) {
			ADXT_ResetEntry(names->adxt);
			names->unknown0 = -1;
		}
		stream->state = 0;
		stream->flags &= ~1;
		if (stream->names != NULL) {
			delete stream->names;
			stream->names = NULL;
		}
		stream->state     = 0;
		stream->mode      = 0;
		stream->flags     = 0;
		stream->unknown2C = 0;
		stream->unknown30 = 0;
		stream->unknown40 = 0;
		stream->volume = stream->volume34 = -90;
		stream->unknown3C                 = -1;
		memset(stream->area50, 0, sizeof(stream->area50));
		memset(stream->area70, 0, sizeof(stream->area70));
		ADXT_SetOutVol(stream->adxt, stream->volume);
	}
}

static inline void StopEffects()
{
	for (s32 i = 0; i < 2; i++) {
		Effect800CCEB0* effect = lbl_8042B634[i];
		if (effect == NULL) {
			continue;
		}
		ADXT_Stop(effect->adxt);
		ADXT_Pause(effect->adxt, 0);
		effect->id = effect->unknown30 = effect->unknown2C = -1;
		effect->state                                      = 0;
		effect->flags &= ~1;
		effect->state     = 0;
		effect->id        = -1;
		effect->unknown2C = -1;
		effect->unknown30 = -1;
		effect->unknown34 = -1;
		effect->volume    = -50;
		effect->flags     = 0;
		ADXT_SetOutVol(effect->adxt, effect->volume);
	}
}

extern "C" void fn_800CCEB0(void)
{
	StopStreams();
	StopEffects();
}
