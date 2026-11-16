struct RpHAnimHierarchy {
	int a;
	int b;
	int c;
	int d;
	char* pNodeInfo;
};
int objRpHAnimHierarchyFindFrameFromBoneID(RpHAnimHierarchy* h, int id);
extern "C" int fn_16_43E14(void* self, RpHAnimHierarchy* hierarchy, int id)
{
	int index = objRpHAnimHierarchyFindFrameFromBoneID(hierarchy, id);
	return *(int*)(hierarchy->pNodeInfo + index * 16 + 12);
}
