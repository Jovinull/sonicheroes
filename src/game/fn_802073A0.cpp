// Applies a pitch bend to a voice entry (see game/audio_system.h): the bend times the entry's up or
// down range gives an offset in 1/8192 semitones, turned into a ratio by octaves (2), semitones
// (2^(1/12)), 1/8-semitone steps (2^(1/96)) and 1/128-semitone steps (2^(1/1536)), inverted for
// negative offsets. The AX voice's sample-rate ratio becomes baseRate * ratio / 65536 * level.
// NonMatching: 169 of 170 instructions. Retail reloads the 1.0f constant for the final division
// (a compiler literal is rematerialized), while the shared extern const lbl_8042FFDC is kept in a
// register (fmr); writing the literal fixes that path but would add a .sdata2 entry this per-
// function unit does not own. The final product also targets f2 (then fmr f1) in retail.
#include "game/audio_system.h"

extern "C" {
extern const float lbl_8042FFDC;  // 1.0f
extern const double lbl_8042FFE8; // 2.0
extern const double lbl_8042FFF0; // 2^(1/12)
extern const double lbl_8042FFF8; // 2^(1/96)
extern const double lbl_80430000; // 2^(1/1536)
extern const float lbl_80430008;  // 65536.0f

void fn_802073A0(PoolEntry10C* e, int bend, float level)
{
	int amount;
	int a;
	float ratio;
	int negative;
	int semis;
	int fine;
	if (bend >= 0) {
		amount = bend * e->bendUp;
	} else {
		amount = bend * e->bendDown;
	}
	ratio    = lbl_8042FFDC;
	a        = amount;
	negative = 0;
	if (amount < 0) {
		negative = 1;
		a        = -amount;
	}
	semis = a / 0x2000;
	fine  = ((a % 0x2000) << 7) / 0x2000;
	for (; semis >= 12; semis -= 12) {
		ratio *= lbl_8042FFE8;
	}
	for (; semis > 0; semis--) {
		ratio *= lbl_8042FFF0;
	}
	for (; fine > 16; fine -= 16) {
		ratio *= lbl_8042FFF8;
	}
	for (; fine > 0; fine--) {
		ratio *= lbl_80430000;
	}
	if (negative) {
		ratio = lbl_8042FFDC / ratio;
	}
	AXSetVoiceSrcRatio(e->voice, ratio * e->baseRate / lbl_80430008 * level);
}
}
