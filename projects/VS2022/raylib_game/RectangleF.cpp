#include "RectangleF.h"

RectangleF::RectangleF(Vector3 position, Vector3 size, Color color):
	Shape(position,size,color)
{

}

void RectangleF::Draw()
{
	DrawCube(position, size.x, size.y, size.z, color);
}
