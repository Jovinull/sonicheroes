// Returns 4 for a null object, otherwise 0x10 plus the result of fn_8019AA5C on it.

extern "C" {
int fn_8019AA5C(void*);

int fn_80147F64(void* a)
{
	int r = 4;
	if (a != 0) {
		r = fn_8019AA5C(a) + 0x10;
	}
	return r;
}
}
