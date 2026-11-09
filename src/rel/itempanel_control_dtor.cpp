#include "types.h"

// TObjItempanelControl's destructor (the PS2 build's name): it clears the
// team's control slot when it is the registered one and deletes the item panel
// instances it still owns, one at a time. The instance's destructor is inline
// here; its unlink from the owner's list is a helper that takes the owner as a
// parameter, which gives the inlined copies the retail register order (a local
// owner makes the list pointers trade r4/r5/r6). The same in the thirteen stage
// modules that share the engine core.

class ItempanelInstance;

typedef struct TObjItempanelControl {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0x14];
	s32 group; // 0x30
	u8 unk34[0x4];
	s32 instanceNum;          // 0x38
	ItempanelInstance* first; // 0x3C
} TObjItempanelControl;

class ItempanelInstance
{
public:
	inline ~ItempanelInstance();

	u8 unk00[0x20];
	TObjItempanelControl* control; // 0x20
	ItempanelInstance* last;       // 0x24
	ItempanelInstance* next;       // 0x28
	s32 counted;                   // 0x2C
};

static inline void itempanelUnlink(ItempanelInstance* self, TObjItempanelControl* owner)
{
	if (owner->first == self) {
		owner->first = self->next;
		if (owner->first != NULL) {
			owner->first->last = self->last;
		}
		self->last = self->next = NULL;
		return;
	}
	if (owner->first->last == self) {
		ItempanelInstance* prev = self->last;

		prev->next         = NULL;
		owner->first->last = prev;
		self->last = self->next = NULL;
		return;
	}
	ItempanelInstance* after;
	ItempanelInstance* prev = self->last;

	after       = self->next;
	prev->next  = after;
	after->last = prev;
	self->last = self->next = NULL;
}

inline ItempanelInstance::~ItempanelInstance()
{
	TObjItempanelControl* owner = control;

	if (counted == 1) {
		owner->instanceNum--;
	}
	itempanelUnlink(this, owner);
}

extern "C" void* lbl_8042C148;
extern "C" TObjItempanelControl* itempanelObjects[];
extern "C" void* __vt__20TObjItempanelControl[];

extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" TObjItempanelControl* __dt__20TObjItempanelControlFv(
    TObjItempanelControl* object, s16 flags)
{
	if (object != NULL) {
		object->vtable = __vt__20TObjItempanelControl;
		if (itempanelObjects[object->group] == object) {
			itempanelObjects[object->group] = NULL;
		}
		while (object->first != NULL) {
			delete object->first;
		}
		__dt__7TObjectFv(object, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
