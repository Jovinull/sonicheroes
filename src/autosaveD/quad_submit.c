#include "types.h"

typedef struct Vec2 {
	f32 x;
	f32 y;
} Vec2;

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct TexCoords {
	f32 left;
	f32 top;
	f32 right;
	f32 bottom;
} TexCoords;

typedef struct Color {
	u8 value[4];
} Color;

typedef struct Vertex {
	Vec3 position;
	u8 color[4];
	Vec2 texcoord;
} Vertex;

extern "C" const Color lbl_2_rodata_D0;

extern "C" void fn_801942C0(s32 primitive, Vertex* vertices, s32 count);

extern "C" void fn_2_31F0(
    void* context, Vec3* position, Vec2* size, TexCoords* texcoords, f32 unused)
{
	Color color = lbl_2_rodata_D0;
	Vertex vertices[4];
	u8& alpha = color.value[3];
	u8& blue  = color.value[2];
	u8& green = color.value[1];
	u8& red   = color.value[0];

	vertices[0].position.x = position->x;
	vertices[0].position.y = position->y;
	vertices[0].position.z = position->z;
	vertices[0].color[0]   = red;
	vertices[0].color[1]   = green;
	vertices[0].color[2]   = blue;
	vertices[0].color[3]   = alpha;
	vertices[0].texcoord.x = texcoords->left;
	vertices[0].texcoord.y = texcoords->top;

	vertices[1].position.x = position->x;
	vertices[1].position.y = position->y + size->y;
	vertices[1].position.z = position->z;
	vertices[1].color[0]   = red;
	vertices[1].color[1]   = green;
	vertices[1].color[2]   = blue;
	vertices[1].color[3]   = alpha;
	vertices[1].texcoord.x = texcoords->left;
	vertices[1].texcoord.y = texcoords->bottom;

	vertices[2].position.x = position->x + size->x;
	vertices[2].position.y = position->y;
	vertices[2].position.z = position->z;
	vertices[2].color[0]   = red;
	vertices[2].color[1]   = green;
	vertices[2].color[2]   = blue;
	vertices[2].color[3]   = alpha;
	vertices[2].texcoord.x = texcoords->right;
	vertices[2].texcoord.y = texcoords->top;

	vertices[3].position.x = position->x + size->x;
	vertices[3].position.y = position->y + size->y;
	vertices[3].position.z = position->z;
	vertices[3].color[0]   = red;
	vertices[3].color[1]   = green;
	vertices[3].color[2]   = blue;
	vertices[3].color[3]   = alpha;
	vertices[3].texcoord.x = texcoords->right;
	vertices[3].texcoord.y = texcoords->bottom;

	fn_801942C0(4, vertices, 4);
}
