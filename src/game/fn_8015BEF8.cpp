// Trivial accessor.

extern "C" {
extern int lbl_8042C924;

int fn_8015BEF8(int a)
{
	return *(int*)(a + lbl_8042C924);
}
}
