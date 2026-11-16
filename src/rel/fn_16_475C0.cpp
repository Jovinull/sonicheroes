extern "C" {
void* fn_8013F484(void*);
void fn_8019EB10(void*, void* (*)(void*, void*), void*);

void* fn_16_475C0(void* arg0, void* arg1)
{
	void* r = *(void**)arg1;
	r       = fn_8013F484(arg0);
	if (r == 0) {
		fn_8019EB10(arg0, fn_16_475C0, arg1);
		return arg0;
	}
	*(void**)arg1 = r;
	return 0;
}
}
