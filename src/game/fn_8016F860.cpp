// If the counter at 0x2B4 of the record at lbl_803EC968 is positive, decrements
// it and clears the two fields at 0x388 and 0x39C. Returns whether it was
// positive.

extern "C" {
struct Rec8016F860 {
	unsigned char pad[0x2b4];
	int count; // 0x2B4
	unsigned char pad2[0x388 - 0x2b8];
	int a; // 0x388
	unsigned char pad3[0x39c - 0x38c];
	int b; // 0x39C
};
extern Rec8016F860 lbl_803EC968;

int fn_8016F860()
{
	Rec8016F860* t = &lbl_803EC968;
	int n          = t->count;
	int ok         = n > 0;
	if (!ok) {
		return ok;
	}
	t->count = n - 1;
	t->a     = 0;
	t->b     = 0;
	return ok;
}
}
