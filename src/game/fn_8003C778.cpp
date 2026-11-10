// Installs the custom render callback on the atomic unless it is already set.
struct Obj8003C778 {
	unsigned char pad0[0x48];
	void* f48;
};
struct Arg8003C778 {
	int a;
	void* old;
};

extern "C" {
void fn_8003C7F0();
void fn_8014F1B0();
void RpAtomicMCCSetCustomRenderCallBack(Obj8003C778* o, Arg8003C778* p);

Obj8003C778* fn_8003C778(Obj8003C778* o, int a)
{
	Arg8003C778 s;
	s.old = o->f48;
	if (s.old == (void*)fn_8003C7F0) {
		return o;
	}
	s.a = a;
	RpAtomicMCCSetCustomRenderCallBack(o, &s);
	o->f48 = (void*)fn_8003C7F0;
	if (o->f48 == 0) {
		o->f48 = (void*)fn_8014F1B0;
	}
	return o;
}
}
