struct TObjSample;
extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
TObjSample* fn_16_148F8(void*, int);
extern int lbl_8042C110;
void fn_16_14D44(void)
{
	void* p = __nw__10TObjSampleFUl(0x164);
	if (p != 0) {
		p = fn_16_148F8(p, lbl_8042C110);
	}
}
}
