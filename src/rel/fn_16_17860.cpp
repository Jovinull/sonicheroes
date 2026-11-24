typedef int s32;
typedef unsigned int u32;
struct RpClump;
struct RpAtomic;
struct E {
	char pad[0x28];
	RpClump* clump;
	char pad2[8];
};
struct O {
	char pad[0x28];
	char frame[0x40];
	E* rings;
};
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump*, u32);
RpAtomic* objRpClumpGetAtomic(RpClump*, RpAtomic*);
extern "C" {
void* RpAtomicMCCGetCustomRenderCallBack(RpAtomic*);
u32 fn_16_170C(void*);
void fn_16_17860(O* o)
{
	if (o->rings != 0) {
		for (int i = 0; i < 3; i++) {
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
			    o->rings[i].clump, fn_16_170C(o->frame) + 4);
			RpAtomic* a = objRpClumpGetAtomic(o->rings[i].clump, 0);
			s32* p      = (s32*)RpAtomicMCCGetCustomRenderCallBack(a);
			*p          = 0x10;
		}
	}
}
}
