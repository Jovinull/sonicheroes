// Returns the minutes part of the frame counter at 0x14 (3600 frames per minute), clamped to 0-99.

extern "C" {
struct Obj80118674 {
	unsigned char pad[0x14];
	int f14;
};

int fn_80118674(Obj80118674* o)
{
	int v = o->f14 / 3600;
	if (v < 0) {
		v = 0;
	}
	if (v > 0x63) {
		return 0x63;
	}
	return v;
}
}
