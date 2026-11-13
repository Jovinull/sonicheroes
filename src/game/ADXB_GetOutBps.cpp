// Output bits per sample from the format (+0x98) and bit width (+0x9A): 4, 8 or 16.

extern "C" {
struct ObjADXB_GetOutBps {
	unsigned char pad[0x98];
	short s98;
	short s9a;
};

int ADXB_GetOutBps(ObjADXB_GetOutBps* o)
{
	short t = o->s98;
	if (t == 0) {
		return 0x10;
	}
	if (t == 2) {
		short w = o->s9a;
		if (w == 2) {
			return 4;
		}
		return w == 1 ? 8 : 0x10;
	}
	if (t == 1) {
		return o->s9a == 2 ? 4 : 0x10;
	}
	return 0x10;
}
}
