// Returns the float at offset 0x1C of the object lbl_8042C9A4 points to.
struct Objfn_80194228 {
	unsigned char pad0[0x1C];
	float f1C;
};

extern "C" {
extern Objfn_80194228* lbl_8042C9A4;

float fn_80194228(void)
{
	return lbl_8042C9A4->f1C;
}
}
