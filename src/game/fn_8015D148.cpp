// Rebuilds the cached value of a's object (0x18) into *out: the source is the object itself and
// its data at 0x58 when its word 0x18 is 1, otherwise a and a's data at 0x14. Objects with flag
// 0x02000000 use fn_801650B4 while lbl_8042BD28 is 1; all others use fn_801659DC. The object's
// halfword 0x0C is cleared and a is returned. Layouts are inferred.
// NonMatching: 2 word diffs. In the "a" branch retail still reads a from r3 (mr r4,r3; addi
// r5,r3,0x14); MWCC uses its saved copy in r29.
struct Obj8015D148 {
	unsigned char pad0[0x8];
	unsigned int flags; // 0x08
	short fC;           // 0x0C
	unsigned char padE[0x18 - 0xE];
	int f18;
};

struct A8015D148 {
	unsigned char pad0[0x18];
	Obj8015D148* obj; // 0x18
};

extern "C" {
extern int lbl_8042BD28;
void* fn_801650B4(Obj8015D148* o, void* src, void* data);
void* fn_801659DC(Obj8015D148* o, void* src, void* data);

A8015D148* fn_8015D148(A8015D148* a, void** out)
{
	Obj8015D148* o = a->obj;
	void* src;
	void* data;
	if (o->f18 != 1) {
		src  = a;
		data = (unsigned char*)a + 0x14;
	} else {
		src  = o;
		data = (unsigned char*)o + 0x58;
	}
	if (o->flags & 0x02000000) {
		if (lbl_8042BD28 == 1) {
			*out = fn_801650B4(o, src, data);
		} else {
			*out = fn_801659DC(o, src, data);
		}
	} else {
		*out = fn_801659DC(o, src, data);
	}
	o->fC = 0;
	return a;
}
}
