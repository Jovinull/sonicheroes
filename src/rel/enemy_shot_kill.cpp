#include "game/effect/eff_bomb.h"
#include "game/object.h"

// ENEMY_SHOT::KillTask (the PS2 build's name): ends the first live enemy shot
// with the number among the parent's descendants (a shot already done is
// skipped; other objects are searched in turn).
//
// The original is a plain recursive function with two inline TObject helpers
// (IsClass and Kill below). MWCC inlined the recursion five levels deep and
// the helpers in every level but the deepest, which calls their out-of-line
// copies; those sit at the end of the original unit (rel/enemy_shot_helpers.cpp,
// after ENEMY_SHOT::Move). Written out level by level here so that this unit
// does not emit the copies itself; the code is the same as the recursion's.

#include "src/rel/enemy_shot.inc"

static inline s32 IsClass(TObject* object, char* name)
{
	return object->ClassName == name;
}

static inline void Kill(TObject* object)
{
	object->Signal |= 1;
}

// the out-of-line copies of IsClass and Kill (rel/enemy_shot_move.cpp)
extern "C" s32 enemyShotIsClass(TObject* object, char* name);
extern "C" void enemyShotKill(TObject* object);

#define KILL_TASK_LEVEL(IS_CLASS, KILL, RECURSE)                                                   \
	TObject* next = parent->Child;                                                                 \
	while (parent->Child != NULL && next != NULL) {                                                \
		TObject* object = next;                                                                    \
		next            = object->Next;                                                            \
		if (IS_CLASS(object, CL_EnemyShot) && object->Tag == id) {                                 \
			if (((ENEMY_SHOT*)object)->done == 0) {                                                \
				KILL(object);                                                                      \
				return;                                                                            \
			}                                                                                      \
		} else {                                                                                   \
			RECURSE(object, id);                                                                   \
		}                                                                                          \
	}

static inline void KillTask6(TObject* parent, u16 id)
{
	KILL_TASK_LEVEL(enemyShotIsClass, enemyShotKill, ENEMY_SHOT::KillTask)
}
static inline void KillTask5(TObject* parent, u16 id)
{
	KILL_TASK_LEVEL(IsClass, Kill, KillTask6)
}
static inline void KillTask4(TObject* parent, u16 id)
{
	KILL_TASK_LEVEL(IsClass, Kill, KillTask5)
}
static inline void KillTask3(TObject* parent, u16 id)
{
	KILL_TASK_LEVEL(IsClass, Kill, KillTask4)
}
static inline void KillTask2(TObject* parent, u16 id)
{
	KILL_TASK_LEVEL(IsClass, Kill, KillTask3)
}

void ENEMY_SHOT::KillTask(TObject* parent, u16 id)
{
	KILL_TASK_LEVEL(IsClass, Kill, KillTask2)
}
