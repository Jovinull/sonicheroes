// Adjusts the manager's reference counter and returns the argument unchanged.
struct G80158904 {
	int f0;
	int f4;
};

extern "C" {
extern G80158904 lbl_8042C908;
int fn_80158904(int a)
{
	lbl_8042C908.f4 = lbl_8042C908.f4 - 1;
	return a;
}
}
