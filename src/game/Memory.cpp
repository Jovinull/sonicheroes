typedef unsigned char u8;
typedef unsigned int u32;

struct sHeap {
	sHeap* Next;
	u32 Size;
};

struct THeapCtrl {
	sHeap* HeapTop;
	u32 HeapSize;
	u32 Boundary;

	THeapCtrl(u32 size, u32 boundary);
	~THeapCtrl();
	void Free(void* address);
	void* Malloc(u32 size);
	static void operator delete(void* address);
	static void* operator new(unsigned long size);
};

struct MemoryAllocator {
	u8 pad[308];
	void* (*Alloc)(u32 size);
	void (*Free)(void* address);
};

extern MemoryAllocator* lbl_8042C9A4;
extern "C" void* memset(void* destination, int value, unsigned long size);

#pragma opt_common_subs off
void THeapCtrl::Free(void* address)
{
	if (address == 0)
		return;

	sHeap* prev = HeapTop;
	sHeap* next;
	while ((next = prev->Next) < (sHeap*)((u32)address - sizeof(sHeap)))
		prev = next;

	if ((char*)((sHeap*)address - 1) + ((sHeap*)address - 1)->Size == (char*)next) {
		((sHeap*)address)[-1].Next = next->Next;
		((sHeap*)address)[-1].Size += next->Size;
	} else {
		((sHeap*)address)[-1].Next = next;
	}

	if ((char*)prev + prev->Size == (char*)((sHeap*)address - 1)) {
		prev->Next = ((sHeap*)address)[-1].Next;
		prev->Size += ((sHeap*)address)[-1].Size;
	} else {
		prev->Next = (sHeap*)address - 1;
	}
}
#pragma opt_common_subs reset

void* THeapCtrl::Malloc(u32 size)
{
	size = Boundary + size;
	size += 7;
	size &= -Boundary;
	sHeap* prev = HeapTop;
	sHeap* current;

	while ((current = prev->Next) != 0) {
		if (current->Size >= size) {
			if (size == current->Size) {
				prev->Next = current->Next;
			} else {
				sHeap* next   = (sHeap*)((char*)current + size);
				next->Next    = current->Next;
				next->Size    = current->Size - size;
				current->Size = size;
				prev->Next    = next;
			}
			return current + 1;
		}
		prev = current;
	}
	return 0;
}

void THeapCtrl::operator delete(void* address)
{
	lbl_8042C9A4->Free(address);
}

THeapCtrl::~THeapCtrl()
{
	lbl_8042C9A4->Free(HeapTop);
}

THeapCtrl::THeapCtrl(u32 size, u32 boundary)
{
	Boundary = boundary;
	HeapTop  = (sHeap*)lbl_8042C9A4->Alloc(size);
	if (HeapTop != 0) {
		memset(HeapTop, 0, size);
		sHeap* next   = HeapTop + 1;
		HeapTop->Next = next;
		HeapTop->Size = 0;
		next->Next    = 0;
		next->Size    = size - sizeof(sHeap);
	}
}

void* THeapCtrl::operator new(unsigned long size)
{
	return lbl_8042C9A4->Alloc(size);
}
