typedef int s32;

extern "C" {
void fn_800421C8(void*, void*);
void fn_80042310(void*, void*);
void fn_800A7614();
void fn_800A75E0();

extern unsigned char lbl_8042C1C0;
extern unsigned char lbl_8042BC80;
}

struct MOVIE_LIST {
	const char* filename;
	s32 eventNumber;
	s32 width;
	s32 height;
	s32 unknown;
	s32 loop;
};

class MOVIE_PLAY
{
public:
	s32 EventNumber2MovieNumber(s32 eventNumber);
	s32 MovieNumber2EventNumber(s32 movieNumber);

	void Loop();
	void End();
	void Init();

	static MOVIE_LIST MovieLists[29];

	void (*init)();
	void (*end)();
	void (*loop)();
	s32 currentMovie;
	s32 state;
};

MOVIE_LIST MOVIE_PLAY::MovieLists[29] = {
	{ "E0000_GC.sfd", 0, 640, 448, 0, 0 },
	{ "E0004_GC.sfd", 4, 640, 448, 0, 0 },
	{ "E0009_GC.sfd", 9, 640, 448, 0, 0 },
	{ "E0012_GC.sfd", 12, 640, 448, 0, 0 },
	{ "E0017_GC.sfd", 17, 640, 448, 0, 1 },
	{ "E0100_GC.sfd", 100, 640, 448, 0, 0 },
	{ "E0104_GC.sfd", 104, 640, 448, 0, 0 },
	{ "E0109_GC.sfd", 109, 640, 448, 0, 0 },
	{ "E0012_GC.sfd", 12, 640, 448, 0, 0 },
	{ "E0117_GC.sfd", 117, 640, 448, 0, 1 },
	{ "E0200_GC.sfd", 200, 640, 448, 0, 0 },
	{ "E0004_GC.sfd", 4, 640, 448, 0, 0 },
	{ "E0209_GC.sfd", 209, 640, 448, 0, 0 },
	{ "E0212_GC.sfd", 212, 640, 448, 0, 0 },
	{ "E0217_GC.sfd", 217, 640, 448, 0, 1 },
	{ "E0300_GC.sfd", 300, 640, 448, 0, 0 },
	{ "E0104_GC.sfd", 104, 640, 448, 0, 0 },
	{ "E0309_GC.sfd", 309, 640, 448, 0, 0 },
	{ "E0212_GC.sfd", 212, 640, 448, 0, 0 },
	{ "E0317_GC.sfd", 317, 640, 448, 0, 1 },
	{ "E0400_GC.sfd", 400, 640, 448, 0, 0 },
	{ "E0401_GC.sfd", 401, 640, 448, 0, 0 },
	{ "E0402_GC.sfd", 402, 640, 448, 0, 0 },
	{ "E0403_GC.sfd", 403, 640, 448, 0, 0 },
	{ "E0404_GC.sfd", 404, 640, 448, 0, 1 },
	{ "S1_Eng_GC.sfd", -1, 0, 0, 1, 0 },
	{ "S1_Jp_GC.sfd", -1, 0, 0, 1, 0 },
	{ "TGS_GCj.sfd", -1, 0, 0, 1, 0 },
	{ "TGS_GCe.sfd", -1, 0, 0, 1, 0 },
};

MOVIE_PLAY MoviePlay = { 0, 0, 0, 0, 0 };

s32 MOVIE_PLAY::EventNumber2MovieNumber(s32 eventNumber)
{
	for (s32 i = 0; i < 29; ++i) {
		if (MovieLists[i].eventNumber == eventNumber) {
			return i;
		}
	}
	return -1;
}

s32 MOVIE_PLAY::MovieNumber2EventNumber(s32 movieNumber)
{
	return MovieLists[movieNumber].eventNumber;
}

void MOVIE_PLAY::Loop()
{
	MoviePlay.loop();
}

void MOVIE_PLAY::End()
{
	MoviePlay.end();
	fn_800421C8(&lbl_8042C1C0, &lbl_8042BC80);
	fn_800A7614();

	MoviePlay.init         = 0;
	MoviePlay.end          = 0;
	MoviePlay.loop         = 0;
	MoviePlay.currentMovie = 0;
	MoviePlay.state        = 0;
}

void MOVIE_PLAY::Init()
{
	loop = 0;
	fn_80042310(&lbl_8042C1C0, &lbl_8042BC80);
	fn_800A75E0();
	MoviePlay.init();
}
