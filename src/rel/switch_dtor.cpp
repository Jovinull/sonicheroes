#include "types.h"

// TObjSwitch's destructor. It restores both class vtables, detaches and
// releases the model, destroys the collision and placement bases, and finally
// frees the object when requested by the deleting-destructor flag.
//
// The claim is .text 0x4580 to 0x4650. The routine is shared by the thirteen
// stage modules that use the common object engine.

typedef struct TObject {
	u8 unk0[0x18];
	void** vtable;
	u8 unk1C[0xC];
} TObject;

typedef struct World {
	u8 unk0[0x725C];
	void* scene;
} World;

typedef struct Switch {
	TObject base;
	u8 placement[0x4];
	void** vtable2;
	u8 collision[0xBC];
	void* model;
} Switch;

extern "C" World* lbl_8042C1D0;
extern "C" void* lbl_8042C148;

extern "C" void dtor_800186D0(TObject* object, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void dtor_8003C52C(void* part, s32 flags);
extern "C" void dtor_8005BD3C(void* motion, s32 flags);
extern "C" void fn_80150958(void* model);
extern "C" void fn_8015BBF8(void* scene, void* model);
extern "C" void* fn_8015BD78(void* model);

extern "C" void* switchVtable[];

extern "C" Switch* switchDtor(Switch* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = switchVtable;
		object->vtable2     = switchVtable + 0xB;

		if (fn_8015BD78(object->model) != NULL) {
			fn_8015BBF8(lbl_8042C1D0->scene, object->model);
		}
		fn_80150958(object->model);
		object->model = NULL;

		dtor_8003C52C(&object->collision, 0);
		dtor_8005BD3C(&object->placement, 0);
		dtor_800186D0(&object->base, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}
