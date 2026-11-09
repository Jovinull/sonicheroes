// Destructor: stores the class vtable at 0x18, destroys the embedded C_COLLI at 0x60, runs the TObject destructor and frees the object when the delete flag is positive.

extern "C" {
struct Obj8010FB50 {
	unsigned char pad[0x18];
	void* vt;
};
extern unsigned char lbl_8025B4F0[];
extern void* lbl_8042C148;
void Free__9THeapCtrlFPv(void*, void*);
void __dt__7TObjectFv(void*, int);
void __dt__7C_COLLIFv(void*, int);

Obj8010FB50* fn_8010FB50(Obj8010FB50* o, short flags)
{
	if (o != 0) {
		o->vt = lbl_8025B4F0;
		__dt__7C_COLLIFv((unsigned char*)o + 0x60, 0);
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, o);
		}
	}
	return o;
}
}
