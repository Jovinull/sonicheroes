// Maps the state fn_80091FAC reports for the current team's entry to a mode: 0 -> 1, 1 -> 4, 2 -> 2.

extern "C" {
extern int lbl_80303DC8[];
extern int lbl_8042C1FC;
int fn_80091FAC(int);

int fn_80050CC8()
{
	int r;
	switch (fn_80091FAC(lbl_80303DC8[lbl_8042C1FC])) {
		case 0:
			r = 1;
			break;
		case 1:
			r = 4;
			break;
		case 2:
			r = 2;
			break;
	}
	return r;
}
}
