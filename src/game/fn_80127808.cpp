// Resets the card state: clears 0x14/0x18, unmounts and/or closes according to the bits of 0x20, clears 0x20 and enters state 2.

extern "C" {
struct Card80127808 {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
	int f18;
	int f1c;
	unsigned f20;
};
void CARDClose(int);
void CARDUnmount(int);
void fn_80127904(Card80127808*, int);

void fn_80127808(Card80127808* o)
{
	o->f14 = 0;
	o->f18 = 0;
	if ((o->f20 & 1) != 0) {
		CARDUnmount(o->f4);
	}
	if ((o->f20 & 2) != 0) {
		CARDClose(o->f0 + 0x24);
	}
	o->f20 = 0;
	fn_80127904(o, 2);
}
}
