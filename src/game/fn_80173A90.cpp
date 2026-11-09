// Calls fn_80173AC0 with fixed or forwarded arguments and returns.

extern "C" {
extern unsigned char lbl_8023BC18[];
extern unsigned char lbl_8023BC28[];
void fn_80173AC0(int, int, int);
void fn_80173A90(int a0)
{
	fn_80173AC0((int)a0, (int)lbl_8023BC18, (int)lbl_8023BC28);
}
}
