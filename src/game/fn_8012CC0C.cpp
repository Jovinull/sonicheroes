// Copies a 2-float vector into the object at +0x1C.
struct V2_8012CC0C {
	float x;
	float y;
};
struct Obj8012CC0C {
	unsigned char pad0[0x1C];
	float f1C;
	float f20;
};

extern "C" {
void fn_8012CC0C(Obj8012CC0C* o, V2_8012CC0C* v)
{
	o->f1C = v->x;
	o->f20 = v->y;
}
}
