#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s13BigmovshipCreate, the editor record factory for TObjS13BigShip (the
// class name its constructor stores) in stage13D. It is a real new-expression
// of the class; rel/sample1_create.cpp has the long form of the allocation.
//
// The set data's kind picks a pair of animations for the ship's two parts.
// While the editor is on, a set data with no speed gets 1/60 and one with no
// distance 20. The constructor clears its time, builds both parts through the
// module's loader (fn_9_75A80) and starts each one's animation of the pair
// (fn_9_757C4), keeps the placement's position and, when the first part's
// first atomic has a frame, that frame's world position (fn_8019E8EC). Both
// parts start hidden.
//
// The zero is the module's s02GreenBound0: rel/s02_green_edit.cpp, which has
// the same body as this family's EditOnChange, is placed here too.

struct RwFrame;

// the parts of an RpAtomic and an RwMatrix read here
struct RpAtomic {
	u8 unk00[0x4];
	RwFrame* frame; // 0x04
};

struct BigShipMatrix {
	u8 unk00[0x30];
	RwV3d pos; // 0x30
};

// the set data's parameters
struct S13BigmovshipParams {
	s8 kind; // 0x00
	u8 pad01[0x3];
	f32 speed;    // 0x04
	f32 distance; // 0x08
};

// the animations a kind uses for the two parts
struct S13BigmovshipPair {
	s8 first;  // 0x00
	s8 second; // 0x01
};

extern "C" char* CL_TObjS13BigShip;
extern "C" u32 s13BigmovshipModels[];
extern "C" u8 s13BigmovshipParts[][0x14];
extern "C" S13BigmovshipPair s13BigmovshipPairs[];
extern "C" const f32 s02GreenBound0;
extern "C" const f32 s13BigmovshipDefaultSpeed;
extern "C" const f32 s13BigmovshipDefaultDistance;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75A80(void* info, s32 index, RpClump** clump, s32 flags);
extern "C" void fn_9_757C4(RpClump* clump, void* animation, void* state);
extern "C" BigShipMatrix* fn_8019E8EC(RwFrame* frame);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* after);
void objRpClumpForAllAtomicsToHide(RpClump* clump);

class TObjS13BigShip : public TObject, public TObjSetObj
{
public:
	s8 unk30; // 0x30
	u8 pad31[0x3];
	f32 time;        // 0x34
	u8 state[0x4];   // 0x38
	RwV3d pos;       // 0x3C
	RwV3d worldPos;  // 0x48
	RpClump* clump;  // 0x54
	RpClump* clump2; // 0x58
	u8 pad5C[0x8];

	TObjS13BigShip(TObject* parent)
	    : TObject(parent)
	{
		S13BigmovshipParams* params = (S13BigmovshipParams*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS13BigShip;
		DispTime  = 0x64;

		S13BigmovshipPair* pair = &s13BigmovshipPairs[params->kind];

		if (OnEdit()) {
			if (s02GreenBound0 == params->speed) {
				params->speed = s13BigmovshipDefaultSpeed;
			}
			if (s02GreenBound0 == params->distance) {
				params->distance = s13BigmovshipDefaultDistance;
			}
		}
		time = s02GreenBound0;

		s8 animation = pair->first;

		fn_9_75A80(s13BigmovshipModels, 0, &clump, 0);
		fn_9_757C4(clump, s13BigmovshipParts[animation], state);
		animation = pair->second;
		fn_9_75A80(s13BigmovshipModels, 1, &clump2, 0);
		fn_9_757C4(clump2, s13BigmovshipParts[animation], state);
		pos = ObjParam->setData.pos;
		if (clump != NULL) {
			RpAtomic* atomic = objRpClumpGetAtomic(clump, NULL);

			if (atomic != NULL) {
				RwFrame* frame = atomic->frame;

				if (frame != NULL) {
					worldPos = fn_8019E8EC(frame)->pos;
				}
			}
		}
		objRpClumpForAllAtomicsToHide(clump);
		objRpClumpForAllAtomicsToHide(clump2);
		unk30 = 0;
	}
	virtual ~TObjS13BigShip();
};

extern "C" void s13BigmovshipCreate(void)
{
	new TObjS13BigShip(lbl_8042C110);
}
