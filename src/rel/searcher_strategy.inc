// TEnemySearcher_Strategy and its kinds (the PS2 build's names): the
// searcher's strategy, a TEnemyStrategy<TObjEnemySearcher> whose modes ask the
// searcher for an enemy mode when they start and switch the strategy to
// another mode while they run. Each kind (search light, machine gun, shot,
// bomb, laser, needle) replaces some of the base modes.

#include "src/rel/enemy_strategy.inc"

class TEnemyGadget
{
public:
	// as in game/enemy/e_gadget.h
	enum eGadgetMode {
		E_GM_NOACTION,
		E_GM_STANDBY,
		E_GM_PREATTACK,
		E_GM_ATTACK,
		E_GM_POSTATTACK,
	};
};

class TObjEnemySearcher
{
public:
	void Cancel();
	int CheckHitPoint();
	int SearchPlayerForSearcher();
	int SearchPlayerFirst();
	void ReqChangeGadgetMode(TEnemyGadget::eGadgetMode mode);
	void SetUpAimPosition();
	int GetMoveType() { return moveType; }

	u8 unk000[0x18C];
	u32 state; // 0x18C
	u8 unk190[0xC];
	s32 mode; // 0x19C
	u8 unk1A0[0x144];
	s32 request; // 0x2E4
	u8 unk2E8[0x38];
	s32 moveType; // 0x320
	u8 unk324[0x8];
	s32 readyWait;  // 0x32C
	s32 attackWait; // 0x330
};

// TObjEnemy's check that the target is still in reach
extern "C" int fn_800A6334(TObjEnemySearcher* enemy);
// TObjEnemy's check for its destruction; returns a bool, tested whole
extern "C" int fn_800A3ED4(TObjEnemySearcher* enemy);

class TEnemySearcher_Strategy : public TEnemyStrategy<TObjEnemySearcher>
{
public:
	// the destructor comes first: it is the key function, so the units that
	// define only modes do not emit this class's vtable
	virtual ~TEnemySearcher_Strategy();
	virtual void ExecStrategyMode(int mode, eStrategy sub);
	virtual int IsReqChangeMode();
	virtual void StrategyMode_Wait(eStrategy sub);
	virtual void StrategyMode_Walk(eStrategy sub);
	virtual void StrategyMode_Wander(eStrategy sub);
	virtual void StrategyMode_Search(eStrategy sub);
	virtual void StrategyMode_Attack(eStrategy sub);
	virtual void StrategyMode_WalkWithAttack(eStrategy sub);
	virtual void StrategyMode_WanderWithAttack(eStrategy sub);
	virtual void StrategyMode_Tornado(eStrategy sub);
	virtual void StrategyMode_Destroy(eStrategy sub);
	virtual void StrategyMode_Ready(eStrategy sub);
	virtual void StrategyMode_Siren(eStrategy sub);
	virtual void StrategyMode_ThunderShoot(eStrategy sub);
	virtual void StrategyMode_ThunderShootReturn(eStrategy sub);
	virtual void StrategyMode_Idle(eStrategy sub);

	TEnemySearcher_Strategy();
	void SetUpFirst(TObjEnemySearcher* owner);

	s32 mTimer;  // 0x18
	s32 mTimer2; // 0x1C
};

class TEnemySearcher_StrategySearchLight : public TEnemySearcher_Strategy
{
public:
	virtual ~TEnemySearcher_StrategySearchLight();
	virtual void StrategyMode_Wait(eStrategy sub);
	virtual void StrategyMode_Walk(eStrategy sub);
	virtual void StrategyMode_Wander(eStrategy sub);
	virtual void StrategyMode_Attack(eStrategy sub);
	virtual void StrategyMode_Siren(eStrategy sub);

	TEnemySearcher_StrategySearchLight();
};

class TEnemySearcher_StrategyMGun : public TEnemySearcher_Strategy
{
public:
	virtual ~TEnemySearcher_StrategyMGun();
	virtual void StrategyMode_Wait(eStrategy sub);
	virtual void StrategyMode_Walk(eStrategy sub);
	virtual void StrategyMode_Wander(eStrategy sub);
	virtual void StrategyMode_Search(eStrategy sub);
	virtual void StrategyMode_Attack(eStrategy sub);
	virtual void StrategyMode_Ready(eStrategy sub);

	TEnemySearcher_StrategyMGun();
};

class TEnemySearcher_StrategyShot : public TEnemySearcher_Strategy
{
public:
	virtual ~TEnemySearcher_StrategyShot();
	virtual void StrategyMode_Wait(eStrategy sub);
	virtual void StrategyMode_Walk(eStrategy sub);
	virtual void StrategyMode_Wander(eStrategy sub);
	virtual void StrategyMode_Search(eStrategy sub);
	virtual void StrategyMode_Attack(eStrategy sub);
	virtual void StrategyMode_Ready(eStrategy sub);
	virtual void StrategyMode_ThunderShoot(eStrategy sub);

	TEnemySearcher_StrategyShot();
};

class TEnemySearcher_StrategyBomb : public TEnemySearcher_Strategy
{
public:
	// the real destructor is implicit; declared here so that the units with
	// only the modes do not emit this class's vtable
	virtual ~TEnemySearcher_StrategyBomb();
	virtual void StrategyMode_Wait(eStrategy sub);
	virtual void StrategyMode_Walk(eStrategy sub);
	virtual void StrategyMode_Wander(eStrategy sub);
	virtual void StrategyMode_Search(eStrategy sub);
	virtual void StrategyMode_Attack(eStrategy sub);

	TEnemySearcher_StrategyBomb();
};

class TEnemySearcher_StrategyLaser : public TEnemySearcher_Strategy
{
public:
	// the real destructor is implicit; declared here so that the units with
	// only the modes do not emit this class's vtable
	virtual ~TEnemySearcher_StrategyLaser();
	virtual void StrategyMode_Wait(eStrategy sub);
	virtual void StrategyMode_Walk(eStrategy sub);
	virtual void StrategyMode_Wander(eStrategy sub);

	TEnemySearcher_StrategyLaser();
};

class TEnemySearcher_StrategyNeedle : public TEnemySearcher_Strategy
{
public:
	// the real destructor is implicit; declared here so that the units with
	// only the modes do not emit this class's vtable
	virtual ~TEnemySearcher_StrategyNeedle();
	virtual void StrategyMode_Wait(eStrategy sub);
	virtual void StrategyMode_Walk(eStrategy sub);
	virtual void StrategyMode_Wander(eStrategy sub);
	virtual void StrategyMode_Search(eStrategy sub);

	TEnemySearcher_StrategyNeedle();

	s32 mFireTimer; // 0x20
	s32 mFiring;    // 0x24
};
