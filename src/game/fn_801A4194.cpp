// Dispatches to one of two handlers depending on the current table entry flag.
extern "C" {
extern int lbl_8042C9C4;
extern int lbl_8042C9A4;
void fn_801A3BD8(int a, int b);
void fn_801A3924(int a, int b);

void fn_801A4194(int a, int b)
{
	int i    = lbl_8042C9C4;
	int base = lbl_8042C9A4;
	if (((int*)(base + i))[0x1c / 4] != 0) {
		fn_801A3BD8(a, b);
	} else {
		fn_801A3924(a, b);
	}
}
}
