extern "C" {
extern unsigned char lbl_8042C1A4[];
void fn_80021824(void*);
unsigned fn_16_DC8(void*, int);
int fn_16_45EF0(register char* self)
{
	if (*(char**)(self + 0x40) == 0) {
		return 0;
	}
	fn_80021824(lbl_8042C1A4);
	if (fn_16_DC8(self + 0x30, 0x13) != 0) {
		**(char**)(self + 0x40) = 0;
		return 1;
	}
	**(char**)(self + 0x40) = 0x1D;
	return 0;
}
}
