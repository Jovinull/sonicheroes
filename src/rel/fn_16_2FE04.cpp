extern "C" void fn_16_2FDDC(void*);
extern "C" void fn_16_2FDF0(void*);
extern "C" void fn_16_2FE04(register int* p)
{
	fn_16_2FDDC(p);
	fn_16_2FDF0(p);
	p[10] = 1;
}
