// Destructor: stores the class vtable at 0x18, releases the five owned handles at 0x2C..0x3C (fn_80150958), runs the TObject destructor and frees the object when the delete flag is positive.

extern "C" {
struct Obj800F609C {
	unsigned char pad[0x18];
	void* vt;
	unsigned char pad1[0x2c - 0x1c];
	unsigned f2c[5];
};
extern unsigned char lbl_80259E14[];
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void __dt__7TObjectFv(void*, int);
void fn_80150958(unsigned);

Obj800F609C* fn_800F609C(Obj800F609C* o, short flags)
{
	int i;
	if (o != 0) {
		o->vt = lbl_80259E14;
		i     = 0;
		do {
			if (o->f2c[i] != 0) {
				fn_80150958(o->f2c[i]);
				o->f2c[i] = 0;
			}
			i++;
		} while (i < 5);
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
