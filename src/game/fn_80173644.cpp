// Calls fn_80170FDC with fixed or forwarded arguments and returns.

extern "C" {
void fn_80170FDC(int);
struct Obj80173644p0 {
	unsigned char pad0[0xac];
	int fac;
};
void fn_80173644(Obj80173644p0* a0)
{
	fn_80170FDC(a0->fac);
}
}
