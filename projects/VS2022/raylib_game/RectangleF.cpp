#include "RectangleF.h"
#include "raymath.h"

RectangleF::RectangleF(Vector3 position, Vector3 size, Color color):
	Shape(position,size,color)
{

}

void RectangleF::Draw()
{
	DrawCube(position, size.x, size.y, size.z, color);
}

void RectangleF::Move(float deltaTime)
{
	Vector2 moveDelta{};

	if (IsKeyDown(KEY_W))
		moveDelta.y += 1.f;
	if (IsKeyDown(KEY_S))
		moveDelta.y -= 1.f;
	if (IsKeyDown(KEY_A))
		moveDelta.x += 1.f;
	if (IsKeyDown(KEY_D))
		moveDelta.x -= 1.f;

	position.x += speed * Vector2Normalize(moveDelta).x * deltaTime;
	position.z += speed * Vector2Normalize(moveDelta).y * deltaTime;
}
