#pragma once
#include "raylib.h"

class Shape {

public:
	Shape() = default;
	Shape(Vector3 position, Vector3 size, Color color);

	virtual void Draw();
	virtual const Vector3& GetPosition() const;
	virtual const Vector3& GetSize() const;
	virtual const Color& GetColor() const;
protected:
	Vector3 position;
	Vector3 size;
	Color color;
};