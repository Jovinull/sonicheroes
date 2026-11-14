// Returns the frequency ratio of a pitch offset in 1/256 semitones, computed in double precision:
// whole semitones multiply (or divide) by 2^(1/12) and the remainder by 2^(1/1536) per two units,
// rounding odd remainders away from zero.
extern "C" {
extern const double lbl_80430078; // 1.0
extern const double lbl_8042FFF0; // 2^(1/12)
extern const double lbl_80430000; // 2^(1/1536)

float fn_80208860(int pitch)
{
	double ratio = lbl_80430078;
	if (pitch > 0) {
		for (; pitch >= 0x100; pitch -= 0x100) {
			ratio *= lbl_8042FFF0;
		}
		for (; pitch > 0; pitch -= 2) {
			ratio *= lbl_80430000;
		}
	}
	if (pitch < 0) {
		for (; pitch <= -0x100; pitch += 0x100) {
			ratio /= lbl_8042FFF0;
		}
		for (; pitch < 0; pitch += 2) {
			ratio /= lbl_80430000;
		}
	}
	return ratio;
}
}
