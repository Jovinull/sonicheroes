#include "game/link.h"

// link.cpp: C++ class names, layout and methods corroborated by PS2 DWARF.
// GameCube complete surviving text: 0x800D03A0-0x800D0624.
CLASS_LINK* CLASS_LINK_MANAGER::UnlinkClass(CLASS_LINK* pClass)
{
	CLASS_LINK* pLast;
	CLASS_LINK* pNext;
	if (pHead == pClass) {
		pHead = pHead->pNext;
		if (pHead) {
			pHead->pLast = pTail;
		} else {
			pTail = 0;
		}
	} else if (pTail == pClass) {
		pTail        = pTail->pLast;
		pTail->pNext = 0;
		pHead->pLast = pTail;
	} else {
		pLast = pClass->GetLastPointer();
		pNext = pClass->GetNextPointer();
		pLast->SetNextPointer(pNext);
		pNext->SetLastPointer(pLast);
	}
	pClass->SetNextPointer(0);
	pClass->SetLastPointer(0);
	pClass->pManager = 0;
	return pClass;
}

CLASS_LINK* CLASS_LINK_MANAGER::LinkClass(CLASS_LINK* pClass)
{
	if (!pHead) {
		pHead = pClass;
		pTail = pClass;
		pClass->SetNextPointer(0);
		pClass->SetLastPointer(pClass);
	} else {
		pTail->pNext = pClass;
		pHead->pLast = pClass;
		pClass->SetNextPointer(0);
		pClass->SetLastPointer(pTail);
		pTail = pClass;
	}
	pClass->pManager = this;
	return pClass;
}

CLASS_LINK_MANAGER::~CLASS_LINK_MANAGER()
{
	while (pHead) {
		UnlinkClass(pHead);
	}
}

CLASS_LINK_MANAGER::CLASS_LINK_MANAGER()
{
	pCurrent = 0;
	pTail    = 0;
	pHead    = 0;
}

CLASS_LINK::~CLASS_LINK()
{
	if (pManager) {
		pManager->UnlinkClass(this);
	}
	pManager = 0;
	pNext    = 0;
	pLast    = 0;
}

CLASS_LINK::CLASS_LINK()
{
	pManager = 0;
	pNext    = 0;
	pLast    = 0;
}
