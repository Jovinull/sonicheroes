// Returns the small selector byte clamped to the 0..3 range (out-of-range values give 0).
struct Obj801185E4 {
	unsigned char pad[0xc];
	signed char bc;
};
extern "C" {
int fn_801185E4(Obj801185E4* o)
{
	int v = o->bc;
	if (v < 0) {
		v = 0;
	}
	if (v > 3) {
		v = 0;
	}
	return v;
}
}
