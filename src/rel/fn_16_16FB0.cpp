typedef int s32;
struct Obj {
	char pad[8];
	s32 state;
	char pad2[0x10];
	s32 v;
};
extern "C" s32 fn_16_167F4(Obj*);
extern "C" void fn_16_1704C(Obj*);
extern "C" s32 fn_16_16FB0(register Obj* o)
{
	s32 r = -1;
	switch (o->state) {
		case 1:
			r = fn_16_167F4(o);
			break;
		case 2:
			o->v = o->v - 0x400;
			fn_16_1704C(o);
			break;
		case 3:
			o->v = o->v - 0x400;
			fn_16_1704C(o);
			break;
	}
	return r;
}
