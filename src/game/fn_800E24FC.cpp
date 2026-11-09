// Returns bit 2 of the signed byte 0xB of the 16-byte entry lbl_802B0310[player] (player = signed byte 0x760 of the object).

extern "C" {
struct Entry800E24FC {
	unsigned char pad[0xa];
	signed char ba;
	signed char bb;
	unsigned char pad1[4];
};
struct Obj800E24FC {
	unsigned char pad[0x760];
	signed char c760;
};
extern unsigned char lbl_802B0310[];

int fn_800E24FC(Obj800E24FC* o)
{
	return ((Entry800E24FC*)(lbl_802B0310 + o->c760 * 0x10))->bb & 4;
}
}
