// Adjusts the manager's reference counter and returns the argument unchanged.
struct G80193FD4 {
	int f0;
	int f4;
};

extern "C" {
extern G80193FD4 lbl_8042C950;
int fn_80193FD4(int a)
{
	lbl_8042C950.f4 = lbl_8042C950.f4 - 1;
	return a;
}
}
