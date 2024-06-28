#pragma once
#include "Shape.h"

class RectangleF : public Shape{
public:
	RectangleF() = default;
	RectangleF(Vector3 position, Vector3 size, Color color);
	void Draw();
};