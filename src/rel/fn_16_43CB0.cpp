extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
void* fn_16_43AF8(void*, void*);
extern void* lbl_8042C110;

void fn_16_43CB0(void)
{
	void* p = __nw__10TObjSampleFUl(0xF8);
	if (p) {
		p = fn_16_43AF8(p, lbl_8042C110);
	}
}
}
