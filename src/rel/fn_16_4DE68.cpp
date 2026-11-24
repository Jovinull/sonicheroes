struct RpClump;
struct ClumpList {
	int count;
	RpClump** clumps;
};
extern "C" {
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(RpClump*, unsigned int);
void fn_16_4DE68(ClumpList* list, int light)
{
	int i;
	for (i = 0; i < list->count; i++) {
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(list->clumps[i], light);
	}
}
}
