// Calls the callback at +0x134 of the global handler with the passthrough argument and the handler.
struct Cb8015565C {
	unsigned char pad0[0x134];
	void (*f134)(int a, Cb8015565C* self);
};

extern "C" {
extern Cb8015565C* lbl_8042C9A4;

void fn_8015565C(int a)
{
	lbl_8042C9A4->f134(a, lbl_8042C9A4);
}
}
