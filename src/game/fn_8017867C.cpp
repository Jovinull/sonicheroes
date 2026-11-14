// Sets up the record lbl_8028D840 (the counterpart of fn_80178608): allocates its 0x18000-byte
// buffer (+0xC) and its 0x3000-byte buffer (+0x10) with the engine memory function, then clears the
// words at +0x8 and +0x4 and sets +0x0 to 1. When the second allocation fails the first buffer is
// released again. Names are UNKNOWN. Returns 1 on success, 0 on failure.
#include "game/rw_engine.h"

struct Rec8017867C {
	s32 f0;
	s32 f4;
	s32 f8;
	void* bufferC;  // 0xC
	void* buffer10; // 0x10
};

extern "C" {
extern Rec8017867C lbl_8028D840;

s32 fn_8017867C(void)
{
	lbl_8028D840.bufferC = lbl_8042C9A4->rwmalloc(0x18000);
	if (lbl_8028D840.bufferC == 0) {
		return 0;
	}
	lbl_8028D840.buffer10 = lbl_8042C9A4->rwmalloc(0x3000);
	if (lbl_8028D840.buffer10 == 0) {
		lbl_8042C9A4->rwfree(lbl_8028D840.bufferC);
		lbl_8028D840.bufferC = 0;
		return 0;
	}
	lbl_8028D840.f8 = 0;
	lbl_8028D840.f4 = 0;
	lbl_8028D840.f0 = 1;
	return 1;
}
}
