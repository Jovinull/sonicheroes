// TObjS13Partition's destructor, out of line. It destroys its clump through
// fn_9_75888, which takes the pointer's address
// (stage13D/o_s13_antenna.cpp calls it the same way), then ends the set
// object when its condition has bit 0x10000 set. The class is shared through
// s13_partition_class.inc, where the destructor is declared after the class's
// first other virtual so this unit does not emit the vtable.

#define S13_PARTITION_CTOR inline
#include "src/rel/s13_partition_class.inc"

extern "C" void fn_9_75888(RpClump** clump);

TObjS13Partition::~TObjS13Partition()
{
	fn_9_75888(&clump);
	if (TstConditionBit(0x10000)) {
		SetEnd();
	}
}
