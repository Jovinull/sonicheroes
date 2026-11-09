// Stores the handle from fn_80209AA4 into *arg0; returns 0x0D000001 when the system is not initialised, 0x07000101 when there is no handle, else 0.

extern "C" {
extern unsigned lbl_8042CF6C;
unsigned fn_80209AA4(void);

int fn_8020B0EC(unsigned* o)
{
	unsigned t;
	if (lbl_8042CF6C == 0) {
		return 0x0d000001;
	}
	t = fn_80209AA4();
	if (t == 0) {
		return 0x07000101;
	}
	*o = t;
	return 0;
}
}
