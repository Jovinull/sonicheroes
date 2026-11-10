// Decrements the global reference counter and returns the argument.
struct C2 {
	int a;
	int f4;
};
extern "C" {
extern C2 lbl_8042BCD0;
int fn_8013D778(int a)
{
	lbl_8042BCD0.f4 = lbl_8042BCD0.f4 - 1;
	return a;
}
}
