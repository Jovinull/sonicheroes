// Runs the four validation stages in order and, only if all pass, calls fn_801B6738 with the value gathered in sp8.

extern "C" {
unsigned fn_801B5B20(void);
unsigned fn_801B6030(int);
unsigned fn_801B6390(int, int*);
unsigned fn_801B6624(int, int*);
void fn_801B6738(int, int);

void fn_801B6B98(int a)
{
	int sp8 = 0;
	if (fn_801B5B20() == 0 && fn_801B6030(a) == 0 && fn_801B6390(a, &sp8) == 0
	    && fn_801B6624(a, &sp8) == 0) {
		fn_801B6738(a, sp8);
	}
}
}
