class TEnemyScoreMan
{
public:
	static TEnemyScoreMan* EnemyScoreMan;
	static void CreateInstance();
};

extern "C" TEnemyScoreMan* fn_16_E610()
{
	if (TEnemyScoreMan::EnemyScoreMan == 0) {
		TEnemyScoreMan::CreateInstance();
	}
	return TEnemyScoreMan::EnemyScoreMan;
}
