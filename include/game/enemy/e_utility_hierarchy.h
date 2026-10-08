#ifndef GAME_E_UTILITY_HIERARCHY_H
#define GAME_E_UTILITY_HIERARCHY_H

struct RpAtomic;
struct RpClump;
struct RpHAnimHierarchy;
struct RwFrame;

namespace nHierarchy
{
RpAtomic* SetHierarchyForSkinAtomic(RpAtomic* atomic, void* data);
RpHAnimHierarchy* GetHierarchy(RpClump* clump);
RwFrame* GetChildFrameHierarchy(RwFrame* frame, void* data);
}

#endif
