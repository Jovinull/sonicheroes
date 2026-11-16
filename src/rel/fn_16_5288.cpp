struct TObjSample;
extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
TObjSample* fn_16_4F50(void*, int);
extern int lbl_8042C110;
void fn_16_5288(void)
{
	void* p = __nw__10TObjSampleFUl(0xE8);
	if (p != 0) {
		p = fn_16_4F50(p, lbl_8042C110);
	}
}
}
