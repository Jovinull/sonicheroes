struct Cfg {
	char pad0[0x2A];
	unsigned char id;
};
struct Node {
	char pad0[0x28];
	unsigned short kind;
	char pad2a[0xE];
	Node* next;
};
struct Obj {
	char pad0[0x28];
	Cfg* cfg;
	char pad2c[0x164];
	Node* target;
};
extern "C" {
extern int lbl_8042C298;
Node* fn_16_33DC(int, unsigned char);
void fn_16_454A0(Obj* o)
{
	Node* n;
	for (n = fn_16_33DC(lbl_8042C298, o->cfg->id); n != 0; n = n->next) {
		if (n->kind == 0x32 && (Cfg*)n != o->cfg) {
			o->target = n;
			break;
		}
	}
}
}
