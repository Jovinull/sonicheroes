// stage07D's and stage13D's copy of the egg mobile strategy
// (rel/e_eggmobile_strategy_stage11.cpp): the same unit, with the shared
// TEnemyStrategy<TObjEnemyCapture>::Execute hook taken by its C++ name, the
// name those modules' capture units define it under.

class TObjEnemyCapture;

template <class T> class TEnemyStrategy
{
public:
	static void Execute(T* enemy);
};

#define E_EGGMOBILE_CAPTURE_EXECUTE TEnemyStrategy<TObjEnemyCapture>::Execute
#include "src/rel/e_eggmobile_strategy_stage11.cpp"
