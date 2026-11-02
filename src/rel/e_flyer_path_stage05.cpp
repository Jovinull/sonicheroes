// stage05D's copy of the flyer path (rel/e_flyer_path_stage11.cpp): the same
// unit, with the shared TEnemyStrategy<TObjEnemyFlyer>::Execute hook taken by
// the C++ name the module's rel/flyer_strategy_execute.cpp defines it under.

class TObjEnemyFlyer;

template <class T> class TEnemyStrategy
{
public:
	static void Execute(T* enemy);
};

#define E_FLYER_PATH_FLYER_EXECUTE TEnemyStrategy<TObjEnemyFlyer>::Execute
#include "src/rel/e_flyer_path_stage11.cpp"
