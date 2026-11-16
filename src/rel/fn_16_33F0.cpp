typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
struct B {
	char pad[0x10];
	s32 x10;
};
struct A {
	char pad[0x28];
	u16 t;
	char p2[6];
	B* b;
	s32 pad34;
	A* next;
};
extern "C" {
extern void* lbl_8042C298;
A* fn_16_33DC(void*, u8);
s32 fn_16_33F0(u8 id)
{
	A* p = fn_16_33DC(lbl_8042C298, id);
	if (p == 0)
		return 0;
	for (; p != 0; p = p->next) {
		if (p->t == 5 || p->t == 7 || p->t == 6 || p->t == 0x1104) {
			B* b = p->b;
			if (b == 0)
				return 0;
			if (b->x10 == 0)
				return 0;
		}
	}
	return 1;
}
}
