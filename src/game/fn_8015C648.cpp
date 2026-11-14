// Registers plugin 0x511: the engine plugin (RwEngineRegisterPlugin with fn_8015C5E4/fn_8015C634),
// then two 4-byte extensions with fn_8015C59C/fn_8015C5A8 whose offsets are kept in lbl_8042C930
// (fn_80152FDC) and lbl_8042C934 (fn_80159F3C). Returns 1, or 0 at the first failure. The offsets
// are re-read after each store, so they are declared volatile.
extern "C" {
extern volatile int lbl_8042C930;
extern volatile int lbl_8042C934;
void* fn_8015C5E4(void* p, int a, int b);
void* fn_8015C634(void* p, int a, int b);
void* fn_8015C59C(void* p, int a, int b);
void* fn_8015C5A8(void* p, int a, int b);
int RwEngineRegisterPlugin(
    int size, unsigned int id, void* (*ctor)(void*, int, int), void* (*dtor)(void*, int, int));
int fn_80152FDC(int size, unsigned int id, void* (*ctor)(void*, int, int),
    void* (*dtor)(void*, int, int), void* copy);
int fn_80159F3C(int size, unsigned int id, void* (*ctor)(void*, int, int),
    void* (*dtor)(void*, int, int), void* copy);

int fn_8015C648(void)
{
	if (RwEngineRegisterPlugin(0, 0x511, fn_8015C5E4, fn_8015C634) < 0) {
		return 0;
	}
	lbl_8042C930 = fn_80152FDC(4, 0x511, fn_8015C59C, fn_8015C5A8, 0);
	if (lbl_8042C930 < 0) {
		return 0;
	}
	lbl_8042C934 = fn_80159F3C(4, 0x511, fn_8015C59C, fn_8015C5A8, 0);
	return lbl_8042C934 < 0 ? 0 : 1;
}
}
