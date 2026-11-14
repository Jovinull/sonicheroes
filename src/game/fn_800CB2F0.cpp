// Returns 1 when one of the two active entries in lbl_8042B634 is in state 1 for slot arg0; else 0.

extern "C" {
struct Entry800CB2F0 {
	unsigned char pad[0x29];
	signed char c29;
	unsigned char pad2[0x30 - 0x2a];
	int f30;
};
extern Entry800CB2F0* lbl_8042B634[2];

int fn_800CB2F0(int arg0)
{
	int i;
	if (arg0 >= 0) {
		for (i = 0; i < 2; i++) {
			Entry800CB2F0* c = lbl_8042B634[i];
			if (c != 0 && c->f30 == arg0 && c->c29 == 1) {
				return 1;
			}
		}
	}
	return 0;
}
}
