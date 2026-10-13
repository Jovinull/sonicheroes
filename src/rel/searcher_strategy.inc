// TEnemySearcher_Strategy and its kinds (the PS2 build's names): the
// searcher's strategy, a TEnemyStrategy<TObjEnemySearcher> whose modes ask the
// searcher for an enemy mode when they start and switch the strategy to
// another mode while they run. Each kind (search light, machine gun, shot,
// bomb, laser, needle) replaces some of the base modes.

#include "src/rel/enemy_strategy.inc"

class TEnemyGadget
{
public:
	// the gadget modes the strategies ask for (the names are ours)
	enum eGadgetMode {
		GADGET_MODE_STOW,
		GADGET_MODE_READY,
		GADGET_MODE_2,
		GADGET_MODE_3,
		GADGET_MODE_4,
	};
};

class TObjEnemySearcher
{
public:
	void Cancel();
	int SearchPlayerForSearcher();
	int SearchPlayerFirst();
	void ReqChangeGadgetMode(TEnemyGadget::eGadgetMode mode);
	void SetUpAimPosition();

	u8 unk000[0x32C];
	s32 readyWait;  // 0x32C
	s32 attackWait; // 0x330
};

// TObjEnemy's check that the target is still in reach
extern "C" int fn_800A6334(TObjEnemySearcher* enemy);

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
