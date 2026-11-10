// Clears one field and sets the other to -1 in the entry at the given offset; returns the offset.
struct T2 {
	int a;
	int b;
};
extern "C" {
extern int lbl_8042C828;
int fn_8013E6D8(int a)
{
	T2* t = (T2*)(a + lbl_8042C828);
	t->b  = 0;
	t->a  = -1;
	return a;
}
}
