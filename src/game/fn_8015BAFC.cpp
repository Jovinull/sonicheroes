// Trivial accessor.

extern "C" {
extern int lbl_8042C91C;

int fn_8015BAFC(int a)
{
	return *(int*)(a + lbl_8042C91C);
}
}
