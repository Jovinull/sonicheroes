// Looks up the entry (fn_8004E408 with type 0x11) in lbl_8042C1F8 for the first argument and stores the second argument at its word 5.

extern "C" {
extern int lbl_8042C1F8;
int* fn_8004E408(int, int, int);

void fn_80131088(int a, int b)
{
	int* p = fn_8004E408(lbl_8042C1F8, a, 0x11);
	p[5]   = b;
}
}
