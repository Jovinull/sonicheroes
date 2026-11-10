// Accessor for the indexed manager table entry.
extern "C" {
extern int lbl_8042C918;
int fn_8015B9BC(int a)
{
	return ((int*)(a + lbl_8042C918))[0xC / 4];
}
}
