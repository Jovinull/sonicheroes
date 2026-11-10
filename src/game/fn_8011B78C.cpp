// Calls the object's handler callback (+0x3C) with the argument, its sub-block (+0x4C) and itself; returns 1.
struct Hdl8011B78C;
struct Hdl8011B78C {
	unsigned char pad0[0x3C];
	void (*f3C)(int, void*, Hdl8011B78C*);
};
struct Obj8011B78C {
	unsigned char pad0[4];
	Hdl8011B78C* f4;
};

extern "C" {
int fn_8011B78C(Obj8011B78C* o, int a)
{
	if (o != 0) {
		Hdl8011B78C* h = o->f4;
		h->f3C(a, (char*)h + 0x4C, h);
	}
	return 1;
}
}
