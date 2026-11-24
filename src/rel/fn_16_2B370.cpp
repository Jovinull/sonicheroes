extern "C" void fn_16_2B370(int a, int b)
{
	register char* p = *(char**)(b + 0x2c);
	if (*p < 0)
		*p = 0;
	if (*p >= 3)
		*p = 2;
}
