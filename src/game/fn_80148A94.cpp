// Returns 0 when the indexed slot is zero and 4 otherwise.
extern "C" {
extern int lbl_8042C85C;
int fn_80148A94(int a)
{
	return (*(int*)(a + lbl_8042C85C) == 0) ? 0 : 4;
}
}
