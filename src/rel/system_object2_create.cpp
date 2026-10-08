#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// systemObject2Create, the factory rel/system_object2_register.cpp puts in
// the editor record for TObjSystem2.
//
// It is the same 35 instructions in the thirteen stage modules that share the
// engine core. Nine of them have it at the same address; stage13D and stage26D
// to 28D have it elsewhere, so each module's splits.txt names its own range and
// its symbols.txt spells the two data symbols the same way.
//
// The original tests the allocator's result in r0 and copies it to r31 inside
// the branch, which is what a real new-expression of a class with two bases
// and an inline constructor compiles to; rel/sample1_create.cpp has the long
// form. TObjSystem2 adds nothing to its two bases, so the constructor only
// names the class and records the instance size, 0x30.
//
// The PS2 build spells the vtable __vt__11TObjSystem2, which is the name each
// module's symbols.txt gives the table the constructor stores.

extern "C" char* systemObject2ClassName;
extern "C" TObject* lbl_8042C110;

class TObjSystem2 : public TObject, public TObjSetObj
{
public:
	TObjSystem2(TObject* parent)
	    : TObject(parent)
	{
		ClassName = systemObject2ClassName;
		DispTime  = 0x30;
	}
	virtual ~TObjSystem2();
	virtual void Exec();
	virtual void Disp();
};

extern "C" void systemObject2Create(void)
{
	new TObjSystem2(lbl_8042C110);
}
