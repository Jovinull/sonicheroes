// Calls the callback stored at +0x8B0 of the record lbl_803EC968, forwarding its argument.
struct Glob8016E810 {
	unsigned char pad0[0x8B0];
	void (*f8B0)(void*);
};

extern "C" {
extern Glob8016E810 lbl_803EC968;

void fn_8016E810(void* a)
{
	lbl_803EC968.f8B0(a);
}
}
