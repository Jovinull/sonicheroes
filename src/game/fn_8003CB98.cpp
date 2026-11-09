// When fn_8015BD78 reports nothing for the handle at 0x8E0, runs fn_8015BB08 on it and then, if there is a handle at 0x950, on that one with the table entry chosen by the state at 0x761 (0xB uses 0x72A4).

extern "C" {
struct Tbl8003CB98 {
	unsigned char pad[0x7258];
	int f7258;
	unsigned char pad1[0x72a4 - 0x725c];
	int f72a4;
};
struct Obj8003CB98 {
	unsigned char pad[0x761];
	signed char c761;
	unsigned char pad1[0x8e0 - 0x762];
	int f8e0;
	unsigned char pad2[0x950 - 0x8e4];
	unsigned f950;
};
extern Tbl8003CB98* lbl_8042C1D0;
unsigned fn_8015BD78(int);
void fn_8015BB08(int, unsigned);

void fn_8003CB98(Obj8003CB98* o)
{
	if (fn_8015BD78(o->f8e0) == 0) {
		fn_8015BB08(lbl_8042C1D0->f7258, o->f8e0);
		if (o->f950 != 0) {
			if (o->c761 == 0xb) {
				fn_8015BB08(lbl_8042C1D0->f72a4, o->f950);
			} else {
				fn_8015BB08(lbl_8042C1D0->f7258, o->f950);
			}
		}
	}
}
}
