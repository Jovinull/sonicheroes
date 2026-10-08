#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s31bobObjectdummyCreate, the factory the editor record for TObjS31Bob points
// at.
//
// It is the same 35 instructions in twelve of the stage modules that share the
// engine core, at a different address in each, so each module's splits.txt
// names its own range. stage13D does not carry the class.
//
// The class name the constructor stores is the module's "TObjS31Bob", and the
// PS2 build spells the vtable __vt__10TObjS31Bob; each module's symbols.txt uses
// those two names for the table and the pointer to the string.
//
// The original tests the allocator's result in r0 and copies it to r31 inside
// the branch, which is what a real new-expression of a class with two bases
// and an inline constructor compiles to; rel/sample1_create.cpp has the long
// form. Like the four system objects, this class adds nothing to its two bases
// at construction, so the constructor only names the class and records the
// instance size, 0x30.

extern "C" char* s31bobObjectdummyClassName;
extern "C" TObject* lbl_8042C110;

class TObjS31Bob : public TObject, public TObjSetObj
{
public:
	TObjS31Bob(TObject* parent)
	    : TObject(parent)
	{
		ClassName = s31bobObjectdummyClassName;
		DispTime  = 0x30;
	}
	virtual ~TObjS31Bob();
	virtual void Exec();
	virtual void Disp();
};

extern "C" void s31bobObjectdummyCreate(void)
{
	new TObjS31Bob(lbl_8042C110);
}
