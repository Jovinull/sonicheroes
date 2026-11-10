// Accessor for the indexed manager table entry.
extern "C" {
extern int lbl_8042C940;
void fn_8015DE98(int a)
{
	*(int*)(a + lbl_8042C940) = 0;
}
}
