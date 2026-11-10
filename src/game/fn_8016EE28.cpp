// Stores the value into the record at +0x394 and clears +0x39C when it exceeds the threshold lbl_8042F464; returns whether it did.
struct Glob8016EE28 {
	unsigned char pad0[0x394];
	float f394;
	unsigned char pad398[4];
	int f39C;
};

extern "C" {
extern Glob8016EE28 lbl_803EC968;
extern float lbl_8042F464;

int fn_8016EE28(float v)
{
	if (v > lbl_8042F464) {
		lbl_803EC968.f394 = v;
		lbl_803EC968.f39C = 0;
		return 1;
	}
	return 0;
}
}
