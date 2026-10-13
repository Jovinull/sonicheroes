// TEnemyPawn_Strategy (the PS2 build's names): the pawn's strategy, a
// TEnemyStrategy<TObjEnemyPawn> whose modes each ask the pawn for an enemy mode
// when they start and may switch the strategy to another mode while they run.

#include "src/rel/enemy_strategy.inc"

class TObjEnemyPawn
{
public:
	int SearchPlayerForPawn(int show);
	int CheckHitPoint();
	// returns a bool; the strategy tests the whole register
	int CheckDamage();

	u8 unk000[0x18C];
	u32 state; // 0x18C
	u8 unk190[0xC];
	s32 mode; // 0x19C
	u8 unk1A0[0xA8];
	s32 request; // 0x248
	s8 start;    // 0x24C
	u8 unk24D[0x2];
	s8 shielded; // 0x24F
	u8 unk250[0xC];
	s32 shotWait; // 0x25C
};

extern "C" int fn_800A3ED4(TObjEnemyPawn* enemy);

class TEnemyPawn_Strategy : public TEnemyStrategy<TObjEnemyPawn>
{
public:
	// IsReqChangeMode comes first: it is the key function, so the units that
	// define the constructor or destructor do not emit this class's vtable
	virtual int IsReqChangeMode();
	virtual ~TEnemyPawn_Strategy();
	virtual void ExecStrategyMode(int mode, eStrategy sub);

	TEnemyPawn_Strategy();
	void SetUpFirst(TObjEnemyPawn* owner);

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
