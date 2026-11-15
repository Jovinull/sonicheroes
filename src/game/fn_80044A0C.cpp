extern "C" {
struct Obj80044A0C {
	unsigned char pad[0x639];
	unsigned char c639;
	short s63a;
	short s63c;
	unsigned char pad1[2];
	int f640;
	unsigned char pad2[0x6f0 - 0x644];
	short s6f0;
	short s6f2;
	short s6f4;
	short s6f6;
};
void fn_800465D8(void*, int);

void fn_80044A0C(Obj80044A0C* o)
{
	short t;

	o->s6f0 = 4;
	t       = o->s6f6;
	o->s6f6 = t & ~0x500;
	o->s63a = 0;
	o->s63c = 0;
	o->f640 = 0;
	o->c639 = 0;
	fn_800465D8(o, t);
}
}
