// Sets the audio system's defaults (see game/audio_system.h): the sixteen default region sizes,
// the high-quality reverb parameters, the word at 0x13A44 and the byte at 0x13A38.
#include "game/audio_system.h"

extern "C" {
extern const float lbl_8042FFB0; // 1.0f
extern const float lbl_8042FFB4; // 0.01f
extern const float lbl_8042FFB8; // 0.8f
extern const float lbl_8042FFBC; // 0.5f
extern const float lbl_8042FFC0; // 0.3f
extern const float lbl_8042FFC4; // 1.004184f

void fn_802061B4(void)
{
	lbl_8042CF6C->regionDefaults[0]   = 900000;
	lbl_8042CF6C->regionDefaults[1]   = 2100000;
	lbl_8042CF6C->regionDefaults[2]   = 1100000;
	lbl_8042CF6C->regionDefaults[3]   = 1000000;
	lbl_8042CF6C->regionDefaults[4]   = 1000000;
	lbl_8042CF6C->regionDefaults[5]   = 1200000;
	lbl_8042CF6C->regionDefaults[6]   = 0x200;
	lbl_8042CF6C->regionDefaults[7]   = 0x200;
	lbl_8042CF6C->regionDefaults[8]   = 0x200;
	lbl_8042CF6C->regionDefaults[9]   = 0x200;
	lbl_8042CF6C->regionDefaults[10]  = 0x200;
	lbl_8042CF6C->regionDefaults[11]  = 0x200;
	lbl_8042CF6C->regionDefaults[12]  = 0x200;
	lbl_8042CF6C->regionDefaults[13]  = 0x200;
	lbl_8042CF6C->regionDefaults[14]  = 0x200;
	lbl_8042CF6C->regionDefaults[15]  = 0x200;
	lbl_8042CF6C->reverbHi.time       = lbl_8042FFB0;
	lbl_8042CF6C->reverbHi.preDelay   = lbl_8042FFB4;
	lbl_8042CF6C->reverbHi.damping    = lbl_8042FFB8;
	lbl_8042CF6C->reverbHi.coloration = lbl_8042FFBC;
	lbl_8042CF6C->reverbHi.crosstalk  = lbl_8042FFC0;
	lbl_8042CF6C->reverbHi.mix        = lbl_8042FFB0;
	lbl_8042CF6C->f13A44              = lbl_8042FFC4;
	lbl_8042CF6C->f13A38              = 0;
}
}
