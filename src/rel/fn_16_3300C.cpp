typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef unsigned int u32;
struct Inner {
	u8 pad[0x2C];
	s32 v2c;
};
struct O {
	u8 pad[0x28];
	Inner* p28;
	u8 pad2[0x94];
	u32 idC0;
};
struct N {
	u8 pad[0x28];
	u16 type;
	u8 pad2[6];
	s32* p30;
	s32 pad34;
	N* next;
};
extern "C" {
N* fn_16_33DC(s32, u8);
extern s32 lbl_8042C298;
void fn_16_3300C(O* obj, u8 kind, s32 val)
{
	s32 v = obj->p28->v2c;
	s16 i;
	N* n;
	s32* p;
	u16 t;
	n = fn_16_33DC(lbl_8042C298, kind);
	if (n != 0) {
		i = 0;
		for (; n != 0; n = n->next) {
			t = n->type;
			if (t == obj->idC0) {
				p = n->p30;
				if (p != 0) {
					*p = val;
				}
			}
		}
	}
}
}
