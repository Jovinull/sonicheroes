// Counts the consecutive non-empty entries from the given index and runs the handler on them.
struct Obj80203144 {
	unsigned char pad0[0x14];
	int f14;
	int f18;
	unsigned char pad1C[4];
	int f20;
	unsigned char pad24[0x20];
	int f44;
};

extern "C" {
int* fn_8019460C(int a);
unsigned int* fn_8019472C(int a, int b);
unsigned int fn_8020366C(Obj80203144* o, int a, unsigned int* p, int n, int b);

Obj80203144* fn_80203144(Obj80203144* o, int idx)
{
	int a;
	unsigned int* first;
	int b;
	unsigned int* p;
	int n;
	a     = fn_8019460C(o->f18)[idx];
	first = fn_8019472C(o->f14, a);
	p     = first;
	b     = a + 1;
	n     = 0;
	while (*p != 0) {
		n++;
		p = fn_8019472C(o->f14, b);
		b++;
	}
	if (n > 0 && fn_8020366C(o, o->f20, first, n, o->f44) == 0) {
		return 0;
	}
	return o;
}
}
