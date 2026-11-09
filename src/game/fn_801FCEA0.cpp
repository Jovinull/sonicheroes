// Forwards (arg0, fn_801FCCE0(arg1), arg2, lbl_80298DE8) to fn_801FCEF4.

extern "C" {
int fn_801FCCE0(int);
void fn_801FCEF4(int, int, int, void*);
extern unsigned char lbl_80298DE8[];

void fn_801FCEA0(int a, int b, int c)
{
	fn_801FCEF4(a, fn_801FCCE0(b), c, lbl_80298DE8);
}
}
