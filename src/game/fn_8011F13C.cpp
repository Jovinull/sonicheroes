#include "types.h"

struct TObjectBase {
	u32 kind;
	u16 flags;
	u8 pad06[2];
	TObjectBase* prev;
	TObjectBase* next;
	TObjectBase* parent;
	TObjectBase* child;
};

struct TObject : TObjectBase {
	virtual void DoSomething(int flag);
};

extern TObject* lbl_8042C6F8;

extern "C" void fn_8011F13C(void)
{
	if (lbl_8042C6F8 != NULL) {
		if (lbl_8042C6F8 != NULL) {
			lbl_8042C6F8->DoSomething(1);
		}
	}
}
