// Returns bit mask 0x4 of the signed byte 0xd of the 16-byte entry lbl_802B0310[player] (player = signed byte 0x760 of the object).

extern "C" {
struct Entry800E2524 {
	unsigned char pad[0xd];
	signed char v;
};
struct Obj800E2524 {
	unsigned char pad[0x760];
	signed char c760;
};
extern unsigned char lbl_802B0310[];

int fn_800E2524(Obj800E2524* o)
{
	return ((Entry800E2524*)(lbl_802B0310 + o->c760 * 0x10))->v & 4;
}
}
