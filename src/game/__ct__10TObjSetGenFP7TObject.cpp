// TObjSetGen::TObjSetGen(TObject*) (the mangled name is CORROBORATED by the PS2 build; the class
// name string it installs is "TObjSetGen"). Builds the TObject and TObjSetObj bases, installs the
// class name and the object size (+0x1E, as the other TObject constructors do), clears
// lbl_8042C284 and the word +0xA34. Field roles are UNKNOWN.
#include "types.h"
#include "game/setObj.h"

class TObject;

struct TObjectBase {
	char* ClassName;
	u16 Signal, Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
};

class TObject : public TObjectBase
{
public:
	TObject(TObject* parent);
	virtual ~TObject();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
};

// Local view; the destructor is not defined here, so this unit does not emit the vtable.
class TObjSetGen : public TObject, public TObjSetObj
{
public:
	TObjSetGen(TObject* parent);
	virtual ~TObjSetGen();

	u8 unknown30[0xA34 - 0x30];
	s32 unknownA34; // 0xA34
	u8 unknownA38[0xA54 - 0xA38];
};

extern "C" {
extern char* lbl_8042B220; // -> "TObjSetGen"
extern s32 lbl_8042C284;
}

TObjSetGen::TObjSetGen(TObject* parent)
    : TObject(parent)
{
	ClassName    = lbl_8042B220;
	DispTime     = sizeof(*this);
	lbl_8042C284 = 0;
	unknownA34   = 0;
}
