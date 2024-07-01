#include "RectangleF.h"


RectangleF::RectangleF(Vector3 position, Vector3 size, Color color):
	Shape(position,size,color)
{
	Vector3 min{ position.x - size.x * 0.5f, position.y - size.y * 0.5f, position.z - size.z * 0.5f };
	Vector3 max{ position.x + size.x * 0.5f, position.y + size.y * 0.5f, position.z + size.z * 0.5f };
	boxCollider = { min,max };
}

void RectangleF::Draw()
{
	DrawCube(position, size.x, size.y, size.z, color);
	DrawBoundingBox(boxCollider, RED);
}

void RectangleF::ReadInput()
{
}

void RectangleF::Update(const float deltaTime)
{
}

BoundingBox& RectangleF::GetCollider()
{
	return boxCollider;
}
