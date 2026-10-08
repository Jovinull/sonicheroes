// Complete C++ enemy/e_utility_system.cpp; the mode-field names and predicate
// below are local reconstruction labels, not asserted original spellings.
#include "game/enemy/e_utility_system.h"

struct SystemModeView {
	u8 unknown[0x1f];
	s8 flag1f, flag20, flag21;
};
extern "C" SystemModeView* lbl_8042C180;

static inline s32 TimerCanAdvance()
{
	if (lbl_8042C180->flag1f)
		return 0;
	if (lbl_8042C180->flag20)
		return 0;
	if (lbl_8042C180->flag21)
		return 0;
	return 1;
}

namespace nSystem
{
void DecreaseTimer(s32& timer)
{
	if (TimerCanAdvance())
		--timer;
}

void IncreaseTimer(s32& timer)
{
	if (TimerCanAdvance())
		++timer;
}
}
