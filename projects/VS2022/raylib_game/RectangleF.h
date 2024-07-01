#pragma once
#include "Shape.h"
#include "raymath.h"
#include "Collideable.h"

class RectangleF : public Shape{
public:
	RectangleF() = default;
	RectangleF(Vector3 position, Vector3 size, Color color);
	void ReadInput();
	void Draw() override;
	void Update(const float deltaTime);
	Collideable& GetCollideable();

private:
	Collideable boxCollider;
};