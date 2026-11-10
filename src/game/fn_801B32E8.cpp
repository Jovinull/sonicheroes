// Stores the id and returns the object when the follow-up check succeeds.
extern "C" {
extern int lbl_8042CA80;
int fn_801B3474();

void* fn_801B32E8(void* a, int b)
{
	lbl_8042CA80 = b;
	if (fn_801B3474() != 0) {
		return a;
	}
	return 0;
}
}
