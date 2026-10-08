#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// sample2Create, the factory that rel/sample2_register.cpp puts in the editor
// record for TObjSample2.
//
// The claim is .text 0x740 to 0x804, the same code at the same address in the
// thirteen stage modules that share the engine core. stage40D is a different
// revision of the source and is left out.
//
// This is the function rel/sample2_object.cpp could not reach with a C
// spelling: the original tests the allocator's result in r0 and copies it to
// r31 only inside the branch. A real new-expression of a class with two bases
// and an inline constructor produces exactly that copy, the same way it does
// for rel/sample1_create.cpp, so the class is written out here as C++ with
// TObject first and TObjSetObj at 0x28.
//
// The PS2 build names the class TObjSample2, with Exec, Disp and a destructor,
// so the vtable each module holds at .data 0xB0 (0xA0 in stage13D) is
// __vt__11TObjSample2. Nothing here defines a virtual function out of line, so
// the compiler references the table without emitting it.
//
// The position and the angle are copied as whole structs, and each assignment
// reads the keyframe pointer again, which is the second load from 0x28.

extern "C" char* sample2ClassName;
extern "C" TObject* lbl_8042C110;

class TObjSample2 : public TObject, public TObjSetObj
{
public:
	RwV3d pos;  // 0x30
	sAngle ang; // 0x3C

	TObjSample2(TObject* parent)
	    : TObject(parent)
	{
		ClassName = sample2ClassName;
		DispTime  = 0x48;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;
	}
	virtual ~TObjSample2();
	virtual void Exec();
	virtual void Disp();
};

extern "C" void sample2Create(void)
{
	new TObjSample2(lbl_8042C110);
}
