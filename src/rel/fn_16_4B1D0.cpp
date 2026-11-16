typedef signed int s32;

extern "C" {
s32 fn_16_5A29C(void);
void fn_16_87270(void*, void*);
void fn_16_87D24(void*);

void fn_16_4B1D0(register char* self)
{
	if (*(s32*)(self + 0xE4) == 0 && fn_16_5A29C() == 0) {
		fn_16_87270(self + 0x10C, self + 0xE0);
		fn_16_87D24(self + 0x10C);
	}
}
}
