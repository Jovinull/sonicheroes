// Loads a stage octree file: reads `name` (fn_800426E0), turns the header's node, polygon and
// vertex offsets into pointers, builds an OCTREE from it and registers it with `owner`
// (fn_8004B6DC, with the node data and the header), then calls fn_80112718. Returns the octree, or
// null when the file is missing. HYPOTHESIS: the roles of the three helpers are UNKNOWN.
#include "game/octree.h"

extern "C" {
OCTREE_FILE_HEADER* fn_800426E0(char* name, s32 flags);
void fn_8004B6DC(void* owner, OCTREE* tree, ONODE* nodes, OCTREE_FILE_HEADER* header);
void fn_80112718(void);

OCTREE* fn_8004B920(void* owner, char* name)
{
	OCTREE_FILE_HEADER* header = fn_800426E0(name, 0);
	OCTREE* tree;

	if (header == NULL) {
		return NULL;
	}
	header->nodeData    = (ONODE*)((u32)header->nodeData + (u32)header);
	header->polygonData = (POLYDATA*)((u32)header->polygonData + (u32)header);
	header->vertexData  = (RwV3d*)((u32)header->vertexData + (u32)header);
	tree                = new OCTREE(header);
	fn_8004B6DC(owner, tree, tree->nodeData, header);
	fn_80112718();
	return tree;
}
}
