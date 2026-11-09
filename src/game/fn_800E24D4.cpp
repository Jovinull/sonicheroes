// Returns bit 3 of the signed byte 0xA of the 16-byte entry lbl_802B0310[player] (player = signed byte 0x760 of the object).

extern "C" {
struct Entry800E24D4 {
	unsigned char pad[0xa];
	signed char ba;
	signed char bb;
	unsigned char pad1[4];
};
struct Obj800E24D4 {
	unsigned char pad[0x760];
	signed char c760;
};
extern unsigned char lbl_802B0310[];

int fn_800E24D4(Obj800E24D4* o)
{
	return ((Entry800E24D4*)(lbl_802B0310 + o->c760 * 0x10))->ba & 8;
}
}
