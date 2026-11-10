// Calls the object's callback at +0x12C with the object itself.
struct Obj8016E840 {
	unsigned char pad0[0x12C];
	void (*f12C)(Obj8016E840*);
};

extern "C" {
void fn_8016E840(Obj8016E840* o)
{
	o->f12C(o);
}
}
