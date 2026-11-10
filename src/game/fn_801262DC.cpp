// Loads the three default entries that are not loaded yet.
extern "C" {
extern char* lbl_80289DE8[];
extern char lbl_80289ED4[];
extern unsigned int lbl_803E8098[];
extern unsigned int lbl_8042C720;
unsigned int fn_800426E0(char* a, int b);

void fn_801262DC()
{
	unsigned int* p;
	char** q;
	int i;
	if (lbl_8042C720 == 0) {
		lbl_8042C720 = fn_800426E0(lbl_80289ED4, 0);
	}
	i = 0;
	p = lbl_803E8098;
	q = lbl_80289DE8;
	for (i = 0; i != 3; i++) {
		if (p[i] == 0) {
			p[i] = fn_800426E0(q[i], 0);
		}
	}
}
}
