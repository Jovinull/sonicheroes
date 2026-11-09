// Calls fn_8019472C with fixed or forwarded arguments and returns.

extern "C" {
void fn_8019472C(int);
struct Obj8020407Cp0 {
	unsigned char pad0[0x8];
	int f8;
};
void fn_8020407C(Obj8020407Cp0* a0)
{
	fn_8019472C(a0->f8);
}
}
