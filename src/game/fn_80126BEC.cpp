// Card free-blocks step: when the card is ready and fn's result code is not "busy", stores the byte/file counts (0x30/0x34) and finishes with fn_80127884 in state 6, else goes idle; errors go to fn_80127760.

extern "C" {
struct Card80126BEC {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
	int f18;
	int f1c;
	int f20;
	int f24;
	int f28;
	int f2c;
	int f30;
	int f34;
};
int CARDFreeBlocks(int, int*, int*);
int fn_801276A8(void);
void fn_80127760(Card80126BEC*, int);
void fn_80127808(Card80126BEC*);
void fn_80127884(Card80126BEC*);

void fn_80126BEC(Card80126BEC* o)
{
	int spC;
	int sp8;
	int r;
	if (fn_801276A8() == 0) {
		r = CARDFreeBlocks(o->f4, &spC, &sp8);
		if (r != -1) {
			if (r == 0) {
				o->f30 = spC;
				o->f34 = sp8;
				if (o->f18 == 6) {
					fn_80127884(o);
					return;
				}
				o->f1c = 2;
				fn_80127808(o);
				return;
			}
			fn_80127760(o, r);
		}
	}
}
}
