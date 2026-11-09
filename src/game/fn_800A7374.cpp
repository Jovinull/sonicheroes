// Brings up the enemy subsystems (enemy manager, paralysis, ring laser, shock wave, power core, power core manager, score manager).

extern "C" {
void CreateInstance__12TObjEnemyManFv();
void Initialize__15TEnemyParalysisFv();
void Initialize__18TObjEnemyRingLaserFv();
void Initialize__15TEnemyShockWaveFv();
void Initialize__15TEnemyPowerCoreFv();
void CreateInstance__18TEnemyPowerCoreManFv();
void CreateInstance__14TEnemyScoreManFv();
void fn_80137F34();
void fn_8010A018();

void fn_800A7374()
{
	CreateInstance__12TObjEnemyManFv();
	Initialize__15TEnemyParalysisFv();
	Initialize__18TObjEnemyRingLaserFv();
	Initialize__15TEnemyShockWaveFv();
	Initialize__15TEnemyPowerCoreFv();
	CreateInstance__18TEnemyPowerCoreManFv();
	CreateInstance__14TEnemyScoreManFv();
	fn_80137F34();
	fn_8010A018();
}
}
