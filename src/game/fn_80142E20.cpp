// Trivial accessor.

extern "C" {
extern int lbl_8042C834;
struct S4 {
	unsigned char pad[0x6c];
	int f6c;
	unsigned char pad1[0x84 - 0x70];
	int f84;
};

void fn_80142E20(S4* o)
{
	o->f6c = lbl_8042C834;
}
}
