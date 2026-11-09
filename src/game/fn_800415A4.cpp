// Returns 1 when either the type-4 or the type-6 entry of the table at +0x28 has a non-zero value at +4, else 0.

extern "C" {
struct Entry800415A4 {
	unsigned char pad[4];
	unsigned f4;
};
Entry800415A4* fn_80020BD8(int, int);
void fn_80021824(int);

int fn_800415A4(int a)
{
	Entry800415A4* t;
	unsigned r;
	fn_80021824(a + 0x28);
	t = fn_80020BD8(a + 0x28, 4);
	if (t != 0) {
		r = t->f4;
	} else {
		r = 0;
	}
	if (r != 0) {
		return 1;
	}
	t = fn_80020BD8(a + 0x28, 6);
	if (t != 0) {
		r = t->f4;
	} else {
		r = 0;
	}
	if (r != 0) {
		return 1;
	}
	return 0;
}
}
