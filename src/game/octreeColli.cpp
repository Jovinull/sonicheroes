#include "game/octree.h"
// Complete inferred octreeColli.cpp range: 0x800546F4--0x800569BC.
// Native reconstruction in progress; no instruction postprocessing.
void* operator new(unsigned long);
extern "C" f64 __fabs(f64);
extern "C" {
u32 lbl_80242B28[4] = { 1, 2, 4, 8 };
}
extern "C" f32 fn_801991B4(RwV3d*);
extern "C" void fn_801990E0(RwV3d*, RwV3d*);
extern "C" f32 fn_800D71DC(const RwV3d*, const RwV3d*);
extern "C" s32 fn_800D218C(const RwV3d*, f32, const RwV3d*, RwV3d*, RwV3d*);
extern "C" s32 fn_800D2ED4(const RwV3d*, f32, RwV3d*, const RwV3d*, RwV3d*, RwV3d*, s16*);

void OCTREE::OmitSameSurfacePolygons(ColliPolyLinearList* list)
{
	OCTREE* context = this;
	POLYDATA* currentLookup;
	RwV3d* currentVector;
	ColliPolyLinearListNode* current = list->topNode;
	f64 threshold                    = 0.0001;
	while (current != 0) {
		ColliPolyLinearListNode* next      = current->nextNode;
		currentLookup                      = &context->polygonData[current->no];
		currentVector                      = &context->vertexData[currentLookup->vertexIndexNo[0]];
		ColliPolyLinearListNode* candidate = current->nextNode;
		while (candidate != 0) {
			ColliPolyLinearListNode* candidateNext = candidate->nextNode;
			POLYDATA* candidateLookup              = &context->polygonData[candidate->no];
			RwV3d* candidateVector = &context->vertexData[candidateLookup->vertexIndexNo[0]];
			if ((f32)__fabs(currentLookup->norm.x - candidateLookup->norm.x) < threshold
			    && (f32)__fabs(currentLookup->norm.y - candidateLookup->norm.y) < threshold
			    && (f32)__fabs(currentLookup->norm.z - candidateLookup->norm.z) < threshold) {
				f32 projected = currentLookup->norm.x * (candidateVector->x - currentVector->x)
				    + currentLookup->norm.y * (candidateVector->y - currentVector->y)
				    + currentLookup->norm.z * (candidateVector->z - currentVector->z);
				if ((f32)__fabs(projected) < threshold) {
					s32 candidateFlags = candidate->on_edge & 0x70;
					if (candidateFlags != 0) {
						if ((current->on_edge & 0x70) == 0) {
							goto removeCandidate;
						}
					}
					if ((s32)(candidateFlags != 0) == (s32)((current->on_edge & 0x70) != 0)) {
						f32 currentLength = current->ansVec.x * current->ansVec.x
						    + current->ansVec.y * current->ansVec.y
						    + current->ansVec.z * current->ansVec.z;
						f32 candidateLength = candidate->ansVec.x * candidate->ansVec.x
						    + candidate->ansVec.y * candidate->ansVec.y
						    + candidate->ansVec.z * candidate->ansVec.z;
						if (currentLength < candidateLength) {
							goto removeCandidate;
						} else {
							goto removeCurrent;
						}
					}
					goto removeCurrent;
				removeCandidate:
					if (candidate == next)
						next = candidateNext;
					list->Delete(candidate);
					goto nextCandidate;
				removeCurrent:
					list->Delete(current);
					break;
				}
			}
		nextCandidate:
			candidate = candidateNext;
		}
		current = next;
	}
}

static inline f32 fn_80054900LengthSq(const RwV3d& value)
{
	return value.x * value.x + value.y * value.y + value.z * value.z;
}

static inline f32 fn_80054900Square(f32 value)
{
	return value * value;
}

static inline void fn_80054900ClearWords(u32*& output, s32 count)
{
	while (count > 0) {
		*output++ = 0;
		count--;
	}
}

static inline u32 fn_80054900TriangleIndex(ONODE* cell, s32 triangleSlot)
{
	if (cell->numPoly == 1 || (cell->numPoly == 2 && triangleSlot == 0)) {
		return (u32)cell->polyIndex & 0x7FFF;
	}
	if (cell->numPoly == 2 && triangleSlot == 1) {
		return ((u32)cell->polyIndex & 0x7FFF0000) >> 16;
	}
	return cell->polyIndex[triangleSlot];
}

ColliPolyLinearList* OCTREE::DetectMovingSphereCollisionWithPolygons(RwV3d* point, f32 radius,
    RwV3d* direction, ENUM_CL_MOVING* contactType, s32 (*predicate)(POLYDATA*))
{
	OCTREE* grid    = this;
	RwV3d* movement = direction;
	u32 rawTriangleIndex;
	s32 visitedMask;
	s32 visitedWord;
	ONODE* cell;
	s32 triangleSlot;
	RwV3d secondContact;
	RwV3d firstContact;
	RwV3d remainingDirection;
	RwV3d normalizedDirection;
	RwV3d surfacePoint;
	RwV3d correction;
	RwV3d resolvedPoint;
	ColliPolyLinearList* contacts = 0;
	s32 words;
	if (fn_801991B4(movement) > 0.0f) {
		fn_801990E0(&normalizedDirection, movement);
	} else {
		normalizedDirection.z = 0.0f;
		normalizedDirection.y = 0.0f;
		normalizedDirection.x = 0.0f;
	}

	*contactType             = CL_MOVING_NONE;
	remainingDirection.x     = movement->x;
	remainingDirection.y     = movement->y;
	remainingDirection.z     = movement->z;
	grid->IntersectionEnable = 1;

	s32 wordsLeft;
	u32 activeBlocks;
	u32* visited;
	visited      = grid->polygonFlagBuff;
	activeBlocks = grid->polyFlagBlock;
	wordsLeft    = grid->polygonFlagBuffSize;
	while (activeBlocks != 0) {
		if ((activeBlocks & 1) != 0) {
			if (wordsLeft >= 64) {
				words = 64;
			} else {
				words = wordsLeft;
			}
			fn_80054900ClearWords(visited, words);
		}
		visited += 64;
		wordsLeft -= 64;
		activeBlocks >>= 1;
	}
	grid->polyFlagBlock = 0;

	MiniLinearList* traversal = MakeIntersectionNodeListWithCapsule(point, movement, radius);
	if (traversal == 0)
		return 0;

	f32 reachSq = radius * radius + fn_80054900LengthSq(*movement);
	while (traversal != 0) {
		cell = &grid->nodeData[traversal->no];
		for (triangleSlot = 0; triangleSlot < cell->numPoly; triangleSlot++) {
			rawTriangleIndex  = fn_80054900TriangleIndex(cell, triangleSlot);
			u16 triangleIndex = (u16)rawTriangleIndex;

			visitedMask = 1 << (triangleIndex & 31);
			visitedWord = triangleIndex >> 5;
			if ((s32)(grid->polygonFlagBuff[visitedWord] & visitedMask) == 0) {
				POLYDATA* triangle = &grid->polygonData[rawTriangleIndex];
				f32 facing         = normalizedDirection.x * triangle->norm.x
				    + normalizedDirection.y * triangle->norm.y
				    + normalizedDirection.z * triangle->norm.z;
				s32 facingAccepted = 0;
				if (facing < 0.001f)
					facingAccepted = 1;
				if (facingAccepted == 1 && (predicate == 0 || predicate(triangle) != 0)) {
					RwV3d triangleVertices[3];
					triangleVertices[0] = grid->vertexData[triangle->vertexIndexNo[0]];
					triangleVertices[1] = grid->vertexData[triangle->vertexIndexNo[1]];
					triangleVertices[2] = grid->vertexData[triangle->vertexIndexNo[2]];

					f32 triangleReachSq
					    = fn_80054900Square(triangleVertices[1].x - triangleVertices[0].x);
					f32 alternateReachSq
					    = fn_80054900Square(triangleVertices[0].x - triangleVertices[2].x);
					triangleReachSq
					    += fn_80054900Square(triangleVertices[1].y - triangleVertices[0].y);
					alternateReachSq
					    += fn_80054900Square(triangleVertices[0].y - triangleVertices[2].y);
					triangleReachSq
					    += fn_80054900Square(triangleVertices[1].z - triangleVertices[0].z);
					alternateReachSq
					    += fn_80054900Square(triangleVertices[0].z - triangleVertices[2].z);
					if (triangleReachSq < alternateReachSq)
						triangleReachSq = alternateReachSq;
					triangleReachSq += reachSq;
					triangleReachSq
					    -= (triangleVertices[0].x - point->x) * (triangleVertices[0].x - point->x);
					s32 inReach = 0;
					if (triangleReachSq > 0.0f) {
					} else {
						goto reachTest;
					}
					triangleReachSq
					    -= (triangleVertices[0].y - point->y) * (triangleVertices[0].y - point->y);
					if (triangleReachSq > 0.0f) {
					} else {
						goto reachTest;
					}
					triangleReachSq
					    -= (triangleVertices[0].z - point->z) * (triangleVertices[0].z - point->z);
					if (triangleReachSq > 0.0f)
						inReach = 1;
				reachTest:
					if (inReach != 0) {
						if (grid->IntersectionEnable == 1 && *contactType == 2) {
							if (fn_800D218C(
							        point, radius, triangleVertices, &surfacePoint, &correction)
							    != 0) {
								resolvedPoint.x = point->x + correction.x;
								resolvedPoint.y = point->y + correction.y;
								resolvedPoint.z = point->z + correction.z;
								contacts->Insert(
								    (u16)rawTriangleIndex, 0, &resolvedPoint, &surfacePoint, 0);
							}
						} else {
							s16 secondaryValue = 0;
							s32 result         = fn_800D2ED4(point, radius, &remainingDirection,
							    triangleVertices, &firstContact, &secondContact, &secondaryValue);
							if (result != 0) {
								if (contacts == 0) {
									contacts = new ColliPolyLinearList;
								}
								if (grid->IntersectionEnable == 1) {
									if (result == 2) {
										contacts->Insert((u16)rawTriangleIndex, 0, &secondContact,
										    &firstContact, &secondaryValue);
										*contactType = CL_MOVING_INTERSECTION;
									} else {
										contacts->Insert((u16)rawTriangleIndex, &firstContact,
										    &secondContact, 0, &secondaryValue);
										*contactType       = CL_MOVING_COLLISION;
										remainingDirection = firstContact;
									}
								} else if (fn_80054900LengthSq(remainingDirection) > 0.0f) {
									contacts->Insert((u16)rawTriangleIndex, &firstContact,
									    &secondContact, 0, &secondaryValue);
									*contactType = CL_MOVING_COLLISION;
								} else {
									contacts->Insert((u16)rawTriangleIndex, 0, &secondContact,
									    &firstContact, &secondaryValue);
									*contactType = CL_MOVING_INTERSECTION;
								}
							}
						}
					}
				}
				grid->polygonFlagBuff[visitedWord] |= visitedMask;
				grid->polyFlagBlock |= 1 << (triangleIndex >> 11);
			}
		}
		MiniLinearList* next = traversal->nextNode;
		DeleteNode_MiniLinearList(traversal);
		traversal = next;
	}
	return contacts;
}

static void fn_80054F08ClearVisited(s32 wordCount, u32 activeBlocks, u32* visited)
{
	for (; activeBlocks != 0; visited += 64, wordCount -= 64, activeBlocks >>= 1) {
		if ((activeBlocks & 1) != 0) {
			s32 words;
			if (wordCount >= 64) {
				words = 64;
			} else {
				words = wordCount;
			}
			while (words > 0) {
				*visited++ = 0;
				words--;
			}
		}
		continue;
	}
}

static inline u32 fn_80054F08TriangleIndex(ONODE* cell, s32 triangleSlot)
{
	if (cell->numPoly == 1 || (cell->numPoly == 2 && triangleSlot == 0)) {
		return (u32)cell->polyIndex & 0x7FFF;
	}
	if (cell->numPoly == 2 && triangleSlot == 1) {
		return ((u32)cell->polyIndex & 0x7FFF0000) >> 16;
	}
	return cell->polyIndex[triangleSlot];
}

ColliPolyLinearList* OCTREE::DetectSphereCollisionWithPolygons(
    RwV3d* point, f32 radius, s32 (*predicate)(POLYDATA*))
{
	OCTREE* grid = this;
	u32 rawTriangleIndex;
	s32 visitedWord;
	u32 visitedMask;
	ONODE* cell;
	ONODE* currentCell;
	s32 triangleSlot;
	POLYDATA* triangle;
	MiniLinearList* traversal;
	ColliPolyLinearList* contacts;
	MiniLinearList* next;
	RwV3d triangleVertices[3];
	RwV3d surfacePoint;
	RwV3d correction;
	RwV3d resolvedPoint;
	RwV3d center;
	RwV3d lower;
	RwV3d upper;
	f32 extent;
	contacts = 0;
	fn_80054F08ClearVisited(grid->polygonFlagBuffSize, grid->polyFlagBlock, grid->polygonFlagBuff);
	grid->polyFlagBlock = 0;
	fn_80054F08ClearVisited(grid->nodeFlagBuffSize, grid->nodeFlagBlock, grid->nodeFlagBuff);
	grid->nodeFlagBlock = 0;

	upper.x = point->x + radius;
	upper.z = point->z + radius;
	lower.x = point->x - radius;
	lower.z = point->z - radius;

	cell = GetNodeFromPosition(point);
	GetCenterPosition(cell, &center);
	extent = grid->nodeHalfLengthEachDepth[cell->depth];
	MiniLinearList* selectedTraversal;
	if (upper.x < extent + center.x && center.x - extent < lower.x && upper.z < extent + center.z
	    && center.z - extent < lower.z) {
		selectedTraversal = AddNode_MiniLinearList(0, cell->nodeNo);
	} else {
		selectedTraversal
		    = MakeIntersectionNodeListWithSmallSphere_Sub(0, cell, point, radius, &upper, &lower);
	}
	traversal = selectedTraversal;
	if (traversal == 0)
		return 0;

	f32 radiusSq = radius * radius;
	while (traversal != 0) {
		currentCell = &grid->nodeData[traversal->no];
		for (triangleSlot = 0; triangleSlot < currentCell->numPoly; triangleSlot++) {
			rawTriangleIndex  = fn_80054F08TriangleIndex(currentCell, triangleSlot);
			u16 triangleIndex = (u16)rawTriangleIndex;

			visitedMask = 1 << (triangleIndex & 31);
			visitedWord = triangleIndex >> 5;
			if ((s32)(grid->polygonFlagBuff[visitedWord] & visitedMask) == 0) {
				triangle = &grid->polygonData[rawTriangleIndex];
				if (predicate == 0 || predicate(triangle) != 0) {
					triangleVertices[0] = grid->vertexData[triangle->vertexIndexNo[0]];
					triangleVertices[1] = grid->vertexData[triangle->vertexIndexNo[1]];
					triangleVertices[2] = grid->vertexData[triangle->vertexIndexNo[2]];

					f32 reachSq          = fn_800D71DC(&triangleVertices[1], &triangleVertices[0]);
					f32 alternateReachSq = fn_800D71DC(&triangleVertices[2], &triangleVertices[0]);
					if (reachSq < alternateReachSq)
						reachSq = alternateReachSq;
					reachSq += radiusSq;
					reachSq
					    -= (triangleVertices[0].x - point->x) * (triangleVertices[0].x - point->x);
					s32 inReach = 0;
					if (reachSq > 0.0f) {
					} else {
						goto reachTest;
					}
					reachSq
					    -= (triangleVertices[0].y - point->y) * (triangleVertices[0].y - point->y);
					if (reachSq > 0.0f) {
					} else {
						goto reachTest;
					}
					reachSq
					    -= (triangleVertices[0].z - point->z) * (triangleVertices[0].z - point->z);
					if (reachSq > 0.0f)
						inReach = 1;
				reachTest:
					if (inReach != 0) {
						if (fn_800D218C(point, radius, triangleVertices, &surfacePoint, &correction)
						    != 0) {
							resolvedPoint.x = point->x + correction.x;
							resolvedPoint.y = point->y + correction.y;
							resolvedPoint.z = point->z + correction.z;
							if (contacts == 0) {
								contacts = new ColliPolyLinearList;
							}
							contacts->Insert((u16)rawTriangleIndex, &correction, &resolvedPoint,
							    &surfacePoint, 0);
						}
					}
				}
				grid->polygonFlagBuff[visitedWord] |= visitedMask;
				grid->polyFlagBlock |= 1 << (triangleIndex >> 11);
			}
		}
		next = traversal->nextNode;
		DeleteNode_MiniLinearList(traversal);
		traversal = next;
	}
	return contacts;
}

MiniLinearList* OCTREE::MakeIntersectionNodeListWithCapsule_Sub(
    MiniLinearList* result, const ONODE* node, const RwV3d* upper, const RwV3d* lower)
{
	OCTREE* grid = this;
	RwV3d center;
	RwV3d maximum;
	RwV3d minimum;
	f32 extent = grid->nodeHalfLengthEachDepth[node->depth];
	GetCenterPosition(node, &center);
	maximum.x = center.x + extent;
	maximum.z = center.z + extent;
	minimum.x = center.x - extent;
	minimum.z = center.z - extent;

	if (lower->x <= minimum.x && maximum.x <= upper->x && lower->z <= minimum.z
	    && maximum.z <= upper->z) {
		if (node->numPoly != 0)
			result = AddNode_MiniLinearList(result, node->nodeNo);
		return result;
	}
	if (node->childNo != 0) {
		u8 selection = 0;
		if (upper->x < center.x)
			selection = 0xA;
		else if (center.x < lower->x)
			selection = 5;
		if (upper->z < center.z)
			selection |= 0xC;
		else if (center.z < lower->z)
			selection |= 3;
		for (s32 index = 0; index < 4; index++) {
			if ((s32)(selection & lbl_80242B28[index]) == 0)
				result = MakeIntersectionNodeListWithCapsule_Sub(
				    result, &grid->nodeData[node->childNo + index], upper, lower);
		}
	} else if (node->numPoly != 0) {
		if (((lower->x <= minimum.x && minimum.x <= upper->x)
		        || (minimum.x <= lower->x && lower->x <= maximum.x))
		    && ((lower->z <= minimum.z && minimum.z <= upper->z)
		        || (minimum.z <= lower->z && lower->z <= maximum.z)))
			result = AddNode_MiniLinearList(result, node->nodeNo);
	}
	return result;
}

MiniLinearList* OCTREE::MakeIntersectionNodeListWithCapsule(
    const RwV3d* point, const RwV3d* direction, f32 radius)
{
	OCTREE* grid = this;
	RwV3d upper;
	RwV3d lower;
	u8 selection           = 0;
	f32 halfExtent         = 0.5f * grid->rootLength;
	MiniLinearList* result = 0;

	if (direction->x >= 0.0f) {
		upper.x = point->x + direction->x + radius;
		lower.x = point->x - radius;
	} else {
		upper.x = point->x + radius;
		lower.x = point->x + direction->x - radius;
	}
	if (direction->z >= 0.0f) {
		upper.z = point->z + direction->z + radius;
		lower.z = point->z - radius;
	} else {
		upper.z = point->z + radius;
		lower.z = point->z + direction->z - radius;
	}

	if (upper.x < grid->rootCenter.x - halfExtent || grid->rootCenter.x + halfExtent < lower.x
	    || upper.z < grid->rootCenter.z - halfExtent || grid->rootCenter.z + halfExtent < lower.z) {
		return 0;
	}

	if (upper.x < grid->rootCenter.x)
		selection = 0xA;
	else if (grid->rootCenter.x < lower.x)
		selection = 5;
	if (upper.z < grid->rootCenter.z)
		selection |= 0xC;
	else if (grid->rootCenter.z < lower.z)
		selection |= 3;

	for (s32 index = 0; index < 4; index++) {
		if ((s32)(selection & lbl_80242B28[index]) == 0) {
			result = MakeIntersectionNodeListWithCapsule_Sub(
			    result, &grid->nodeData[grid->nodeData->childNo + index], &upper, &lower);
		}
	}
	return result;
}

MiniLinearList* OCTREE::MakeIntersectionNodeListWithSmallSphere_Sub(MiniLinearList* result,
    const ONODE* node, const RwV3d* point, f32 radius, const RwV3d* upper, const RwV3d* lower)
{
	OCTREE* grid = this;
	s32 neighbourIndex;
	u8 selection = 0;
	f32 extent   = grid->nodeHalfLengthEachDepth[node->depth];
	RwV3d center;
	{
		u16 value = node->nodeNo;
		grid->nodeFlagBuff[value >> 5] |= 1 << (value & 31);
		grid->nodeFlagBlock |= 1 << (value >> 11);
	}
	GetCenterPosition(node, &center);

	if (node->childNo != 0) {
		if (upper->x < center.x)
			selection = 0xA;
		else if (center.x < lower->x)
			selection = 5;
		if (upper->z < center.z)
			selection |= 0xC;
		else if (center.z < lower->z)
			selection |= 3;

		for (s32 index = 0; index < 4; index++) {
			s32 child      = node->childNo + index;
			u16 childIndex = child;
			if ((s32)(grid->nodeFlagBuff[childIndex >> 5] & (1 << (childIndex & 31))) == 0
			    && (s32)(selection & lbl_80242B28[index]) == 0) {
				result = MakeIntersectionNodeListWithSmallSphere_Sub(
				    result, &grid->nodeData[child], point, radius, upper, lower);
			}
		}
	} else if (node->numPoly != 0) {
		f32 leafExtent = grid->nodeHalfLengthEachDepth[node->depth];
		s32 region     = 0;
		f32 deltaX;
		deltaX           = point->x - center.x;
		const f32 deltaZ = point->z - center.z;
		s32 intersects;

		if (leafExtent < deltaX)
			region = 1;
		else if (deltaX < -leafExtent)
			region = 2;
		if (leafExtent < deltaZ)
			region += 3;
		else if (deltaZ < -leafExtent)
			region += 6;

		switch (region) {
			case 0:
				intersects = true;
				break;
			case 1:
			case 2:
				intersects = (f32)__fabs(deltaX) <= leafExtent + radius;
				break;
			case 3:
			case 6:
				intersects = (f32)__fabs(deltaZ) <= leafExtent + radius;
				break;
			case 4:
			case 5:
			case 7:
			case 8:
				f32 cornerX = (f32)__fabs(deltaX) - leafExtent;
				f32 cornerZ = (f32)__fabs(deltaZ) - leafExtent;
				intersects  = cornerX * cornerX + cornerZ * cornerZ <= radius * radius;
				break;
			default:
				intersects = false;
				break;
		}
		if (intersects)
			result = AddNode_MiniLinearList(result, node->nodeNo);
	}

	for (neighbourIndex = 0; neighbourIndex <= 3; neighbourIndex++) {
		u16 neighbour = node->neighborNo[neighbourIndex];
		if ((s32)neighbour != 0
		    && (s32)(grid->nodeFlagBuff[neighbour >> 5] & (1 << (neighbour & 31))) == 0) {
			switch (neighbourIndex) {
				case 0:
					if (upper->x < center.x + extent)
						continue;
					break;
				case 1:
					if (lower->x > center.x - extent)
						continue;
					break;
				case 2:
					if (upper->z < center.z + extent)
						continue;
					break;
				case 3:
					if (lower->z > center.z - extent)
						continue;
					break;
			}
			result = MakeIntersectionNodeListWithSmallSphere_Sub(
			    result, &grid->nodeData[neighbour], point, radius, upper, lower);
		}
	}
	return result;
}

ONODE* OCTREE::GetNextNeighborNode(
    const ONODE* node, const RwV3d* start, const RwV3d* end, RwV3d* boundary)
{
	f32 ratio = 0.0f;
	f32 half  = nodeHalfLengthEachDepth[node->depth];
	f32 dx    = end->x - start->x;
	f32 dz    = end->z - start->z;
	RwV3d center;
	GetCenterPosition(node, &center);
	f32 x = start->x - center.x;
	f32 z = start->z - center.z;
	s32 side;
	if (dx != 0.0f) {
		s32 negative = dx < 0.0f;
		if (negative) {
			dx = -dx;
			x  = -x;
		}
		if (x < half && x + dx > half) {
			ratio = dx / (half - x);
			side  = negative ? 1 : 0;
		}
	}
	if (dz != 0.0f) {
		s32 negative = dz < 0.0f;
		if (negative) {
			dz = -dz;
			z  = -z;
		}
		if (z < half && z + dz > half) {
			f32 candidate = dz / (half - z);
			if (ratio < candidate) {
				ratio = candidate;
				side  = negative ? 3 : 2;
			}
		}
	}
	if (ratio == 0.0f)
		return 0;
	if (node->neighborNo[side] == 0)
		return 0;
	ONODE* next  = &nodeData[node->neighborNo[side]];
	f32 fraction = 1.0f / ratio;
	f32 bx       = start->x + fraction * (end->x - start->x);
	f32 bz       = start->z + fraction * (end->z - start->z);
	// Retail stores an uninitialized f31 into Y; traversal only uses X/Z.
	f32 by;
	while (next->childNo != 0) {
		GetCenterPosition(next, &center);
		s32 child = bx >= center.x ? 1 : 0;
		if (bz >= center.z)
			child |= 2;
		next = &nodeData[next->childNo + child];
	}
	if (boundary) {
		boundary->x = bx;
		boundary->y = by;
		boundary->z = bz;
	}
	return next;
}

extern "C" RwV3d lbl_80239984;
extern "C" s32 fn_800D1C04(const RwV3d*, const RwV3d*, const RwV3d*, RwV3d*, u32*);
extern "C" s32 fn_800D1CE0(const RwV3d*, const RwV3d*, const RwV3d*, RwV3d*, u32*);

static inline void ClearPolygonFlags(OCTREE* tree)
{
	u32* flags    = tree->polygonFlagBuff;
	u32 blocks    = tree->polyFlagBlock;
	s32 wordsLeft = tree->polygonFlagBuffSize;
	while (blocks) {
		if (blocks & 1) {
			s32 count = wordsLeft >= 64 ? 64 : wordsLeft;
			while (count > 0) {
				*flags++ = 0;
				count--;
			}
		} else
			flags += 64;
		wordsLeft -= 64;
		blocks >>= 1;
	}
	tree->polyFlagBlock = 0;
}
static inline void SetPolygonFlag(OCTREE* tree, u16 no)
{
	tree->polygonFlagBuff[no >> 5] |= 1 << (no & 31);
	tree->polyFlagBlock |= 1 << (no >> 11);
}
static inline void SetNeighborPolygonFlags(OCTREE* tree, POLYDATA* polygon, u32 flags)
{
	if ((flags & 7) == 0) {
		if (polygon->neighbor[0] != 0xffff && (flags & 0x4d))
			SetPolygonFlag(tree, polygon->neighbor[0]);
		if (polygon->neighbor[1] != 0xffff && (flags & 0x27))
			SetPolygonFlag(tree, polygon->neighbor[1]);
		if (polygon->neighbor[2] != 0xffff && (flags & 0x1b))
			SetPolygonFlag(tree, polygon->neighbor[2]);
	}
}
POLYDATA* OCTREE::DetectAxisYCollisionWithPolygons(
    const RwV3d* start, f32 distance, RwV3d* result, s32 (*predicate)(POLYDATA*))
{
	POLYDATA* collision = 0;
	f32 dx              = lbl_80239984.x * distance;
	f32 dz              = lbl_80239984.z * distance;
	f32 dy              = lbl_80239984.y * distance;
	ClearPolygonFlags(this);
	ONODE* node = GetNodeFromPosition(start);
	if (!node)
		return 0;
	RwV3d end, movement, boundary, contact, vertices[3];
	do {
		end.x       = start->x;
		end.y       = start->y + dy;
		end.z       = start->z;
		ONODE* next = GetNextNeighborNode(node, start, &end, &boundary);
		movement.x  = dx;
		movement.y  = dy;
		movement.z  = dz;
		for (s32 slot = 0; slot < node->numPoly; slot++) {
			u32 raw  = fn_80054900TriangleIndex(node, slot);
			u16 no   = raw;
			u32 mask = 1 << (no & 31);
			s32 word = no >> 5;
			if ((s32)(polygonFlagBuff[word] & mask) == 0) {
				POLYDATA* polygon = &polygonData[raw];
				u32 flags         = 0x80;
				if (!predicate || predicate(polygon)) {
					vertices[0] = vertexData[polygon->vertexIndexNo[0]];
					vertices[1] = vertexData[polygon->vertexIndexNo[1]];
					vertices[2] = vertexData[polygon->vertexIndexNo[2]];
					s32 outside = 1;
					for (s32 i = 2; i >= 0; i--) {
						f32 delta = vertices[i].y - start->y;
						if (!((distance < 0.0f && delta < distance)
						        || (distance > 0.0f && delta > distance))) {
							outside = 0;
							break;
						}
					}
					if (outside != 1 && fn_800D1C04(start, &movement, vertices, &contact, &flags)) {
						end        = contact;
						dy         = contact.y - start->y;
						movement.y = dy;
						collision  = polygon;
					}
				}
				polygonFlagBuff[word] |= mask;
				polyFlagBlock |= 1 << (no >> 11);
				SetNeighborPolygonFlags(this, polygon, flags);
			}
		}
		if (collision)
			break;
		node = next;
	} while (node);
	if (collision && result)
		*result = end;
	return collision;
}
POLYDATA* OCTREE::DetectLineCollisionWithPolygons(
    const RwV3d* start, const RwV3d* direction, RwV3d* result, s32 (*predicate)(POLYDATA*))
{
	POLYDATA* collision = 0;
	f32 dx = direction->x, dy = direction->y, dz = direction->z;
	ClearPolygonFlags(this);
	ONODE* node = GetNodeFromPosition(start);
	if (!node)
		return 0;
	RwV3d end, movement, boundary, contact, vertices[3];
	do {
		end.x        = start->x + dx;
		end.y        = start->y + dy;
		end.z        = start->z + dz;
		ONODE* next  = GetNextNeighborNode(node, start, &end, &boundary);
		movement.x   = dx;
		movement.y   = dy;
		movement.z   = dz;
		f32 lengthSq = direction->z * direction->z
		    + (direction->x * direction->x + direction->y * direction->y);
		for (s32 slot = 0; slot < node->numPoly; slot++) {
			u32 raw  = fn_80054900TriangleIndex(node, slot);
			u16 no   = raw;
			u32 mask = 1 << (no & 31);
			s32 word = no >> 5;
			if ((s32)(polygonFlagBuff[word] & mask) == 0) {
				POLYDATA* polygon = &polygonData[raw];
				u32 flags         = 0x80;
				if (!predicate || predicate(polygon)) {
					vertices[0] = vertexData[polygon->vertexIndexNo[0]];
					vertices[1] = vertexData[polygon->vertexIndexNo[1]];
					vertices[2] = vertexData[polygon->vertexIndexNo[2]];
					f32 reach   = fn_80054900Square(vertices[1].x - vertices[0].x)
					    + fn_80054900Square(vertices[1].y - vertices[0].y)
					    + fn_80054900Square(vertices[1].z - vertices[0].z);
					f32 other = fn_80054900Square(vertices[0].x - vertices[2].x)
					    + fn_80054900Square(vertices[0].y - vertices[2].y)
					    + fn_80054900Square(vertices[0].z - vertices[2].z);
					if (reach < other)
						reach = other;
					reach += lengthSq;
					reach -= fn_80054900Square(vertices[0].x - start->x);
					s32 inReach = 0;
					if (reach > 0.0f) {
						reach -= fn_80054900Square(vertices[0].y - start->y);
						if (reach > 0.0f) {
							reach -= fn_80054900Square(vertices[0].z - start->z);
							if (reach > 0.0f)
								inReach = 1;
						}
					}
					if (inReach && fn_800D1CE0(start, &movement, vertices, &contact, &flags)) {
						end        = contact;
						dx         = contact.x - start->x;
						dy         = contact.y - start->y;
						dz         = contact.z - start->z;
						movement.x = dx;
						movement.y = dy;
						movement.z = dz;
						collision  = polygon;
					}
				}
				polygonFlagBuff[word] |= mask;
				polyFlagBlock |= 1 << (no >> 11);
				SetNeighborPolygonFlags(this, polygon, flags);
			}
		}
		if (collision)
			break;
		node = next;
	} while (node);
	if (collision && result)
		*result = end;
	return collision;
}
