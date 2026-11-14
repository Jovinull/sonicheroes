// Applies a received state message to the player it addresses (HYPOTHESIS): ignores messages from
// the receiver's own player slot (the signed byte selected by its index byte at 0x3A in its 0x110
// table), messages of kind 0x27 and players in state 0x28; otherwise copies the message's three
// words at 0x20, two float triples at 0x2C/0x38, halfword at 0xB4 and byte at 0xE4 into the
// player object lbl_802AD070[slot]. Field names are inferred from this function only.
#include "types.h"

struct Receiver8009A638 {
	u8 pad0[0x3A];
	s8 tableIndex; // 0x3A
	u8 pad3B[0x110 - 0x3B];
	s8 table[1]; // 0x110 (extent UNKNOWN)
};

struct Message8009A638 {
	s32 slot; // 0x0
	u8 pad4[0x20 - 0x4];
	s32 word20; // 0x20
	s32 word24; // 0x24
	s32 word28; // 0x28
	f32 a[3];   // 0x2C
	f32 b[3];   // 0x38
	u8 pad44[0xB0 - 0x44];
	s16 kind; // 0xB0
	u8 padB2[0x2];
	s16 halfB4; // 0xB4
	u8 padB6[0xE4 - 0xB6];
	u8 byteE4; // 0xE4
};

struct Player8009A638 {
	u8 pad0[0x6F0];
	s16 state; // 0x6F0
	u8 pad6F2[0x720 - 0x6F2];
	f32 a[3]; // 0x720
	u8 pad72C[0x738 - 0x72C];
	s32 word738; // 0x738
	s32 word73C; // 0x73C
	s32 word740; // 0x740
	u8 pad744[0x774 - 0x744];
	s16 half774; // 0x774
	u8 pad776[0x7C0 - 0x776];
	f32 b[3]; // 0x7C0
	u8 pad7CC[0x9E9 - 0x7CC];
	u8 byte9E9; // 0x9E9
};

extern "C" {
extern Player8009A638* lbl_802AD070[8];

void fn_8009A638(Receiver8009A638* receiver, Message8009A638* message)
{
	Player8009A638* player;
	s32 slot;

	if (message->slot == (slot = receiver->table[receiver->tableIndex])) {
		return;
	}
	if (message->kind == 0x27) {
		return;
	}
	player = lbl_802AD070[slot];
	switch (player->state) {
		case 0x28:
			return;
		default:
			break;
	}
	player->word738 = message->word20;
	player->word73C = message->word24;
	player->word740 = message->word28;
	player->a[0]    = message->a[0];
	player->a[1]    = message->a[1];
	player->a[2]    = message->a[2];
	player->b[0]    = message->b[0];
	player->b[1]    = message->b[1];
	player->b[2]    = message->b[2];
	player->half774 = message->halfB4;
	player->byte9E9 = message->byteE4;
}
}
