#include "types.h"

// TObjEnemySearcher::UpdateJetFrame and UpdateOnEdit (the PS2 build's names):
// switching the light shows the lit or the dark body and parts and moves the
// shown ones to the jet frame's matrix; in the editor the searcher re-reads
// its parameters and placement.

#include "src/rel/searcher.inc"

typedef struct RwMatrixTag RwMatrixTag;

void objRpClumpForAllAtomicsToRender(RpClump* clump);
void objRpClumpForAllAtomicsToHide(RpClump* clump);

extern "C" RwMatrixTag* fn_8019E8EC(RwFrame* frame);
extern "C" void fn_8019ECCC(RwFrame* frame, RwMatrixTag* matrix, s32 combine);
extern "C" void SetParameter__17TObjEnemySearcherFv(Searcher* searcher);
extern "C" void SetPosition__17TObjEnemySearcherFv(Searcher* searcher);

extern "C" void UpdateJetFrame__17TObjEnemySearcherFv(Searcher* searcher)
{
	RwFrame* body;
	RwFrame* parts;

	searcher->lit = searcher->lit ? 0 : 1;
	if (searcher->lit) {
		objRpClumpForAllAtomicsToRender(searcher->clumps[0]);
		objRpClumpForAllAtomicsToRender(searcher->clumps[2]);
		objRpClumpForAllAtomicsToHide(searcher->clumps[1]);
		objRpClumpForAllAtomicsToHide(searcher->clumps[3]);
		body  = searcher->clumps[0]->frame;
		parts = searcher->clumps[2]->frame;
	} else {
		objRpClumpForAllAtomicsToHide(searcher->clumps[0]);
		objRpClumpForAllAtomicsToHide(searcher->clumps[2]);
		objRpClumpForAllAtomicsToRender(searcher->clumps[1]);
		objRpClumpForAllAtomicsToRender(searcher->clumps[3]);
		body  = searcher->clumps[1]->frame;
		parts = searcher->clumps[3]->frame;
	}
	if (searcher->jetFrame != NULL) {
		RwMatrixTag* matrix = fn_8019E8EC(searcher->jetFrame);

		if (body != NULL) {
			fn_8019ECCC(body, matrix, 0);
		}
		if (parts != NULL) {
			fn_8019ECCC(parts, matrix, 0);
		}
	}
}

extern "C" void UpdateOnEdit__17TObjEnemySearcherFv(Searcher* searcher)
{
	SetParameter__17TObjEnemySearcherFv(searcher);
	SetPosition__17TObjEnemySearcherFv(searcher);
}
