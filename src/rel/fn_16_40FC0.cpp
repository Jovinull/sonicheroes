typedef int s32;
extern "C" {
extern void* lbl_8042C180;
int fn_16_F20(void*, int);
void fn_8014FF2C(s32);
void fn_80194234(s32, s32);
void fn_80194294(s32, s32*);
void fn_16_40FC0(register char* self)
{
	s32 a, b, c;
	if (!fn_16_F20(lbl_8042C180, 0x20)) {
		fn_80194294(10, &a);
		fn_80194294(11, &b);
		fn_80194294(20, &c);
		fn_80194234(10, 2);
		fn_80194234(11, 6);
		fn_80194234(20, 1);
		fn_8014FF2C(*(s32*)(self + 0x5C));
		fn_80194234(10, a);
		fn_80194234(11, b);
		fn_8014FF2C(*(s32*)(self + 0x68));
		fn_80194234(20, c);
	}
}
}
