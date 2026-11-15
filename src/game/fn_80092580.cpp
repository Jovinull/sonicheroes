struct Pad80092580 {
	unsigned char pad[0x18];
};

class Child80092580 : public Pad80092580
{
public:
	virtual void m0();
	virtual void m1();
	virtual void m2();
	virtual void m3();
	virtual void m4();
	virtual void m5();
	virtual void m6();
	virtual void m7();
	virtual void m8();
	virtual void m9();
	virtual void m10();
	virtual void m11();
	virtual void m12();
	virtual void m13();
};

struct Obj80092580 {
	unsigned char pad0[4];
	unsigned short fl;
	unsigned char pad1[0x39 - 6];
	signed char c39;
};

extern "C" {
void ClearInfo__7C_COLLIFv(void*);

void fn_80092580(struct Obj80092580* o)
{
	struct Obj80092580** p;
	int i;

	o->fl |= 8;
	o->fl |= 0x10;
	i = 0;
	p = (struct Obj80092580**)o;
	for (; i < o->c39; i++) {
		Child80092580* t = (Child80092580*)p[0x114 / 4];
		if (t != 0) {
			ClearInfo__7C_COLLIFv((unsigned char*)t + 0x28);
			t->m11();
		}
		p++;
	}
}
}
