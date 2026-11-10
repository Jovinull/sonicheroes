// Adjusts the manager's reference counter and returns the argument unchanged.
struct G80193F84 {
	int f0;
	int f4;
};

extern "C" {
extern G80193F84 lbl_8042C948;
int fn_80193F84(int a)
{
	lbl_8042C948.f4 = lbl_8042C948.f4 - 1;
	return a;
}
}
