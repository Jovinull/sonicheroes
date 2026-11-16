extern "C" {
void* __nw__10TObjSampleFUl(unsigned long);
void* fn_16_4A1EC(void*, void*);
extern void* lbl_8042C110;

void fn_16_4A4F0(void)
{
	void* p = __nw__10TObjSampleFUl(0xC4);
	if (p)
		p = fn_16_4A1EC(p, lbl_8042C110);
}
}
