// Returns 0 when any of flag bits 0xC002 is set in the word at 0x18, otherwise whether bit 19 is set.

extern "C" {
struct Obj8007DC44 {
	unsigned char pad[0x18];
	unsigned f18;
};

int fn_8007DC44(Obj8007DC44* o)
{
	unsigned t = o->f18;
	if ((t & 0xC002) != 0) {
		return 0;
	}
	return (t & 0x80000) != 0;
}
}
