// Adjusts the manager's reference counter and returns the argument unchanged.
struct G80152274 {
	int f0;
	int f4;
};

extern "C" {
extern G80152274 lbl_8042C8E0;
int fn_80152274(int a)
{
	lbl_8042C8E0.f4 = lbl_8042C8E0.f4 - 1;
	return a;
}
}
