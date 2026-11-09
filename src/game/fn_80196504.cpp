// Trivial accessor.

extern "C" {
extern int lbl_8042BDF0;

void fn_80196504(int a)
{
	lbl_8042BDF0 = a;
}
}
