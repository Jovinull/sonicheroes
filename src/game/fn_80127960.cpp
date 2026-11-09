// Advances the card operation: when not yet busy, checks fn_80127A78 and (if set) marks busy; runs fn_801279C8 with the state at 0xC; returns the result field at 0x14.

extern "C" {
struct Card80127960 {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
};
int fn_80127A78(Card80127960*, int);
void fn_801279C8(Card80127960*, int);

int fn_80127960(Card80127960* o)
{
	if (o->f10 == 0) {
		if (fn_80127A78(o, o->fc) != 0) {
			o->f10 = 1;
			fn_801279C8(o, o->fc);
		}
	} else {
		fn_801279C8(o, o->fc);
	}
	return o->f14;
}
}
