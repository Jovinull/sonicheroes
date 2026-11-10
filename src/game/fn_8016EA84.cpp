// Calls the callback stored at +0x408 of the record lbl_803EC968, forwarding its argument.
struct Glob8016EA84 {
	unsigned char pad0[0x408];
	void (*f408)(void*);
};

extern "C" {
extern Glob8016EA84 lbl_803EC968;

void fn_8016EA84(void* a)
{
	lbl_803EC968.f408(a);
}
}
