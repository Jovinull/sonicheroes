// Bumps the global counter, runs the no-argument follow-up fn_80146C58 and returns the argument.
struct Cnt80145F94 {
	int f0;
	int f4;
};

extern "C" {
extern Cnt80145F94 lbl_8042BCE0;
void fn_80146C58();

int fn_80145F94(int o)
{
	lbl_8042BCE0.f4 = lbl_8042BCE0.f4 + 1;
	fn_80146C58();
	return o;
}
}
