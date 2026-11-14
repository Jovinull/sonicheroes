// Sets up an object for key: stores fn_80171620() at 0xAC, clears bit 0 of word 0x08, then
// requires fn_80192F38(key, 0x1A1, ...) and fn_80171D84(that, key) to succeed. Returns the
// object, or null on failure.
struct Obj801736F0 {
	unsigned char pad0[0x8];
	unsigned int f8;
	unsigned char padC[0xAC - 0xC];
	void* fAC;
};

extern "C" {
void* fn_80171620(void);
int fn_80192F38(int key, int id, int* a, int* b);
void* fn_80171D84(void* p, int key);

Obj801736F0* fn_801736F0(Obj801736F0* o, int key)
{
	int a;
	int b;
	o->fAC = fn_80171620();
	o->f8 &= ~1;
	if (fn_80192F38(key, 0x1A1, &a, &b) == 0) {
		return 0;
	}
	if (fn_80171D84(o->fAC, key) != 0) {
		return o;
	}
	return 0;
}
}
