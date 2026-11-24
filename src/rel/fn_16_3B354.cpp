extern "C" {
void* fn_80020ABC(void* a, int b);
void fn_16_D4C(void* a, void* b);
void fn_16_3B354(void* a, int b);
}
void fn_16_3B354(void* a, int b)
{
	fn_16_D4C(a, fn_80020ABC(a, b));
}
