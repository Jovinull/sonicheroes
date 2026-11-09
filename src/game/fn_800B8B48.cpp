// Calls fn_801527A4 with fixed or forwarded arguments and returns.

extern "C" {
void fn_800B8BA4();
void fn_801527A4(int, int, int);
struct Obj800B8B48p0 {
	unsigned char pad0[0x18];
	int f18;
};
void fn_800B8B48(Obj800B8B48p0* a0)
{
	fn_801527A4(a0->f18, (int)fn_800B8BA4, 0);
}
}
