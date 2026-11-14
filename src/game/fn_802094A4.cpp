// Applies MIDI controller `cc` with `value` to channel `ch` of an audio pool slot (see
// game/audio_system.h): bank select (0, 32), volume (7), pan (10, which also resets f24), 11, 63,
// 62 (split into f24/f20 around 0x40), sustain (64, bit 0 of f00) and reset all controllers (121).
// Other controllers are ignored.
#include "game/audio_system.h"

extern "C" {
void fn_802094A4(PoolSlot* s, unsigned char ch, unsigned char cc, unsigned char value)
{
	switch (cc) {
		case 0x00:
		case 0x20:
			s->channels[ch].f08 = value & 0x7F;
			break;
		case 0x07:
			s->channels[ch].f10 = value & 0x7F;
			break;
		case 0x0A:
			s->channels[ch].f18 = value & 0x7F;
			s->channels[ch].f24 = -1;
			break;
		case 0x0B:
			s->channels[ch].f14 = value & 0x7F;
			break;
		case 0x3F:
			s->channels[ch].f20 = value & 0x7F;
			break;
		case 0x3E: {
			unsigned char v = value & 0x7F;
			int a;
			int b;
			if (v <= 0x40) {
				a = v * 2;
				if (a > 0x7F) {
					a = 0x7F;
				}
				b = 0;
			} else {
				a = (0x7F - v) * 2;
				b = 0x7F;
			}
			s->channels[ch].f24 = a;
			s->channels[ch].f20 = b;
			break;
		}
		case 0x40:
			if ((unsigned char)(value & 0x7F) >= 0x40) {
				s->channels[ch].f00 |= 1;
			} else {
				s->channels[ch].f00 &= ~1;
			}
			break;
		case 0x79:
			ResetPoolChannel(s, ch);
			break;
	}
}
}
