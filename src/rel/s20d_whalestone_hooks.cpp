#include "types.h"

// The whalestone's Unload and Load hooks (s20dWhalestoneUnload and s20dWhalestoneLoad here): its model
// list is released; the list is loaded and the two models it keeps at hand,
// entries 6 and 7, are looked up in it.

extern "C" u8 s20dWhalestoneModelList[];
extern "C" void* s20dWhalestoneModels[2];

extern "C" void LoadFilesEx__6BMODELFP11BMODEL_DATAP15BMODEL_ANIMDATAP17BMODEL_CAMERADATA(
    void* list, void* a, void* b);
extern "C" void* SearchClump__6BMODELFP11BMODEL_DATAs(void* list, s16 index);
extern "C" void
ReleaseFiles__6BMODELFPP15RwTexDictionaryP11BMODEL_DATAP15BMODEL_ANIMDATAP17BMODEL_CAMERADATA(
    s32 a, void* list, void* b, void* c);

extern "C" void s20dWhalestoneUnload(void)
{
	ReleaseFiles__6BMODELFPP15RwTexDictionaryP11BMODEL_DATAP15BMODEL_ANIMDATAP17BMODEL_CAMERADATA(
	    0, s20dWhalestoneModelList, NULL, NULL);
}

extern "C" void s20dWhalestoneLoad(void)
{
	LoadFilesEx__6BMODELFP11BMODEL_DATAP15BMODEL_ANIMDATAP17BMODEL_CAMERADATA(
	    s20dWhalestoneModelList, NULL, NULL);
	s20dWhalestoneModels[0] = SearchClump__6BMODELFP11BMODEL_DATAs(s20dWhalestoneModelList, 6);
	s20dWhalestoneModels[1] = SearchClump__6BMODELFP11BMODEL_DATAs(s20dWhalestoneModelList, 7);
}
