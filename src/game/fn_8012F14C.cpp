// Pushes stored values to the backend, one id at a time.
struct Obj8012F14C {
	unsigned char pad0[0x228C];
	int f228C;
	int f2290;
	int f2294;
	int f2298;
	int f229C;
	int f22A0;
	int f22A4;
	int f22A8;
};

extern "C" {
void fn_80194234(int a, int b);

void fn_8012F14C(Obj8012F14C* o)
{
	fn_80194234(6, o->f228C);
	fn_80194234(8, o->f2290);
	fn_80194234(0xC, o->f2294);
	fn_80194234(0xA, o->f2298);
	fn_80194234(0xB, o->f229C);
	fn_80194234(9, o->f22A0);
	fn_80194234(0x14, o->f22A4);
	fn_80194234(1, 0);
	fn_80194234(0xE, o->f22A8);
	fn_80194234(0xA, o->f2298);
	fn_80194234(0xB, o->f229C);
}
}
