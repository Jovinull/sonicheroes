// Registers the 0x12F engine plugin and its handler set (fn_801520D0); returns whether the second registration succeeded, 0 if the first failed.

extern "C" {
extern unsigned char fn_801FD3D8[];
extern unsigned char fn_801FD49C[];
extern unsigned char fn_801FC3C8[];
extern unsigned char fn_801FC3D8[];
extern unsigned lbl_8042CF48;
extern int lbl_8042CF4C;
int RwEngineRegisterPlugin(int, int, void*, void*);
unsigned fn_801520D0(int, int, void*, void*, int);

int fn_801FC470(void)
{
	lbl_8042CF4C = RwEngineRegisterPlugin(4, 0x12f, fn_801FD3D8, fn_801FD49C);
	if (*(volatile int*)&lbl_8042CF4C >= 0) {
		lbl_8042CF48 = fn_801520D0(4, 0x12f, fn_801FC3C8, fn_801FC3D8, 0);
		return ((*(volatile unsigned*)&lbl_8042CF48) >> 31) ^ 1;
	}
	return 0;
}
}
