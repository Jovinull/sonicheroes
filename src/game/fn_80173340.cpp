// Runs the per-mode handler for the mode word at *arg0 (1..4; mode 0 does nothing); returns arg0, or 0 for any unknown mode.

extern "C" {
void fn_80172A24(void);
void fn_8017377C(void);
void fn_80173AC0(void);
void fn_801751D0(void);

int* fn_80173340(int* o)
{
	int* r = o;
	switch (*o) {
		case 0:
			break;
		case 1:
			fn_80173AC0();
			break;
		case 2:
			fn_801751D0();
			break;
		case 3:
			fn_8017377C();
			break;
		case 4:
			fn_80172A24();
			break;
		default:
			r = 0;
			break;
	}
	return r;
}
}
