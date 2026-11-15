// Raises signal bits 0x8 and 0x10 of a team object (+0x4) and, for each of its members (count
// +0x39, players at +0x114), clears the collision info (C_COLLI at +0x28) and calls the virtual at
// +0x34, then, in a second pass, the virtual at +0x30. HYPOTHESIS: a team pause/reset; the
// virtuals' names are UNKNOWN.
#include "types.h"

struct Header8009C618 {
	u8 pad00[0x18];
};

class C_COLLI
{
public:
	void ClearInfo();
};

// Local view of a player: TObject's nine virtuals, then the two used here.
class Player8009C618 : public Header8009C618
{
public:
	virtual ~Player8009C618();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();
	virtual void UnknownSlot2C();
	virtual void UnknownSlot30();
	virtual void UnknownSlot34();

	u8 pad1C[0x28 - 0x1C];
	C_COLLI colli; // 0x28
};

struct Team8009C618 {
	u8 pad0[4];
	u16 signal; // 0x4
	u8 pad6[0x39 - 0x6];
	s8 count; // 0x39
	u8 pad3A[0x114 - 0x3A];
	Player8009C618* players[3]; // 0x114
};

// Clears the collision info of each member and calls its virtual at +0x34.
static inline void ResetMembers(Team8009C618* team)
{
	int i;

	for (i = 0; i < team->count; i++) {
		Player8009C618* player = team->players[i];

		if (player != NULL) {
			player->colli.ClearInfo();
			player->UnknownSlot34();
		}
	}
}

// Calls the virtual at +0x30 of each member.
static inline void RestartMembers(Team8009C618* team)
{
	int i;

	for (i = 0; i < team->count; i++) {
		if (team->players[i] != NULL) {
			team->players[i]->UnknownSlot30();
		}
	}
}

extern "C" void fn_8009C618(Team8009C618* team)
{
	team->signal |= 0x8;
	team->signal |= 0x10;
	ResetMembers(team);
	RestartMembers(team);
}
