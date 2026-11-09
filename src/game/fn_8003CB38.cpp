// For each of the two handles at 0x8E0 and 0x950 (the second only if set), looks the handle up with fn_8015BD78 and, if found, passes the result and the handle to fn_8015BBF8.

extern "C" {
struct Obj8003CB38 {
	unsigned char pad[0x8e0];
	unsigned f8e0;
	unsigned char pad1[0x950 - 0x8e4];
	unsigned f950;
};
unsigned fn_8015BD78(unsigned);
void fn_8015BBF8(unsigned, unsigned);

void fn_8003CB38(Obj8003CB38* o)
{
	unsigned t = fn_8015BD78(o->f8e0);
	if (t != 0) {
		fn_8015BBF8(t, o->f8e0);
	}
	if (o->f950 != 0) {
		t = fn_8015BD78(o->f950);
		if (t != 0) {
			fn_8015BBF8(t, o->f950);
		}
	}
}
}
