// Fills object b of owner a, unless either is null: with data c, allocates n bytes from a
// (fn_8017CDA4, after fn_8017C024 with flag 0x2000), records them in b and a, copies c there and
// sets b's flag 0x2000; with d, copies its 0x0A bytes to b + 0x50 (n becomes at least 1). Then
// stores n at 0x16 and sets flag 0x10 of word 0x08. Field names are not known.
struct A80190DD8 {
	unsigned char pad0[0x148];
	void* f148;
};

struct B80190DD8 {
	unsigned char pad0[0x8];
	unsigned int f8;
	unsigned char padC[0xA];
	short f16;
	unsigned char pad18[0x34];
	void* f4C;
	unsigned char pad50[0x68];
	unsigned int fB8;
};

extern "C" {
void fn_8017C024(A80190DD8* a, B80190DD8* b, int c, int d);
void* fn_8017CDA4(A80190DD8* a, int n);
void* memcpy(void* d, const void* s, unsigned int n);

void fn_80190DD8(A80190DD8* a, B80190DD8* b, void* c, int n, void* d)
{
	if (a == 0 || b == 0) {
		return;
	}
	if (c != 0) {
		void* t;
		fn_8017C024(a, b, 0x2000, 0);
		t       = fn_8017CDA4(a, n);
		b->f4C  = t;
		a->f148 = t;
		memcpy(b->f4C, c, n);
		b->fB8 = b->fB8 | 0x2000;
	}
	if (d != 0) {
		memcpy((char*)b + 0x50, d, 0xA);
		if (n == 0) {
			n = 1;
		}
	}
	b->f16 = n;
	b->f8  = b->f8 | 0x10;
}
}
