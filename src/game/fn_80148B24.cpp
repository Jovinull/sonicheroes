// Same as fn_80148A2C but dispatches to fn_80149214 when the flag is set.

extern "C" {
unsigned fn_80193884(void*, void*, int);
int fn_80149214(int);

void* fn_80148B24(void* a, int unused, int c)
{
	int sp8;
	if (fn_80193884(a, &sp8, 4) == 0) {
		return 0;
	}
	if (sp8 != 0) {
		fn_80149214(c);
	}
	return a;
}
}
