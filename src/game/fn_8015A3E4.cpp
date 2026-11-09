// Saves the object's three callbacks (+0x18, +0x1C, +0x10) into the record at lbl_8042C918 and installs fn_8015A340 / fn_8015A2B8 / fn_8015A304 in their place.

extern "C" {
struct Saved8015A3E4 {
	int f0;
	int f4;
	int f8;
	int fc;
	void* f10;
	void* f14;
	void* f18;
};
struct Obj8015A3E4 {
	unsigned char pad[0x10];
	void* f10;
	unsigned char pad1[4];
	void* f18;
	void* f1c;
};
extern int lbl_8042C918;
extern unsigned char fn_8015A340[];
extern unsigned char fn_8015A2B8[];
extern unsigned char fn_8015A304[];

void fn_8015A3E4(Obj8015A3E4* o)
{
	Saved8015A3E4* c = (Saved8015A3E4*)((unsigned char*)o + lbl_8042C918);
	c->f0            = 0;
	c->f4            = 0;
	c->f8            = 0;
	c->f10           = o->f18;
	c->f14           = o->f1c;
	c->f18           = o->f10;
	o->f10           = fn_8015A340;
	o->f18           = fn_8015A2B8;
	o->f1c           = fn_8015A304;
	c->fc            = 0;
}
}
