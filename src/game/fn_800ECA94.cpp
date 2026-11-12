// Indexed accessor: signed bytes below 0x2C, ints at -0x88 + index*4 below 0x33.

extern "C" {
int fn_800ECA94(int* s, int i)
{
	if (i < 0)
		return -1;
	if (i < 0x2C) {
		signed char* b = (signed char*)s;
		return b[i];
	}
	if (i < 0x33)
		return s[i - 0x22];
	return -1;
}
}
