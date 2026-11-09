// Looks up the frame of bone id arg2 in the hierarchy arg1, storing its index at 0 and the value at +0xC of that frame (16-byte entries at +0x10) at 8.

extern "C" {
struct Frame8003C9D8 {
	unsigned char pad[0xc];
	int fc;
};
struct Hier8003C9D8 {
	unsigned char pad[0x10];
	Frame8003C9D8* f10;
};
struct Out8003C9D8 {
	int f0;
	int f4;
	int f8;
};
int objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(Hier8003C9D8*, int);

void fn_8003C9D8(Out8003C9D8* a, Hier8003C9D8* h, int id)
{
	a->f0 = objRpHAnimHierarchyFindFrameFromBoneID__FP16RpHAnimHierarchyi(h, id);
	a->f8 = (h->f10 + a->f0)->fc;
}
}
