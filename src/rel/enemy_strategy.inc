// TEnemyStrategy (the PS2 build's name): an enemy's strategy, which runs one
// strategy mode at a time and passes on the enemy mode the mode asks for.

namespace nSystem
{
void DecreaseTimer(int& timer);
void IncreaseTimer(int& timer);
}

// TObjEnemy's request for a new enemy mode
extern "C" void fn_800A31B8(void* enemy, int mode);

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
		mFirstMode    = 0;
		mpOwner       = NULL;
		mReqEnemyMode = 0;
	}
	virtual ~TEnemyStrategy() { }
	virtual void Execute(T* owner);
	virtual void ExecStrategyMode(int mode, eStrategy sub) = 0; // 0x10
	virtual int IsReqChangeMode()                          = 0;

	// enters the first mode and passes on the enemy mode it asks for
	void StartStrategyMode(int mode)
	{
		mFirstMode    = mode;
		mReqEnemyMode = 0;
		mMode         = mode;
		ExecStrategyMode(mMode, STRATEGY_INIT);
		if (mReqEnemyMode != 0) {
			fn_800A31B8(mpOwner, mReqEnemyMode);
		}
	}

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
	s32 mFirstMode;    // 0x0C
	s32 mReqEnemyMode; // 0x10
	T* mpOwner;        // 0x14
};
