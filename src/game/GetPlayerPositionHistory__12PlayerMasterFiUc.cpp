// Returns the player's position history entry for the given offset into the ring.
extern "C" {
extern unsigned char lbl_8042C1A8[8];
extern char* lbl_8042C1B0;

char* GetPlayerPositionHistory__12PlayerMasterFiUc(void* self, int a, unsigned char b)
{
	char* base      = lbl_8042C1B0;
	unsigned char t = lbl_8042C1A8[a] - b;
	return base + ((t + (a << 8)) * 0xC);
}
}
