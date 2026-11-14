// Reads a count and that many words from a stream into an object's array: the array object at 0x18
// (with a 0x10-byte helper at 0x14) is created on first use with fn_80194318, resized with
// fn_80194510 and filled with fn_80193884. Returns the object, or null on a short read or an
// allocation failure.
struct Obj80203068 {
	unsigned char pad0[0x14];
	void* f14;
	void* f18;
};

extern "C" {
unsigned int fn_80193884(void* stream, void* dst, unsigned int n);
void* fn_80194318(unsigned int size);
void* fn_80194510(void* array, int count);

Obj80203068* fn_80203068(Obj80203068* o, void* stream)
{
	int n;
	void* p;
	if (fn_80193884(stream, &n, 4) == 0) {
		return 0;
	}
	if (n > 0) {
		if (o->f18 == 0) {
			if ((o->f18 = fn_80194318(4)) != 0) {
				o->f14 = fn_80194318(0x10);
			}
		}
		if (o->f18 != 0) {
			p = fn_80194510(o->f18, n);
			if (p == 0) {
				return 0;
			}
			if (fn_80193884(stream, p, n << 2) == 0) {
				return 0;
			}
		} else {
			return 0;
		}
	}
	return o;
}
}
