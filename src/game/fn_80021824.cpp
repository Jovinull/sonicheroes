// Resets the four-word cache record to 0, -1, -1, -1.
#include "types.h"

struct Fn80021824Cache {
	s32 f0;
	s32 f4;
	s32 f8;
	s32 fC;
};

extern "C" {
extern Fn80021824Cache lbl_802AD060;

void fn_80021824(void)
{
	lbl_802AD060.f0 = 0;
	lbl_802AD060.f4 = -1;
	lbl_802AD060.f8 = -1;
	lbl_802AD060.fC = -1;
}
}
