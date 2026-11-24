extern "C" {
void* fn_16_939C0(void);
int fn_16_93940(void*);

int fn_16_4CC40(void)
{
	if (fn_16_939C0() != 0) {
		return fn_16_93940(fn_16_939C0());
	}
	return 1;
}
}
