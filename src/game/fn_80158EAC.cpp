// Destroys a world sector tree (HYPOTHESIS: the RpWorld sector tree destructor used by
// fn_80159798): an atomic sector (type -1) releases its instanced data (fn_80197384), unlinks the
// atomic and light ties of its three lists (fn_8015A58C, fn_8015A51C), runs the sector plugin
// destructors and frees its vertex arrays, its eight texture coordinate arrays and itself; an
// empty sector (type -2) is freed; a plane sector destroys both subtrees first. Names are
// inferred from this function and fn_80159798.
// NonMatching: retail copies the sector into a second saved register for the atomic-sector case
// (mr r31, r28; one instruction more), which this source's copy does not keep apart, so the
// registers of that case differ (123 words). Moving that case into an inline helper makes the
// compiler inline the recursion instead.
#include "game/rw_engine.h"

#define RP_WORLD_ATOMIC_SECTOR      -1
#define RP_WORLD_EMPTY_SECTOR       -2
#define RP_WORLD_NUM_TEX_COORD_SETS 8

struct Sector80158EAC {
	s32 type;              // 0x0
	void* array4;          // 0x4
	Sector80158EAC* left;  // 0x8: plane sectors (atomic sectors: vertex array)
	Sector80158EAC* right; // 0xC: plane sectors (atomic sectors: normal array)
	void* texCoords[RP_WORLD_NUM_TEX_COORD_SETS]; // 0x10
	void* array30;                                // 0x30
	void* repEntry;                               // 0x34
	RwLinkList atomics;                           // 0x38
	RwLinkList atomics2;                          // 0x40
	RwLinkList lights;                            // 0x48
};

extern "C" {
// World sector plugin registry (HYPOTHESIS: sectorTKList).
extern RwPluginRegistry lbl_8028D2D0;
// HYPOTHESIS: RwResourcesFreeResEntry and the atomic/light tie removals.
s32 fn_80197384(void* resEntry);
void fn_8015A58C(RwLLLink* tie);
void fn_8015A51C(RwLLLink* tie);
void fn_80158EAC(Sector80158EAC* sector)
{
	switch (sector->type) {
		case RP_WORLD_ATOMIC_SECTOR: {
			Sector80158EAC* atomicSector = sector;
			RwLLLink* cur;
			s32 i;

			if (atomicSector->repEntry != 0) {
				fn_80197384(atomicSector->repEntry);
			}
			cur = atomicSector->atomics.link.next;
			while (cur != &atomicSector->atomics.link) {
				RwLLLink* tie = cur;
				cur           = cur->next;
				fn_8015A58C(tie);
			}
			cur = atomicSector->atomics2.link.next;
			while (cur != &atomicSector->atomics2.link) {
				RwLLLink* tie = cur;
				cur           = cur->next;
				fn_8015A58C(tie);
			}
			cur = atomicSector->lights.link.next;
			while (cur != &atomicSector->lights.link) {
				RwLLLink* tie = cur;
				cur           = cur->next;
				fn_8015A51C(tie);
			}
			fn_80198E04(&lbl_8028D2D0, atomicSector);
			if (atomicSector->left != 0) {
				lbl_8042C9A4->rwfree(atomicSector->left);
				atomicSector->left = 0;
			}
			if (atomicSector->right != 0) {
				lbl_8042C9A4->rwfree(atomicSector->right);
				atomicSector->right = 0;
			}
			if (atomicSector->array30 != 0) {
				lbl_8042C9A4->rwfree(atomicSector->array30);
				atomicSector->array30 = 0;
			}
			if (atomicSector->array4 != 0) {
				lbl_8042C9A4->rwfree(atomicSector->array4);
				atomicSector->array4 = 0;
			}
			for (i = 0; i < RP_WORLD_NUM_TEX_COORD_SETS; i++) {
				if (atomicSector->texCoords[i] != 0) {
					lbl_8042C9A4->rwfree(atomicSector->texCoords[i]);
					atomicSector->texCoords[i] = 0;
				}
			}
			lbl_8042C9A4->rwfree(atomicSector);
			break;
		}
		case RP_WORLD_EMPTY_SECTOR:
			lbl_8042C9A4->rwfree(sector);
			break;
		default:
			fn_80158EAC(sector->left);
			sector->left = 0;
			fn_80158EAC(sector->right);
			sector->right = 0;
			lbl_8042C9A4->rwfree(sector);
			break;
	}
}
}
