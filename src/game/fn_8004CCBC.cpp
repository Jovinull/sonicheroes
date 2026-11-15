// Releases the ten entries of lbl_802D5B20 that are set (fn_8014D8A4) and clears them. The entry
// type and the release function's role are UNKNOWN.
#include "types.h"

extern "C" {
extern void* lbl_802D5B20[10];
void fn_8014D8A4(void* entry);

void fn_8004CCBC(void)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (lbl_802D5B20[i] != NULL) {
			fn_8014D8A4(lbl_802D5B20[i]);
			lbl_802D5B20[i] = NULL;
		}
	}
}
}
