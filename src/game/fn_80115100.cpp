// Returns 1 when any of the four entries in lbl_80288E0C is in state 3 (+0x100), else 0.

extern "C" {
struct Entry80115100 {
	unsigned char pad[0x100];
	int f100;
};
extern Entry80115100* lbl_80288E0C[4];

int fn_80115100(void)
{
	int i;
	for (i = 0; i < 4; i++) {
		Entry80115100* e = lbl_80288E0C[i];
		if (e != 0 && e->f100 == 3) {
			return 1;
		}
	}
	return 0;
}
}
