// Calls fn_8019469C with fixed or forwarded arguments and returns.

extern "C" {
void fn_8019469C(int);
struct Obj8020128Cp0 {
	int f0;
};
void fn_8020128C(Obj8020128Cp0* a0)
{
	fn_8019469C(a0->f0);
}
}
