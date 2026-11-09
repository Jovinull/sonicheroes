// Calls DiffAngle__Fii with fixed or forwarded arguments and returns.

extern "C" {
void DiffAngle__Fii(int, int);
struct Obj800A5998p0 {
	unsigned char pad0[0x150];
	int f150;
	unsigned char pad154[0x20];
	int f174;
};
void fn_800A5998(Obj800A5998p0* a0)
{
	DiffAngle__Fii(a0->f150, a0->f174);
}
}
