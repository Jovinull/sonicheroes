// Returns the address of entry k (16 bytes each) of the table whose handle is *arg0; 0 when the handle is unset.

extern "C" {
int fn_8019460C(unsigned);

int fn_8020530C(unsigned* o, int k)
{
	if (*o == 0) {
		return 0;
	}
	{
		int r = fn_8019460C(*o);
		r += k << 4;
		return r;
	}
}
}
