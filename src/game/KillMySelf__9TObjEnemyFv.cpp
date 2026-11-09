// Returns 1 when the enemy's TObjSetObj part (+0xB0) is out of range or must be killed, else 0.

extern "C" {
int CheckRangeOut__10TObjSetObjFv(void*);
int CheckMustKill__10TObjSetObjFv(void*);

int KillMySelf__9TObjEnemyFv(unsigned char* o)
{
	if (CheckRangeOut__10TObjSetObjFv(o + 0xb0) != 0
	    || CheckMustKill__10TObjSetObjFv(o + 0xb0) != 0) {
		return 1;
	}
	return 0;
}
}
