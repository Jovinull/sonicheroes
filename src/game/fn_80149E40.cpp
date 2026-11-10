// Adjusts the manager's reference counter and returns the argument unchanged.
struct G80149E40 {
	int f0;
	int f4;
};

extern "C" {
extern G80149E40 lbl_8042C870;
int fn_80149E40(int a)
{
	lbl_8042C870.f4 = lbl_8042C870.f4 - 1;
	return a;
}
}
