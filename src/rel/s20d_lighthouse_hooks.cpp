#include "types.h"

// The lighthouse's Unload and Load hooks (s20dLighthouseUnload and s20dLighthouseLoad here): its model
// list is released; the list is loaded and the two models it keeps at hand,
// entries 3 and 4, are looked up in it.

extern "C" u8 s20dLighthouseModelList[];
extern "C" void* s20dLighthouseModels[2];

extern "C" void LoadFilesEx__6BMODELFP11BMODEL_DATAP15BMODEL_ANIMDATAP17BMODEL_CAMERADATA(
    void* list, void* a, void* b);
extern "C" void* SearchClump__6BMODELFP11BMODEL_DATAs(void* list, s16 index);
extern "C" void
ReleaseFiles__6BMODELFPP15RwTexDictionaryP11BMODEL_DATAP15BMODEL_ANIMDATAP17BMODEL_CAMERADATA(
    s32 a, void* list, void* b, void* c);

extern "C" void s20dLighthouseUnload(void)
{
	ReleaseFiles__6BMODELFPP15RwTexDictionaryP11BMODEL_DATAP15BMODEL_ANIMDATAP17BMODEL_CAMERADATA(
	    0, s20dLighthouseModelList, NULL, NULL);
}

extern "C" void s20dLighthouseLoad(void)
{
	LoadFilesEx__6BMODELFP11BMODEL_DATAP15BMODEL_ANIMDATAP17BMODEL_CAMERADATA(
	    s20dLighthouseModelList, NULL, NULL);
	s20dLighthouseModels[0] = SearchClump__6BMODELFP11BMODEL_DATAs(s20dLighthouseModelList, 3);
	s20dLighthouseModels[1] = SearchClump__6BMODELFP11BMODEL_DATAs(s20dLighthouseModelList, 4);
}
