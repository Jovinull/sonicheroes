// Adjusts the manager's reference counter and returns the argument unchanged.
struct G8014EFC0 {
	int f0;
	int f4;
};

extern "C" {
extern G8014EFC0 lbl_8042C8C0;
int fn_8014EFC0(int a)
{
	lbl_8042C8C0.f4 = lbl_8042C8C0.f4 - 1;
	return a;
}
}
