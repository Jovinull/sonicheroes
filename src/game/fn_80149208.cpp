// Trivial accessor.

extern "C" {
extern int lbl_8042C85C;

int fn_80149208(int a)
{
	return *(int*)(a + lbl_8042C85C);
}
}
