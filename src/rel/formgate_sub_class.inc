// TObjFormGateSub, shared by rel/formgate_sub_exec.cpp (Exec, which inlines
// CheckLeaderPlayerInGate twice) and rel/formgate_sub_check.cpp (the
// out-of-line copy the module also keeps; FORMGATE_SUB_CHECK_INLINE empty).

#ifndef FORMGATE_SUB_CHECK_INLINE
#define FORMGATE_SUB_CHECK_INLINE inline
#endif

class TObjFormGateSub : public TObject, public C_COLLI
{
public:
	s8 kind; // 0xB0
	u8 padB1[0x3];
	s32 passed; // 0xB4
	f32 offset; // 0xB8

	TObjFormGateSub(TObject* parent, RwV3d* place, sAngle* turn, s8 kind, f32 offset);
	// Disp comes first so that it is the key function: no unit of ours emits
	// the vtable, which stays in each module's data.
	virtual void Disp();
	virtual void Exec();
	virtual ~TObjFormGateSub();
	s32 CheckLeaderPlayerInGate();
	void SetColli(RwV3d* place, sAngle* turn);
	// The collision base without the null test a pointer conversion makes.
	C_COLLI& Colli() { return *this; }
}; // 0xBC

struct FormGateHitter {
	u8 pad000[0x78];
	u32 type; // 0x78
};

struct FormGateHit {
	u8 pad00[0x4];
	FormGateHitter* hitter; // 0x04
};

struct FormGatePlayerInfo {
	s16 state; // 0x00
};

struct FormGatePlayer {
	u8 pad000[0x25C];
	s8 team; // 0x25C
};

extern "C" u8 lbl_8042C1A4[];
extern "C" void* lbl_802AD070[];
extern "C" FormGatePlayerInfo* lbl_802AD090[];
extern "C" FormGatePlayer* lbl_802AD0D0[];
extern "C" void* lbl_80303DC8[];

extern "C" void fn_80021824(void* world);
extern "C" FormGateHit* fn_800211A8(C_COLLI* colli);
extern "C" s32 fn_80041B64(u32 type);
extern "C" s32 fn_80089204(void* player);
extern "C" s32 fn_800892A0(void* player);
extern "C" void fn_80091830(void* team, s32 formation);

static inline FormGateHitter* formgateHitter(FormGateHit* hit)
{
	return hit != NULL ? hit->hitter : NULL;
}

// Moves the collision to a position and angles, keeping the last position.
inline void TObjFormGateSub::SetColli(RwV3d* place, sAngle* turn)
{
	pre_pos      = C_COLLI::pos;
	C_COLLI::pos = *place;
	C_COLLI::ang = *turn;
}

FORMGATE_SUB_CHECK_INLINE s32 TObjFormGateSub::CheckLeaderPlayerInGate()
{
	FormGateHitter* hitter;

	fn_80021824(lbl_8042C1A4);
	while ((hitter = formgateHitter(fn_800211A8(&Colli()))) != NULL) {
		s32 no = fn_80041B64(hitter->type);

		if (fn_80089204(lbl_802AD070[no]) != 0 || fn_800892A0(lbl_802AD070[no]) != 0) {
			if (lbl_802AD090[no]->state != 0x3C && lbl_802AD090[no]->state != 0x3B) {
				return no;
			}
		}
	}
	return -1;
}
