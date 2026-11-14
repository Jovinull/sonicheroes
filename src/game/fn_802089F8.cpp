// Returns 90316.8 scaled by a note distance, computed in double precision: each octave of key
// above base halves it and each remaining semitone divides it by 2^(1/12); below base, octaves
// double it and semitones multiply by 2^(1/12). The fine tune (1/128 semitone units; a negative
// value moves key up by one and adds 0x80, as in retail) then multiplies by 2^(1/96) per 16 units
// and by 2^(1/1536) per remaining unit.
extern "C" {
extern const double lbl_80430080; // 90316.8
extern const double lbl_80430088; // 0.5
extern const double lbl_8042FFE8; // 2.0
extern const double lbl_8042FFF0; // 2^(1/12)
extern const double lbl_8042FFF8; // 2^(1/96)
extern const double lbl_80430000; // 2^(1/1536)

float fn_802089F8(int key, int fine, int base)
{
	double rate = lbl_80430080;
	if (fine < 0) {
		key += 1;
		fine += 0x80;
	}
	key -= base;
	if (key >= 0) {
		for (; key >= 12; key -= 12) {
			rate *= lbl_80430088;
		}
		for (; key > 0; key--) {
			rate /= lbl_8042FFF0;
		}
	} else {
		key = -key;
		for (; key >= 12; key -= 12) {
			rate *= lbl_8042FFE8;
		}
		for (; key > 0; key--) {
			rate *= lbl_8042FFF0;
		}
	}
	for (; fine > 16; fine -= 16) {
		rate *= lbl_8042FFF8;
	}
	for (; fine > 0; fine--) {
		rate *= lbl_80430000;
	}
	return rate;
}
}
