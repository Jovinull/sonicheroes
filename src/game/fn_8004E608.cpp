#include "types.h"

extern "C" {
struct Team8004E608 {
	unsigned char pad[0x8c];
	int f8c;
	unsigned char pad1[0x2324 - 0x90];
};
extern Team8004E608 lbl_802B908C[];
extern int lbl_8042C1FC;

int fn_8004E608(void)
{
	return lbl_802B908C[lbl_8042C1FC].f8c;
}
}
