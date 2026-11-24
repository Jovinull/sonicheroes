extern "C" {
void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
void* fn_16_518AC(void);

void fn_16_5191C(void* arg0, void* arg1)
{
	fn_8014FFBC(arg0, (void* (*)(void*))fn_16_518AC, arg1);
}
}
