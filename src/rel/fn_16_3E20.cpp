typedef int s32;
extern "C" {
void* RpAtomicMCCGetCustomRenderCallBack(void*);
void RpAtomicMCCSetMaterialPointer(void*, void*);
struct O {
	char pad[0xF4];
	void* a;
};
void fn_16_3E20(O* o, void* m)
{
	void* v = m;
	s32* p;
	RpAtomicMCCSetMaterialPointer(o->a, v);
	p  = (s32*)RpAtomicMCCGetCustomRenderCallBack(o->a);
	*p = 0x10;
}
}
