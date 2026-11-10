// Runs every registered callback of the hook list lbl_8042C1C4.
struct Hook800422C4 {
	unsigned char pad0[4];
	void (*f4)();
	Hook800422C4* f8;
};

extern "C" {
extern Hook800422C4* lbl_8042C1C4;

void fn_800422C4()
{
	Hook800422C4* h;
	for (h = lbl_8042C1C4; h != 0; h = h->f8) {
		if (h->f4 != 0) {
			h->f4();
		}
	}
}
}
