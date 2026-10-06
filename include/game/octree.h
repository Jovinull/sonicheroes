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
};
#endif
