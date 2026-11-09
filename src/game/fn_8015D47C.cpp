// Fills the object's callback table (at 0x14) with fn_8015D148, fn_8015CFDC, fn_8015CBBC and fn_8015C090; returns 1.

extern "C" {
struct Table8015D47C {
	void* f0;
	void* f4;
	void* f8;
	void* fc;
};
struct Obj8015D47C {
	unsigned char pad[0x14];
	Table8015D47C* f14;
};
void fn_8015D148();
void fn_8015CFDC();
void fn_8015CBBC();
void fn_8015C090();

int fn_8015D47C(Obj8015D47C* o)
{
	Table8015D47C* t = o->f14;
	t->f0            = (void*)fn_8015D148;
	t->f4            = (void*)fn_8015CFDC;
	t->f8            = (void*)fn_8015CBBC;
	t->fc            = (void*)fn_8015C090;
	return 1;
}
}
