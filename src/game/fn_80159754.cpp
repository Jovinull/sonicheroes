// Calls fn_8015BCF4 with the word lbl_8042C9A4 points to, the callback fn_80158A1C and the object; returns the object.

extern "C" {
extern int* lbl_8042C9A4;
void fn_8015BCF4(int, void (*)(), int);
void fn_80158A1C();

int fn_80159754(int a)
{
	fn_8015BCF4(*lbl_8042C9A4, fn_80158A1C, a);
	return a;
}
}
