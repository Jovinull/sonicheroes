// Byte offset selected by the five index bytes at 0x39..0x3D: a 0x38-byte header followed by
// 0x34-, 0xC-, 0x1C- and 8-byte strided records (strides measured from the retail code).
struct Obj80142E60 {
	unsigned char pad0[0x39];
	unsigned char f39;
	unsigned char f3A;
	unsigned char f3B;
	unsigned char f3C;
	unsigned char f3D;
};
extern "C" {
int fn_80142E60(Obj80142E60* o)
{
	int r = o->f3B * 0x34 + 0x38;
	r += o->f39 * 0xC;
	r += o->f3D * 0x1C;
	r += o->f3C * 8;
	r += o->f3A * 0x1C;
	return r;
}
}
