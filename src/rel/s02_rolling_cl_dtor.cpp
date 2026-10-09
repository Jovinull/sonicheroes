// TObjS02Rolling_CL's destructor, out of line. Placed in the editor (OnEdit),
// it walks the set objects of its communication group, the list at +0x30 of
// lbl_8042C298 indexed by its communicateId, and clears its bit in the work
// byte of each object of kind 0x204. It then ends the set object when its
// condition has bit 0x10000 set. The work pointer is read through the entry
// each time: a local for it trades the walk's registers (r4 and r5). The
// class is shared through s02_rolling_cl_class.inc, where the destructor is
// declared after the class's first other virtual so this unit does not emit
// the vtable.

#define S02_ROLLING_CL_CTOR inline
#include "src/rel/s02_rolling_cl_class.inc"

// The set-object lists lbl_8042C298 points to, one per communication group.
struct SetObjLists {
	u8 unk0[0x30];
	SETOBJ_PARAM* list[1]; // 0x30
};

extern "C" SetObjLists* lbl_8042C298;

TObjS02Rolling_CL::~TObjS02Rolling_CL()
{
	if (OnEdit()) {
		SETOBJ_PARAM* p = lbl_8042C298->list[ObjParam->setData.communicateId];

		if (p != NULL) {
			while (p != NULL) {
				if (p->setData.uniqueId == 0x204) {
					if (p->originalWork != NULL) {
						*(u8*)p->originalWork &= ~bit;
					}
				}
				p = p->next;
			}
		}
	}
	if (TstConditionBit(0x10000)) {
		SetEnd();
	}
}
