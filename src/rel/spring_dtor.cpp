#include "types.h"

// TObjSpring's destructor. It sits apart from the rest of the class in
// rel/spring_object.cpp because the constructor between them is not carvable on
// its own: it shares the asset name strings with the loader.
//
// The claim is .text 0x1430 to 0x1500 and nothing else. Everything it touches
// is either a DOL symbol or a name the module already exports, the vtable
// among them, so there is no data to take.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out, as everywhere
// else.
//
// Both vtables are restored out of one address, the way the other destructors
// in this family do it, and the two bases are torn down inner first. What is
// specific to the spring is the model in front of that: it is unregistered from
// the world it was added to, but only if it is still attached.

typedef struct TObject {
	u8 unk0[0x18]; // 0x00
	void** vtable; // 0x18
	u8 unk1C[0xC]; // 0x1C
} TObject;

typedef struct World {
	u8 unk0[0x7274]; // 0x0000
	void* scene;     // 0x7274
} World;

typedef struct Spring {
	TObject base;   // 0x000
	u8 unk28[0x4];  // 0x028
	void** vtable2; // 0x02C
	u8 unk30[0xC8]; // 0x030
	void* model;    // 0x0F8
} Spring;

extern "C" World* lbl_8042C1D0;
extern "C" void* lbl_8042C148;

extern "C" void dtor_800186D0(TObject* object, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void dtor_8003C52C(void* part, s32 flags);
extern "C" void dtor_8005BD3C(void* motion, s32 flags);
extern "C" void fn_80150958(void* model);
extern "C" void fn_8015BBF8(void* scene, void* model);
extern "C" void* fn_8015BD78(void* model);

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* springVtable[];

extern "C" Spring* springDtor(Spring* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = springVtable;
		object->vtable2     = springVtable + 0xB;

		if (fn_8015BD78(object->model) != NULL) {
			fn_8015BBF8(lbl_8042C1D0->scene, object->model);
		}
		fn_80150958(object->model);
		object->model = NULL;

		dtor_8003C52C(&object->unk30, 0);
		dtor_8005BD3C(&object->unk28, 0);
		dtor_800186D0(&object->base, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}
