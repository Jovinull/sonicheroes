#ifndef EFFECT_EFF_WINK_H
#define EFFECT_EFF_WINK_H

#include "types.h"

enum Enum_EffWinkMode {
	EFFWINKMODE_NORMAL,
	EFFWINKMODE_WINK,
	EFFWINKMODE_OPEN,
	EFFWINKMODE_MANUAL,
	NUM_EFFWINKMODE
};

class EffWink
{
public:
	EffWink();
	~EffWink();
	void Exec();
	void SetPatternMax(s32);
	void SetPatternSpeed(f32);
	void SetMode(Enum_EffWinkMode);
	void SetModeNormal(s32, s32);
	void SetPatternForManualMode(s32);
	s32 GetPattern() const;
	void SyncPattern(EffWink*);
	Enum_EffWinkMode GetMode() const { return mode; }
	Enum_EffWinkMode GetLastMode() const { return mode_last; }

private:
	f32 patno, patno_max, patno_speed;
	Enum_EffWinkMode mode_last, mode;
	s32 timer, interval, interval_base, interval_diff, wink;
};

#endif
