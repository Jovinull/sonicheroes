// Card operation step (state 2): when the card is ready and the result code is not "busy" (-1), finishes with fn_80127884 when the operation state at 0x18 is 2, else goes idle (0x1C = 2, fn_80127808); otherwise reports the error via fn_80127760.

extern "C" {
struct Card80126B68 {
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
int CARDGetResultCode(int);
int fn_801276A8(void);
void fn_80127760(Card80126B68*, int);
void fn_80127808(Card80126B68*);
void fn_80127884(Card80126B68*);

void fn_80126B68(Card80126B68* o)
{
	int r;
	if (fn_801276A8() == 0) {
		r = CARDGetResultCode(o->f4);
		if (r != -1) {
			if (r == 0) {
				if (o->f18 == 2) {
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
