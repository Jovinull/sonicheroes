// Returns 4 when the indexed slot is occupied and 0 otherwise.
extern "C" {
extern int lbl_8042C860;
int fn_80148B8C(int a)
{
	return (*(int*)(a + lbl_8042C860) == 0) ? 0 : 4;
}
}
