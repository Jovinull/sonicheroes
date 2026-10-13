#include "types.h"

// TObjEnemyPawn::UpdateOnEdit (the PS2 build's name, by its member order):
// while the object is edited it rereads its parameters and places itself again.

extern "C" void SetParameter__13TObjEnemyPawnFv(void* pawn);
extern "C" void SetPosition__13TObjEnemyPawnFv(void* pawn);

extern "C" void UpdateOnEdit__13TObjEnemyPawnFv(void* pawn)
{
	SetParameter__13TObjEnemyPawnFv(pawn);
	SetPosition__13TObjEnemyPawnFv(pawn);
}
