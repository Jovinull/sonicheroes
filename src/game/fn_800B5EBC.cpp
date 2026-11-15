#include "game/rw_engine.h"

// Starts the sound manager's streams (returns 1): stops a running setup (fn_8020AD44, mode 2 of
// fn_8020ADCC, the two state bytes +0x974/+0x975 and the flag +0x970 cleared), runs fn_800B48B8,
// loads the sound data file lbl_80253898 once (+0x5; fn_800426E0 reads it, fn_8020B44C opens a
// handle that fn_8020B3B4 fills and fn_8020B14C, fn_8020B2FC finish, and the file buffer is
// freed), and when not running restarts the eight voices of lbl_80303FE0 (fn_8020AD88,
// fn_8020A704 with the state byte) and sets +0x970. HYPOTHESIS: the fn_8020A* sound library calls
// are UNKNOWN.
// NonMatching (9 words, registers only): in the voice loop retail keeps the counter in r30 and the
// table pointer in r29 (MWCC swaps them), and loads the state byte into r0 before sign-extending
// it into r4. Passing (s8)(u8)state reproduces the load (7 words left); pointer walks, a u8 state
// field and other counter forms did not fix the swap.

struct Sound800B5EBC {
	u8 pad0[0x5];
	s8 loaded; // 0x5
	u8 pad6[0x970 - 0x6];
	s32 running; // 0x970
	s8 state;    // 0x974
	s8 previous; // 0x975
};

extern "C" {
extern char lbl_80253898[];
extern void* lbl_80303FE0[8];
void fn_8020AD44(void);
void fn_8020ADCC(s32 mode);
void fn_800B48B8(Sound800B5EBC* sound);
void* fn_800426E0(char* name, u32* size);
u32 fn_8020B44C(void** handle);
s32 fn_8020B3B4(void* handle, void* data, u32 size, s32 unknown1, s32 unknown2);
void fn_8020B14C(void* handle);
void fn_8020B2FC(void* handle);
void fn_8020AD88(s32 unknown1, s32 unknown2);
void fn_8020A704(void* voice, s32 state);
}

extern "C" s32 fn_800B5EBC(Sound800B5EBC* sound)
{
	if (sound->running != 0) {
		fn_8020AD44();
		fn_8020ADCC(2);
		sound->running = sound->previous = sound->state = 0;
	}
	fn_800B48B8(sound);
	if (sound->loaded != 1) {
		char* name = lbl_80253898;
		if (name != NULL) {
			void* handle = NULL;
			u32 size;
			void* data = fn_800426E0(name, &size);
			if (data != NULL) {
				if (fn_8020B44C(&handle) == 0 && fn_8020B3B4(handle, data, size, -1, 0) == 0) {
					fn_8020B14C(handle);
				}
				if (handle != NULL) {
					fn_8020B2FC(handle);
				}
				lbl_8042C9A4->rwfree(data);
			}
		}
		sound->loaded = 1;
	}
	if (sound->running == 0) {
		fn_8020AD88(0, 0);
		s8 i;
		sound->previous = sound->state;
		sound->state = i = 0;
		for (; i < 8; i++) {
			fn_8020A704(lbl_80303FE0[i], sound->state);
		}
		fn_8020ADCC(2);
		sound->previous = sound->state = 0;
		sound->running                 = 1;
	}
	return 1;
}
