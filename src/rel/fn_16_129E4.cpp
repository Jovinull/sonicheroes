typedef int s32;
s32 AdjustAngle(s32, s32, s32);
extern "C" void fn_16_1431C(void*);

struct Obj {
	char pad[0xCC];
	s32 a;
	char pad2[0xFC - 0xD0];
	s32 b;
	s32 c;
};

extern "C" void fn_16_129E4(register Obj* o)
{
	s32 t1 = o->b;
	s32 t2 = o->c;
	o->b   = AdjustAngle(o->b, 0, 0x200);
	o->c   = AdjustAngle(o->c, o->a, 0x200);
	if (o->b != t1 || t2 != o->c) {
		fn_16_1431C(o);
	}
}
