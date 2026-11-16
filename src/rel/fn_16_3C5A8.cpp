struct RpHAnimHierarchy {
	int a;
	int b;
	int c;
	int d;
	char* nodes;
};
int objRpHAnimHierarchyFindFrameFromBoneID(RpHAnimHierarchy* h, int id);
extern "C" int fn_16_3C5A8(void* self, RpHAnimHierarchy* h, int id)
{
	int idx = objRpHAnimHierarchyFindFrameFromBoneID(h, id);
	return *(int*)(h->nodes + idx * 16 + 12);
}
