// Stores the two values into consecutive slots of the pool table entry.
extern "C" {
extern int lbl_8042C848;
extern int lbl_8042C9A4;
void fn_80145F0C(int a, int b)
{
	((int*)(lbl_8042C9A4 + lbl_8042C848))[1] = a;
	*(int*)(lbl_8042C9A4 + lbl_8042C848)     = b;
}
}
