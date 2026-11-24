typedef unsigned char u8;
typedef unsigned int u32;
struct B {
	char pad[0x2A];
	u8 id;
};
struct A {
	char pad[0x38];
	u32 x38;
};
struct O {
	char pad[0x28];
	A* a;
};
extern "C" {
extern int lbl_8042C298;
A* fn_16_33DC(int, u8);
u8 fn_16_40C8C(O* o)
{
	A* p = fn_16_33DC(lbl_8042C298, ((B*)o->a)->id);
	u8 r = 0;
	if (p == o->a && p->x38 == 0)
		r = 1;
	return r == 0;
}
}
