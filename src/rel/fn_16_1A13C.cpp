extern "C" {
extern int lbl_80303DC8[];
int fn_16_1E1C(int);
void fn_16_2E9F0(int, int, int, int);
void fn_16_74B8(void*);
void fn_16_1A13C(register char* self)
{
	int v;
	if (((signed char*)self)[0xBD] != -1) {
		switch (*(int*)(self + 0xC0)) {
			case 2:
				v = 5;
				break;
			case 1:
				v = 7;
				break;
			case 0:
			default:
				v = 1;
				break;
		}
		fn_16_2E9F0(
		    ((signed char*)self)[0xBD], fn_16_1E1C(lbl_80303DC8[((signed char*)self)[0xBD]]), v, 0);
		fn_16_74B8(self + 0x28);
	}
}
}
