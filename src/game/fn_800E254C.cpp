// Returns bit mask 0x4 of the signed byte 0xc of the 16-byte entry lbl_802B0310[player] (player = signed byte 0x760 of the object).

extern "C" {
struct Entry800E254C {
	unsigned char pad[0xc];
	signed char v;
};
struct Obj800E254C {
	unsigned char pad[0x760];
	signed char c760;
};
extern unsigned char lbl_802B0310[];

int fn_800E254C(Obj800E254C* o)
{
	return ((Entry800E254C*)(lbl_802B0310 + o->c760 * 0x10))->v & 4;
}
}
