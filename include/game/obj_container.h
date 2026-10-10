#ifndef GAME_OBJ_CONTAINER_H
#define GAME_OBJ_CONTAINER_H
#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// TObjContainer, the breakable crate base the wood, iron and unbreakable
// containers derive from. The PS2 build keeps it in one class; the GameCube
// stage modules derive one class per material, each with its own vtable and
// class name, and inline their constructors into the factories.
//
// The constructor and SetPosition are out of line in each module's run, and the
// factories reach them by these names. Fields are named where the factories
// and the constructor show what they hold.
class TObjContainer : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 material;     // 0xB8: 1 iron, 2 unbreakable
	s32 unkBC;        // 0xBC
	s8 kind;          // 0xC0: the placement's first parameter
	u8 unkC1;         // 0xC1
	u16 unkC2;        // 0xC2
	RwV3d pos;        // 0xC4
	sAngle ang;       // 0xD0
	f32 unkDC;        // 0xDC
	f32 height;       // 0xE0
	RpClump* clump;   // 0xE4
	void* pieces;     // 0xE8: the debris models the module loads
	s32 unkEC;        // 0xEC
	void* pieceTable; // 0xF0: name and count of each kind of debris
	s16 pieceKinds;   // 0xF4

	TObjContainer(TObject* parent);
	void SetOriginalCColli();
	void SetFallingCColli();
	s32 CheckGround();
	s32 CheckPiled();
	s32 CheckBreak_Sub(int type);
	void Broken(int breaker);
	void SetPosition();
	void SetParameter();
	// Exec first: it is the key function and no unit defines it yet, so the
	// units that define the others do not emit the vtable.
	virtual void Exec();
	virtual ~TObjContainer();
	virtual void Disp();
	// The class's own virtuals, after the second base's slots (PS2 names).
	virtual s32 CheckBreak();
	virtual void BrokenSE();
	virtual void EditOnChange(SETDATA_PARAM*);
};

// TObjBobcontainer, the bobsleigh course's crate base. It has the container's
// layout field for field and its own copies of the methods; the unbreakable
// one derives from it the way the plain containers derive from TObjContainer.
class TObjBobcontainer : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 material;     // 0xB8
	s32 unkBC;        // 0xBC
	s8 kind;          // 0xC0: the placement's first parameter
	u8 unkC1;         // 0xC1
	u16 unkC2;        // 0xC2
	RwV3d pos;        // 0xC4
	sAngle ang;       // 0xD0
	f32 unkDC;        // 0xDC
	s32 unkE0;        // 0xE0
	RpClump* clump;   // 0xE4
	void* pieces;     // 0xE8
	s32 unkEC;        // 0xEC
	void* pieceTable; // 0xF0
	s16 pieceKinds;   // 0xF4

	TObjBobcontainer(TObject* parent);
	void SetPosition();
	void SetParameter();
	// Exec first: it is the key function and no unit defines it yet, so the
	// units that define the others do not emit the vtable.
	virtual void Exec();
	virtual ~TObjBobcontainer();
	virtual void Disp();
	// The class's own virtuals, after the second base's slots (PS2 names).
	virtual s32 CheckBreak();
	virtual void BrokenSE();
	virtual void EditOnChange(SETDATA_PARAM*);
};

#endif
