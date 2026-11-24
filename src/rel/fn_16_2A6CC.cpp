class TObjSample;
extern "C" void* lbl_8042C110;
extern "C" void* __nw__10TObjSampleFUl(unsigned long);
extern "C" void* fn_16_29C2C(void*, void*);

extern "C" void fn_16_2A6CC(void)
{
	void* p = __nw__10TObjSampleFUl(0x40);
	if (p) {
		p = fn_16_29C2C(p, lbl_8042C110);
	}
}
