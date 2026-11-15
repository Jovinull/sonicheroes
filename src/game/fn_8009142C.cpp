#include "types.h"

struct TObjectBase {
	char* ClassName;
	u16 Signal;
	u16 Tag;
	void* Prev;
	void* Next;
	void* Parent;
	void* Child;
};

class Member : public TObjectBase
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();

	virtual void target();
};

struct Team {
	u8 pad0[0x39];
	s8 count;
	u8 pad3A[0x114 - 0x3A];
	Member* members[4];
};

extern "C" void fn_8009142C(Team* team)
{
	Team* p;
	s32 i;

	i = 0;
	p = team;
	for (; i < team->count; i++) {
		Member* m = p->members[0];
		if (m != NULL) {
			m->target();
		}
		p = (Team*)((char*)p + 4);
	}
}
