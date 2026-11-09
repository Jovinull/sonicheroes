// Like fn_80127808 but also clears 0x1C and enters state 1.

extern "C" {
struct Card80127884 {
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
void fn_80127904(Card80127884*, int);

void fn_80127884(Card80127884* o)
{
	o->f14 = 0;
	o->f18 = 0;
	o->f1c = 0;
	if ((o->f20 & 1) != 0) {
		CARDUnmount(o->f4);
	}
	if ((o->f20 & 2) != 0) {
		CARDClose(o->f0 + 0x24);
	}
	o->f20 = 0;
	fn_80127904(o, 1);
}
}
