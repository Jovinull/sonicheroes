// TObjSystem1, shared by rel/system_object1_create.cpp, which defines SYSTEM_OBJECT1_CTOR
// as inline so its factory inlines the constructor, and rel/system_object1_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

extern "C" char* systemObject1ClassName;
extern "C" TObject* lbl_8042C110;

class TObjSystem1 : public TObject, public TObjSetObj
{
public:
	TObjSystem1(TObject* parent);
	// The first virtual declared is the key function, and the unit that defines
	// it emits the vtable. These are all overrides, whose order does not move
	// their slots, so each fragment unit can put first one it does not define:
	// rel/system_object1_exec.cpp (Exec and Disp) declares the destructor first.
#ifdef SYSTEM_OBJECT_DTOR_FIRST
	virtual ~TObjSystem1();
#endif
	virtual void Exec();
#ifndef SYSTEM_OBJECT_DTOR_FIRST
	virtual ~TObjSystem1();
#endif
	virtual void Disp();
};

SYSTEM_OBJECT1_CTOR TObjSystem1::TObjSystem1(TObject* parent)
    : TObject(parent)
{
	ClassName = systemObject1ClassName;
	DispTime  = 0x30;
}
