// Looks up the entry for arg1 (type 0x10) and returns fn_80041B64 of the value at +0x78 of its object, or -1 when there is none.

extern "C" {
struct Obj800A2B78 {
	unsigned char pad[0x78];
	int f78;
};
struct Entry800A2B78 {
	unsigned char pad[4];
	Obj800A2B78* f4;
};
extern unsigned char lbl_8042C1A4;
void fn_80021824(void*);
Entry800A2B78* fn_80020BD8(int, int);
int fn_80041B64(int);

int fn_800A2B78(int unused, int a)
{
	Entry800A2B78* e;
	Obj800A2B78* z;
	fn_80021824(&lbl_8042C1A4);
	e = fn_80020BD8(a, 0x10);
	if (e != 0) {
		z = e->f4;
	} else {
		z = 0;
	}
	if (z != 0) {
		return fn_80041B64(z->f78);
	}
	return -1;
}
}
