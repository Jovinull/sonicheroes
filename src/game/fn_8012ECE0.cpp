// Counts down lbl_8042C768; when it reaches 0 releases the object in lbl_8042C76C (fn_800426B4) and clears lbl_8042C770.

extern "C" {
extern int lbl_8042C768;
extern void* lbl_8042C76C;
extern int lbl_8042C770;
void fn_800426B4(void*);

void fn_8012ECE0()
{
	if (lbl_8042C768 > 0) {
		lbl_8042C768 = lbl_8042C768 - 1;
		if (lbl_8042C768 == 0) {
			if (lbl_8042C76C != 0) {
				fn_800426B4(lbl_8042C76C);
				lbl_8042C76C = 0;
			}
			lbl_8042C770 = 0;
		}
	}
}
}
