// Calls fn_801B2A14 and registers three entries (10 -> 5, 11 -> 6, 20 -> 2) with fn_80194234.

extern "C" {
void fn_801B2A14();
void fn_80194234(int, int);

void fn_800B7820()
{
	fn_801B2A14();
	fn_80194234(0xa, 5);
	fn_80194234(0xb, 6);
	fn_80194234(0x14, 2);
}
}
