#include "types.h"

// Destructor (HYPOTHESIS; the class name is UNKNOWN): installs the class vtable lbl_80289C38,
// deletes the task object at 0x50 until none is left (each deletion is expected to replace the
// pointer with the next one, through the virtual destructor), runs the TObject destructor and frees
// the object on the game heap when the delete flag is positive. Returns the object.

class TObject;

struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
};

// Local view of TObject: only the virtual destructor is used here.
class TObject : public TObjectBase
{
public:
	virtual ~TObject();
};

struct THeapCtrl {
	void Free(void* p);
};

struct Obj8012226C {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x50 - 0x1C];
	TObject* f50; // 0x50
};

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern u8 lbl_80289C38[];
void __dt__7TObjectFv(void* object, s16 flags);

Obj8012226C* fn_8012226C(Obj8012226C* o, s16 flags)
{
	if (o != NULL) {
		o->vtable = lbl_80289C38;
		while (o->f50 != NULL) {
			delete o->f50;
		}
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			lbl_8042C148->Free(o);
		}
	}
	return o;
}
}
