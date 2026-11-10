// Adjusts the manager's reference counter and returns the argument unchanged.
struct G8014EFD4 {
	int f0;
	int f4;
};

extern "C" {
extern G8014EFD4 lbl_8042C8C0;
int fn_8014EFD4(int a)
{
	lbl_8042C8C0.f4 = lbl_8042C8C0.f4 + 1;
	return a;
}
}
