typedef unsigned char u8;
typedef signed char s8;
typedef int s32;

struct PlayerWork {
	u8 pad000[0x25E];
	s8 team; // 0x25E
};

extern "C" {
u8* GetGamePeriPtr(s32 port);
s32 fn_16_57BAC(s32);
extern PlayerWork* lbl_802AD0D0[];

void fn_16_4CBCC(s32 arg0)
{
	s32 idx = fn_16_57BAC(arg0);
	PlayerWork* player;

	if (idx < 0) {
		for (;;) {
		}
	}
	player = lbl_802AD0D0[idx];
	if (player == 0) {
		for (;;) {
		}
	}
	GetGamePeriPtr(player->team);
}
}
