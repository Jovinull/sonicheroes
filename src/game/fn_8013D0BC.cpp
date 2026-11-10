// Clears the three words of the entry at the given offset and returns the offset.
struct T3 {
	int a;
	int b;
	int c;
};
extern "C" {
extern int lbl_8042C820;
int fn_8013D0BC(int a)
{
	T3* t = (T3*)(a + lbl_8042C820);
	t->a  = 0;
	t->b  = 0;
	t->c  = 0;
	return a;
}
}
