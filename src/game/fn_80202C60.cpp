// Calls fn_8019472C with fixed or forwarded arguments and returns.

extern "C" {
void fn_8019472C(int);
struct Obj80202C60p0 {
	unsigned char pad0[0x10];
	int f10;
};
void fn_80202C60(Obj80202C60p0* a0)
{
	fn_8019472C(a0->f10);
}
}
