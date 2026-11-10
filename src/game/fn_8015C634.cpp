// Adjusts the manager's reference counter and returns the argument unchanged.
struct G8015C634 {
	int f0;
	int f4;
};

extern "C" {
extern G8015C634 lbl_8042C938;
int fn_8015C634(int a)
{
	lbl_8042C938.f4 = lbl_8042C938.f4 - 1;
	return a;
}
}
