class TObjSample;
extern "C" void* lbl_8042C110;
extern "C" void* __nw__10TObjSampleFUl(unsigned long);
extern "C" void* fn_16_32D34(void*, void*);

extern "C" void fn_16_32F10(void)
{
	void* p = __nw__10TObjSampleFUl(0x40);
	if (p) {
		p = fn_16_32D34(p, lbl_8042C110);
	}
}
