// Copies the position vector of the current node (own or selected from the owner's entries) into the object and sets its float at +0x28.
struct Rec8003CA34 {
	unsigned char pad0[0x30];
	float f30;
	float f34;
	float f38;
};
struct Ent8003CA34 {
	unsigned char pad0[0xC];
	Rec8003CA34* fC;
};
struct Obj8003CA34 {
	unsigned char pad0[4];
	Rec8003CA34* f4;
	unsigned char pad8[0x10];
	int f18;
	float f1C;
	float f20;
	float f24;
	float f28;
	unsigned char pad2C[0x20];
	int f4C;
};
struct Own8003CA34 {
	unsigned char pad0[0x10];
	Ent8003CA34* f10;
};

extern "C" {
extern int lbl_8042AF04;
extern float lbl_8042D0E4;
void fn_8014F854();
unsigned int fn_80226468(int a);

Obj8003CA34* fn_8003CA34(Obj8003CA34* o, Own8003CA34* w)
{
	Rec8003CA34* r;
	if ((o->f4C & 2) != 0) {
		fn_8014F854();
	}
	if (fn_80226468(o->f18) != 0) {
		r = (Rec8003CA34*)((unsigned char*)w->f10[lbl_8042AF04].fC + 0x10);
	} else {
		r = (Rec8003CA34*)((unsigned char*)o->f4 + 0x10);
	}
	o->f1C = r->f30;
	o->f20 = r->f34;
	o->f24 = r->f38;
	o->f28 = lbl_8042D0E4;
	return o;
}
}
