#include "types.h"

// Starts AFS sound `file` with priority `priority` on one of the two voice streams lbl_8042B634
// (HYPOTHESIS: the voice/jingle player; see fn_800CB84C) and returns the stream used, or -1. A
// stream already playing `id` (+0x30) is reused when the new priority wins over its own (+0x2A);
// otherwise an idle stream (state +0x29 not 1) is taken, else the playing stream with the
// weakest priority that the new one beats. A priority wins over a stream's priority p when p is
// not 3 and either p <= 0 or p < the new one. The stream is stopped and cleared, and when the
// play-mode flag 23 of lbl_8042C180 is set it starts `file` (ADXT_StartAfs, partition 0).
// NonMatching (one instruction shorter, registers): retail has an unreachable second branch to
// the shared tail after the id match, walks the table in r4 with the stream in r3 (MWCC swaps
// them), and in the second search hoists the sign-extended priority (r7) and keeps the best slot
// in r4. Tried: a switch on the state, double gotos, a local for the stream's priority.

struct Voice800CB368 {
	u8 pad0[0x29];
	s8 state;    // 0x29
	s8 priority; // 0x2A
	u8 flags;    // 0x2B
	s32 file;    // 0x2C
	s32 id;      // 0x30
	u8 pad34[0x3C - 0x34];
	void* adxt; // 0x3C
};

struct PlayMode800CB368 {
	s8 flags[44];
};

extern "C" {
extern Voice800CB368* lbl_8042B634[2];
extern PlayMode800CB368* lbl_8042C180;
void ADXT_Stop(void* adxt);
void ADXT_Pause(void* adxt, s32 pause);
void ADXT_StartAfs(void* adxt, s32 partition, s32 file);
}

// Whether `priority` wins over a stream playing with priority `current`.
static inline BOOL Wins(s8 current, s8 priority)
{
	if (current == 3) {
		return FALSE;
	}
	if (current <= 0) {
		return TRUE;
	}
	return current < priority;
}

extern "C" s32 fn_800CB368(s32 file, s8 priority, s32 id)
{
	s32 slot;

	if (id >= 0) {
		for (slot = 0; slot < 2; slot++) {
			Voice800CB368* voice = lbl_8042B634[slot];
			if (voice != NULL && voice->id == id) {
				if (!Wins(voice->priority, priority)) {
					slot = -1;
				}
				goto found;
			}
		}
	}
	{
		s32 best = -1;
		for (slot = 0; slot < 2; slot++) {
			Voice800CB368* voice = lbl_8042B634[slot];
			if (voice == NULL) {
				continue;
			}
			switch (voice->state) {
				case 1:
					break;
				default:
					goto found;
			}
			s8 current = voice->priority;
			if (Wins(current, priority) == TRUE) {
				if (best < 0) {
					best = slot;
				} else if (Wins(current, lbl_8042B634[best]->priority) == TRUE) {
					best = slot;
				}
			}
		}
		slot = best;
	}
found:
	if (slot < 0) {
		return -1;
	}
	Voice800CB368* voice = lbl_8042B634[slot];
	ADXT_Stop(voice->adxt);
	ADXT_Pause(voice->adxt, 0);
	voice->file     = -1;
	voice->id       = -1;
	voice->priority = -1;
	voice->state    = 0;
	voice->flags &= ~1;
	voice = lbl_8042B634[slot];
	if (lbl_8042C180->flags[23] != 0) {
		voice->file     = file;
		voice->priority = priority;
		voice->id       = id;
		ADXT_StartAfs(voice->adxt, 0, voice->file);
		voice->state = 1;
	}
	return slot;
}
