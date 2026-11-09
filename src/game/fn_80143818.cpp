// Calls fn_80146C2C with fixed or forwarded arguments and returns.

extern "C" {
void fn_8014332C();
void fn_80142EA0();
void fn_80142E60();
void fn_80146C2C(int, int, int, int, int);
void fn_80143818()
{
	fn_80146C2C(6, (int)fn_8014332C, (int)fn_80142EA0, (int)fn_80142E60, 0);
}
}
