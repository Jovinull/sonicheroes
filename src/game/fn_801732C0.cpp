// Runs the per-mode handler for the mode word at *arg0 (1..4); returns arg0, or 0 for any other mode.

extern "C" {
void fn_80172C20(void);
void fn_801736F0(void);
void fn_80173DF0(void);
void fn_80175720(void);

int* fn_801732C0(int* o)
{
	switch (*o) {
		case 1:
			fn_80173DF0();
			break;
		case 2:
			fn_80175720();
			break;
		case 3:
			fn_801736F0();
			break;
		case 4:
			fn_80172C20();
			break;
		default:
			return 0;
	}
	return o;
}
}
