// When lbl_8042C61C is set, calls fn_80203998 on it and then fn_801A46D0 on the object's word 1.

extern "C" {
struct Obj801125D8 {
	int f0;
	int f4;
};
extern void* lbl_8042C61C;
void fn_80203998(void*);
void fn_801A46D0(int);

void fn_801125D8(Obj801125D8* o)
{
	if (lbl_8042C61C != 0) {
		fn_80203998(lbl_8042C61C);
		fn_801A46D0(o->f4);
	}
}
}
