// TObjSystem3, shared by rel/system_object3_create.cpp, which defines SYSTEM_OBJECT3_CTOR
// as inline so its factory inlines the constructor, and rel/system_object3_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

extern "C" char* systemObject3ClassName;
extern "C" TObject* lbl_8042C110;

class TObjSystem3 : public TObject, public TObjSetObj
{
public:
	TObjSystem3(TObject* parent);
	virtual ~TObjSystem3();
	virtual void Exec();
	virtual void Disp();
};

SYSTEM_OBJECT3_CTOR TObjSystem3::TObjSystem3(TObject* parent)
    : TObject(parent)
{
	ClassName = systemObject3ClassName;
	DispTime  = 0x30;
}
