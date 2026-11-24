extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
void* fn_16_2B0D8(void*, void*);
extern void* lbl_8042C110;
void fn_16_2B670(void)
{
	void* p = __nw__10TObjSampleFUl(0xFC);
	if (p != 0) {
		p = fn_16_2B0D8(p, lbl_8042C110);
	}
}
}
