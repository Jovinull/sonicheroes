// Returns 1 when one of the two active entries in lbl_8042B634 is in state 1 for the slot arg0 (0..3); else 0.

extern "C" {
struct Entry800CB264 {
	unsigned char pad[0x29];
	signed char c29;
	signed char c2a;
};
extern Entry800CB264* lbl_8042B634[2];

int fn_800CB264(signed char k)
{
	int i;
	if (k >= 0 && k <= 3) {
		for (i = 0; i < 2; i++) {
			Entry800CB264* c = lbl_8042B634[i];
			if (c != 0 && c->c2a == k && c->c29 == 1) {
				return 1;
			}
		}
	}
	return 0;
}
}
