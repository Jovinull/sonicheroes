// Destructor: stores the class vtable at 0x18; if a linked record is held at 0x4C, flags it (bit 0 of its halfword at 4) when fn_80017800 says it is still live and drops the link; then runs the TObject destructor and frees the object when the delete flag is positive.

extern "C" {
struct Link80090374 {
	unsigned char pad[4];
	unsigned short f4;
};
struct Obj80090374 {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0x4c - 0x1c];
	Link80090374* f4c;
};
extern unsigned char lbl_8024FD58[];
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void __dt__7TObjectFv(void*, int);
int fn_80017800(void*);

Obj80090374* fn_80090374(Obj80090374* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8024FD58;
		if (o->f4c != 0) {
			if (fn_80017800(o->f4c) != 0) {
				Link80090374* t = o->f4c;
				t->f4 |= 1;
			}
			o->f4c = 0;
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
