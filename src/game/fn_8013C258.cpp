// Releases the object found at the object + lbl_8042C818 offset (fn_8013CAE8) when it holds something, clears that slot and returns the object.

extern "C" {
extern int lbl_8042C818;
void fn_8013CAE8(int, unsigned*);

int fn_8013C258(int o)
{
	unsigned* t = *(unsigned**)(o + lbl_8042C818);
	if (t != 0 && *t != 0) {
		fn_8013CAE8(o, t);
	}
	*(int*)(o + lbl_8042C818) = 0;
	return o;
}
}
