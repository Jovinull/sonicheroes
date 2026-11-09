// Returns the object, or 0 when the handle at +0x24 is set but fn_80173A90 rejects it.

extern "C" {
struct Obj802048CC {
	unsigned char pad[0x24];
	unsigned f24;
};
unsigned fn_80173A90(unsigned);

Obj802048CC* fn_802048CC(Obj802048CC* o)
{
	if (o->f24 != 0 && fn_80173A90(o->f24) == 0) {
		return 0;
	}
	return o;
}
}
