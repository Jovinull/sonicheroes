// Enables or disables the slot's 2-float parameter and returns its address.
struct Slot8004D4D4 {
	unsigned char pad0[0x2310];
	int f2310;
	float f2314;
	float f2318;
	unsigned char pad231C[8];
};
struct V2_8004D4D4 {
	float x;
	float y;
};

extern "C" {
extern Slot8004D4D4 lbl_802B908C[];

float* fn_8004D4D4(int unused, int i, V2_8004D4D4* v)
{
	if (v != 0) {
		lbl_802B908C[i].f2310 = 1;
		lbl_802B908C[i].f2314 = v->x;
		lbl_802B908C[i].f2318 = v->y;
	} else {
		lbl_802B908C[i].f2310 = 0;
	}
	return &lbl_802B908C[i].f2314;
}
}
