extern "C" {
extern void* lbl_8042C180;
int fn_16_F20(void* game, int flag);
int fn_16_2FE44(void*);
void fn_80194294(int, int*);
void fn_80194234(int, int);
void fn_8014FF2C(int);

void fn_16_30138(register char* self)
{
	int a, b, c;
	if (fn_16_F20(lbl_8042C180, 0x20) == 0 && fn_16_2FE44(self) != 0) {
		fn_80194294(10, &a);
		fn_80194294(11, &b);
		fn_80194294(20, &c);
		fn_80194234(10, 2);
		fn_80194234(11, 2);
		fn_80194234(20, 1);
		fn_8014FF2C(*(int*)(self + 0xF4));
		fn_80194234(20, c);
		fn_80194234(10, a);
		fn_80194234(11, b);
	}
}
}
