#pragma once
#include "raylib.h"

class Shape {

public:
	Shape() = default;
	Shape(Vector3 position, Vector3 size, Color color);

	void Draw();
protected:
	Vector3 position;
	Vector3 size;
	Color color;
};