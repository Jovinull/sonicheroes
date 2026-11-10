// Calls the callback at +0xFC of the global handler with (a + 8, passthrough, 0x1F, handler) and returns a.
struct Cb801478CC {
	unsigned char pad0[0xFC];
	void (*fFC)(int a, int b, int c, Cb801478CC* self);
};

extern "C" {
extern Cb801478CC* lbl_8042C9A4;

int fn_801478CC(int a, int b)
{
	lbl_8042C9A4->fFC(a + 8, b, 0x1F, lbl_8042C9A4);
	return a;
}
}
