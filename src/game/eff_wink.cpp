#include "effect/eff_wink.h"

// eff_wink.cpp: PS2 C++ DWARF corroborates the class, members and methods.
// GameCube surviving text: 0x800CF070-0x800CF5E4; the following empty
// function belongs to another class's vtable. All ten methods match natively.
// Deferred emission reverses the definitions and permits Exec to inline
// SetMode; see docs/language-audit.md.
extern "C" s32 rand();

EffWink::EffWink()
{
	patno         = 0.0f;
	patno_max     = 0.0f;
	patno_speed   = 1.0f;
	timer         = 0;
	interval      = 0;
	interval_base = 0;
	interval_diff = 0;
	wink          = 0;
	mode          = EFFWINKMODE_MANUAL;
	mode_last     = EFFWINKMODE_MANUAL;
}

EffWink::~EffWink() { }

void EffWink::Exec()
{
	switch (mode) {
		case EFFWINKMODE_NORMAL:
			if (interval <= 0) {
				patno += patno_speed;
				if (patno_max < patno) {
					if ((s32)(2.0f * patno_max - patno) < 0) {
						patno = 0.0f;
						interval
						    = interval_base + (s32)(interval_diff * (rand() * (1.0f / 32768.0f)));
					}
				}
			} else {
				--interval;
			}
			break;
		case EFFWINKMODE_OPEN:
			if (patno != 0.0f) {
				if (patno_max < patno) {
					patno += patno_speed;
					if ((s32)(2.0f * patno_max - patno) < 0) {
						patno = 0.0f;
						interval
						    = interval_base + (s32)(interval_diff * (rand() * (1.0f / 32768.0f)));
					}
				} else {
					patno -= patno_speed;
					if (patno < 0.0f) {
						patno = 0.0f;
						interval
						    = interval_base + (s32)(interval_diff * (rand() * (1.0f / 32768.0f)));
					}
				}
			}
			break;
		case EFFWINKMODE_WINK:
			if (timer <= 0) {
				timer = 0;
				if (patno_max < patno) {
					patno += patno_speed;
					if ((s32)(2.0f * patno_max - patno) < 0) {
						patno = 0.0f;
						interval
						    = interval_base + (s32)(interval_diff * (rand() * (1.0f / 32768.0f)));
						SetMode(GetLastMode());
					}
				} else {
					patno += patno_speed;
					if (patno_max < patno) {
						timer = 30;
					}
				}
			} else {
				--timer;
			}
			break;
		case EFFWINKMODE_MANUAL:
			break;
	}
}

void EffWink::SetPatternMax(s32 patno_max_Set)
{
	patno_max = patno_max_Set;
	patno     = 0.0f;
}

void EffWink::SetPatternSpeed(f32 patno_speed_Set)
{
	patno_speed = patno_speed_Set;
}

void EffWink::SetMode(Enum_EffWinkMode mode_Request)
{
	mode_last = mode;
	mode      = mode_Request;
}

void EffWink::SetModeNormal(s32 _int_base, s32 _int_diff)
{
	interval_base = _int_base;
	interval_diff = _int_diff;
	interval      = 0;
	SetMode(EFFWINKMODE_NORMAL);
}

void EffWink::SetPatternForManualMode(s32 pat_Request)
{
	if (mode == EFFWINKMODE_MANUAL) {
		patno = pat_Request;
	}
}

s32 EffWink::GetPattern() const
{
	s32 patno_Ret = patno;
	if (patno_max < patno_Ret) {
		patno_Ret = (s32)(2.0f * patno_max) - patno_Ret;
		if (patno_Ret < 0) {
			patno_Ret = 0;
		}
	}
	return patno_Ret;
}

void EffWink::SyncPattern(EffWink* pBase)
{
	switch (pBase->GetMode()) {
		case EFFWINKMODE_NORMAL:
			SetPatternForManualMode(pBase->GetPattern());
			break;
	}
}
