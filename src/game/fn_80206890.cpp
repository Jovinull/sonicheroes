// Releases the voice held in the record at +4 (via fn_8020728C when +0x10 is set) and clears its first byte; no-op for null.

extern "C" {
struct Rec80206890 {
	unsigned char c0;
	unsigned char pad[0xf];
	unsigned f10;
};
struct Obj80206890 {
	void* f0;
	Rec80206890* f4;
};
void fn_8020728C(void*);

void fn_80206890(Obj80206890* o)
{
	Rec80206890* t;
	if (o != 0) {
		t = o->f4;
		if (t != 0) {
			if (t->f10 != 0) {
				fn_8020728C((unsigned char*)t + 0x10);
			}
			t->c0 = 0;
		}
	}
}
}
