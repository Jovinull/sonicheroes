#ifndef GAME_C_COLLI_REACT_H
#define GAME_C_COLLI_REACT_H
#include "game/pathctrl.h"

enum CCL_REACTION {
	CCL_REACTION_NONE,
	CCL_REACTION_FORCE,
	CCL_REACTION_REALFORCE,
	CCL_REACTION_PUSHPULL,
	NUM_CCL_REACTION
};

class CCL_REACTOR
{
public:
	s32 countReffered;
	CCL_REACTION react;
	RwV3d vecParam;
	sAngle angParam;
	RwV3d vecDirection;

	CCL_REACTOR()
	    : countReffered(0)
	    , react(CCL_REACTION_NONE)
	{
		ClrParameter();
	}
	virtual ~CCL_REACTOR();
	virtual CCL_REACTION React(RwV3d*, sAngle*);
	virtual f32 GetDotProductOfDirection(RwV3d*);
	virtual void SetParameter(RwV3d*, sAngle*);
	virtual void ClrParameter();
	virtual void AddParameter(RwV3d*, sAngle*);
	virtual void GetParameter(RwV3d*, sAngle*);
	virtual void SetDirection(RwV3d* p) { vecDirection = *p; }
	virtual void ClrDirection();
	virtual void GetDirection(RwV3d* p) { *p = vecDirection; }
	s32 CheckReactor(CCL_REACTION type) { return react == type; }
	s32 AddCountReffered() { return ++countReffered; }
	s32 SubCountReffered() { return --countReffered; }
};

class CCL_REACTOR_PUSHPULL : public virtual CCL_REACTOR
{
public:
	CCL_REACTOR_PUSHPULL() { react = CCL_REACTION_PUSHPULL; }
	virtual ~CCL_REACTOR_PUSHPULL();
	virtual void SetParameter(RwV3d*, sAngle*);
	virtual void AddParameter(RwV3d*, sAngle*);
	virtual f32 GetDotProductOfDirection(RwV3d*);
	virtual CCL_REACTION React(RwV3d*, sAngle*);
};
class CCL_REACTOR_TURNTABLE : public virtual CCL_REACTOR
{
public:
	CCL_REACTOR_TURNTABLE() { react = CCL_REACTION_REALFORCE; }
	virtual ~CCL_REACTOR_TURNTABLE();
	virtual void SetParameter(RwV3d*, sAngle*);
	virtual CCL_REACTION React(RwV3d*, sAngle*);
};
class CCL_REACTOR_TRANSROTS : public virtual CCL_REACTOR
{
public:
	CCL_REACTOR_TRANSROTS() { react = CCL_REACTION_REALFORCE; }
	virtual ~CCL_REACTOR_TRANSROTS();
	virtual void SetParameter(RwV3d*, sAngle*);
	virtual CCL_REACTION React(RwV3d*, sAngle*);
};
class CCL_REACTOR_TRANS : public virtual CCL_REACTOR
{
public:
	CCL_REACTOR_TRANS() { react = CCL_REACTION_FORCE; }
	virtual ~CCL_REACTOR_TRANS();
	virtual void SetParameter(RwV3d*, sAngle*);
	virtual CCL_REACTION React(RwV3d*, sAngle*);
};
struct CCL_INFO {
	u8 kind, form, push, damage;
	u32 attr;
	RwV3d center;
	f32 a, b, c;
	CCL_REACTOR* pReactor;
	s32 angx, angy, angz;
};
CCL_REACTOR_PUSHPULL* Construct_CCL_REACTOR_PUSHPULL(CCL_INFO*);
s32 Construct_CCL_REACTOR_TURNTABLE(CCL_INFO*);
s32 Construct_CCL_REACTOR_TRANSROTS(CCL_INFO*);
s32 Construct_CCL_REACTOR_TRANS(CCL_INFO*);
s32 Destruct_CCL_REACTOR(CCL_INFO*);
#endif
