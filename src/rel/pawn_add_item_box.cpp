#include "types.h"

// TObjEnemyPawn::AddItemBox (the PS2 build's name): drops an item box where
// the pawn was destroyed (nItemBox::CreateItemBox picks the nearest team and a
// random item).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

namespace nItemBox
{
void CreateItemBox(RwV3d* pos);
}

typedef struct Pawn Pawn;

extern "C" void AddItemBox__13TObjEnemyPawnFP5RwV3d(Pawn* pawn, RwV3d* pos)
{
	nItemBox::CreateItemBox(pos);
}
