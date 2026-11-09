// Calls fn_8015CA74, fn_8015CB68 and fn_8015C9D0 in turn.

extern "C" {
void fn_8015CA74();
void fn_8015CB68();
void fn_8015C9D0();

void fn_8015BF7C()
{
	fn_8015CA74();
	fn_8015CB68();
	fn_8015C9D0();
}
}
