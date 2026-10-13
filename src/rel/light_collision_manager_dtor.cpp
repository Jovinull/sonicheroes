#include "types.h"

// The light collision manager's destructor (lightCollisionManagerDtor here;
// TObjLightColliMaster's in the PS2 build). It restores the vtable, gives each
// of the eight players back the light set the light keeps for it, forgets
// itself as the stage's manager and runs the object base down, freeing the
// object when the delete flag asks for it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject; // 0x28

class CLIGHT
{
public:
	u8 unk000[0x4C7];
	s8 players[8]; // 0x4C7

	void SetCurrentNumPlayer(s8 player, s8 num);
};

extern "C" void* lbl_8042C148;
extern "C" CLIGHT lbl_802D5E80;
extern "C" void* lightCollisionManagerVtable[];
extern "C" TObject* lightCollisionManager;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);

extern "C" TObject* lightCollisionManagerDtor(TObject* object, s16 flags)
{
	if (object != NULL) {
		object->vtable = lightCollisionManagerVtable;

		for (s8 i = 0; i < 8; i++) {
			lbl_802D5E80.SetCurrentNumPlayer(i, lbl_802D5E80.players[i]);
		}
		if (lightCollisionManager == object) {
			lightCollisionManager = NULL;
		}

		__dt__7TObjectFv(object, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
