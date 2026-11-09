// Returns the word at 0x258 of the record in slot i of lbl_802AD0D0, or 0 when the slot is empty.

extern "C" {
struct Rec800924E4 {
	unsigned char pad[0x258];
	int f258;
};
extern Rec800924E4* lbl_802AD0D0[];

int fn_800924E4(int i)
{
	Rec800924E4* p = lbl_802AD0D0[i];
	if (p == 0) {
		return 0;
	}
	return p->f258;
}
}
