// TEnemyPawn_Strategy (the PS2 build's names): the pawn's strategy, a
// TEnemyStrategy<TObjEnemyPawn> whose modes each ask the pawn for an enemy mode
// when they start and may switch the strategy to another mode while they run.

typedef struct RwV3d RwV3d;

namespace nSystem
{
void DecreaseTimer(int& timer);
}

class TObjEnemyPawn
{
public:
	int SearchPlayerForPawn(int show);
	// returns a bool; the strategy tests the whole register
	int CheckDamage();

	u8 unk000[0x24C];
	s8 start; // 0x24C
	u8 unk24D[0xF];
	s32 shotWait; // 0x25C
};

template <class T> class TEnemyStrategy
{
public:
	enum eStrategy {
		STRATEGY_INIT,
		STRATEGY_EXEC,
		STRATEGY_PAUSE,
		STRATEGY_EXIT,
	};

	TEnemyStrategy()
	{
		mMode         = 0;
		mPrevMode     = 0;
		unk0C         = 0;
		mpOwner       = NULL;
		mReqEnemyMode = 0;
	}
	virtual ~TEnemyStrategy() { }
	virtual void Execute(T* owner);
	virtual void ExecStrategyMode(int mode, eStrategy sub) = 0; // 0x10
	virtual int IsReqChangeMode()                          = 0;

	// leaves the current mode and enters the given one
	void InitStrategyMode(int mode)
	{
		mPrevMode = mMode;
		ExecStrategyMode(mMode, STRATEGY_EXIT);
		mMode = mode;
		ExecStrategyMode(mMode, STRATEGY_INIT);
	}

	s32 mMode;         // 0x04
	s32 mPrevMode;     // 0x08
	s32 unk0C;         // 0x0C
	s32 mReqEnemyMode; // 0x10
	T* mpOwner;        // 0x14
};

class TEnemyPawn_Strategy : public TEnemyStrategy<TObjEnemyPawn>
{
public:
	// IsReqChangeMode comes first: it is the key function, so the units that
	// define the constructor or destructor do not emit this class's vtable
	virtual int IsReqChangeMode();
	virtual ~TEnemyPawn_Strategy();
	virtual void ExecStrategyMode(int mode, eStrategy sub);

	TEnemyPawn_Strategy();

	void StrategyMode_Idle(eStrategy sub);
	void StrategyMode_BiteNail(eStrategy sub);
	void StrategyMode_BlowShield(eStrategy sub);
	void StrategyMode_Run(eStrategy sub);
	void StrategyMode_MgunFire(eStrategy sub);
	void StrategyMode_MgunReady(eStrategy sub);
	void StrategyMode_ShotFire(eStrategy sub);
	void StrategyMode_ShotReady(eStrategy sub);
	void StrategyMode_ThunderShoot(eStrategy sub);
	void StrategyMode_Dropped(eStrategy sub);
	void StrategyMode_Tornado(eStrategy sub);
	void StrategyMode_Destroy(eStrategy sub);
	void StrategyMode_Ctrl(eStrategy sub);
	void StrategyMode_WarpOut(eStrategy sub);
	void StrategyMode_WarpHide(eStrategy sub);
	void StrategyMode_HideComeOut(eStrategy sub);
	void StrategyMode_Hide(eStrategy sub);
	void StrategyMode_FallLand(eStrategy sub);
	void StrategyMode_FallDown(eStrategy sub);
	void StrategyMode_FallHide(eStrategy sub);
	void StrategyMode_WanderWalk(eStrategy sub);
	void StrategyMode_WanderTurn(eStrategy sub);
	void StrategyMode_Wander(eStrategy sub);
	void StrategyMode_Turn(eStrategy sub);
	void StrategyMode_Wait(eStrategy sub);
	void StrategyMode_CrouchStand(eStrategy sub);
	void StrategyMode_Crouch(eStrategy sub);

	s32 mTimer; // 0x18

	static void (TEnemyPawn_Strategy::* FuncTbl[27])(eStrategy sub);
};
