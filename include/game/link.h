#ifndef GAME_LINK_H
#define GAME_LINK_H

class CLASS_LINK_MANAGER;

class CLASS_LINK
{
public:
	CLASS_LINK();
	~CLASS_LINK();
	CLASS_LINK* GetLastPointer() { return pLast; }
	CLASS_LINK* GetNextPointer() { return pNext; }
	void SetLastPointer(CLASS_LINK* p) { pLast = p; }
	void SetNextPointer(CLASS_LINK* p) { pNext = p; }
	CLASS_LINK_MANAGER* pManager;
	CLASS_LINK* pLast;
	CLASS_LINK* pNext;
	void* pData;
};

class CLASS_LINK_MANAGER
{
public:
	CLASS_LINK_MANAGER();
	~CLASS_LINK_MANAGER();
	CLASS_LINK* UnlinkClass(CLASS_LINK*);
	CLASS_LINK* LinkClass(CLASS_LINK*);
	CLASS_LINK* pHead;
	CLASS_LINK* pTail;
	CLASS_LINK* pCurrent;
};

#endif
