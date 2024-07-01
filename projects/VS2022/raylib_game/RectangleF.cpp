#include "RectangleF.h"


RectangleF::RectangleF(Vector3 position, Vector3 size, Color color, Layers::Layer layer):
	Shape(position,size,color)
{
	Vector3 min{ position.x - size.x * 0.5f, position.y - size.y * 0.5f, position.z - size.z * 0.5f };
	Vector3 max{ position.x + size.x * 0.5f, position.y + size.y * 0.5f, position.z + size.z * 0.5f };
	boxCollider = Collideable{ BoundingBox{ min , max }, layer };
}

void RectangleF::Draw()
{
	DrawCube(position, size.x, size.y, size.z, color);
	DrawBoundingBox(boxCollider.GetCollider(), RED);
}

void RectangleF::ReadInput()
{
}

void RectangleF::Update(const float deltaTime)
{
}

Collideable& RectangleF::GetCollideable()
{
	return boxCollider;
}
