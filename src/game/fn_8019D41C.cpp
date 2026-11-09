// Calls fn_80198A60 with fixed or forwarded arguments and returns.

extern "C" {
extern unsigned char lbl_802904E0[];
void fn_80198A60(int, int);
void fn_8019D41C(int a0)
{
	fn_80198A60((int)lbl_802904E0, (int)a0);
}
}
