// Shuts down the enemy subsystems (score manager, power core, shock wave, ring laser, paralysis, enemy manager).

extern "C" {
void fn_80109FF0();
void DeleteInstance__14TEnemyScoreManFv();
void DeleteInstance__18TEnemyPowerCoreManFv();
void Finalize__15TEnemyPowerCoreFv();
void Finalize__15TEnemyShockWaveFv();
void Finalize__18TObjEnemyRingLaserFv();
void Finalize__15TEnemyParalysisFv();
void DestroyInstance__12TObjEnemyManFv();

void fn_800A7338()
{
	fn_80109FF0();
	DeleteInstance__14TEnemyScoreManFv();
	DeleteInstance__18TEnemyPowerCoreManFv();
	Finalize__15TEnemyPowerCoreFv();
	Finalize__15TEnemyShockWaveFv();
	Finalize__18TObjEnemyRingLaserFv();
	Finalize__15TEnemyParalysisFv();
	DestroyInstance__12TObjEnemyManFv();
}
}
