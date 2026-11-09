// Releases the buffer at 0x10 of the record in slot i of lbl_802AD280 (fn_800126C8) and clears it, if set; returns 1.

extern "C" {
struct Rec800F2ECC {
	unsigned char pad[0x10];
	unsigned f10;
};
struct Slot800F2ECC {
	int a;
	int b;
	Rec800F2ECC* r;
	int d;
};
extern Slot800F2ECC lbl_802AD280[];
void fn_800126C8(unsigned);

int fn_800F2ECC(int i)
{
	Rec800F2ECC* r = lbl_802AD280[i].r;
	if (r != 0 && r->f10 != 0) {
		fn_800126C8(r->f10);
		r->f10 = 0;
	}
	return 1;
}
}
