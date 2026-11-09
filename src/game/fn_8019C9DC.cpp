// Runs the mode-specific update and copies the 8-byte state block.
struct Obj8019C9DC {
	unsigned char pad0[0x14];
	int f14;
};

extern "C" {
void fn_8019C1E0();
void fn_8019B9FC(Obj8019C9DC* o);
void fn_8019C86C();
void fn_8019C354(Obj8019C9DC* o);
void fn_80199E98(void* a, void* b, int c);

Obj8019C9DC* fn_8019C9DC(Obj8019C9DC* o)
{
	if (o->f14 == 1) {
		fn_8019C1E0();
		fn_8019B9FC(o);
	} else {
		fn_8019C86C();
		fn_8019C354(o);
	}
	fn_80199E98((char*)o + 0x10C, (char*)o + 0x124, 8);
	return o;
}
}
