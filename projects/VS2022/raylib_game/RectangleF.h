#pragma once
#include "Shape.h"

class RectangleF : public Shape{
public:
	RectangleF() = default;
	RectangleF(Vector3 position, Vector3 size, Color color);
	void Draw() override;
	void Move(const float deltaTime);
private:
	static constexpr float speed = 15.f;
};