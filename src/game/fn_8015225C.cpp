// Adjusts the manager's reference counter and returns the argument unchanged.
struct G8015225C {
	int f0;
	int f4;
};

extern "C" {
extern G8015225C lbl_8042C8E0;
int fn_8015225C(int a, int b)
{
	lbl_8042C8E0.f0 = b;
	lbl_8042C8E0.f4 = lbl_8042C8E0.f4 + 1;
	return a;
}
}
