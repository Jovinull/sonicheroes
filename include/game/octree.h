#ifndef GAME_OCTREE_H
#define GAME_OCTREE_H
#include "types.h"
// Recovered names/layouts from PS2 metadata; offsets checked against GameCube.
struct RwV3d {
	f32 x, y, z;
};
struct ONODE {
	u16 nodeNo, parentNo, childNo, neighborNo[4], numPoly;
	u16* polyIndex;
	u16 nx, nz;
	u8 depth, dummy[7];
};
struct POLYDATA {
	u16 vertexIndexNo[3], neighbor[3];
	RwV3d norm;
	u32 attribute;
	u16 groupIndexNo;
	u8 dummy[2];
};
struct OCTREE_FILE_HEADER {
	u32 dataSize;
	ONODE* nodeData;
	POLYDATA* polygonData;
	RwV3d* vertexData;
	RwV3d rootCenter;
	f32 rootLength;
	u16 maxDepth, numPolygons, numVertices, numNodes;
};
struct ColliPolyLinearListNode {
	u16 no;
	s16 on_edge;
	RwV3d ansVec, coliPos, pushVec;
	ColliPolyLinearListNode* prevNode;
	ColliPolyLinearListNode* nextNode;
};
class ColliPolyLinearList
{
public:
	s32 numNode;
	ColliPolyLinearListNode* topNode;
	ColliPolyLinearListNode* bottomNode;
	ColliPolyLinearList();
	~ColliPolyLinearList();
	void Clear();
	void Delete(ColliPolyLinearListNode*);
	void Insert(u16, RwV3d*, RwV3d*, RwV3d*, s16*);
};
struct MiniLinearList {
	u16 no;
	MiniLinearList* prevNode;
	MiniLinearList* nextNode;
};
void DeleteNode_MiniLinearList(MiniLinearList*);
MiniLinearList* AddNode_MiniLinearList(MiniLinearList*, u16);
enum ENUM_CL_MOVING { CL_MOVING_NONE, CL_MOVING_COLLISION, CL_MOVING_INTERSECTION };
class OCTREE
{
public:
	ONODE* nodeData;
	POLYDATA* polygonData;
	RwV3d* vertexData;
	u32* polygonFlagBuff;
	s32 polygonFlagBuffSize;
	u32* nodeFlagBuff;
	s32 nodeFlagBuffSize;
	u32 polyFlagBlock, nodeFlagBlock;
	RwV3d rootCenter, rootMinPos;
	f32 rootLength;
	s32 maxDepth;
	f32 deepestChildLengthRatio;
	s32 numPolygons, numVertices, numNodes;
	f32 nodeHalfLengthEachDepth[16];
	s32 totalMemory, totalMemoryTmp;
	s32 numNodesEachDepth[16], numPolygonsEachDepth[16], numZeroPolyNodesEachDepth[16];
	OCTREE_FILE_HEADER octreeDataForSave;
	void* packedOctreeData;
	s32 IntersectionEnable;
	OCTREE(OCTREE_FILE_HEADER*);
	~OCTREE();
	void GetCenterPosition(const ONODE*, RwV3d*);
	ONODE* GetNodeFromPosition(const RwV3d*);
	s32 CheckPolygonFlag(u16) const;
	s32 CheckNodeFlag(u16) const;
	void SetPolygonFlag(u16);
	void SetNodeFlag(u16);
	s32 GetPolygonNoInTheNode(ONODE*, s32) const;
	void ClearPolygonFlagAll();
	void ClearNodeFlagAll();
	void OmitSameSurfacePolygons(ColliPolyLinearList*);
	ColliPolyLinearList* DetectMovingSphereCollisionWithPolygons(
	    RwV3d*, f32, RwV3d*, ENUM_CL_MOVING*, s32 (*)(POLYDATA*));
	ColliPolyLinearList* DetectSphereCollisionWithPolygons(RwV3d*, f32, s32 (*)(POLYDATA*));
	MiniLinearList* MakeIntersectionNodeListWithCapsule_Sub(
	    MiniLinearList*, const ONODE*, const RwV3d*, const RwV3d*);
	MiniLinearList* MakeIntersectionNodeListWithCapsule(const RwV3d*, const RwV3d*, f32);
	MiniLinearList* MakeIntersectionNodeListWithSmallSphere_Sub(
	    MiniLinearList*, const ONODE*, const RwV3d*, f32, const RwV3d*, const RwV3d*);
	ONODE* GetNextNeighborNode(const ONODE*, const RwV3d*, const RwV3d*, RwV3d*);
	POLYDATA* DetectAxisYCollisionWithPolygons(const RwV3d*, f32, RwV3d*, s32 (*)(POLYDATA*));
	POLYDATA* DetectLineCollisionWithPolygons(
	    const RwV3d*, const RwV3d*, RwV3d*, s32 (*)(POLYDATA*));
};
#endif
