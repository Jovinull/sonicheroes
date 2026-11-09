// Calls fn_800AB42C on the object in slot idx of lbl_802AD070 when the slot is occupied.

extern "C" {
extern void* lbl_802AD070[];
void fn_800AB42C(void*);

void fn_800A4630(int a, int idx)
{
	if (lbl_802AD070[idx] != 0) {
		fn_800AB42C(lbl_802AD070[idx]);
	}
}
}
