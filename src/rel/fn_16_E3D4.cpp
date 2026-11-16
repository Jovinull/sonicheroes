struct TObjSample;
extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
TObjSample* fn_16_DEF4(void*, int);
extern int lbl_8042C110;
void fn_16_E3D4(void)
{
	void* p = __nw__10TObjSampleFUl(0x7C);
	if (p != 0) {
		p = fn_16_DEF4(p, lbl_8042C110);
	}
}
}
