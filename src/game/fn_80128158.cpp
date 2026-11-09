// If fn_801281AC(object, 1) succeeds, sets words 0x10 = 1 and 0xC = 3 and returns 1; otherwise 0.

extern "C" {
struct Obj80128158 {
	unsigned char pad[0xc];
	int fc;
	int f10;
};
int fn_801281AC(Obj80128158*, int);

int fn_80128158(Obj80128158* o)
{
	if (fn_801281AC(o, 1) != 0) {
		o->f10 = 1;
		o->fc  = 3;
		return 1;
	}
	return 0;
}
}
