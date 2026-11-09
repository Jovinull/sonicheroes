// Links the object's node into the manager's list on first activation and marks both active.
struct Link8019EC30 {
	unsigned char pad0[3];
	unsigned char f3;
	unsigned char pad4[4];
	void* f8;
	void* fC;
};
struct Obj8019EC30 {
	unsigned char pad0[3];
	unsigned char f3;
	unsigned char pad4[0xC];
	unsigned char f10[0x90];
	Link8019EC30* fA0;
};
struct Mgr8019EC30 {
	unsigned char pad0[0xBC];
	void** fBC;
};

extern "C" {
extern Mgr8019EC30* lbl_8042C9A4;
void fn_80195E44(void* p);

Obj8019EC30* fn_8019EC30(Obj8019EC30* o)
{
	unsigned char t;
	fn_80195E44(o->f10);
	t = o->fA0->f3;
	if (!(t & 3)) {
		o->fA0->f8                               = lbl_8042C9A4->fBC;
		o->fA0->fC                               = (char*)lbl_8042C9A4 + 0xBC;
		*(void***)((char*)lbl_8042C9A4->fBC + 4) = (void**)((char*)o->fA0 + 8);
		lbl_8042C9A4->fBC                        = (void**)((char*)o->fA0 + 8);
	}
	o->fA0->f3 = t | 3;
	o->f3      = o->f3 | 0xC;
	return o;
}
}
