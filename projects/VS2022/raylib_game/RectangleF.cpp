#include "RectangleF.h"


RectangleF::RectangleF(Vector3 position, Vector3 size, Color color):
	Shape(position,size,color)
{

}

void RectangleF::Draw()
{
	DrawCube(position, size.x, size.y, size.z, color);
}

void RectangleF::ReadInput()
{
	moveDelta = {};

	if (IsKeyDown(KEY_W))
		moveDelta.y += 1.f;
	if (IsKeyDown(KEY_S))
		moveDelta.y -= 1.f;
	if (IsKeyDown(KEY_A))
		moveDelta.x += 1.f;
	if (IsKeyDown(KEY_D))
		moveDelta.x -= 1.f;
}

void RectangleF::Update(const float deltaTime)
{
	position.x += speed * Vector2Normalize(moveDelta).x * deltaTime;
	position.z += speed * Vector2Normalize(moveDelta).y * deltaTime;
}
