// Scales value by the ratio of a pitch offset in 1/8191 semitones (octaves 2, semitones 2^(1/12),
// 1/8-semitone steps 2^(1/96), 1/128-semitone steps 2^(1/1536)), dividing for negative offsets,
// and returns it as an unsigned integer of at least 0x200; above 0x40000 it becomes 0x3FFFF.
extern "C" {
extern const float lbl_8042FFDC;  // 1.0f
extern const double lbl_8042FFE8; // 2.0
extern const double lbl_8042FFF0; // 2^(1/12)
extern const double lbl_8042FFF8; // 2^(1/96)
extern const double lbl_80430000; // 2^(1/1536)

unsigned int fn_802085AC(int offset, float value)
{
	float ratio  = lbl_8042FFDC;
	int negative = 0;
	int semis;
	int fine;
	unsigned int result;
	if (offset < 0) {
		negative = 1;
		offset   = -offset;
	}
	semis = offset / 0x1FFF;
	fine  = offset % 0x1FFF;
	fine <<= 7;
	fine /= 0x1FFE;
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
		value /= ratio;
	} else {
		value *= ratio;
	}
	result = value;
	if (result < 0x200) {
		result = 0x200;
	}
	if (result > 0x40000) {
		result = 0x3FFFF;
	}
	return result;
}
}
