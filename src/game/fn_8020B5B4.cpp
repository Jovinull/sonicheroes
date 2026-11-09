// Calls fn_8020A12C with the argument, 0x30, 0xE1000 and 0x800000, and returns 0.

extern "C" {
void fn_8020A12C(int, int, int, int);

int fn_8020B5B4(int a)
{
	fn_8020A12C(a, 0x30, 0xe1000, 0x800000);
	return 0;
}
}
