// Returns the float at offset 0x18 of the object lbl_8042C9A4 points to.
struct Objfn_8019421C {
	unsigned char pad0[0x18];
	float f18;
};

extern "C" {
extern Objfn_8019421C* lbl_8042C9A4;

float fn_8019421C(void)
{
	return lbl_8042C9A4->f18;
}
}
