// Sets the state at 0xC and the busy flag at 0x10 (1 when fn_80127A78 reports non-zero, else 0).

extern "C" {
struct Card80127904 {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
};
int fn_80127A78(void);

void fn_80127904(Card80127904* o, int a)
{
	if (fn_80127A78() != 0) {
		o->f10 = 1;
		o->fc  = a;
		return;
	}
	o->f10 = 0;
	o->fc  = a;
}
}
