#include "types.h"
#include "dolphin/ar.h"
#include "dolphin/arq.h"
extern "C" {
#include "dolphin/os.h"
}

// GameCube ARAM pool and transfer unit, 0x800D0624-0x800D0B08.
// AramAllocation is a descriptive name: the original name is unknown.
// The allocation/deletion paths preserve native C++ new/delete behavior.
class AramAllocation;
extern "C" {
u32 lbl_8042C488;
AramAllocation* lbl_8042C48C;
volatile s32 lbl_8042C490;
void DCFlushRange(void*, u32);
void fn_800D0750(u32);
}

class AramAllocation
{
public:
	AramAllocation(AramAllocation* previous, u32 bytes)
	{
		if (previous) {
			next = previous->next;
			if (next)
				next->prev = this;
			previous->next = this;
			prev           = previous;
			address        = previous->address + previous->size;
			size           = bytes;
		} else {
			next    = 0;
			prev    = this;
			address = lbl_8042C488;
			size    = bytes;
		}
	}
	~AramAllocation()
	{
		if (lbl_8042C48C == this) {
			prev         = 0;
			next         = 0;
			address      = 0;
			size         = 0;
			lbl_8042C48C = 0;
		} else {
			if (next)
				next->prev = prev;
			else
				lbl_8042C48C->prev = prev;
			prev->next = next;
			next       = 0;
			prev       = 0;
			address    = 0;
			size       = 0;
		}
	}
	AramAllocation* next;
	AramAllocation* prev;
	u32 address, size;
};

extern "C" void fn_800D0624(void* destination, u32 source, u32 bytes)
{
	ARQRequest request;
	DCInvalidateRange(destination, bytes);
	lbl_8042C490 = 0;
	ARQPostRequest(&request, 0, 1, 1, source, (u32)destination, bytes, fn_800D0750);
	DCInvalidateRange(destination, bytes);
	while (lbl_8042C490 != 1) {
	}
	DCInvalidateRange(destination, bytes);
}
extern "C" void fn_800D06C0(void* source, u32 destination, u32 bytes)
{
	ARQRequest request;
	DCFlushRange(source, bytes);
	lbl_8042C490 = 0;
	ARQPostRequest(&request, 0, 0, 1, (u32)source, destination, bytes, fn_800D0750);
	while (lbl_8042C490 != 1) {
	}
	DCInvalidateRange(source, bytes);
}
extern "C" void fn_800D0750(u32)
{
	lbl_8042C490 = 1;
}
extern "C" void fn_800D075C(u32 address)
{
	if (!address)
		return;
	if (!lbl_8042C48C)
		return;
	AramAllocation* p = lbl_8042C48C;
	while (p->address != address || !p->size) {
		p = p->next;
		if (!p)
			return;
	}
	delete p;
}
extern "C" u32 fn_800D082C(u32 bytes)
{
	if (!bytes)
		return 0;
	if (!lbl_8042C48C)
		return 0;
	u32 aligned       = (bytes + 31) & ~31U;
	AramAllocation* p = lbl_8042C48C;
	while (p && p->next) {
		if (p->next->address - (p->address + p->size) >= aligned) {
			return (new AramAllocation(p, aligned))->address;
		}
		p = p->next;
	}
	if (p->address + p->size + bytes <= lbl_8042C488 + 0x600000) {
		return (new AramAllocation(p, aligned))->address;
	}
	return 0;
}
extern "C" void fn_800D09C4()
{
	if (lbl_8042C48C) {
		while (lbl_8042C48C && lbl_8042C48C->prev) {
			delete lbl_8042C48C->prev;
		}
		delete lbl_8042C48C;
	}
	ARFree(0);
}
extern "C" void fn_800D0AA8()
{
	if (!lbl_8042C488)
		lbl_8042C488 = ARAlloc(0x600000);
	lbl_8042C48C = new AramAllocation(0, 0);
}
