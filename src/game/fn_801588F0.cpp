// Adjusts the manager's reference counter and returns the argument unchanged.
struct G801588F0 {
	int f0;
	int f4;
};

extern "C" {
extern G801588F0 lbl_8042C908;
int fn_801588F0(int a)
{
	lbl_8042C908.f4 = lbl_8042C908.f4 + 1;
	return a;
}
}
