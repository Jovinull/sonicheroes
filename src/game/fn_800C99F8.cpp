// Whether any sound stream reported an ADX error since the last check: reads and clears the error
// code of each stream's player (+0x44 for lbl_8042B624, +0x3C for lbl_8042B634) and returns 1 when
// any was set.
#include "types.h"

struct Main800C99F8 {
	u8 pad0[0x44];
	void* player; // 0x44
};

struct Voice800C99F8 {
	u8 pad0[0x3C];
	void* player; // 0x3C
};

extern "C" {
extern Main800C99F8* lbl_8042B624[2];
extern Voice800C99F8* lbl_8042B634[2];
s32 ADXT_GetErrCode(void* handle);
void ADXT_ClearErrCode(void* handle);
}

// Reads and clears the error code of a stream's ADX player; 1 when it was set.
template <class T> static inline s32 TakeError(T* s)
{
	if (s->player != NULL) {
		s32 code = ADXT_GetErrCode(s->player);

		ADXT_ClearErrCode(s->player);
		if (code != 0) {
			return 1;
		}
	}
	return 0;
}

extern "C" s32 fn_800C99F8(void)
{
	Main800C99F8* main;
	int i;
	s32 error;
	int j;
	Voice800C99F8* voice;

	error = 0;
	for (i = 0; i < 2; i++) {
		main = lbl_8042B624[i];
		if (main != NULL && TakeError(main)) {
			error = 1;
		}
	}
	for (j = 0; j < 2; j++) {
		voice = lbl_8042B634[j];
		if (voice != NULL && TakeError(voice)) {
			error = 1;
		}
	}
	return error;
}
