// TObjSystem4, shared by rel/system_object4_create.cpp, which defines SYSTEM_OBJECT4_CTOR
// as inline so its factory inlines the constructor, and rel/system_object4_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

extern "C" char* systemObject4ClassName;
extern "C" TObject* lbl_8042C110;

class TObjSystem4 : public TObject, public TObjSetObj
{
public:
	TObjSystem4(TObject* parent);
	virtual void Exec();
	virtual ~TObjSystem4();
	virtual void Disp();
};

SYSTEM_OBJECT4_CTOR TObjSystem4::TObjSystem4(TObject* parent)
    : TObject(parent)
{
	ClassName = systemObject4ClassName;
	DispTime  = 0x30;
}
