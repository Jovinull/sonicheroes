// Clears the word at the offset fn_801521F4(0x120) returns inside the object and stores the result of fn_8015BF40(0) at 0x6C; returns the object.

extern "C" {
int fn_801521F4(int);
int fn_8015BF40(int);
struct Obj800B8604 {
	unsigned char pad[0x6c];
	int f6c;
};

Obj800B8604* fn_800B8604(Obj800B8604* o)
{
	int off                          = fn_801521F4(0x120);
	*(int*)((unsigned char*)o + off) = 0;
	o->f6c                           = fn_8015BF40(0);
	return o;
}
}
