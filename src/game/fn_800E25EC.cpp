// Returns bit mask 0x1 of the signed byte 0x9 of the 16-byte entry lbl_802B0310[player] (player = signed byte 0x760 of the object).

extern "C" {
struct Entry800E25EC {
	unsigned char pad[0x9];
	signed char v;
};
struct Obj800E25EC {
	unsigned char pad[0x760];
	signed char c760;
};
extern unsigned char lbl_802B0310[];

int fn_800E25EC(Obj800E25EC* o)
{
	return ((Entry800E25EC*)(lbl_802B0310 + o->c760 * 0x10))->v & 1;
}
}
