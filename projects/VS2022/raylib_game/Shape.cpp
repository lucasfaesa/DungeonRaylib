#include "Shape.h"

Shape::Shape(Vector3 position, Vector3 size, Color color):
	position(position), size(size), color(color)
{
}

void Shape::Draw()
{
}

const Vector3& Shape::GetPosition() const
{
	return position;
}

const Vector3& Shape::GetSize() const
{
	return size;
}

const Color& Shape::GetColor() const
{
	return color;
}


