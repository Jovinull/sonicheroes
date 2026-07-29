typedef unsigned int u32;

struct RwFrame;
struct RpClump;
struct RpSkin;
struct RpHAnimHierarchy;

struct RwFrame {
	unsigned char pad[0x10];
};

struct RpAtomic {
	unsigned char pad[0x18];
	void* geometry;
};

struct RpHAnimNodeInfo {
	int nodeID;
	unsigned char pad[8];
	RwFrame* frame;
};

struct RpHAnimHierarchy {
	unsigned char pad0[4];
	int numNodes;
	unsigned char pad8[8];
	RpHAnimNodeInfo* nodeInfo;
};

struct RtAnimAnimation {
	unsigned char pad[0xC];
	float duration;
};

struct DANIM_KEY {
	int first;
	int last;
	float start;
	float end;
};

extern "C" {
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpSkin* fn_80226468(void*);
RpHAnimHierarchy* fn_80226454(RpAtomic*);
RpAtomic* fn_80226440(RpAtomic*, RpHAnimHierarchy*);
RwFrame* fn_8013F484(RwFrame*);
RwFrame* fn_8019EB10(RwFrame*, RwFrame* (*)(RwFrame*, void*), void*);
}

class HAnimClass
{
public:
	HAnimClass();
	~HAnimClass();

	RwFrame* SearchNodeFrameFromNodeID(RpHAnimHierarchy*, int);
	float GetHAnimKeyList(DANIM_KEY*, int, RtAnimAnimation*);
	void GetSkinHierarchy(RpClump*, RpHAnimHierarchy*);
	void SetHierarchyForAtomic(RpClump*, RpHAnimHierarchy*);
	RpHAnimHierarchy* GetHierarchy(RpClump*);

private:
	unsigned char pad[8];
};

extern "C" RpAtomic* getSkinHierarchy(RpAtomic*, void*);
extern "C" RpAtomic* setHierarchyForSkinAtomic(RpAtomic*, void*);
extern "C" RwFrame* getChildFrameHierarchy(RwFrame*, void*);

RwFrame* HAnimClass::SearchNodeFrameFromNodeID(RpHAnimHierarchy* hierarchy, int nodeID)
{
	int found = -1;

	for (int i = 0; i < hierarchy->numNodes; ++i) {
		if (hierarchy->nodeInfo[i].nodeID == nodeID) {
			found = i;
			break;
		}
	}

	if (found == -1) {
		return 0;
	}
	return hierarchy->nodeInfo[found].frame;
}

float HAnimClass::GetHAnimKeyList(DANIM_KEY* keys, int count, RtAnimAnimation* animation)
{
	for (int i = 0; i < count; ++i) {
		if (keys[i].first == -1) {
			keys[i].first = 60.0f * animation->duration;
		}
		if (keys[i].last == -1) {
			keys[i].last = 60.0f * animation->duration;
		}

		keys[i].start = keys[i].first * (1.0f / 60.0f);
		keys[i].end   = keys[i].last * (1.0f / 60.0f) - 0.00001f;
	}
	return animation->duration;
}

void HAnimClass::GetSkinHierarchy(RpClump* clump, RpHAnimHierarchy* hierarchy)
{
	fn_8014FFBC(clump, getSkinHierarchy, &hierarchy);
}

extern "C" RpAtomic* getSkinHierarchy(RpAtomic* atomic, void* data)
{
	RpHAnimHierarchy** hierarchy = (RpHAnimHierarchy**)data;

	if (fn_80226468(atomic->geometry) != 0) {
		*hierarchy = fn_80226454(atomic);
	}
	return atomic;
}

void HAnimClass::SetHierarchyForAtomic(RpClump* clump, RpHAnimHierarchy* hierarchy)
{
	fn_8014FFBC(clump, setHierarchyForSkinAtomic, hierarchy);
}

extern "C" RpAtomic* setHierarchyForSkinAtomic(RpAtomic* atomic, void* data)
{
	if (fn_80226468(atomic->geometry) != 0) {
		fn_80226440(atomic, (RpHAnimHierarchy*)data);
	}
	return atomic;
}

RpHAnimHierarchy* HAnimClass::GetHierarchy(RpClump* clump)
{
	RwFrame* frame = 0;
	frame          = fn_8013F484(*(RwFrame**)((unsigned char*)clump + 4));

	if (frame == 0) {
		fn_8019EB10(*(RwFrame**)((unsigned char*)clump + 4), getChildFrameHierarchy, &frame);
	}
	return (RpHAnimHierarchy*)frame;
}

extern "C" RwFrame* getChildFrameHierarchy(RwFrame* frame, void* data)
{
	RwFrame* child = fn_8013F484(frame);
	if (child == 0) {
		fn_8019EB10(frame, getChildFrameHierarchy, data);
		return frame;
	}

	*(RwFrame**)data = child;
	return 0;
}

HAnimClass::~HAnimClass() { }

HAnimClass::HAnimClass() { }

HAnimClass HAnim;
