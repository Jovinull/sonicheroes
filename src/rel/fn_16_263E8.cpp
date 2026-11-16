class TObjSample;
extern "C" void* __nw__10TObjSampleFUl(unsigned long);
extern "C" {
extern int lbl_8042C110;
void* fn_16_26040(void*, int);
void fn_16_263E8(void)
{
	void* p = __nw__10TObjSampleFUl(0x110);
	if (p) {
		p = fn_16_26040(p, lbl_8042C110);
	}
}
}
