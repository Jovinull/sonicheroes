#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// sample1Create, the factory that rel/sample1_register.cpp puts in the editor
// record for TObjSample.
//
// The claim is .text 0x3E0 to 0x494, the same code at the same address in the
// thirteen stage modules that share the engine core. stage40D is a different
// revision of the source and is left out.
//
// rel/sample1_object.cpp stops short of this function because a plain C
// spelling, an allocation followed by an if and the constructor's stores, never
// produced the extra copy the original makes: the allocator's result goes to r0,
// is tested there, and only then moves to r31. That copy is what a real
// new-expression of a class with two bases and an inline constructor compiles
// to, so this is written as one. The second base, TObjSetObj at 0x28, is why
// there are two vtable stores, the class's own vtable and the same table 0x2C
// further in.
//
// The PS2 build names the class TObjSample and gives it Exec, Disp and a
// destructor, so the vtable each module holds at .data 0x50 (0x40 in stage13D)
// is __vt__10TObjSample. Nothing here defines a virtual function out of line, so
// the compiler references the table without emitting it.
//
// angle and timer are cleared by two statements. Chaining them as one
// assignment loads the zero once but stores timer first.

extern "C" char* sample1Defaults;
extern "C" TObject* lbl_8042C110;

class TObjSample : public TObject, public TObjSetObj
{
public:
	RwV3d pos; // 0x30
	s32 angle; // 0x3C
	s32 timer; // 0x40

	TObjSample(TObject* parent)
	    : TObject(parent)
	{
		ClassName = sample1Defaults;
		DispTime  = 0x44;

		SETDATA_PARAM* data = &ObjParam->setData;

		pos.x = data->pos.x;
		pos.y = data->pos.y;
		pos.z = data->pos.z;

		angle = 0;
		timer = 0;
	}
	virtual ~TObjSample();
	virtual void Exec();
	virtual void Disp();
};

extern "C" void sample1Create(void)
{
	new TObjSample(lbl_8042C110);
}
