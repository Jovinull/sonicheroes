// Sets the global gauge value and clears the counter when the value exceeds lbl_8042F464; returns whether it was accepted.
struct Glob8016EE58 {
	unsigned char pad0[0x388];
	int f388;
	unsigned char pad38C[4];
	float f390;
};

extern "C" {
extern Glob8016EE58 lbl_803EC968;
extern float lbl_8042F464;

int fn_8016EE58(float v)
{
	if (v > lbl_8042F464) {
		lbl_803EC968.f390 = v;
		lbl_803EC968.f388 = 0;
		return 1;
	}
	return 0;
}
}
