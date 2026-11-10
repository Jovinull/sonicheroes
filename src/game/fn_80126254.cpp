// Releases the cached handle and the three default handles.
extern "C" {
extern unsigned int lbl_803E8098[];
extern unsigned int lbl_8042C720;
extern int lbl_8042C724;
void fn_800426B4(unsigned int p);

void fn_80126254()
{
	unsigned int* p;
	int i;
	if (lbl_8042C720 != 0) {
		fn_800426B4(lbl_8042C720);
		lbl_8042C720 = 0;
	}
	p = lbl_803E8098;
	for (i = 0; i != 3; i++) {
		if (p[i] != 0) {
			fn_800426B4(p[i]);
			p[i] = 0;
		}
	}
	lbl_8042C724 = 0;
}
}
