#include "types.h"

struct B {
	s32 pad10[4];
	s32 k;
};
struct N {
	u8 pad[0x28];
	u16 type;
	u8 pad2[6];
	B* b;
	s32 pad34;
	N* next;
};

extern "C" N* fn_16_33DC(s32, u8);
extern s32 lbl_8042C298;

extern "C" s32 fn_16_331C(u8 kind)
{
	N* n = fn_16_33DC(lbl_8042C298, kind);
	if (n == NULL) {
		return 0;
	}
	while (n != NULL) {
		if (n->type == 5 || n->type == 7 || n->type == 6 || n->type == 0x1104) {
			B* b = n->b;
			if (b == NULL) {
				return 0;
			}
			if (b->k != 2) {
				return 0;
			}
		}
		n = n->next;
	}
	return 1;
}
