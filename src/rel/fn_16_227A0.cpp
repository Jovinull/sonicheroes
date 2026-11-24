extern "C" void* __nw__10TObjSampleFUl(unsigned long size);
extern "C" void* fn_16_22188(void* p, void* owner);
extern "C" void* lbl_8042C110;

extern "C" void fn_16_227A0(void)
{
	void* p = __nw__10TObjSampleFUl(0xF0);
	if (p) {
		p = fn_16_22188(p, lbl_8042C110);
	}
}
