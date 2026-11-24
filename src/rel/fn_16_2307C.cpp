extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
void* fn_16_22E04(void*, void*);
extern void* lbl_8042C110;
void fn_16_2307C(void)
{
	void* p = __nw__10TObjSampleFUl(0x11C);
	if (p != 0) {
		p = fn_16_22E04(p, lbl_8042C110);
	}
}
}
