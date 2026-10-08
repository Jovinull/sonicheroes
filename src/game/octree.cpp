#include "game/octree.h"
// Whole-unit boundary inferred from the correlated C++ function sequence.
// Clear is inlined into the destructor; ten functions survive in GameCube.
struct OctreeAllocator {
	u8 unk_0x00[0x134];
	void* (*allocate)(u32);
	void (*release)(void*);
	u8 unk_0x13C[4];
	void* (*allocateZeroed)(u32, u32);
};
extern "C" OctreeAllocator* lbl_8042C9A4;

typedef char OctreeSize[(sizeof(OCTREE) == 0x18c) ? 1 : -1];
typedef char OctreeNodeSize[(sizeof(ONODE) == 0x20) ? 1 : -1];
typedef char OctreeHeaderSize[(sizeof(OCTREE_FILE_HEADER) == 0x28) ? 1 : -1];
typedef char ColliNodeSize[(sizeof(ColliPolyLinearListNode) == 0x30) ? 1 : -1];

OCTREE::OCTREE(OCTREE_FILE_HEADER* data)
{
	totalMemory  = data->dataSize;
	nodeData     = data->nodeData;
	polygonData  = data->polygonData;
	vertexData   = data->vertexData;
	rootCenter.x = data->rootCenter.x;
	rootCenter.y = data->rootCenter.y;
	rootCenter.z = data->rootCenter.z;
	rootLength   = data->rootLength;
	maxDepth     = data->maxDepth;
	numPolygons  = data->numPolygons;
	numVertices  = data->numVertices;
	numNodes     = data->numNodes;
	((u32*)&rootLength)[0] &= ~0xFFF;
	f32 half                   = 0.5f;
	nodeHalfLengthEachDepth[0] = half * rootLength;
	rootMinPos.x               = rootCenter.x - nodeHalfLengthEachDepth[0];
	rootMinPos.z               = rootCenter.z - nodeHalfLengthEachDepth[0];
	deepestChildLengthRatio    = 1.0f / (f32)(1 << maxDepth);
	for (s32 i = 1; i <= maxDepth; i++)
		nodeHalfLengthEachDepth[i] = half * nodeHalfLengthEachDepth[i - 1];
	polygonFlagBuffSize = numPolygons / 32 + 1;
	u32* polygons       = (u32*)lbl_8042C9A4->allocateZeroed(4, polygonFlagBuffSize);
	polygonFlagBuff     = polygons;
	if (polygons == 0)
		return;
	polyFlagBlock    = 0;
	nodeFlagBuffSize = numNodes / 32 + 1;
	u32* nodes       = (u32*)lbl_8042C9A4->allocateZeroed(4, nodeFlagBuffSize);
	nodeFlagBuff     = nodes;
	if (nodes == 0)
		return;
	nodeFlagBlock      = 0;
	packedOctreeData   = data;
	IntersectionEnable = 1;
}
OCTREE::~OCTREE()
{
	lbl_8042C9A4->release(packedOctreeData);
	packedOctreeData = 0;
	if (polygonFlagBuff) {
		lbl_8042C9A4->release(polygonFlagBuff);
		polygonFlagBuff = 0;
	}
	if (nodeFlagBuff) {
		lbl_8042C9A4->release(nodeFlagBuff);
		nodeFlagBuff = 0;
	}
}
ONODE* OCTREE::GetNodeFromPosition(const RwV3d* point)
{
	ONODE* nodes = nodeData;
	if (nodes == 0)
		return 0;
	u16 childIndex;
	ONODE* node = nodes;
	while ((childIndex = node->childNo) != 0) {
		f32 scale;
		f32 cellSize = nodeHalfLengthEachDepth[node->depth];
		scale        = rootLength * deepestChildLengthRatio;
		f32 maxZ     = rootMinPos.z + ((f32)node->nz * scale + cellSize);
		f32 maxX     = rootMinPos.x + ((f32)node->nx * scale + cellSize);
		u32 child    = (point->x >= maxX) ? 1 : 0;
		if (point->z >= maxZ)
			child |= 2;
		node = &nodes[childIndex + child];
	}
	return node;
}
void OCTREE::GetCenterPosition(const ONODE* node, RwV3d* point)
{
	f32 half   = nodeHalfLengthEachDepth[node->depth];
	f32 length = rootLength * deepestChildLengthRatio;
	point->x   = rootMinPos.x + (half + (f32)node->nx * length);
	point->z   = rootMinPos.z + (half + (f32)node->nz * length);
}
MiniLinearList* AddNode_MiniLinearList(MiniLinearList* next, u16 no)
{
	MiniLinearList* node = (MiniLinearList*)lbl_8042C9A4->allocate(sizeof(MiniLinearList));
	if (node == 0)
		return 0;
	if (next) {
		node->nextNode = next;
		next->prevNode = node;
	} else
		node->nextNode = 0;
	node->prevNode = 0;
	node->no       = no;
	return node;
}
void DeleteNode_MiniLinearList(MiniLinearList* node)
{
	if (node) {
		if (node->prevNode)
			node->prevNode->nextNode = node->nextNode;
		if (node->nextNode)
			node->nextNode->prevNode = node->prevNode;
		lbl_8042C9A4->release(node);
	}
}
ColliPolyLinearList::ColliPolyLinearList()
{
	numNode    = 0;
	bottomNode = 0;
	topNode    = 0;
}
inline void ColliPolyLinearList::Clear()
{
	if (numNode) {
		ColliPolyLinearListNode* previous = 0;
		do {
			ColliPolyLinearListNode* next = 0;
			if (topNode->nextNode) {
				topNode->nextNode->prevNode = previous;
				next                        = topNode->nextNode;
			}
			lbl_8042C9A4->release(topNode);
			topNode = next;
		} while (topNode);
		bottomNode = 0;
		numNode    = 0;
	}
}
ColliPolyLinearList::~ColliPolyLinearList()
{
	Clear();
}
void ColliPolyLinearList::Insert(u16 no, RwV3d* ansVec, RwV3d* coliPos, RwV3d* pushVec, s16* onEdge)
{
	ColliPolyLinearListNode* node = (ColliPolyLinearListNode*)lbl_8042C9A4->allocateZeroed(
	    sizeof(ColliPolyLinearListNode), 1);
	if (node) {
		if (topNode) {
			node->nextNode    = topNode;
			topNode->prevNode = node;
		}
		node->no = no;
		if (ansVec)
			node->ansVec = *ansVec;
		if (coliPos)
			node->coliPos = *coliPos;
		if (pushVec)
			node->pushVec = *pushVec;
		if (onEdge)
			node->on_edge = *onEdge;
		topNode = node;
		if (numNode == 0)
			bottomNode = node;
		numNode++;
	}
}
void ColliPolyLinearList::Delete(ColliPolyLinearListNode* node)
{
	if (node) {
		if (node->prevNode)
			node->prevNode->nextNode = node->nextNode;
		else
			topNode = node->nextNode;
		if (node->nextNode)
			node->nextNode->prevNode = node->prevNode;
		else
			bottomNode = node->prevNode;
		lbl_8042C9A4->release(node);
		numNode--;
	}
}
