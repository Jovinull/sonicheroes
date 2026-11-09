// Returns the address +0x18 of the object in table lbl_802AD090 selected by arg1 (looked up with fn_800A5844 when -1); 0 when none is found.

extern "C" {
int fn_800A5844(void);
extern int* lbl_802AD090[];

int fn_800A57F0(int unused, int k)
{
	if (k == -1) {
		k = fn_800A5844();
		if (k == -1) {
			if (k == -1) {
				return 0;
			}
		}
	}
	return (int)lbl_802AD090[k] + 0x18;
}
}
